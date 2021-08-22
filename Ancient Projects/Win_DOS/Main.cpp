#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <conio.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

#include <My Header Files\_MJCF_ConGLob.h>
#include <My Header Files\_MJCF_Output.h>
#include <My Header Files\_MJCF_Mouse.h>
#include <My Header Files\_MJCF_Keyboard.h>

#include "Win_DOS_DataStructures.h"
#include "Win_DOS_Graphics.h"
#include "Win_DOS_System.h"

void Shutdown();

void LoadWindows()
{
	cout<<"Maximize this DOS console by pushing Alt-Enter\n\n";
	cout<<"Then press the space bar to continue loading Win-DOS.";

	KB_WAIT(VK_SPACE);

	ConsoleSetup(ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	LoadGraphics();
	DrawObject("CLEARSCRN");
}

void main()
{
	LoadWindows();

	while(!SysMan.Shutdown)
	{
		DrawScrn();
		Text(79,49,"", Blue);

		GetMouseInput();

		ProcessClick();

		Text(0, 0, Mouse.X);
		Text(0, 1, Mouse.Y);
	}
	Shutdown();
}

void Shutdown()
{
	DrawObject("CLEARSCRN");
}