CMenuObject::CMenuObject()
{
	pItemListHead = NULL;
	pNext = NULL;
	nItems = 0;
	bMenuUp = false;
	bEmbMenuUp = false;
	pDaddyMenu = NULL;
}

//**********************************************
CMenuObject::~CMenuObject()
{
	if(pItemListHead == NULL)
		return;

	CMenuItem* pCurrent = pItemListHead;
	CMenuItem* pNext;

	/*do{
		Next = pCurrent->pNext;
		delete pCurrent;
	}while(Next != NULL);*/

	while(true)
	{
		if(!pCurrent)
			break;

		pNext = pCurrent->pNext;

		delete pCurrent;

		pCurrent = pNext;
	}
}

//**********************************************
void CMenuObject::Setup(BYTE ID, string ButtonText, COORD ButtonPos)
{
	MenuID = ID;
	Title = ButtonText;
	Button = ReturnBar(ButtonPos.Y, ButtonPos.X, ButtonPos.X + ButtonText.length() + 1);

	// Draw the button
	Draw::BAR(Button, ' ', MCS_ButtonOFF);
	Text(Button.Left + 1, Button.Y, Title, MCS_ButtonTextOFF);
}

//**********************************************
void CMenuObject::SetupAsEmbedded(BYTE ID, string MenuText)
{
	MenuID = ID;
	Title = MenuText;
	Button = ReturnBar(0, 0, 0);
}

void CMenuObject::AddEmbeddedMenu(BYTE EmbMenuID, string MenuTitle)
{
	// Check if that ID is already being used for an item
	if(GetItem(EmbMenuID) != NULL)
		KILL("CMenuObject::AddEmbeddedMenu, ItemID already in use.");

	CEmbMenuObject* pEmbMenu = new CMenuObject;

	if(!pEmbMenu)
		KillProgram((string)"CMenuObject::AddEmbeddedMenu" + KP_NOMEM);

	pEmbMenu->SetupAsEmbedded(EmbMenuID, MenuTitle);

	CMenuItem* pEmbItem = new CMenuItem;

	if(!pEmbItem)
		KillProgram((string)"CMenuObject::AddEmbeddedMenu" + KP_NOMEM);

	pEmbItem->SetupAsEmbedded(pEmbMenu, this);

	// Add it to the link
	if(pItemListHead == NULL)
		pItemListHead = pEmbItem;
	else
		GetLastItem()->pNext = pEmbItem;

	nItems++;
}

//**********************************************
void CMenuObject::AddItem(BYTE ItemID, string ItemName, void(Function()))
{
	// Check if that item ID is already being used
	if(GetItem(ItemID) != NULL)
		KILL("CMenuObject::AddItem, ItemID already in use.");

	CMenuItem* pNewItem = new CMenuItem;

	if(!pNewItem)
		KillProgram((string)"CMenuObject::AddItem" + KP_NOMEM);

	// Setup the new item
	pNewItem->Setup(ItemID, ItemName, Function);

	// Add it to the link
	if(pItemListHead == NULL)
		pItemListHead = pNewItem;
	else
		GetLastItem()->pNext = pNewItem;

	nItems++;
}

//**********************************************
void CMenuObject::AddSeparator()
{
	CMenuItem* pNewItem = new CMenuItem;

	if(!pNewItem)
		KillProgram((string)"CMenuObject::AddSeperator" + KP_NOMEM);

	pNewItem->SetupAsSeparator();

	// Add it to the link
	if(pItemListHead == NULL)
		pItemListHead = pNewItem;
	else
		GetLastItem()->pNext = pNewItem;

	nItems++;
}

//**********************************************
void CMenuObject::DrawMenu()
{
	if(bMenuUp)
		return;

	bMenuUp = true;

	// Draw the button
	Draw::BAR(Button, ' ', MCS_ButtonON);
	Text(Button.Left + 1, Button.Y, Title, MCS_ButtonTextON);

	CMenuItem* pCurrent = pItemListHead;

	BYTE MenuWidth = 12;
	BYTE MenuHeight = nItems + 2;

	// Make sure the menu is wide enough
	for(int n = 0; n<nItems; n++)
	{
		if(pCurrent->isBar != true)
		{
			if(MenuWidth <= pCurrent->Text.length() + 1)
				if(pCurrent->isEmb)
					MenuWidth = pCurrent->Text.length() + 3;
				else
					MenuWidth = pCurrent->Text.length() + 2;
		}
		pCurrent = pCurrent->pNext;
	}

	// Get the top left corner of the menu
	COORD MenuCoords = ReturnCoord(Button.Left, Button.Y + 1);

	// Setup the shadow
	Shadow.GetFromScreen(ReturnRect(MenuCoords.X, MenuCoords.Y, MenuCoords.X + MenuWidth, MenuCoords.Y + MenuHeight));

	// Reset item pointer pCurrent
	pCurrent = pItemListHead;

	BYTE y = MenuCoords.Y;

	// Draw the top of the menu
	Draw::HorizLine(y, MenuCoords.X, MenuWidth, (char)196, MCS_MenuBorder);
	Text(MenuCoords.X, y, (char)218, MCS_MenuBorder);
	Text(MenuCoords.X + MenuWidth - 1, y, (char)191, MCS_MenuBorder);
	y++;

	Sleep(MenuDrawDelay);

	if(pCurrent != NULL)
	{
		while(true)
		{
			if(pCurrent->isBar)
			{
				Draw::HorizLine(y, MenuCoords.X + 1, MenuWidth - 2, (char)196, MCS_MenuBorder);
				Text(MenuCoords.X, y, (char)195, MCS_MenuBorder);
				Text(MenuCoords.X + MenuWidth - 1, y, (char)180, MCS_MenuBorder);
			}
			else
			{
				Draw::HorizLine(y, MenuCoords.X + 1, MenuWidth - 2, (char)219, MCS_ItemTextBlank);
				Text(MenuCoords.X, y, (char)179, MCS_MenuBorder);
				Text(MenuCoords.X + MenuWidth - 1, y, (char)179, MCS_MenuBorder);

				Text(MenuCoords.X + 1, y, pCurrent->Text, MCS_ItemText);

				if(pCurrent->isEmb)
				{
					Text(MenuCoords.X + MenuWidth - 1, y, (char)16, MCS_MenuBorder);
					pCurrent->OverMsg.SetHotSpot(ReturnBar(y, MenuCoords.X + 1, MenuCoords.X + MenuWidth - 1));
				}
				else
					pCurrent->OverMsg.SetHotSpot(ReturnBar(y, MenuCoords.X + 1, MenuCoords.X + MenuWidth - 2));
			}

			y++;

			Sleep(MenuDrawDelay);

			// If this is the last item
			if(pCurrent->pNext == NULL)
				break;

			pCurrent = pCurrent->pNext;
		}
	}

	//Draw the bottom of the menu
	Draw::HorizLine(y, MenuCoords.X, MenuWidth, (char)196, MCS_MenuBorder);
	Text(MenuCoords.X, y, (char)192, MCS_MenuBorder);
	Text(MenuCoords.X + MenuWidth - 1, y, (char)217, MCS_MenuBorder);
}

//**********************************************
void CMenuObject::DrawEmbMenu(COORD MenuCoords)
{
	if(bMenuUp)
		return;

	bMenuUp = true;

	CMenuItem* pCurrent = pItemListHead;

	BYTE MenuWidth = 12;
	BYTE MenuHeight = nItems + 2;

	// Make sure the menu is wide enough
	for(int n = 0; n<nItems; n++)
	{
		if(pCurrent->isBar != true)
		{
			if(MenuWidth <= pCurrent->Text.length() + 1)
					MenuWidth = pCurrent->Text.length() + 3;
		}
		pCurrent = pCurrent->pNext;
	}

	// Setup the shadow
	Shadow.GetFromScreen(ReturnRect(MenuCoords.X, MenuCoords.Y, MenuCoords.X + MenuWidth, MenuCoords.Y + MenuHeight));

	// Reset item pointer pCurrent
	pCurrent = pItemListHead;

	BYTE y = MenuCoords.Y;

	// Draw the top of the menu
	Draw::HorizLine(y, MenuCoords.X, MenuWidth, (char)196, MCS_MenuBorder);
	Text(MenuCoords.X, y, (char)218, MCS_MenuBorder);
	Text(MenuCoords.X + MenuWidth - 1, y, (char)191, MCS_MenuBorder);
	y++;

	Sleep(MenuDrawDelay);

	if(pCurrent != NULL)
	{
		while(true)
		{
			if(pCurrent->isBar)
			{
				Draw::HorizLine(y, MenuCoords.X + 1, MenuWidth - 2, (char)196, MCS_MenuBorder);
				Text(MenuCoords.X, y, (char)195, MCS_MenuBorder);
				Text(MenuCoords.X + MenuWidth - 1, y, (char)180, MCS_MenuBorder);
			}
			else
			{
				Draw::HorizLine(y, MenuCoords.X + 1, MenuWidth - 2, (char)219, MCS_ItemTextBlank);
				Text(MenuCoords.X, y, (char)179, MCS_MenuBorder);
				Text(MenuCoords.X + MenuWidth - 1, y, (char)179, MCS_MenuBorder);

				Text(MenuCoords.X + 1, y, pCurrent->Text, MCS_ItemText);

				pCurrent->OverMsg.SetHotSpot(ReturnBar(y, MenuCoords.X + 1, MenuCoords.X + MenuWidth - 2));
			}

			y++;

			Sleep(MenuDrawDelay);

			if(pCurrent->pNext == NULL)
				break;

			pCurrent = pCurrent->pNext;
		}
	}

	Draw::HorizLine(y, MenuCoords.X, MenuWidth, (char)196, MCS_MenuBorder);
	Text(MenuCoords.X, y, (char)192, MCS_MenuBorder);
	Text(MenuCoords.X + MenuWidth - 1, y, (char)217, MCS_MenuBorder);
}

//**********************************************
void CMenuObject::EraseMenu()
{
	if(bEmbMenuUp)
		return;

	if(bMenuUp == false)
		return;

	bMenuUp = false;

	// Draw the button
	Draw::BAR(Button, ' ', MCS_ButtonOFF);
	Text(Button.Left + 1, Button.Y, Title, MCS_ButtonTextOFF);

	Shadow.Draw();
}

//**********************************************
void CMenuObject::Regulate()
{
	if(bMenuUp == false)
		return;

	if((!Mouse.OverScrnBuffer(Shadow)) && (!Mouse.OverBar(Button)))
		EraseMenu();
}

//**********************************************
void CMenuObject::Run()
{
	if(bMenuUp)
	{
		if(pItemListHead == NULL)
			return;

		CMenuItem* pCurrent = pItemListHead;
		BYTE Y = Shadow.Edges.Top + 1;

		RegulateOverMsgs();
		RunOverMsgs();

		while(true)
		{
			if((!pCurrent->isBar) && (!pCurrent->isEmb))
			{
				if(Mouse.OverBar(ReturnBar(Y, Shadow.Edges.Left + 1, Shadow.Edges.Right - 1)))
					SetHighlightedState(pCurrent, Y, true);
				else if(pCurrent->bHighlighted)
					SetHighlightedState(pCurrent, Y, false);

				if(Mouse.Clicked(ReturnBar(Y, Shadow.Edges.Left + 1, Shadow.Edges.Right - 1)))
				{
					EraseMenu();
					pCurrent->Call();
					HideOverMsgs();
					return;
				}
			}

			//This routine takes care of:
			//1) Highlighting the Embedded Menu's "button" item
			//2) Erasing and drawing the menu
			//3) Calling the Embedded Menu's Run() function
			if(pCurrent->isEmb)
			{
				if(Mouse.OverBar(ReturnBar(Y, Shadow.Edges.Left + 1, Shadow.Edges.Right)))
				{
					SetHighlightedState(pCurrent, Y, true);
					pCurrent->pEmbMenu->DrawEmbMenu(ReturnCoord(Shadow.Edges.Right + 1, Y));
					bEmbMenuUp = true;
				}
				else
				{
					SetHighlightedState(pCurrent, Y, false);

					if(!Mouse.OverScrnBuffer(pCurrent->pEmbMenu->Shadow))
					{
						if(pCurrent->pEmbMenu->bMenuUp)
						{
							//Erase the menu
							pCurrent->pEmbMenu->bMenuUp = false;
							pCurrent->pEmbMenu->Shadow.Draw();
							bEmbMenuUp = false;
						}
					}
				}
				pCurrent->pEmbMenu->RunEmbMenu();
			}

			if(pCurrent->pNext == NULL)
				return;

			pCurrent = pCurrent->pNext;
			Y++;
		}
	}

	if(bMenuUp == false)
	{
		if(Mouse.OverBar(Button))
			DrawMenu();
	}
}

//**********************************************
void CMenuObject::RunEmbMenu()
{
	if(bMenuUp)
	{
		if(pItemListHead == NULL)
			return;

		CMenuItem* pCurrent = pItemListHead;
		BYTE Y = Shadow.Edges.Top + 1;

		RegulateOverMsgs();
		RunOverMsgs();

		while(true)
		{
			if((!pCurrent->isBar) && (!pCurrent->isEmb))
			{
				if(Mouse.OverBar(ReturnBar(Y, Shadow.Edges.Left + 1, Shadow.Edges.Right - 1)))
					SetHighlightedState(pCurrent, Y, true);
				else if(pCurrent->bHighlighted)
					SetHighlightedState(pCurrent, Y, false);

				if(Mouse.Clicked(ReturnBar(Y, Shadow.Edges.Left + 1, Shadow.Edges.Right - 1)))
				{
					//Erase the menu
					bMenuUp = false;
					Shadow.Draw();

					pDaddyMenu->bEmbMenuUp = false;
					pDaddyMenu->EraseMenu();
					HideOverMsgs();
					pCurrent->Call();
					return;
				}
			}

			if(pCurrent->pNext == NULL)
				return;

			pCurrent = pCurrent->pNext;
			Y++;
		}
	}
}

//**********************************************
void CMenuObject::HideOverMsgs()
{
	if(pItemListHead == NULL)
			return;

	CMenuItem* pCurrent = pItemListHead;

	do{
		pCurrent->OverMsg.Hide();
		pCurrent = pCurrent->pNext;
	}while(pCurrent != NULL);
}

//**********************************************
void CMenuObject::RegulateOverMsgs()
{
	if(pItemListHead == NULL)
			return;

	CMenuItem* pCurrent = pItemListHead;

	do{
		pCurrent->OverMsg.Regulate();
		pCurrent = pCurrent->pNext;
	}while(pCurrent != NULL);
}

//**********************************************
void CMenuObject::RunOverMsgs()
{
	if(pItemListHead == NULL)
			return;

	CMenuItem* pCurrent = pItemListHead;

	do{
		pCurrent->OverMsg.Run();
		pCurrent = pCurrent->pNext;
	}while(pCurrent != NULL);
}

//**********************************************
void CMenuObject::SetHighlightedState(CMenuItem* pItem, BYTE Y, bool State)
{
	if(pItem->bHighlighted == State)
		return;

	pItem->bHighlighted = (State == true);

	ULONG N;
	BYTE TextLength = pItem->Text.length() + 1;

	if(State)
		Text(Shadow.Edges.Left, Y, (char)'>', MCS_ItemTextHigh);
	else
		Text(Shadow.Edges.Left, Y, (char)179, MCS_MenuBorder);

	// Color the text
	WORD Color = (State)?(MCS_ItemTextHigh):(MCS_ItemText);
	for(BYTE n = Shadow.Edges.Left + 1; n < Shadow.Edges.Left + TextLength; n++)
		WriteConsoleOutputAttribute(hOutput, &Color, 1, ReturnCoord(n, Y), &N);

	// Color the rest of it
	Color = (State)?(MCS_ItemBlankHigh):(MCS_ItemTextBlank);
	for(; n < Shadow.Edges.Right; n++)
		WriteConsoleOutputAttribute(hOutput, &Color, 1, ReturnCoord(n, Y), &N);
}

//**********************************************
CMenuItem* CMenuObject::GetItem(BYTE ID)
{
	if(pItemListHead == NULL)
		return NULL;

	CMenuItem* pCurrent = pItemListHead;

	while(true)
	{
		if(pCurrent->ItemID == ID)
			return pCurrent;

		if(pCurrent->pNext == NULL)
			return NULL;

		pCurrent = pCurrent->pNext;
	}
}

//**********************************************
CMenuItem* CMenuObject::GetLastItem()
{
	if(pItemListHead == NULL)
		return NULL;

	CMenuItem* pCurrent = pItemListHead;

	while(pCurrent->pNext != NULL)
		pCurrent = pCurrent->pNext;

	return pCurrent;
}

//**********************************************
CMenuItem* CMenuObject::GetPrevItem(CMenuItem* pItem)
{
	if(pItemListHead == NULL)
		return NULL;

	CMenuItem* pCurrent = pItemListHead;

	if(pItemListHead == pItem)
		return NULL;

	while(true)
	{
		if(pCurrent->pNext == pItem)
			return pCurrent;

		if(pCurrent->pNext == NULL)
			return NULL;

		pCurrent = pCurrent->pNext;
	}

	return pCurrent;
}
