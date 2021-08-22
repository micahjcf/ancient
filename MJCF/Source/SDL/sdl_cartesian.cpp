#include <SDL.h>

#include <type.h>

#include <sdl_common.h>

//conversion from 'double' to 'int', possible loss of data
#pragma warning(disable:4244)

SDL_CartesianGraph::SDL_CartesianGraph()
{
}

SDL_CartesianGraph::~SDL_CartesianGraph()
{
}

void SDL_CartesianGraph::SetupGraph(double xmin, double xmax, double ymin, double ymax, COORD size, COORD pos)
{
	Xmin = xmin;
	Xmax = xmax;
	Ymin = ymin;
	Ymax = ymax;
	Position = pos;

	Size = size;

	SDL_Surface* t = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, size.X, size.Y, SCREEN_BPP, 0xFF0000, 0xFF00, 0xFF, 0xFF000000);

	graph = SDL_DisplayFormatAlpha(t);

	SDL_FreeSurface(t);

	originX = (-((xmax + xmin) / 2.0)) * (Size.X / (Xmax + abs(Xmin))) + (size.X / 2.0);
	originY = (-((ymax + ymin) / 2.0)) * (Size.Y / (Ymax + abs(Ymin))) + (size.Y / 2.0);

	AxesVisible = 1;
	TicksVisible = 2;
	GridVisible = 0;

	Draw();
}

BOOL SDL_CartesianGraph::PointToPixel(double x, double y, COORD* p, bool check = true)
{
	if( check )
		if( x < Xmin || x > Xmax || y < Ymin || y > Ymax)
		{
			//printf("Point (%.2f, %.2f) is out of bounds\n", x, y);
			return FALSE;
		}

	double xscale = Size.X / (Xmax + abs(Xmin));
	double yscale = Size.Y / (Ymax + abs(Ymin));

	p->X = (short)(originX + (x * xscale));
	p->Y = (short)(originY - (y * yscale));

	return TRUE;
}

BOOL SDL_CartesianGraph::PixelToPoint(SHORT x, SHORT y, double* pX, double* pY)
{
	if( x - Position.X < 0 || x >= Size.X + Position.X || y - Position.Y < 0 || y >= Size.Y + Position.Y )
		return FALSE;

	double xscale = Size.X / (Xmax + abs(Xmin));
	double yscale = Size.Y / (Ymax + abs(Ymin));

	*pX = (-originX) + x - Position.X;
	*pX /= xscale;

	*pY = originY - y + Position.Y;
	*pY /= yscale;

	return TRUE;
}

void SDL_CartesianGraph::plot(COORD p, SDL_Enum::PointStyles type, Uint32 color)
{
	if( p.X < 0 || p.X >= graph->w || p.Y < 0 || p.Y >= graph->h )
		return;

	if( type == SDL_Enum::POINT_X || type == SDL_Enum::POINT_SQUARE )
	{
		setpixel(p.X + 1, p.Y + 1, color, graph);
		setpixel(p.X + 1, p.Y - 1, color, graph);
		setpixel(p.X - 1, p.Y + 1, color, graph);
		setpixel(p.X - 1, p.Y - 1, color, graph);
	}

	if( type == SDL_Enum::POINT_PLUS || type == SDL_Enum::POINT_DIAMOND || type == SDL_Enum::POINT_SQUARE)
	{
		setpixel(p.X + 1, p.Y, color, graph);
		setpixel(p.X, p.Y + 1, color, graph);
		setpixel(p.X - 1, p.Y, color, graph);
		setpixel(p.X, p.Y - 1, color, graph);
	}

	if( type != SDL_Enum::POINT_SQUARE && type != SDL_Enum::POINT_DIAMOND && type != SDL_Enum::POINT_SQUARE)
		setpixel(p.X, p.Y, color, graph);
}

void SDL_CartesianGraph::Draw()
{
	int x, y;
	for(x = 0; x < Size.X; x++)
		for(y = 0; y < Size.Y; y++)
			setpixel(x, y, SDL_MapRGB(graph->format, BG_COLOR), graph);

	if( AxesVisible )
	{
		for(x = 0; x < Size.X; x++)
			setpixel(x, (short)originY, AXES_COLOR, graph);

		for(y = 0; y < Size.Y; y++)
			setpixel((short)originX, y, AXES_COLOR, graph);
	}

	if( TicksVisible )
	{
		COORD p;
		double d, d2;

		printf("ticks every: %f\n", ((Xmax + abs(Xmin)) / 20));

		//X axis ticks
		for(d = ((Xmax + abs(Xmin)) / 20); d < Xmax; d += ((Xmax + abs(Xmin)) / 20))
		{
			PointToPixel(d, 0, &p);

			p.Y -= TicksVisible;
			for(x = 0; x < (2 * TicksVisible + 1); x++, p.Y++)
				plot(p, SDL_Enum::PointStyles::POINT_DOT, SDL_MapRGB(graph->format, TICK_COLOR));

			d2 = -d; //flip over Y axis and do left side
			PointToPixel(d2, 0, &p);

			p.Y -= TicksVisible;
			for(x = 0; x < (2 * TicksVisible + 1); x++, p.Y++)
				plot(p, SDL_Enum::PointStyles::POINT_DOT, SDL_MapRGB(graph->format, TICK_COLOR));
		}

		//Y axis ticks
		for(d = ((Ymax + abs(Ymin)) / 20); d < Ymax; d += ((Ymax + abs(Ymin)) / 20))
		{
			PointToPixel(0, d, &p);

			p.X -= TicksVisible;
			for(x = 0; x < (2 * TicksVisible + 1); x++, p.X++)
				plot(p, SDL_Enum::PointStyles::POINT_DOT, SDL_MapRGB(graph->format, TICK_COLOR));

			d2 = -d; //flip over X axis and do botton side
			PointToPixel(0, d2, &p);

			p.X -= TicksVisible;
			for(x = 0; x < (2 * TicksVisible + 1); x++, p.X++)
				plot(p, SDL_Enum::PointStyles::POINT_DOT, SDL_MapRGB(graph->format, TICK_COLOR));
		}
	}

	if( GridVisible )
	{
	}

	SDL_Rect src, dest;
	src.h = dest.h = Size.Y;
	src.w = dest.w = Size.X;
	src.x = 0;
	src.y = 0;
	dest.x = Position.X;
	dest.y = Position.Y;

	SDL_BlitSurface(graph, &src, sdl_screen, &dest);

	SDL_Flip(sdl_screen);
}

BOOL SDL_CartesianGraph::PointOK(COORD p)
{
	if(p.X >= 0 && p.X < graph->w && p.Y >= 0 && p.Y < graph->h)
		return TRUE;
	return FALSE;
}

void SDL_CartesianGraph::DrawFunction(pRetArgFunc function)
{
	COORD p1, p2;
	double n, step = .25;//(abs(Xmin) + Xmax) / 100;
	unsigned i = 0;

	PointToPixel(Xmin, function(Xmin), &p1, false);

	do {
		n = Xmin + (i * step);

		PointToPixel(n, function(n), &p2, false);

		if(PointOK(p1) || PointOK(p2))
			line(p1, p2, SDL_MapRGB(graph->format, LINE_COLOR), graph);

		p1 = p2;
		i++;
	}while(n < Xmax);

	SDL_Rect src, dest;
	src.h = dest.h = Size.Y;
	src.w = dest.w = Size.X;
	src.x = 0;
	src.y = 0;
	dest.x = Position.X;
	dest.y = Position.Y;

	SDL_BlitSurface(graph, &src, sdl_screen, &dest);

	SDL_Flip(sdl_screen);
}