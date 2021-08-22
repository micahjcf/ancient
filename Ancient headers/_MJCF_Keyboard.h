/*
	Needed include files/namespaces
#include <conio.h>
#include <_MJCF_ConGlob.h>
*/

#ifndef _MJCF_KEYOARD_
#define _MJCF_KEYOARD_

#define REPEAT 0x0001

struct KEYBOARD
{
	DWORD	dwKeyPressed;
};KEYBOARD kb;

// NOTE: KB_WAIT() may also be passed a char ( KB_WAIT('P') ) but it must be uppercase!
void KB_WAIT(DWORD dwKey)
{
	do{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
	}while(InputRecord.Event.KeyEvent.wVirtualKeyCode != dwKey);

	// Keeps from repeating by reading input until key is released
	do{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
	}while(InputRecord.Event.KeyEvent.bKeyDown);
}

void inline Pause()
{
	while(!kbhit());
}

void GetKeyboardInput(BYTE KeyRepeat = false)
{
	// Allow repeating
	if(KeyRepeat & 0x0001 == 0x0001)
	{
		do{
			ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		}while(!InputRecord.Event.KeyEvent.bKeyDown);
	}
	else
	{
		do{
			ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		}while(!InputRecord.Event.KeyEvent.bKeyDown);
		
		do{
			ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		}while(InputRecord.Event.KeyEvent.bKeyDown);
	}

	kb.dwKeyPressed = InputRecord.Event.KeyEvent.wVirtualKeyCode;
}

void inline FlushKeyboard()
{
	kb.dwKeyPressed = 0;
}

void inline WaitForKeyRelease()
{
	do{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
	}while(InputRecord.Event.KeyEvent.bKeyDown);
}

#endif