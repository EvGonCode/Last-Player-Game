#include "GuideWindow.h"
#include "cMain.h"


wxBEGIN_EVENT_TABLE(GuideWindow, wxFrame)

wxEND_EVENT_TABLE()

static int ID_STT_GUIDE = 101;


GuideWindow::GuideWindow(wxWindow* parent) : wxFrame(parent, wxID_ANY, "Text guide", wxPoint(0, 0), wxSize(420, 840))
{
	this->parentWindow = parent;
	cMain* cmain = (cMain*)parentWindow;
	SetIcon(wxICON(icon_guide_frame));
	this->SetBackgroundColour(wxColor(255, 255, 255));

	guide = new wxTextCtrl(this, ID_STT_GUIDE, wxT(""), wxPoint(-1, -1), wxSize(400, 800), wxTE_MULTILINE | wxTE_READONLY);
	GuideTxt* guideTxt = new GuideTxt();
	guide->WriteText(guideTxt->getText());
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false);
	guide->SetFont(font);

	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(guide, 1, wxEXPAND);
	this->SetSizer(vbox);
	vbox->Layout();
}

GuideWindow::~GuideWindow() {
	cMain* cmain = (cMain *)parentWindow;
	cmain->isGuideOpen = false;
}