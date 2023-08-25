#include "cMain.h"


using namespace std;

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	
wxEND_EVENT_TABLE()




cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Last player", wxPoint(420, 150), wxSize(800, 600),
	wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN) {
	SetIcon(wxICON(icon_frame));
	gameProcess = new GameProcess();

	mainPanel = new wxPanel(this, -1);

	guideWindow = new GuideWindow(this);

	gamePanel = new GamePanel(mainPanel);

	menuPanel = new MenuPanel(mainPanel);
}




cMain::~cMain()
{

}