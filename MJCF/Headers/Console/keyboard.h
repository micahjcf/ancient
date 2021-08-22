#ifndef MJCF_KEYBOARD
#define MJCF_KEYBOARD

enum K_Keys {K_ALT = 0x0001, K_CTRL = 0x0002, K_SHIFT = 0x0004, K_ENTER = 0x0008, K_ESCAPE = 0x0010, K_BACKSPACE = 0x0020,
			K_TAB = 0x0040, K_DELETE = 0x0080, K_INSERT = 0x0100, K_UP = 0x0200, K_DOWN = 0x0400, K_LEFT = 0x0800, K_RIGHT = 0x1000};

enum K_FKeys { FUNC1 = 0x00010000, FUNC2 = 0x00020000, FUNC3 = 0x00040000, FUNC4 = 0x00080000, FUNC5 = 0x00100000, FUNC6 = 0x00200000,
				FUNC7 = 0x00400000, FUNC8 = 0x00800000, FUNC9 = 0x01000000, FUNC10 = 0x02000000, FUNC11 = 0x04000000, FUNC12 = 0x08000000 };

class KEYBOARD
{
	public:
		KEYBOARD() : bInputRecieved(FALSE) {}

		BOOL GetInput();

		//You can OR different keys in here to check for combos
		BOOL Pressed(UINT Keys) {
			return (KeysPressed & Keys) == Keys;
		}

		BOOL bInputRecieved;
		char AsciiKey;
private:
		DWORD KeysPressed;
		INPUT_RECORD InputBuffer;
};

#endif