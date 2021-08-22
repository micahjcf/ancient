#ifndef MJCF_INPUT
#define MJCF_INPUT

#define INPUT_PASSWORD	0x0002
#define INPUT_HIDE		0x0004

#define INPUT_ALPHA		0x0008
#define INPUT_NUM		0x0010
#define INPUT_ALL		0x0020

#define INPUT_SPACE		0x0040

#define _input(var, flags, length) Input(var, flags, length, White, ' ')

BOOL Input(unsigned long& Number,
		   DWORD Flags,
		   UINT  MaxLength = 9,
		   COLOR color = White,
		   char  EmptyChar = ' ');

BOOL Input(std::string& st,
		   DWORD Flags = INPUT_ALL,
		   UINT	 MaxLength = 20,
		   COLOR color = White,
		   char  EmptyChar = ' ');

#endif