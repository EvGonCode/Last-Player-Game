#pragma once
#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/sound.h>
#include <wx/bmpbuttn.h>
#include "resource.h"
#include "Music.h"
#include "CardsImagesPath.h"




class GamePanel : public wxPanel
{
public:
	wxPanel* parrentPanel;
	wxButton* btnMuteMusic;
	wxButton* btnExitToMenu;
	wxButton* btnOnGuide;
	wxButton* btnOnPlayCard;
	wxButton* btnOnTakeCard;
	wxButton* btnOnEndStep;
	wxButton* btnOnSayUno;

	wxPanel* cardsPanel;
	wxTextCtrl* userSelectedCardTxt;
	vector<wxButton*> btnsUserCards;
	void hideUserPanel();
	void showUserPanel();
	void OnButtonCard(wxCommandEvent& event);

	wxPanel* selectNewSuitPanel;
	wxButton* btnOnSeletcDiamonds;
	wxButton* btnOnSeletcHearts;
	wxButton* btnOnSeletcClubs;
	wxButton* btnOnSeletcSpades;
	string selectedSuit;
	void hideSelectSuitButtons();
	void showSelectSuitButtons();

	wxPanel* selectNewMassPanel;
	vector<wxButton*> btnsOnSelectMass;
	void createSelectMassBtns();
	void OnSelectMass(wxCommandEvent& event);
	void hideSelectMassButtons();
	void showSelectMassButtons();
	int selectedMass;

	wxStaticBitmap* PlayedCardsBtm;
	wxStaticBitmap* StockCardsBtm;
	wxStaticBitmap* GameDirectionBtm;
	wxStaticBitmap* SnowballModeBtm;
	wxStaticBitmap* CurrentSuitBtm;
	wxTextCtrl* currentPlayerNameTxt;
	wxTextCtrl* cardsmustBeTakenAmountTxt;
	wxTextCtrl* currStepMustBeSkippedTxt;

	vector<wxTextCtrl*> botsTxt;

	bool isMuted;
	wxSound* sound;

	GamePanel(wxPanel* parent);
	~GamePanel();

public:
	void OnMuteMusic(wxCommandEvent& event);
	void OnExitToMenu(wxCommandEvent& event);
	void OnGuide(wxCommandEvent& event);
	void OnPlayCard(wxCommandEvent& event);
	void OnTakeCard(wxCommandEvent& event);
	void OnEndStep(wxCommandEvent& event);
	void OnSayUno(wxCommandEvent& event);

	void OnSeletcDiamonds(wxCommandEvent& event);
	void OnSeletcHearts(wxCommandEvent& event);
	void OnSeletcClubs(wxCommandEvent& event);
	void OnSeletcSpades(wxCommandEvent& event);

	void displayUserCards();
	void displayGameDirection();
	void displayPlayedCards();
	void displayNameOfCurrentPlayer();
	void displayStockCardsAmount();
	void displaycardsmustBeTakenAmount();
	vector<wxStaticBitmap*> BotsCardsBtms;
	void displayBotPlayers();
	void displayCurrSuit();
	void displayCurrStepMustBeSkipped();
	void displayIsSnowballMode();
	void refreshInfo();

	void rollStepsToUser(wxCommandEvent& event, bool skipTime);

	void runLooseActions(wxCommandEvent& event);
	void runVictoryActions(wxCommandEvent& event);
};

