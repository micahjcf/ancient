#ifndef _SYSTEM_
#define _SYSTEM_

// Menu Buttons
#define ClickedFileMenuButton  (Mouse.Y==0&&Mouse.X>=1&&Mouse.X<=6)
#define ClickedEditMenuButton  (Mouse.Y==0&&Mouse.X>=9&&Mouse.X<=14)
#define ClickedToolMenuButton  (Mouse.Y==0&&Mouse.X>=17&&Mouse.X<=23)
#define ClickedColorMenuButton (Mouse.Y==0&&Mouse.X>=26&&Mouse.X<=33)

// Menu
#define ClickedFileMenu (Mouse.X<=11&&Mouse.Y<=12&&Mouse.Y>=2)
#define ClickedEditMenu (Mouse.X>=8&&Mouse.X<=19&&Mouse.Y>=2&&Mouse.Y<=12)
#define ClickedToolMenu (Mouse.X>=16&&Mouse.X<=27&&Mouse.Y>=2&&Mouse.Y<=12)
#define ClickedColorMenu (Mouse.X>=25&&Mouse.X<=35&&Mouse.Y>=2&&Mouse.Y<=30)

// Menu Items
#define ClickedFileMenuItem1 (Mouse.X<=11&&Mouse.Y==3)
#define ClickedFileMenuItem2 (Mouse.X<=11&&Mouse.Y==5)
#define ClickedFileMenuItem3 (Mouse.X<=11&&Mouse.Y==7)
#define ClickedFileMenuItem4 (Mouse.X<=11&&Mouse.Y==9)
#define ClickedFileMenuItem5 (Mouse.X<=11&&Mouse.Y==11)

#define ClickedEditMenuItem1 (Mouse.X>=8&&Mouse.X<=19&&Mouse.Y==3)

#define ClickedField (Mouse.Y>1&&Mouse.Y<47)

void MenuItemSelect();

bool ActionMessage(string msg, DWORD key)
{
	msg = "< "+msg+" >";
	Text(1, 48, msg, Teal_I);
	//given two choices this should wait until one of those are pushed and return
		//true or false like (Save Picture?  space = yes, esc = no)
	return true;
}

void PrintMsg(string msg)
{
	msg = "< "+msg+" >";
	Text(1, 48, msg, Teal_I);
}

void ClearMsgBoard()
{
	DrawObject("CLEARMSGBOARD");
}

void ProcessMouseInput()
{
	if((!SysMan.MenuUp) && ClickedField)
		Draw();

	if(SysMan.DrawStat.FileMenuUp&&(!ClickedFileMenu)&&(!ClickedFileMenuButton)&&Mouse.bLeftClicked)
		DrawObject("FILEMENU_SHADOW");
	if(SysMan.DrawStat.EditMenuUp&&(!ClickedEditMenu)&&(!ClickedEditMenuButton)&&Mouse.bLeftClicked)
		DrawObject("EDITMENU_SHADOW");
	if(SysMan.DrawStat.ToolMenuUp&&(!ClickedToolMenu)&&(!ClickedToolMenuButton)&&Mouse.bLeftClicked)
		DrawObject("TOOLMENU_SHADOW");
	if(SysMan.DrawStat.ColorMenuUp&&(!ClickedColorMenu)&&(!ClickedColorMenuButton)&&Mouse.bLeftClicked)
		DrawObject("COLORMENU_SHADOW");

	if(ClickedFileMenuButton)
	{
		if(!SysMan.DrawStat.FileMenuUp)
		{
			SysMan.DrawFlag.DrawFileMenu = true;
		}
		else
		{
			DrawObject("FILEMENU_SHADOW");
		}
	}
	if(ClickedEditMenuButton)
	{
		if(!SysMan.DrawStat.EditMenuUp)
		{
			SysMan.DrawFlag.DrawEditMenu = true;
		}
		else
		{
			DrawObject("EDITMENU_SHADOW");
		}
	}
	if(ClickedToolMenuButton)
	{
		if(!SysMan.DrawStat.ToolMenuUp)
		{
			SysMan.DrawFlag.DrawToolMenu = true;
		}
		else
		{
			DrawObject("TOOLMENU_SHADOW");
		}
	}
	if(ClickedColorMenuButton)
	{
		if(!SysMan.DrawStat.ColorMenuUp)
		{
			SysMan.DrawFlag.DrawColorMenu = true;
		}
		else
		{
			DrawObject("COLORMENU_SHADOW");
		}
	}
	if(Mouse.bLeftClicked)
		MenuItemSelect();
}


void MenuItemSelect()
{
	// File Menu
	if(SysMan.DrawStat.FileMenuUp && ClickedFileMenu)
	{
		if(ClickedFileMenuItem1)
		{
		}
		if(ClickedFileMenuItem2)
		{
		}
		if(ClickedFileMenuItem3)
		{
		}
		if(ClickedFileMenuItem4)
		{
		}
		if(ClickedFileMenuItem5)
		{
			PrintMsg("Are you sure you want to quit DOS-Paint?   Space = Quit,  Any key = Cancel");
			DrawObject("FILEMENU_SHADOW");
			GetKeyboardInput();
			switch(kb.dwKeyPressed)
			{
			case VK_SPACE:
				SysMan.done = true;
				break;
			default:
				ClearMsgBoard();
				break;
			}
		}
	}
	// Edit Menu
	if(SysMan.DrawStat.EditMenuUp && ClickedEditMenu)
	{
	}
}

void DrawScrn()
{
	if(SysMan.DrawFlag.DrawScrn)
	{
		DrawObject("TOOLBAR");
		DrawObject("MSGBOARD");
	}
	if(SysMan.DrawFlag.DrawFileMenu)
		DrawObject("FILEMENU");
	if(SysMan.DrawFlag.DrawEditMenu)
		DrawObject("EDITMENU");
	if(SysMan.DrawFlag.DrawToolMenu)
		DrawObject("TOOLMENU");
	if(SysMan.DrawFlag.DrawColorMenu)
		DrawObject("COLORMENU");
}

#endif