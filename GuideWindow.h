#pragma once
#include "wx\wx.h"
#include "wx\icon.h"
#include "resource.h"
#include <wx/panel.h>
#include "GuideTxt.h"


class GuideWindow : public wxFrame
{
public:
	GuideWindow(wxWindow* parent);
	~GuideWindow();

	wxPanel* mainPanel;
	wxWindow* parentWindow;
	wxTextCtrl* guide;
public:
	wxDECLARE_EVENT_TABLE();
};

