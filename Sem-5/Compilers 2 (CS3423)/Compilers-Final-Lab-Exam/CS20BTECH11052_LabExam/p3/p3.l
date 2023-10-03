%{
	#include"y.tab.h" 
%}

%%

[0-9]+	{yylval.num = atoi(yytext); return NUM;}
[XO#] 	{yylval.ch = yytext[0]; return MOVE;}
[AB]	{yylval.ch = yytext[0]; return PLAYER;}
[ \t\n]	;
%%

int yywrap(void){
	return 1;
}

