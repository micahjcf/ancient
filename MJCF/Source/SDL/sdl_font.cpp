#include <windows.h>

#include <debug.h>
#include <Console\stdcon.h>

#include <filepath.h>

#include <SDL.h>

#include <sdl_common.h>

SDL_TextGrid::SDL_TextGrid() : font(NULL)
{
}

SDL_TextGrid::~SDL_TextGrid()
{
	SDL_FreeSurface(font);
}

BOOL SDL_TextGrid::init(const char* font_file)
{
	ASSERT( font == NULL );

	if ( NULL == (font = SDL_LoadBMP(font_file)) ) {
		SDL_ERROR();
		return FALSE;
	}

	// We don't want a black box with white text, just the text
	SDL_SetColorKey(font, SDL_SRCCOLORKEY, 0/*black*/);

	cur_pos.X = 0;
	cur_pos.Y = 0;

	BITMAPINFOHEADER bmih;
	DWORD n;

	HANDLE file = CreateFile(font_file, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, NULL, NULL); // Shouldn't ever fail

	SetFilePointer(file, sizeof(BITMAPFILEHEADER), NULL, FILE_BEGIN); // skip over file header

	ReadFile(file, &bmih, sizeof(BITMAPINFOHEADER), &n, NULL);

	font_size.X = (SHORT)((bmih.biWidth + 1) / 16) - 1;
	font_size.Y = (SHORT)((bmih.biHeight + 1) / 16) - 1;

	max_pos.X = SCREEN_WIDTH / (font_size.X + 1);
	max_pos.Y = SCREEN_HEIGHT / (font_size.Y + 1);

	return TRUE;
}

void SDL_TextGrid::out(const char* sz)
{
	for( int n = 0; sz[n]; n++)
		put_char( sz[n] );

	//SDL_Flip(sdl_screen);
}

void SDL_TextGrid::out(const char c)
{
	put_char( c );

	//SDL_Flip(sdl_screen);
}

void SDL_TextGrid::text(COORD pos, const char* sz)
{
	cur_pos = pos;

	out(sz);
}

void SDL_TextGrid::put_char(BYTE c)
{
	ASSERT( font != NULL );

	SDL_Rect draw_at;
	SDL_Rect index;

	// clip cursor position
	if( cur_pos.X >= max_pos.X )
	{
		cur_pos.X = 0;
		cur_pos.Y++;
	}
	cur_pos.Y %= max_pos.Y;

	if( c == '\n' ) // 0x0A "newline"
	{
		cur_pos.X = 0;
		cur_pos.Y++;

		return;
	}

	//X and Y to blit to on sdl_screen
	draw_at.x = ((font_size.X + 1) * cur_pos.X);
	draw_at.y = ((font_size.Y + 1) * cur_pos.Y);
	draw_at.w = 0; //ignore
	draw_at.h = 0; //ignore

	index.w = font_size.X;
	index.h = font_size.Y;

	index.x = ((c & 0x0F) * (font_size.X + 1));
	index.y = ((c >> 4) * (font_size.Y + 1));

	SDL_BlitSurface(font, &index, sdl_screen, &draw_at);

	cur_pos.X++;
}