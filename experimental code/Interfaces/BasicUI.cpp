#include <windows.h>

#include <stdcon.h>
#include <graphics.h>

#include <BasicUI.h>

//MessageBar:: Print CRITICAL message! have it flash

void CMessageBar::Setup(BAR pos, COLOR MsgBarColor)
{
	Position = pos;
	Color = MsgBarColor;

	bMsgUp = false;
	bOverMsgUp = false;
}

void CMessageBar::Clear()
{
	Draw::HorizLine(coord(Position.Y, Position.Left+1), (Position.Right - Position.Left-1), ' ', White_I);
}

void CMessageBar::Draw()
{
	Draw::Line(Position, ' ',  Color);
	Text(coord(Position.Left, Position.Y), '<', Color);
	Text(coord(Position.Right, Position.Y), '>', Color);
	Clear();
}

void CMessageBar::ClearMsg()
{
	Draw::Line(Position, ' ', White_I);
	//Draw::HorizLine(Position.Y, Position.Left+1, (Position.Right - Position.Left-1), ' ', White_I);
	bMsgUp = false;
}

void CMessageBar::PrintMsg(char* Message, BYTE ShowStyle = CMB_ALIGN_CENTER, COLOR Color = GeneralMsgClr)
{
	Msg = Message;
	MsgColor = Color;
	DispStyle = ShowStyle;

	Counter = 0;

	bMsgUp = true;

	if(!bOverMsgUp)
		Clear();

	if(!(ShowStyle & CMB_SCROLL_ALIGN) && !bOverMsgUp)
	{
		if(ShowStyle & CMB_ALIGN_CENTER)
			Text(coord((Position.Right/2 - strlen(Msg)/2), Position.Y), Msg, MsgColor);
		else if(ShowStyle & CMB_ALIGN_LEFT)
			Text(coord(Position.Left + 2, Position.Y), Msg, MsgColor);
	}
	else if(ShowStyle & CMB_SCROLL_ALIGN)
	{
		if(ShowStyle & CMB_ALIGN_CENTER)
			ScrollDest = (Position.Right/2 - strlen(Msg)/2);
		else if(ShowStyle & CMB_ALIGN_LEFT)
			ScrollDest = Position.Left + 2;

		CurrentX = Position.Right - 1;
	}
}

void CMessageBar::PrintOverMsg(char* Message, BYTE ShowStyle = CMB_ALIGN_CENTER, COLOR Color = GeneralMsgClr)
{
	OverMsg = Message;
	OverMsgColor = Color;
	OverMsgDispStyle = ShowStyle;

	bOverMsgUp = true;

	Counter = 0;

	Clear();

	if(!(ShowStyle & CMB_SCROLL_ALIGN))
	{
		if(ShowStyle & CMB_ALIGN_CENTER)
			Text(coord((Position.Right/2 - strlen(OverMsg)/2), Position.Y), OverMsg, OverMsgColor);
		else if(ShowStyle & CMB_ALIGN_LEFT)
			Text(coord(Position.Left + 2, Position.Y), OverMsg, OverMsgColor);
	}
	else if(ShowStyle & CMB_SCROLL_ALIGN)
	{
		if(ShowStyle & CMB_ALIGN_CENTER)
			OverMsgScrollDest = (Position.Right/2 - strlen(OverMsg)/2);
		else if(ShowStyle & CMB_ALIGN_LEFT)
			OverMsgScrollDest = Position.Left + 2;

		OverMsgCurrentX = Position.Right - 1;
	}
}

void CMessageBar::ClearOverMsg()
{
	if(!bOverMsgUp)
		return;

	bOverMsgUp = false;

	Clear();

	if(!bMsgUp)
		return;

	if(!(DispStyle & CMB_SCROLL_ALIGN) || (CurrentX < ScrollDest))
	{
		if(DispStyle & CMB_ALIGN_CENTER)
			Text(coord((Position.Right/2 - strlen(Msg)/2), Position.Y), Msg, MsgColor);
		else if(DispStyle & CMB_ALIGN_LEFT)
			Text(coord(Position.Left + 2, Position.Y), Msg, MsgColor);
	}
}

//This function must be in the active loop!!!
void CMessageBar::Run()
{
	if((!bMsgUp) && (!bOverMsgUp))
		return;

	if(bMsgUp && (!bOverMsgUp))
	{
		if(! (DispStyle & CMB_SCROLL_ALIGN))
			return;
		if(CurrentX < ScrollDest)
			return;
	}

	if(bOverMsgUp)
	{
		if(! (OverMsgDispStyle & CMB_SCROLL_ALIGN))
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
		for(UINT n = 0; n < strlen(Msg); n++)
		{
			if(n + CurrentX >= Position.Right)
				break;

			WriteConsoleOutputCharacter(hOutput, &Msg[n], 1, coord(CurrentX + n, Position.Y), &N);
			WriteConsoleOutputAttribute(hOutput, &MsgColor, 1, coord(CurrentX + n, Position.Y), &N);
		}
		CurrentX--;
	}
	else if(bOverMsgUp)
	{
		for(UINT n = 0; n < strlen(OverMsg); n++)
		{
			if(n + OverMsgCurrentX >= Position.Right)
				break;

			WriteConsoleOutputCharacter(hOutput, &OverMsg[n], 1, coord(OverMsgCurrentX + n, Position.Y), &N);
			WriteConsoleOutputAttribute(hOutput, &OverMsgColor, 1, coord(OverMsgCurrentX + n, Position.Y), &N);
		}
		OverMsgCurrentX--;
	}
}
/*
//***********************************************
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
*/