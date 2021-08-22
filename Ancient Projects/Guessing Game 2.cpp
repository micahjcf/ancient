#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

#include <MJCF\ConGlob.h>
#include <MJCF\ErrorLog.h>
#include <MJCF\Graphics.h>
#include <MJCF\Keyboard.h>
#include <MJCF\Random.h>

int Range[2];
int Guess;
int Chances;
int RandomNumber;
bool GuessedCorrect;
bool done = false;

void Difficulty()
{
	ClrScrn();
	bool valid = false;
	cout<<"Select your difficulty\n\n";
	cout<<"(1)Easy\n(2)Normal\n(3)Hard\n(4)Good Luck!\n";
	
	while(!valid)
	{
		switch(getch())
		{
		case '1':
			Range[0] = 0;
			Range[1] = 100;
			Chances = 10;
			valid = true;
			break;
		case '2':
			Range[0] = 0;
			Range[1] = 150;
			Chances = 10;
			valid = true;
			break;
		case '3':
			Range[0] = Random(1,9);
			Range[1] = Random(154,178);
			Chances = Random(7,9);
			valid = true;
			break;
		case '4':
			Range[0] = Random(5,10);
			Range[1] = Random(111,120);
			Chances = Random(4,5);
			valid = true;
			break;
		default:
			break;
		}
	}
}

void Play()
{
	RandomNumber = Random(Range[0], Range[1]);
	GuessedCorrect = false;

	ClrScrn();

	cout<<"The range is from " <<Range[0] <<" to " <<Range[1];

	do
	{
		if(Chances != 1)
			cout<<"\n\nGuesses left = " <<Chances;
		else
			cout<<"\n\nLast chance!!";
		cout<<"\nYour guess:";

		Input(Guess, 3, NORMAL, White_I);

		if(Guess < Range[0] || Guess > Range[1])
		{
			cout<<"\n\nGuess out of range";
			continue;
		}

		if(Guess > RandomNumber)
			cout<<"\n\nYou Guessed too high";
		if(Guess < RandomNumber)
			cout<<"\n\nYou Guessed too low";
		if(Guess == RandomNumber)
			GuessedCorrect = true;

		--Chances;
	}while(!GuessedCorrect && Chances > 0);

	ClrScrn();

	if(GuessedCorrect)
		cout<<"You guessed correct!\n\n";
	else
	{
		cout<<"You failed to guess the number\n";
		cout<<"The number was: " <<RandomNumber <<endl <<endl;
	}
}

int main()
{
	SetupConsole(30,30,"Guessing Game");
	cout<<"Guessing Game\nby Micah Fullerton\n\n";
	cout<<"(1)Play\n(2)Quit\n";

	while(!done)
	{
		switch(getch())
		{
		case '1':
			Difficulty();
			Play();
			cout<<"(1)Play\n(2)Quit\n";
			break;
		case '2':
			done = true;
			break;
		default:
			break;
		}
	}
	return 0;
}
