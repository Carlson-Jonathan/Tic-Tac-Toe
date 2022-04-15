/* (C) Jonathan Carlson 2022
   Random Tic Tac Toe game I made in about 2 hours on a 
   Saturday morning as I was teaching my son C++. Several
   of my co-workers had to create games like this for
   their university classes so I figured I would give it
   a shot. I could probably dress it up with SFML, but
   a simple game deserves a simple gui. */ 

#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Board {

public:

	vector<vector<char>> exampleBoard =
	{{'1', ' ', '|', ' ', '2', ' ', '|', ' ', '3'},
	 {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
	 {'4', ' ', '|', ' ', '5', ' ', '|', ' ', '6'},
	 {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
	 {'7', ' ', '|', ' ', '8', ' ', '|', ' ', '9'}};

	vector<vector<char>> board =
	{{' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' '},
	 {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
	 {' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' '},
	 {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
	 {' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' '}};

	map<int, pair<int, int>> position = {
		{1, {0, 0}}, {2, {0, 4}}, {3, {0, 8}},
		{4, {2, 0}}, {5, {2, 4}}, {6, {2, 8}},
		{7, {4, 0}}, {8, {4, 4}}, {9, {4, 8}}
	};

	bool isValidMove(string move) {
		if(move.length() != 1)
			return false;

		if(!isdigit(move[0]))
			return false;

		int imove = move[0] - 48;

		pair pos = this->position[imove];

		if(board[pos.first][pos.second] != ' ')
			return false;

		return imove <= 9 && imove > 0;
	}

	void placeMove(char mark, int position) {
		pair pos = this->position[position];
		board[pos.first][pos.second] = mark;
	}

	void printBoard() {
		cout << "\n\t  Moves\n";
		for(int i = 0; i < board.size(); i++) {

			cout << "\t";

			for(int j = 0; j < board[0].size(); j++)
				cout << exampleBoard[i][j];

			cout << "\t";	

			for(int j = 0; j < board[0].size(); j++)
				cout << board[i][j];

			cout << "\n";
		}
	}

	void clearScreen() {
		int x = 50;
		while(x--)
			cout << endl;
	}

	void refresh() {
		clearScreen();
		cout << "==========================================\n";
		cout << "               TIC TAC TOE" << endl;
		cout << "==========================================\n";
		printBoard();
		cout << "\n==========================================\n";
	}

	bool isVictorious() {
		vector<char> row1  = {board[0][0], board[0][4], board[0][8]};
		vector<char> row2  = {board[2][0], board[2][4], board[2][8]};
		vector<char> row3  = {board[4][0], board[4][4], board[4][8]};
		vector<char> col1  = {board[0][0], board[2][0], board[4][0]};
		vector<char> col2  = {board[0][4], board[2][4], board[4][4]};
		vector<char> col3  = {board[0][8], board[2][8], board[4][8]};
		vector<char> diag1 = {board[0][0], board[2][4], board[4][8]};
		vector<char> diag2 = {board[4][0], board[2][4], board[0][8]};

		vector<char> xWins = {'X', 'X', 'X'};
		vector<char> oWins = {'O', 'O', 'O'};

		vector<vector<char>> all = {row1, row2, row3, col1, col2, col3, diag1, diag2};

		for(auto i : all) {
			if(i == xWins || i == oWins)
				return true;
		}

		return false;
	}

};

int main() {

	Board board;
	char playerMarks[] = "XO";
	string playerMove, victor;
	int currentPlayer;
	int turnCount = 0;

	board.refresh();
	while(!board.isVictorious()) {

		currentPlayer = turnCount % 2;

		do {
			cout << "Player " << playerMarks[currentPlayer] << " Move: ";		
			getline(cin, playerMove);
			board.refresh();
		} while(!board.isValidMove(playerMove));

		board.placeMove(playerMarks[currentPlayer], playerMove[0] - 48);

		board.refresh();

		victor = "             Player # Wins!\n==========================================\n";
		victor[20] = playerMarks[currentPlayer];

		if(board.isVictorious())
			break;

		turnCount++;
		if(turnCount >= 9) {
			victor = "==================================\n\t\tDraw!\n==================================";
			break;
		}
	}

	cout << victor << endl;

	return 0;
}
#endif