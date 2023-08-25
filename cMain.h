#pragma once
#include "wx\wx.h"
#include "wx\icon.h"
#include "resource.h"
#include <wx/panel.h>
#include <wx/button.h>
#include <wx\sizer.h>
#include <wx/sound.h>
#include <wx/textfile.h>
#include <wx/string.h>
#include "MenuPanel.h"
#include "GamePanel.h"
#include "GuideWindow.h"
#include "GameProcess.h"


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	wxPanel* mainPanel;
	MenuPanel* menuPanel;
	GamePanel* gamePanel;
	GuideWindow* guideWindow;
	GameProcess* gameProcess;

	bool isGuideOpen;

public:
	wxDECLARE_EVENT_TABLE();
};