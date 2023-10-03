%define parse.error verbose
%{
	extern int yylex();
	void yyerror(const char*s);

	#include <iostream>
	#include <vector>
	using namespace std;

	int N;
	vector<vector<char>> board;
	char player, cur_move;
%}

%union {
	int num;
	char ch;
}
%token <num> NUM
%token <ch> MOVE PLAYER

%start S
%%
    S   : NUM { N = $1; }
		  board
		  PLAYER MOVE { player = $4; cur_move = $5; }
        ;

	board: MOVE { board.push_back(vector<char>()); board.back().push_back($1); }
		| board MOVE { if(board.back().size() == N) board.push_back(vector<char>()); board.back().push_back($2);}
		;
%%

void yyerror(const  char *s){
	exit(1);
}

pair<int, int> checkHorizontalWin(){ 
	for(int i = 0; i < N; i++){
		int move_count = 0, free_count = 0;
		for(int j = 0; j < N; j++){
			if(board[i][j] == cur_move) move_count++;
			else if(board[i][j] == '#') free_count++;
		}
		if(move_count == N-1 && free_count == 1) 
			for(int j = 0; j < N; j++)
				if(board[i][j] == '#') return {i, j};
	}
	return {-1, -1};
}

pair<int, int> checkVerticalWin(){
	for(int i = 0; i < N; i++){
		int move_count = 0, free_count = 0;
		for(int j = 0; j < N; j++){
			if(board[j][i] == cur_move) move_count++;
			else if(board[j][i] == '#') free_count++;
		}
		if(move_count == N-1 && free_count == 1)
			for(int j = 0; j < N; j++)
				if(board[j][i] == '#') return {j, i};
	}
	return {-1, -1};
}

pair<int, int> checkDiagonalWin(){
	int move_count = 0, free_count = 0;
	for(int i = 0; i < N; i++){
		if(board[i][i] == cur_move) move_count++;
		else if(board[i][i] == '#') free_count++;
	}
	if(move_count == N-1 && free_count == 1){
		for(int i = 0; i < N; i++)
			if(board[i][i] == '#') return {i, i};
	}
	move_count = 0, free_count = 0;
	for(int i = 0; i < N; i++){
		if(board[i][N-i-1] == cur_move) move_count++;
		else if(board[i][N-i-1] == '#') free_count++;
	}
	if(move_count == N-1 && free_count == 1) {
		for(int i = 0; i < N; i++)
			if(board[i][N-i-1] == '#') return {i, N-i-1};
	}
	return {-1, -1};
}

int main(){
	yyparse();

	// We can read directly from stdin, but we use the scanner to get our input
	/* cin >> N;
	board = vector(N, vector(N, '#'));
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			cin >> board[i][j];
	cin >> player >> move; */

	for(auto& v: board){
		for(auto& c: v)
			cout << c;
		cout << endl;
	}

	pair<int, int> win = checkHorizontalWin();
	if(win.first != -1) cout << win.first+1 << " " << win.second+1 << endl;
	else{
		win = checkVerticalWin();
		if(win.first != -1) cout << win.first+1 << " " << win.second+1 << endl;
		else{
			win = checkDiagonalWin();
			if(win.first != -1) cout << win.first+1 << " " << win.second+1 << endl;
			else cout << "Draw" << endl;
		}
	}
	
	return 0;
}
