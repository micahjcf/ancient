#ifndef _MJCF_RANDNUMGEN_
#define _MJCF_RANDNUMGEN_

/////////////////////////////////////////
///
///		Created:		Micah Fullerton
///		Modified:		Micah Fullerton
///		Date Modified:	9/12/04
///		Requirements:	stdlid.h
///
/////////////////////////////////////////

int Random(int Min, int Max)
{
	srand(GetTickCount()+rand());
	return Min + (rand() % (Max - Min + 1));
}

/*
	//A simple test for the effecivness of the Random() function
void main()
{
	int arr[25];

	for(int n=0; n<25; n++)
	{
		arr[n] = Random(1, 5);
		cout<<arr[n] << endl;
	}

	int sum = 0;
	for(n = 0; n<25; n++)
	{
		sum += arr[n];
	}

	cout<<sum/25;
}
*/

#endif