#include <windows.h>

#include <Console\stdcon.h>

#include <Console\scrnbuffer.h>

void ScrnShadow::GetFromScreen(SMALL_RECT rect)
{
	Size = coord(rect.Right - rect.Left + 1, rect.Bottom - rect.Top + 1);
	Edges = rect;

	if(pGFX)
		delete[] pGFX;

	pGFX = new CHAR_INFO[Size.X * Size.Y];

	ReadConsoleOutput(hStdOutput, pGFX, Size, coord(0,0), &Edges);
}

/*
_ScrnBuffer::_ScrnBuffer(int X, int Y)
{
	pGFX = new CHAR_INFO[X * Y];
	memset(pGFX, 0, sizeof(X * Y));

	Size = coord(X,Y);
}

void _ScrnBuffer::SetSize(int X, int Y)
{
	if(pGFX)
		delete[] pGFX;

	pGFX = new CHAR_INFO[X * Y];
	memset(pGFX, 0, (X * Y));

	Size = coord(X, Y);
}

void _ScrnBuffer::GetFromScreen(SMALL_RECT srEdges)
{
	Size = coord(srEdges.Right - srEdges.Left, srEdges.Bottom-srEdges.Top);
	Edges = srEdges;

	if(pGFX)
		delete[] pGFX;

	pGFX = new CHAR_INFO[Size.X * Size.Y];

	ReadConsoleOutput(hOutput, pGFX, Size, coord(0,0), &Edges);
}

void _ScrnBuffer::FillBuffer(char Char, COLOR Color)
{
	for(int y = 0; y < Size.Y; y++)
	{
		for(int x = 0; x < Size.X; x++)
		{
			pGFX[x + y * Size.X].Char.AsciiChar = Char;
			pGFX[x + y * Size.X].Attributes = Color;
		}
	}
}

void _ScrnBuffer::MoveEdges(int xMove, int yMove)
{
	Edges.Left += xMove;
	Edges.Right += xMove;
	Edges.Top += yMove;
	Edges.Bottom += yMove;

	if(Edges.Left < 0)
	{
		Edges.Left = 0;
		Edges.Right = Size.X - 1;
	}
	if(Edges.Top < 0)
	{
		Edges.Top = 0;
		Edges.Bottom = Size.Y - 1;
	}
	if(Edges.Right > SCRN_XMAX)
	{
		Edges.Right = SCRN_WIDTH;
		Edges.Left = SCRN_WIDTH - Size.X;
	}
	if(Edges.Bottom > SCRN_YMAX)
	{
		Edges.Bottom = SCRN_HEIGHT;
		Edges.Top = SCRN_HEIGHT - Size.Y;
	}
}

void _ScrnBuffer::DrawAt(int Left, int Top, const COORD IndexCoords = coord(0,0))
{
	SMALL_RECT rect = {Left, Top, Left + Size.X - 1, Top + Size.Y - 1};
	WriteConsoleOutput(hOutput, pGFX, Size, IndexCoords, &rect);
}*/

//*********************************************
/*bool WriteScrnBufferToFile(ScrnBuffer& s, string FileName, string SBOLabel)
{
	ofstream f;
	f.open(FileName.c_str());

	if(f.fail())
		return false;

	f<<"[SBO_DATABASE_START]\n";

	f<<"{[" + SBOLabel + "]}\n";

	f<<s.Size.X <<' ';
	f<<s.Size.Y <<' ';

	for(int y = 0; y < s.Size.Y; y++)
	{
		for(int x = 0; x < s.Size.X; x++)
		{
			f<<(int)s.pGFX[x + y * s.Size.X].Char.AsciiChar <<' ';
		}
	}

	for(y = 0; y < s.Size.Y; y++)
	{
		for(int x = 0; x < s.Size.X; x++)
		{
			f<<s.pGFX[x + y * s.Size.X].Attributes <<' ';
		}
	}

	f<<"\n[SBO_DATABASE_END]";

	return true;
}

//*********************************************
bool LoadScrnBufferFromFile(string FileName, string Label)
{
	ifstream GF;
	GF.open(FileName.c_str(), std::ios::in);

	if(GF.fail())
	{
		Status = SBO_SOURCE_FILE_LOAD_FAILURE;
		PrintError(FileName, Label);
		return false;
	}

	//Find the start of the ScrnBuffer database
	string Buffer;
	while(true)
	{
		if(GF.eof())
		{
			Status = SBO_DATABASE_NOT_FOUND;
			PrintError(FileName, Label);
			return false;
		}

		GF>>Buffer;
		if(Buffer == "[SBO_DATABASE_START]")
			break;
	}

	//Find the specific ScrnBuffer in database
	do
	{
		GF>>Buffer;
		if(Buffer == "[SBO_DATABASE_END]" || GF.eof())
		{
			Status = SBO_NOT_FOUND_IN_DATABASE;
			PrintError(FileName, Label);
			return false;
		}
	}while(Buffer != "{["+Label+"]}");

	int x,y,t;

	GF>>Size.X;
	GF>>Size.Y;

	if(pGFX)
		delete[] pGFX;
	pGFX = new CHAR_INFO[Size.X * Size.Y];

	for(y = 0; y < Size.Y; y++)
	{
		for(x = 0; x < Size.X; x++)
		{
			GF>>t;
			pGFX[x + y * Size.X].Char.AsciiChar = (char)t;
		}
	}
	for(y = 0; y < Size.Y; y++)
	{
		for(x = 0; x < Size.X; x++)
		{
			GF>>t;
			pGFX[x + y * Size.X].Attributes = t;
		}
	}
	Status = SBO_LOAD_GOOD;

	bBufferInit = true;

	return true;
}*/
