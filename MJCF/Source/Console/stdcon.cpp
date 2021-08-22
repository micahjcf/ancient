#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <Console\stdcon.h>

HWND hThisWindow = GetConsoleWindow();

bool operator== (SMALL_RECT l, SMALL_RECT r) {
	return(l.Left == r.Left && l.Top == r.Top && l.Right == r.Right && l.Bottom == r.Bottom);
}

bool operator== (BAR l, BAR r) {
	return(l.Left == r.Left && l.Right == r.Right && l.Y == r.Y);
}

bool operator== (COORD l, COORD r) {
	return(l.X == r.X && l.Y == r.Y);
}

bool operator!= (COORD l, COORD r) {
	return(l.X != r.X && l.Y != r.Y);
}

COORD operator-(COORD c) {
	return coord(-c.X, -c.Y);
}

COORD operator+(COORD l, COORD r) {
	return coord(l.X + r.X, l.Y + r.Y);
}

COORD operator-(COORD l, COORD r) {
	return coord(r.X - l.X, r.Y - l.Y);
}

const COORD& operator+=(COORD &l, COORD r) {
	l.X += r.X;
	l.Y += r.Y;
	return l;
}

const COORD& operator-=(COORD &l, COORD r) {
	r.X -= l.X;
	r.Y -= l.Y;
	return l;
}

std::ostream& operator << (std::ostream& s, COORD& c) {
	s << '(' << c.X <<',' <<c.Y <<')';

	return s;
}

std::ostream& operator << (std::ostream& s, BAR& b) {
	s << "{" << b.Y <<"}|[" <<b.Left <<',' <<b.Right <<']';  //{Y}|[L,R]

	return s;
}

void ClrScrn(char Char, COLOR Color)
{
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	DWORD n, len;

	GetConsoleScreenBufferInfo(hStdOutput, &ConsoleInfo);
	len = (ConsoleInfo.srWindow.Right + 1) * (ConsoleInfo.srWindow.Bottom + 1);

	FillConsoleOutputCharacter(hStdOutput, Char, len, coord(0, 0), &n);
	FillConsoleOutputAttribute(hStdOutput, Color, len, coord(0, 0), &n);
	SetConsoleCursorPosition(hStdOutput, coord(0, 0));
}

COORD GetCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	GetConsoleScreenBufferInfo(hStdOutput, &ConsoleInfo);
	return ConsoleInfo.dwCursorPosition;
}

COORD GetPrevCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;

	GetConsoleScreenBufferInfo(hStdOutput, &ConsoleInfo);

	if(ConsoleInfo.dwCursorPosition.X == 0 && ConsoleInfo.dwCursorPosition.Y == 0)
		return coord(0, 0);

	if(ConsoleInfo.dwCursorPosition.X == 0)
	{
		ConsoleInfo.dwCursorPosition.X = ConsoleInfo.srWindow.Right;
		ConsoleInfo.dwCursorPosition.Y--;
	}
	else
		ConsoleInfo.dwCursorPosition.X--;

	return ConsoleInfo.dwCursorPosition;
}

void Text(COORD pos, char* Text, COLOR Color)
{
	DWORD n, len = (int)strlen(Text);
	FillConsoleOutputAttribute(hStdOutput, Color, len, pos, &n);
	WriteConsoleOutputCharacter(hStdOutput, Text, len, pos, &n);
}

void Text(COORD pos, char Char, COLOR Color)
{
	DWORD n;
	WriteConsoleOutputAttribute(hStdOutput, &Color, 1, pos, &n);
	WriteConsoleOutputCharacter(hStdOutput, &Char, 1, pos, &n);
}

void Text(COORD pos, int num, COLOR Color)
{
	DWORD n;
	SetConsoleCursorPosition(hStdOutput, pos);
	FillConsoleOutputAttribute(hStdOutput, Color, printf("%d", num), pos, &n);
}

void Text(COORD pos, double num, COLOR Color)
{
	DWORD n;
	SetConsoleCursorPosition(hStdOutput, pos);
	FillConsoleOutputAttribute(hStdOutput, Color, printf("%.2f", num), pos, &n);
}

void FillPrevLineColor(COLOR c)
{
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	DWORD n;

	GetConsoleScreenBufferInfo(hStdOutput, &ConsoleInfo);

	FillConsoleOutputAttribute(hStdOutput, c, ConsoleInfo.srWindow.Right, coord(0, ConsoleInfo.dwCursorPosition.Y - 1), &n);
}