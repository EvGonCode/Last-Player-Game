#pragma once
#include "wx\wx.h"
#include "cMain.h"

class cApp : public wxApp
{
public:
	cApp();

	~cApp();
	bool OnInit();
private:
	cMain* main_frame = nullptr;
};

