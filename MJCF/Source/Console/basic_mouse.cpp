#include <windows.h>

#include <Console\stdcon.h>

#include <Console\cursor_mouse.h>

CONSOLEMOUSE Mouse;

CONSOLEMOUSE::CONSOLEMOUSE()
{
	bClicked = false;
	bLeftClicked = false;
	bRightClicked = false;
	bDoubleClicked = false;
	bLeftDown = false;
	bRightDown = false;
	bLeftReleased = false;
	bRightReleased = false;

	FlushConsoleInputBuffer(&InputBuffer);
}

// Checks for valid mouse input and updates the mouse object
// Returns true if valid mouse input was recived
BOOL CONSOLEMOUSE::GetInput()
{
	DWORD Events;

	do
	{
		GetNumberOfConsoleInputEvents(hStdInput, &Events);

		if(!Events)
			return FALSE;

		ReadConsoleInput(hStdInput, &InputBuffer, 1, &Events);

		if(InputBuffer.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED)
			return FALSE;

		if(InputBuffer.EventType == MOUSE_EVENT)
			break;
	}while(true);

	Update();

	return TRUE;
}

void CONSOLEMOUSE::Update()
{
	Position = InputBuffer.Event.MouseEvent.dwMousePosition;

	static BOOL bLeftWasDown = FALSE;
	static BOOL bRightWasDown = FALSE;

	bLeftReleased = false;
	bRightReleased = false;

	if(InputBuffer.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		bLeftWasDown = true;
		bLeftClicked = true;
		bLeftDown = true;
	}
	else
	{
		bLeftClicked = false;
		bLeftDown = false;

		if(bLeftWasDown)
		{
			bLeftReleased = true;
			bLeftWasDown = false;
		}
	}

	if(InputBuffer.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
	{
		bRightWasDown = true;
		bRightClicked = true;
		bRightDown = true;
	}
	else
	{
		bRightClicked = false;
		bRightDown = false;

		if(bRightWasDown)
		{
			bRightReleased = true;
			bRightWasDown = false;
		}
	}

	if((InputBuffer.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK) && bLeftClicked)
		bDoubleClicked = true;
	else
		bDoubleClicked = false;

	if(bLeftClicked || bRightClicked)
		bClicked = true;
	else
		bClicked = false;

	if(bClicked && InputBuffer.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
	{
		bLeftClicked = false;
		bRightClicked = false;
		bDoubleClicked = false;
		bClicked = false;
	}
}

void CONSOLEMOUSE::WaitForActivity()
{
	DWORD Events;

	do
	{
		ReadConsoleInput(hStdInput, &InputBuffer, 1, &Events);
		if(InputBuffer.EventType == MOUSE_EVENT)
			return;
	}while(true);
}

BOOL CONSOLEMOUSE::OverScrnBuffer(ScrnShadow& s)
{
	if(Position.X >= s.Edges.Left &&
		Position.X <= s.Edges.Right &&
		Position.Y >= s.Edges.Top &&
		Position.Y <= s.Edges.Bottom)
		return TRUE;
	return FALSE;
}

BOOL CONSOLEMOUSE::OverRectangle(SMALL_RECT& sr)
{
	if(Position.X >= sr.Left &&
		Position.X <= sr.Right &&
		Position.Y >= sr.Top &&
		Position.Y <= sr.Bottom)
		return TRUE;
	return FALSE;
}

BOOL CONSOLEMOUSE::OverBar(BAR& B)
{
	if(Position.Y == B.Y && Position.X >= B.Left && Position.X <= B.Right)
		return TRUE;
	return FALSE;
}

BOOL CONSOLEMOUSE::Clicked(ScrnShadow& s)
{
	if(!bLeftClicked)
		return FALSE;

	if(Position.X >= s.Edges.Left &&
		Position.X <= s.Edges.Right &&
		Position.Y >= s.Edges.Top &&
		Position.Y <= s.Edges.Bottom)
		return TRUE;
	return FALSE;
}

BOOL CONSOLEMOUSE::Clicked(SMALL_RECT& sr)
{
	if(!bLeftClicked)
		return FALSE;

	if(Position.X >= sr.Left &&
		Position.X <= sr.Right &&
		Position.Y >= sr.Top &&
		Position.Y <= sr.Bottom)
		return TRUE;
	return FALSE;
}

BOOL CONSOLEMOUSE::Clicked(BAR& B)
{
	if(!bLeftClicked)
		return FALSE;

	if(Position.Y == B.Y && Position.X >= B.Left && Position.X <= B.Right)
		return TRUE;
	return FALSE;
}

BOOL CONSOLEMOUSE::Clicked(COORD& C)
{
	if(!bLeftClicked)
		return FALSE;

	if(Position.X == C.X && Position.Y == C.Y)
		return TRUE;
	return FALSE;
}