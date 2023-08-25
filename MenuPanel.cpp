#include "MenuPanel.h"
#include "GamePanel.h"
#include "GuideWindow.h"
#include "cMain.h"
using namespace std;

using namespace std;
const int ID_P_MENU = 100;				//P = Panel, B = Button, T = Text, ST = static 
const int ID_B_MUTEMUSIC = 101;
const int ID_B_OPENGAME = 102;
const int ID_STT_PLAYERSINFO = 103;
const int ID_STT_CARDSINFO = 104;
const int ID_B_INCREASEPLAYERSAMOUNT = 105;
const int ID_B_DECREASEPLAYERSAMOUNT = 106;
const int ID_B_INCREASECARDSAMOUNT = 107;
const int ID_B_DECREASECARDSAMOUNT = 108;
const int ID_B_GUIDE = 109;

MenuPanel::MenuPanel(wxPanel* parent) : wxPanel(parent, ID_P_MENU, wxPoint(0, 0), wxSize(800, 600)) {
	parrentPanel = parent;

	startPlayersAmount = 2;
	startCardsAmount = 4;
	isMuted = false;

	btnMuteMusic = new wxButton(this, ID_B_MUTEMUSIC, wxT(" "), wxPoint(730, 10), wxSize(40, 40));
	btnOpenGame = new wxButton(this, ID_B_OPENGAME, wxT("Play"), wxPoint(360, 200));
	btnOnIncreasePlayersAmount = new wxButton(this, ID_B_INCREASEPLAYERSAMOUNT, wxT("+"), wxPoint(350, 230), wxSize(20, 15));
	btnOnDecreasePlayersAmount = new wxButton(this, ID_B_DECREASEPLAYERSAMOUNT, wxT("-"), wxPoint(350, 245), wxSize(20, 15));
	btnOnIncreaseStartCardsAmount = new wxButton(this, ID_B_INCREASECARDSAMOUNT, wxT("+"), wxPoint(350, 265), wxSize(20, 15));
	btnOnDecreaseStartCardsAmount = new wxButton(this, ID_B_INCREASECARDSAMOUNT, wxT("-"), wxPoint(350, 280), wxSize(20, 15));
	btnOnGuide = new wxButton(this, ID_B_GUIDE, wxT("Guide"), wxPoint(720, 540), wxSize(50, 20));


	btnMuteMusic->SetBitmap(wxICON(icon_unmute));
	sound->Play(music_Serious_Sam, wxSOUND_ASYNC | wxSOUND_LOOP);

	btnMuteMusic->Bind(wxEVT_BUTTON, &MenuPanel::OnMuteMusic, this);
	btnOpenGame->Bind(wxEVT_BUTTON, &MenuPanel::OnOpenGame, this);
	btnOnIncreasePlayersAmount->Bind(wxEVT_BUTTON, &MenuPanel::OnIncreasePlayersAmount, this);
	btnOnDecreasePlayersAmount->Bind(wxEVT_BUTTON, &MenuPanel::OnDecreasePlayersAmount, this);
	btnOnIncreaseStartCardsAmount->Bind(wxEVT_BUTTON, &MenuPanel::OnIncreaseStartCardsAmount, this);
	btnOnDecreaseStartCardsAmount->Bind(wxEVT_BUTTON, &MenuPanel::OnDecreaseStartCardsAmount, this);
	btnOnGuide->Bind(wxEVT_BUTTON, &MenuPanel::OnGuide, this);

	playersAmountText = new wxStaticText(this, ID_STT_PLAYERSINFO, wxT("Players: 2"), wxPoint(375, 230));
	cardsAmountText = new wxStaticText(this, ID_STT_CARDSINFO, wxT("Cards: 4"), wxPoint(375, 265));
}

MenuPanel::~MenuPanel() {

}

void MenuPanel::OnMuteMusic(wxCommandEvent& event) {
	if (isMuted) {
		btnMuteMusic->SetBitmap(wxICON(icon_unmute));
		sound->Play(music_Serious_Sam, wxSOUND_ASYNC | wxSOUND_LOOP);
		isMuted = false;
	}
	else {
		btnMuteMusic->SetBitmap(wxICON(icon_mute));
		sound->Stop();
		isMuted = true;
	}
}
void MenuPanel::OnOpenGame(wxCommandEvent& event) {
	this->Hide();
	cMain* cm = (cMain*)this->parrentPanel->GetParent();
	GamePanel* gamePanel = (GamePanel*)this->parrentPanel->GetChildren()[0];
	gamePanel->Show();

	this->sound->Stop();
	if (!this->isMuted) {
		gamePanel->isMuted = false;
		gamePanel->btnMuteMusic->SetBitmap(wxICON(icon_unmute));
		gamePanel->sound->Play(music_DOOM, wxSOUND_ASYNC | wxSOUND_LOOP);
	}
	else {
		gamePanel->isMuted = true;
		gamePanel->btnMuteMusic->SetBitmap(wxICON(icon_mute));
		gamePanel->sound->Stop();
	}

	cm->gameProcess->InitiateNewGame(startPlayersAmount, startCardsAmount, "P1");

	gamePanel->refreshInfo();
	gamePanel->rollStepsToUser(event, true);
}
void MenuPanel::OnExitButton(wxCommandEvent& event) {
	wxPuts("Exit");
	Close(true);
	event.Skip();
}
void MenuPanel::OnIncreasePlayersAmount(wxCommandEvent& event) {
	if (this->startPlayersAmount == 4) {
		this->playersAmountText->SetLabelText(wxT("Players: 4\n4 players max"));
		event.Skip();
	}
	else if (this->startPlayersAmount < 4) {
		this->startPlayersAmount++;
		wxString str = wxString::Format(wxT("Players: %d"), startPlayersAmount);
		this->playersAmountText->SetLabelText(str);
		event.Skip();
	}
	else {
		this->playersAmountText->SetLabelText(wxT("Players: 4"));
		this->startPlayersAmount = 4;
		event.Skip();
	}
}
void MenuPanel::OnDecreasePlayersAmount(wxCommandEvent& event) {
	if (this->startPlayersAmount == 2) {
		this->playersAmountText->SetLabelText(wxT("Players: 2\n2 players min"));
		event.Skip();
	}
	else if (this->startPlayersAmount > 2) {
		this->startPlayersAmount--;
		wxString str = wxString::Format(wxT("Players: %d"), startPlayersAmount);
		this->playersAmountText->SetLabelText(str);
		event.Skip();
	}
	else {
		this->playersAmountText->SetLabelText(wxT("Players: 2"));
		this->startPlayersAmount = 2;
		event.Skip();
	}
}
void MenuPanel::OnIncreaseStartCardsAmount(wxCommandEvent& event) {
	if (this->startCardsAmount == 8) {
		this->cardsAmountText->SetLabelText(wxT("Cards: 8\n8 cards max"));
		event.Skip();
	}
	else if (this->startCardsAmount < 8) {
		this->startCardsAmount++;
		wxString str = wxString::Format(wxT("Cards: %d"), startCardsAmount);
		this->cardsAmountText->SetLabelText(str);
		event.Skip();
	}
	else {
		this->cardsAmountText->SetLabelText(wxT("Cards: 8"));
		this->startCardsAmount = 8;
		event.Skip();
	}
}
void MenuPanel::OnDecreaseStartCardsAmount(wxCommandEvent& event) {
	if (this->startCardsAmount == 4) {
		this->cardsAmountText->SetLabelText(wxT("Cards: 4\n4 cards min"));
		event.Skip();
	}
	else if (this->startCardsAmount > 4) {
		this->startCardsAmount--;
		wxString str = wxString::Format(wxT("Cards: %d"), startCardsAmount);
		this->cardsAmountText->SetLabelText(str);
		event.Skip();
	}
	else {
		this->cardsAmountText->SetLabelText(wxT("Cards: 4"));
		this->startCardsAmount = 4;
		event.Skip();
	}
}
void MenuPanel::OnGuide(wxCommandEvent& event) {
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
