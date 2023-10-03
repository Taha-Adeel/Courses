%require "3.8"
/* %language "c++" */
%code top{
	#include <iostream>
	#include <fstream>
	#include <filesystem>
	#include <string>
	#include "astNodes.h"

	extern int yylex();
	extern void yyrestart(FILE*);
	void yyerror(const char* s);
	extern int yylineno;

	#define YYFPRINTF(f, fmt, ...)  printf(fmt, ##__VA_ARGS__)
	#if YYDEBUG == 1
	#define PARSER_TRACE_DEBUG
	#define SYMBOL_TABLE_DEBUG
	#define AST_DEBUG
	#endif
}

%define parse.error detailed
%define parse.trace

%locations
%code requires{
	#define YYLTYPE YYLTYPE
	typedef struct YYLTYPE
	{
		int first_line;
		int first_column;
		int last_line;
		int last_column;
		std::string filename;
	} YYLTYPE;
	#define YYLTYPE_IS_DECLARED 1
	#define YYLTYPE_IS_TRIVIAL 1
}

%code{
	#include "symbolTable.h"

	SymbolTable global_symbol_table(NULL, "global");
	SymbolTable* cur_symbol_table = &global_symbol_table;
	Program* root;
}

/* Listing the different types of the terminals and non-terminals */
%union 
{
	Program *pgm;
	vector<Statement*> *stmt_list;
	vector<Expression*> *exp_list;
	Expression *exp;
	Statement* stmt;
	Identifier *t;
	string *id;
	int valuei;
	float valuef;
	bool valueb;
	string *values;
	ACCESS_SPEC *access_spec;
	FamilyMembers *class_member;
	vector<FamilyMembers*> *class_members;
	Arg* argument;
	vector<Arg*>* arg_list;
}

/* Declaring types to the different non-terminals */
%type <pgm> program
%type <stmt_list> translation_unit statement_list
%type <exp_list> new_variable_list expression_list
%type <arg_list> args_list
%type <stmt> external_declaration statement
%type <stmt> driver_definition function_declaration variable_declaration family_declaration
%type <stmt> jump_statement iteration_statement labeled_statement expression_statement
%type <stmt> selection_statement compound_statement
%type <stmt> constructor_declaration error

%type <exp> expression primary_expression iter_expression
%type <exp> new_variable literal variable
%type <argument> arg
%type <t> type
%type <access_spec> access_specifier
%type <class_member> class_member 
%type <class_members>class_members

/*** TOKEN DECLARATION ***/
%header


/* data types */
%token CONST VAR
%token <id> BOOL FLOAT INT STRING VOID 
%token <id> POINT PATH IMAGE RECTANGLE CIRCLE ELLIPSE POLYGON CURVE PI COLOUR
/* Literals */
%token <valuei> INTEGER_LITERAL
%token <valuef> FLOAT_LITERAL
%token <valueb> BOOL_LITERAL
%token <values> STRING_LITERAL

/* Control flow keywords */
%token IF ELSE SWITCH CASE DEFAULT WHILE FOR BREAK CONTINUE SEND

/* Derived data types and their member fields */
%token FAMILY INHERITS
%token PUBLIC PRIVATE 

/* Driver keyword */
%token DRIVER

/* Variables */
%token <id> IDENTIFIER

/* The operator precedence and associativity rules for the language. The higher precedence operators are listed below the lower precedence rules. */
%left ','
%right ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%right '?' ':'
%left LOGICAL_OR
%left LOGICAL_AND
%left EQ NOT_EQ
%left LS_THAN LS_THAN_EQ GR_THAN GR_THAN_EQ
%left '+' '-'
%left '*' '/' '%'
%precedence INC DEC
%precedence INC_POST DEC_POST UPLUS UMINUS LOGICAL_NOT
%left '(' ')' '[' ']' SCOPE_ACCESS

/*** RULES ***/
%%

/*------------------------------------------------------------------------
 * Translation unit
 *------------------------------------------------------------------------*/
program
	: %empty				{$$ = new Program(); root = $$;}
 	| translation_unit		{$$ = new Program($1); root = $$;}
	;

translation_unit
	: external_declaration					{$$ = new vector<Statement*>(); $$->push_back($1);}
	| translation_unit external_declaration	{$$ = $1; $$->push_back($2);}
	;

external_declaration
	: driver_definition		{$$ = $1;}
	| variable_declaration	{$$ = $1;}
	| function_declaration	{$$ = $1;}
	| family_declaration	{$$ = $1;}
	;

driver_definition
	: DRIVER 							{cur_symbol_table = cur_symbol_table->addSymbol("driver", "void->()", &@1, KIND::FUNCTION);} 
		'(' ')' compound_statement 		{$$ = new DriverDefinition($5); cur_symbol_table = cur_symbol_table->returnFromFunction();}
	;


/*----------------------------------------------------------------------
 * Declarations
 *----------------------------------------------------------------------*/
 type
	: INT   		{$$ = new Identifier("int");}
	| FLOAT   		{$$ = new Identifier("float");}
	| STRING   		{$$ = new Identifier("string");}
	| BOOL   		{$$ = new Identifier("bool");}
	| VOID		   	{$$ = new Identifier("void");}
	| POINT 		{$$ = new Identifier("Point");}
	| PATH			{$$ = new Identifier("Path");}
	| IMAGE			{$$ = new Identifier("Image");}
	| RECTANGLE 	{$$ = new Identifier("Rectangle");}
	| CIRCLE		{$$ = new Identifier("Circle");}
	| ELLIPSE		{$$ = new Identifier("Ellipse");}
	| POLYGON		{$$ = new Identifier("Polygon");}
	| CURVE			{$$ = new Identifier("Curve");}
	| PI			{$$ = new Identifier("Pi");}
	| COLOUR		{$$ = new Identifier("Colour");}
	| IDENTIFIER   	{$$ = new Identifier(*($1));}
	;

literal
	: INTEGER_LITERAL	{$$ = new IntegerLiteral($1);}
	| FLOAT_LITERAL		{$$ = new FloatLiteral($1);}
	| STRING_LITERAL	{$$ = new StringLiteral(*($1));}
	| BOOL_LITERAL		{$$ = new BooleanLiteral($1);}
	;

variable_declaration
	: VAR type { SymbolTable::currentVariableType = $2->ret_id(); }
	  		new_variable_list ';' { $$ = new VariableDeclaration(*($2), *($4)); }
	| CONST type { SymbolTable::currentVariableType = $2->ret_id(); } 
	  		new_variable_list ';' { $$ = new VariableDeclaration(*($2), *($4)); }
	;

new_variable_list
	: new_variable						 {$$ = new vector<Expression*>(); $$->push_back($1);}
	| new_variable_list ',' new_variable {$$ = $1; $$->push_back($3);}
	;

new_variable
	: IDENTIFIER 							
			{
				cur_symbol_table->addSymbol(*$1, SymbolTable::currentVariableType, &@1); 
				$$ = new Identifier(*($1));
			}
	| IDENTIFIER ASSIGN expression			
			{
				cur_symbol_table->addSymbol(*$1, SymbolTable::currentVariableType, &@1); 
				Variable* temp = new Identifier(*($1)); 
				$$ = new AssignmentExp(temp, $3);
			}
	| IDENTIFIER '(' ')'					
			{
				cur_symbol_table->addSymbol(*$1, SymbolTable::currentVariableType, &@1); 
				Variable* temp = new Identifier(*($1)); 
				$$ = new FunctionCall(temp);
			}
	| IDENTIFIER '(' expression_list ')'	
			{
				cur_symbol_table->addSymbol(*$1, SymbolTable::currentVariableType, &@1); 
				Variable* temp = new Identifier(*($1)); 
				$$ = new FunctionCall(temp, *($3));
			}
	;

function_declaration
	: type IDENTIFIER '(' 
			{ 
				cur_symbol_table = cur_symbol_table->addSymbol(*$2, $1->ret_id()+"->()", &@1, KIND::FUNCTION); 
			}
	  ')' compound_statement	
			{ 
				cur_symbol_table = cur_symbol_table->returnFromFunction(); 
				auto temp = new Identifier(*($2)); 
				$$ = new FunctionDeclaration(temp, *($1), $6); 
			}
	| type IDENTIFIER '(' 
			{
				cur_symbol_table = cur_symbol_table->addSymbol(*$2, $1->ret_id()+"->", &@1, KIND::FUNCTION);
			} 
	  args_list ')'
	  		{
				std::string arg_types = "";
				for(auto arg: *($5)) arg_types += arg->getType() + ",";
				cur_symbol_table->lookUp(*$2)->addArgTypeNames(arg_types.substr(0, arg_types.size()-1));
			}
	  compound_statement	
	  		{
				cur_symbol_table = cur_symbol_table->returnFromFunction();
				auto temp = new Identifier(*($2)); 
				$$ = new FunctionDeclaration(temp, *($1), $8, *($5));
			}
	;

args_list
	: arg				{$$ = new vector<Arg*>(); $$->push_back($1);}
	| args_list ',' arg	{$$ = $1; $$->push_back($3);}
	;

arg
	: type IDENTIFIER
			{
				cur_symbol_table->addSymbol(*$2, $1->ret_id(), &@1); 
				$$ = new Arg(*($1), Identifier(*($2)));
			}
	| VAR type IDENTIFIER	
			{
				cur_symbol_table->addSymbol(*$3, $2->ret_id(), &@1); 
				$$ = new Arg(*($2), Identifier(*($3)));
			}
	| CONST type IDENTIFIER	
			{
				cur_symbol_table->addSymbol(*$3, $2->ret_id(), &@1); 
				$$ = new Arg(*($2), Identifier(*($3)));
			}
	;

/*------------------------------------------------------------------------
 * Classes
 *------------------------------------------------------------------------*/
family_declaration
	: FAMILY IDENTIFIER '{' '}' ';'														
			{
				cur_symbol_table->addSymbol(*$2, "Family", &@1, KIND::FAMILY);
				$$ = new FamilyDecl(Identifier(*$2));
			}
	| FAMILY IDENTIFIER '{'
			{ 
				cur_symbol_table = cur_symbol_table->addSymbol(*$2, "Family", &@1, KIND::FAMILY); 
			}
	 class_members '}' ';' 	
	 		{
				$$ = new FamilyDecl(Identifier(*$2), *($5)); 
				cur_symbol_table = cur_symbol_table->endScope();
			}
	| FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' '}' ';' 				
			{
				cur_symbol_table->addSymbol(*$2, "Family", &@1, KIND::FAMILY);
				// TODO: Copy public members from parent class
				$$ = new FamilyDecl(Identifier(*($2)),optional<pair<Identifier, ACCESS_SPEC>>(make_pair(Identifier(*$5), *($4))));
			}
	| FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{'
			{
				cur_symbol_table = cur_symbol_table->addSymbol(*$2, "Family", &@1, KIND::FAMILY);
				// TODO: Copy public members from parent class
			}
	 class_members '}' ';'	
			{
				$$ = new FamilyDecl(Identifier(*($2)),*($8), optional<pair<Identifier, ACCESS_SPEC>>(make_pair(Identifier(*$5), *($4))));
				cur_symbol_table = cur_symbol_table->endScope();
			}
	;

access_specifier
	: PUBLIC 	{$$ = new ACCESS_SPEC(ACCESS_SPEC::PUBLIC);}
	| PRIVATE	{$$ = new ACCESS_SPEC(ACCESS_SPEC::PRIVATE);}
	;

class_members
	: class_member 					{$$ = new vector<FamilyMembers*>(); $$->push_back($1);}
	| class_members class_member	{$$ =$1; $$->push_back($2);}
	;

class_member
	: access_specifier variable_declaration	{$$ = new FamilyMembers(*($1), $2);}
	| access_specifier function_declaration	{$$ = new FamilyMembers(*($1), $2);}
	| constructor_declaration				{$$ = new FamilyMembers(ACCESS_SPEC::PUBLIC, $1);}
	;

constructor_declaration
	: IDENTIFIER '(' 
			{
				cur_symbol_table = cur_symbol_table->addSymbol(*$1, "void->", &@1, KIND::FUNCTION);
			} 
	  args_list ')'
	  		{
				std::string arg_types = "";
				for(auto arg: *($4)) arg_types += arg->getType() + ",";
				cur_symbol_table->lookUp(*$1)->addArgTypeNames(arg_types.substr(0, arg_types.size()-1));
			}
	  compound_statement	
	  		{
				cur_symbol_table = cur_symbol_table->returnFromFunction();
				$$ = new ConstructorDeclaration(Identifier(*($1)), $7, *($4));
			}
	;

/*------------------------------------------------------------------------
 * Expressions
 *------------------------------------------------------------------------*/
primary_expression
	: literal							{$$ = (Expression*)$1;}
	| variable							{$$ = (Expression*)$1;}
	| variable '(' ')'					{$$ = new FunctionCall($1);}
	| variable '(' expression_list ')'	{$$ = new FunctionCall($1, *($3));}
	| '(' expression ')'				{$$ = $2;}
	;

variable
	: IDENTIFIER						{$$ = new Identifier(*($1));}
	| variable SCOPE_ACCESS IDENTIFIER	{$$ = new MemberAccess((Variable*)$1, *($3));}
	| variable '[' expression ']'		{$$ = new ArrayAccess($1, $3);}
	;

expression
	: primary_expression						//$$ = $1
	| '+' expression %prec UPLUS				{$$ = new UnaryPlus($2);}
	| '-' expression %prec UMINUS				{$$ = new UnaryMinus($2);}
	| expression '*' expression					{$$ = new Multiplication($1, $3);}
	| expression '/' expression					{$$ = new Division($1, $3);}
	| expression '%' expression					{$$ = new ModularDiv($1, $3);}
	| expression '+' expression					{$$ = new Addition($1, $3);}
	| expression '-' expression					{$$ = new Subtraction($1, $3);}
	| expression EQ expression					{$$ = new CompEQ($1, $3);}
	| expression NOT_EQ expression				{$$ = new CompNEQ($1, $3);}
	| expression LS_THAN expression				{$$ = new CompLT($1, $3);}
	| expression LS_THAN_EQ expression			{$$ = new CompLE($1, $3);}
	| expression GR_THAN expression				{$$ = new CompGT($1, $3);}
	| expression GR_THAN_EQ expression			{$$ = new CompGE($1, $3);}
	| expression LOGICAL_AND expression			{$$ = new LogicalAND($1, $3);}
	| expression LOGICAL_OR expression			{$$ = new LogicalOR($1, $3);}
	| LOGICAL_NOT expression					{$$ = new LogicalNOT($2);}
	| INC variable								{$$ = new PrefixInc((Variable*)$2);}
	| DEC variable								{$$ = new PostfixDec((Variable*)$2);}
	| variable INC %prec INC_POST				{$$ = new PostfixInc((Variable*)$1);}
	| variable DEC %prec DEC_POST				{$$ = new PostfixDec((Variable*)$1);}
	| variable ASSIGN expression				{$$ = new AssignmentExp((Variable*)$1, $3);}
	| variable MUL_ASSIGN expression			{$$ = new MulAssign((Variable*)$1, $3);}
	| variable DIV_ASSIGN expression			{$$ = new DivAssign((Variable*)$1, $3);}
	| variable MOD_ASSIGN expression			{$$ = new ModAssign((Variable*)$1, $3);}
	| variable ADD_ASSIGN expression			{$$ = new AddAssign((Variable*)$1, $3);}
	| variable SUB_ASSIGN expression			{$$ = new SubAssign((Variable*)$1, $3);}
	| expression '?' expression ':' expression	{$$ = new TernaryOperator($1, $3, $5);}
	;

expression_list
	: expression						{$$ = new vector<Expression*>(); ($$)->push_back($1);}
	| expression_list ',' expression	{$$ = $1; ($$)->push_back($3);}
	;

/*------------------------------------------------------------------------
 * Statements
 *------------------------------------------------------------------------*/
statement
	: labeled_statement
	| compound_statement
	| variable_declaration
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	| error ';'
	;

compound_statement
	: '{' '}'					{$$ = new CompoundStatement(vector<Statement*>());}
	| '{' {cur_symbol_table = cur_symbol_table->startNewScope();} 
			statement_list 
	  '}' {cur_symbol_table = cur_symbol_table->endScope(); $$ = new CompoundStatement(*($3));}
	;

statement_list
	: statement					{$$ = new vector<Statement*>(); ($$)->push_back($1);}
	| statement_list statement	{$$ = $1; ($$)->push_back($2);}
	;

expression_statement
	: ';'			 	  {$$ = new ExpressionStatement();}
	| expression_list ';' {$$ = new ExpressionStatement($1);}
	;

selection_statement
	: IF '(' expression ')' compound_statement							{$$ = new IfStatement($3, (CompoundStatement*)$5);}
	| IF '(' expression ')' compound_statement ELSE compound_statement 	{$$ = new IfElseStatement($3, (CompoundStatement*)$5, (CompoundStatement*)$7);}
	| SWITCH '(' expression ')' statement								{$$ = new SwitchStatement($3, (CompoundStatement*)$5);}
	;

labeled_statement
	: IDENTIFIER ':' statement		{Expression* temp = new Identifier(*($1));$$ = new LabeledStatement(temp, $3);}
	| CASE expression ':' statement	{$$ = new CaseLabel($2, $4);}
	| DEFAULT ':' statement			{$$ = new DefaultLabel($3);}
	;

iteration_statement
	: WHILE '(' {cur_symbol_table = cur_symbol_table->startNewScope("while", true);} 
		 iter_expression ')' compound_statement											{$$ = new WhileLoop((CompoundStatement*)$6, $4); cur_symbol_table = cur_symbol_table->endScope();}
	| FOR '(' {cur_symbol_table = cur_symbol_table->startNewScope("for", true);}
		statement expression_statement iter_expression ')' compound_statement 	{$$ = new ForLoop((CompoundStatement*)$8, (ExpressionStatement*)$4, (ExpressionStatement*)$5, $6); cur_symbol_table = cur_symbol_table->endScope();}
	;

iter_expression
	:  %empty {$$ = NULL;}
	| expression
	;

jump_statement
	: CONTINUE ';' 				{$$ = new ContinueStatement();}
	| BREAK ';'					{$$ = new BreakStatement();}
	| SEND expression_statement	{$$ = new ReturnStatement((((ExpressionStatement*)$2)->getValue()).back());}
	;

%%

void init_yylloc(const char* filename){
	yylloc.first_line = yylloc.last_line = yylineno = 1;
	yylloc.first_column = yylloc.last_column = 0;
	yylloc.filename = filename;
}

int main(int argc, char **argv){
	// The parser trace is generated only if yydebug is set to 1
	#ifdef PARSER_TRACE_DEBUG
		yydebug = 1;
	#endif
	
	if(argc < 2){
		string filename = "test10.tngt";
		init_yylloc(filename.c_str());
		yyrestart(fopen(filename.c_str(), "r"));
		yyparse();
		#ifdef SYMBOL_TABLE_DEBUG
			global_symbol_table.printSymbolTable(std::cout);
		#endif
	}
    else{
        for(int i = 1; i < argc; i++){
            init_yylloc(argv[i]);
            FILE *file = fopen(argv[i], "r");
            if(file == NULL){ perror(argv[i]); return -1; }
            yyrestart(file);

			yyparse();

			#ifdef SYMBOL_TABLE_DEBUG
			int file_dir_path_size = (string(argv[i]).find_last_of('/') == string::npos) ? 0 : string(argv[i]).find_last_of('/') + 1;
			string dirname = string(argv[i]).substr(0, file_dir_path_size);
			string filename = string(argv[i]).substr(file_dir_path_size, string(argv[i]).size() - file_dir_path_size - 5);
			filesystem::create_directory(dirname + "output/");
			string symbol_table_filename = dirname + "output/" + filename + ".sym";
			ofstream symbol_table_output_file(symbol_table_filename);
			global_symbol_table.printSymbolTable(symbol_table_output_file);
			#endif

            fclose(file);
        }
    }
}

void yyerror(const char*s){
	fprintf(stdout, "%s: Line %d-(%d..%d):\n\t%s\n", yylloc.filename.c_str(), yylloc.first_line, yylloc.first_column, yylloc.last_column, s);
	fprintf(stderr, "%s: Line %d-(%d..%d):\n\t%s\n", yylloc.filename.c_str(), yylloc.first_line, yylloc.first_column, yylloc.last_column, s);
}
