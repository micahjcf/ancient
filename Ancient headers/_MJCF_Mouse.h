#ifndef _MJCF_MOUSE_
#define _MJCF_MOUSE_

/*
// Needed include files/namespaces
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
using namespace std;
*/

struct MOUSE
{ 
	SHORT X;
	SHORT Y;
	bool bLeftClicked;
	bool bRightClicked;
}; MOUSE Mouse = {0,0,false,false};

void GetMouseInput()
{
	do{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
	}while(InputRecord.Event.MouseEvent.dwButtonState);

	while(!InputRecord.Event.MouseEvent.dwButtonState)
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
	}

	FlushConsoleInputBuffer(hInput);

	if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		Mouse.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
		Mouse.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
		Mouse.bLeftClicked = true;
		Mouse.bRightClicked = false;
	}
	if(InputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
	{
		Mouse.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
		Mouse.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
		Mouse.bLeftClicked = false;
		Mouse.bRightClicked = true;
	}
}

#endif