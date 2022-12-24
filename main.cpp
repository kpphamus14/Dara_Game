#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Declare all functions
void displayBoard(char board[5][6]);
void readBoard(string fName, char (&board)[5][6]);
bool configurationCheck(char board[5][6]);
bool rowCheck(char board[5][6]);
bool columnCheck(char board[5][6]);
char winnerCheck(char board[5][6]);
bool move(int row, int col, char direction, char(&board)[5][6]);
bool removePiece(int row, int col, char currentPiece, char(&board)[5][6]);
bool consecutiveCheck(int row, int col, char board[5][6]);

int main()
{
	char board[5][6];
	int row;
	int col;
	char direction;
	char currentPiece;
	char replay;

	//Open board
	readBoard("D://daraBoard.txt", board);

	//Check if the initial board is valid and print the board
	if (configurationCheck(board)) {
		displayBoard(board);
	}

	//Show the current state of the board
	//Ask player to choose the piece and the direction
	while(true) {
		displayBoard(board);

		cout << "Row: "; cin >> row;
		cout << "Col: "; cin >> col;
		cout << "Direction: "; cin >> direction;
		currentPiece = board[row][col];

		//Check if move is valid
		//If 3 pieces consecutively. Then take one opponent's piece
		if (move(row, col, direction, board)) {
			if (consecutiveCheck(row, col, board)) {
				cout << "You can remove an oppent's piece" << endl;
				cout << "Row: "; cin >> row;
				cout << "Col: "; cin >> col;
				removePiece(row, col, currentPiece, board);

				//Check if the game is ended. Print out the winner
				char winner = winnerCheck(board);
				if (winner != NULL) {
					displayBoard(board);
					cout << "Winner is: " << winner << endl;
				//Ask player to play again
				//If enter 'y' open the board again
					cout << "Do you want to play again? (y/n)";
					cin >> replay;
					if (replay = 'y'){
						readBoard("D://daraBoard.txt", board);
					}
					else{
						break;
					}
				}
			}
		}
	}

	return 0;
}

//Read the board from a file
void readBoard(string fName, char (&board)[5][6]) {
	string line;
	int counter = 0;

	ifstream myFile(fName);

	//If the file is open and then read until the end of file
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			for (int i = 0; i < 6; i++) {
				board[counter][i] = line[i];
			}

			counter++;
		}

		myFile.close();
	}
}

//Print the board
void displayBoard(char board[5][6]) {
	cout << "------------------------------------------------" << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}

//Check the configuration of the initial board
bool configurationCheck(char board[5][6]) {
	int xCounter = 0;
	int oCounter = 0;
	
	//Count the number of X and O
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (board[i][j] == 'X') {
				xCounter++;
			}
			else if (board[i][j] == 'O') {
				oCounter++;
			}
		}
	}

	//The number of each X and O is 12. If not, print error message
	if (xCounter != 12 || oCounter != 12) {
		cout << "Invalid dara pieces configuration!!!" << endl;
		cout << "Number of X pieces: " << xCounter << endl;
		cout << "Number of O pieces: " << oCounter << endl;
		return false;
	}

	//Check if 3 or more same consecutive pieces on a row or column
	if (rowCheck(board)) {
		cout << "Invalid dara pieces configuration!!!" << endl;
		cout << "There should be no more than 3 same pieces on a row" << endl;
		return false;
	}

	if (columnCheck(board)) {
		cout << "Invalid dara pieces configuration!!!" << endl;
		cout << "There should be no more than 3 same pieces on a column" << endl;
		return false;
	}

	return true;
}

//This function will check 3 or more same consecutive pieces on a row.
//If the count is 3. Return true
bool rowCheck(char board[5][6]) {
	int xCounter = 0;
	int oCounter = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (board[i][j] == 'X') {
				xCounter++;
				oCounter = 0;
			}
			else if (board[i][j] == 'O') {
				oCounter++;
				xCounter = 0;
			}
			else {
				xCounter = 0;
				oCounter = 0;
			}

			if (xCounter == 3) {
				return true;
				break;
			}

			if (oCounter == 3) {
				return true;
				break;
			}
		}

		xCounter = 0;
		oCounter = 0;
	}

	return false;
}

//This function will check 3 or more same consecutive pieces on a column.
//If the count is 3. Return true
bool columnCheck(char board[5][6]) {
	int xCounter = 0;
	int oCounter = 0;

	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 5; i++) {
			if (board[i][j] == 'X') {
				xCounter++;
				oCounter = 0;
			}
			else if (board[i][j] == 'O') {
				oCounter++;
				xCounter = 0;
			}
			else {
				xCounter = 0;
				oCounter = 0;
			}

			if (xCounter == 3) {
				return true;
				break;
			}

			if (oCounter == 3) {
				return true;
				break;
			}
		}

		xCounter = 0;
		oCounter = 0;
	}

	return false;
}

//This function will check the area around a piece after a player make a move
//2 positions left, 2 positions right, 2 positions up, 2 positions down
//If there are 3 same consecutive pieces. Return true
bool consecutiveCheck(int row, int col, char board[5][6]) {
	char piece = board[row][col];
	int rowBottom = (row - 2 >= 0) ? (row - 2) : 0;
	int rowCeiling = (row + 2 <= 4) ? (row + 2) : 4;
	int colBottom = (col - 2 >= 0) ? (col - 2) : 0;
	int colCeiling = (col + 2 <= 5) ? (col + 2) : 5;
	int consecutive = 0;

	for (int i = colBottom; i <= colCeiling; i++) {
		if (board[row][i] == piece) {
			consecutive++;

			if (consecutive == 3) {
				return true;
			}
		}
	}

	consecutive = 0;

	for (int i = rowBottom; i <= rowCeiling; i++) {
		if (board[i][col] == piece) {
			consecutive++;

			if (consecutive == 3) {
				return true;
			}
		}
	}
	return false;
}

//This function counts how many X and O are on the board after each player makes a move
char winnerCheck(char board[5][6]) {
	int xCounter = 0;
	int oCounter = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (board[i][j] == 'X') {
				xCounter++;
			}
			else if(board[i][j] == 'O') {
				oCounter++;
			}
		}
	}

	//If oCounter=0 means X win and if xCounter=0 means O win
	if (oCounter == 0) {
		return 'X';
	}

	if (xCounter == 0) {
		return 'O';
	}

	return NULL;
}

//Direction of the move
bool move(int row, int col, char direction, char (&board)[5][6]) {
	char piece = board[row][col];
	int newRow = row;
	int newCol = col;

	if (direction == 'l') {
		if (newCol - 1 >= 0) {
			newCol--;
		}
		else{
		return false;
		}
	}

	if (direction == 'r') {
		if (newCol + 1 <= 5) {
			newCol++;
		}
		else{
		return false;
		}
	}

	if (direction == 'u') {
		if (newRow - 1 >= 0) {
			newRow--;
		}
		else{
		return false;
		}
	}

	if (direction == 'd') {
		if (newRow + 1 <= 4) {
			newRow++;
		}
		else{
		return false;
		}
	}

	//If new position is empty then the player can move
	//The old position will become empty
	if (board[newRow][newCol] == '.') {
		board[newRow][newCol] = piece;
		board[row][col] = '.';
	}
	else{
	return false;
	}

	return true;
}

//Take opponent piece
bool removePiece(int row, int col, char currentPiece, char (&board)[5][6]) {
	//Can't remove your piece or empty position
	if (board[row][col] == currentPiece || board[row][col] == '.') {
		return false;
	}

	board[row][col] = '.';
	return true;
}
