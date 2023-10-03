%{
	#include"y.tab.h" 
	#include <iostream>
	#include <fstream>
	#include <string>
	using namespace std;

	string out_file = "out.py";
	std::ofstream out(out_file);

	// Helps convert the curly brace after if, while, etc to a python colon when needed.
	bool convert_curly_brace_to_colon = false;
	bool at_line_beginning = true;
	int cur_scope_depth = 0;

	bool in_print = false;

	// Below macro is called each time before a pattern is matched. 
	// Hence if in_program boolean is not set, we just ignore the pattern.
	// Or else we indent the code to match the current scope depth.
	bool in_program = false;
	#define YY_USER_ACTION \
		if(!in_program && string(yytext) != "hi bhai") \
			return -1; \
		else if(at_line_beginning){ \
			for(int i = 0; i < cur_scope_depth; i++) \
				out << "  "; \
			at_line_beginning = false; \
		}
%}

%%
^"hi bhai"					in_program = true; out << "# Program starts here" << endl;
"bye bhai"					in_program = false; out << "# Program ends here" << endl;
"bhai ye hai"				;	
"nalla"						out << "None ";
"sahi"						out << "True ";
"galat"						out << "False ";
"bol bhai"					out << "print("; in_print = true;					
"agar bhai"					out << "if "; convert_curly_brace_to_colon = true;
"nahi to bhai"				out << "elif "; convert_curly_brace_to_colon = true;
"warna bhai"				out << "else "; convert_curly_brace_to_colon = true;
"jab tak bhai"				out << "while "; convert_curly_brace_to_colon = true;
"agla dekh bhai"			out << "continue";
"bas kar bhai"				out << "break";

";"							if(in_print){out << ")"; in_print = false;} out << "\n"; at_line_beginning = true;
"{"							if(convert_curly_brace_to_colon) out << ": \n"; convert_curly_brace_to_colon = false; cur_scope_depth++; at_line_beginning = true;
"}"							cur_scope_depth--; out << "\n"; at_line_beginning = true;
[\"\'].+[\"\']				out << string(yytext); /*Assumption that the string does not contain escaped ' or ". */
[ \t]+						;
[\n]+						at_line_beginning = true;
[^ \t\n]					out << string(yytext);
<<EOF>>						return 0;
%%

int yywrap(void){
	return 1;
}

int main(int argc, char *argv[]){
	if(argc > 1)
		yyin = fopen(argv[1], "r");
	else
		yyin = stdin;

	while(yylex())
		;
	
	return 0;
}