/*
	Micah JC Fullerton
	
	(~) Part of the C++ Kataline Project
	
	Abstract:
		Command line parsing

	NOTICE: all command arguments are case sensitive
*/

#include <windows.h>
#include <string>
//#include <math.h>

BOOL cmdarg_FindString(char* ValName, std::string* str)
{
	for(int n = 1; __argv[n]; n++)
	{
		if(__argv[n][0] == '/')
		{
			for(int i = 1; __argv[n][i]; i++)
			{
				//Find the ':' and make sure a string is given
				if( (__argv[n][i] == ':') && __argv[n][i+1])
				{
					__argv[n][i] = '\0';

					if(strcmp(&__argv[n][1], ValName) == 0)
					{
						if(str)
							*str = &__argv[n][i+1];

						__argv[n][i] = ':';	//restore
						return TRUE;
					}
					else
						__argv[n][i] = ':'; //restore
				}
			}
		}
	}

	return FALSE;
}

//pVal can be NULL.  Do this to check if a value for ValName is given in the program args
//Returns true only if ValName is found and a valid value is given.
//If user doesnt specify a value eg. /ValName:\0, Then FALSE is returned
BOOL cmdarg_FindValue(char* ValName, int* pVal) //Finds /ValName:value
{
	for(int n = 1; __argv[n]; n++)
	{
		if(__argv[n][0] == '/')
		{
			for(int i = 1; __argv[n][i]; i++)
			{
				//Find the ':' and make sure a number is given
				if( (__argv[n][i] == ':') && __argv[n][i+1])
				{
					__argv[n][i] = '\0';

					if(strcmp(&__argv[n][1], ValName) == 0)
					{
						if(pVal)
						{
							if(! isdigit(__argv[n][i+1]))	//Make sure it's a digit
								if( __argv[n][i+1] != '-')	//Allows negative numbers
									continue;

							int t = atoi(&__argv[n][i+1]);

							if(errno == ERANGE)
								continue;
							else
								*pVal = t;
						}

						__argv[n][i] = ':';	//restore
						return TRUE;
					}
					else
						__argv[n][i] = ':'; //restore
				}
			}
		}
	}

	return FALSE;
}

BOOL cmdarg_FindSwitch(char* SwitchString) //Finds -SwitchString
{
	for(int n = 1; __argv[n]; n++)
		if((__argv[n][0] == '-') && (strcmp(&__argv[n][1], SwitchString) == 0))
				return TRUE;

	return FALSE;
}