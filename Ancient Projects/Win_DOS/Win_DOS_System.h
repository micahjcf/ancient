#ifndef _WD_SYSTEM_
#define _WD_SYSTEM_

/***************************************************************
/**Mouse Functions
***/
void ProcessClick()
{
	if(SysMan.DrawStat.RightClickMenuUp)
	{
		DrawObject("RIGHTCLICKMENU_SHADOW");
	}
	if(Mouse.bRightClicked && !ClickedStartMenu)
	{
		DrawObject("RIGHTCLICKMENU");
	}
/***
/**Start Button
***/if(ClickedStartButton && Mouse.bLeftClicked)
	{
		if(SysMan.DrawStat.StartMenuUp)
		{
			DrawObject("STARTMENU_SHADOW");
			return;
		}
		else
		{
			SysMan.DrawFlag.DrawStartMenu = true;
			return;
		}
	}

/***
/**Start Menu
***/
	if(SysMan.DrawStat.StartMenuUp)
	{
		if(!ClickedStartMenu || Mouse.bRightClicked)
		{
			DrawObject("STARTMENU_SHADOW");
			return;
		}
		else
		{
			if(ClickedMenuItem1)
			{
			}
			if(ClickedMenuItem2)
			{
			}
			if(ClickedMenuItem3)
			{
			}
			if(ClickedMenuItem4)
			{
			}
			if(ClickedMenuItem5)
			{
			}
			if(ClickedMenuItem6)
			{
			}
			if(ClickedMenuItem7)
			{
				SysMan.Shutdown = true;
			}
		}
		return;
	}
	if(Mouse.bRightClicked)
	{
		if(SysMan.DrawStat.RightClickMenuUp)
		{
			DrawObject("RIGHTCLICKMENU_SHADOW");
		}
		DrawObject("RIGHTCLICKMENU");
	}
}

/***************************************************************
/**Win_DOS GUI Functions
***/
// This function draws the entire screen (taskbar, start menu, windows, ...)
void DrawScrn()
{
	if(SysMan.DrawFlag.DrawTaskbar)
	{
		DrawObject("TASKBAR");
	}

	// Draw your windows  (BEFORE THE START MENU)

	if(SysMan.DrawFlag.DrawStartMenu)	// Draw the start menu
		DrawObject("STARTMENU");
}

#endif