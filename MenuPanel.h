#pragma once
#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/sound.h>
#include <wx/stattext.h>
#include "resource.h"
#include "Music.h"



class MenuPanel : public wxPanel
{
public:
	wxPanel* parrentPanel;
	wxButton* btnMuteMusic;
	wxButton* btnOpenGame;
	wxButton* btnOnIncreasePlayersAmount;
	wxButton* btnOnDecreasePlayersAmount;
	wxButton* btnOnIncreaseStartCardsAmount;
	wxButton* btnOnDecreaseStartCardsAmount;
	wxButton* btnOnGuide;
	wxSound* sound;
	wxStaticText* playersAmountText;
	wxStaticText* cardsAmountText;

	int startCardsAmount;
	int startPlayersAmount;
	bool isMuted;

	MenuPanel(wxPanel* parent);
	~MenuPanel();

public:
	void OnExitButton(wxCommandEvent& evt);
	void OnMuteMusic(wxCommandEvent& event);
	void OnOpenGame(wxCommandEvent& event);
	void OnIncreasePlayersAmount(wxCommandEvent& event);
	void OnDecreasePlayersAmount(wxCommandEvent& event);
	void OnIncreaseStartCardsAmount(wxCommandEvent& event);
	void OnDecreaseStartCardsAmount(wxCommandEvent& event);
	void OnGuide(wxCommandEvent& event);
};

