#include <iostream>
#include "Cards.h"
#include <time.h>
#include "Board.h"

using namespace std;


int main() {
	const int numberOfPlayers = 4;
	playerStruc player[numberOfPlayers];
	initializePlayers(player, numberOfPlayers);

	srand(time(0));
	deckState deck;
	initializeDeck(&deck);

	int i = 0;
	do {
		cout << drawCard(&deck) << " \n";
		i++;
	} while (i < deck.deckSize);


	for (int i = 0; i < numberOfPlayers; i++) {
		cout << player[i].playerID << "  " << player[i].SafezoneStart << "  " << player[i].Spawn << "  " << player[i].Token << "  \n";
	}
	system("pause");

	board Testboard;
	for (int i = 0; i < Testboard.boardsize; i++) {	
		Testboard.board[i] = 0;
	}
	Testboard.board[16] = 1000;
	Testboard.board[17] = 17;
	Testboard.board[18] = 18;
	Testboard.board[19] = 19;
	Testboard.board[20] = 20;
	Testboard.board[23] = 23;
	Testboard.board[24] = 1000; // or 1000 if you want to have it move
	Testboard.board[25] = 25;
	Testboard.board[26] = 26;
	printBoard(Testboard);
	system("pause");
	checkForSlides(&Testboard);
	printBoard(Testboard);
	system("pause");

}