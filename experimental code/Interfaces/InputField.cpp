#include <windows.h>
#include <iostream>
using std::string;

#include <stdcon.h>

#include <Console\Interfaces\InputField.h>

#include <Console\Mouse.h>
#include <Console\Input.h>
#include <Console\graphics.h>

InputField::InputField()
{
}

void InputField::Setup(BAR region, COLOR c, char ch, DWORD flags)
{
	Region = region;
	TextColor = c;
	BackgroundChar = ch;
	InputFlags = flags;
	MaxLength = region.Right - region.Left;
	InputRecived = FALSE;

	ConsoleDraw::HorizLine(coord(region.Left, region.Y), region.Right - region.Left, ch, c);
}

void InputField::Run()
{
	if(!Mouse.Clicked(Region))
		return;

	SetConsoleCursorPosition(hStdOutput, coord(Region.Left, Region.Y));

	if( Input(MyText, InputFlags, MaxLength, TextColor, BackgroundChar) )
		InputRecived = TRUE;
	else
		InputRecived = FALSE;
}