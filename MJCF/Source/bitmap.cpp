#include <windows.h>
#include <iostream>

#include <bitmap.h>

#include <kataline.h>

BOOL LoadBMP(Bitmap* bmp, char* filename)
{
	HANDLE f;
	DWORD n;
	
	if( NULL == (f = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_ALWAYS, NULL, NULL)) ) {
		SetLastErrorMsg("File not found.");
		return FALSE;
	}

	ReadFile(f, &bmp->bmfh, sizeof(bmp->bmfh), &n, NULL);

	if(n != sizeof(bmp->bmfh) || bmp->bmfh.bfType != 19778) { // 19778 == 'BM'
		SetLastErrorMsg("Incorrect file format.");
		return FALSE;
	}

	ReadFile(f, &bmp->bmih, sizeof(bmp->bmih), &n, NULL);

	if(n != sizeof(bmp->bmih)) {
		SetLastErrorMsg("Incorrect file format.");
		return FALSE;
	}

	CloseHandle(f);

	return TRUE;
}