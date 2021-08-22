#ifndef _DATA_STRUCTURES_
#define _DATA_STRUCTURES_

#define FIELD_WIDTH		60
#define FIELD_HEIGHT	50

typedef bool FLAG;

struct TOOLS
{
	WORD		SelectedCharColor;
	WORD		SelectedBGColor;
	string		SelectedChar;
};

struct DRAWFLAGS
{
	FLAG		DrawScrn;
	FLAG		DrawFileMenu;
	FLAG		DrawEditMenu;
	FLAG		DrawToolMenu;
	FLAG		DrawColorMenu;
};

struct DRAWSTAT
{
	bool		FileMenuUp;
	bool		EditMenuUp;
	bool		ToolMenuUp;
	bool		ColorMenuUp;
};

class SYSTEMMANAGER
{
public:
	SYSTEMMANAGER();
	~SYSTEMMANAGER();
	DRAWFLAGS	DrawFlag;
	DRAWSTAT	DrawStat;
	TOOLS		Tool;
	bool		MenuUp;
	bool		done;
}; SYSTEMMANAGER SysMan;

SYSTEMMANAGER::SYSTEMMANAGER()
{
	DrawFlag.DrawScrn		= true;
	DrawFlag.DrawFileMenu	= false;
	DrawFlag.DrawEditMenu	= false;
	DrawFlag.DrawToolMenu	= false;
	DrawFlag.DrawColorMenu	= false;
	DrawStat.FileMenuUp		= false;
	DrawStat.EditMenuUp		= false;
	DrawStat.ToolMenuUp		= false;
	DrawStat.ColorMenuUp	= false;
	Tool.SelectedBGColor	= 0x0001;
	Tool.SelectedChar		= ' ';
	Tool.SelectedCharColor	= 0x0010;
	MenuUp					= false;
	done					= false;
}

SYSTEMMANAGER::~SYSTEMMANAGER()
{
}

struct PICTURE
{
	WORD	BGColor[FIELD_WIDTH][FIELD_HEIGHT];
	char	Char[FIELD_WIDTH][FIELD_HEIGHT];
	WORD	CharColor[FIELD_WIDTH][FIELD_HEIGHT];
};

#endif