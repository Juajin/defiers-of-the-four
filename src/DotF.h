//-----------------------------------------------------------------
// DotF Application
// C++ Header - DotF.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include <vector>
#include <algorithm>
#include "Resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "Character.h"
#include "Robot.h"
#include "Button.h"


//-----------------------------------------------------------------
// Resolution
//-----------------------------------------------------------------
const int RES_W = 1024;
const int RES_H = 768;

//-----------------------------------------------------------------
// Scene Flags
//-----------------------------------------------------------------
enum SCENE {
	MENU_MAIN = 0,
	MENU_SELECT_PLAYERS = 1,
	MENU_SELECT_ROBOTS = 2,
	GAME_PLAY = 3,
	GAME_PAUSE = 4
};

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE   hInstance;
GameEngine* game;
HDC         offScreenDC;
HBITMAP     offScreenBitmap;
SCENE		currentScene;

//-----------------------------------------------------------------
// Characters
//-----------------------------------------------------------------
vector<Robot*>	robots;
vector<int>	selectedRobots;
int			playerNum; // single player or multiplayer

//-----------------------------------------------------------------
// Menu Bitmaps / Sprites
//-----------------------------------------------------------------
Bitmap  	*bmMenuBackground;
Bitmap  	*bmMenuTitle;
Bitmap  	*bmMenuStar;

//-----------------------------------------------------------------
// Buttons
//-----------------------------------------------------------------
vector<Button*>	menuMainButtons, menuPlayersButtons, menuRobotsButtons;
Button			*btnPlay, *btnExit;
Button			*btn1Player, *btn2Player, *btnBackToMain;
Button			*btnReady, *btnBackToPlayers;


//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Menu functions
//-----------------------------------------------------------------
void	HandleMenuButtonClick(int _x, int _y);
void	HandleMenuButtonHover(int _x, int _y);
void	DrawRobotsOnMenu(HDC _hDC);

//-----------------------------------------------------------------
// Utility
//-----------------------------------------------------------------
LPWSTR ConvertString(const std::string& instr);
