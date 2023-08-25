#pragma once
#include <string>
#include <vector>
using namespace std;
const string s = "../Last_Player/Images";
const string d = s + "/Diamonds";
const string c = s + "/Clubs";
const string h = s + "/Hearts";
const string S = s + "/Spades";
const vector<string> path{
	d + "/2.png", d + "/3.png", d + "/4.png", d + "/5.png", d + "/6.png", d + "/7.png", d + "/8.png", d + "/9.png", d + "/10.png", d + "/J.png", d + "/Q.png", d + "/K.png", d + "/A.png",
	h + "/2.png", h + "/3.png", h + "/4.png", h + "/5.png", h + "/6.png", h + "/7.png", h + "/8.png", h + "/9.png", h + "/10.png", h + "/J.png", h + "/Q.png", h + "/K.png", h + "/A.png",
	c + "/2.png", c + "/3.png", c + "/4.png", c + "/5.png", c + "/6.png", c + "/7.png", c + "/8.png", c + "/9.png", c + "/10.png", c + "/J.png", c + "/Q.png", c + "/K.png", c + "/A.png",
	S + "/2.png", S + "/3.png", S + "/4.png", S + "/5.png", S + "/6.png", S + "/7.png", S + "/8.png", S + "/9.png", S + "/10.png", S + "/J.png", S + "/Q.png", S + "/K.png", S + "/A.png",
};

const string IM_NONE_P = "../Last_Player/Images/None.png";
const string IM_NA_P = "../Last_Player/Images/NA.png";
const string IM_BACK_CARD_P = "../Last_Player/Images/Back_Card.png";
const string IM_BACK_CARD_ROTATED_P = "../Last_Player/Images/Back_Card_Rotated.png";
const string IM_JOKER_BLACK_P = "../Last_Player/Images/BJ.png";
const string IM_JOKER_RED_P = "../Last_Player/Images/RJ.png";

const string IM_SNOWBOLLMODE_P = "../Last_Player/Images/Up_Sign.png";
const string IM_CLOCKWISE_P = "../Last_Player/Images/Clockwise.png";
const string IM_ANTICLOCKWISE_P = "../Last_Player/Images/Anticlockwise.png";

const string IM_SUIT_DIAMONDS_P = "../Last_Player/Images/Diamonds.png";
const string IM_SUIT_HEARTS_P = "../Last_Player/Images/Hearts.png";
const string IM_SUIT_CLUBS_P = "../Last_Player/Images/Clubs.png";
const string IM_SUIT_SPADES_P = "../Last_Player/Images/Spades.png";

const vector<string> IM_SUITS_P{ IM_SUIT_DIAMONDS_P, IM_SUIT_HEARTS_P, IM_SUIT_CLUBS_P, IM_SUIT_SPADES_P };