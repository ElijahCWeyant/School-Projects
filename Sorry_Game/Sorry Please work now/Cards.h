#include<iostream>
#include<stack>
#include<stdlib.h> // for random numbers
#include<stdio.h> // for quick sort#pragma once

using namespace std;

struct card {
	int value;
	int random;
};

struct deckState {
	const int deckSize = 45;
	stack<card> drawDeck;
	card discard[45];																			// can this be made to be "card discard[deckSize];" in any way?
	int discardSize = 0;
};

int cardCount(int);																				// How many cards are in the game
void intializeDeck(deckState deck);																// intializes the deck
void shuffleDeck(deckState deck);																// shuffles the discards into the Deck
int drawCard(deckState deck);																	// Draws a card
double getProbCard(int Pcard, deckState deck);													// gets the probabilty of drawing a card

void quickSort(card arr[], int low, int high);													// broken right now	
int partition(card arr[], int low, int high);													// part of the quick sort
void swap(card* a, card* b);																	// part of the quick sort



int cardCount(int Pcard) {
	switch (Pcard) {
	case 1: return 5;
	case 2: return 4;
	case 3: return 4;
	case 4: return 4;
	case 5: return 4;
	case 7: return 4;
	case 8: return 4;
	case 10: return 4;
	case 11: return 4;
	case 12: return 4;
	case 13: return 4;
	default:
		system("cls");
		cout << "Error in cardCount, Pcard value = " << Pcard;
		system("Pause");
		return 0;
	}
};

void intializeDeck(deckState deck) {									//this should be called once to set up the intial deck and never again
	int count = 0;

	for (int i = 0; i < cardCount(1); i++) {			//each of the for loops adds a type of card into the deck
		deck.discard[count] = { 1, rand() };					//this one adds the 1's to the deck
		count++;
	}
	for (int i = 0; i < cardCount(2); i++) {
		deck.discard[count] = { 2, rand() };
		count++;
	}
	for (int i = 0; i < cardCount(3); i++) {
		deck.discard[count] = { 3, rand() };
		count++;
	}
	for (int i = 0; i < cardCount(4); i++) {
		deck.discard[count] = { 4, rand() };
		count++;
	}
	for (int i = 0; i < cardCount(5); i++) {
		deck.discard[count] = { 5, rand() };
		count++;
	}
	for (int i = 0; i < cardCount(7); i++) {
		deck.discard[count] = { 7, rand() };
		count++;
	}
	for (int i = 0; i < cardCount(8); i++) {
		deck.discard[count] = { 8, rand() };
		count++;
	}
	for (int i = 0; i < cardCount(10); i++) {
		deck.discard[count] = { 10, rand() };
		count++;
	}
	for (int i = 0; i < cardCount(11); i++) {
		deck.discard[count] = { 11, rand() };
		count++;
	}
	for (int i = 0; i < cardCount(12); i++) {
		deck.discard[count] = { 12, rand() };
		count++;
	}
	for (int i = 0; i < cardCount(13); i++) {
		deck.discard[count] = { 13, rand() };
		count++;
	}

	shuffleDeck(deck);

}

void shuffleDeck(deckState deck) {
	for (int i = 0; i < deck.deckSize; i++) {				//Assign random values to the cards
		deck.discard[i] = { deck.discard[i].value, rand() };
	}

	quickSort(deck.discard, 0, deck.deckSize - 1);				//Sort the cards based on those random Values

	for (int i = 0; i < deck.deckSize; i++) {				//push the cards into the deck stack and empty the discard array
		deck.drawDeck.push(deck.discard[i]);
		deck.discard[i] = { 0, 0 };
	}

	deck.discardSize = 0;
}

int drawCard(deckState deck) {
	card draw = deck.drawDeck.top();								//draw a card
	deck.drawDeck.pop();											//remove card from deck
	deck.discard[deck.discardSize++] = draw;						// add card to discard pile

	if (deck.drawDeck.empty()) {									// if the deck is empty shuffel the discard pile back into deck
		shuffleDeck(deck);
	}

	return draw.value;									// return the drawn card;
} // Draws a card from the deck

double getProbCard(int Pcard, deckState deck) {						// gets the probability of drawing a card from the deck
	int Pcount = 0;
	int remDeck = deck.drawDeck.size();
	for (int i = 0; i < deck.discardSize; i++) {
		if (deck.discard[i].value == Pcard)
			Pcount++;
	}
	return (cardCount(Pcard) - Pcount) / remDeck;
};



// quick sort code from https://www.geeksforgeeks.org/quick-sort/      !!!! I have not switched this from sorting an interger array to an array of cards   !!!!!!!


// A utility function to swap two elements 
void swap(card* a, card* b)
{
	card t = *a;
	*a = *b;
	*b = t;
}

int partition(card arr[], int low, int high)
{
	card pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (arr[j].random <= pivot.random)
		{
			i++;    // increment index of smaller element 
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */

void quickSort(card arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		   at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}


// end quick sort code from  https://www.geeksforgeeks.org/quick-sort/





