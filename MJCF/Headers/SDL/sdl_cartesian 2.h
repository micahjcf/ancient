class SDL_CartesianGraph
{
public:
	SDL_CartesianGraph();
	~SDL_CartesianGraph();

	// seperate this out from graph setup and "graphics" setup parameters into 2 functions
	// ^^^ nevermind that.. just call it something else
	void SetupGraph(double, double, double, double, COORD, COORD);

	BOOL PointToPixel(double x, double y, COORD*, bool);
	BOOL SDL_CartesianGraph::PixelToPoint(SHORT, SHORT, double*, double*);

	void plot(COORD, enum SDL_Enum::PointStyles, Uint32);	//make me private

	BOOL PointOK(COORD);

	void Draw();

	void DrawFunction(pRetArgFunc);

	//void DrawAsInverted();   f-1()
	//void Normalize()		new dim = (ymax + abs(ymin)) * size.X   /over/   size.Y\

//private:
	double Xmin, Xmax;
	double Ymin, Ymax;
	COORD Size;		// in pixels
	COORD Position;
	double originX, originY;
	BYTE	AxesVisible;
	BYTE	TicksVisible; //The number of pixels, 0 for invisible
	BYTE	GridVisible;
	BYTE	reserved;

	SDL_Surface*	graph;
};