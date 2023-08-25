#include "Player.h"


string Player::getName() {
	return name;
}
vector<Card> Player::getAvailableCards() {
	return availableCards;
}
Player::Player(string name) {
	this->name = name;
	this->gameScore = 0;
	this->availableCards = vector<Card>();
	isMustSkipStep = false;
	
}
bool Player::getIsMustSkipStep() {
	return this->isMustSkipStep;
}
void Player::setIsMustSkipStep(bool isMustSkipStep) {
	this->isMustSkipStep = isMustSkipStep;
}
vector<Card> Player::sortCards(vector<Card> AC_notSorted) {
	vector<Card> sorted;
	for (int i = 0; i < 2; i++) {
		for (int k = MIN_CARD_VALUE; k <= MAX_CARD_VALUE; k++) {
			for (int j = 0; j < AC_notSorted.size(); j++) {
				Card card(SUITS[i], k);
				if (card.Compare(card, AC_notSorted[j])) {
					sorted.push_back(card);
				}
			}
		}
	}

	for (int i = 0; i < AC_notSorted.size(); i++) {
		Card card(SUIT_JOKER_RED, 15);
		if (card.Compare(card, AC_notSorted[i])) {
			sorted.push_back(card);
		}
	}


	for (int i = 2; i < 4; i++) {
		for (int k = MIN_CARD_VALUE; k <= MAX_CARD_VALUE; k++) {
			for (int j = 0; j < AC_notSorted.size(); j++) {
				Card card(SUITS[i], k);
				if (card.Compare(card, AC_notSorted[j])) {
					sorted.push_back(card);
				}
			}
		}
	}

	for (int i = 0; i < AC_notSorted.size(); i++) {
		Card card(SUIT_JOKER_BLACK, 15);
		if (card.Compare(card, AC_notSorted[i])) {
			sorted.push_back(card);
		}
	}
	return sorted;
}
void Player::addCard(Card card) {
	vector<Card> AC_notSorted;
	AC_notSorted.push_back(card);
	for (int i = 0; i < availableCards.size(); i++) {
		AC_notSorted.push_back(availableCards[i]);
	}
	availableCards.clear();
	availableCards = sortCards(AC_notSorted);
}
Card Player::getCard(int ID) {
	Card card = availableCards[ID];
	vector<Card> newVector = vector<Card>();

	for (int i = 0; i < availableCards.size(); i++) {
		if (i != ID) {
			newVector.push_back(availableCards[i]);
		}
	}
	this->availableCards = newVector;
	return card;
}
int Player::countScore() {
	int score = 0;
	for (int i = 0; i < availableCards.size(); i++) {
		switch (availableCards[i].getMass()) {
		case 8:
			score += 25;
			break;

		case 10:
			score += 10;
			break;

		case 11:
			score += 10;
			break;

		case 12:
			score += 10;
			break;

		case 13:
			score += 10;
			break;

		case 14:
			score += 15;
			break;

		case 15:
			score += 40;
			break;
		}
	}
	gameScore = score;
	return score;
}
void Player::clearCards() {
	this->availableCards.clear();
}
int Player::countScore(Player* player) {
	int score = 0;
	for (int i = 0; i < availableCards.size(); i++) {
		score += availableCards[i].getScoreMass();
	}
	if (score == 0) {
		score = availableCards.size();
	}
}
