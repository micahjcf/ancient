#include <SDL.h>

#include <type.h>

#include <sdl_common.h>

SDL_Surface *sdl_screen;

#if (SCREEN_BPP != 8) && (SCREEN_BPP != 16) && (SCREEN_BPP != 32)
#error setting for SCREEN_BPP not allowed.  Use 8, 16 or 32
#endif

// Used only in this module
void _putp(SHORT x, SHORT y, Uint32 pixel, SDL_Surface* surface)
{
#if (SCREEN_BPP == 8)
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x;
#endif
#if (SCREEN_BPP == 16)
	Uint16 *p = (Uint16 *)surface->pixels + y * surface->pitch / 2+ x;
#endif
#if (SCREEN_BPP == 32)
	Uint32 *p = (Uint32 *)surface->pixels + y * surface->pitch / 4 + x;
#endif

	if(x >= 0 && y >=0 && x < surface->w && y < surface->h)
		*p = pixel;
#ifdef _DEBUG
	else
	printf("_putp() : (%d, %d) is out of bounds\n", x, y);
#endif
}

void setpixel(SHORT x, SHORT y, Uint32 pixel, SDL_Surface* surface)
{
	_putp(x, y, pixel, surface);
}

void setpixel(SHORT x, SHORT y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Surface* surface)
{
	_putp(x, y, SDL_MapRGBA(surface->format, r, g, b, a), surface);
}

//WARNING: THIS ASSUMES THE BITS PER PIXEL IS 32!
Uint32 getpixel(SHORT x, SHORT y, SDL_Surface* surface)
{
	if(x >= 0 && y >=0 && x < surface->w && y < surface->h)
		return *((Uint32 *)surface->pixels + y * surface->pitch / 4 + x);
	else
	//printf("getpixel() : (%d, %d) is out of bounds\n", x, y);
	return rand();
}

void line(COORD p1, COORD p2, Uint32 color, SDL_Surface* surface)
{
	signed	dy = p2.Y - p1.Y,
			dx = p2.X - p1.X,
			e  = 0;

	if(dx < 0) // make sure p1 is on the left, p2 is on the right
	{
		COORD t = p1;
		p1 = p2;
		p2 = t;

		dx = -dx;
		dy = -dy;
	}

	if( dx == 0 ) { // verticle line
		for(int n = min(p1.Y, p2.Y); n <= max(p1.Y, p2.Y); n++)
			_putp(p1.X, n, color, surface);
		return;
	}
	else if ( dy == 0 ) { // horizontal line
		for(int n = p1.X; n <= p2.X; n++)
			_putp(n, p1.Y, color, surface);
		return;
	}

	int inc, guess;

	if(dx >= abs(dy)) // x-incremental
	{
		inc = p1.X;
		guess = p1.Y;

		do {
			_putp(inc++, guess, color, surface);

			e += dy;

			if(dy >= 0) { // positive slope
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

		if( dy > 0 ) // y-incremental; large positive slope
		{
			do {
				_putp(guess, inc++, color, surface);

				e += dx;

				if((e << 1) >= dy)
				{
					guess++;
					e -= dy;
				}
			}while(inc <= p2.Y);
		}
		else // y-incremental; large negative slope
		{

			do {
				_putp(guess, inc--, color, surface);
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

//http://www.codecodex.com/wiki/index.php?title=Bresenham%27s_line_algorithm
void rasterCircle(COORD origin, int radius, Uint32 color, SDL_Surface* surface)
{
	int f = 1 - radius;
	int ddF_x = 0;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	_putp(origin.X, origin.Y + radius, color, surface);
	_putp(origin.X, origin.Y - radius, color, surface);
	_putp(origin.X + radius, origin.Y, color, surface);
	_putp(origin.X - radius, origin.Y, color, surface);

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
		_putp(origin.X + x, origin.Y + y, color, surface);
		_putp(origin.X - x, origin.Y + y, color, surface);
		_putp(origin.X + x, origin.Y - y, color, surface);
		_putp(origin.X - x, origin.Y - y, color, surface);
		_putp(origin.X + y, origin.Y + x, color, surface);
		_putp(origin.X - y, origin.Y + x, color, surface);
		_putp(origin.X + y, origin.Y - x, color, surface);
		_putp(origin.X - y, origin.Y - x, color, surface);
	}
}