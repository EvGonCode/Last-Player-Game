#include "Deck.h"

void Deck::generateAndSort() {
	srand(time(NULL));

	vector<Card> deck_notSorted;

	for (int i = 0; i < SUITS_AMOUNT; i++) {
		for (int j = MIN_CARD_VALUE; j <= MAX_CARD_VALUE; j++) {
			Card card(SUITS[i], j);
			deck_notSorted.push_back(card);
		}
	}
	Card cardjb(SUIT_JOKER_BLACK, 15);
	deck_notSorted.push_back(cardjb);
	Card cardjr(SUIT_JOKER_RED, 15);
	deck_notSorted.push_back(cardjr);


	for (int i = 0; i < DECK_SIZE; i++) {
		int range = (DECK_SIZE - 1) - i - 0 + 1;
		int randIndex = rand() % range + 0;

		Card card = deck_notSorted[randIndex];
		remove(deck_notSorted.begin(), deck_notSorted.end(), card);
		deck.push_back(card);
	}

}
Deck::Deck() {
	generateAndSort();
}
Deck::~Deck() {
}
vector<Card> Deck::getDeckCards() {
	return deck;
}
int Deck::getSize() {
	return deck.size();
}
Card Deck::pop_front() {
	if (deck.size() > 0) {
		Card card = deck[0];
		deck.erase(deck.begin());
		return card;
	}
	throw new exception;
}
