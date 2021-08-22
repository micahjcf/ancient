#ifndef _WD_GRAPHICS_
#define _WD_GRAPHICS_

#define TASKBAR_WIDTH		80
#define TASKBAR_HEIGHT		2
#define TASKBAR_X			0
#define TASKBAR_Y			48

#define STARTMENU_WIDTH		16
#define STARTMENU_HEIGHT	30
#define STARTMENU_X			0
#define STARTMENU_Y			18

#define RIGHTCLICKMENU_WIDTH		12
#define RIGHTCLICKMENU_HEIGHT		11

CHAR_INFO TASKBAR_GFX[TASKBAR_WIDTH * TASKBAR_HEIGHT];
SMALL_RECT TASKBAR_EDGES = {TASKBAR_X,TASKBAR_Y,TASKBAR_X+(TASKBAR_WIDTH-1),TASKBAR_Y+(TASKBAR_HEIGHT-1)};
COORD TASKBAR_SIZE = {TASKBAR_WIDTH , TASKBAR_HEIGHT};

CHAR_INFO STARTMENU_GFX[STARTMENU_WIDTH * STARTMENU_HEIGHT];
SMALL_RECT STARTMENU_EDGES = {STARTMENU_X,STARTMENU_Y,STARTMENU_X+(STARTMENU_WIDTH-1),STARTMENU_Y+(STARTMENU_HEIGHT-1)};
COORD STARTMENU_SIZE = {STARTMENU_WIDTH , STARTMENU_HEIGHT};

CHAR_INFO SH_STARTMENU_GFX[STARTMENU_WIDTH * STARTMENU_HEIGHT];

CHAR_INFO RIGHTCLICKMENU_GFX[RIGHTCLICKMENU_WIDTH * RIGHTCLICKMENU_HEIGHT];
SMALL_RECT RIGHTCLICKMENU_EDGES;
COORD RIGHTCLICKMENU_SIZE = {RIGHTCLICKMENU_WIDTH , RIGHTCLICKMENU_HEIGHT};

CHAR_INFO SH_RIGHTCLICKMENU_GFX[RIGHTCLICKMENU_WIDTH * RIGHTCLICKMENU_HEIGHT];

void LoadGraphics()
{
	int x,y;
//********************Taskbar***
	char Taskbar[8] = " Start ";
	for(y = 0; y < TASKBAR_SIZE.Y; y++)
	{
		for(x = 0; x < TASKBAR_SIZE.X; x++)
		{
			TASKBAR_GFX[x + y * TASKBAR_WIDTH].Char.AsciiChar = ' ';
			TASKBAR_GFX[x + y * TASKBAR_WIDTH].Attributes = B_Blue_I | White_I;
		}
	}
	for(y = 0; y < TASKBAR_SIZE.Y; y++)
	{
		for(x = 0; x < 7; x++)
		{
			TASKBAR_GFX[x + y * TASKBAR_WIDTH].Char.AsciiChar = ' ';
			TASKBAR_GFX[x + y * TASKBAR_WIDTH].Attributes = B_Green_I | White_I;
		}
	}
	for(x = 0; x < 7; x++)
	{
		TASKBAR_GFX[x + 1 * TASKBAR_WIDTH].Char.AsciiChar = Taskbar[x];
		TASKBAR_GFX[x + 1 * TASKBAR_WIDTH].Attributes = B_Green_I | White_I;
	}
//********************StartMenu***
	for(y = 0; y < STARTMENU_SIZE.Y; y++)
	{
		for(x = 0; x < STARTMENU_SIZE.X; x++)
		{
			STARTMENU_GFX[x + y * STARTMENU_WIDTH].Char.AsciiChar = ' ';
			STARTMENU_GFX[x + y * STARTMENU_WIDTH].Attributes = B_Blue | Blue_I;
		}
	}
	for(y = 2; y < STARTMENU_SIZE.Y; y+=4)
	{
		for(x = 0; x < STARTMENU_SIZE.X; x++)
		{
			STARTMENU_GFX[x + y * STARTMENU_WIDTH].Char.AsciiChar = '-';
			STARTMENU_GFX[x + y * STARTMENU_WIDTH].Attributes = B_Blue | Blue_I;
		}
	}
	for(y = 0; y < STARTMENU_SIZE.Y; y++)
	{
		for(x = 0; x < STARTMENU_SIZE.X; x+=15)
		{
			STARTMENU_GFX[x + y * STARTMENU_WIDTH].Char.AsciiChar = '|';
			STARTMENU_GFX[x + y * STARTMENU_WIDTH].Attributes = B_Blue | Blue_I;
		}
	}
	for(x = 0; x < STARTMENU_SIZE.X; x++)
	{
		STARTMENU_GFX[x + 0 * STARTMENU_WIDTH].Char.AsciiChar = '=';
		STARTMENU_GFX[x + 0 * STARTMENU_WIDTH].Attributes = B_Blue | Blue_I;
	}
//********************Right Click Menu***
	for(y = 0; y < RIGHTCLICKMENU_SIZE.Y; y++)
	{
		for(int x = 0; x < RIGHTCLICKMENU_SIZE.X; x++)
		{
			RIGHTCLICKMENU_GFX[x + y * RIGHTCLICKMENU_WIDTH].Char.AsciiChar = ' ';
			RIGHTCLICKMENU_GFX[x + y * RIGHTCLICKMENU_WIDTH].Attributes = B_White | White_I;
		}
	}
//**********************************SHADOWS***
//********************StartMenu***
	for(y = 0; y < STARTMENU_SIZE.Y; y++)
	{
		for(x = 0; x < STARTMENU_SIZE.X; x++)
		{
			SH_STARTMENU_GFX[x + y * STARTMENU_WIDTH].Char.AsciiChar = ' ';
			SH_STARTMENU_GFX[x + y * STARTMENU_WIDTH].Attributes = White_I;
		}
	}
//********************Right Click Menu***
	for(y = 0; y < RIGHTCLICKMENU_SIZE.Y; y++)
	{
		for(int x = 0; x < RIGHTCLICKMENU_SIZE.X; x++)
		{
			SH_RIGHTCLICKMENU_GFX[x + y * RIGHTCLICKMENU_WIDTH].Char.AsciiChar = ' ';
			SH_RIGHTCLICKMENU_GFX[x + y * RIGHTCLICKMENU_WIDTH].Attributes = White_I;
		}
	}
}

void DrawObject(string Object)
{
	if(Object == "CLEARSCRN")
	{
		ClrScrn;
		SysMan.DrawFlag.DrawTaskbar = true;
	}
	if(Object == "TASKBAR")
	{
		WriteConsoleOutput(hOutput, TASKBAR_GFX, TASKBAR_SIZE, SCRNST, &TASKBAR_EDGES);
		SysMan.DrawFlag.DrawTaskbar = false;
	}
	if(Object == "STARTMENU")
	{
		WriteConsoleOutput(hOutput, STARTMENU_GFX, STARTMENU_SIZE, SCRNST, &STARTMENU_EDGES);

		Text(1, 19, "  Windows XP  ", B_Purple | Yellow_I);
		Text(1, 22, "  Programs   >", B_Blue | Yellow_I);
		Text(1, 26, "  Documents  >", B_Blue | Yellow_I);
		Text(1, 30, "  Games      >", B_Blue | Yellow_I);
		Text(1, 46, "  Shut Down   ", B_Blue | Red_I);

		SysMan.DrawFlag.DrawStartMenu = false;
		SysMan.DrawStat.StartMenuUp = true;
	}
	if(Object == "RIGHTCLICKMENU")
	{
		if(Mouse.X<=68){
			RIGHTCLICKMENU_EDGES.Left   = Mouse.X;
			RIGHTCLICKMENU_EDGES.Right  = Mouse.X + (RIGHTCLICKMENU_WIDTH-1);
		}else{
			RIGHTCLICKMENU_EDGES.Left   = SCREEN_WIDTH - RIGHTCLICKMENU_WIDTH;
			RIGHTCLICKMENU_EDGES.Right  = SCREEN_WIDTH -1;
		}if(Mouse.Y<=37){
			RIGHTCLICKMENU_EDGES.Top    = Mouse.Y;
			RIGHTCLICKMENU_EDGES.Bottom = Mouse.Y + (RIGHTCLICKMENU_HEIGHT-1);
		}else{
			RIGHTCLICKMENU_EDGES.Top    = SCREEN_HEIGHT - RIGHTCLICKMENU_HEIGHT-2;
			RIGHTCLICKMENU_EDGES.Bottom = SCREEN_WIDTH -3;
		}

		WriteConsoleOutput(hOutput, RIGHTCLICKMENU_GFX, RIGHTCLICKMENU_SIZE, SCRNST, &RIGHTCLICKMENU_EDGES);

		if(!ClickedTaskbar)
		{
			Text(RIGHTCLICKMENU_EDGES.Left+1, RIGHTCLICKMENU_EDGES.Top+1, "Refresh", Black | B_White);
			Text(RIGHTCLICKMENU_EDGES.Left+1, RIGHTCLICKMENU_EDGES.Top+9, "Properties", Black | B_White);
		}
		SysMan.DrawStat.RightClickMenuUp = true;
	}
	if(Object == "STARTMENU_SHADOW")
	{
		WriteConsoleOutput(hOutput, SH_STARTMENU_GFX, STARTMENU_SIZE, SCRNST, &STARTMENU_EDGES);
		SysMan.DrawStat.StartMenuUp = false;
	}
	if(Object == "RIGHTCLICKMENU_SHADOW")
	{
		WriteConsoleOutput(hOutput, SH_RIGHTCLICKMENU_GFX, RIGHTCLICKMENU_SIZE, SCRNST, &RIGHTCLICKMENU_EDGES);
		SysMan.DrawStat.RightClickMenuUp = false;
	}
}

#endif