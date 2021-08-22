void putpixel(SHORT, SHORT, Uint32, SDL_Surface* = sdl_screen);
void putpixel(SHORT x, SHORT y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Surface* surface = sdl_screen);
void setpixel(SHORT, SHORT, Uint32, SDL_Surface* = sdl_screen);
void setpixel(SHORT x, SHORT y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Surface* surface = sdl_screen);
Uint32 getpixel(SHORT x, SHORT y, SDL_Surface* surface);

void line(COORD p1, COORD p2, Uint32, SDL_Surface*);
void rasterCircle(COORD, int, Uint32, SDL_Surface*);