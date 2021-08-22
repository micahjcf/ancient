#include <windows.h>

#include <Console\stdcon.h>
#include <Console\keyboard.h>

BOOL KEYBOARD::GetInput()
{
	DWORD Events;

	bInputRecieved = FALSE;

	GetNumberOfConsoleInputEvents(hStdInput, &Events);

	if(!Events)
		return FALSE;

	ReadConsoleInput(hStdInput, &InputBuffer, 1, &Events);

	//Don't do anything for a key release
	if(InputBuffer.EventType != KEY_EVENT || (!InputBuffer.Event.KeyEvent.bKeyDown))
		return FALSE;

	bInputRecieved = TRUE;

	if(InputBuffer.Event.KeyEvent.uChar.AsciiChar < 32 || InputBuffer.Event.KeyEvent.uChar.AsciiChar > 126)
		AsciiKey = NULL;
	else
		AsciiKey = InputBuffer.Event.KeyEvent.uChar.AsciiChar;

	KeysPressed = 0;

	//Put the least important keys on top.  Ctrl and shift are on here because they can't be used
	//	 for combos and it's hard to read accurate input for them
	if(InputBuffer.Event.KeyEvent.dwControlKeyState & (RIGHT_CTRL_PRESSED | LEFT_CTRL_PRESSED))
		KeysPressed = K_CTRL;

	if(InputBuffer.Event.KeyEvent.dwControlKeyState & SHIFT_PRESSED)
		KeysPressed = K_SHIFT;

	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode == VK_TAB)
		KeysPressed = K_TAB;

	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
		KeysPressed = K_ESCAPE;

	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
		KeysPressed = K_ENTER;

	if(InputBuffer.Event.KeyEvent.dwControlKeyState & (RIGHT_ALT_PRESSED | LEFT_ALT_PRESSED))
		KeysPressed = K_ALT;

	//Everything below can be OR'ed in so that key combos work (Alt + ?)
	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode == VK_BACK)
		KeysPressed |= K_BACKSPACE;

	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode == VK_DELETE)
		KeysPressed |= K_DELETE;

	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode == VK_INSERT)
		KeysPressed |= K_INSERT;

	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode == VK_UP)
		KeysPressed |= K_UP;

	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
		KeysPressed |= K_DOWN;

	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
		KeysPressed |= K_LEFT;

	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
		KeysPressed |= K_RIGHT;

	//Function Keys
	if(InputBuffer.Event.KeyEvent.wVirtualKeyCode >= VK_F1 && InputBuffer.Event.KeyEvent.wVirtualKeyCode <= VK_F12)
		KeysPressed |= FUNC1 << (InputBuffer.Event.KeyEvent.wVirtualKeyCode - VK_F1);
	
	return TRUE;
}