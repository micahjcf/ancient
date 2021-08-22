#ifndef MJCF_DOS_MOUSE
#define MJCF_DOS_MOUSE

#include <Console\ScrnBuffer.h>

class CONSOLEMOUSE
{
	public:
		CONSOLEMOUSE();

		BOOL GetInput();

		BOOL OverScrnBuffer(ScrnShadow&);
		BOOL OverRectangle(SMALL_RECT&);
		BOOL OverBar(BAR&);
		BOOL OverCoord(COORD& c) {return Position == c;}

		// Only true for left click
		BOOL Clicked(ScrnShadow&);
		BOOL Clicked(SMALL_RECT&);
		BOOL Clicked(BAR&);
		BOOL Clicked(COORD&);

		void WaitForActivity();

		INPUT_RECORD InputBuffer;
		COORD Position;

		bool bClicked;
		bool bLeftClicked;
		bool bRightClicked;
		bool bDoubleClicked;
		bool bLeftDown;
		bool bRightDown;
		bool bLeftReleased;
		bool bRightReleased;

	protected:
		void Update();
};

extern CONSOLEMOUSE Mouse;

#endif