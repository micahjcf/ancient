#ifndef _MJCF_VIOBJECTS_
#define _MJCF_VIOBJECTS_

/*

  linked listed menus
  radio buttons
  check boxes
  scrolling text
  activity/loading bars
  tabed form areas
  auto shadow mouse
  input()
  action buttons
  tooltips
  right click info
  help buttons
  msg boxes

*/

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

		void SetHotSpot(SMALL_RECT SR){
			HotSpot = ReturnRect(SR.Left, SR.Top, SR.Right, SR.Bottom);
		}

		void SetHotSpot(BAR B){
			HotSpot = ReturnRect(B.Left, B.Y, B.Right, B.Y);
		}

		void Enable(){
			bEnabled = true;
		}

		void Disable();

		void Hide();
		void Regulate();
		void Run();

	private:
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
	//if((!bOverMsgUp) || (!bEnabled))
	if(!bOverMsgUp)
		return;
	if(!bEnabled)
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

//***********************************************
//***********************************************
class CMarqueeBar
{
	public:
		CMarqueeBar(){}
		~CMarqueeBar(){}

		void Setup(BAR position, WORD color, int speed, bool draw);
		void Draw(){Draw::BAR(Position, (char)219, BarColor);}

		void Run();

		void SetText(string NewText, WORD Color){ScrollingText=NewText;TextColor=Color;}
		void SetSpeed(int NewSpeed){nSpeed=NewSpeed;}

		BAR GetPosition(){return Position;}

	private:
		BAR Position;
		int nSpeed;
		WORD BarColor;
		WORD TextColor;
		string ScrollingText;

		int PrevSec;
		int Counter;
		int Index;
		int Length;
		int xPos;
};

void CMarqueeBar::Setup(BAR position, WORD color, int speed, bool bDraw)
{
	Position = position;
	nSpeed = speed;
	BarColor = color;
	xPos = Position.Right;
	PrevSec = Counter = Index = Length = 0;

	if(bDraw)
		Draw();
}

void CMarqueeBar::Run()
{
	SYSTEMTIME Time;
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

#endif