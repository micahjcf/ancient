#ifndef _MJCF_INPUT_
#define _MJCF_INPUT_

#define ALLOW_ALL	0x0001
#define ALLOW_ALPHA	0x0002
#define ALLOW_NUM	0x0004

#define SHOW		0x0001
#define NOSHOW		0x0002
#define HIDE		0x0004

void Input(int		&Variable,
		   int		Length,
		   int		X,
		   int		Y,
		   WORD		wInputType		= ALLOW_ALL,
		   WORD		wShowChoice		= SHOW,
		   DWORD	dwTextColor		= White)
{
	txtPosition.X = X;
	txtPosition.Y = Y;

	SetCursorPosition(X, Y);
	SetConsoleTextAttribute(hOutput, dwTextColor);
	SetConsoleCursorPosition(hOutput, txtPosition);

	char hi;
	do
	{
		GetKeyboardInput(REPEAT);

		hi = (char)InputRecord.Event.KeyEvent.uChar.AsciiChar;

		cout<<hi;
		/*
		switch(kb.dwKeyPressed)
		{
		case VK_PRIOR:
			Index--;
			break;
		default:
			break;
		}

		Buffer[Index++] = (int)input.Event.KeyEvent.uChar.AsciiChar*/

	}while(InputRecord.Event.KeyEvent.wVirtualKeyCode != VK_RETURN);
}

#endif