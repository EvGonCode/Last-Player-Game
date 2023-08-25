#pragma once
#include <sstream>
#include <fstream>
#include <codecvt>
using namespace std;


class GuideTxt {
public:
	GuideTxt() {}

	wstring  getText() {
		wifstream wif("../Last_Player/Guide/Guide.txt");
		wif.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
		wstringstream wss;
		wss << wif.rdbuf();
		return wss.str();
		wif.close();
	}
};