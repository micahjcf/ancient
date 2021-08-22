#ifndef _MJCF_SBO_MENU_SYSTEM_
#ifndef _MJCF_MENU_SYSTEM_
#define _MJCF_MENU_SYSTEM_

#define MenuDrawDelay		15

//Menu Color Scheme
#define MCS_MenuBar			(B_White_I | Blue)

#define MCS_ButtonOFF		(B_Blue_I | White_I)
#define MCS_ButtonON		(B_Teal | White_I)
#define MCS_ButtonTextOFF	(B_Blue_I | White_I)
#define MCS_ButtonTextON	(B_Teal | White_I)

#define MCS_MenuBorder		(B_Blue | Teal_I)
#define MCS_ItemText		(B_Blue | White_I)
#define MCS_ItemTextHigh	(B_Teal | White_I)
#define MCS_ItemTextBlank	(B_White_I | Blue)
#define MCS_ItemBlankHigh	(B_White_I | Teal)

#define DMS_ITEM_GREY	1
#define DMS_ITEM_NORMAL	2

class CMenuObject;
#define CEmbMenuObject	CMenuObject

#include <Menus\CMenuItem.h>
#include <Menus\CMenuObject.h>
#include <Menus\CMenuBar.h>

#include <Menus\CMenuItem.cpp>
#include <Menus\CMenuObject.cpp>
#include <Menus\CMenuBar.cpp>

#endif
#endif
