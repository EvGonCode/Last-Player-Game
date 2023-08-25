#pragma once
#include <string>

using namespace std;
//Diamonds(Бубы / Дзвінка)
//Hearts(Черви / Чирва)
//Clubs(Трефы / Жир)
//Spades(Пики / Вино)


static const char* SUIT_DIAMONDS = "diamonds";
static const char* SUIT_HEARTS = "hearts";
static const char* SUIT_CLUBS = "clubs";
static const char* SUIT_SPADES = "spades";
static const char* SUIT_JOKER_BLACK = "joker_black";
static const char* SUIT_JOKER_RED = "joker_red";
static const char** SUITS = new const char* [4]{ SUIT_DIAMONDS, SUIT_HEARTS, SUIT_CLUBS, SUIT_SPADES};
static const int SUITS_AMOUNT = 4;
static const int MIN_CARD_VALUE = 2;
static const int MAX_CARD_VALUE = 14;


static const char* SUIT_DIAMONDS_CHAR = u8"♦";
static const char* SUIT_HEARTS_CHAR = u8"♥";
static const char* SUIT_CLUBS_CHAR = u8"♣";
static const char* SUIT_SPADES_CHAR = u8"♠";

static const char** VALUE_NAMES = new const char* [14]{ "2", "3", "4", "5", "6", "7", "8", "9", "10", "Валет", "Дама", "Король", "Туз", "Джокер"};
static const char** SUITS_NAMES = new const char* [4]{ "Дзвінка", "Чирва", "Жир", "Вино" }; //{ "♢", "♡", "♧", "♤" }
static const char* SUIT_JOKER_BLACK_NAME = "Чор-й Джокер";
static const char* SUIT_JOKER_RED_NAME = "Чер-й Джокер";


class Card
{
private:
	string suit;
	int mass;
public:
	Card(string suit, int mass);
	string getSuit();
	int getMass();
	bool Compare(Card card1, Card card2);
	bool operator==(Card card);
	string toString();
	int getScoreMass();
};
