#ifndef _MJCF_VIOBJECTS_
#define _MJCF_VIOBJECTS_

#define DOS_GUI_ROUTINE

#define GeneralMsgClr Green_I
#define NoticeMsgClr Yellow_I
#define ErrorMsgClr Red_I

// Show styles
#define CMB_ALIGN_CENTER		1
#define CMB_ALIGN_LEFT			2

// Combined with show styles
#define CMB_SCROLL_ALIGN		4

//***********************************************
//***********************************************
class CMessageBar
{
	public:
		CMessageBar(){}
		~CMessageBar(){}

		void Setup(int Y, int xLeft, int xRight, WORD MsgBarColor, bool bDraw);
		void Draw();
		void Clear(){Draw::HorizLine(Position.Y, Position.Left+1, (Position.Right - Position.Left-1), ' ', White_I);}

		void PrintMsg(char* Msg, BYTE ShowStyle, WORD Color);
		void ClearMsg();
		void PrintOverMsg(char* OverMsg, BYTE ShowStyle, WORD Color);
		void ClearOverMsg();

		void Run();

		BAR Position;

	private:
		WORD Color;
		int PrevTime;
		int Counter;

		bool bMsgUp;
		bool bOverMsgUp;

		char* Msg;
		WORD MsgColor;
		BYTE DispStyle;
		SHORT ScrollDest;
		SHORT CurrentX;

		char* OverMsg;
		WORD OverMsgColor;
		BYTE OverMsgDispStyle;
		SHORT OverMsgScrollDest;
		SHORT OverMsgCurrentX;
};

//***********************************************
void CMessageBar::Setup(int Y, int Left, int Right, WORD MsgBarColor, bool bDraw)
{
	Position = ReturnBar(Y,Left,Right);
	Color = MsgBarColor;

	bMsgUp = false;
	bOverMsgUp = false;

	if(bDraw)
		Draw();
}

//***********************************************
void CMessageBar::Draw()
{
	Draw::HorizLine(Position.Y,Position.Left,(Position.Right - Position.Left),' ',B_White_I);
	Text(Position.Left, Position.Y, '<', Color);
	Text(Position.Right, Position.Y, '>', Color);
	Clear();
}

//***********************************************
void CMessageBar::ClearMsg()
{
	Draw::HorizLine(Position.Y, Position.Left+1, (Position.Right - Position.Left-1), ' ', White_I);
	bMsgUp = false;
}

//***********************************************
void CMessageBar::PrintMsg(char* Message, BYTE ShowStyle = CMB_ALIGN_CENTER, WORD Color = GeneralMsgClr)
{
	Msg = Message;
	MsgColor = Color;
	DispStyle = ShowStyle;

	Counter = 0;

	bMsgUp = true;

	if(!bOverMsgUp)
		Clear();

	if((!has(ShowStyle, CMB_SCROLL_ALIGN)) && (!bOverMsgUp))
	{
		if(has(ShowStyle, CMB_ALIGN_CENTER))
			Text((Position.Right/2 - LengthOf(Msg)/2), Position.Y, Msg, MsgColor);
		else if(has(ShowStyle, CMB_ALIGN_LEFT))
			Text(Position.Left + 2, Position.Y, Msg, MsgColor);
	}
	else if(has(ShowStyle, CMB_SCROLL_ALIGN))
	{
		if(has(ShowStyle, CMB_ALIGN_CENTER))
			ScrollDest = (Position.Right/2 - LengthOf(Msg)/2);
		else if(has(ShowStyle, CMB_ALIGN_LEFT))
			ScrollDest = Position.Left + 2;

		CurrentX = Position.Right - 1;
	}
}

//***********************************************
void CMessageBar::PrintOverMsg(char* Message, BYTE ShowStyle = CMB_ALIGN_CENTER, WORD Color = GeneralMsgClr)
{
	OverMsg = Message;
	OverMsgColor = Color;
	OverMsgDispStyle = ShowStyle;

	bOverMsgUp = true;

	Counter = 0;

	Clear();

	if(!has(ShowStyle, CMB_SCROLL_ALIGN))
	{
		if(has(ShowStyle, CMB_ALIGN_CENTER))
			Text((Position.Right/2 - LengthOf(OverMsg)/2), Position.Y, OverMsg, OverMsgColor);
		else if(has(ShowStyle, CMB_ALIGN_LEFT))
			Text(Position.Left + 2, Position.Y, OverMsg, OverMsgColor);
	}
	else if(has(ShowStyle, CMB_SCROLL_ALIGN))
	{
		if(has(ShowStyle, CMB_ALIGN_CENTER))
			OverMsgScrollDest = (Position.Right/2 - LengthOf(OverMsg)/2);
		else if(has(ShowStyle, CMB_ALIGN_LEFT))
			OverMsgScrollDest = Position.Left + 2;

		OverMsgCurrentX = Position.Right - 1;
	}
}

//***********************************************
void CMessageBar::ClearOverMsg()
{
	if(!bOverMsgUp)
		return;

	bOverMsgUp = false;

	Clear();

	if(!bMsgUp)
		return;

	if((!has(DispStyle, CMB_SCROLL_ALIGN)) || (CurrentX < ScrollDest))
	{
		if(has(DispStyle, CMB_ALIGN_CENTER))
			Text((Position.Right/2 - LengthOf(Msg)/2), Position.Y, Msg, MsgColor);
		else if(has(DispStyle, CMB_ALIGN_LEFT))
			Text(Position.Left + 2, Position.Y, Msg, MsgColor);
	}
}

//This function must be in the active loop!!!
//***********************************************
void CMessageBar::Run()
{
	if((!bMsgUp) && (!bOverMsgUp))
		return;

	if(bMsgUp && (!bOverMsgUp))
	{
		if(!has(DispStyle, CMB_SCROLL_ALIGN))
			return;
		if(CurrentX < ScrollDest)
			return;
	}

	if(bOverMsgUp)
	{
		if(!has(OverMsgDispStyle, CMB_SCROLL_ALIGN))
			return;
		if(OverMsgCurrentX < OverMsgScrollDest)
			return;
	}

	SYSTEMTIME Time;
	GetSystemTime(&Time);

	if(PrevTime != Time.wMilliseconds)
	{
		PrevTime = Time.wMilliseconds;
		Counter++;
	}

	if(Counter != 1)
		return;

	Counter = 0;

	Clear();

	ULONG N;

	if(bMsgUp && (!bOverMsgUp))
	{
		for(int n = 0; n < LengthOf(Msg); n++)
		{
			if(n + CurrentX >= Position.Right)
				break;

			WriteConsoleOutputCharacter(hOutput, &Msg[n], 1, ReturnCoord(CurrentX + n, Position.Y), &N);
			WriteConsoleOutputAttribute(hOutput, &MsgColor, 1, ReturnCoord(CurrentX + n, Position.Y), &N);
		}
		CurrentX--;
	}
	else if(bOverMsgUp)
	{
		for(int n = 0; n < LengthOf(OverMsg); n++)
		{
			if(n + OverMsgCurrentX >= Position.Right)
				break;

			WriteConsoleOutputCharacter(hOutput, &OverMsg[n], 1, ReturnCoord(OverMsgCurrentX + n, Position.Y), &N);
			WriteConsoleOutputAttribute(hOutput, &OverMsgColor, 1, ReturnCoord(OverMsgCurrentX + n, Position.Y), &N);
		}
		OverMsgCurrentX--;
	}
}

//***********************************************
//***********************************************
class COverMsg
{
	public:
		COverMsg(){bEnabled = false;}
		~COverMsg(){}

		void Setup(string OverMsg, COLOR MsgColor, BYTE ShowStyle, CMessageBar* pMsgBar);
		void SetHotSpot(SMALL_RECT SR){HotSpot=ReturnRect(SR.Left, SR.Top, SR.Right, SR.Bottom);}
		void SetHotSpot(BAR B){HotSpot=ReturnRect(B.Left, B.Y, B.Right, B.Y);}
		void Enable(){bEnabled=true;}
		void Disable();

		void Hide();
		void Regulate();
		void Run();

	//private:
		SMALL_RECT HotSpot;
		CMessageBar* MyMsgBar;

		string Msg;
		WORD Color;
		BYTE DispStyle;

		bool bOverMsgUp;
		bool bEnabled;
};

//***********************************************
void COverMsg::Setup(string OverMsg, COLOR MsgColor, BYTE ShowStyle, CMessageBar* pMsgBar)
{
	Msg = OverMsg;
	Color = MsgColor;
	DispStyle = ShowStyle;
	MyMsgBar = pMsgBar;

	bOverMsgUp = false;
	bEnabled = true;
}

//***********************************************
void COverMsg::Disable()
{
	bEnabled = false;

	if(bOverMsgUp)
		MyMsgBar->ClearOverMsg();
}

//***********************************************
void inline COverMsg::Hide()
{
	if((!bOverMsgUp) || (!bEnabled))
		return;

	bOverMsgUp = false;
	MyMsgBar->ClearOverMsg();
}

//***********************************************
void COverMsg::Regulate()
{
	if(!bEnabled)
		return;

	if(bOverMsgUp && (!Mouse.OverRectangle(HotSpot)))
	{
		bOverMsgUp = false;
		MyMsgBar->ClearOverMsg();
	}
}

//***********************************************
void COverMsg::Run()
{
	if(!bEnabled)
		return;

	if(bOverMsgUp)
		return;

	if(Mouse.OverRectangle(HotSpot))
	{
		bOverMsgUp = true;
		MyMsgBar->PrintOverMsg((char*)Msg.c_str(), DispStyle, Color);
	}
}

//Color Schemes:		// Off Colors			// On Colors
#define ButtonScheme1 (B_Red    | Red_I  ),(B_Green  | Green_I)	//Normal Red\Green
#define ButtonScheme2 (B_Blue_I | White_I),(B_Teal   | White_I)	//Blue\Dark Teal
#define ButtonScheme3 (B_Teal   | White_I),(B_Blue   | White_I)	//D.Teal\D.Blue
#define ButtonScheme4 (B_Teal   | White_I),(B_Blue_I | White_I)	//D.Teal\D.Blue
#define ButtonScheme5 (B_Blue_I | White_I),(B_Teal   | Teal_I )	//Blue\Dark Teal

//***********************************************
//***********************************************
class CButton
{
	public:
		CButton(){bIsInit=false;}
		~CButton(){}

		void Setup(char* ButtonText, int xLeft, int Y, WORD offColor, WORD onColor, bool bDraw);
		void SetupOverMsg(char* MsgTxt, WORD Color, CMessageBar* pMsgBar);
		void SetState(bool Pushed){bPushedIn=Pushed;Draw();}
		void Enable(){bEnabled=true;Draw();}
		void Disable(){bEnabled=false;Draw();}
		void Draw();

		void Regulate(){OverMsg.Regulate();}
		void Run();

		BAR Position;

		bool bEnabled;
		bool bPushedIn;
		bool bChanged; //Has the button just been toggled

	private:
		COverMsg OverMsg;

		char* szText;
		WORD OffColor;
		WORD OnColor;
		bool bIsInit;
};

//***********************************************
void CButton::Setup(char* ButtonText, int xLeft, int Y, WORD offColor, WORD onColor, bool bDraw)
{
	if(bIsInit)
		return;

	szText = ButtonText;
	OffColor = offColor;
	OnColor = onColor;
	Position = ReturnBar(Y,xLeft,xLeft + LengthOf(szText) - 1);

	bEnabled = true;

	if(bDraw)
		Draw();
}

//***********************************************
void CButton::SetupOverMsg(char* MsgTxt, WORD Color, CMessageBar* pMsgBar)
{
	OverMsg.SetHotSpot(Position);
	OverMsg.Setup(MsgTxt, Color, CMB_ALIGN_CENTER, pMsgBar);
}

//***********************************************
void CButton::Draw()
{
	if(bEnabled)
		Text(Position.Left, Position.Y, szText, (bPushedIn?OnColor:OffColor));
	else
		Text(Position.Left, Position.Y, szText, B_Grey | White);
}

//***********************************************
void CButton::Run()
{
	if(!bEnabled)
		return;

	if(bChanged)
		bChanged = false;

	OverMsg.Run();

	if(Mouse.Clicked(Position))
	{
		bPushedIn = (bPushedIn?false:true);	//Toggle
		Draw();
		bChanged = true;
	}
}

//***********************************************
//***********************************************
/*class CMenu
{
public:
	CMenu(){bIsInit=false;}
	~CMenu(){}

	bool SetupMenu(string SourceFile,string Label, int xLeft, int yTop);
	void SetupButton(int x, int y, string Text, WORD onColor, WORD offColor, bool bDraw);
	void DrawButton();
	void Enable();
	void Disable();
	void Toggle();
	void Regulate();
	void Run();
	int GetChoice();

	bool IsMenuUp(){return MenuUp;}

	ScrnBuffer Graphics;
	ScrnBuffer Shadow;
	BAR ButtonBar;

private:
	string ButtonText;
	WORD OnColor;
	WORD OffColor;
	bool DrawMenu;
	bool MenuUp;
	bool Enabled;
	bool bIsInit;
};

//***********************************************
bool CMenu::SetupMenu(string FileName, string Label, int xMenuLeft, int yMenuTop)
{
	if(!Graphics.LoadFromFile(FileName, Label))
		return false;

	Graphics.Place(xMenuLeft,yMenuTop);
	Shadow.GetFromScreen(Graphics.Edges);
	Shadow.Place(xMenuLeft, yMenuTop);

	MenuUp = DrawMenu = false;
	Enabled = true;

	return true;
}

//***********************************************
void CMenu::SetupButton(int x, int y, string text, WORD onColor, WORD offColor, bool bDraw)
{
	ButtonText = text;
	OnColor = onColor;
	OffColor = offColor;

	ButtonBar = ReturnBar(y, x, (x + text.length() - 1));

	if(bDraw)
		DrawButton();
}

//***********************************************
void CMenu::DrawButton()
{
	if(Enabled)
		Text(ButtonBar.Left, ButtonBar.Y, ButtonText, (MenuUp?OffColor:OnColor));
	else
		Text(ButtonBar.Left, ButtonBar.Y, ButtonText, B_Grey | White);
}

//***********************************************
void CMenu::Enable()
{
	if(Enabled)
		return;

	Enabled = true;
	DrawButton();
}

//***********************************************
void CMenu::Disable()
{
	if(!Enabled)
		return;

	Enabled = false;

	if(MenuUp)
		Toggle();
	else
		DrawButton();
}

//***********************************************
void CMenu::Toggle()
{
	if(!Enabled)
		return;

	if(MenuUp)
	{
		Shadow.Draw();
		MenuUp = false;
	}
	else
	{
		Shadow.FillFromScreen();
		Graphics.Draw();
		MenuUp = true;
	}
	DrawButton();
}

// Purpose: This turns the menu off if it needs to.
void CMenu::Regulate()
{
	if((!MenuUp) || (!Enabled))
		return;

	//Assume that the menu is showing

	if(Mouse.bLeftDown)
	{
	}
	else
	{
		if(Mouse.bLeftClicked && (!Mouse.OverScrnBuffer(Graphics)))// && (!Mouse.OverBar(ButtonBar)))
		{
			MenuUp = false;
			Shadow.Draw();
			DrawButton();
		}
	}

	//Get rid of menu if button is toggled or mouse clicked off menu
	//if(Mouse.bLeftClicked && (!Mouse.OverScrnBuffer(Graphics)))// && (!Mouse.OverBar(ButtonBar)))
	//{
		//MenuUp = false;
		//Shadow.Draw();
		//DrawButton();
		//return;
	//}

	//((!Mouse.OverScrnBuffer(Graphics)) && (!Mouse.OverBar(ButtonBar)))
	//if(
		//(!Mouse.OverScrnBuffer(Graphics))
		//|| ((!Mouse.OverBar(ButtonBar)) && Mouse.bLeftDown))
	//if((!Mouse.OverBar(ButtonBar)) && Mouse.bLeftDown)
	//{
		//MenuUp = false;
		//Shadow.Draw();
		//DrawButton();
		//return;
	//}
}

// Purpose: This draws the menu if it needs to.
void CMenu::Run()
{
	if(((!Mouse.bLeftClicked) || (!Enabled)) && (!Mouse.bLeftDown))
		return;

	if(Mouse.OverBar(ButtonBar))
	{
		if(MenuUp)
		{
			MenuUp = false;
			Shadow.Draw();
			DrawButton();
		}
		else
		{
			MenuUp = true;
			Shadow.FillFromScreen();
			Graphics.Draw();
			DrawButton();
		}
	}
}

// Note: This returns 0 if nothing was picked
int CMenu::GetChoice()
{
	if(!Mouse.bLeftClicked)
		return 0;

	if((!MenuUp) || (!Mouse.OverRectangle(Graphics.Edges)))
		return 0;

	int Choice = (Mouse.Position.Y - Graphics.Edges.Top + 1);

	// If you hit a choice
	if(!wholenum(((double)Choice/2)))
		Toggle();
	else
		return 0;

	return (Choice / 2);
}*/

//***************************************
class CCheckBox
{
	public:
		CCheckBox();
		~CCheckBox(){}

		void Setup(int xLeft, int Y, WORD color, bool bDraw);
		void SetupOverMsg(char* MsgTxt, WORD Color, CMessageBar* pMsgBar);
		void SetState(bool Checked){bChecked=Checked;Draw();}
		void Enable(){bEnabled=true;Draw();}
		void Disable(){bEnabled=false;Draw();}
		void Draw();
		void Run();

		bool isChecked(){return bChecked;}
		bool isEnabled(){return bEnabled;}

		COverMsg OverMsg;
		BAR Position;

	private:
		bool isInit;

		bool bEnabled;
		bool bChecked;

		bool bHalfClicked;

		WORD Color;
};

CCheckBox::CCheckBox()
{
	isInit = false;
	bEnabled = true;
	bChecked = false;
	bHalfClicked = false;
}

void CCheckBox::Setup(int xLeft, int Y, WORD color, bool bDraw)
{
	Position = ReturnBar(Y, xLeft, xLeft + 2);

	Color = color;

	isInit = true;

	if(bDraw)
		Draw();
}

void CCheckBox::SetupOverMsg(char* MsgTxt, WORD Color, CMessageBar* pMsgBar)
{
	OverMsg.SetHotSpot(Position);
	OverMsg.Setup(MsgTxt, Color, CMB_ALIGN_CENTER, pMsgBar);
}

void CCheckBox::Draw()
{
	//if(!isInit)
	//	KillProgram("Uninitialized CCheckBox object being drawn");

	if(!bEnabled)
	{
		Text(Position.Left, Position.Y, "[ ]", Grey);
		Text(Position.Left+1, Position.Y, (char)254, Grey);
		return;
	}

	if(bChecked)
		Text(Position.Left, Position.Y, "[*]", Color);
	else
		Text(Position.Left, Position.Y, "[ ]", Color);
}

void CCheckBox::Run()
{
	//if(!isInit)
	//	PrintCriticalError("Uninitialized CCheckBox object being run");

	if(!bEnabled)
		return;

	OverMsg.Run();

	if(Mouse.OverBar(Position) && Mouse.bLeftClicked)
		bHalfClicked = true;

	if(Mouse.OverBar(Position) && Mouse.bLeftReleased && bHalfClicked)
	{
		bChecked = (bChecked?false:true);
		Draw();
	}

	if(Mouse.bLeftReleased)
		bHalfClicked = false;
}

class CMarqueeBar
{
	public:
		CMarqueeBar(){isInit=false;}
		~CMarqueeBar(){}

		void Setup(BAR position, WORD color, int speed, bool draw);
		void Draw(){Draw::BAR(Position, (char)219, BarColor);}

		void Run();

		void SetText(string NewText, WORD Color){ScrollingText=NewText;TextColor=Color;}
		void SetSpeed(int NewSpeed){nSpeed=NewSpeed;}

		BAR GetPosition(){return Position;}

	private:
		bool isInit;

		BAR Position;
		int nSpeed;
		WORD BarColor;
		WORD TextColor;
		string ScrollingText;
};

void CMarqueeBar::Setup(BAR position, WORD color, int speed, bool bDraw)
{
	Position = position;
	nSpeed = speed;
	BarColor = color;

	isInit = true;

	if(bDraw)
		Draw();
}

void CMarqueeBar::Run()
{
	if(!isInit)
		return;

	static SYSTEMTIME Time;
	static int PrevSec = 0;
	static int Counter = 0;
	static int Index = 0;
	static int Length = 0;
	static int xPos = Position.Right;

	GetSystemTime(&Time);

	if(PrevSec != Time.wMilliseconds)
	{
		PrevSec = Time.wMilliseconds;
		Counter++;
	}

	if(Counter == nSpeed)
	{
		Counter = 0;

		if(xPos == Position.Left-1)
		{
			if(Index == ScrollingText.length())
			{
				Length = 1;
				xPos = Position.Right;
				Index = 0;
			}
			else
			{
				Index++;
				xPos = Position.Left;
			}
		}
		else
			Length++;

		Draw();
		Text(xPos, Position.Y, ScrollingText.substr(Index,Length), TextColor | (BarColor<<4));
		xPos--;
	}
}

class CActivityBar
{
public:
	CActivityBar(){}
	~CActivityBar(){}

	void Setup(BAR Pos, char Character, WORD Colors, WORD ProgressColors, int Speed);
	void Increment();
	void IncrementOnCounter();

	BAR Position;
	char Char;
	WORD Color;
	WORD ProgressColor;
	int CounterTime;	// # of milliseconds that has to pass before another increment

	// Previous static members
	int X;
	bool WaxOn;
	int PrevTime;
	int Counter;
};

void CActivityBar::Setup(BAR Pos, char Character, WORD Colors, WORD ProgressColors, int Speed = 6)
{
	Char = Character;
	Position = Pos;
	Color = Colors;
	ProgressColor = ProgressColors;
	CounterTime = Speed;

	X = Position.Left;
	WaxOn = true;
	PrevTime = 0;
	Counter = 0;

	Draw::BAR(Position, Char, Color);
}

void CActivityBar::Increment()
{
	//static int X = Position.Left;
	//static bool WaxOn = true;

	Text(X++, Position.Y, Char, (WaxOn?ProgressColor:Color));

	if(X == Position.Right + 1)
	{
		X = Position.Left;
		WaxOn = (WaxOn?false:true);
	}
}

void CActivityBar::IncrementOnCounter()
{
	//static int PrevTime = 0;
	//static int Counter = 0;

	SYSTEMTIME Time;
	GetSystemTime(&Time);

	if(PrevTime != Time.wMilliseconds)
	{
		PrevTime = Time.wMilliseconds;
		Counter++;
	}

	if(Counter == CounterTime)
	{
		Counter = 0;
		Increment();
	}
}

class CLoadBar
{
public:
	CLoadBar(){}
	~CLoadBar(){}

	void Setup(BAR Pos, char Character, WORD SideColors, WORD BackgroundColor, WORD ProgressColors, int Speed);
	void Reset();
	void inline Clear();

	void Increment();
	void IncrementOnCounter();

	BAR Position;
	string Chars;
	WORD SideColor;
	WORD BGColor;
	WORD ProgressColor;
	int TimeWait;	// # of milliseconds that has to pass before another increment

	// Previous static members
	int Index;
	int Length;
	int xPos;
	int PrevTime;
	int Counter;
};

void CLoadBar::Setup(BAR Pos, char Character, WORD SideColors, WORD BackgroundColor, WORD ProgressColors, int Speed = 5)
{
	Position = ReturnBar(Pos.Y, Pos.Left, Pos.Right);
	Chars.resize(3);

	for(int n = 0; n < 3; n++)
	{
		Chars[n] = Character;
	}

	SideColor = SideColors;
	BGColor = BackgroundColor;
	ProgressColor = ProgressColors;
	TimeWait = Speed;

	Index = Chars.length();
	Length = 0;
	xPos = Position.Left;
	PrevTime = 0;
	Counter = 0;

	Draw::BAR(Position, (char)219, BGColor);
	Text(Position.Left - 1, Position.Y, '(', SideColor);
	Text(Position.Right + 1, Position.Y, ')', SideColor);
}

void CLoadBar::Reset()
{
	Index = Chars.length();
	Length = 0;
	xPos = Position.Left;
	PrevTime = 0;
	Counter = 0;
}

void inline CLoadBar::Clear()
{
	Draw::BAR(Position, (char)219, BGColor);
}

void CLoadBar::Increment()
{
	if(xPos >= Position.Right - 2)
	{
		if(Length > 0)
		{
			Length--;
			xPos++;
		}
		else
		{
			Index = Chars.length();
			Length = 0;
			xPos = Position.Left;
		}
	}
	else
	{
		if(Index > 0)
		{
			Index--;
			Length++;
		}
		else
			xPos++;
	}

	Draw::BAR(Position, (char)219, BGColor);
	Text(xPos, Position.Y, Chars.substr(Index,Length), (ProgressColor | DeleteBG(BGColor)<<4));
																//(ProgressColor | (Color<<4)));
}

void CLoadBar::IncrementOnCounter()
{
	SYSTEMTIME Time;
	GetSystemTime(&Time);

	if(PrevTime != Time.wMilliseconds)
	{
		PrevTime = Time.wMilliseconds;
		Counter++;
	}

	if(Counter == TimeWait)
	{
		Counter = 0;
		Increment();
	}
}

#endif