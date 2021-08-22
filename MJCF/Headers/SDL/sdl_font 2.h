class SDL_TextGrid
{
public:
	SDL_TextGrid();
	~SDL_TextGrid();

	BOOL init(const char*);

	COORD MouseToGrid(SHORT X, SHORT Y) { return coord(X / (font_size.X + 1), Y / (font_size.Y + 1)); }

	void out(const char*);
	void out(const char c);
	void text(COORD, const char*);

	void set_pos(SHORT X, SHORT Y) { cur_pos = coord(X, Y); }
	COORD pos() { return cur_pos; }

	void operator << (const char* sz) { out( sz ); } // Cannot use more than once in a single statement unlike cout.

private:
	void put_char(BYTE);

	SDL_Surface* font;
	COORD cur_pos;
	COORD font_size;
	COORD max_pos;
};
