#include <windows.h>
#include <string>

#include <type.h>
#include <Console\stdcon.h>

#ifndef _DEBUG
	static const char tm[] = "none.like.us";
//#pragma comment(exestr, "none.liks.us")
#endif

//Cruel, cruel code...
//SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);// Turn off  monitor

using std::string;

#include <Kataline.h>

SMALL_RECT gWindowRect;

#define LAST_ERROR_MSG_SIZE		80
char gszLastErrorMsg[ LAST_ERROR_MSG_SIZE ];

BOOL SetConsoleWindowAlwaysOnTop(BOOL OnTop)
{
	return ::SetWindowPos(hThisWindow, (OnTop) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void SetupKatalineConsole(char* title, COORD size)
{
	ClearLastErrorMsg();

#ifdef USE_CUSTOM_CTRL_HANDLER
	if(! SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE))
		goto fail;
#endif

	gWindowRect = rect(0, 0, size.X - 1, size.Y - 1);

	//Now no matter what properties are set for the console, it will always be the size I want it to be
	if(! SetConsoleWindowInfo(hStdOutput, 1, &gWindowRect))
	{
		if(! SetConsoleScreenBufferSize(hStdOutput, size))
			goto fail;

		if(! SetConsoleWindowInfo(hStdOutput, 1, &gWindowRect))
			goto fail;
	}
	else if(! SetConsoleScreenBufferSize(hStdOutput, size))
			goto fail;

	if(! SetConsoleMode(hStdInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT))
		goto fail;

	if(! SetConsoleMode(hStdOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT))
		goto fail;

	if(title)
		if(! SetConsoleTitle(title))
			goto fail;

	ClrScrn();

	return;

fail:
	MessageBox(hThisWindow, "Console failed to setup", "Console Error", MB_OK);
	exit(2);
}

const char* GetLastErrorMsg()
{
	if( gszLastErrorMsg[0] == '\0' )
		SetLastErrorMsg("No Error");

	return gszLastErrorMsg;
}

void SetLastErrorMsg(string msg)//(const char* msg)
{
	strcpy_s(gszLastErrorMsg, LAST_ERROR_MSG_SIZE, msg.c_str());
}

void ClearLastErrorMsg()
{
	gszLastErrorMsg[0] = '\0';
}