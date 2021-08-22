#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

#include <stdcode.h>

#include <HiResTimer.h>

#include <Crypto\dllMFCryptic.h>
#include <Crypto\dllAchillea.h>

//clock()
//clock()/CLOCKS_PER_SEC

int RunSHA1Test(BOOL);
int RunMD5Test(BOOL);
int RunMFATest(BOOL);

//****************************************************************
HANDLE GetFileHandle(char* name)
{
	SetLastError(0);

	HANDLE handle = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);

	if(GetLastError() != 0)
	{
		printf("An error occured while trying to open the file.\n");
		exit(1);
	}

	return handle;
}

//****************************************************************
void Help()
{
	printf("FileHash -icheck [ icheck_options ]\n-or-\n");
	printf("FileHash filepath [ options ]\n\n");
	printf("This utility calculates the hash value of a given file using the MD5,\n");
	printf("SHA-1 and MFA-256 cryptographic hash algorithms.  ");
	printf("Calling this program with\nno arguments displays this help.\n\n");

	printf("The -icheck option runs test vectors to verify algorithm implementations\n");

	printf("\nicheck_options:\n");
	printf("-sha      verify SHA1 implementation\n");
	printf("-md5      verify MD5 implementation\n");
	printf("-mfa      verify MFA implementation\n");
	printf("-v        verbose mode (default only shows PASSED/FAILED)\n");

	printf("\noptions:\n");
	printf("-sha      calculate SHA1 hash value\n");
	printf("-md5      calculate MD5 hash value\n");
	printf("-mfa      calculate MFA hash value\n");
	printf("-v        verbose mode\n");
	printf("-beep     Beep when done (useful when hashing huge files)\n\n");

	system("pause");
}

//****************************************************************
int main(int argc, char** arg)
{
	int n;
	UINT i;
	BOOL SHA = 0, MD5 = 0, MFA = 0, verbose = 0, beep = 0;
	char spin[] = {'-', '\\', '|', '/'};

	if(argc == 1)
	{
		Help();
		return 0;
	}

	//change all parameters to lowercase
	for(n = 1; n < argc; n++)
	{
		for(i = 0; i < strlen(arg[n]); i++)
		{
			if(isupper(arg[n][i]))
				arg[n][i] = (char)tolower(arg[n][i]);
		}
	}

	//set flags based off of the arguments
	if(strcmp(arg[1], "-icheck") == 0)
	{
		UINT test = 0;

		for(n = 2; n < argc; n++)
		{
			i = 0;
			if(strcmp(arg[n], "-sha") == 0)
				SHA = i = 1;

			if(strcmp(arg[n], "-md5") == 0)
				MD5 = i = 1;

			if(strcmp(arg[n], "-mfa") == 0)
				MFA = i = 1;

			if(strcmp(arg[n], "-v") == 0)
				verbose = i = 1;

			if(!i)
			{
				printf("Unknown parameter: %s\n", arg[n]);
				return 1;
			}
		}

		if(!(SHA | MD5 | MFA))
		{
			printf("No algorithms specified to test.\n");
			return 1;
		}

		if(verbose)
			printf("Checking implementation integrity...\n\n");

		if(SHA) test += RunSHA1Test(verbose);
		if(MD5) test += RunMD5Test(verbose);
		if(MFA) test += RunMFATest(verbose);

		if(test)
		{
			if(verbose)
			{
				system("color c");
				printf("Integrity check FAILED!!!\n");
				printf("Warning: This program may not produce accurate hashes!\n");
				printf("The .dll implementation files may be corrupt.\n");
			}
			else
				printf("FAILED\n");

			return 1;
		}
		else
		{
			if(verbose)
				printf("Integrity check	PASSED\n");
			else
				printf("PASSED\n");

			return 0;
		}
	}

	HANDLE hFile = GetFileHandle(arg[1]);

	//set flags based off of the arguments
	for(n = 2; n < argc; n++)
	{
		i = 0;
		if(strcmp(arg[n], "-sha") == 0)
			SHA = i = 1;

		if(strcmp(arg[n], "-md5") == 0)
			MD5 = i = 1;

		if(strcmp(arg[n], "-mfa") == 0)
			MFA = i = 1;

		if(strcmp(arg[n], "-v") == 0)
			verbose = i = 1;

		if(strcmp(arg[n], "-beep") == 0)
			beep = i = 1;

		if(!i)
		{
			printf("Unknown parameter: %s\n", arg[n]);
			return 1;
		}
	}

	if(!(SHA | MD5 | MFA))
	{
		printf("No algorithms specified to run.\n");
		return 1;
	}

	SHA1State SHA1Data;
	MD5State MD5Data;
	MFAState MFAData;

	BYTE SHAhash[ SHA1HASHSIZE ], MD5hash[ MD5HASHSIZE ], MFAhash[ MFAHASHSIZE ], buf[ 524288 ];

	DWORD BYTEsRead;
	string hash_string = "";

	if(SHA)
		SHA1Init(&SHA1Data);

	if(MD5)
		MD5Init(&MD5Data);

	if(MFA)
		MFAInit(&MFAData);

	if(verbose)
	{
		LARGE_INTEGER FileSize;

		if( GetFileSizeEx(hFile, &FileSize) == 0 )
			printf("An error has occured while accessing the file.\n");

		if(FileSize.QuadPart >= 1048576)
			printf("File Size %.2f MB\n", FileSize.QuadPart/1048576.0);
		else
			printf("File Size %.2f KB\n", FileSize.QuadPart/1024.0);
	}

	if(verbose)
		printf("Calculating hash values for \"%s\"...-", strrchr(__argv[1], '\\') + 1);

	n = 0;
	do
	{
		ReadFile(hFile, buf, 524288, &BYTEsRead, NULL);

		if(SHA)
			SHA1Update(&SHA1Data, buf, BYTEsRead);
		if(MD5)
			MD5Update(&MD5Data, buf, BYTEsRead);
		if(MFA)
			MFAUpdate(&MFAData, buf, BYTEsRead);

		if(verbose)
			printf("\b%c", spin[(++n) % 4]);

	} while(BYTEsRead == 524288);

	if(verbose)
		printf("\n\n");

	if(SHA)
		SHA1Result(&SHA1Data, SHAhash);
	if(MD5)
		MD5Result(&MD5Data, MD5hash);
	if(MFA)
		MFAResult(&MFAData, MFAhash);

	if(SHA)
	{
		for(n = 0; n < 20; n++)
			hash_string += ntoh(SHAhash[n]);

		printf("SHA1:\t%s\n", hash_string.c_str());
	}

	if(MD5)
	{
		hash_string = "";
		for(n = 0; n < 16; n++)
			hash_string += ntoh(MD5hash[n]);

		printf("MD5:\t%s\n", hash_string.c_str());
	}

	if(MFA)
	{
		hash_string = "";
		for(n = 0; n < 32; n++)
			hash_string += ntoh(MFAhash[n]);

		printf("MFA:\t%s\n", hash_string.c_str());
	}

	if(beep)
		Beep(2500, 270);

	CloseHandle(hFile);

	return 0;
}
