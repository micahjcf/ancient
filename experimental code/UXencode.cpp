#include <windows.h>
#include <string>

using namespace std;

#include <stdcode.h>
#include <CRC32.h>

#include <UXencode.h>

#include <FilePath.h>

#define bias 33

namespace UXencode
{

// 0		 1		   2		 3
// [@@111111][@@112222][@@222233][@@333333]
void EncodeGroup(BYTE* Raw, BYTE* Encoded)
{
	Encoded[0] = Raw[0] >> 2;

	Encoded[1] = (Raw[0] << 4) & 0x3F;
	Encoded[1] |= Raw[1] >> 4;

	Encoded[2] = (Raw[1] << 2) & 0x3F;
	Encoded[2] |= Raw[2] >> 6;

	Encoded[3] = Raw[2] & 0x3F;

	Encoded[0] += bias;
	Encoded[1] += bias;
	Encoded[2] += bias;
	Encoded[3] += bias;
}

// 0		 1		   2
// [00000011][11112222][22333333]
void DecodeGroup(BYTE* Encoded, BYTE* Raw)
{
	Raw[0] = (Encoded[0] - bias) << 2;
	Raw[0] |= (Encoded[1] - bias) >> 4;

	Raw[1] = (Encoded[1] - bias) << 4;
	Raw[1] |= (Encoded[2] - bias) >> 2;

	Raw[2] = (Encoded[2] - bias) << 6;
	Raw[2] |= (Encoded[3] - bias);
}

//Take decoded stopline to determine how long the endline is
unsigned GetEndLineSize(unsigned nRawBytes)
{
	div_t len = div(nRawBytes, 3);
	return (len.quot + (len.rem != 0)) << 2;
}

//Encodes the stopline given the length number of raw bytes in the endline
void GetStopLine(BYTE StopLine[72], unsigned nEndLineBytes)
{
	StopLine[0] = '|';
	StopLine[1] = nEndLineBytes + bias;

	for(unsigned n = 2; n < 72; n++)
		StopLine[n] = '=';
}

//Get the number of raw bytes in the endline
unsigned DecodeStopLine(BYTE StopLine[72])
{
	return StopLine[1] - bias;
}

void EncodeFullLine(BYTE RawData[54], BYTE EncodedData[72])
{
	for(int n = 0; n < 18; n++)
		EncodeGroup(RawData+(n*3), EncodedData+(n*4));
}

void DecodeFullLine(BYTE EncodedData[72], BYTE RawData[54])
{
	for(int n = 0; n < 18; n++)
		DecodeGroup(EncodedData+(n*4), RawData+(n*3));
}

void EncodeEndLine(BYTE RawData[54], BYTE EncodedData[72], unsigned nRawBytes)
{
	div_t Groups = div(nRawBytes, 3);
	int n;

	for(n = 0; n < Groups.quot; n++)
		EncodeGroup(RawData+(n*3), EncodedData+(n*4));

	if(!Groups.rem)
		return;

	/*EncodedData[n*4] = RawData[n*3] >> 2;

	EncodedData[n*4+1] = (RawData[n*3] << 4) & 0x3F;

	EncodedData[n*4] += bias;
	EncodedData[n*4+1] += bias;


	EncodedData[n*4+3] = (char)95;

	if(Groups.rem == 2)
	{
		EncodedData[n*4+1] |= RawData[n*3+1] >> 4;

		EncodedData[n*4+2] = (RawData[n*3+1] << 2) & 0x3F;
		EncodedData[n*4+2] |= RawData[n*3+2] >> 6;
	}*/

	switch(Groups.rem)
	{
	case 1:
		EncodedData[n*4] = RawData[n*3] >> 2;

		EncodedData[n*4+1] = (RawData[n*3] << 4) & 0x3F;

		EncodedData[n*4] += bias;
		EncodedData[n*4+1] += bias;

		EncodedData[n*4+2] = (char)95;
		EncodedData[n*4+3] = (char)95;
		break;
	case 2:
		EncodedData[n*4] = RawData[n*3] >> 2;

		EncodedData[n*4+1] = (RawData[n*3] << 4) & 0x3F;
		EncodedData[n*4+1] |= RawData[n*3+1] >> 4;

		EncodedData[n*4+2] = (RawData[n*3+1] << 2) & 0x3F;
		EncodedData[n*4+2] |= RawData[n*3+2] >> 6;

		EncodedData[n*4] += bias;
		EncodedData[n*4+1] += bias;
		EncodedData[n*4+2] += bias;

		EncodedData[n*4+3] = (char)95;
		break;
	};
}

void DecodeEndLine(BYTE EncodedData[72], BYTE RawData[54], unsigned nRawBytes)
{
	div_t Groups = div(nRawBytes, 3);
	int n;

	for(n = 0; n < Groups.quot; n++)
		DecodeGroup(EncodedData+(n*4), RawData+(n*3));

	if(!Groups.rem)
		return;

	switch(Groups.rem)
	{
	case 1:
		RawData[n*3] = (EncodedData[n*4] - bias) << 2;
		RawData[n*3] |= (EncodedData[n*4+1] - bias) >> 4;
		break;
	case 2:
		RawData[n*3] = (EncodedData[n*4] - bias) << 2;
		RawData[n*3] |= (EncodedData[n*4+1] - bias) >> 4;
		RawData[n*3+1] = (EncodedData[n*4+1] - bias) << 4;
		RawData[n*3+1] |= (EncodedData[n*4+2] - bias) >> 2;
		break;
	};

	//Try this
	/*RawData[n*3] = (EncodedData[n*4] - bias) << 2;
	RawData[n*3] |= (EncodedData[n*4+1] - bias) >> 4;

	if(Groups.rem == 2)
	{
		RawData[n*3+1] = (EncodedData[n*4+1] - bias) << 4;
		RawData[n*3+1] |= (EncodedData[n*4+2] - bias) >> 2;
	}*/
}

} //UXencode

//About 137% file expansion

//Returns GetLastError() or 0 for success
//Returns 0xFFFFFFFF if trying to encode .uxe file
DWORD UXEncodeFile(char filename[ MAX_PATH ])
{
	BYTE RawData[5400], EncodedData[74];  //72 + 2 for end line chars ('CR', 'LF')

	CFilePath EncodedFileName;
	EncodedFileName = filename;
	EncodedFileName.ChangeExtension("uxe");

	//Don't encode .uxe files
	if( strcmp(EncodedFileName.GetPath(), filename) == 0)
		return (DWORD)-1;

	HANDLE hFile = CreateFile(filename, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
		return GetLastError();

	HANDLE hOut = CreateFile(EncodedFileName.GetPath(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if(hOut == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		return GetLastError();
	}

	int extlen;

	if( char* t = strrchr(filename, '.') )
		extlen = (int)min(strlen( t ) - 1, 8);	//Don't let the extension get longer than 8 chars
	else
		extlen = 0;

	char Header[9];
	strcpy(Header, "UXcode\15\12");
	Header[8] = extlen + bias;

	DWORD nWritten;

	//Write the standard header
	if( WriteFile(hOut, Header, 9, &nWritten, NULL) == 0)
		goto encerr;

	DWORD CRCEncode;
	CRC32Init(&CRCEncode);
	CRC32Update(Header, 9, &CRCEncode);

	//Write the extension
	if(extlen)
	{
		if( WriteFile(hOut, strrchr(filename, '.') + 1, extlen, &nWritten, NULL) == 0)
			goto encerr;

		CRC32Update(strrchr(filename, '.') + 1, extlen, &CRCEncode);
	}

	//Write the newline chars
	if( WriteFile(hOut, Header + 6, 2, &nWritten, NULL) == 0)
		goto encerr;

	CRC32Update(Header + 6, 2, &CRCEncode);

	EncodedData[72] = '\15'; //13 'CR'
	EncodedData[73] = '\12'; //10 'LF'

	while(true);

	DWORD nRead;
	//DoubleUsing nRead = size of file
	if((nRead = GetFileSize(hFile, NULL)) == 0xFFFFFFFF)
		goto encerr;

	//	3 choices:
	//file can be empty	(coded lines, null stop line, no end line)
	//even block length	(coded lines, null stop line, no end line)
	//uneven block length	(no coded lines, coded stop line, end line)

	DWORD CRCRaw;
	CRC32Init(&CRCRaw);

	if(nRead != 0)
	{
		do
		{
			if( ReadFile(hFile, RawData, 5400, &nRead, NULL) == 0)
				goto encerr;

			CRC32Update(RawData, nRead, &CRCRaw);

			div_t lines = div(nRead, 54);

			for(int n = 0; n < lines.quot; n++)
			{
				UXencode::EncodeFullLine(&(RawData[n*54]), EncodedData);

				CRC32Update(EncodedData, 74, &CRCEncode);

				if( WriteFile(hOut, EncodedData, 74, &nWritten, NULL) == 0)
					goto encerr;
			}

			if( nRead != 5400 )
			{
				UXencode::GetStopLine(EncodedData, lines.rem);
				CRC32Update(EncodedData, 74, &CRCEncode);

				if( WriteFile(hOut, EncodedData, 74, &nWritten, NULL) == 0)
					goto encerr;

				//We have an odd block length
				if(UXencode::GetEndLineSize(lines.rem) != 0)
				{
					UXencode::EncodeEndLine(&(RawData[lines.quot*54]), EncodedData, lines.rem);

					CRC32Update(EncodedData, UXencode::GetEndLineSize(lines.rem), &CRCEncode);

					if( WriteFile(hOut, EncodedData, UXencode::GetEndLineSize(lines.rem), &nRead, NULL) == 0)
						goto encerr;

					CRC32Update(EncodedData + 72, 2, &CRCEncode);

					if( WriteFile(hOut, EncodedData + 72, 2, &nRead, NULL) == 0)
						goto encerr;
				}

				break;
			}
		}while(true);
	}
	else	//File is empty
	{
		UXencode::GetStopLine(EncodedData, 0);

		CRC32Update(EncodedData, 74, &CRCEncode);

		if( WriteFile(hOut, EncodedData, 74, &nWritten, NULL) == 0)
			goto encerr;
	}

	CloseHandle(hFile);

	CRC32Result(&CRCRaw);
	CRC32Result(&CRCEncode);

	printf("%s\n%s", ntoh(CRCRaw), ntoh(CRCEncode));

	strcpy(Header, "CHK:");

	if( WriteFile(hOut, Header, 4, &nWritten, NULL) == 0)
		goto encerr;

	RawData[0] = (BYTE)CRCRaw;
	RawData[1] = (BYTE)(CRCRaw >> 8);
	RawData[2] = (BYTE)(CRCRaw >> 16);
	RawData[3] = (BYTE)(CRCRaw >> 24);
	RawData[4] = (BYTE)CRCEncode;
	RawData[5] = (BYTE)(CRCEncode >> 8);
	RawData[6] = (BYTE)(CRCEncode >> 16);
	RawData[7] = (BYTE)(CRCEncode >> 24);

	UXencode::EncodeEndLine(RawData, EncodedData, 8);

	if( WriteFile(hOut, EncodedData, 11, &nWritten, NULL) == 0)
		goto encerr;

	CloseHandle(hOut);

	return 0;

encerr:
	nRead = GetLastError();

	//CloseHandle(hFile);
	//CloseHandle(hOut);

	//DeleteFile(OutName);

	return nRead;
}

//Returns GetLastError() or 0 for success
//Returns 0xFFFFFFFF if file is not in correct format
//Doesn't care what the file extension is for the file you give it.  It bases UXE-ness on file content
//############################################################
DWORD UXDecodeFile(CFilePath fpEncoded)
{
	BYTE RawData[54], EncodedData[7400];
	HANDLE hEncoded, hDecoded;
	CFilePath fpDecoded;
	DWORD nRead, nWritten;
	DWORD CRCRaw, CRCEncode;
	int extlen;

	CRC32Init(&CRCRaw);
	CRC32Init(&CRCEncode);

	printf("file to decode: %s\n", fpEncoded.GetPath());

	//Open file, if error return
	if( INVALID_HANDLE_VALUE ==
			(hEncoded = CreateFile(fpEncoded.GetPath(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) )
		return GetLastError();

	//Read in first line plus extension length char
	ReadFile(hEncoded, RawData, 9, &nRead, NULL);

	CRC32Update(RawData, 9, &CRCEncode);

	if( (memcmp(RawData, "UXcode\15\12\0", 8) != 0) != 0)
		return 0xFFFFFFFF;

	extlen = RawData[8] - bias;

	if( (extlen < 0) | (extlen > 10) )
		return 0xFFFFFFFF;

	//Read in file extension, plus 2 for the end line chars
	ReadFile(hEncoded, RawData, extlen + 2, &nRead, NULL);

	CRC32Update(RawData, extlen + 2, &CRCEncode);

	RawData[ extlen ] = '\0';

	//TODO: use copy constructor instead
	fpDecoded = fpEncoded;
	fpDecoded.ChangeExtension((char*)RawData);

	printf("decoded name: %s\n", fpDecoded.GetPath());

	//Create output file, return if fail
	if( INVALID_HANDLE_VALUE ==
			(hDecoded = CreateFile(fpDecoded.GetPath(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) )
	{
		int ret = GetLastError();
		CloseHandle(hEncoded);

		return ret;
	}

	/*do
	{
		int limit;

		ReadFile(hEncoded, EncodedData, 7200, &nRead, NULL);
		CRC32Update(EncodedData, 7200, &CRCEncode);

		if(nRead != 7200)
		{
			//div_t t = div(7200, nRead);
			printf("%d", nRead);

			//while(true);
			UXencode::DecodeFullLine(&EncodedData[0], RawData);
			WriteFile(hDecoded, RawData, 54, &nWritten, NULL);

			UXencode::DecodeFullLine(&EncodedData[73], RawData);
			WriteFile(hDecoded, RawData, 54, &nWritten, NULL);

			UXencode::DecodeFullLine(&EncodedData[147], RawData);
			WriteFile(hDecoded, RawData, 54, &nWritten, NULL);

			UXencode::DecodeFullLine(&EncodedData[221], RawData);
			WriteFile(hDecoded, RawData, 54, &nWritten, NULL);

			UXencode::DecodeFullLine(&EncodedData[295], RawData);
			WriteFile(hDecoded, RawData, 54, &nWritten, NULL);

			UXencode::DecodeFullLine(&EncodedData[369], RawData);
			WriteFile(hDecoded, RawData, 54, &nWritten, NULL);

			//UXencode::DecodeFullLine(&EncodedData[431], RawData);
			//WriteFile(hDecoded, RawData, 54, &nWritten, NULL);

			//UXencode::DecodeEndLine(&EncodedData[503], RawData, UXencode::DecodeStopLine(&EncodedData[444]));
			//WriteFile(hDecoded, RawData, 10, &nWritten, NULL);

			while(true);

			//limit 
			return 3;
		}

		for(int i = 0; i < 100; i++)
		{
			UXencode::DecodeFullLine(&EncodedData[i * 74], RawData);

			CRC32Update(RawData, 54, &CRCRaw);

			WriteFile(hDecoded, RawData, 54, &nWritten, NULL);
		}

	}while(nRead == 7200);*/

	do
	{
		int i;
		ReadFile(hEncoded, EncodedData, 7400, &nRead, NULL);
		CRC32Update(EncodedData, 7400, &CRCEncode);

		if(nRead == 7400)
		{
			for(i = 0; i < 100; i++)
			{
				UXencode::DecodeFullLine(&EncodedData[i * 74], RawData);

				CRC32Update(RawData, 54, &CRCRaw);

				WriteFile(hDecoded, RawData, 54, &nWritten, NULL);
			}
		}
		else
		{
			for(int n = 0; true; n++)
			{
				if(EncodedData[n*74] == '|')
				{
					int b = UXencode::DecodeStopLine(&EncodedData[n]);

					UXencode::DecodeEndLine(&EncodedData[n+74], RawData, b);
					WriteFile(hDecoded, RawData, b, &nWritten, NULL);
					return 0;
				}
				else
				{
					UXencode::DecodeFullLine(&EncodedData[n*74], RawData);
					WriteFile(hDecoded, RawData, 54, &nWritten, NULL);
				}
			}
		}

	}while(nRead == 7400);

	/*do
	{
		if( ReadFile(hFile, EncodedData, 7200, &nRead, NULL) == 0)
			goto decerr;

		if(nRead == 7200)
		{
			CRC32Update(EncodedData, 7200, &CRCEncode);

			//for(n = 0; n < 100; n++)
			//{
			//	UXencode::DecodeFullLine(&EncodedData[n*72], RawData);

			//	CRC32Update(RawData, 54, &CRCRaw);

			//	if( WriteFile(hOut, RawData, 54, &nWritten, NULL) == 0)
			//		goto decerr;
			//}

			UXencode::DecodeFullLine(EncodedData, RawData);

			CRC32Update(RawData, 54, &CRCRaw);

			if( WriteFile(hOut, RawData, 54, &nWritten, NULL) == 0)
				goto decerr;

			while(true);
		}
		else
		{
		}

	}while(true);*/

	CloseHandle(hEncoded);
	CloseHandle(hDecoded);

	return 0;
}

//BACKUP
/*
DWORD UXDecodeFile(char* filename)
{
	BYTE RawData[54], EncodedData[7200];
	DWORD nRead, nWritten;
	DWORD CRCRaw, CRCEncode;
	char OutName[ MAX_PATH ];
	char Header[11];
	int extlen;
	int n, i;
	HANDLE hFile, hOut = INVALID_HANDLE_VALUE;

	hFile = CreateFile(filename, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
		return GetLastError();

	if( ReadFile(hFile, Header, 8, &nRead, NULL) == 0)
		goto decerr;

	CRC32Init(&CRCRaw);
	CRC32Init(&CRCEncode);
	CRC32Update(Header, 10, &CRCEncode);

	if( memcmp(Header, "UXcode\15\12\0", 8) != 0)
	{
		SetLastError((DWORD)-1);
		goto decerr;
	}

	//Read the extension length char
	if( ReadFile(hFile, Header, 1, &nRead, NULL) == 0)
	{
		SetLastError((DWORD)-1);
		goto decerr;
	}

	CRC32Update(Header, 1, &CRCEncode);

	extlen = Header[0] - bias;

	if(extlen < 0 || extlen > 10)
	{
		SetLastError((DWORD)-1);
		goto decerr;
	}

	if( ReadFile(hFile, Header, extlen, &nRead, NULL) == 0)
		goto decerr;

	CRC32Update(Header, extlen, &CRCEncode);

	Header[ extlen ] = '\0';
	strcpy(OutName, filename);
	ChangeFileExtension(OutName, Header);

	hOut = CreateFile(OutName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if(hOut == INVALID_HANDLE_VALUE)
		goto decerr;

	//DoubleUsing nRead = size of file
	if((nRead = GetFileSize(hFile, NULL)) == 0xFFFFFFFF)
		goto decerr;

	if(nRead < (DWORD)(100 + extlen)) //Minimun size of a .uxe file (with checksum)
	{
		SetLastError((DWORD)-1);
		goto decerr;
	}

	i = 0;

	do
	{
		if( ReadFile(hFile, EncodedData, 7200, &nRead, NULL) == 0)
			goto decerr;

		if(nRead == 7200)
		{
			CRC32Update(EncodedData, 7200, &CRCEncode);

			//for(n = 0; n < 100; n++)
			//{
			//	UXencode::DecodeFullLine(&EncodedData[n*72], RawData);

			//	CRC32Update(RawData, 54, &CRCRaw);

			//	if( WriteFile(hOut, RawData, 54, &nWritten, NULL) == 0)
			//		goto decerr;
			//}

			UXencode::DecodeFullLine(EncodedData, RawData);

			CRC32Update(RawData, 54, &CRCRaw);

			if( WriteFile(hOut, RawData, 54, &nWritten, NULL) == 0)
				goto decerr;

			while(true);
		}
		else
		{
		}

	}while(true);

	CloseHandle(hFile);
	CloseHandle(hOut);

	return 0;

decerr:
	nRead = GetLastError();

	CloseHandle(hFile);
	CloseHandle(hOut);

	return nRead;
}
*/