#ifndef _MJCF_OUTPUT_
#define _MJCF_OUTPUT_

/////////////////////////////////////////
///
///		Created:		Micah Fullerton
///		Modified:		Micah Fullerton
///		Date Modified:	9/12/04
///		Requirements:	iostream, windows.h, string, std::cout, std::string
///
/////////////////////////////////////////

#define ClrScrn		WriteConsoleOutput(hOutput,(*&cs.p_GFX),cs._SIZE,SCRNST,&cs._EDGES);

#define Black		0x0000
#define Red			FOREGROUND_RED
#define Green		FOREGROUND_GREEN
#define Blue		FOREGROUND_BLUE
#define Red_I		FOREGROUND_RED | FOREGROUND_INTENSITY
#define Green_I		FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define Blue_I		FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define White		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define White_I		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define Yellow		FOREGROUND_RED | FOREGROUND_GREEN
#define Yellow_I	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define Purple		FOREGROUND_RED | FOREGROUND_BLUE
#define Purple_I	FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define Teal		FOREGROUND_GREEN | FOREGROUND_BLUE
#define Teal_I		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY

#define B_Black		0x0000
#define B_Red		BACKGROUND_RED
#define B_Green		BACKGROUND_GREEN
#define B_Blue		BACKGROUND_BLUE
#define B_Red_I		BACKGROUND_RED | BACKGROUND_INTENSITY
#define B_Green_I	BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define B_Blue_I	BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define B_White		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
#define B_White_I	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define B_Yellow	BACKGROUND_RED | BACKGROUND_GREEN
#define B_Yellow_I	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define B_Purple	BACKGROUND_RED | BACKGROUND_BLUE
#define B_Purple_I	BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define B_Teal		BACKGROUND_GREEN | BACKGROUND_BLUE
#define B_Teal_I	BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY

COORD txtPosition;

void SetCursorPosition(int X, int Y)
{
	txtPosition.X = X;
	txtPosition.Y = Y;
	SetConsoleCursorPosition(hOutput, txtPosition);
}

void AdvanceCursor(int nChars)
{
	GetConsoleCursorInfo(hOutput, &CursorInfo);
	txtPosition.X = ConsoleInfo.dwCursorPosition.X;
	txtPosition.Y = ConsoleInfo.dwCursorPosition.Y;

	for(int n = 0; n<nChars; n++)
	{
		txtPosition.X++;
		if(txtPosition.X == SCREEN_XMAX)
		{
			txtPosition.X = 0;
			txtPosition.Y++;
		}
	}
	SetConsoleCursorPosition(hOutput, txtPosition);
}

void Text(int X, int Y, string Text, WORD color = White)
{
	txtPosition.X = X;
	txtPosition.Y = Y;

	SetConsoleTextAttribute(hOutput, color);
	SetConsoleCursorPosition(hOutput, txtPosition);

	cout<<Text;

	/* Changes the text color back the the default white */
	SetConsoleTextAttribute(hOutput, White);
	/* Keeps the cursor from moving to the end of the outputed text */
	SetConsoleCursorPosition(hOutput, txtPosition);
}

void Text(int X, int Y, int nValue, WORD color = White)
{
	txtPosition.X = X;
	txtPosition.Y = Y;

	SetConsoleTextAttribute(hOutput, color);
	SetConsoleCursorPosition(hOutput, txtPosition);

	cout<<nValue;

	/* Changes the text color back the the default white */
	SetConsoleTextAttribute(hOutput, White);
	/* Keeps the cursor from moving to the end of the outputed value */
	SetConsoleCursorPosition(hOutput, txtPosition);
}

void Text_char(int X, int Y, char cChar, WORD color = White)
{
	txtPosition.X = X;
	txtPosition.Y = Y;

	SetConsoleTextAttribute(hOutput, color);
	SetConsoleCursorPosition(hOutput, txtPosition);

	cout<<cChar;

	/* Changes the text color back the the default white */
	SetConsoleTextAttribute(hOutput, White);
	/* Keeps the cursor from moving one to the right after the outputed character */
	SetConsoleCursorPosition(hOutput, txtPosition);
}

#define ScreenSize 0,0,	SCREEN_WIDTH, SCREEN_HEIGHT
#define _ScreenSize 1,1, SCREEN_XMAX-1, SCREEN_YMAX-1

void DrawBox(int xStart, int yStart, int xLength, int yLength, char Border, WORD Color = White)
{
	int n;
	for(n=xStart; n<xStart+xLength; n++)
	{
		Text_char(n, yStart, Border, Color);
		Text_char(n, yStart+yLength-1, Border, Color);
	}
	for(n=yStart+1; n<yStart+yLength-1; n++)
	{
		Text_char(xStart, n, Border, Color);
		Text_char(xStart+xLength-1, n, Border, Color);
	}
}

#endif