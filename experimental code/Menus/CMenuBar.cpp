CMenuBar::CMenuBar()
{
	pMenuListHead = NULL;
	nMenus = 0;
	pMyMsgBar = NULL;
}

//**********************************************
CMenuBar::~CMenuBar()
{
	if(pMenuListHead == NULL)
		return;

	CMenuObject* pCurrent = pMenuListHead;
	CMenuObject* pNext;

	do{
		pNext = pCurrent->pNext;
		delete pCurrent;
	}while(pNext != NULL);
}

//**********************************************
void CMenuBar::Setup(BAR Bar)
{
	Position = Bar;
	Draw::BAR(Position, (char)219, MCS_MenuBar);
}


//**********************************************
void inline CMenuBar::SetDefaultMsgBar(CMessageBar* pMsgBar)
{
	pMyMsgBar = pMsgBar;
}

//**********************************************
void CMenuBar::AddMenu(BYTE MenuID, string MenuTitle)
{
	if(CheckForRoom(MenuTitle.length()) == false)
		KILL("CMenuBar::AddMenu, No room for new menu");

	if(GetMenu(MenuID) != NULL)
		KILL("CMenuBar::AddMenu, MenuID already in use");

	CMenuObject* pNewMenu = new CMenuObject;

	if(pNewMenu == NULL)
		KillProgram("CMenuBar::AddMenu, " + KP_NOMEM);

	// Setup the new Menu
	pNewMenu->Setup(MenuID, MenuTitle, GetNextMenuButtonCoords());

	// Add it to the link
	if(pMenuListHead == NULL)
		pMenuListHead = pNewMenu;
	else
		GetLastMenu()->pNext = pNewMenu;

	nMenus++;

	return;
}

//**********************************************
void CMenuBar::AddEmbeddedMenu(BYTE MenuID, BYTE EmbMenuID, string MenuTitle)
{
	CMenuObject* pMenu = GetMenu(MenuID);

	if(pMenu == NULL)
		KILL("CMenuBar::AddEmbeddedMenu, No such Menu");

	pMenu->AddEmbeddedMenu(EmbMenuID, MenuTitle);
}

//**********************************************
void CMenuBar::AddEmbeddedItem(BYTE MenuID, BYTE EmbMenuID, BYTE EmbItemID, string ItemText, void(Function()))
{
	CMenuObject* pMenu = GetMenu(MenuID);

	if(pMenu == NULL)
		KILL("CMenuBar::AddEmbeddedItem, No such Menu");

	CMenuItem* pEmb = pMenu->GetItem(EmbMenuID);

	if(pEmb == NULL)
		KILL("CMenuBar::AddEmbeddedItem, No such Embedded Menu");

	pEmb->pEmbMenu->AddItem(EmbItemID, ItemText, Function);
}

//**********************************************
void CMenuBar::AddEmbeddedSeparator(BYTE MenuID, BYTE EmbMenuID)
{
	CMenuObject* pMenu = GetMenu(MenuID);

	if(pMenu == NULL)
		KILL("CMenuBar::AddEmbeddedItem, No such Menu");

	CMenuItem* pEmb = pMenu->GetItem(EmbMenuID);

	if(pEmb == NULL)
		KILL("CMenuBar::AddEmbeddedItem, No such Embedded Menu");

	pEmb->pEmbMenu->AddSeparator();
}

//**********************************************
void CMenuBar::RemoveMenu(BYTE MenuID)
{
	if(GetMenu(MenuID) == NULL)
		KILL("CMenuBar::RemoveMenu, No such menu");

	TurnOffAllMenus();

	CMenuObject* pLinkBefore = GetPrevMenu(GetMenu(MenuID));
	CMenuObject* pLinkAfter = GetMenu(MenuID)->pNext;

	// If we are trying to delete the head
	if(pMenuListHead->MenuID == MenuID)
	{
		delete pMenuListHead;
		pMenuListHead = pLinkAfter;
		RepositionAllButtons();
		return;
	}

	CMenuObject* pCurrent = pMenuListHead;

	pCurrent = GetMenu(MenuID);

	delete pCurrent;

	pLinkBefore->pNext = pLinkAfter;

	nMenus--;

	RepositionAllButtons();
}

//**********************************************
void CMenuBar::AddItem(BYTE MenuID, BYTE ItemID, string ItemName, pFunc CallFunc)
{
	CMenuObject* pMenu = GetMenu(MenuID);

	if(pMenu == NULL)
		KILL("CMenuBar::AddItem, No such Menu");

	pMenu->AddItem(ItemID, ItemName, CallFunc);
}

//**********************************************
void CMenuBar::AddItemOverMsg(BYTE MenuID, BYTE ItemID, string Msg, COLOR Color = Teal_I, BYTE ShowStyle = CMB_ALIGN_CENTER)
{
	if(pMyMsgBar == NULL)
		KILL("CMenuBar::AddItemOverMsg, No default CMessageBar set");

	CMenuItem* pItem = GetMenu(MenuID)->GetItem(ItemID);

	if(pItem == NULL)
		KILL("CMenuBar::AddItemOverMsg, No such Menu and/or Item");

	pItem->SetupOverMsg(Msg, Color, ShowStyle, pMyMsgBar);
}

//**********************************************
void CMenuBar::AddEmbeddedItemOverMsg(BYTE MenuID, BYTE EmbMenuID, BYTE EmbItemID, string Msg, COLOR Color = Teal_I, BYTE ShowStyle = CMB_ALIGN_CENTER)
{
	if(pMyMsgBar == NULL)
		KILL("CMenuBar::AddItemOverMsg, No default CMessageBar set");

	CMenuItem* pEmbItem = GetMenu(MenuID)->GetItem(EmbMenuID)->pEmbMenu->GetItem(EmbItemID);

	if(pEmbItem == NULL)
		KILL("CMenuBar::AddEmbeddedItemOverMsg, No such Menu and/or Item");

	pEmbItem->SetupOverMsg(Msg, Color, ShowStyle, pMyMsgBar);
}

//**********************************************
void CMenuBar::AddSeparator(BYTE MenuID)
{
	CMenuObject* pMenu = GetMenu(MenuID);

	if(pMenu == NULL)
		KILL("CMenuBar::AddItem, No such Menu");

	pMenu->AddSeparator();
}

//**********************************************
void CMenuBar::Draw()
{
	Draw::BAR(Position, (char)219, MCS_MenuBar);

	if(pMenuListHead == NULL)
		return;

	TurnOffAllMenus();

	CMenuObject* pCurrent = pMenuListHead;

	while(true)
	{
		Draw::BAR(pCurrent->Button, ' ', MCS_ButtonOFF);
		Text(pCurrent->Button.Left + 1, pCurrent->Button.Y, pCurrent->Title, MCS_ButtonTextOFF);

		if(pCurrent->pNext == NULL)
			return;

		pCurrent = pCurrent->pNext;
	}
}

//**********************************************
void CMenuBar::Run()
{
	if(pMenuListHead == NULL)
		return;

	CMenuObject* pCurrent = pMenuListHead;

	do{
		pCurrent->Regulate();
		pCurrent = pCurrent->pNext;
	}while(pCurrent != NULL);

	pCurrent = pMenuListHead;

	do{
		pCurrent->Run();
		pCurrent = pCurrent->pNext;
	}while(pCurrent != NULL);
}

//**********************************************
CMenuObject* CMenuBar::GetMenu(BYTE ID)
{
	if(pMenuListHead == NULL)
		return NULL;

	CMenuObject* pCurrent = pMenuListHead;

	while(true)
	{
		if(pCurrent->MenuID == ID)
			return pCurrent;

		if(pCurrent->pNext == NULL)
			return NULL;

		pCurrent = pCurrent->pNext;
	}
}

//**********************************************
CMenuObject* CMenuBar::GetLastMenu()
{
	if(pMenuListHead == NULL)
		return NULL;

	CMenuObject* pCurrent = pMenuListHead;

	while(pCurrent->pNext != NULL)
		pCurrent = pCurrent->pNext;

	return pCurrent;
}

//**********************************************
CMenuObject* CMenuBar::GetPrevMenu(CMenuObject* pMenu)
{
	if(pMenuListHead == NULL)
		return NULL;

	CMenuObject* pCurrent = pMenuListHead;

	if(pMenuListHead == pMenu)
		return NULL;

	while(true)
	{
		if(pCurrent->pNext == pMenu)
			return pCurrent;

		if(pCurrent->pNext == NULL)
			return NULL;

		pCurrent = pCurrent->pNext;
	}
}

//**********************************************
COORD CMenuBar::GetNextMenuButtonCoords()
{
	if(pMenuListHead == NULL)
		return ReturnCoord(Position.Left+2, Position.Y);

	return ReturnCoord(GetLastMenu()->Button.Right+2, Position.Y);
}

//**********************************************
bool CMenuBar::CheckForRoom(BYTE NewButtonTextLength)
{
	if(pMenuListHead == NULL)
	{
		if((2 + NewButtonTextLength) > (Position.Right - 1))
			return false;
		else
			return true;
	}

	if((GetLastMenu()->Button.Right + 2 + NewButtonTextLength) > Position.Right - 1)
		return false;

	return true;
}

//**********************************************
void CMenuBar::RepositionAllButtons()
{
	if(pMenuListHead == NULL)
		return;

	// Reposition the head
	pMenuListHead->Button = ReturnBar(Position.Y, Position.Left + 2,(Position.Left + 3 + pMenuListHead->Title.length()));

	CMenuObject* pCurrent = pMenuListHead->pNext;

	if(pCurrent == NULL)
		return;

	BAR LastButton;

	while(true)
	{
		LastButton = GetPrevMenu(pCurrent)->Button;

		pCurrent->Button = ReturnBar(Position.Y, LastButton.Right + 2,(LastButton.Right + 3 + pCurrent->Title.length()));

		if(pCurrent->pNext == NULL)
			break;

		pCurrent = pCurrent->pNext;
	}

	Draw();
}

//**********************************************
void CMenuBar::TurnOffAllMenus()
{
	if(pMenuListHead == NULL)
		return;

	CMenuObject* pCurrent = pMenuListHead;

	while(true)
	{
		if(pCurrent->bMenuUp)
			pCurrent->EraseMenu();

		if(pCurrent->pNext == NULL)
			break;

		pCurrent = pCurrent->pNext;
	}
}