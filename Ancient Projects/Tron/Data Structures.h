#ifndef _DATA_SCTRUCTURES_
#define _DATA_SCTRUCTURES_

#define UP		0x0001
#define DOWN	0x0002
#define LEFT	0x0004
#define RIGHT	0x0008

struct GAMEVARIABLES
{
	int		StartPos;
	int		GameSpeed;
	int		HumanScore;
	int		CompScore;
	int		CurMatch;
	int		MatchSize;
};GAMEVARIABLES gv;

class LINE
{
public:
	LINE(int, BYTE, WORD);
	~LINE(){}

	void Move();
	bool Collision();
	void Kill();
	bool Dead();

	bool	Alive;
	COORD	Head;
	COORD	Heading;
	BYTE	Direction;
	WORD	Bodycolor;
};

LINE::LINE(int yStartPos, BYTE Direction, WORD bodycolor)
{
	Head.X = Random(2, SCREEN_XMAX-2);
	Head.Y = yStartPos;
	Matrix[Head.X + Head.Y * SCREEN_WIDTH] = 1;

	Heading.X = 0;
	if(Direction == UP)
		Heading.Y = -1;
	if(Direction == DOWN)
		Heading.Y = 1;
	Bodycolor = bodycolor;
	Text_char(Head.X, Head.Y, (char)219, Bodycolor);
}

void LINE::Move()
{
	Head.X += Heading.X;
	Head.Y += Heading.Y;
	if(this->Collision())
	{
		this->Kill();
	}
	Matrix[Head.X + Head.Y * SCREEN_WIDTH] = 1;
	Text_char(Head.X, Head.Y, (char)219, Bodycolor);
}

bool LINE::Collision()
{
	return Matrix[Head.X + Head.Y * SCREEN_WIDTH] == 1;
}

void LINE::Kill()
{
	Alive = false;
}

bool LINE::Dead()
{
	return Alive == false;
}

#endif