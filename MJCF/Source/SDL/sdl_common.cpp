#include <SDL.h>

#include <sdl_common.h>

void Magnifier(COORD offset)
{
	int mx, my;
	SDL_GetMouseState(&mx, &my);

	Uint32 color;

	for(unsigned y = 0; y < 40; y++)
	{
		for(unsigned x = 0; x < 40; x++)
		{
			if( mx == x + mx - 20 && my == y + my - 20 )
				color = SDL_MapRGB(sdl_screen->format, _Red);
			else
				color = getpixel(x + mx - 20, y + my - 20, sdl_screen);

			for(unsigned i = 0; i < 5; i++)
			{
				setpixel(offset.X + x*5  , offset.Y + y*5+i, color, sdl_screen);
				setpixel(offset.X + x*5+1, offset.Y + y*5+i, color, sdl_screen);
				setpixel(offset.X + x*5+2, offset.Y + y*5+i, color, sdl_screen);
				setpixel(offset.X + x*5+3, offset.Y + y*5+i, color, sdl_screen);
				setpixel(offset.X + x*5+4, offset.Y + y*5+i, color, sdl_screen);
			}
		}
	}

	//Show mouse coordinates
	//char st[12]; // "(xxxx,yyyy)\0"

	//sprintf(st, "(%d,%d)", mx, my);

	//tg.text(coord(0, 0), st);
}