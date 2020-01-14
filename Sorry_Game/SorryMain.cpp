#include <iostream>
#include "Cards.h"

using namespace std;

int main() {
	deckState deck;
	srand(time(0));
	intializeDeck(&deck);
	int i = 0;
	do{
		cout << drawCard(&deck) << " \n";
		i++;
	} while (i < deck.deckSize);

	system("pause");
}