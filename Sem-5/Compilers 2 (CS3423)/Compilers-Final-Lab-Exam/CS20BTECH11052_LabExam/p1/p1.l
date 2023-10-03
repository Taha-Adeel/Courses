%{
	#include"y.tab.h" 
%}

%%
^"///".*"\n"			{yyval.str = yytext; return DOCUMENTATION_COMMENT; }
"//".*"\n"				; /*C comment. Ignore*/

^"#include"[ ]*[<\"].*[>\"].*\n	{yyval.str = yytext; return INCLUDE_DIRECTIVE; }

"class"					return CLASS;
"int"					return INT;
"void"					return VOID;

[_a-zA-Z][_a-zA-Z0-9]*	{yylval.str = yytext; return IDENTIFIER;}
[0-9]+					return INTEGER_LITERAL;
"public"				return PUBLIC;
"protected"				return PROTECTED;
"private"				return PRIVATE;

.						return yytext[0];


%%

int yywrap(void){
	return 1;
}

