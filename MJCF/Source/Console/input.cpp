#include <windows.h>
#include <iostream>

using std::string;

#include <Console\stdcon.h>
#include <Console\cursor_mouse.h>
#include <Console\keyboard.h>

#include <Console\input.h>

BOOL Input(unsigned long& Number, DWORD Flags, UINT MaxLength, COLOR color, char EmptyChar)
{
	// unsigned long =	0 to 4,294,967,295
	// Input() =		0 to   999,999,999
	if(MaxLength > 9)
		MaxLength = 9;

	int Buffer[9], len = 0;
	COORD pos;

	CONSOLE_CURSOR_INFO PrevCursorSettings, CursorSettings = {100, true};

	GetConsoleCursorInfo(hStdOutput, &PrevCursorSettings);
	SetConsoleCursorInfo(hStdOutput, &CursorSettings);

	DWORD n;
	FillConsoleOutputAttribute(hStdOutput, color, MaxLength, GetCursorPosition(), &n);
	FillConsoleOutputCharacter(hStdOutput, EmptyChar, MaxLength, GetCursorPosition(), &n);

	KEYBOARD Keyboard;

	do
	{
		if(!Keyboard.GetInput())
			continue;

		if(Keyboard.Pressed(K_ENTER))
		{
			if(! len)
			{
				SetConsoleCursorInfo(hStdOutput, &PrevCursorSettings);
				return FALSE;
			}
			else
				break;
		}

		if(Keyboard.Pressed(K_BACKSPACE) && len)
		{
			pos = GetCursorPosition();
			pos.X--;
			SetConsoleCursorPosition(hStdOutput, pos);

			FillConsoleOutputAttribute(hStdOutput, color, 1, GetCursorPosition(), &n);
			FillConsoleOutputCharacter(hStdOutput, EmptyChar, 1, GetCursorPosition(), &n);

			len--;
			continue;
		}

		if(Keyboard.Pressed(K_ESCAPE))
		{
			pos = GetCursorPosition();
			pos.X -= len;
			SetConsoleCursorPosition(hStdOutput, pos);

			FillConsoleOutputAttribute(hStdOutput, color, MaxLength, GetCursorPosition(), &n);
			FillConsoleOutputCharacter(hStdOutput, EmptyChar, MaxLength, GetCursorPosition(), &n);

			len = 0;
			continue;
		}

		if(len == MaxLength || !isdigit(Keyboard.AsciiKey))
			continue;

		int i = Buffer[len++] = (int)Keyboard.AsciiKey & 0xCF;

		if(Flags & INPUT_HIDE)
			continue;

		pos = GetCursorPosition();
		pos.X++;

		FillConsoleOutputAttribute(hStdOutput, color, 1, GetCursorPosition(), &n);

		if(Flags & INPUT_PASSWORD)
			FillConsoleOutputCharacter(hStdOutput, '*', 1, GetCursorPosition(), &n);

		if(Flags & INPUT_HIDE)
			continue;

		FillConsoleOutputCharacter(hStdOutput, Keyboard.AsciiKey, 1, GetCursorPosition(), &n);

		SetConsoleCursorPosition(hStdOutput, pos);

	}while(true);

	Number = 0;

	for(int hedge = 1, n = len - 1; n >- 1; n--, hedge *= 10)
		Number += Buffer[n] * hedge;

	SetConsoleCursorInfo(hStdOutput, &PrevCursorSettings);

	return TRUE;
}

//Max length of input is 63 characters
BOOL Input(string& st, DWORD Flags, UINT MaxLength, COLOR color, char EmptyChar)
{
	if(MaxLength > 63)
		MaxLength = 63;

	char* Buffer = new char[ MaxLength + 1 ];
	int len = 0;
	COORD pos;

	CONSOLE_CURSOR_INFO PrevCursorSettings, CursorSettings = {100, true};

	GetConsoleCursorInfo(hStdOutput, &PrevCursorSettings);
	SetConsoleCursorInfo(hStdOutput, &CursorSettings);

	DWORD n;
	FillConsoleOutputAttribute(hStdOutput, color, MaxLength, GetCursorPosition(), &n);
	FillConsoleOutputCharacter(hStdOutput, EmptyChar, MaxLength, GetCursorPosition(), &n);

	KEYBOARD Keyboard;

	do
	{
		if(!Keyboard.GetInput())
			continue;

		if(Keyboard.Pressed(K_ENTER))
		{
			if(! len)
			{
				delete[] Buffer;
				SetConsoleCursorInfo(hStdOutput, &PrevCursorSettings);

				return FALSE;
			}
			else
				break;
		}

		if(Keyboard.Pressed(K_BACKSPACE) && len)
		{
			pos = GetCursorPosition();
			pos.X--;
			SetConsoleCursorPosition(hStdOutput, pos);

			FillConsoleOutputAttribute(hStdOutput, color, 1, GetCursorPosition(), &n);
			FillConsoleOutputCharacter(hStdOutput, EmptyChar, 1, GetCursorPosition(), &n);

			len--;
			continue;
		}

		if(Keyboard.Pressed(K_ESCAPE))
		{
			pos = GetCursorPosition();
			pos.X -= len;
			SetConsoleCursorPosition(hStdOutput, pos);

			FillConsoleOutputAttribute(hStdOutput, color, MaxLength, GetCursorPosition(), &n);
			FillConsoleOutputCharacter(hStdOutput, EmptyChar, MaxLength, GetCursorPosition(), &n);

			len = 0;
			continue;
		}

		if(len == MaxLength)
			continue;

		if(Flags & INPUT_SPACE && Keyboard.AsciiKey == ' ')
			goto goodkey;

		if(Flags & INPUT_NUM)
			if((int)Keyboard.AsciiKey >= 48 && (int)Keyboard.AsciiKey <= 57)
				goto goodkey;

		if(Flags & INPUT_ALPHA)
		{
			if(Keyboard.AsciiKey & 0x20)
			{
				if((int)Keyboard.AsciiKey >= 97 && (int)Keyboard.AsciiKey <= 122)
					goto goodkey;
			}
			else
			{
				if((int)Keyboard.AsciiKey >= 65 && (int)Keyboard.AsciiKey <= 90)
					goto goodkey;
			}
		}

		if(Flags & INPUT_ALL)
			if((int)Keyboard.AsciiKey >= 33 && (int)Keyboard.AsciiKey <= 126)
				goto goodkey;

		continue;

goodkey:

		Buffer[ len++ ] = Keyboard.AsciiKey;

		if(Flags & INPUT_HIDE)
			continue;

		pos = GetCursorPosition();
		pos.X++;

		FillConsoleOutputAttribute(hStdOutput, color, 1, GetCursorPosition(), &n);

		if(Flags & INPUT_PASSWORD)
			FillConsoleOutputCharacter(hStdOutput, '*', 1, GetCursorPosition(), &n);

		if(Flags & INPUT_HIDE)
			continue;

		FillConsoleOutputCharacter(hStdOutput, Keyboard.AsciiKey, 1, GetCursorPosition(), &n);

		SetConsoleCursorPosition(hStdOutput, pos);
	}while(true);

	Buffer[len] = '\0';

	st = Buffer;

	SetConsoleCursorInfo(hStdOutput, &PrevCursorSettings);

	delete[] Buffer;

	return TRUE;
}