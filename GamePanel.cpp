#include "GamePanel.h"
#include "MenuPanel.h"
#include "cMain.h"
#include <string>
#include <format>
using namespace std;

const int ID_B_EXITTOMENU = 100;
const int ID_B_MUTEMUSIC = 101;
const int ID_B_GUIDE = 102;
const int ID_B_PLAYCARD = 103;
const int ID_B_TAKECARD = 104;
const int ID_B_ENDSTEP = 105;
const int ID_B_UNO = 106;
const int ID_B_SELECTDIAMONDS = 106;
const int ID_B_SELECTHEARTS = 107;
const int ID_B_SELECTCLUBS = 108;
const int ID_B_SELECTSPADES = 109;
const int ID_P_CARDSPANEL = 302;
const int ID_P_SELECTNEWSUITPANEL = 303;
const int ID_P_SELECTNEWMASSPANEL = 304;

GamePanel::GamePanel(wxPanel* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(800, 600)) {
	wxInitAllImageHandlers();
	parrentPanel = parent; 
	//menu
	isMuted = false;

	btnMuteMusic = new wxButton(this, ID_B_MUTEMUSIC, wxT(" "), wxPoint(80, 520), wxSize(40, 40));
	btnExitToMenu = new wxButton(this, ID_B_EXITTOMENU, wxT("Exit"), wxPoint(0, 540));
	btnOnGuide = new wxButton(this, ID_B_GUIDE, wxT("Guide"), wxPoint(720, 540), wxSize(50, 20));
	btnOnTakeCard = new wxButton(this, ID_B_TAKECARD, wxT("Take card"), wxPoint(300, 305), wxSize(92, 20));
	btnOnEndStep = new wxButton(this, ID_B_ENDSTEP, wxT("End step"), wxPoint(682, 400), wxSize(100, 100));
	btnOnSayUno = new wxButton(this, ID_B_UNO, wxT("UNO!"), wxPoint(30, 400), wxSize(100, 100));

	btnMuteMusic->SetBitmap(wxICON(icon_unmute));
	sound->Play(music_DOOM, wxSOUND_ASYNC | wxSOUND_LOOP);

	btnMuteMusic->Bind(wxEVT_BUTTON, &GamePanel::OnMuteMusic, this);
	btnExitToMenu->Bind(wxEVT_BUTTON, &GamePanel::OnExitToMenu, this);
	btnOnGuide->Bind(wxEVT_BUTTON, &GamePanel::OnGuide, this);
	btnOnTakeCard->Bind(wxEVT_BUTTON, &GamePanel::OnTakeCard, this);
	btnOnEndStep->Bind(wxEVT_BUTTON, &GamePanel::OnEndStep, this);
	btnOnSayUno->Bind(wxEVT_BUTTON, &GamePanel::OnSayUno, this);



	//Game table
	PlayedCardsBtm = new wxStaticBitmap(this, wxID_ANY, wxBitmap(IM_NA_P, wxBITMAP_TYPE_PNG), wxPoint(395, 150), wxSize(92, 134));
	StockCardsBtm = new wxStaticBitmap(this, wxID_ANY, wxBitmap(IM_BACK_CARD_P, wxBITMAP_TYPE_PNG), wxPoint(300, 150), wxSize(92, 134));
	currentPlayerNameTxt = new wxTextCtrl(this, wxID_ANY, wxT("Your turn!"), wxPoint(150, 250), wxSize(100, 20), wxTE_READONLY);
	currentPlayerNameTxt->Hide();
	GameDirectionBtm = new wxStaticBitmap(this, wxID_ANY, wxBitmap(IM_CLOCKWISE_P, wxBITMAP_TYPE_PNG), wxPoint(350, 350), wxSize(40, 40));
	cardsmustBeTakenAmountTxt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(300, 285), wxSize(92, 20), wxTE_READONLY);
	CurrentSuitBtm = new wxStaticBitmap(this, wxID_ANY, wxBitmap(IM_SUIT_CLUBS_P, wxBITMAP_TYPE_PNG), wxPoint(500, 210), wxSize(40, 40));
	CurrentSuitBtm->Hide();
	currStepMustBeSkippedTxt = new wxTextCtrl(this, wxID_ANY, wxT("SKIP"), wxPoint(500, 170), wxSize(60, 40), wxTE_READONLY);
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false);
	currStepMustBeSkippedTxt->SetFont(font);
	currStepMustBeSkippedTxt->Hide();

	SnowballModeBtm = new wxStaticBitmap(this, wxID_ANY, wxBitmap(IM_SNOWBOLLMODE_P, wxBITMAP_TYPE_PNG), wxPoint(500, 250), wxSize(40, 40));
	SnowballModeBtm->Hide();



	//User cards panel
	cardsPanel = new wxPanel(this, ID_P_CARDSPANEL, wxPoint(130, 400), wxSize(552, 132));
	userSelectedCardTxt = new wxTextCtrl(cardsPanel, wxID_ANY, wxT(""), wxPoint(400, -1), wxSize(100, 20));

	btnOnPlayCard = new wxButton(cardsPanel, ID_B_PLAYCARD, wxT("put"), wxPoint(400, 20), wxSize(100, 20));
	btnOnPlayCard->Bind(wxEVT_BUTTON, &GamePanel::OnPlayCard, this);




	//Select new suit panel
	selectNewSuitPanel = new wxPanel(this, ID_P_SELECTNEWSUITPANEL, wxPoint(160, 400), wxSize(500, 140));

	btnOnSeletcDiamonds = new wxButton(selectNewSuitPanel, ID_B_SELECTDIAMONDS, wxT("Дзвінка"), wxPoint(0, 0), wxSize(125, 140));
	btnOnSeletcHearts = new wxButton(selectNewSuitPanel, ID_B_SELECTHEARTS, wxT("Чирва"), wxPoint(125, 0), wxSize(125, 140));
	btnOnSeletcClubs = new wxButton(selectNewSuitPanel, ID_B_SELECTCLUBS, wxT("Жир"), wxPoint(250, 0), wxSize(125, 140));
	btnOnSeletcSpades = new wxButton(selectNewSuitPanel, ID_B_SELECTSPADES, wxT("Вино"), wxPoint(375, 0), wxSize(125, 140));

	btnOnSeletcDiamonds->Bind(wxEVT_BUTTON, &GamePanel::OnSeletcDiamonds, this);
	btnOnSeletcHearts->Bind(wxEVT_BUTTON, &GamePanel::OnSeletcHearts, this);
	btnOnSeletcClubs->Bind(wxEVT_BUTTON, &GamePanel::OnSeletcClubs, this);
	btnOnSeletcSpades->Bind(wxEVT_BUTTON, &GamePanel::OnSeletcSpades, this);

	hideSelectSuitButtons();

	//Select new mass panel
	selectNewMassPanel = new wxPanel(this, ID_P_SELECTNEWMASSPANEL, wxPoint(160, 400), wxSize(500, 140));
	createSelectMassBtns();
	hideSelectMassButtons();
	selectedMass = 0;

	this->Hide();

}

GamePanel::~GamePanel() {

}



void GamePanel::OnMuteMusic(wxCommandEvent& event) {
	if (isMuted) {
		btnMuteMusic->SetBitmap(wxICON(icon_unmute));
		sound->Play(music_DOOM, wxSOUND_ASYNC | wxSOUND_LOOP);
		isMuted = false;
	}
	else {
		btnMuteMusic->SetBitmap(wxICON(icon_mute));
		sound->Stop();
		isMuted = true;
	}
}
void GamePanel::OnExitToMenu(wxCommandEvent& event) {
	this->Hide();
	MenuPanel* mp = (MenuPanel*)this->parrentPanel->GetChildren()[1];
	mp->Show();

	this->sound->Stop();
	if (!this->isMuted) {
		mp->isMuted = false;
		mp->btnMuteMusic->SetBitmap(wxICON(icon_unmute));
		mp->sound->Play(music_Serious_Sam, wxSOUND_ASYNC | wxSOUND_LOOP);
	}
	else {
		mp->isMuted = true;
		mp->btnMuteMusic->SetBitmap(wxICON(icon_mute));
		mp->sound->Stop();
	}

	this->userSelectedCardTxt->Clear();
	this->selectedMass = 0;
	this->selectedSuit = "";
	hideSelectSuitButtons();
	hideSelectMassButtons();
	CurrentSuitBtm->Hide();
}
void GamePanel::OnGuide(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	if (cmain->isGuideOpen == false) {
		cmain->guideWindow = new GuideWindow(cmain);
		cmain->guideWindow->Show();
		cmain->isGuideOpen = true;
	}
	else {
		cmain->guideWindow->Close();
		cmain->isGuideOpen = false;
	}
}
void GamePanel::OnPlayCard(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;
	vector<Card> userCards = gameprocess->getCurrentPlayer()->getAvailableCards();
	int cardID = wxAtoi(userSelectedCardTxt->GetValue()) - 1;

	if (gameprocess->getCurrentPlayer()->getName() == gameprocess->getUserName()) {
		if (cardID < 0 or cardID >= userCards.size()) {
			userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
		}
		else if (gameprocess->getIsCurrStepMustBeSkiped()) {
			userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
		}
		else if (!cmain->gameProcess->isCardCanBePlayed(userCards[cardID])) {
			userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
		}
		else {
			if (userCards[cardID].getMass() != 8 and userCards[cardID].getMass() != 15) {
				gameprocess->makeStep(cardID, "");
				userSelectedCardTxt->SetBackgroundColour(wxColor(255, 255, 255));
				this->refreshInfo();
			}
			else {
				if (userCards[cardID].getMass() == 8) {
					if (this->selectedSuit == "") {
						showSelectSuitButtons();
					}
					else {
						Card card(selectedSuit, 8);
						selectedSuit = "";
						selectedMass = 0;
						if (gameprocess->isCardCanBePlayed(card)) {
							if (!gameprocess->getIsCardPlayed() and gameprocess->getCurrSuet() != card.getSuit() and gameprocess->getPlayedCards().size() != 0) {
								userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
							}
							else if (gameprocess->getIsSnowballMode() and gameprocess->getCurrSuet() != card.getSuit()) {
								userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
							}
							else {
								gameprocess->makeStep(cardID, card.getSuit());
								userSelectedCardTxt->SetBackgroundColour(wxColor(255, 255, 255));
							}
						}
						else {
							userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
						}
					}
				}
				else if (userCards[cardID].getMass() == 15) {
					if (selectedMass == 0) {
						showSelectMassButtons();
					}
					else if (selectedSuit == "") {
						showSelectSuitButtons();
					}
					else {
						Card card(selectedSuit, selectedMass);
						selectedMass = 0;
						selectedSuit = "";
						if (gameprocess->isCardCanBePlayed(card)) {
							Player* user = gameprocess->getCurrentPlayer();
							if (card.getMass() != 8) {
								user->getCard(cardID);
								user->addCard(card);
								for (int i = 0; i < user->getAvailableCards().size(); i++) {
									if (user->getAvailableCards()[i] == card) {
										cardID = i;
										break;
									}
								}
								gameprocess->makeStep(cardID, "");
								userSelectedCardTxt->SetBackgroundColour(wxColor(255, 255, 255));
							}
							else {
								if (!gameprocess->getIsCardPlayed() and gameprocess->getCurrSuet() != card.getSuit() and gameprocess->getPlayedCards().size() != 0) {
									userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
								}
								else if (gameprocess->getIsSnowballMode() and gameprocess->getCurrSuet() != card.getSuit()) {
									userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
								}
								else {
									user->getCard(cardID);
									user->addCard(card);
									for (int i = 0; i < user->getAvailableCards().size(); i++) {
										if (user->getAvailableCards()[i] == card) {
											cardID = i;
											break;
										}
									}
									gameprocess->makeStep(cardID, card.getSuit());
									userSelectedCardTxt->SetBackgroundColour(wxColor(255, 255, 255));
								}
							}
						}
						else {
							userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
						}
					}
				}
				this->refreshInfo();
			}
		}
	}
}
void GamePanel::OnTakeCard(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	if (gameprocess->getCardsMustBeTakenCurrent() > 0 and gameprocess->getCurrentPlayer()->getName() == gameprocess->getUserName()) {
		gameprocess->getCurrentPlayer()->addCard(gameprocess->getStockCards()->pop_front());
		gameprocess->reduceMustBeenTakenCards();
		refreshInfo();
	}
}
void GamePanel::hideUserPanel() {
	this->cardsPanel->Hide();
	this->userSelectedCardTxt->Hide();
}
void GamePanel::showUserPanel() {
	this->cardsPanel->Show();
	this->userSelectedCardTxt->Show();
}
void GamePanel::OnButtonCard(wxCommandEvent& event) {
	int id = event.GetId() - 11000;
	userSelectedCardTxt->Clear();
	wxString text = wxString::Format(wxT("%d) "), (id));
	userSelectedCardTxt->WriteText(text);
	this->OnPlayCard(event);
}

//Select new suit
void GamePanel::OnSeletcDiamonds(wxCommandEvent& event) {
	this->selectedSuit = SUITS[0];
	hideSelectSuitButtons();
	this->OnPlayCard(event);
}
void GamePanel::OnSeletcHearts(wxCommandEvent& event) {
	this->selectedSuit = SUITS[1];
	hideSelectSuitButtons();
	this->OnPlayCard(event);
}
void GamePanel::OnSeletcClubs(wxCommandEvent& event) {
	this->selectedSuit = SUITS[2];
	hideSelectSuitButtons();
	this->OnPlayCard(event);
}
void GamePanel::OnSeletcSpades(wxCommandEvent& event) {
	this->selectedSuit = SUITS[3];
	hideSelectSuitButtons();
	this->OnPlayCard(event);
}
void GamePanel::hideSelectSuitButtons() {
	this->selectNewSuitPanel->Hide();
	btnOnSeletcDiamonds->Hide();
	btnOnSeletcHearts->Hide();
	btnOnSeletcClubs->Hide();
	btnOnSeletcSpades->Hide();
	this->cardsPanel->Show();
	showUserPanel();
}
void GamePanel::showSelectSuitButtons() {
	hideUserPanel();
	this->selectNewSuitPanel->Show();
	btnOnSeletcDiamonds->Show();
	btnOnSeletcHearts->Show();
	btnOnSeletcClubs->Show();
	btnOnSeletcSpades->Show();
	this->cardsPanel->Hide();
}

//Select new mass
void GamePanel::createSelectMassBtns() {
	for (int i = 0; i < 13; i++) {
		wxButton* btn;
		if (i < 9) {
			btn = new wxButton(selectNewMassPanel, 10002 + i, VALUE_NAMES[i], wxPoint(0 + 55 * i, 0), wxSize(55, 70));
		}
		else {
			btn = new wxButton(selectNewMassPanel, 10002 + i, VALUE_NAMES[i], wxPoint(0 + 125 * (i-9), 70), wxSize(125, 70));
		}
		btn->Bind(wxEVT_BUTTON, &GamePanel::OnSelectMass, this);
		btnsOnSelectMass.push_back(btn);
	}
}
void GamePanel::OnSelectMass(wxCommandEvent& event) {
	this->selectedMass = event.GetId() - 10000;
	hideSelectMassButtons();
	this->OnPlayCard(event);
}
void GamePanel::hideSelectMassButtons() {
	selectNewMassPanel->Hide();
	for (int i = 0; i < btnsOnSelectMass.size(); i++) {
		btnsOnSelectMass[i]->Hide();
	}
	showUserPanel();
}
void GamePanel::showSelectMassButtons() {
	hideUserPanel();
	selectNewMassPanel->Show();
	for (int i = 0; i < btnsOnSelectMass.size(); i++) {
		btnsOnSelectMass[i]->Show();
	}
}

void GamePanel::displayUserCards() {
	cMain* cm = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cm->gameProcess;
	vector<Card> userCards = gameprocess->getPlayersInGame()[0]->getAvailableCards();
	userSelectedCardTxt->Hide();
	btnOnPlayCard->Hide();

	wxButton* btn;
	int Hlevel = 0;
	int Wlevel = 0;

	for (int i = 0; i < btnsUserCards.size(); i++) {
		btnsUserCards[i]->Destroy();
	}
	btnsUserCards.clear();
	if (userCards.size() != 0) {
		for (int i = 0; i < userCards.size(); i++) {
			int cord_corr = 460 / userCards.size();
			if (userCards.size() > 6) {
				btn = new wxButton(cardsPanel, 11001 + i, "", wxPoint(cord_corr * i, 0), wxSize(92, 134));
			}
			else {
				btn = new wxButton(cardsPanel, 11001 + i, "", wxPoint(92 * i, 0), wxSize(92, 134));
			}
			if (userCards[i].getMass() != 15) {
				int add_ID = 0;
				for (int j = 0; j < SUITS_AMOUNT; j++) {
					if (userCards[i].getSuit() == SUITS[j]) {
						add_ID = j * 13;
					}
				}
				string str = path[userCards[i].getMass() - 2 + add_ID];
				wxBitmap b(str, wxBITMAP_TYPE_PNG);
				btn->SetBitmap(b);
			}
			else {
				if (userCards[i].getSuit() == SUIT_JOKER_BLACK) {
					wxBitmap b(IM_JOKER_BLACK_P, wxBITMAP_TYPE_PNG);
					btn->SetBitmap(b);
				}
				else {
					wxBitmap b(IM_JOKER_RED_P, wxBITMAP_TYPE_PNG);
					btn->SetBitmap(b);
				}
			}
			btn->Bind(wxEVT_BUTTON, &GamePanel::OnButtonCard, this);
			btnsUserCards.push_back(btn);
			Wlevel++;
		}
	}
}
void GamePanel::displayGameDirection() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	if (gameprocess->getIsClockwise()) {
		GameDirectionBtm->SetBitmap(wxBitmap(IM_CLOCKWISE_P, wxBITMAP_TYPE_PNG));
	}
	else {
		GameDirectionBtm->SetBitmap(wxBitmap(IM_ANTICLOCKWISE_P, wxBITMAP_TYPE_PNG));
	}
}
void GamePanel::displayPlayedCards() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;
	vector<Card> cards = gameprocess->getPlayedCards();

	string str;
	if (cards.size() == 0) {
		wxBitmap b(IM_NA_P, wxBITMAP_TYPE_PNG);
		PlayedCardsBtm->SetBitmap(b);
	}
	else {
		int add_ID = 0;
		for (int i = 0; i < SUITS_AMOUNT; i++) {
			if (cards[cards.size() - 1].getSuit() == SUITS[i]) {
				add_ID = i * 13;
			}
		}
		str = path[cards[cards.size()-1].getMass() - 2 + add_ID];
		wxBitmap b(str, wxBITMAP_TYPE_PNG);
		PlayedCardsBtm->SetBitmap(b);
	}

}
void GamePanel::displayNameOfCurrentPlayer() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	if (gameprocess->getCurrentPlayer()->getName() == gameprocess->getUserName()) {
		currentPlayerNameTxt->Show();
	}
	else {
		currentPlayerNameTxt->Hide();
	}
}
void GamePanel::displayStockCardsAmount() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;
	Deck* cards = gameprocess->getStockCards();

	if (cards->getSize() == 0) {
		wxBitmap b(IM_NONE_P, wxBITMAP_TYPE_PNG);
		StockCardsBtm->SetBitmap(b);
	}
	else {
		wxBitmap b(IM_BACK_CARD_P, wxBITMAP_TYPE_PNG);
		StockCardsBtm->SetBitmap(b);
	}
}
void GamePanel::displayBotPlayers() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;
	vector<Player*> PIG = gameprocess->getPlayersInGame();

	for (int i = 0; i < BotsCardsBtms.size(); i++) {
		BotsCardsBtms[i]->Destroy();
	}
	BotsCardsBtms.clear();
	wxStaticBitmap* stb;
	int cord_correct;
	for (int i = 1; i < PIG.size(); i++) {
		if (PIG[i]->getAvailableCards().size() != 0) {
			if (i == 1) {
				cord_correct = 300 / PIG[i]->getAvailableCards().size();
				wxBitmap b(IM_BACK_CARD_ROTATED_P, wxBITMAP_TYPE_PNG);
				for (int j = 0; j < PIG[i]->getAvailableCards().size(); j++) {
					if (PIG[i]->getAvailableCards().size() > 3) {
						stb = new wxStaticBitmap(this, wxID_ANY, b, wxPoint(0, 20 + cord_correct * j), wxSize(134, 92));
					}
					else {
						stb = new wxStaticBitmap(this, wxID_ANY, b, wxPoint(0, 20 + 92 * j), wxSize(134, 92));
					}
					BotsCardsBtms.push_back(stb);
				}
			}
			else if (i == 2) {
				cord_correct = 300 / PIG[i]->getAvailableCards().size();
				wxBitmap b(IM_BACK_CARD_P, wxBITMAP_TYPE_PNG);
				for (int j = 0; j < PIG[i]->getAvailableCards().size(); j++) {
					if (PIG[i]->getAvailableCards().size() > 3) {
						stb = new wxStaticBitmap(this, wxID_ANY, b, wxPoint(200 + cord_correct * j, 0), wxSize(92, 134));
					}
					else {
						stb = new wxStaticBitmap(this, wxID_ANY, b, wxPoint(200 + 92 * j, 0), wxSize(92, 134));
					}
					BotsCardsBtms.push_back(stb);
				}
			}
			else if(i == 3) {
				cord_correct = 300 / PIG[i]->getAvailableCards().size();
				wxBitmap b(IM_BACK_CARD_ROTATED_P, wxBITMAP_TYPE_PNG);
				for (int j = 0; j < PIG[i]->getAvailableCards().size(); j++) {
					if (PIG[i]->getAvailableCards().size() > 3) {
						stb = new wxStaticBitmap(this, wxID_ANY, b, wxPoint(648, 20 + cord_correct * j), wxSize(134, 92));
					}
					else {
						stb = new wxStaticBitmap(this, wxID_ANY, b, wxPoint(648, 20 + 92 * j), wxSize(134, 92));
					}
					BotsCardsBtms.push_back(stb);
				}
			}
		}
	}

}
void GamePanel::displaycardsmustBeTakenAmount() {
	this->cardsmustBeTakenAmountTxt->Clear();
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	wxString stringnumber = wxString::Format(wxT("%d"), (int)gameprocess->getCardsMustBeTakenCurrent());
	this->cardsmustBeTakenAmountTxt->WriteText("Must take: " + stringnumber);
}
void GamePanel::displayCurrSuit() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	if (gameprocess->getIsItFirstStep()) {
		CurrentSuitBtm->Hide();
	}
	for (int i = 0; i < SUITS_AMOUNT; i++) {
		if (gameprocess->getCurrSuet() == SUITS[i]) {
			CurrentSuitBtm->SetBitmap(wxBitmap(IM_SUITS_P[i], wxBITMAP_TYPE_PNG));
			CurrentSuitBtm->Show();
			break;
		}
	}
}
void GamePanel::displayCurrStepMustBeSkipped() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	if (gameprocess->getIsCurrStepMustBeSkiped()) {
		currStepMustBeSkippedTxt->Show();
	}
	else {
		currStepMustBeSkippedTxt->Hide();
	}
}
void GamePanel::displayIsSnowballMode() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	if (gameprocess->getIsSnowballMode()) {
		SnowballModeBtm->Show();
	}
	else {
		SnowballModeBtm->Hide();
	}
}

void GamePanel::refreshInfo() {
	displayUserCards();
	displayGameDirection();
	displayPlayedCards();
	displayNameOfCurrentPlayer();
	displayStockCardsAmount();
	displaycardsmustBeTakenAmount();
	displayBotPlayers();
	displayCurrSuit();
	displayCurrStepMustBeSkipped();
	displayIsSnowballMode();
}

void GamePanel::runLooseActions(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	wxString looseString = wxString::Format(wxT("You lost - Game Over :( \n your score: %d"), (int)gameprocess->getLooserScore());
	wxMessageBox(looseString);
	OnExitToMenu(event);
}
void GamePanel::runVictoryActions(wxCommandEvent& event) {
	wxMessageBox("Congrats! - You won");
	OnExitToMenu(event);
}

void GamePanel::rollStepsToUser(wxCommandEvent& event, bool skipTime) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;
	if (!skipTime) {
		while (gameprocess->getCurrentPlayer()->getName() != gameprocess->getUserName()) {
			Sleep(1000);			//Sleep needed to let user see the game process
			gameprocess->makeMoveForBot();
			refreshInfo();
			if (!gameprocess->getIsUserLoosed() and gameprocess->getIsSomeoneLoosed()) {
				string looseString = gameprocess->GetLooserName() + " score: ";
				wxString playerScore = wxString::Format(wxT("%d"), (int)gameprocess->getLooserScore());
				looseString += playerScore;
				gameprocess->resetLooser();
				wxMessageBox(looseString);
				Sleep(2000);
			}
			if (gameprocess->getIsUserLoosed()) {
				runLooseActions(event);
				gameprocess->resetLooser();
				break;
			}
			else if (gameprocess->getIsUserWon()) {
				runVictoryActions(event);
				break;
			}
		}
	}
	else {
		refreshInfo();
		while (gameprocess->getCurrentPlayer()->getName() != gameprocess->getUserName()) {
			gameprocess->makeMoveForBot();
			if (gameprocess->getIsUserLoosed()) {
				runLooseActions(event);
				break;
			}
			else if (gameprocess->getIsUserWon()) {
				runVictoryActions(event);
				break;
			}
		}
		refreshInfo();
	}
}
void GamePanel::OnEndStep(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;
	
	if (gameprocess->isStepCanBeEnded() and gameprocess->getCurrentPlayer()->getName() == gameprocess->getUserName()) {
		gameprocess->endStep();
		if (!gameprocess->getIsUserLoosed() and gameprocess->getIsSomeoneLoosed()) {
			string looseString = gameprocess->GetLooserName() + " score: ";
			wxString playerScore = wxString::Format(wxT("%d"), (int)gameprocess->getLooserScore());
			looseString += playerScore;
			gameprocess->resetLooser();
			wxMessageBox(looseString);
		}
		if (gameprocess->getIsUserLoosed()) {
			runLooseActions(event);
			return;
		}
		else if (gameprocess->getIsUserWon()) {
			runVictoryActions(event);
			return;
		}
		refreshInfo();
		rollStepsToUser(event, false);
	}
}

void GamePanel::OnSayUno(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	gameprocess->sayUno();
}
