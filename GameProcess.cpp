#include "GameProcess.h"

Player* GameProcess::getPlayerWithMaxPoints() {
	Player* player = new Player("tmpr");
	int max = 0;
	for (int i = 0; i < playersInGame.size(); i++) {
		if (playersInGame[i]->countScore() > max) {
			max = playersInGame[i]->countScore();
		}
	}
	for (int i = 0; i < playersInGame.size(); i++) {
		if (playersInGame[i]->countScore() == max) {
			player = playersInGame[i];
		}
	}
	if (max == 0) {
		for (int i = 0; i < playersInGame.size(); i++) {
			if (playersInGame[i]->getAvailableCards().size() > max) {
				max = playersInGame[i]->getAvailableCards().size();
			}
		}
		for (int i = 0; i < playersInGame.size(); i++) {
			if (playersInGame[i]->getAvailableCards().size() == max) {
				player = playersInGame[i];
			}
		}
		return player;
	}
	else {
		return player;
	}
}
void GameProcess::startNewRound() {
	Player* looser = getPlayerWithMaxPoints();
	looserScore = looser->countScore();
	looserName = looser->getName();
	isSomeoneLoosed = true;
	if (looser->getName() != playerName and playersInGame.size() == 2) {
		isUserWon = true;
		return;
	}
	playersAmount--;
	isItFirstStep = true;
	isClockwise = true;
	isCardPlayed = false;
	isCardTaken = false;
	this->stockCards = new Deck();
	playedCards.clear();

	for (int i = 0; i < playersInGame.size(); i++) {
		if (playersInGame[i]->getName() == looser->getName()) {
			if (playersInGame[i]->getName() == playerName) {
				isUserLoosed = true;
				return;
			}
			playersInGame.erase(playersInGame.begin() + i);
			break;
		}
	}

	if (firstPlayerToStep >= playersInGame.size()) {
		firstPlayerToStep = playersInGame.size() - 1;
	}
	currPlayer = playersInGame[firstPlayerToStep];
	currentSuet = "";
	isSnowballMode = false;

	isCurrStepMustBeSkiped = false;
	cardsMustBeTakenCurrent = 0;

	isNextStepMustBeSkiped = false;
	cardsMustBeTakenNext = 0;

	for (int i = 0; i < playersInGame.size(); i++) {
		playersInGame[i]->clearCards();
		for (int j = 0; j < startCardsAmount; j++) {
			playersInGame[i]->addCard(stockCards->pop_front());
		}
	}
}
Player* GameProcess::getNextPlayer() {
	if (isClockwise) {
		for (int i = 0; i < playersInGame.size(); i++) {
			if (playersInGame[i]->getName() == currPlayer->getName()) {
				if (i + 1 == playersInGame.size()) {
					return playersInGame[0];
				}
				else {
					return playersInGame[i + 1];
				}
			}
		}
	}
	else {
		for (int i = 0; i < playersInGame.size(); i++) {
			if (playersInGame[i]->getName() == currPlayer->getName()) {
				if (i - 1 < 0) {
					return playersInGame[playersInGame.size() - 1];
				}
				else {
					return playersInGame[i - 1];
				}
			}
		}
	}
}
Card GameProcess::getCardToStep(Player* player) {
	vector<Card> playerCards = player->getAvailableCards();
	bool needToCheck = true;
	while (needToCheck) {
		needToCheck = false;
		for (int i = 0; i < playerCards.size(); i++) {
			if (!isCardCanBePlayed(playerCards[i])) {
				playerCards.erase(playerCards.begin() + i);
				needToCheck = true;
				break;
			}
		}
	}

	Card card = playerCards[0];
	for (int i = 0; i < playerCards.size(); i++) {
		if (card.getScoreMass() < playerCards[i].getScoreMass()) {
			card = playerCards[i];
		}
	}
	return card;

}
vector<Card> GameProcess::getAllowedCardsToStep() {
	Deck* deck = new Deck();
	vector<Card> allawedCardsNotSorted;
	for (int i = 0; i < 54; i++) {
		Card card = deck->pop_front();
		if (isCardCanBePlayed(card)) {
			allawedCardsNotSorted.push_back(card);
		}
	}

	return currPlayer->sortCards(allawedCardsNotSorted);
}
vector<Card> GameProcess::getPlayedCards() {
	return this->playedCards;
}
void GameProcess::reduceMustBeenTakenCards() {
	this->cardsMustBeTakenCurrent--;
}
Player* GameProcess::getCurrentPlayer() {
	return this->currPlayer;
}
bool GameProcess::getIsClockwise() {
	return this->isClockwise;
}
bool GameProcess::getIsUserLoosed() {
	return this->isUserLoosed;
}
bool GameProcess::getIsUserWon() {
	return this->isUserWon;
}
bool GameProcess::getIsSnowballMode() {
	return this->isSnowballMode;
}
bool GameProcess::getIsItFirstStep() {
	return this->isItFirstStep;
}
bool GameProcess::getIsCardPlayed() {
	return this->isCardPlayed;
}
Deck* GameProcess::getStockCards() {
	return this->stockCards;
}
int GameProcess::getPlayersAmount() {
	return this->playersAmount;
}
bool GameProcess::getIsCurrStepMustBeSkiped() {
	return this->isCurrStepMustBeSkiped;
}
string GameProcess::getUserName() {
	return playerName;
}
string GameProcess::getCurrSuet() {
	return this->currentSuet;
}
void GameProcess::InitiateNewGame(int playersAmount, int startCardsAmount, string playerName) {
	this->playerName = playerName;
	this->playersAmount = playersAmount;
	this->startCardsAmount = startCardsAmount;
	stockCards = new Deck();
	if (playedCards.size() != 0) {
		playedCards.clear();
	}
	if (playersInGame.size() != 0) {
		playersInGame.clear();
	}
	isClockwise = true;
	isItFirstStep = true;
	isCardPlayed = false;
	isCardTaken = false;
	isSnowballMode = false;
	isCurrStepMustBeSkiped = false;
	cardsMustBeTakenCurrent = false;
	isNextStepMustBeSkiped = false;
	cardsMustBeTakenNext = false;
	isUserLoosed = false;
	isUserWon = false;
	isUnoSaid = false;
	isSomeoneLoosed = false;
	looserScore = 0;
	looserName = "";
	firstPlayerToStep = rand() % ((playersAmount - 1) - 0 + 1) + 0;


	Player* player = new Player(playerName);
	playersInGame.push_back(player);
	wxString stringnumber;
	for (int i = 1; i < playersAmount; i++) {
		stringnumber = wxString::Format(wxT("%d"), (int)(i + 1));
		string str = "P" + stringnumber.ToStdString();
		player = new Player(str);
		playersInGame.push_back(player);
	}

	for (int i = 0; i < playersAmount; i++) {
		for (int j = 0; j < startCardsAmount; j++) {
			playersInGame[i]->addCard(stockCards->pop_front());
		}
	}

	currPlayer = playersInGame[firstPlayerToStep];
}
GameProcess::GameProcess(int playersAmount, int startCardsAmount, string playerName) {
	InitiateNewGame(playersAmount, startCardsAmount, playerName);
}
GameProcess::GameProcess() {}
bool GameProcess::isStepCanBeEnded() {
	if (isCardPlayed) {
		return true;
	}
	else if (cardsMustBeTakenCurrent == 0 and isCardTaken) {
		return true;
	}
	else if (isCurrStepMustBeSkiped and cardsMustBeTakenCurrent == 0) {
		return true;
	}
	return false;
}
int GameProcess::getPlayedCardsAmount() {
	return playedCards.size();
}
int GameProcess::getCardsMustBeTakenCurrent() {
	return cardsMustBeTakenCurrent;
}
void GameProcess::endStep() {
	if (!isUnoSaid and currPlayer->getAvailableCards().size() == 1) {
		isCurrStepMustBeSkiped = true;
		if (stockCards->getSize() >= 1) {
			cardsMustBeTakenCurrent = 1;
		}
	}
	else if (currPlayer->getAvailableCards().size() == 0) {
		startNewRound();
		if (isUserWon or isUserLoosed) {
			return;
		}
	}
	else {
		bool deadEnd = true;
		for (int i = 0; i < playersInGame.size(); i++) {
			if (isPlayerHaveAppropriateCard(playersInGame[i])) {
				deadEnd = false;
				break;
			}
		}
		if (deadEnd and stockCards->getSize() == 0) {
			startNewRound();
			if (isUserWon or isUserLoosed) {
				return;
			}
		}
		currPlayer = getNextPlayer();
		isCardPlayed = false;
		isCardTaken = false;
		isUnoSaid = false;
		isCurrStepMustBeSkiped = isNextStepMustBeSkiped;
		isNextStepMustBeSkiped = false;
		cardsMustBeTakenCurrent = cardsMustBeTakenNext;
		cardsMustBeTakenNext = 0;
		if (currPlayer->getIsMustSkipStep()) {
			isCurrStepMustBeSkiped = true;
			currPlayer->setIsMustSkipStep(false);
		}

		if (currPlayer->getName() == getUserName() and !isCurrStepMustBeSkiped) {
			if (!isPlayerHaveAppropriateCard(currPlayer)) {
				isCurrStepMustBeSkiped = true;
				if (isSnowballMode) {
					isSnowballMode = false;
					if (playedCards[playedCards.size() - 1].getMass() > stockCards->getSize()) {
						for (int i = 0; i < stockCards->getSize(); i++) {
							cardsMustBeTakenCurrent++;
						}
					}
					else {
						for (int i = 0; i < playedCards[playedCards.size() - 1].getMass(); i++) {
							cardsMustBeTakenCurrent++;
						}
					}
				}
				else {
					cardsMustBeTakenCurrent++;
				}
			}
		}
		if (stockCards->getSize() < 1) {
			cardsMustBeTakenCurrent = 0;
		}
	}
}
vector<Player*> GameProcess::getPlayersInGame() {
	return playersInGame;
}
bool GameProcess::isCardCanBePlayed(Card card) {
	if (this->isItFirstStep) {
		return true;
	}
	Card prevCard = playedCards[playedCards.size() - 1];

	if (card.getMass() == 15) {
		if (isSnowballMode and prevCard.getMass() == 14) {
			return false;
		}
		else {
			return true;
		}
	}
	if (!isCardPlayed) {
		if (isSnowballMode and card.getMass() != prevCard.getMass() + 1) {
			return false;
		}
		if (isSnowballMode and card.getMass() == prevCard.getMass() + 1 and card.getMass() == 8) {
			return true;
		}
		if (isSnowballMode and card.getSuit() != currentSuet) {
			return false;
		}
		if (isSnowballMode and prevCard.getMass() == 14) {
			return false;
		}

		if (card.getMass() == 8 and !isCardPlayed) {
			return true;
		}

		if (!isSnowballMode and (prevCard.getMass() == 5 or prevCard.getMass() == 6 or prevCard.getMass() == 7)) {
			if (card.getMass() == 4 and card.getSuit() == currentSuet) {
				return true;
			}
		}

		if (!isSnowballMode and currentSuet != card.getSuit() and card.getMass() != prevCard.getMass()) {
			return false;
		}

		return true;
	}
	else {
		if (isSnowballMode and card.getMass() == prevCard.getMass() + 1 and card.getMass() == 8) {
			return true;
		}
		if (isSnowballMode and card.getSuit() != currentSuet) {
			return false;
		}
		if (isSnowballMode and card.getMass() != prevCard.getMass() + 1) {
			return false;
		}
		if (isSnowballMode and prevCard.getMass() == 14) {
			return false;
		}
		if (!isSnowballMode and (prevCard.getMass() == 5 or prevCard.getMass() == 6 or prevCard.getMass() == 7)) {
			if (card.getMass() == 4 and card.getSuit() == currentSuet) {
				return true;
			}
		}
		if (!isSnowballMode and isCardPlayed and prevCard.getMass() == 3) {
			return true;
		}
		if (!isSnowballMode and card.getMass() != prevCard.getMass()) {
			return false;
		}
		return true;
	}
}
bool GameProcess::isPlayerHaveAppropriateCard(Player* player) {
	vector<Card> cards = player->getAvailableCards();
	for (int i = 0; i < cards.size(); i++) {
		if (isCardCanBePlayed(cards[i])) {
			return true;
		}
	}
	return false;
}
void GameProcess::makeMoveForBot() {
	isUnoSaid = true;
	if (isCurrStepMustBeSkiped) {
		for (int i = 0; i < cardsMustBeTakenCurrent; i++) {
			currPlayer->addCard(stockCards->pop_front());
		}
		endStep();
	}
	else if (!isPlayerHaveAppropriateCard(currPlayer) and !isCardPlayed) {
		if (isSnowballMode) {
			isSnowballMode = false;
			if (playedCards[playedCards.size() - 1].getMass() <= stockCards->getSize()) {
				for (int i = 0; i < playedCards[playedCards.size() - 1].getMass(); i++) {
					currPlayer->addCard(stockCards->pop_front());
				}
			}
			else {
				for (int i = 0; i < stockCards->getSize(); i++) {
					currPlayer->addCard(stockCards->pop_front());
				}
			}
		}
		else {
			if (stockCards->getSize() != 0) {
				currPlayer->addCard(stockCards->pop_front());
			}
		}
		endStep();
	}
	else if (!isPlayerHaveAppropriateCard(currPlayer) and isCardPlayed) {
		endStep();
	}
	else if (isPlayerHaveAppropriateCard(currPlayer)) {
		Card card = getCardToStep(currPlayer);
		int cardID = 0;
		for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
			if (currPlayer->getAvailableCards()[i] == card) {
				cardID = i;
				break;
			}
		}
		if (card.getMass() == 8) {
			if (isSnowballMode) {
				makeStep(cardID, playedCards[playedCards.size() - 1].getSuit());
			}
			else {
				if (!isCardPlayed) {
					if (isItFirstStep) {
						makeStep(cardID, SUITS[0]);
					}
					else {
						makeStep(cardID, playedCards[playedCards.size() - 1].getSuit());
					}
				}
				else if (isCardPlayed) {
					makeStep(cardID, playedCards[playedCards.size() - 1].getSuit());
				}
			}
		}

		else if (card.getMass() == 15) {
			if (isItFirstStep) {
				currPlayer->getCard(cardID);
				Card jokerCard(SUITS[0], 3);
				currPlayer->addCard(jokerCard);
				for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
					if (jokerCard == currPlayer->getAvailableCards()[i]) {
						cardID = i;
						break;
					}
				}
				makeStep(cardID, "");
			}
			else {
				currPlayer->getCard(cardID);
				if (isSnowballMode) {
					Card jokerCard(playedCards[playedCards.size() - 1].getSuit(), playedCards[playedCards.size() - 1].getMass() + 1);
					currPlayer->addCard(jokerCard);
					for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
						if (jokerCard == currPlayer->getAvailableCards()[i]) {
							cardID = i;
							break;
						}
					}
					makeStep(cardID, "");
				}
				else {
					if (!isCardPlayed) {
						Card jokerCard(playedCards[playedCards.size() - 1].getSuit(), 3);
						currPlayer->addCard(jokerCard);
						for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
							if (jokerCard == currPlayer->getAvailableCards()[i]) {
								cardID = i;
								break;
							}
						}
						makeStep(cardID, "");
					}
					else {
						if (playedCards[playedCards.size() - 1].getMass() == 3) {
							Card jokerCard(playedCards[playedCards.size() - 1].getSuit(), 3);
							currPlayer->addCard(jokerCard);
							for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
								if (jokerCard == currPlayer->getAvailableCards()[i]) {
									cardID = i;
									break;
								}
							}
							makeStep(cardID, "");
						}
						else {
							Card jokerCard(playedCards[playedCards.size() - 1].getSuit(), playedCards[playedCards.size() - 1].getMass());
							currPlayer->addCard(jokerCard);
							for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
								if (jokerCard == currPlayer->getAvailableCards()[i]) {
									cardID = i;
									break;
								}
							}
							makeStep(cardID, "");
						}
					}
				}
			}
		}
		else {
			makeStep(cardID, "");
		}
	}
}
void GameProcess::makeStep(int card_ID, string newSuit) {
	if (!isUnoSaid and currPlayer->getAvailableCards().size() == 1) {
		isCurrStepMustBeSkiped = true;
		if (stockCards->getSize() >= 1) {
			cardsMustBeTakenCurrent = 1;
		}
	}
	else {
		Card choosenCard = currPlayer->getCard(card_ID);
		playedCards.push_back(choosenCard);

		if (choosenCard.getMass() == 2) {
			isNextStepMustBeSkiped = true;
			cardsMustBeTakenNext++;
			if (stockCards->getSize() < cardsMustBeTakenNext) {
				cardsMustBeTakenNext = stockCards->getSize();
			}
		}
		else if (choosenCard.getMass() == 4) {
			isSnowballMode = true;
		}
		else if (choosenCard.getMass() == 8) {
			currentSuet = newSuit;
			if (isItFirstStep) {
				isItFirstStep = false;
			}
			if (!isCardPlayed) {
				isCardPlayed = true;
			}
			return;
		}
		else if (choosenCard.getMass() == 11) {
			if (isClockwise) {
				getNextPlayer()->setIsMustSkipStep(true);
			}
			else {
				isClockwise = true;
				getNextPlayer()->setIsMustSkipStep(true);
				isClockwise = false;
			}
		}
		else if (choosenCard.getMass() == 14) {
			if (isClockwise) {
				isClockwise = false;
			}
			else {
				isClockwise = true;
			}
		}
		if (isItFirstStep) {
			isItFirstStep = false;
		}
		if (!isCardPlayed) {
			isCardPlayed = true;
		}
		currentSuet = choosenCard.getSuit();
	}
}
void GameProcess::sayUno() {
	this->isUnoSaid = true;
}

bool GameProcess::getIsSomeoneLoosed() {
	return isSomeoneLoosed;
}
int GameProcess::getLooserScore() {
	return looserScore;
}
void GameProcess::resetLooser() {
	isSomeoneLoosed = false;
	looserScore = 0;
	looserName = "";
}
string GameProcess::GetLooserName() {
	return looserName;
}