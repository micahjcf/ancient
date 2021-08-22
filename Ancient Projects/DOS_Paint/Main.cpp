#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <conio.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

#include <My Header Files\_MJCF_ConGlob.h>
#include <My Header Files\_MJCF_Output.h>
#include <My Header Files\_MJCF_Mouse.h>
#include <My Header Files\_MJCF_Keyboard.h>

#include "Data Structures.h"
#include "Graphics.h"
#include "System.h"

void Welcome_Load()
{
	cout<<"Maximize this DOS console by pushing Alt-Enter\n\n";
	cout<<"Then press the space bar to continue.";

	KB_WAIT(VK_SPACE);

	LoadGraphics();
	DrawObject("CLEARSCRN");
}

void GoodBye()
{
	Text(0,0,"");
	DrawObject("CLEARSCRN");
}

void main()
{
	Welcome_Load();
	//system("CLS");

	while(!SysMan.done)
	{
		DrawScrn();
		Text(79,49,"");

		GetMouseInput();
		ProcessMouseInput();

		Text(78, 0, "  ", Blue_I | B_Blue);
		Text(78, 1, "  ", Blue_I | B_Blue);
		Text(78,0,Mouse.X, White_I | B_Blue);
		Text(78,1,Mouse.Y, White_I | B_Blue);
	}
	GoodBye();
}