#include <windows.h>
#include <stdlib.h>
#include <crtdbg.h>

#include <Console\stdcon.h>

#include <FilePath.h>

CFilePath::CFilePath()
{
	path[0] = '\0';
}

CFilePath::CFilePath(char* path)
{
	*this = path; //This is OK!  I overloaded the = operator
}

//Do not call with a . in ext
//Call with "" to get rid of extension
void CFilePath::ChangeExtension(char* ext)
{
	_ASSERTE( !strrchr(ext, '.') );
	_ASSERT( path[0] );

	char* dot = strrchr(path, '.');

	if( dot )
		*dot = '\0';

	if(! ext[0])
		return;

	if(strlen(path) + 1 + strlen(ext) >= MAX_PATH)
	{
		_ASSERT(0);
		//MessageBox(hThisWindow, "Execution has been stopped to prevent a possible fatal error.\nCause: File name too long.\nProgram will now terminate.", "Buffer overrun prevention", MB_OK | MB_ICONSTOP);
		exit(1);
	}
	else
	{
		//I made sure it won't go past the buffer...
		#pragma warning(disable : 4996) //'function' deprecation warning
		strcat(path, ".");
		strcat(path, ext);
		#pragma warning(default : 4996)
	}
}

BOOL CFilePath::ThisFileExists()
{
	return FileExists(path);
}

const char* CFilePath::GetPath()
{
	return (const char*)path;
}

const char* CFilePath::GetFileName()
{
	if( char* dot = strrchr(path, '\\') )
		return dot + 1;
	else
		return NULL;
}

const char* CFilePath::GetExtension()
{
	if( char* dot = strrchr(path, '.') )
		return dot + 1;
	else
		return NULL;
}

char* CFilePath::operator=(char* operand)
{
	int n = 0;

	while(path[n] = operand[n])
		if(++n == MAX_PATH - 1)
			break;

	path[n] = '\0';

	return path;
}

CFilePath::operator char*()
{
	return path;
}
/*
	GetLastError() returns ERROR_FILE_NOT_FOUND the files doesn't exist.
*/
BOOL FileExists(const char* filename)
{
	HANDLE file = CreateFile(filename, NULL, NULL, NULL, OPEN_EXISTING, NULL, NULL);

	if(file == INVALID_HANDLE_VALUE)
		return FALSE;
	else
	{
		CloseHandle(file);
		return TRUE;
	}
}

//DO NOT HAVE A PERIOD IN THE GIVEN EXTENSION
/*void ChangeFileExtension(char* filename, char* ext)
{
	char* dot = strrchr(filename, '.');

	if( dot )
		*dot = '\0';

	strcat(filename, ".");
	strcat(filename, ext);
}

char* GetFileExt(char* filename)
{
	if(char* ext = strrchr(filename, '.') )
		return ext + 1;
	else
		return NULL;
}*/
