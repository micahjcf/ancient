#include <iostream>
#include <windows.h>
//#include <stdlib.h>
#include <string>
#include <conio.h>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ios;
using std::ofstream;

#include <My Header Files\_MJCF_ConGlob.h>
#include <My Header Files\_MJCF_Output.h>
#include <My Header Files\_MJCF_Keyboard.h>
#include <My Header Files\_MJCF_RandNumGen.h>

#define MM_WIDTH	18
#define MM_HEIGHT	10
#define MM_LEFT		(SCREEN_XMAX/2)-(MM_WIDTH/2)
#define MM_TOP		(SCREEN_YMAX/2)-(MM_HEIGHT/2)

#define SM_WIDTH	30
#define SM_HEIGHT	12
#define SM_LEFT		(SCREEN_XMAX/2)-(SM_WIDTH/2)
#define SM_TOP		(SCREEN_YMAX/2)-(SM_HEIGHT/2)

int* Matrix = NULL;

void UpdateGameFile(int, int, int);

#include "Data Structures.h"
#include "GameSystem.h"

void Play()
{
	bool giveup = false;
	gv.CurMatch = 0;
	while(gv.CurMatch < gv.MatchSize && !giveup)
	{
		Engine();
		gv.CurMatch++;
		Text((SCREEN_XMAX/2)-20, SCREEN_YMAX, "Press Space to continue or 'G' to give up");
		do{
			GetKeyboardInput();
			switch(kb.dwKeyPressed)
			{
			case 'G':
				giveup = true;
				break;
			case VK_SPACE:
				break;
			default:
				break;
			}
		}
		while(kb.dwKeyPressed != VK_SPACE && kb.dwKeyPressed != 'G');
	}
	ResultsScrn();
}

void Options()
{
	char LeftA = (char)60, RightA = (char)62, Curs = (char)29;
	ClrScrn;
	DrawBox(SM_LEFT, SM_TOP, SM_WIDTH, SM_HEIGHT, '*', Red_I);
	Text(SM_LEFT+6, SM_TOP+1, "Settings", Green_I);
	Text(SM_LEFT+6, SM_TOP+3, "Game Speed", Teal_I);
	Text(SM_LEFT+22, SM_TOP+3, gv.GameSpeed);
	Text(SM_LEFT+6, SM_TOP+5, "Start Position", Teal_I);

	int speed = gv.GameSpeed, start = gv.StartPos, match = gv.MatchSize;
	if(gv.StartPos == 1)
		Text(SM_LEFT+22, SM_TOP+5, "Top");
	else
		Text(SM_LEFT+22, SM_TOP+5, "Bottom");

	Text(SM_LEFT+6, SM_TOP+7, "Match Size", Teal_I);
	Text(SM_LEFT+22, SM_TOP+7, match);
	Text(SM_LEFT+6, SM_TOP+9, "Done", Teal_I);

	for(int y=SM_TOP+3; y<SM_TOP+9; y+=2)
	{
		Text_char(SM_LEFT+2, y, LeftA, Green);
		Text_char(SM_LEFT+4, y, RightA, Green);
	}
	Text_char(SM_LEFT+3, SM_TOP+3, Curs, Green_I);
	SetCursorPosition(0,0);

	int Y = SM_TOP+3;
	int X = SM_LEFT+3;
	int Choice = 1;

	while(1)
	{
		GetKeyboardInput(REPEAT);

		switch(kb.dwKeyPressed)
		{
		case VK_UP:
			if(Y > SM_TOP+3)
			{
				Text_char(X, Y, ' ', Green_I);
				Y -= 2;
				Choice--;
				Text_char(X, Y, Curs, Green_I);
				SetCursorPosition(0,0);
			}
			break;
		case VK_DOWN:
			if(Y < SM_TOP+9)
			{
				Text_char(X, Y, ' ', Green_I);
				Y += 2;
				Choice++;
				Text_char(X, Y, Curs, Green_I);
				SetCursorPosition(0,0);
			}
			break;
		case VK_RIGHT:
			if(Y == SM_TOP+9)
				break;
			Text_char(X+1, Y, RightA, Green_I);
			SetCursorPosition(0,0);

			if(Y == SM_TOP+3 && speed < 110)
			{
				Text(SM_LEFT+22, SM_TOP+3, speed+=10);
			}
			if(Y == SM_TOP+5)
			{
				if(start)
				{
					start = 0;
					Text(SM_LEFT+22, SM_TOP+5, "Bottom");
				}
				else
				{

					start = 1 ;
					Text(SM_LEFT+22, SM_TOP+5, "Top   ");
				}
			}
			if(Y == SM_TOP+7 && match < 15)
			{
				Text(SM_LEFT+22, SM_TOP+7, ++(++match));
			}

			WaitForKeyRelease();

			Text_char(X+1, Y, RightA, Green);
			SetCursorPosition(0,0);
			break;
		case VK_LEFT:
			if(Y == SM_TOP+9)
				break;
			Text_char(X-1, Y, LeftA, Green_I);
			SetCursorPosition(0,0);

			if(Y == SM_TOP+3 && speed > 30)
			{
				Text_char(SM_LEFT+24, SM_TOP+3, ' ');
				Text(SM_LEFT+22, SM_TOP+3, speed-=10);
			}
			if(Y == SM_TOP+5)
			{
				if(!start)
				{
					start = 1 ;
					Text(SM_LEFT+22, SM_TOP+5, "Top   ");
				}
				else
				{
					start = 0;
					Text(SM_LEFT+22, SM_TOP+5, "Bottom");
				}
			}
			if(Y == SM_TOP+7 && match > 1)
			{
				Text_char(SM_LEFT+23, SM_TOP+7, ' ');
				Text(SM_LEFT+22, SM_TOP+7, --(--match));
			}

			WaitForKeyRelease();

			Text_char(X-1, Y, LeftA, Green);
			SetCursorPosition(0,0);
			break;
		default:
			break;
		}
		if(Y == SM_TOP+9 && kb.dwKeyPressed == VK_RETURN)
			break;
	}
	UpdateGameFile(speed, start, match);

	gv.GameSpeed = speed;
	gv.StartPos = start;
	gv.MatchSize = match;

	// For the menu change
	WaitForKeyRelease();
}

void MainMenu()
{
	bool done = false;
	while(!done)
	{
		ClrScrn;
		DrawBox(MM_LEFT, MM_TOP, MM_WIDTH, MM_HEIGHT, '*', Blue_I);
		Text(MM_LEFT+7, MM_TOP+1, "Tron", Green_I);
		Text(MM_LEFT+2, MM_TOP+3, "[ ] Play Game", Teal_I);
		Text(MM_LEFT+2, MM_TOP+5, "[ ] Settings", Teal_I);
		Text(MM_LEFT+2, MM_TOP+7, "[ ] Exit", Teal_I);
		Text_char(MM_LEFT+3, MM_TOP+3, (char)4, Green_I);
		Text(SCREEN_XMAX-5, SCREEN_YMAX, "v.1.02", Red);
		SetCursorPosition(0,0);

		int Y = MM_TOP+3;
		int Choice = 1;
		do{
			GetKeyboardInput(REPEAT);

			switch(kb.dwKeyPressed)
			{
			case VK_RETURN:
				break;
			case VK_UP:
				if(Y > MM_TOP+3)
				{
					Text_char(MM_LEFT+3, Y, ' ', Green_I);
					Y -= 2;
					Choice--;
					Text_char(MM_LEFT+3, Y, (char)4, Green_I);
					SetCursorPosition(0,0);
				}
				break;
			case VK_DOWN:
				if(Y < MM_TOP+7)
				{
					Text_char(MM_LEFT+3, Y, ' ', Green_I);
					Y += 2;
					Choice++;
					Text_char(MM_LEFT+3, Y, (char)4, Green_I);
					SetCursorPosition(0,0);
				}
				break;
			default:
				break;
			}
		}while(kb.dwKeyPressed != VK_RETURN);
		
		WaitForKeyRelease();

		switch(Choice)
		{
		case 1:
			Play();
			break;
		case 2:
			Options();
			break;
		case 3:
			done = true;
			break;
		default:	// impossible event
			break;
		}
	}
}

// Game speed
// Start position		1 = top, 0 = bottom
// Matchsize
// 
bool LoadGameFile()
{
	ifstream LF;
	LF.open("Settings.dsf", ios::in);

	if(LF.fail())
	{
		cout<<"\n\nSettings.dsf cannot be found.\nPress space to continue.";
		KB_WAIT(VK_SPACE);

		return false;
	}

	LF>>gv.GameSpeed;
	LF>>gv.StartPos;
	LF>>gv.MatchSize;

	LF.close();
	return true;
}

void UpdateGameFile(int speed, int start, int match)
{
	ofstream LF;
	LF.open("Settings.dsf", ios::out);

	LF<<speed <<endl <<start <<endl <<match;

	LF.close();
}

bool CreateGameFile()
{
	ofstream LF;
	LF.open("Settings.dsf", ios::out);
	if(LF.fail())
		return false;

	LF<<60 <<endl <<0 <<endl <<3;

	LF.close();

	gv.GameSpeed = 60;
	gv.StartPos = 0;
	gv.MatchSize = 3;
	return true;
}

void main()
{
	if(!LoadGameFile())
	{
		if(!CreateGameFile())
			return;
	}
	Matrix = new int[SCREEN_WIDTH * SCREEN_HEIGHT];
	Opening();
	MainMenu();
	ClrScrn;
	// Exit whatever...
	delete[] Matrix;
}
