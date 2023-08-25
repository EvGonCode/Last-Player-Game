#pragma once
#include <wx/string.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include "Card.h"
#include "Player.h"
#include "Deck.h"
using namespace std;

class GameProcess
{
private:
	int playersAmount;
	int startCardsAmount;
	int firstPlayerToStep;
	Deck* stockCards;
	vector<Card> playedCards;
	vector<Player*> playersInGame;
	Player* currPlayer;
	string playerName;
	string currentSuet; //Масть яку можна класти
	string looserName;
	bool isItFirstStep;
	bool isClockwise;
	bool isCardPlayed;
	bool isCardTaken;
	bool isSnowballMode; //Чи діє на теперішній хід правило із пункту про карту 4
	bool isUserLoosed;
	bool isUserWon;
	bool isUnoSaid;
	bool isSomeoneLoosed;
	int looserScore;


	
	bool isCurrStepMustBeSkiped; //Чи повинен теперішній гравець пропустити свій хід
	int cardsMustBeTakenCurrent; //Скільки карт повинен взяти теперішній гравець

	
	bool isNextStepMustBeSkiped; 
	int cardsMustBeTakenNext;

	Player* getPlayerWithMaxPoints();
	void startNewRound();
	Player* getNextPlayer();
	Card getCardToStep(Player* player);
public:
	//Tests
	vector<Card> getAllowedCardsToStep();

	vector<Card> getPlayedCards();
	void reduceMustBeenTakenCards();
	Player* getCurrentPlayer();
	bool getIsClockwise();
	bool getIsUserLoosed();
	bool getIsUserWon();
	bool getIsSnowballMode();
	bool getIsItFirstStep();
	bool getIsCardPlayed();
	Deck* getStockCards();
	int getPlayersAmount();
	bool getIsCurrStepMustBeSkiped();
	string getUserName();
	string getCurrSuet();
	void InitiateNewGame(int playersAmount, int startCardsAmount, string playerName);
	GameProcess(int playersAmount, int startCardsAmount, string playerName);
	GameProcess();
	bool isStepCanBeEnded();
	int getPlayedCardsAmount();
	int getCardsMustBeTakenCurrent();
	void endStep();
	vector<Player*> getPlayersInGame();
	bool isCardCanBePlayed(Card card);
	bool isPlayerHaveAppropriateCard(Player* player);
	// AI (smarter than you)
	void makeMoveForBot();
	void makeStep(int card_ID, string newSuit);
	void sayUno();

	bool getIsSomeoneLoosed();
	int getLooserScore();
	string GetLooserName();
	void resetLooser();
};

