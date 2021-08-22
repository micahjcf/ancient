#ifndef MJCF_ADVANCED_MOUSE
#define MJCF_ADVANCED_MOUSE

#include <Console\basic_mouse.h>

#include <Console\ScrnBuffer.h>

class CURSORMOUSE : public CONSOLEMOUSE
{
	public:
		CURSORMOUSE();

		void SetCursor(int AsciiCode, COLOR Color) {
			CursorChar = AsciiCode;
			CursorColor = DeleteBG(Color);
		}

		BOOL GetInput();

		void UpdateCursor();

		void Disable();
		void Enable();

		bool bCursorEnabled;

	private:
		void UpdateCursorShadowMemory();

		void ReprintCursor();
		void DispCursor();
		void DrawCursor();
		void EraseCursor() {Text(PrevCoords, CursorCharShadow, CursorColorShadow);}

		// Used for the cursor
		char CursorCharShadow;
		COLOR CursorColorShadow;

		COLOR CurrentColor;
		COORD PrevCoords;

		char CursorChar;
		COLOR CursorColor;
};

extern CONSOLEMOUSE Mouse;

#endif