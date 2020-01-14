#include <iostream>
#include "Cards.h"

using namespace std;

int main() {
	deckState deck;
	intializeDeck(deck);

	for (int i = 0; i < deck.deckSize - 1; i++) {
		cout << drawCard(deck) << " \n";
	}
	system("pause");
}