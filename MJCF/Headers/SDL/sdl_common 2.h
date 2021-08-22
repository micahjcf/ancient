#include <type.h>

#include <debug.h>

#include <stdcon.h>

#ifndef SCREEN_WIDTH
#error	SCREEN_WIDTH undefined
#endif
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT undefined
#endif
#ifndef SCREEN_BPP
#error	SCREEN_BPP undefined
#endif

#define SCREEN_XMAX	(SCREEN_WIDTH - 1)
#define SCREEN_YMAX	(SCREEN_HEIGHT - 1)

// Only used after a failed function call of a NATIVE SDL function
#define SDL_ERROR_(l, f) printf("%d:%s() - Error w/ SDL function: \"%s\"\n", l, f, SDL_GetError())
#define SDL_ERROR() SDL_ERROR_(__LINE__, __FUNCTION__)

//#define FAILURE_BLOCK_SDL( func )	((func != NULL))
//#define FAILURE_BLOCK( func )		(((func) != FALSE) || printf("%d:%s() - %s", __LINE__, __FUNCTION__, GetLastErrorMsg()) )

namespace SDL_Enum {
	enum PointStyles {SOLID_LINE, DOTTED_LINE, POINT_DOT, POINT_PLUS, POINT_SQUARE, POINT_X, POINT_DIAMOND};
	//enum Colors {White, Black, Red, Blue, Green, Yellow, Purple, Teal};
};

// obnoxious enum warning
#pragma warning(disable:4482)

#define _White	0xFF, 0xFF, 0xFF
#define _Black	0x0, 0x0, 0x0
#define _Red	0xFF, 0x0, 0x0
#define _Blue	0x0, 0x0, 0xFF
#define _Green	0x0, 0xFF, 0x0
#define _Yellow	0xFF, 0xFF, 0x0
#define _Purple	0xFF, 0x0, 0xFF
#define _Teal	0x0, 0xFF, 0xFF

//Cartesian graph colors
#define BG_COLOR	10, 42, 27
#define AXES_COLOR	0xFF, 0xFF, 0xFF, 0x33
#define TICK_COLOR	8, 138, 133
#define GRID_COLOR
#define DOT_COLOR	0x0, 0xFF, 0xFF		//teal
#define LINE_COLOR	0xAA, 0xCC, 0x11

extern SDL_Surface *sdl_screen;

typedef double (*pRetArgFunc)(double);

//BOOL Input(string* st, COORD p, 
void Magnifier(COORD offset);

#include <sdl_basic.h>
#include <sdl_layers.h>
#include <sdl_font.h>
#include <sdl_wavrender.h>
#include <sdl_cartesian.h>