#ifndef _GAME_SYSTEM_
#define _GAME_SYSTEM_

//AI4 of calc Tron
void AI_(LINE& AI)
{
	bool flag = false;

	for(int n = 1; n<5; n+=2)
	{
		if(Matrix[AI.Head.X + ((AI.Head.Y+n) * SCREEN_WIDTH)] == 1)
			flag = true;
	}
	if(Random(1,10) == 10)
		flag = true;

	if(!flag)
		return;

	if(AI.Heading.Y == 1)
	{
		AI.Heading.Y = 0;
		if(Random(0,1))
		{
			AI.Heading.X = 1;
		}
		else
		{
			AI.Heading.X = -1;
		}
		return;
	}
	if(AI.Heading.Y == -1)
	{
		AI.Heading.Y = 0;
		if(Random(0,1))
		{
			AI.Heading.X = 1;
		}
		else
		{
			AI.Heading.X = -1;
		}
		return;
	}
	if(AI.Heading.X == 1)
	{
		AI.Heading.X = 0;
		if(Random(0,1))
		{
			AI.Heading.Y = 1;
		}
		else
		{
			AI.Heading.Y = -1;
		}
		return;
	}
	if(AI.Heading.X == -1)
	{
		AI.Heading.X = 0;
		if(Random(0,1))
		{
			AI.Heading.Y = 1;
		}
		else
		{
			AI.Heading.Y = -1;
		}
		return;
	}
}
void Setup()
{
	ClrScrn;

	DrawBox(_ScreenSize, '*', Blue_I);
	SetCursorPosition(0,0);

	int x,y;
	for(y=0; y<SCREEN_HEIGHT; y++)
		for(x=0; x<SCREEN_WIDTH; x++)
			Matrix[x + y * SCREEN_WIDTH] = 0;

	for(y = 0; y<SCREEN_HEIGHT; y++)
	{
		Matrix[1 + y * SCREEN_WIDTH] = 1;
		Matrix[SCREEN_WIDTH-2 + y * SCREEN_WIDTH] = 1;
	}

	for(x = 0; x<SCREEN_WIDTH; x++)
	{
		Matrix[x + 1 * SCREEN_WIDTH] = 1;
		Matrix[x + (SCREEN_YMAX-1) * SCREEN_WIDTH] = 1;
	}
}

void Engine()
{
	Setup();

	LINE Player(
		(gv.StartPos == 0)?(SCREEN_YMAX-2):(2),
		(gv.StartPos == 0)?(UP):(DOWN),
		Green_I);

	LINE Opponent(
		(gv.StartPos == 1)?(SCREEN_YMAX-2):(2),
		(gv.StartPos == 1)?(UP):(DOWN),
		Red_I);

	bool done = false;
	while(!done)
	{
		if(kbhit())
		{
			ReadConsoleInput(hInput, &InputRecord, 1, &Events);

			kb.dwKeyPressed = InputRecord.Event.KeyEvent.wVirtualKeyCode;

			switch(kb.dwKeyPressed)
			{
			case VK_UP:
				if(Player.Direction == DOWN)
					break;
				Player.Heading.X = 0;
				Player.Heading.Y = -1;
				Player.Direction = UP;
				break;
			case VK_DOWN:
				if(Player.Direction == UP)
					break;
				Player.Heading.X = 0;
				Player.Heading.Y = 1;
				Player.Direction = DOWN;
				break;
			case VK_LEFT:
				if(Player.Direction == RIGHT)
					break;
				Player.Heading.X = -1;
				Player.Heading.Y = 0;
				Player.Direction = LEFT;
				break;
			case VK_RIGHT:
				if(Player.Direction == LEFT)
					break;
				Player.Heading.X = 1;
				Player.Heading.Y = 0;
				Player.Direction = RIGHT;
				break;
			case 'P':
				DrawBox(_ScreenSize, '*', Teal_I);
				Text(MM_LEFT-5, SCREEN_YMAX-1, "Press Enter to continue playing", Blue_I);
				SetCursorPosition(0,0);
				KB_WAIT(VK_RETURN);
				DrawBox(_ScreenSize, '*', Blue_I);
				SetCursorPosition(0,0);
				break;
			case VK_ESCAPE:
				done = true;
				break;
			default:
				break;
			}
			FlushKeyboard();
		}

		Player.Move();

		if(Player.Dead())
			break;

		AI_(Opponent);

		Opponent.Move();

		if(Opponent.Dead())
			break;

		Sleep(gv.GameSpeed);
	}

	if(Player.Dead())
	{
		DrawBox(_ScreenSize, '*', Red_I);
		Text_char(Player.Head.X, Player.Head.Y, '*', Black | B_Blue_I);
		Text(0,0,"Computer's Point");
		gv.CompScore++;
	}
	else
	{
		DrawBox(_ScreenSize, '*', Green_I);
		Text_char(Opponent.Head.X, Opponent.Head.Y, '*', Black | B_Blue_I);
		Text(SCREEN_XMAX-10,0,"Human Point");
		gv.HumanScore++;
	}
}

void ResultsScrn()
{
	ClrScrn;
	if(gv.HumanScore > gv.CompScore)
	{
		DrawBox(0,0,20 ,15,'*',Green_I);
	}
	else
	{
		DrawBox(0,0,20,15,'*', Red_I);
	}
	Text(3, 1, "Match complete", Yellow_I);
	GetKeyboardInput();
}

#endif