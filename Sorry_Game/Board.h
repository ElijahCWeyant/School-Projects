#pragma once
#include <cmath>
#include <iostream>
using namespace std;


struct playerStruc {												// Players exist now :)
	int playerID = 0;
	int SafezoneStart = ((playerID) * 15) +2 ;
	int Spawn = ((playerID) * 15) + 4;
	double Token = pow(10, playerID);
};


struct board {														//its a thing!
	const int boardsize = 60;
	int board[60];													//needs to get intaialized somehow thats not me adding 60 0's
	int side[4] = {1, 10, 100, 1000};								//used in checking slides
	int shortslide[4] = { 1, 16, 31, 46 };							//used in manipulating slides
	int shortStop[4] = { 4, 19, 34, 49 };							//used in manipulating slides
	int longslide[4] = { 9, 24, 39, 54 };							//used in manipulating slides
	int longStop[4] = { 13, 28, 43, 58 };							//used in manipulating slides
};

void initializePlayers(playerStruc player[], int numberOfPlayers)	// makes a number of players specified by the input
{
	for (int i = 0; i < numberOfPlayers; i++) {
		player[i] = { i, ((i) * 15) + 2,((i) * 15) + 4,pow(10,i)};
	}
};



void checkForSlides(board* board) { //Tested and functional! YAY!!!!
	for (int i = 0; i < 4; i++)
	{
		int a = board->side[i];
		int x = board->board[board->shortslide[i]];
		if (x != a && board->board[board->shortslide[i]] != 0)
		{
			for (int k = 0; k < 3; k++) {
				board->board[board->shortslide[i]+k] = 0;
			}
			board->board[board->shortStop[i]] = x;
		}

		int b = board->side[i];
		int y = board->board[board->longslide[i]];
		if ( y != b && board->board[board->longslide[i]] != 0)
		{
			for (int k = 0; k < 4; k++) {
				board->board[board->longslide[i]+k] = 0;
			}
			board->board[board->longStop[i]] = y;
		};
	}

};


void printBoard(board print) {	// simplistic for testing boardstates only
	cout << "Possition     Value\n";
	for (int i = 0; i < print.boardsize; i++) {
		cout << i << "      " << print.board[i] << endl;
	}

};