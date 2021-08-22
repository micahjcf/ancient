#ifndef _Win_DOS_DataStructures_
#define _Win_DOS_DataStructures_

#define ClickedTaskbar (Mouse.Y>47)
#define ClickedStartButton ((Mouse.Y==SCREEN_HEIGHT||Mouse.Y==SCREEN_HEIGHT-1)&&Mouse.X<=7)
#define ClickedStartMenu (Mouse.Y>=18&&Mouse.Y<=47&&Mouse.X<=15)
#define ClickedMenuItem1 (Mouse.Y>=21&&Mouse.Y<=23&&Mouse.X>=1&&Mouse.X<=14)
#define ClickedMenuItem2 (Mouse.Y>=25&&Mouse.Y<=27&&Mouse.X>=1&&Mouse.X<=14)
#define ClickedMenuItem3 (Mouse.Y>=29&&Mouse.Y<=31&&Mouse.X>=1&&Mouse.X<=14)
#define ClickedMenuItem4 (Mouse.Y>=33&&Mouse.Y<=35&&Mouse.X>=1&&Mouse.X<=14)
#define ClickedMenuItem5 (Mouse.Y>=37&&Mouse.Y<=39&&Mouse.X>=1&&Mouse.X<=14)
#define ClickedMenuItem6 (Mouse.Y>=41&&Mouse.Y<=43&&Mouse.X>=1&&Mouse.X<=14)
#define ClickedMenuItem7 (Mouse.Y>=45&&Mouse.Y<=47&&Mouse.X>=1&&Mouse.X<=14)
#define ClickedRightClickMenu (Mouse.X>=RIGHTCLICKMENU_EDGES.Left&&Mouse.X<=RIGHTCLICKMENU_EDGES.Right&&Mouse.Y>=RIGHTCLICKMENU_EDGES.Top&&Mouse.Y<=RIGHTCLICKMENU_EDGES.Bottom)

typedef bool FLAG;

struct DRAWFLAGS
{
	FLAG		DrawTaskbar;
	FLAG		DrawStartMenu;
};

struct DRAWSTAT
{
	bool StartMenuUp;
	bool RightClickMenuUp;
};

struct RCMPROPERTIES
{
	bool ontaskbar;
};

class SYSTEMMANAGER
{
public:
	SYSTEMMANAGER();
	~SYSTEMMANAGER();
	DRAWFLAGS		DrawFlag;
	DRAWSTAT		DrawStat;
	RCMPROPERTIES	RightClickMenuProp;
	bool			Shutdown;
}; SYSTEMMANAGER SysMan;

class WINDOWSMAJOR
{
public:
	WINDOWSMAJOR();
	~WINDOWSMAJOR();
	char			*pszStartMenuItems;
}; WINDOWSMAJOR WinMaj;

SYSTEMMANAGER::SYSTEMMANAGER()
{
	DrawFlag.DrawStartMenu		= false;
	DrawFlag.DrawTaskbar		= true;
	DrawStat.StartMenuUp		= false;
	DrawStat.RightClickMenuUp	= false;
	Shutdown					= false;
}

SYSTEMMANAGER::~SYSTEMMANAGER()
{
}

WINDOWSMAJOR::WINDOWSMAJOR()
{
}

WINDOWSMAJOR::~WINDOWSMAJOR()
{
	delete [] pszStartMenuItems;
}

#endif