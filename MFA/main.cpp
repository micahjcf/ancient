#include <windows.h>
#include <iostream>
using namespace std;

#include <stdcode.h>

#include "mfa.h"

void main()
{
	MFAState mfa;
	BYTE M[100];
	BYTE hash[ MFAHASHSIZE ];

	for(int n = 0; n < 100; n++)
		M[n] = n;

	MFAInit(&mfa);

	MFAUpdate(&mfa, M, 100);
	MFAUpdate(&mfa, M, 10);
	MFAUpdate(&mfa, M, 1);

	MFAResult(&mfa, hash);

	for(int n = 0; n < MFAHASHSIZE; n++)
		printf("%s", ntoh(hash[n]).c_str());

	while(true);
}