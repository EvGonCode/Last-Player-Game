#pragma once
#include "Card.h"
#include <vector>
#include <random>
#include <ctime>
using namespace std;

const int DECK_SIZE = 54;

class Deck
{
private:
	vector<Card> deck;
	void generateAndSort();

public:
	Deck(); 
	~Deck();
	vector<Card> getDeckCards();
	int getSize();
	Card pop_front();

};

