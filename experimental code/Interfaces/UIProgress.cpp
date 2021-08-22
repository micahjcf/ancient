class CActivityBar
{
public:
	CActivityBar(){}
	~CActivityBar(){}

	void Setup(BAR Pos, char Character, WORD Colors, WORD ProgressColors, int Speed);
	void Increment();
	void IncrementOnCounter();

	BAR Position;
	char Char;
	WORD Color;
	WORD ProgressColor;
	int CounterTime;	// # of milliseconds that has to pass before another increment

	// Previous static members
	int X;
	bool WaxOn;
	int PrevTime;
	int Counter;
};

void CActivityBar::Setup(BAR Pos, char Character, WORD Colors, WORD ProgressColors, int Speed = 6)
{
	Char = Character;
	Position = Pos;
	Color = Colors;
	ProgressColor = ProgressColors;
	CounterTime = Speed;

	X = Position.Left;
	WaxOn = true;
	PrevTime = Counter = 0;

	Draw::BAR(Position, Char, Color);
}

void CActivityBar::Increment()
{
	Text(X++, Position.Y, Char, (WaxOn?ProgressColor:Color));

	if(X == Position.Right + 1)
	{
		X = Position.Left;
		WaxOn = (WaxOn?false:true);
	}
}

void CActivityBar::IncrementOnCounter()
{
	SYSTEMTIME Time;
	GetSystemTime(&Time);

	if(PrevTime != Time.wMilliseconds)
	{
		PrevTime = Time.wMilliseconds;
		Counter++;
	}

	if(Counter == CounterTime)
	{
		Counter = 0;
		Increment();
	}
}

//***********************************************
//***********************************************
class CLoadBar
{
public:
	CLoadBar(){}
	~CLoadBar(){}

	void Setup(BAR Pos, char Character, WORD SideColors, WORD BackgroundColor, WORD ProgressColors, int Speed);
	void Reset();
	void inline Clear();

	void Increment();
	void IncrementOnCounter();

	BAR Position;
	string Chars;
	WORD SideColor;
	WORD BGColor;
	WORD ProgressColor;
	int TimeWait;	// # of milliseconds that has to pass before another increment

	// Previous static members
	int Index;
	int Length;
	int xPos;
	int PrevTime;
	int Counter;
};

void CLoadBar::Setup(BAR Pos, char Character, WORD SideColors, WORD BackgroundColor, WORD ProgressColors, int Speed = 5)
{
	Position = ReturnBar(Pos.Y, Pos.Left, Pos.Right);
	Chars.resize(3);

	for(int n = 0; n < 3; n++)
	{
		Chars[n] = Character;
	}

	SideColor = SideColors;
	BGColor = BackgroundColor;
	ProgressColor = ProgressColors;
	TimeWait = Speed;

	Index = Chars.length();
	xPos = Position.Left;
	Length = PrevTime = Counter = 0;

	Draw::BAR(Position, (char)219, BGColor);
	Text(Position.Left - 1, Position.Y, '(', SideColor);
	Text(Position.Right + 1, Position.Y, ')', SideColor);
}

void CLoadBar::Reset()
{
	Index = Chars.length();
	Length = PrevTime = Counter = 0;
	xPos = Position.Left + 1;
}

void inline CLoadBar::Clear()
{
	Draw::BAR(Position, (char)219, BGColor);
}

void CLoadBar::Increment()
{
	if(xPos >= Position.Right - 2)
	{
		if(Length > 0)
		{
			Length--;
			xPos++;
		}
		else
		{
			Index = Chars.length();
			Length = 0;
			xPos = Position.Left;
		}
	}
	else
	{
		if(Index > 0)
		{
			Index--;
			Length++;
		}
		else
			xPos++;
	}

	Draw::BAR(Position, (char)219, BGColor);
	Text(xPos, Position.Y, Chars.substr(Index,Length), (ProgressColor | DeleteBG(BGColor)<<4));
																//(ProgressColor | (Color<<4)));
}

void CLoadBar::IncrementOnCounter()
{
	SYSTEMTIME Time;
	GetSystemTime(&Time);

	if(PrevTime != Time.wMilliseconds)
	{
		PrevTime = Time.wMilliseconds;
		Counter++;
	}

	if(Counter == TimeWait)
	{
		Counter = 0;
		Increment();
	}
}