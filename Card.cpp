#include "Card.h"



Card::Card(string suit, int mass) {
	this->suit = suit;
	this->mass = mass;
}
string Card::getSuit() {
	return this->suit;
}
int Card::getMass() {
	return this->mass;
}
bool Card::Compare(Card card1, Card card2) {
	if (card1.getSuit() == card2.getSuit() and card1.getMass() == card2.getMass()) {
		return true;
	}
	return false;
}
bool Card::operator==(Card card) {
	if (this->getSuit() != card.getSuit()) {
		return false;
	}
	if (this->getMass() != card.getMass()) {
		return false;
	}
	return true;
}
string Card::toString() {
	int suitNameID = 0;
	int valueNameID = this->getMass() - 2;
	if (this->getMass() == 15) {
		if (this->getSuit() == SUIT_JOKER_RED) {
			return SUIT_JOKER_RED_NAME;
		}
		else {
			return SUIT_JOKER_BLACK_NAME;
		}
	}
	for (int i = 0; i < SUITS_AMOUNT; i++) {
		if (this->getSuit() == SUITS[i]) {
			suitNameID = i;
			break;
		}
	}
	string strCard = SUITS_NAMES[suitNameID];
	strCard += " ";
	strCard += VALUE_NAMES[valueNameID];

	return strCard;
}
int Card::getScoreMass() {
	switch (mass) {
	case 8:
		return 25;
		break;

	case 10:
		return 10;
		break;

	case 11:
		return 10;
		break;

	case 12:
		return 10;
		break;

	case 13:
		return 10;
		break;

	case 14:
		return 15;
		break;

	case 15:
		return 40;
		break;

	default:
		return 0;
		break;
	}
}
