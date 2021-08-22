#ifndef MJCF_STDCON
#define MJCF_STDCON

#define hStdInput GetStdHandle(STD_INPUT_HANDLE)
#define hStdOutput GetStdHandle(STD_OUTPUT_HANDLE)

extern HWND hThisWindow;

typedef struct _BAR {
	SHORT Y;
	SHORT Left;
	SHORT Right;
} BAR, *pBAR;

typedef COORD XYPOINT;

__forceinline SMALL_RECT rect(int Left, int Top, int Right, int Bottom) {
	SMALL_RECT sr = {Left, Top, Right, Bottom};
	return sr;
}

__forceinline BAR bar(int Y, int Left, int Right) {
	BAR b = {Y, Left, Right};
	return b;
}

__forceinline COORD coord(int X, int Y) {
	COORD C = {X,Y};
	return C;
}

__forceinline XYPOINT xypoint(int X, int Y) {
	XYPOINT p = {X,Y};
	return p;
}

bool operator== (SMALL_RECT, SMALL_RECT);
bool operator== (BAR, BAR);
bool operator== (COORD, COORD);
bool operator!= (COORD l, COORD r);
COORD operator-(COORD c); //negation
COORD operator+(COORD l, COORD r);
COORD operator-(COORD l, COORD r);
const COORD& operator+=(COORD &l, COORD r);
const COORD& operator-=(COORD &l, COORD r);

#include <iostream>

std::ostream& operator << (std::ostream&, COORD&);
std::ostream& operator << (std::ostream&, BAR&);

typedef WORD	COLOR; //0x00FB F=foreground, B=background

#define Black		((COLOR)(0))
#define Red			((COLOR)(FOREGROUND_RED))
#define Green		((COLOR)(FOREGROUND_GREEN))
#define Blue		((COLOR)(FOREGROUND_BLUE))
#define Grey		((COLOR)(FOREGROUND_INTENSITY))
#define Red_I		((COLOR)(FOREGROUND_RED | FOREGROUND_INTENSITY))
#define Green_I		((COLOR)(FOREGROUND_GREEN | FOREGROUND_INTENSITY))
#define Blue_I		((COLOR)(FOREGROUND_BLUE | FOREGROUND_INTENSITY))
#define White		((COLOR)(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE))
#define White_I		((COLOR)(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY))
#define Yellow		((COLOR)(FOREGROUND_RED | FOREGROUND_GREEN))
#define Yellow_I	((COLOR)(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY))
#define Purple		((COLOR)(FOREGROUND_RED | FOREGROUND_BLUE))
#define Purple_I	((COLOR)(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY))
#define Cyan		((COLOR)(FOREGROUND_GREEN | FOREGROUND_BLUE))
#define Cyan_I		((COLOR)(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY))

#define B_Black		((COLOR)(0))
#define B_Red		((COLOR)(BACKGROUND_RED))
#define B_Green		((COLOR)(BACKGROUND_GREEN))
#define B_Blue		((COLOR)(BACKGROUND_BLUE))
#define B_Grey		((COLOR)(BACKGROUND_INTENSITY))
#define B_Red_I		((COLOR)(BACKGROUND_RED | BACKGROUND_INTENSITY))
#define B_Green_I	((COLOR)(BACKGROUND_GREEN | BACKGROUND_INTENSITY))
#define B_Blue_I	((COLOR)(BACKGROUND_BLUE | BACKGROUND_INTENSITY))
#define B_White		((COLOR)(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE))
#define B_White_I	((COLOR)(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY))
#define B_Yellow	((COLOR)(BACKGROUND_RED | BACKGROUND_GREEN))
#define B_Yellow_I	((COLOR)(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY))
#define B_Purple	((COLOR)(BACKGROUND_RED | BACKGROUND_BLUE))
#define B_Purple_I	((COLOR)(BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY))
#define B_Cyan		((COLOR)(BACKGROUND_GREEN | BACKGROUND_BLUE))
#define B_Cyan_I	((COLOR)(BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY))

#define FlipFGBG(Color) (((Color & 0xFF) << 4) | ((Color & 0xFF) >> 4))
#define DeleteFG(Color) (Color & 0x00F0)
#define DeleteBG(Color) (Color & 0x000F)

void ClrScrn(char Char = ' ', COLOR Color = White_I);
COORD GetCursorPosition();
COORD GetPrevCursorPosition();

void Text(COORD pos, char* Text, COLOR Color = White);
void Text(COORD pos, char Char, COLOR Color = White);
void Text(COORD pos, int num, COLOR Color = White);
void Text(COORD pos, double num, COLOR Color = White);

void FillPrevLineColor(COLOR);

#endif