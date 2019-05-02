//-----------------------------------------------------------------
// Defiers of the Four Application
// C++ Source - DotF.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "DotF.h"


//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------
BOOL GameInitialize(HINSTANCE _hInstance)
{
	// Create the game engine
	game = new GameEngine(_hInstance, (LPTSTR) TEXT("Defiers of the Four"),
		(LPTSTR) TEXT("Defiers of the Four"), (WORD) IDI_DOTF, (WORD) IDI_DOTF_SM, 1024, 768);
	if (game == NULL)
		return FALSE;

	// Set the frame rate
	game->SetFrameRate(30);

	// Store the instance handle
	hInstance = _hInstance;	

	// Configure game variables
	currentScene = MENU_MAIN;
	playerNum = -1;

	return TRUE;
}

void GameStart(HWND _hWindow)
{
	// Seed the random number generator
	srand(GetTickCount());

	// Create the offscreen device context and bitmap
	offScreenDC = CreateCompatibleDC(GetDC(_hWindow));
	offScreenBitmap = CreateCompatibleBitmap(GetDC(_hWindow),
		game->GetWidth(), game->GetHeight());
	SelectObject(offScreenDC, offScreenBitmap);

	// Device context
	HDC hDC = GetDC(_hWindow);

	//-----------------------------------------------------------------
	// Characters
	//-----------------------------------------------------------------
	Bitmap *robotBitmap = new Bitmap(hDC, IDB_MENU_ROBOT, hInstance);
	RECT test = { 0, 100, 0, 100 };
	Sprite *robotSprite;
	POINT pos;
	pos.x = 250;
	pos.y = 250;
	robotSprite = new Sprite(robotBitmap);
	Robot *robot1 = new Robot({ "Robot 1" }, { "Robot 1 Desc" }, robotSprite, 100, 7, pos, PLAYER_1, 10, 30);
	robotSprite = new Sprite(robotBitmap);
	Robot *robot2 = new Robot({ "Robot 2" }, { "Robot 2 Desc" }, robotSprite, 100, 7, pos, PLAYER_1, 10, 30);
	robotSprite = new Sprite(robotBitmap);
	Robot *robot3 = new Robot({ "Robot 3" }, { "Robot 3 Desc" }, robotSprite, 100, 7, pos, PLAYER_1, 10, 30);
	robotSprite = new Sprite(robotBitmap);
	Robot *robot4 = new Robot({ "Robot 4" }, { "Robot 4 Desc" }, robotSprite, 100, 7, pos, PLAYER_1, 10, 30);
	robots.push_back(robot1);
	robots.push_back(robot2);
	robots.push_back(robot3);
	robots.push_back(robot4);

	// Menu bitmaps and sprites
	bmMenuBackground = new Bitmap(hDC, 1024, 768, RGB(22, 15, 28));
	bmMenuTitle = new Bitmap(hDC, IDB_MENU_TITLE, hInstance);
	bmMenuStar = new Bitmap(hDC, IDB_MENU_STAR, hInstance);

	//-----------------------------------------------------------------
	// Buttons
	//-----------------------------------------------------------------
	// Main menu buttons 
	btnPlay = new Button(hDC, (LPTSTR) TEXT("Play"), (RES_W/2) - (BTN_WIDTH/2), 400);
	menuMainButtons.push_back(btnPlay);
	btnExit = new Button(hDC, (LPTSTR)TEXT("Exit"), (RES_W/2) - (BTN_WIDTH/2), 450);
	menuMainButtons.push_back(btnExit);
	
	// Play menu buttons 
	btn1Player = new Button(hDC, (LPTSTR)TEXT("1 Player"), (RES_W/2) - (BTN_WIDTH/2), 400);
	menuPlayersButtons.push_back(btn1Player);
	btn2Player = new Button(hDC, (LPTSTR)TEXT("2 Player"), (RES_W/2) - (BTN_WIDTH/2), 450);
	menuPlayersButtons.push_back(btn2Player);
	btnBackToMain = new Button(hDC, (LPTSTR)TEXT("Back"), (RES_W/2) - (BTN_WIDTH/2), 500);
	menuPlayersButtons.push_back(btnBackToMain);

	// Character select buttons
	btnReady = new Button(hDC, (LPTSTR)TEXT("Begin"), (RES_W / 2) - (BTN_WIDTH / 2), 650);
	menuRobotsButtons.push_back(btnReady);
	btnBackToPlayers = new Button(hDC, (LPTSTR)TEXT("Back"), (RES_W / 2) - (BTN_WIDTH / 2), 700);
	menuRobotsButtons.push_back(btnBackToPlayers);

}

void GameEnd()
{
	// Cleanup the offscreen device context and bitmap
	DeleteObject(offScreenBitmap);
	DeleteDC(offScreenDC);

	// Cleanup the sprites
	game->CleanupSprites();

	// Cleanup the game engine
	delete game;
}

void GameActivate(HWND _hWindow)
{
}

void GameDeactivate(HWND _hWindow)
{
}

void GamePaint(HDC _hDC)
{
	switch (currentScene) {
		case MENU_MAIN:
			bmMenuBackground->Draw(_hDC, 0, 0);
			game->PrintText(_hDC, (LPTSTR)TEXT("Defiers of the Four"), 96, { 0, 150, 1024, 300 });
			for (auto &Button : menuMainButtons) {
				Button->Draw(_hDC);
			}
			break;
		case MENU_SELECT_PLAYERS:
			bmMenuBackground->Draw(_hDC, 0, 0);
			game->PrintText(_hDC, (LPTSTR)TEXT("Game Type"), 64, { 0, 150, 1024, 300 });
			for (auto &Button : menuPlayersButtons) {
				Button->Draw(_hDC);
			}
			break;
		case MENU_SELECT_ROBOTS:
			bmMenuBackground->Draw(_hDC, 0, 0);
			game->PrintText(_hDC, (LPTSTR)TEXT("Select Characters"), 64, { 0, 150, 1024, 300 });

			// Draw robots
			DrawRobotsOnMenu(_hDC);
			// Select menu buttons
			btnBackToPlayers->Draw(_hDC);
			if (selectedRobots.size() == playerNum * 2) {
				btnReady->Draw(_hDC);
			}
			break;
		case GAME_PLAY:
			game->DrawSprites(_hDC);
			break;
		case GAME_PAUSE:
			break;
		default:
			break;
	}
}

void GameCycle()
{
	// Update the sprites
	game->UpdateSprites();

	// Obtain a device context for repainting the game
	HWND  hWindow = game->GetWindow();
	HDC   hDC = GetDC(hWindow);

	// Paint the game to the offscreen device context
	GamePaint(offScreenDC);

	// Blit the offscreen bitmap to the game screen
	BitBlt(hDC, 0, 0, game->GetWidth(), game->GetHeight(),
		offScreenDC, 0, 0, SRCCOPY);

	// Cleanup
	ReleaseDC(hWindow, hDC);
}

void HandleKeys()
{
}


void MouseButtonDown(int _x, int _y, BOOL _isLeftClick)
{
}

void MouseButtonUp(int _x, int _y, BOOL _isLeftClick)
{
	if (_isLeftClick) {
		HandleMenuButtonClick(_x, _y);
	}
}

void MouseMove(int _x, int _y)
{
	// Hover effect for menu
	HandleMenuButtonHover(_x, _y);
	
}

void HandleJoystick(JOYSTATE _joystickState)
{
}

BOOL SpriteCollision(Sprite* _spriteHitter, Sprite* _spriteHittee)
{
	// Swap the sprite velocities so that they appear to bounce
	POINT ptSwapVelocity = _spriteHitter->GetVelocity();
	_spriteHitter->SetVelocity(_spriteHittee->GetVelocity());
	_spriteHittee->SetVelocity(ptSwapVelocity);
	return TRUE;
}

//-----------------------------------------------------------------
// Menu functions
//-----------------------------------------------------------------
void HandleMenuButtonClick(int _x, int _y) {
	int i = 0; // to retrieve which robot is clicked

	switch (currentScene) {
	case MENU_MAIN:
		// Play clicked
		if (btnPlay->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK, hInstance, SND_ASYNC | SND_RESOURCE);
			currentScene = MENU_SELECT_PLAYERS;
		}

		// Exit clicked
		if (btnExit->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK_BACK, hInstance, SND_ASYNC | SND_RESOURCE);
			GameEnd();
		}
		break;
	case MENU_SELECT_PLAYERS:
		// Back to main menu clicked
		if (btnBackToMain->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK_BACK, hInstance, SND_ASYNC | SND_RESOURCE);
			currentScene = MENU_MAIN;
		}

		// 1 - Player selected
		if (btn1Player->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK, hInstance, SND_ASYNC | SND_RESOURCE);
			playerNum = 1;
			currentScene = MENU_SELECT_ROBOTS;
		}

		// 2 - Player selected
		if (btn2Player->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK, hInstance, SND_ASYNC | SND_RESOURCE);
			playerNum = 2;
			currentScene = MENU_SELECT_ROBOTS;
		}
		break;
	case MENU_SELECT_ROBOTS:
		// Button click - Ready
		if (btnReady->GetSprite()->IsPointInside(_x, _y) && playerNum * 2 == selectedRobots.size()) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK, hInstance, SND_ASYNC | SND_RESOURCE);
			currentScene = GAME_PLAY;
		}

		// Button click - Back
		if (btnBackToPlayers->GetSprite()->IsPointInside(_x, _y)) {
			PlaySound((LPCWSTR)IDW_MENU_CLICK_BACK, hInstance, SND_ASYNC | SND_RESOURCE);
			currentScene = MENU_SELECT_PLAYERS;
		}

		// Robot select
		for (auto &Robot : robots) {
			if (Robot->GetSprite()->IsPointInside(_x, _y)) {
				bool robotIsSelected = std::find(selectedRobots.begin(), selectedRobots.end(), i) != selectedRobots.end();

				// Add to selected if not selected, erase otherwise
				if (!robotIsSelected) {
					PlaySound((LPCWSTR)IDW_MENU_SELECT, hInstance, SND_ASYNC | SND_RESOURCE);
					selectedRobots.push_back(i);
				}
				else {
					selectedRobots.erase(std::remove(selectedRobots.begin(), selectedRobots.end(), i), selectedRobots.end());
				}
			}
			i++;
		}
		break;
	default:
		break;
	}
}

void HandleMenuButtonHover(int _x, int _y) {
	switch (currentScene) {
	case MENU_MAIN:
		for (auto &Button : menuMainButtons)
		{
			if (Button->GetSprite()->IsPointInside(_x, _y)) {
				Button->SetHover(true);
			}
			else {
				Button->SetHover(false);
			}
		}
		break;
	case MENU_SELECT_PLAYERS:
		for (auto &Button : menuPlayersButtons)
		{
			if (Button->GetSprite()->IsPointInside(_x, _y)) {
				Button->SetHover(true);
			}
			else {
				Button->SetHover(false);
			}
		}
		break;
	case MENU_SELECT_ROBOTS:
		for (auto &Button : menuRobotsButtons)
		{
			if (Button->GetSprite()->IsPointInside(_x, _y)) {
				Button->SetHover(true);
			}
			else {
				Button->SetHover(false);
			}
		}

		for (auto &Robot : robots) {
			if (Robot->GetSprite()->IsPointInside(_x, _y)) {
				Robot->SetMenuHover(true);
			}
			else {
				Robot->SetMenuHover(false);
			}
		}
		break;
	default:
		break;
	}
}

void DrawRobotsOnMenu(HDC _hDC) {
	// 100 x 100 robot icons
	int iconWidth = 100;
	int offset = iconWidth + iconWidth;

	// Calculate to center robot icons
	POINT start;
	start.x = (RES_W/2) - (iconWidth/2) - ((robots.size()-1) * iconWidth);
	start.y = 300;

	int i = 0; // to see which robot is clicked
	for (auto &Robot : robots) {
		Robot->GetSprite()->SetPosition(start.x + (i*offset), start.y); // set new position
		bool robotIsSelected = std::find(selectedRobots.begin(), selectedRobots.end(), i) != selectedRobots.end(); // check if robot is selected

		/*
		// If robot is hovered:
		//		not selected -> white focus
		//		selected	 -> red focus
		// If not hovered:
		//		not selected -> nothing
		//		selected	 -> green focus
		*/
		if (Robot->GetMenuHover()) {
			game->PrintText(_hDC, (LPCWSTR)ConvertString(Robot->GetName()), 36, { 0, 500, 1024, 550 });
			game->PrintText(_hDC, (LPCWSTR)ConvertString(Robot->GetDescription()), 36, { 224, 550, 800, 700 });

			HBRUSH hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
			if (robotIsSelected) {
				SelectObject(_hDC, hRedBrush);
			}

			Rectangle(_hDC, Robot->GetSprite()->GetPosition().left - 5, Robot->GetSprite()->GetPosition().top - 5,
				Robot->GetSprite()->GetPosition().right + 20, Robot->GetSprite()->GetPosition().bottom + 20);
			DeleteObject(hRedBrush);
		}
		else if (robotIsSelected) {
			HBRUSH hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(_hDC, hGreenBrush);
			
			Rectangle(_hDC, Robot->GetSprite()->GetPosition().left - 5, Robot->GetSprite()->GetPosition().top - 5,
				Robot->GetSprite()->GetPosition().right + 20, Robot->GetSprite()->GetPosition().bottom + 20);
			DeleteObject(hGreenBrush);
		}	
		Robot->GetSprite()->Draw(_hDC);
		i++;
	}

	// Display how many robots more should be selected
	if (playerNum * 2 > selectedRobots.size()) {
		std::string remaining = std::to_string(playerNum * 2 - selectedRobots.size()) + " remaining";
		game->PrintText(_hDC, (LPCWSTR)ConvertString(remaining), 24, { 0, 250, 1024, 300 });
	}
}

//-----------------------------------------------------------------
// Utility
//-----------------------------------------------------------------
LPWSTR ConvertString(const std::string& instr) {
	// Assumes std::string is encoded in the current Windows ANSI codepage
	int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);

	if (bufferlen == 0)
	{
		// Something went wrong. Perhaps, check GetLastError() and log.
		return 0;
	}

	// Allocate new LPWSTR - must deallocate it later
	LPWSTR widestr = new WCHAR[bufferlen + 1];

	::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);

	// Ensure wide string is null terminated
	widestr[bufferlen] = 0;

	// Do something with widestr
	return widestr;
	//delete[] widestr;
}
