#ifndef _GRAPHICS_
#define _GRAPHICS_

#define TOOLBAR_WIDTH		80
#define TOOLBAR_HEIGHT		2
#define TOOLBAR_X			0
#define TOOLBAR_Y			0

#define FILEMENU_WIDTH		12
#define FILEMENU_HEIGHT		11
#define FILEMENU_X			0
#define FILEMENU_Y			2

#define EDITMENU_WIDTH		12
#define EDITMENU_HEIGHT		11
#define EDITMENU_X			8
#define EDITMENU_Y			2

#define TOOLMENU_WIDTH		12
#define TOOLMENU_HEIGHT		11
#define TOOLMENU_X			16
#define TOOLMENU_Y			2

#define COLORMENU_WIDTH		11
#define COLORMENU_HEIGHT	29
#define COLORMENU_X			25
#define COLORMENU_Y			2

#define MSGBOARD_WIDTH		80
#define MSGBOARD_HEIGHT		3
#define MSGBOARD_X			0
#define MSGBOARD_Y			47

#define CL_MSGBOARD_WIDTH	80
#define CL_MSGBOARD_HEIGHT	1
#define CL_MSGBOARD_X		0
#define CL_MSGBOARD_Y		48

//#define FIELD_WIDTH			80
//#define FIELD_HEIGHT		45
#define FIELD_X				0
#define FIELD_Y				2

COORD FIELDST = {0,2};

CHAR_INFO CLEARSCRN_GFX[80 * 50];
SMALL_RECT CLEARSCRN_EDGES = {0,0,79,49};
COORD CLEARSCRN_SIZE = {SCREEN_WIDTH, SCREEN_HEIGHT};

CHAR_INFO TOOLBAR_GFX[TOOLBAR_WIDTH * TOOLBAR_HEIGHT];
SMALL_RECT TOOLBAR_EDGES = {TOOLBAR_X,TOOLBAR_Y,TOOLBAR_X+(TOOLBAR_WIDTH-1),TOOLBAR_Y+(TOOLBAR_HEIGHT-1)};
COORD TOOLBAR_SIZE = {TOOLBAR_WIDTH, TOOLBAR_HEIGHT};

CHAR_INFO FILEMENU_GFX[FILEMENU_WIDTH * FILEMENU_HEIGHT];
SMALL_RECT FILEMENU_EDGES = {FILEMENU_X,FILEMENU_Y,FILEMENU_X+(FILEMENU_WIDTH-1),FILEMENU_Y+(FILEMENU_HEIGHT-1)};
COORD FILEMENU_SIZE = {FILEMENU_WIDTH, FILEMENU_HEIGHT};

CHAR_INFO SH_FILEMENU_GFX[FILEMENU_WIDTH * FILEMENU_HEIGHT];

CHAR_INFO EDITMENU_GFX[EDITMENU_WIDTH * EDITMENU_HEIGHT];
SMALL_RECT EDITMENU_EDGES = {EDITMENU_X,EDITMENU_Y,EDITMENU_X+(EDITMENU_WIDTH-1),EDITMENU_Y+(EDITMENU_HEIGHT-1)};
COORD EDITMENU_SIZE = {EDITMENU_WIDTH, EDITMENU_HEIGHT};

CHAR_INFO SH_EDITMENU_GFX[EDITMENU_WIDTH * EDITMENU_HEIGHT];

CHAR_INFO TOOLMENU_GFX[TOOLMENU_WIDTH * TOOLMENU_HEIGHT];
SMALL_RECT TOOLMENU_EDGES = {TOOLMENU_X,TOOLMENU_Y,TOOLMENU_X+(TOOLMENU_WIDTH-1),TOOLMENU_Y+(TOOLMENU_HEIGHT-1)};
COORD TOOLMENU_SIZE = {TOOLMENU_WIDTH, TOOLMENU_HEIGHT};

CHAR_INFO SH_TOOLMENU_GFX[TOOLMENU_WIDTH * TOOLMENU_HEIGHT];

CHAR_INFO COLORMENU_GFX[COLORMENU_WIDTH * COLORMENU_HEIGHT];
SMALL_RECT COLORMENU_EDGES = {COLORMENU_X,COLORMENU_Y,COLORMENU_X+(COLORMENU_WIDTH-1),COLORMENU_Y+(COLORMENU_HEIGHT-1)};
COORD COLORMENU_SIZE = {COLORMENU_WIDTH, COLORMENU_HEIGHT};

CHAR_INFO SH_COLORMENU_GFX[COLORMENU_WIDTH * COLORMENU_HEIGHT];

CHAR_INFO MSGBOARD_GFX[MSGBOARD_WIDTH * MSGBOARD_HEIGHT];
SMALL_RECT MSGBOARD_EDGES = {MSGBOARD_X,MSGBOARD_Y,MSGBOARD_X+(MSGBOARD_WIDTH-1),MSGBOARD_Y+(MSGBOARD_HEIGHT-1)};
COORD MSGBOARD_SIZE = {MSGBOARD_WIDTH, MSGBOARD_HEIGHT};

CHAR_INFO CL_MSGBOARD_GFX[CL_MSGBOARD_WIDTH * CL_MSGBOARD_HEIGHT];
SMALL_RECT CL_MSGBOARD_EDGES = {CL_MSGBOARD_X,CL_MSGBOARD_Y,CL_MSGBOARD_X+(CL_MSGBOARD_WIDTH-1),CL_MSGBOARD_Y+(CL_MSGBOARD_HEIGHT-1)};
COORD CL_MSGBOARD_SIZE = {CL_MSGBOARD_WIDTH, CL_MSGBOARD_HEIGHT};

CHAR_INFO FIELD_GFX[FIELD_WIDTH * FIELD_HEIGHT];
SMALL_RECT FIELD_EDGES = {FIELD_X,FIELD_Y,FIELD_X+(FIELD_WIDTH-1),FIELD_Y+(FIELD_HEIGHT-1)};
COORD FIELD_SIZE = {FIELD_WIDTH, FIELD_HEIGHT};

void LoadGraphics()
{
	int x,y;
	// Clear Screen
	for(y = 0; y < CLEARSCRN_SIZE.Y; y++)
	{
		for(x = 0; x < CLEARSCRN_SIZE.X; x++)
		{
			CLEARSCRN_GFX[x + y * SCREEN_WIDTH].Char.AsciiChar = ' ';
			CLEARSCRN_GFX[x + y * SCREEN_WIDTH].Attributes = White_I;
		}
	}
	// Tool Bar
	for(y = 0; y < TOOLBAR_SIZE.Y; y++)
	{
		for(x = 0; x < TOOLBAR_SIZE.X; x++)
		{
			TOOLBAR_GFX[x + y * TOOLBAR_WIDTH].Char.AsciiChar = ' ';
			TOOLBAR_GFX[x + y * TOOLBAR_WIDTH].Attributes = White_I | B_Blue;
		}
	}
	// File Menu
	for(y = 0; y < FILEMENU_SIZE.Y; y++)
	{
		for(x = 0; x < FILEMENU_SIZE.X; x++)
		{
			FILEMENU_GFX[x + y * FILEMENU_WIDTH].Char.AsciiChar = ' ';
			FILEMENU_GFX[x + y * FILEMENU_WIDTH].Attributes = B_Blue | White_I;
		}
	}
	for(y = 0; y < FILEMENU_SIZE.Y; y+=2)
	{
		for(x = 0; x < FILEMENU_SIZE.X; x++)
		{
			FILEMENU_GFX[x + y * FILEMENU_WIDTH].Char.AsciiChar = '-';
			FILEMENU_GFX[x + y * FILEMENU_WIDTH].Attributes = B_Blue | Teal;
		}
	}
	// Edit Menu
	for(y = 0; y < EDITMENU_SIZE.Y; y++)
	{
		for(x = 0; x < EDITMENU_SIZE.X; x++)
		{
			EDITMENU_GFX[x + y * EDITMENU_WIDTH].Char.AsciiChar = ' ';
			EDITMENU_GFX[x + y * EDITMENU_WIDTH].Attributes = B_Blue | White_I;
		}
	}
	for(y = 0; y < EDITMENU_SIZE.Y; y+=2)
	{
		for(x = 0; x < EDITMENU_SIZE.X; x++)
		{
			EDITMENU_GFX[x + y * EDITMENU_WIDTH].Char.AsciiChar = '-';
			EDITMENU_GFX[x + y * EDITMENU_WIDTH].Attributes = B_Blue | Teal;
		}
	}
	// Tool Menu
	for(y = 0; y < TOOLMENU_SIZE.Y; y++)
	{
		for(x = 0; x < TOOLMENU_SIZE.X; x++)
		{
			TOOLMENU_GFX[x + y * TOOLMENU_WIDTH].Char.AsciiChar = ' ';
			TOOLMENU_GFX[x + y * TOOLMENU_WIDTH].Attributes = B_Blue | White_I;
		}
	}
	for(y = 0; y < TOOLMENU_SIZE.Y; y+=2)
	{
		for(x = 0; x < TOOLMENU_SIZE.X; x++)
		{
			TOOLMENU_GFX[x + y * TOOLMENU_WIDTH].Char.AsciiChar = '-';
			TOOLMENU_GFX[x + y * TOOLMENU_WIDTH].Attributes = B_Blue | Teal;
		}
	}
	// Color Menu
	for(y = 0; y < COLORMENU_SIZE.Y; y++)
	{
		for(x = 0; x < COLORMENU_SIZE.X; x++)
		{
			COLORMENU_GFX[x + y * COLORMENU_WIDTH].Char.AsciiChar = ' ';
			COLORMENU_GFX[x + y * COLORMENU_WIDTH].Attributes = B_Blue | White_I;
		}
	}
	for(y = 0; y < COLORMENU_SIZE.Y; y+=2)
	{
		for(x = 0; x < COLORMENU_SIZE.X; x++)
		{
			COLORMENU_GFX[x + y * COLORMENU_WIDTH].Char.AsciiChar = '-';
			COLORMENU_GFX[x + y * COLORMENU_WIDTH].Attributes = B_Blue | Teal;
		}
	}
	// Message Board
	for(y = 0; y < MSGBOARD_SIZE.Y; y++)
	{
		for(x = 0; x < MSGBOARD_SIZE.X; x++)
		{
			MSGBOARD_GFX[x + y * MSGBOARD_WIDTH].Char.AsciiChar = '-';
			MSGBOARD_GFX[x + y * MSGBOARD_WIDTH].Attributes = Teal;
		}
	}
	// Clear Message Board
	for(y = 0; y < CL_MSGBOARD_SIZE.Y; y++)
	{
		for(x = 0; x < CL_MSGBOARD_SIZE.X; x++)
		{
			CL_MSGBOARD_GFX[x + y * CL_MSGBOARD_WIDTH].Char.AsciiChar = ' ';
			CL_MSGBOARD_GFX[x + y * CL_MSGBOARD_WIDTH].Attributes = White_I;
		}
	}
//*******************SHADOWS***
	// File Menu
	for(y = 0; y < FILEMENU_SIZE.Y; y++)
	{
		for(x = 0; x < FILEMENU_SIZE.X; x++)
		{
			SH_FILEMENU_GFX[x + y * FILEMENU_WIDTH].Char.AsciiChar = ' ';
			SH_FILEMENU_GFX[x + y * FILEMENU_WIDTH].Attributes = White_I;
		}
	}
	// Edit Menu
	for(y = 0; y < EDITMENU_SIZE.Y; y++)
	{
		for(x = 0; x < EDITMENU_SIZE.X; x++)
		{
			SH_EDITMENU_GFX[x + y * EDITMENU_WIDTH].Char.AsciiChar = ' ';
			SH_EDITMENU_GFX[x + y * EDITMENU_WIDTH].Attributes = White_I;
		}
	}
	// Tool Menu
	for(y = 0; y < TOOLMENU_SIZE.Y; y++)
	{
		for(x = 0; x < TOOLMENU_SIZE.X; x++)
		{
			SH_TOOLMENU_GFX[x + y * TOOLMENU_WIDTH].Char.AsciiChar = ' ';
			SH_TOOLMENU_GFX[x + y * TOOLMENU_WIDTH].Attributes = White_I;
		}
	}
	// Color Menu
	for(y = 0; y < COLORMENU_SIZE.Y; y++)
	{
		for(x = 0; x < COLORMENU_SIZE.X; x++)
		{
			SH_COLORMENU_GFX[x + y * COLORMENU_WIDTH].Char.AsciiChar = ' ';
			SH_COLORMENU_GFX[x + y * COLORMENU_WIDTH].Attributes = White_I;
		}
	}
}

void DrawObject(string Object)
{
	if(Object == "CLEARSCRN")
	{
		ClrScrn;
	}
	if(Object == "TOOLBAR")
	{
		WriteConsoleOutput(hOutput, TOOLBAR_GFX, TOOLBAR_SIZE, SCRNST, &TOOLBAR_EDGES);

		// Menu
		Text(1,0," File ", B_Blue_I | White_I);
		Text(9,0," Edit ", B_Blue_I | White_I);
		Text(17,0," Tools ", B_Blue_I | White_I);
		Text(26,0," Colors ", B_Blue_I | White_I);

		SysMan.DrawFlag.DrawScrn = false;
	}
	if(Object == "FILEMENU")
	{
		WriteConsoleOutput(hOutput, FILEMENU_GFX, FILEMENU_SIZE, SCRNST, &FILEMENU_EDGES);
		Text(1, 3, "New", Teal_I | B_Blue);
		Text(1, 5, "Open", Teal_I | B_Blue);
		Text(1, 7, "Save", Teal_I | B_Blue);
		Text(1, 9, "Save As...", Teal_I | B_Blue);
		Text(1, 11, "Exit", Teal_I | B_Blue);

		SysMan.MenuUp = true;
		SysMan.DrawFlag.DrawFileMenu = false;
		SysMan.DrawStat.FileMenuUp = true;
	}
	if(Object == "FILEMENU_SHADOW")
	{
		WriteConsoleOutput(hOutput, SH_FILEMENU_GFX, FILEMENU_SIZE, SCRNST, &FILEMENU_EDGES);
		SysMan.DrawStat.FileMenuUp = false;
		SysMan.MenuUp = false;
	}
	if(Object == "EDITMENU")
	{
		WriteConsoleOutput(hOutput, EDITMENU_GFX, EDITMENU_SIZE, SCRNST, &EDITMENU_EDGES);
		Text(9, 3, "Clear Pic", Teal_I | B_Blue);
		Text(9, 5, "?", Teal_I | B_Blue);
		Text(9, 7, "?", Teal_I | B_Blue);
		Text(9, 9, "?", Teal_I | B_Blue);
		Text(9, 11, "?", Teal_I | B_Blue);

		SysMan.MenuUp = true;
		SysMan.DrawFlag.DrawEditMenu = false;
		SysMan.DrawStat.EditMenuUp = true;
	}
	if(Object == "EDITMENU_SHADOW")
	{
		WriteConsoleOutput(hOutput, SH_EDITMENU_GFX, EDITMENU_SIZE, SCRNST, &EDITMENU_EDGES);
		SysMan.DrawStat.EditMenuUp = false;
		SysMan.MenuUp = false;
	}
	if(Object == "TOOLMENU")
	{
		WriteConsoleOutput(hOutput, TOOLMENU_GFX, TOOLMENU_SIZE, SCRNST, &TOOLMENU_EDGES);
		Text(17, 3, "Clear Pic", Teal_I | B_Blue);
		Text(17, 5, "?", Teal_I | B_Blue);
		Text(17, 7, "?", Teal_I | B_Blue);
		Text(17, 9, "?", Teal_I | B_Blue);
		Text(17, 11, "?", Teal_I | B_Blue);

		SysMan.MenuUp = true;
		SysMan.DrawFlag.DrawToolMenu = false;
		SysMan.DrawStat.ToolMenuUp = true;
	}
	if(Object == "TOOLMENU_SHADOW")
	{
		WriteConsoleOutput(hOutput, SH_TOOLMENU_GFX, TOOLMENU_SIZE, SCRNST, &TOOLMENU_EDGES);
		SysMan.DrawStat.ToolMenuUp = false;
		SysMan.MenuUp = false;
	}
	if(Object == "COLORMENU")
	{
		WriteConsoleOutput(hOutput, COLORMENU_GFX, COLORMENU_SIZE, SCRNST, &COLORMENU_EDGES);
		Text(26, 3,  " ", White_I | B_Red_I);
		Text(26, 5,  " ", White_I | B_Red);
		Text(26, 7,  " ", White_I | B_Green_I);
		Text(26, 9,  " ", White_I | B_Green);
		Text(26, 11, " ", White_I | B_Blue_I);
		Text(26, 13, " ", White_I | B_Blue);
		Text(26, 15, " ", White_I | B_Yellow_I);
		Text(26, 17, " ", White_I | B_Yellow);
		Text(26, 19, " ", White_I | B_Purple_I);
		Text(26, 21, " ", White_I | B_Purple);
		Text(26, 23, " ", White_I | B_Teal_I);
		Text(26, 25, " ", White_I | B_Teal);
		Text(26, 27, " ", White_I | B_White);
		Text(26, 29, " ", White_I | B_White_I);

		Text(28, 3, "L. Red", B_Blue | Teal_I);
		Text(28, 5, "D. Red", B_Blue | Teal_I);
		Text(28, 7, "L. Green", B_Blue | Teal_I);
		Text(28, 9, "D. Green", B_Blue | Teal_I);
		Text(28, 11,"L. Blue", B_Blue | Teal_I);
		Text(28, 13,"D. Blue", B_Blue | Teal_I);
		Text(28, 15,"Yellow", B_Blue | Teal_I);
		Text(28, 17,"Gold", B_Blue | Teal_I);
		Text(28, 19,"Pink", B_Blue | Teal_I);
		Text(28, 21,"Purple", B_Blue | Teal_I);
		Text(28, 23,"L. Teal", B_Blue | Teal_I);
		Text(28, 25,"D. Teal", B_Blue | Teal_I);
		Text(28, 27,"Grey", B_Blue | Teal_I);
		Text(28, 29,"White", B_Blue | Teal_I);

		SysMan.MenuUp = true;
		SysMan.DrawFlag.DrawColorMenu = false;
		SysMan.DrawStat.ColorMenuUp = true;
	}
	if(Object == "COLORMENU_SHADOW")
	{
		WriteConsoleOutput(hOutput, SH_COLORMENU_GFX, COLORMENU_SIZE, SCRNST, &COLORMENU_EDGES);
		SysMan.DrawStat.ColorMenuUp = false;
		SysMan.MenuUp = false;
	}
	if(Object == "MSGBOARD")
	{
		WriteConsoleOutput(hOutput, MSGBOARD_GFX, MSGBOARD_SIZE, SCRNST, &MSGBOARD_EDGES);
		WriteConsoleOutput(hOutput, CL_MSGBOARD_GFX, CL_MSGBOARD_SIZE, SCRNST, &CL_MSGBOARD_EDGES);
	}
	if(Object == "CLEARMSGBOARD")
	{
		WriteConsoleOutput(hOutput, CL_MSGBOARD_GFX, CL_MSGBOARD_SIZE, SCRNST, &CL_MSGBOARD_EDGES);
	}
}

void Draw()
{
	Text(Mouse.X, Mouse.Y, " ", SysMan.Tool.SelectedCharColor | White_I);
}

#endif