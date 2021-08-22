//#define MOUSE_NO_ICON

#include <MJCF\StdInc.h>

#define FILE_MENU 1
#define EDIT_MENU 2
#define TOOL_MENU 3
#define VIEW_MENU 4
#define HELP_MENU 5

CButton RB;

CMessageBar MsgBar;
CButton Button;
CCheckBox Check;

CMenuBar MenuBar;
CMarqueeBar Scroll;

void Setup()
{
	MsgBar.Setup(0,0,79,Yellow_I,true);
	MsgBar.PrintMsg("DEMO: February 25, 2005");

	Button.Setup(" Button ", 38, 7, ButtonScheme1, true);
	Button.SetupOverMsg("You are over the button", Purple_I, &MsgBar);

	RB.Setup("Remove Tool Menu", 29, 38, ButtonScheme1, true);

	Check.Setup(43, 10, Grey, true);
	Check.SetupOverMsg("You are over the check box", Purple, &MsgBar);
	Text(47, 10, "Check Box");

	MenuBar.Setup(ReturnBar(1,0,79), (B_White_I | Blue), ButtonScheme2);
	MenuBar.AddMenu(FILE_MENU, " File ", "Basic.sbd", "FileMenu");
	MenuBar.AddMenu(EDIT_MENU, " Edit ", "Basic.sbd", "EditMenu");
	MenuBar.AddMenu(TOOL_MENU, " Tool ", "Basic.sbd", "ToolMenu");
	MenuBar.AddMenu(VIEW_MENU, " View ", "Basic.sbd", "ViewMenu");
	MenuBar.AddMenu(HELP_MENU, " Help ", "Basic.sbd", "HelpMenu");

	Scroll.Setup(ReturnBar(48,0,79), Blue | B_White_I, 6, true);
	Scroll.SetText("Scrolling Text!!!!!!", Yellow_I);
}

SYSTEMTIME tm;

void ShowTime()
{
	static PrevSec = tm.wSecond-1;
	GetSystemTime(&tm);

	if(tm.wSecond != PrevSec)
	{
		PrevSec = tm.wSecond;
		Text(1,30,' ');
		Text(0,30,tm.wSecond,Yellow_I);
	}
}

bool killRB = false;
bool addRB = false;
bool set = false;

void main(int argc, char** args)
{
	Console.SetWindowSize(80,50);
	Console.SetWindowTitle("DEMO | Micah Fullerton");
	Console.ClrScrn();

	Setup();

	//WORD Color = B_White_I | Red_I;

	//Text(15,15,'*',Color);
	//Text(15,16,'*',FlipFGBG(Color));

	while(true)
	{
		ShowTime();

		Scroll.Run();

		if(!Mouse.GetInput())
			continue;

		Text(1,25,' ');
		Text(0,25,Mouse.Position.X);
		Text(1,26,' ');
		Text(0,26,Mouse.Position.Y);

		Button.OverMsg.Regulate();
		Check.OverMsg.Regulate();

		if(!addRB)
			RB.Run();

		Button.Run();
		MenuBar.RunMenuBar();
		Check.Run();

		if(killRB && (!addRB) && (!set))
		{
			RB.Setup("Add Tool Menu", 15, 32, ButtonScheme1, true);
			set = true;
		}

		if(!addRB)
		{
			if(RB.bChanged && killRB)
			{
				addRB = true;
				MenuBar.AddMenu(TOOL_MENU, " Tool ", "Basic.sbd", "ToolMenu");
				Draw::BAR(RB.Position, ' ', Black);
				Mouse.UpdateIconMemory();
			}

			if(RB.bChanged && (!killRB))
			{
				killRB = true;
				MenuBar.RemoveMenu(TOOL_MENU);
				Draw::BAR(RB.Position, ' ', Black);
				Mouse.UpdateIconMemory();
			}
		}
	}

	ErrorLog.CleanUp();
}
