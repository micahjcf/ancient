#ifndef MJCF_GRAPHICS
#define MJCF_GRAPHICS

#define BORDER_DOUBLE		1
#define BORDER_SKINNY		2
#define BORDER_HALFBLOCKS	3

void ScreenDissolve(char Char, COLOR Color, int SleepTime);

namespace ConsoleDraw
{
	void inline HorizLine(COORD pos, int len, char Char, COLOR Color) {
		DWORD n;
		FillConsoleOutputAttribute(hStdOutput, Color, len, pos, &n);
		FillConsoleOutputCharacter(hStdOutput, Char, len, pos, &n);
	}

	void VertLine(COORD pos, int len, char Char, COLOR Color);
	void Box(int xLeft, int yTop, int Width, int Height, char Border, COLOR Color);
	void CenterBox(int Width, int Height, char Border, COLOR Color);
	void BorderBox(int xLeft, int yTop, int Width, int Height, COLOR Color, int BorderType);
	void CenterBorderBox(int Width, int Height, COLOR Color, int BorderType);

	void inline Rectangle(SMALL_RECT sr, char Char, COLOR Color) {
		Box(sr.Left, sr.Top, sr.Right - sr.Left + 1, sr.Bottom - sr.Top + 1, Char, Color);
	}

	void FillRectangle(SMALL_RECT sr, char Char, COLOR Color);

	void inline Line(BAR bar, char Char, COLOR Color) {
		DWORD n;
		FillConsoleOutputAttribute(hStdOutput, Color, bar.Right - bar.Left + 1, coord(bar.Left, bar.Y), &n);
		FillConsoleOutputCharacter(hStdOutput, Char, bar.Right - bar.Left + 1, coord(bar.Left, bar.Y), &n);
	}
}

BOOL COORDOverRect(COORD, SMALL_RECT);
BOOL COORDOverBar(COORD, BAR);

void plot_point(unsigned x, unsigned y, char c = (char)0xDB, COLOR color = White);

void rasterCircle(COORD origin, int radius, char c = (char)0xDB, COLOR color = White);
void line(COORD, COORD, char = (char)0xDB, COLOR color = White);

#endif