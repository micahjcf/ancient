#define MJCF_DOSBASIC
#define MJCF_DOSUI
#define MJCF_DOSMENUS

#include <StdInc.h>

CMenuBar MBar;
CMessageBar MsgBar;
bool done = false;

/*
			Menu System + Interfaces

Create methods:

SetItemStatus()
DisableMenuItems()
SetEmbItemStatus()
DisableEmbMenu()
ect...

add [BYTE Status] to CMenuItem

we shouldn't have to make a system to add/remove items
if we can just grey out (disable) the items we dont want
to use at a particular moment in time.
*/

//MenuID
#define FileMenu		1
#define EditMenu		2

//ItemID
#define FileEmbNew		1
#define FileQuit		2

#define EditCopy		1

//EmbItemID
#define FileEmbNewS		1
#define FileEmbNewA		2

void Copy()
{
	cout<<"\n\nCopied.";
}

void FNS()
{
	cout<<"\n\nSingle.";
}

void FNA()
{
	cout<<"\n\nArchive.";
}

void QQQ()
{
	done = true;
}

void main()
{
	Console::SetWindowSize(80, 50);
	Console::ClrScrn();
	Console::SetCursorVisibility(false);

	MsgBar.Setup(SCRN_YMAX, 0, 79, Green_I, true);
	MsgBar.PrintMsg("Default Message");

	MBar.Setup(ReturnBar(0, 0, 79));
	MBar.SetDefaultMsgBar(&MsgBar);

	MBar.AddMenu(FileMenu, "File");
	MBar.AddEmbeddedMenu(FileMenu, FileEmbNew, "New");
	MBar.AddEmbeddedItem(FileMenu, FileEmbNew, FileEmbNewS, "Single File", FNS);
	MBar.AddEmbeddedItem(FileMenu, FileEmbNew, FileEmbNewA, "File Archive", FNA);
	MBar.AddItem(FileMenu, FileQuit, "Quit", QQQ);

	MBar.AddMenu(EditMenu, "Edit");
	MBar.AddItem(EditMenu, EditCopy, "Copy", Copy);

	//exit(0);

	while(!done)
	{
		MsgBar.Run();

		if(!Mouse.GetInput())
			continue;

		if(Mouse.bLeftClicked)
		{
			//MBar.SetItemStatus(FileMenu, FileClose, DMS_ITEM_GREY);
		}
		if(Mouse.bRightClicked)
		{
			//MBar.SetItemStatus(FileMenu, FileClose, DMS_ITEM_NORMAL);
		}

		MBar.Run();
	}
}
