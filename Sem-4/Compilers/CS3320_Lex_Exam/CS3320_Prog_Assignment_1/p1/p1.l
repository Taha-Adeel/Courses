column 			[a-h]
row 			[1-8]
piece			(R|N|B|K|Q)
coords			({column}{row})
promotion		("="{piece})

s_no 			([0-9]+".")
whitespace		(" "|\t|\v|\n)

%{
#include <stdio.h>

char board[8][8] = {
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
};
int turn_counter = 0;

void move();
%}


%%


{s_no}												{turn_counter++;/*assert(turn_counter == s_no);*/}
{whitespace}+										{/*do nothing*/;}
{piece}?{coords}(-|x){coords}{promotion}?			{ move();}


%%

void display_board(){
	printf("\n \t");
	for(char column = 'a'; column <= 'h'; column++)
		printf("%c\t", column);
	printf("\n\n");

	for(int i = 0; i < 8; i++){
		printf("%d\t", i+1);
		for(int j = 0; j < 8; j++){
			printf("%c\t", board[i][j]);
		}
		printf("\n\n");
	}
}


void move(){
	int x1, y1, x2, y2;
	char piece;
	int is_piece;

	if(yytext[0]-'Z' < 0){ // Checks if first character is a capital letter
		piece = yytext[0];
		is_piece = 1;
	}
	else{
		piece = 'P';
		is_piece = 0;
	}

	x1 = yytext[0 + is_piece] - 'a'; // Converting character to integer
	y1 = yytext[1 + is_piece] - '1';
	x2 = yytext[3 + is_piece] - 'a';
	y2 = yytext[4 + is_piece] - '1';

	board[y1][x1] = ' ';
	board[y2][x2] = piece;

	if(piece=='P' && (y2+1 == 1 || y2+1 == 8)){
		board[y2][x2] = yytext[6];
	}
}

int yywrap(void){
	display_board();
	return 1;
}

int main()
{
	yylex();
	
	return 0;
}