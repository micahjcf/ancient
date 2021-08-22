#include <windows.h>

#include <Console\stdcon.h>

#include <Console\cursor_mouse.h>

CURSORMOUSE Mouse;

CURSORMOUSE::CURSORMOUSE()
{
	CursorChar = 30;
	CursorColor = White_I;
	CurrentColor = B_White_I;

	bCursorEnabled = true;

	//FlushConsoleInputBuffer(&InputBuffer);   <-- this was moved to CONSOLEMOUSE constructor

	PrevCoords = InputBuffer.Event.MouseEvent.dwMousePosition;
	Position = InputBuffer.Event.MouseEvent.dwMousePosition;
}

void CURSORMOUSE::UpdateCursor()
{
	if(! bCursorEnabled)
		return;

	// Redraw the icon if it's been drawn over and update the shadow memory
	ReprintCursor();

	// Erase the icon and draw it in it's new spot if it moved
	DispCursor();
}

void CURSORMOUSE::ReprintCursor()
{
	// Check if the icon has been drawn over
	char CurChar;
	COLOR CurColor;
	DWORD n;

	ReadConsoleOutputCharacter(hStdOutput, &CurChar, 1, PrevCoords, &n);
	ReadConsoleOutputAttribute(hStdOutput, &CurColor, 1, PrevCoords, &n);

	if((CurrentColor != CurColor) || (CurChar != CursorChar))
	{
		if(CurrentColor != CurColor)
			CursorColorShadow = CurColor;
		if(CurChar != CursorChar)
			CursorCharShadow = CurChar;

		DrawCursor();
	}
}

void CURSORMOUSE::DispCursor()
{
	if(InputBuffer.EventType != MOUSE_EVENT)
		return;

	if(InputBuffer.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED)
		return;

	if(InputBuffer.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
	{
		if(((PrevCoords.X == InputBuffer.Event.MouseEvent.dwMousePosition.X) &&
		(PrevCoords.Y == InputBuffer.Event.MouseEvent.dwMousePosition.Y)))
			return;
	}
	else
		return;

	EraseCursor();

	PrevCoords = InputBuffer.Event.MouseEvent.dwMousePosition;

	UpdateCursorShadowMemory();

	DrawCursor();
}

// Displays the mouse icon
void CURSORMOUSE::DrawCursor()
{
	COLOR DispColor;
	DWORD n;
	ReadConsoleOutputAttribute(hStdOutput, &DispColor, 1, PrevCoords, &n);

	//If the current background color is the same as the cursor color
	//This will washout the cursor so the user can't see it on screen
	if(DeleteFG(DispColor) == CursorColor << 4)
	{
		if(DeleteBG(DispColor) != CursorColor)
			DispColor = FlipFGBG(DispColor);
		else //If the current foreground and background colors are both the same as the cursor color
			DispColor = CursorColor << 4;
	}
	else
		DispColor = DeleteFG(DispColor) | CursorColor;

	CurrentColor = FlipFGBG(DispColor);

	Text(PrevCoords, CursorChar, CurrentColor);
}

void CURSORMOUSE::UpdateCursorShadowMemory()
{
	DWORD n;
	ReadConsoleOutputCharacter(hStdOutput, &CursorCharShadow, 1, PrevCoords, &n);
	ReadConsoleOutputAttribute(hStdOutput, &CursorColorShadow, 1, PrevCoords, &n);
}

void CURSORMOUSE::Disable()
{
	if(! bCursorEnabled)
		return;

	DWORD Mode;

	GetConsoleMode(hStdOutput, &Mode);

	Mode &= ~ENABLE_MOUSE_INPUT;

	SetConsoleMode(hStdInput, Mode);

	bCursorEnabled = false;
	EraseCursor();
}

void CURSORMOUSE::Enable()
{
	if(bCursorEnabled)
		return;

	bCursorEnabled = true;

	SetConsoleMode(hStdInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);
}