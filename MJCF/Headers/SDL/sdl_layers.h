typedef struct _SDL_Layer
{
	SDL_Surface*	surface;
	BOOL			enabled;
} SDL_Layer;

class Layer_Manager
{
	public:
	Layer_Manager(unsigned n) : redraw(TRUE), layer_count(n)
	{
		layers = new SDL_Layer[ n ];

		blank = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0xFF0000, 0xFF00, 0xFF, 0xFF000000);

		for(int x = 0; x < SCREEN_WIDTH; x++)
		{
			for(int y = 0; y < SCREEN_HEIGHT; y++)
			{
				setpixel(x, y, 0, 0, 0, 0xFF, blank);
			}
		}
	}


	~Layer_Manager()
	{
		for(unsigned n = 0; n < layer_count; n++)
			SDL_FreeSurface(layers[n].surface);

		SDL_FreeSurface(blank);
	}

	void AddLayer(unsigned ID)
	{
		ASSERT (ID < layer_count );

		layers[ID].enabled = TRUE;

		layers[ID].surface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0xFF0000, 0xFF00, 0xFF, 0xFF000000);

		//for(int x = 0; x < 300; x++)
		//	setpixel(x, 0, 0xFF, 0x00, 0xFF, x % 0xFF, layers[ID].surface);
	}

	void SetRedraw()
	{
		redraw = TRUE;
	}

	void DrawScreen()
	{
		if( redraw == FALSE )
			return;

		SDL_Rect r;
		r.x = 0;
		r.y = 0;
		r.w = SCREEN_WIDTH;
		r.h = SCREEN_HEIGHT;

		SDL_BlitSurface(blank, &r, sdl_screen, &r);

		for(unsigned n = 0; n < layer_count; n++)
			if( layers[n].enabled )
				SDL_BlitSurface(layers[n].surface, &r, sdl_screen, &r);
		
		redraw = FALSE;

		SDL_Flip(sdl_screen);
	}
private:
	BOOL			redraw;
	SDL_Layer*		layers;
	SDL_Surface*	blank;
	DWORD			layer_count;
};