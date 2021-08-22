#include <windows.h>
#include <iostream>

using namespace std;

#include <type.h>
#include <Console\stdcon.h>
#include <Console\graphics.h>
#include <Kataline.h>

#define UP		coord(0, -1)
#define DOWN	coord(0, 1)
#define LEFT	coord(-1, 0)
#define RIGHT	coord(1, 0)

#define WALL_CHAR	'@'
#define MOUSE_CHAR	'&'
#define CHEESE_CHAR	'$'
#define MAZE_X		63
#define MAZE_Y		63

char board[] = "\
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\
@$        @     @           @   @   @ @           @       @   @\
@@@@@ @@@ @ @@@@@ @@@@@@@@@ @ @ @ @ @ @ @ @ @@@@@ @ @@@@@ @ @@@\
@     @   @ @       @     @ @ @   @ @   @ @   @   @ @   @     @\
@ @@@@@ @@@ @ @@@@@ @ @@@ @@@ @@@@@ @@@@@ @ @ @@@@@ @ @@@@@ @ @\
@ @   @   @   @ @   @ @ @     @   @       @ @       @ @   @ @ @\
@ @ @ @@@ @@@@@ @ @ @ @ @@@@@@@ @ @@@@@@@@@ @@@@@@@@@ @ @ @ @ @\
@ @ @   @       @ @   @   @     @ @   @     @   @     @ @   @ @\
@ @ @@@ @@@@@@@ @ @@@@@@@ @ @ @@@ @@@ @ @ @@@@@ @ @@@@@ @@@@@ @\
@   @   @     @ @ @     @ @ @   @   @   @     @ @       @   @ @\
@@@@@ @@@ @ @@@@@ @ @@@ @ @ @@@ @@@ @@@@@@@@@ @ @@@@@@@@@ @@@ @\
@   @   @ @     @   @   @ @ @   @ @ @       @   @         @   @\
@ @@@@@ @ @@@ @ @@@@@ @@@ @@@ @ @ @ @ @@@@@ @@@@@@@ @@@@@ @ @@@\
@ @     @ @   @     @ @   @   @ @ @ @   @   @       @   @ @   @\
@ @ @ @@@@@ @@@@@@@ @ @ @@@ @ @@@ @ @@@ @ @@@ @@@@@@@ @ @ @@@ @\
@ @ @     @ @   @     @     @ @   @     @   @         @ @   @ @\
@ @ @@@@@ @ @@@ @ @@@@@@@@@@@ @ @@@@@@@@@@@ @ @@@@@@@@@ @@@@@ @\
@ @   @   @     @ @   @       @ @       @   @       @ @     @ @\
@ @@@ @@@@@ @@@@@ @ @ @ @@@@@@@ @ @@@@@ @ @ @@@@@@@ @ @@@@@ @@@\
@ @ @     @ @   @   @ @ @     @   @   @ @ @       @ @   @ @   @\
@ @ @@@@@ @ @ @ @@@@@ @ @ @@@ @ @@@ @@@ @ @ @@@ @ @ @ @ @ @@@ @\
@     @ @   @ @     @   @   @ @ @ @   @   @   @ @   @ @   @   @\
@@@@@ @ @@@ @ @ @@@@@@@@@@@ @ @ @ @ @ @@@@@@@@@ @@@@@ @@@@@ @@@\
@   @ @ @   @ @         @ @ @   @   @     @     @   @   @   @ @\
@ @ @ @ @ @@@ @@@@@@@ @ @ @ @@@@@@@@@@@@@ @ @@@ @@@ @@@ @ @@@ @\
@ @ @ @   @ @ @       @ @ @ @ @           @   @ @   @ @   @   @\
@ @ @ @ @@@ @ @ @@@@@ @ @ @ @ @ @ @@@ @@@@@@@ @@@ @ @ @@@@@ @ @\
@ @   @ @   @ @ @     @   @ @   @   @ @     @     @ @       @ @\
@ @@@@@@@ @ @ @@@ @@@@@@@@@ @@@@@@@@@ @@@@@ @ @@@@@ @@@@@@@@@ @\
@ @       @   @   @   @   @     @   @ @     @   @   @     @   @\
@ @ @ @@@@@@@@@ @@@ @ @@@ @ @@@ @ @ @ @ @@@@@@@ @ @@@ @@@ @ @ @\
@   @ @       @   @ @   @ @   @   @ @   @     @ @     @   @ @ @\
@@@@@ @@@ @@@ @@@ @ @@@ @ @@@ @@@@@@@@@ @ @@@ @ @@@@@@@ @@@ @ @\
@   @   @   @   @ @ @ @     @           @ @ @ @   @   @     @ @\
@ @@@ @ @@@ @@@ @ @ @ @@@@@ @@@@@@@@@@@ @ @ @ @@@ @@@ @@@@@@@ @\
@ @   @   @ @ @ @   @       @         @ @   @   @     @   @   @\
@ @ @@@@@ @ @ @ @ @@@@@@@@@@@ @@@ @@@@@ @@@@@@@ @@@ @@@ @ @ @@@\
@ @   @ @   @ @ @ @ @     @ @   @     @     @ @ @   @   @   @ @\
@ @ @ @ @ @@@ @ @ @ @ @@@ @ @@@ @@@@@ @@@ @ @ @ @ @@@ @@@@@ @ @\
@ @ @ @   @   @ @ @ @ @   @     @   @   @ @ @ @   @   @   @ @ @\
@ @@@ @@@@@ @@@ @ @ @ @ @@@ @@@@@ @ @@@ @ @ @ @@@@@ @ @ @@@ @ @\
@   @ @   @   @ @ @   @   @ @   @ @   @ @ @ @   @   @   @   @ @\
@@@ @ @ @ @ @@@ @ @ @@@@@ @ @ @@@ @ @ @ @ @ @@@ @ @@@@@@@ @@@ @\
@ @     @ @     @ @ @   @ @ @     @ @ @   @   @       @   @   @\
@ @@@@@@@@@ @@@@@ @ @ @ @ @ @@@@@@@ @ @@@@@@@ @@@@@@@@@ @@@ @@@\
@ @         @   @ @ @ @ @ @     @   @       @   @     @       @\
@ @ @@@@@@@@@ @@@ @ @ @ @ @@@@@ @ @@@@@@@@@@@@@ @ @@@ @@@@@@@ @\
@   @ @       @   @ @ @     @   @ @             @ @ @     @   @\
@@@ @ @ @@@ @@@ @@@ @ @@@@@@@ @@@ @ @@@@@@@@@ @ @ @ @@@@@ @ @@@\
@ @ @ @   @     @   @ @     @   @ @ @     @   @   @     @ @   @\
@ @ @ @@@ @@@@@@@@@@@ @ @ @ @@@ @ @ @ @@@ @ @@@@@@@ @@@@@ @@@@@\
@   @ @   @ @   @   @   @ @   @ @   @   @ @   @     @   @ @   @\
@@@@@ @ @@@ @ @ @ @ @@@ @@@@@ @ @ @@@@@ @ @@@@@ @@@ @ @ @ @ @ @\
@     @ @     @ @ @   @ @   @   @     @ @ @     @   @ @ @   @ @\
@ @@@@@ @ @@@@@ @ @@@ @@@ @ @@@@@@@@@ @ @ @ @@@ @@@@@ @ @@@@@ @\
@ @     @     @   @   @   @ @   @     @ @ @   @       @       @\
@ @ @@@@@@@@@ @@@ @@@@@ @ @@@ @ @ @@@@@@@ @ @ @@@@@@@@@@@@@@@@@\
@   @       @ @   @     @ @   @ @ @     @ @ @ @     @         @\
@@@ @@@@@ @ @ @ @@@ @@@@@ @ @@@ @ @ @@@ @ @ @ @@@@@ @ @ @@@@@ @\
@   @     @ @ @     @ @   @   @ @ @ @   @   @ @   @   @ @   @ @\
@ @@@ @@@ @@@ @@@@@@@ @ @@@@@ @ @ @ @ @@@ @ @ @ @ @@@@@@@ @ @ @\
@     @       @               @   @ @     @ @   @         @  &@\
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";

COORD dir = UP;
COORD mouse_pos;
COORD cheese_pos;

char _board(COORD c)
{
	return board[c.X + (c.Y * MAZE_X)];
}

COORD right_of(COORD d)
{
	if( d == UP )
		return RIGHT;
	if( d == RIGHT )
		return DOWN;
	if( d == DOWN )
		return LEFT;
	if( d == LEFT )
		return UP;
	__assume(0);
}

COORD left_of(COORD d)
{
	if( d == UP )
		return LEFT;
	if( d == LEFT )
		return DOWN;
	if( d == DOWN )
		return RIGHT;
	if( d == RIGHT )
		return UP;
	__assume(0);
}

void main()
{
	SetupKatalineConsole("Mouse and Cheese", coord(MAZE_X + 1, MAZE_Y + 1));

	CONSOLE_CURSOR_INFO i = {25, 0};
	SetConsoleCursorInfo(hStdOutput, &i);

	char line[ MAZE_X + 1];

	for(int y = 0; y < MAZE_Y; y++)
	{
		line[ MAZE_X ] = 0;

		for(int x = 0; x < MAZE_X; x++)
		{
			char c = _board(coord(x, y));
			COLOR cl = Grey;

			if( c == MOUSE_CHAR )
				mouse_pos = coord(x, y);

			if( c == CHEESE_CHAR )
				cheese_pos = coord(x, y);

			line[x] = (c == WALL_CHAR) ? (char)0xDB : ' ';
		}

		Text(coord(0, y), line, Grey);
	}

	Text(cheese_pos, CHEESE_CHAR, Green_I);
	Text(mouse_pos, MOUSE_CHAR, White_I);

	for(;;)
	{
		//while( _getch() != ' ' ); //step through

		if( WALL_CHAR != _board(mouse_pos + right_of(dir)) )
			dir = right_of(dir);

		if( WALL_CHAR == _board(mouse_pos + dir) ) // can't move forward
		{
			if( WALL_CHAR != _board(mouse_pos + left_of(dir)) ) // left move possible
				dir = left_of(dir);
			if( WALL_CHAR != _board(mouse_pos + -dir) )
				dir = -dir;
		}

		Text(mouse_pos, ' ');
		mouse_pos += dir;
		Text(mouse_pos, MOUSE_CHAR, White_I);

		if( mouse_pos == cheese_pos )
			break;

		Sleep(10);
	}
	Text(coord(30, 30), "the mouse has found the cheese.");
}