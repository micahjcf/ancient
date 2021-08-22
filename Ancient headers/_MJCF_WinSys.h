#ifndef _MJCF_WINSYS_
#define _MJCF_WINSYS_

class ERRORLOG
{
public:
	ERRORLOG(){index = 0;Errors[0] = "No errors";}
	~ERRORLOG(){}
	void AddError(string);
	void ShowErrors();

	string		Errors[10];
	int			index;
};ERRORLOG errorlog;

void ERRORLOG::AddError(string error)
{
	if(index < 10)
	{
		Errors[index++] = error;
	}
	else
	{
		cout<<"Errors full";
		KB_WAIT('R');
	}
}

void ERRORLOG::ShowErrors()
{
	SetCursorPosition(0,0);
	for(int n=0; n<index+1; n++)
		cout<<Errors[n] <<endl;
}

class WINDOW
{
public:
	WINDOW(){};
	~WINDOW(){};
	void Draw();
	void Resize(int, int);

	string					Title;
	SCREEN_BUFFER_OBJECT	Background;
};

void WINDOW::Draw()
{
	WriteConsoleOutput(hOutput, Background.p_GFX, Background._SIZE, SCRNST, &Background._EDGES);
	DrawBox(Background._EDGES.Left,Background._EDGES.Top, Background._SIZE.X,Background._SIZE.Y, (char)219, Blue | B_White_I);
	Text(Background._EDGES.Left+1, Background._EDGES.Top, Title, White_I | B_Blue);
	Text_char(Background._EDGES.Right, Background._EDGES.Top, (char)219, Red_I | B_White_I);
}

void WINDOW::Resize(int xSize, int ySize)
{
	delete Background.p_GFX;
	Background.p_GFX = new CHAR_INFO[xSize * ySize];

	for(int y = 0; y < Background._SIZE.Y; y++)
	{
		for(int x = 0; x < Background._SIZE.X; x++)
		{
			Background.p_GFX[x + y * Background._SIZE.X].Char.AsciiChar = ' ';
			Background.p_GFX[x + y * Background._SIZE.X].Attributes = White_I;
		}
	}
}

class WINDOWNODE
{
public:
	WINDOWNODE(){pNext = NULL;}
	~WINDOWNODE(){}
	WINDOW*		MyWindow;
	WINDOWNODE*		pNext;
};

class WINDOWSMANAGER
{
public:
	WINDOWSMANAGER(){pHead = NULL;}
	~WINDOWSMANAGER(){}

	bool Window_Create(string, int, int, int, int);
	WINDOW* Window_Register();

	WINDOWNODE*		pHead;

	void StartList(WINDOW*&);
	void AddWindow(WINDOW*&);
};WINDOWSMANAGER WinMan;

bool WINDOWSMANAGER::Window_Create(string Name, int xStart, int yStart, int Width, int Height)
{
	WINDOW* Win = WinMan.Window_Register();
	if(NULL == Win)
	{
		errorlog.AddError("WinReg Failure");
		return false;
	}

	Win->Title = Name;
	Win->Background._EDGES.Left		= xStart;
	Win->Background._EDGES.Top		= yStart;
	Win->Background._EDGES.Right	= xStart+Width;
	Win->Background._EDGES.Bottom	= yStart+Height;
	Win->Background._SIZE.X = Width;
	Win->Background._SIZE.Y = Height;
	Win->Background.p_GFX = NULL;

	Win->Resize(Width, Height);
	Win->Draw();

	return true;
}

WINDOW* WINDOWSMANAGER::Window_Register()
{
	WINDOW* pW = new WINDOW;
	if(NULL == pHead)
		StartList(pW);
	else
		AddWindow(pW);
	return pW;
}

void WINDOWSMANAGER::StartList(WINDOW*& pW)
{
	pHead = new WINDOWNODE;
	pHead->MyWindow = pW;
	pHead->pNext = NULL;
}

void WINDOWSMANAGER::AddWindow(WINDOW*& pW)
{
	WINDOWNODE* pCurrent = pHead;

	while(pCurrent->pNext != NULL)
		pCurrent = pCurrent->pNext;

	pCurrent->pNext = new WINDOWNODE;
	pCurrent->pNext->MyWindow = pW;
	pCurrent->pNext = NULL;
}
#endif