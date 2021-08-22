#ifndef _MJCF_SBO_MENU_SYSTEM_
#define _MJCF_SBO_MENU_SYSTEM_

class CMenuObject
{
	public:
		CMenuObject();
		~CMenuObject(){delete[] OverMsgs;}

		bool Setup(int ID, string GraphicsSourceFile, string SBOLabel);
		void SetupButton(COORD ButtonCoords, string text, WORD ButtonOnColor, WORD ButtonOffColor);
		void SetupOverMsg(string, WORD, int, CMessageBar*);

		void DrawButton();

		void Enable(){bEnabled=true;DrawButton();}
		void Disable(){bEnabled=false;DrawButton();}
		void Toggle();
		void Regulate();
		void Run();
		int GetChoice();

		int GetMenuID(){return nMenuID;}
		CMenuObject* GetNextMenuObject(){return pNextMenuObject;}
		bool IsEnabled(){return bEnabled;}
		bool IsMenuUp(){return bMenuUp;}

		void SetNextMenuObject(CMenuObject* pNew){pNextMenuObject = pNew;}

		ScrnBuffer Graphics;
		ScrnBuffer Shadow;
		COverMsg* OverMsgs;
		int nOverMsgs;

		BAR ButtonBar;
		string ButtonText;

	private:
		int nMenuID;
		CMenuObject* pNextMenuObject;

		bool bEnabled;
		bool bMenuUp;

		WORD OnColor;
		WORD OffColor;
};

CMenuObject::CMenuObject()
{
	pNextMenuObject = NULL;
	OverMsgs = NULL;
	nOverMsgs = 0;

	bEnabled = true;
	bMenuUp = false;
}

bool CMenuObject::Setup(int ID, string GraphicsSourceFile, string SBOLabel)
{
	if(!Graphics.LoadFromFile(GraphicsSourceFile, SBOLabel))
		return false;

	COORD MenuCoords = ReturnCoord(ButtonBar.Left, ButtonBar.Y+1);

	if(MenuCoords.X + Graphics.Size.X > SCRN_XMAX)
		MenuCoords.X = SCRN_WIDTH - Graphics.Size.X;

	Shadow.SetSize(Graphics.Size.X, Graphics.Size.Y);
	Shadow.FillBuffer(' ', 0);

	Graphics.Place(MenuCoords.X,MenuCoords.Y);
	Shadow.Place(MenuCoords.X, MenuCoords.Y);

	nOverMsgs = (Graphics.Size.Y-1)/2;
	OverMsgs = new COverMsg[nOverMsgs];

	nMenuID = ID;
	return true;
}

void CMenuObject::SetupButton(COORD ButtonCoords, string text, WORD ButtonOnColor, WORD ButtonOffColor)
{
	ButtonText = text;
	ButtonBar = ReturnBar(ButtonCoords.Y, ButtonCoords.X, (ButtonCoords.X + text.length() - 1));
	OnColor = ButtonOnColor;
	OffColor = ButtonOffColor;
}

void CMenuObject::SetupOverMsg(string Msg, WORD Color, int ChoiceNum, CMessageBar* pMsgBar)
{
	if((ChoiceNum < 0) && (ChoiceNum > nOverMsgs))
		return;

	BAR Area = ReturnBar(Graphics.Edges.Top+(ChoiceNum*2)-1, Graphics.Edges.Left,
		Graphics.Edges.Right-1);

	OverMsgs[ChoiceNum-1].Setup(Msg, Color, pMsgBar);
	OverMsgs[ChoiceNum-1].SetHotSpot(Area);
}

void CMenuObject::DrawButton()
{
	if(!bEnabled)
	{
		Text(ButtonBar.Left, ButtonBar.Y, ButtonText, B_Grey | White);
		return;
	}

	Text(ButtonBar.Left, ButtonBar.Y, ButtonText, (bMenuUp?OffColor:OnColor));

#if defined _MJCF_MOUSE_ADVANCED_
	if(Mouse.OverBar(ButtonBar))
		Mouse.UpdateIconShadowMemory();
#endif
}

void CMenuObject::Toggle()
{
	if(bMenuUp)
	{
		bMenuUp = false;
		Shadow.Draw();

		// Turn off all Over Messages
		for(int n=0; n<nOverMsgs; n++)
			OverMsgs[n].Hide();
	}
	else
	{
#if defined _MJCF_MOUSE_ADVANCED_
		if(Mouse.OverScrnBuffer(Graphics))
			Mouse.EraseIcon();
#endif
		bMenuUp = true;
		Shadow.FillFromScreen();
		Graphics.Draw();
	}
	DrawButton();

#if defined _MJCF_MOUSE_ADVANCED_
	if(Mouse.OverScrnBuffer(Graphics))
		Mouse.UpdateIconShadowMemory();
#endif
}

void CMenuObject::Regulate()
{
	if((!bMenuUp) || (!bEnabled))
		return;

	if(!Mouse.bLeftClicked)
		return;

	//Get rid of menu if button is toggled or mouse clicked off menu
	if((!Mouse.Clicked(ButtonBar)) && (!Mouse.Clicked(Graphics)))
	{
		bMenuUp = false;
		Shadow.Draw();
		DrawButton();
	}
}

void CMenuObject::Run()
{
	//static bool ShadowFirstDraw = true;

	if(!bEnabled)
		return;

	if(Mouse.Clicked(ButtonBar))
	{
		if(bMenuUp)
		{
			bMenuUp = false;
			Shadow.Draw();
			DrawButton();
		}
		else
		{
			bMenuUp = true;
			Shadow.FillFromScreen();
			Graphics.Draw();
			DrawButton();
		}
	}
}

int CMenuObject::GetChoice()
{
	if(!Mouse.bLeftClicked)
		return 0;

	if((!bMenuUp) || (!Mouse.OverRectangle(Graphics.Edges)))
		return 0;

	int Choice = (Mouse.Position.Y - Graphics.Edges.Top + 1);

	// If you hit a choice
	if(!wholenum(((double)Choice/2)))
		Toggle();
	else
		return 0;

	// Turn off all Over Messages
	for(int n=0; n<nOverMsgs; n++)
		OverMsgs[n].Hide();

	return (Choice / 2);
}

//*******************************************************
//*******************************************************
//CMenuBar Error Codes:
#define MENU_SETUP_FAILURE		1
#define MENU_ID_NOT_FOUND		2
#define MENU_ID_ALREADY_IN_USE	3
#define MENUBAR_FULL			4
//*******************************************************
class CMenuBar
{
	public:
		CMenuBar();
		~CMenuBar();

		void Setup(BAR Position, WORD Color, WORD ButtonOnColors, WORD ButtonOffColors);

		int AddMenu(int ID, string ButtonText, string GraphicsSourceFile, string SBOLabel);
		bool RemoveMenu(int MenuID);

		void ViewList();

		void ToggleMenu(int ID);
		void EnableMenu(int ID);
		void DisableMenu(int ID);
		void TurnOffAllMenus();
		int GetMenuChoice(int ID);
		void SetMenuOverMsg(int ID, string Msg, WORD Color, int ChoiceNum, CMessageBar* pMsgBar)
		{
			if(GetMenuObject(ID) == NULL)
				return;
			GetMenuObject(ID)->SetupOverMsg(Msg, Color, ChoiceNum, pMsgBar);
		}

		void DOS_GUI_ROUTINE RunMenuBar();

		BAR GetPosition(){return Position;}

	private:
		bool CheckForRoom(string);
		COORD GetNextButtonCoords();
		CMenuObject* GetLastMenuObject();
		CMenuObject* GetMenuObject(int ID);
		bool IsLastMenuObject(CMenuObject* pMenu){return (pMenu->GetNextMenuObject()==NULL);}
		CMenuObject* GetPrevMenuObject(CMenuObject*);
		void AddMenuNodeToTail(CMenuObject*);
		void PrintAddMenuError(int, string);
		void RepositionAllButtons();
		int NumberOfMenus;

		bool isInit;
		BAR Position;
		WORD Color;
		WORD ButtonOnColor;
		WORD ButtonOffColor;

		void Draw();

		CMenuObject* pMenuListHead;
};

CMenuBar::CMenuBar()
{
	pMenuListHead = NULL;
	isInit = false;
	NumberOfMenus = 0;
}

CMenuBar::~CMenuBar()
{
	if(NumberOfMenus == 0)
		return;

	if(NumberOfMenus == 1)
	{
		delete pMenuListHead;
		return;
	}

	CMenuObject* pCurrentNode = pMenuListHead;
	CMenuObject* pNext = pMenuListHead->GetNextMenuObject();

	while(true)
	{
		delete pCurrentNode;

		pCurrentNode = pNext;
		pNext = pNext->GetNextMenuObject();

		if((!pNext) || IsLastMenuObject(pCurrentNode))
			break;
	}
}

//*****************
void CMenuBar::ViewList()
{
	ErrorLog.AddEntry("\nLinked list of MenuBar:");

	for(int n=0; n<NumberOfMenus; n++)
	{
		ErrorLog.Write('(');
		ErrorLog.Write(n);
		ErrorLog.Write(") - ");
		ErrorLog.Write((int*)GetMenuObject(n+1));
		ErrorLog.Write('\n');
	}

	ErrorLog.Write("Head - ");
	ErrorLog.Write((int*)pMenuListHead);
	ErrorLog.Write("\nTail - ");
	ErrorLog.Write((int*)GetLastMenuObject());
	ErrorLog.Write("\nMemory Usage: ");

	int Size = sizeof(CMenuBar)+(sizeof(CMenuObject) * NumberOfMenus);

	ErrorLog.Write(Size);
	ErrorLog.Write(" Bytes\n\n");
}
//*****************

void CMenuBar::ToggleMenu(int ID)
{
	CMenuObject* pMenu = GetMenuObject(ID);

	if(pMenu == NULL)
		return;

	pMenu->Toggle();
}

void CMenuBar::EnableMenu(int ID)
{
	CMenuObject* pMenu = GetMenuObject(ID);

	if(pMenu == NULL)
		return;

	pMenu->Enable();
}

void CMenuBar::DisableMenu(int ID)
{
	CMenuObject* pMenu = GetMenuObject(ID);

	if(pMenu == NULL)
		return;

	pMenu->Disable();
}

void CMenuBar::TurnOffAllMenus()
{
	if(pMenuListHead == NULL)
		return;

	CMenuObject* pCurrentNode = pMenuListHead;

	while(true)
	{
		if(pCurrentNode->IsMenuUp())
			pCurrentNode->Toggle();

		if(IsLastMenuObject(pCurrentNode))
			break;

		pCurrentNode = pCurrentNode->GetNextMenuObject();
	}
}

int CMenuBar::GetMenuChoice(int ID)
{
	if(!GetMenuObject(ID))
		return -1;
	return GetMenuObject(ID)->GetChoice();
}

//*******************************************************
void CMenuBar::Setup(BAR brPosition, WORD color, WORD ButtonOnColors, WORD ButtonOffColors)
{
	Position = brPosition;
	Color = color;
	ButtonOnColor = ButtonOnColors;
	ButtonOffColor = ButtonOffColors;

	isInit = true;

	Draw::BAR(Position, (char)219, Color);
}

//*******************************************************
int CMenuBar::AddMenu(int ID, string ButtonText, string GraphicsSourceFile, string SBOLabel)
{
	if(!isInit)
		PrintCriticalError("Uninitialized CMenuBar object is adding a menu");

	if(!CheckForRoom(ButtonText))
		return MENUBAR_FULL;

	// Check if an existing menu has that ID
	if(GetMenuObject(ID) != NULL)
		return MENU_ID_ALREADY_IN_USE;

	// Create a new menu object off the heap
	CMenuObject* NewMenu = new CMenuObject;

	// If it could not be created
	if(NewMenu == NULL)
		return -1;

	NewMenu->SetupButton(GetNextButtonCoords(), ButtonText, ButtonOnColor, ButtonOffColor);

	if(!NewMenu->Setup(ID, GraphicsSourceFile, SBOLabel))
	{
		delete NewMenu;
		PrintAddMenuError(ID, ButtonText);
		return MENU_SETUP_FAILURE;
	}

	AddMenuNodeToTail(NewMenu);

	Draw();

	NumberOfMenus++;

	return 0;
}

bool CMenuBar::RemoveMenu(int MenuID)
{
	TurnOffAllMenus();

	if(GetMenuObject(MenuID) == NULL)
		return false;

	if(pMenuListHead == NULL)
		return false;

	CMenuObject* pLinkBefore = GetPrevMenuObject(GetMenuObject(MenuID));
	CMenuObject* pLinkAfter = GetMenuObject(MenuID)->GetNextMenuObject();

	CMenuObject* pCurrentNode;

	// If we are trying to delete the head
	if(pMenuListHead->GetMenuID() == MenuID)
	{
		delete pMenuListHead;
		pMenuListHead = pLinkAfter;
		RepositionAllButtons();
		return true;
	}

	// If we are trying to delete the tail
	if(GetLastMenuObject()->GetMenuID() == MenuID)
	{
		pCurrentNode = GetLastMenuObject();
		GetPrevMenuObject(pCurrentNode)->SetNextMenuObject(NULL);
		delete pCurrentNode;
		RepositionAllButtons();
		return true;
	}

	pCurrentNode = GetMenuObject(MenuID);
	delete pCurrentNode;

	pLinkBefore->SetNextMenuObject(pLinkAfter);

	NumberOfMenus--;

	RepositionAllButtons();
	return true;
}

//*******************************************************
COORD CMenuBar::GetNextButtonCoords()
{
	if(pMenuListHead == NULL)
		return ReturnCoord(Position.Left + 1, Position.Y);

	return ReturnCoord((GetLastMenuObject()->ButtonBar.Right + 2), Position.Y);
}

//*******************************************************
void CMenuBar::Draw()
{
	if(!isInit)
		PrintCriticalError("Uninitalized CMenuBar Object being drawn");

	Draw::BAR(Position, (char)219, Color);

	if(pMenuListHead == NULL)
		return;

	CMenuObject* pCurrentNode = pMenuListHead;

	while(true)
	{
		pCurrentNode->DrawButton();

		if(IsLastMenuObject(pCurrentNode))
			break;

		pCurrentNode = pCurrentNode->GetNextMenuObject();
	}
}

//*******************************************************
CMenuObject* CMenuBar::GetLastMenuObject()
{
	if(pMenuListHead == NULL)
		return NULL;

	CMenuObject* pCurrentNode = pMenuListHead;

	while(pCurrentNode->GetNextMenuObject() != NULL)
		pCurrentNode = pCurrentNode->GetNextMenuObject();

	return pCurrentNode;
}

//*******************************************************
CMenuObject* CMenuBar::GetPrevMenuObject(CMenuObject* pNode)
{
	if(pMenuListHead == NULL)
		return NULL;

	CMenuObject* pCurrentNode = pMenuListHead;

	if(pMenuListHead == pNode)
		return NULL;

	while(true)
	{
		if(pCurrentNode->GetNextMenuObject() == pNode)
			return pCurrentNode;

		if(pCurrentNode->GetNextMenuObject() == NULL)
			return NULL;

		pCurrentNode = pCurrentNode->GetNextMenuObject();
	}
	return pCurrentNode;
}

//*******************************************************
void CMenuBar::AddMenuNodeToTail(CMenuObject* pNewTail)
{
	if(pMenuListHead == NULL)
		pMenuListHead = pNewTail;
	else
		GetLastMenuObject()->SetNextMenuObject(pNewTail);
}

//*******************************************************
CMenuObject* CMenuBar::GetMenuObject(int ID)
{
	if(pMenuListHead == NULL)
		return NULL;

	CMenuObject* pCurrentNode = pMenuListHead;

	while(true)
	{
		if(pCurrentNode->GetMenuID() == ID)
			break;

		if(pCurrentNode == GetLastMenuObject())
			return NULL;

		pCurrentNode = pCurrentNode->GetNextMenuObject();
	}

	return pCurrentNode;
}

//*******************************************************
void DOS_GUI_ROUTINE CMenuBar::RunMenuBar()
{
	if(pMenuListHead == NULL)
		return;

	CMenuObject* pCurrentNode = pMenuListHead;

	while(true)
	{
		pCurrentNode->Regulate();

		for(int n=0; n<pCurrentNode->nOverMsgs; n++)
			pCurrentNode->OverMsgs[n].Regulate();

		if(IsLastMenuObject(pCurrentNode))
			break;

		pCurrentNode = pCurrentNode->GetNextMenuObject();
	}

	pCurrentNode = pMenuListHead;

	while(true)
	{
		pCurrentNode->Run();

		if(pCurrentNode->IsMenuUp())
		{
			for(int n=0; n<pCurrentNode->nOverMsgs; n++)
				pCurrentNode->OverMsgs[n].Run();
		}

		if(IsLastMenuObject(pCurrentNode))
			break;

		pCurrentNode = pCurrentNode->GetNextMenuObject();
	}
}

void CMenuBar::PrintAddMenuError(int ID, string ButtonText)
{
	ErrorLog.AddEntry("\n*** Resulting error caused a CMenuBar::AddMenu() failure");
	ErrorLog.Write("Menu ID: ");
	ErrorLog.Write(ID);
	ErrorLog.Write("\nButtonText: \"");
	ErrorLog.Write(ButtonText);
	ErrorLog.Write("\"\n");
}

bool CMenuBar::CheckForRoom(string ButtonText)
{
	if(pMenuListHead == NULL)
		return true;
	BAR LastButton = GetLastMenuObject()->ButtonBar;

	if((LastButton.Right + 2 + ButtonText.length() - 1) > SCRN_XMAX)
		return false;

	return true;
}

//There is no need to update Shadow's graphics because all menus are turned
// Off when you remove a menu
void CMenuBar::RepositionAllButtons()
{
	if(pMenuListHead == NULL)
		return;

	// Reposition the head
	pMenuListHead->ButtonBar = ReturnBar(Position.Y, Position.Left + 1,(Position.Left + 1 + pMenuListHead->ButtonText.length() - 1));
	pMenuListHead->Graphics.Place(Position.Left+1, Position.Y+1);
	pMenuListHead->Shadow.Place(Position.Left+1, Position.Y+1);

	CMenuObject* pCurrentNode = pMenuListHead->GetNextMenuObject();
	BAR LastButton;
	COORD ButtonCoords;
	COORD MenuCoords;

	while(true)
	{
		LastButton = GetPrevMenuObject(pCurrentNode)->ButtonBar;
		ButtonCoords = ReturnCoord(LastButton.Right+2, Position.Y);
		MenuCoords = ReturnCoord(ButtonCoords.X, Position.Y+1);

		pCurrentNode->ButtonBar = ReturnBar(ButtonCoords.Y, ButtonCoords.X,(ButtonCoords.X + pCurrentNode->ButtonText.length() - 1));
		pCurrentNode->Graphics.Place(MenuCoords.X, MenuCoords.Y);
		pCurrentNode->Shadow.Place(MenuCoords.X, MenuCoords.Y);

		if(IsLastMenuObject(pCurrentNode))
			break;

		pCurrentNode = pCurrentNode->GetNextMenuObject();
	}

	Draw();
}

#endif