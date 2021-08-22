#ifndef MJCF_SCREEN_BUFFER
#define MJCF_SCREEN_BUFFER

//************************************************
//
// ScrnShadow objects are used by Console interface
// objects to preserve the characters and colors that
// they may cover up during their use.  They are the
//  object's "shadows"
//
//************************************************

class ScrnShadow
{
public:
	ScrnShadow() : pGFX(NULL) {}
	~ScrnShadow() {delete[] pGFX;}

	void GetFromScreen(SMALL_RECT);

	void Draw() {
		WriteConsoleOutput(hStdOutput, pGFX, Size, coord(0,0), &Edges);
	}

	CHAR_INFO*	pGFX;
	SMALL_RECT	Edges;
	COORD		Size;

};

/*
typedef class _ScrnBuffer : public ScrnShadow
{
public:
	_ScrnBuffer() {pGFX = NULL;}

	_ScrnBuffer(int, int);

	~_ScrnBuffer() {delete[] pGFX;}

	// Graphics array setup funcions
	void SetSize(int X, int Y);
	void GetFromScreen(SMALL_RECT);

	// Set the on screen position
	//void SetEdges(int Left, int Top, int Right, int Bottom){Edges=ReturnRect(Left,Top,Right,Bottom);}
	void Place(int Left, int Top){
		Edges = rect(Left, Top, Left + Size.X, Top + Size.Y);
	}

	// Full the buffer with graphics
	void FillBuffer(char, COLOR);
	void FillFromScreen(){
		ReadConsoleOutput(hOutput, pGFX, Size, coord(0,0), &Edges);
	}

	// Move it around on screen
	void MoveEdges(int xMove, int yMove);

	// Draw it on the screen
	void Draw(const COORD IndexCoords = coord(0,0)){
		WriteConsoleOutput(hOutput, pGFX, Size, IndexCoords, &Edges);
	}

	void DrawAt(int Left, int Top, const COORD);

	CHAR_INFO*	pGFX;
	SMALL_RECT	Edges;
	COORD		Size;

} ScrnBuffer, *pScrnBuffer;
*/

#endif
