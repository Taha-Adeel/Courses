w			(" "|\t|\v|\n)
digit				[0-9]

init 				(i|I)(n|N)(i|I)(t|T)
select 				(s|S)(e|E)(l|L)(e|E)(c|C)(t|T)
delay 				(d|D)(e|E)(l|L)(a|A)(y|Y)
signals 			(\t(0|1)){8}

if 					(i|I)(f|F)
else 				(e|E)(l|L)(s|S)(e|E)
comparision_op		(==|!=|<|>|<=|>=)


%{
#include <stdio.h>
#include <string.h>

FILE* output_file;
int indent_counter = 0;
bool user_input = false;
bool inside_ifelse = false;

void print_statement(const char*);

void print_int_decl();
void print_readint();
void print_select();
void print_signal();
void print_delay();
void print_if();
void print_else();
%}


%%

^#.*\n												{/*comment*/;}
{w}+												{;}

{init}													{print_statement("init();");}
"input:"{w}+"int"										{print_int_decl();}
"input"{w}*"="{w}*"readInt"								{print_statement("input = readInt();");}
{select}": "{digit}+									{print_select();}
{signals}												{print_signal();}
{delay}": "{digit}+										{print_delay();}
{if}{w}+"input"{w}*{comparision_op}{w}*{digit}+":"		{print_if();}
{else}":"													{print_else();}

%%

void indent(){
	for(int i = 0; i < indent_counter; ++i)
		fprintf(output_file, "\t");
}
void print_statement(const char* string){
	indent();
	fprintf(output_file, "%s\n", string);
}
void start_scope(){
	print_statement("{");
	indent_counter++;
}
void end_scope(){
	indent_counter--;
	print_statement("}");
}


void print_int_decl(){
	user_input = true;
	print_statement("int input;");
	print_statement("while(1)");
	start_scope();
}

void print_select(){
	static int while_loop_printed = 0;
	if(user_input == true)
		while_loop_printed = 1;
	if(while_loop_printed == 0){
		print_statement("while(1)");
		start_scope();
		while_loop_printed = 1;
	}

	char num[yyleng - strlen("Select: ")];
	for(int i = 0; i < yyleng - strlen("Select: "); ++i){
		num[i] = yytext[(int)strlen("Select: ") + i];
	}
	indent();
	fprintf(output_file, "select(%d);\n", atoi(num));
}

void print_signal(){
	char signal[8];
	for(int i = 0; i < 8; ++i){
		signal[i] = yytext[2*i + 1];
	}
	indent();
	fprintf(output_file, "write(strtol(%s));\n", signal);

	if(inside_ifelse){
		end_scope();
		inside_ifelse = false;
	}
}

void print_delay(){
	char num[yyleng - strlen("Delay: ")];
	for(int i = 0; i < yyleng - strlen("Delay: "); ++i){
		num[i] = yytext[(int)strlen("Delay: ") + i];
	}
	indent();
	fprintf(output_file, "delay(%d);\n", atoi(num));
}

void print_if(){
	print_statement("if (input==0)");
	start_scope();
	inside_ifelse = true;
}
void print_else(){
	print_statement("else");
	start_scope();
	inside_ifelse = true;
}

int yywrap(void){
	end_scope(); // Ending scope for the while true loop
	end_scope(); // Ending scope for the main function
	fclose(output_file);
	return 1;
}


int main()
{
	output_file = fopen("output.c", "w");
	if(output_file == NULL){
		printf("Failed to open output file.\n");
		return -1;
	}

	print_statement("#include<stdio.h>");
	print_statement("#include<stdlib.h>");
	print_statement("#include<seven_segment.h>");
	print_statement("");
	print_statement("int main()");
	start_scope();

	yylex();

	return 0;
}

