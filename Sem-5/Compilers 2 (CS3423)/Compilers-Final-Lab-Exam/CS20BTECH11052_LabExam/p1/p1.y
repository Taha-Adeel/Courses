%define parse.error verbose
%{
	#include <stdio.h>
	#include <string.h>
	#include <iostream>
	#include <fstream>
	#include <string>
	#include <map>
	#include <vector>
	using namespace std;

	extern int yylex();
	void yyerror(const char*s);

	string dot_output_filename = "output.dot", documentation_filename = "output.md";
	std::ofstream dot_output_file(dot_output_filename), documentation_file(documentation_filename);

	class Class{
	public:
		string name;
		string public_parent, private_parent, protected_parent;
		vector<string> documentation;
		vector<string> public_attributes, private_attributes, protected_attributes;
		vector<string> public_methods, private_methods, protected_methods;
		Class(string name, vector<string> documentation, string public_parent, string private_parent, string protected_parent){
			this->name = name;
			this->documentation = documentation;
			this->public_parent = public_parent;
			this->private_parent = private_parent;
			this->protected_parent = protected_parent;

			if(public_parent != ""){
				Class& parent = symbol_table[public_parent];
				public_attributes.insert(public_attributes.end(), parent.public_attributes.begin(), parent.public_attributes.end());
				public_methods.insert(public_methods.end(), parent.public_methods.begin(), parent.public_methods.end());
				protected_attributes.insert(protected_attributes.end(), parent.protected_attributes.begin(), parent.protected_attributes.end());
				protected_methods.insert(protected_methods.end(), parent.protected_methods.begin(), parent.protected_methods.end());
			}
			if(protected_parent != ""){
				Class& parent = symbol_table[protected_parent];
				protected_attributes.insert(public_attributes.end(), parent.public_attributes.begin(), parent.public_attributes.end());
				protected_methods.insert(public_methods.end(), parent.public_methods.begin(), parent.public_methods.end());
				protected_attributes.insert(protected_attributes.end(), parent.protected_attributes.begin(), parent.protected_attributes.end());
				protected_methods.insert(protected_methods.end(), parent.protected_methods.begin(), parent.protected_methods.end());
			}
			if(private_parent != ""){
				Class& parent = symbol_table[private_parent];
				private_attributes.insert(public_attributes.end(), parent.public_attributes.begin(), parent.public_attributes.end());
				private_methods.insert(public_methods.end(), parent.public_methods.begin(), parent.public_methods.end());
				private_attributes.insert(protected_attributes.end(), parent.protected_attributes.begin(), parent.protected_attributes.end());
				private_methods.insert(protected_methods.end(), parent.protected_methods.begin(), parent.protected_methods.end());
			}
		}
	};

	// Holds all the classes declared so far.
	map<string, Class> symbol_table;
%}

%union{
	string* str;
	vector<string>* vec;
}

%token <str> IDENTIFIER DOCUMENTATION_COMMENT INCLUDE_DIRECTIVE
%token INT VOID PUBLIC PROTECTED PRIVATE CLASS INTEGER_LITERAL

%start S
%%
    S   :
        ;

	class_declaration: CLASS IDENTIFIER '{' class_body '}' {
		Class c($2, *$4, "", "", "");
		symbol_table[$2] = c;
	}

	class_body: class_body class_member | class_member | ;

	class_member: documentation member_type IDENTIFIER ';' {
		Class& c = symbol_table[$3];
		if($2 == "public"){
			c.public_attributes.push_back($3);
		}
		else if($2 == "private"){
			c.private_attributes.push_back($3);
		}
		else if($2 == "protected"){
			c.protected_attributes.push_back($3);
		}
	}

	documentation: DOCUMENTATION_COMMENT {
		$$ = new vector<string>;
		$$->push_back($1);
	}

	member_type: PUBLIC | PRIVATE | PROTECTED {
		$$ = $1;
	}

	function_declaration: member_type IDENTIFIER '(' ')' '{' function_body '}' {
		Class& c = symbol_table[$2];
		if($1 == "public"){
			c.public_methods.push_back($2);
		}
		else if($1 == "private"){
			c.private_methods.push_back($2);
		}
		else if($1 == "protected"){
			c.protected_methods.push_back($2);
		}
	}

	function_body: ;
%%

void yyerror(const  char *s){
	exit(1);
}


int main(){	
	yyparse();
	return 0;
}
