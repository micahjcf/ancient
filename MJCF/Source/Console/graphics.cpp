#include <windows.h>

#include <stdcode.h>
#include <stdcon.h>
#include <graphics.h>
#include <kataline.h>

namespace ConsoleDraw
{

void VertLine(COORD pos, int len, char Char, COLOR Color)
{
	DWORD _n;

	for(int n = pos.Y; n < pos.Y + len; n++)
	{
		FillConsoleOutputAttribute(hStdOutput, Color, 1, coord(pos.X, n), &_n);
		FillConsoleOutputCharacter(hStdOutput, Char, 1, coord(pos.X, n), &_n);
	}
}

void Box(int Left, int Top, int Width, int Height, char Char, COLOR Color)
{
	DWORD _n;

	ConsoleDraw::HorizLine(coord(Left, Top), Width, Char, Color);
	ConsoleDraw::HorizLine(coord(Left, Top + Height - 1), Width, Char, Color);

	for(int n = Top + 1; n < Top + Height - 1; n++)
	{
		FillConsoleOutputAttribute(hStdOutput, Color, 1, coord(Left,n), &_n);
		FillConsoleOutputCharacter(hStdOutput, Char, 1, coord(Left,n), &_n);

		FillConsoleOutputAttribute(hStdOutput, Color, 1, coord(Left + Width - 1,n), &_n);
		FillConsoleOutputCharacter(hStdOutput, Char, 1, coord(Left + Width - 1,n), &_n);
	}
}

void CenterBox(int Width, int Height, char Char, COLOR Color)
{
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	GetConsoleScreenBufferInfo(hStdOutput, &ConsoleInfo);

	ConsoleDraw::Box((ConsoleInfo.srWindow.Right-Width)/2, (ConsoleInfo.srWindow.Bottom-Height)/2, Width, Height, Char, Color);
}

void CenterBorderBox(int Width, int Height, COLOR Color, int BorderType)
{
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	GetConsoleScreenBufferInfo(hStdOutput, &ConsoleInfo);

	ConsoleDraw::BorderBox((ConsoleInfo.srWindow.Right-Width)/2, (ConsoleInfo.srWindow.Bottom-Height)/2, Width, Height, Color, BorderType);
}

void BorderBox(int Left, int Top, int Width, int Height, COLOR Color, int BorderType)
{
	char Border[8]; //horizontal top, horizontal bottom, vertical left, vertical right, top right, top left, bottom right, bottom left
	DWORD _n;

	if(BorderType == BORDER_SKINNY)
	{
		Border[0] = (char)196;Border[1] = (char)196;
		Border[2] = (char)179;Border[3] = (char)179;
		Border[4] = (char)218;Border[5] = (char)191;
		Border[6] = (char)192;Border[7] = (char)217;
	}
	else if (BorderType == BORDER_DOUBLE)
	{
		Border[0] = (char)205;Border[1] = (char)205;
		Border[2] = (char)186;Border[3] = (char)186;
		Border[4] = (char)201;Border[5] = (char)187;
		Border[6] = (char)200;Border[7] = (char)188;
	}
	else if (BorderType == BORDER_HALFBLOCKS)
	{
		Border[0] = (char)220;Border[1] = (char)223;
		Border[2] = (char)222;Border[3] = (char)221;
		Border[4] = (char)254;Border[5] = (char)254;
		Border[6] = (char)254;Border[7] = (char)254;
	}

	VertLine(coord(Left, Top + 1), Height - 2, Border[2], Color);
	VertLine(coord(Left + Width - 1, Top + 1), Height - 2, Border[3], Color);

	HorizLine(coord(Left + 1, Top), Width - 2, Border[0], Color);
	HorizLine(coord(Left + 1, Top + Height - 1), Width - 2, Border[1], Color);

	FillConsoleOutputAttribute(hStdOutput, Color, 1, coord(Left, Top), &_n);
	FillConsoleOutputCharacter(hStdOutput, Border[4], 1, coord(Left, Top), &_n);

	FillConsoleOutputAttribute(hStdOutput, Color, 1, coord(Left + Width - 1, Top), &_n);
	FillConsoleOutputCharacter(hStdOutput, Border[5], 1, coord(Left + Width - 1, Top), &_n);

	FillConsoleOutputAttribute(hStdOutput, Color, 1, coord(Left, Top + Height - 1), &_n);
	FillConsoleOutputCharacter(hStdOutput, Border[6], 1, coord(Left, Top + Height - 1), &_n);

	FillConsoleOutputAttribute(hStdOutput, Color, 1, coord(Left + Width - 1, Top + Height - 1), &_n);
	FillConsoleOutputCharacter(hStdOutput, Border[7], 1, coord(Left + Width - 1, Top + Height - 1), &_n);
}

void FillRectangle(SMALL_RECT sr, char Char, COLOR Color)
{
	DWORD _n;

	for(int n = sr.Top; n < sr.Bottom + 1; n++)
	{
		FillConsoleOutputAttribute(hStdOutput, Color, sr.Right - sr.Left + 1, coord(sr.Left, n), &_n);
		FillConsoleOutputCharacter(hStdOutput, Char, sr.Right - sr.Left + 1, coord(sr.Left, n), &_n);
	}
}

} // namespace ConsoleDraw

BOOL COORDOverRect(COORD p, SMALL_RECT sr)
{
	if(p.X >= sr.Left && p.X <= sr.Right && p.Y >= sr.Top && p.Y <= sr.Bottom)
		return TRUE;
	return FALSE;
}

BOOL COORDOverBar(COORD p, BAR b)
{
	if(p.Y == b.Y && p.X >= b.Left && p.X <= b.Right)
		return TRUE;
	return FALSE;
}

void plot_point(unsigned x, unsigned y, char c /* = (char)0xDB */, COLOR color /* = White */)
{
	if( COORDOverRect( xypoint(x, y) , gWindowRect) )
		Text(coord(x, GetConsoleSize().Y - y), c, color);
}

//http://www.codecodex.com/wiki/index.php?title=Bresenham%27s_line_algorithm
void rasterCircle(COORD origin, int radius, char c /* = (char)0xDB */, COLOR color /* = White */)
{
	int f = 1 - radius;
	int ddF_x = 0;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	Text(coord(origin.X, origin.Y + radius), c, color);
	Text(coord(origin.X, origin.Y - radius), c, color);
	Text(coord(origin.X + radius, origin.Y), c, color);
	Text(coord(origin.X - radius, origin.Y), c, color);

	while(x < y)
	{
		if(f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x + 1;
		Text(coord(origin.X + x, origin.Y + y), c, color);
		Text(coord(origin.X - x, origin.Y + y), c, color);
		Text(coord(origin.X + x, origin.Y - y), c, color);
		Text(coord(origin.X - x, origin.Y - y), c, color);
		Text(coord(origin.X + y, origin.Y + x), c, color);
		Text(coord(origin.X - y, origin.Y + x), c, color);
		Text(coord(origin.X + y, origin.Y - x), c, color);
		Text(coord(origin.X - y, origin.Y - x), c, color);
	}
}

void line(COORD p1, COORD p2, char c /* = (char)0xDB */, COLOR color /* = White */)
{
	signed	dy = p2.Y - p1.Y,
			dx = p2.X - p1.X,
			e  = 0;

	if(dx < 0) //make sure p1 is on the left, p2 is on the right
	{
		COORD t = p1;
		p1 = p2;
		p2 = t;

		dx = -dx;
		dy = -dy;
	}

	if( dx == 0 ) // verticle line (no slope)
	{
		for(int n = min(p1.Y, p2.Y); n <= max(p1.Y, p2.Y); n++)
			Text(coord(p1.X, n), c, color);
		return;
	}
	else if ( dy == 0 ) // horizontal line
	{
		for(int n = p1.X; n <= p2.X; n++)
			Text(coord(n, p1.Y), c, color);
		return;
	}

	int inc, guess;

	if(dx >= abs(dy)) //x-incremental
	{
		inc = p1.X;
		guess = p1.Y;

		do {
			Text(coord(inc++, guess), c, color);

			e += dy;

			if(dy >= 0) { //positive slope
				if((e << 1) >= dx)
				{
					guess++;
					e -= dx;
				}
			} else {		// negative slope
				if( -(e << 1) >= dx)
				{
					guess--;
					e += dx;
				}
			}
		}while(inc <= p2.X);
	}
	else
	{
		inc = p1.Y;
		guess = p1.X;

		if( dy > 0 ) //y-incremental; large positive slope
		{
			do {
				Text(coord(guess, inc++), c, color);

				e += dx;

				if((e << 1) >= dy)
				{
					guess++;
					e -= dy;
				}
			}while(inc <= p2.Y);
		}
		else //y-incremental; large negative slope
		{

			do {
				Text(coord(guess, inc--), c, color);
				e += dx;

				if( -(e << 1) <= dy )
				{
					guess++;
					e += dy;
				}
			}while(inc >= p2.Y);
		}
	}
}
