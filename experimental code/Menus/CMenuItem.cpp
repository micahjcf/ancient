CMenuItem::CMenuItem()
{
	pNext = NULL;
	bHighlighted = false;
	pEmbMenu = NULL;
}

CMenuItem::~CMenuItem()
{
}

//**********************************************
void CMenuItem::Setup(BYTE ID, string ItemName, void(CallFunc()))
{
	ItemID = ID;
	Text = ItemName;
	isBar = false;
	isEmb = false;
	CallFunction = &CallFunc;
}

//**********************************************
void inline CMenuItem::SetupOverMsg(string Msg, COLOR Color, BYTE ShowStyle, CMessageBar* pMsgBar)
{
	OverMsg.Setup(Msg, Color, ShowStyle, pMsgBar);
}

//**********************************************
void inline CMenuItem::SetupAsSeparator()
{
	isBar = true;
	isEmb = false;
}

//**********************************************
void inline CMenuItem::SetupAsEmbedded(CEmbMenuObject* pNewEmbMenu, CMenuObject* pDaddy)
{
	pEmbMenu = pNewEmbMenu;
	isBar = false;
	isEmb = true;
	CallFunction = NULL;
	ItemID = pNewEmbMenu->MenuID;
	Text = pNewEmbMenu->Title;
	pEmbMenu->pDaddyMenu = pDaddy;
}