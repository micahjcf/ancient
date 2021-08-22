#ifndef _MJCF_CONSOLE_
#define _MJCF_CONSOLE_

HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
INPUT_RECORD InputRecord;
DWORD Events=0;

CONSOLE_SCREEN_BUFFER_INFO	ConsoleInfo;
CONSOLE_CURSOR_INFO			CursorInfo;
SYSTEMTIME					SysTime;
SYSTEMTIME					ProgStartTime;

COORD SCRNST = {0,0};

#define SCREEN_WIDTH	(ConsoleInfo.dwMaximumWindowSize.X)
#define SCREEN_HEIGHT	(ConsoleInfo.srWindow.Bottom+1)
#define SCREEN_XMAX		(ConsoleInfo.srWindow.Right)
#define SCREEN_YMAX		(ConsoleInfo.srWindow.Bottom)

class SCREEN_BUFFER_OBJECT
{
public:
	SCREEN_BUFFER_OBJECT(){p_GFX = NULL;}
	SCREEN_BUFFER_OBJECT(int, int);
	~SCREEN_BUFFER_OBJECT(){delete[] p_GFX;}
	void InitGFX(int size){if(p_GFX)delete[] p_GFX;p_GFX=new CHAR_INFO[size];}
	CHAR_INFO*	p_GFX;
	SMALL_RECT	_EDGES;
	COORD		_SIZE;
};

SCREEN_BUFFER_OBJECT::SCREEN_BUFFER_OBJECT(int xSize, int ySize)
{
	p_GFX = new CHAR_INFO[xSize * ySize];
	_SIZE.X = xSize;
	_SIZE.Y = ySize;
}

SCREEN_BUFFER_OBJECT cs;

//ENABLE_PROCESSED_INPUT	keyboard
//ENABLE_MOUSE_INPUT		mouse
void ConsoleSetup(BYTE InputType)
{
	GetSystemTime(&ProgStartTime);
	SetConsoleMode(hInput, InputType);
	GetConsoleScreenBufferInfo(hOutput, &ConsoleInfo);

	cs.p_GFX = new CHAR_INFO[ConsoleInfo.dwSize.X * ConsoleInfo.dwSize.Y];
	cs._EDGES.Left		= 0;
	cs._EDGES.Top		= 0;
	cs._EDGES.Right		= SCREEN_XMAX;
	cs._EDGES.Bottom	= SCREEN_YMAX;

	cs._SIZE.X = SCREEN_XMAX;
	cs._SIZE.Y = SCREEN_YMAX;

	for(int y = 0; y < cs._SIZE.Y; y++)
	{
		for(int x = 0; x < cs._SIZE.X; x++)
		{
			cs.p_GFX[x + y * cs._SIZE.X].Char.AsciiChar = ' ';
			cs.p_GFX[x + y * cs._SIZE.X].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		}
	}
}

bool Compatible(int WidthMin, int HeightMin)
{
	if(WidthMin > ConsoleInfo.srWindow.Right+1)
		return false;
	if(HeightMin > ConsoleInfo.srWindow.Bottom+1)
		return false;
	return true;
}

bool Compatible_Exact(int Width, int Height)
{
	if(Width != ConsoleInfo.srWindow.Right+1)
		return false;
	if(Height != ConsoleInfo.srWindow.Bottom+1)
		return false;
	return true;
}

#endif