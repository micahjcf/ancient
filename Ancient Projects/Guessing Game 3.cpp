#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <My Header Files\_MJCF_RandNumGen.h>

//************************** MAIN() ***************************
int main()
{
	int nGuess, nRandomNumber, nChances(10);
	bool bGuessedCorrect = false;
	cout<<"Guessing Game\nby Micah Fullerton";
	nRandomNumber = RNG(0,100);
	
	do
	{
		cout<<"\n\nEnter your guess (0-100)";
		cout<<"\n(" <<nChances <<" chance(s) left) :";
		cin>>nGuess;

		if(nGuess > nRandomNumber)
			cout<<"\nYou Guessed too high";
		if(nGuess < nRandomNumber)
			cout<<"\nYou Guessed too low";
		if(nGuess == nRandomNumber)
			bGuessedCorrect = true;
	}
	while(!bGuessedCorrect && --nChances > 0);

	if(bGuessedCorrect == true)
	{
		cout<<"\n\nYou guessed correct!\n\n";
	}
	else
	{
		cout<<"\n\nYou failed to guess the number.\n\n";
	}
	return 0;
}
