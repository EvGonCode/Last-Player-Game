#pragma once
#include "Card.h"
#include <string>
#include <vector>

using namespace std;


class Player
{
private:
	string name;
	vector<Card> availableCards;
	int gameScore;
	bool isMustSkipStep;
public:

	string getName();
	vector<Card> getAvailableCards();
	bool getIsMustSkipStep();
	void setIsMustSkipStep(bool isMustSkipStep);

	Player(string name);
	void addCard(Card card);
	Card getCard(int ID);
	void clearCards();
	int countScore();
	vector<Card> sortCards(vector<Card> AC_notSorted);
	int countScore(Player* player);
};

