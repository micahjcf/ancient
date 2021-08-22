class CMenuObject
{
public:
	CMenuObject();
	~CMenuObject();

	void Setup(BYTE, string, COORD);
	void SetupAsEmbedded(BYTE, string);

	void AddEmbeddedMenu(BYTE, string);

	void AddItem(BYTE, string, pFunc);
	void AddSeparator();

	void DrawMenu();
	void DrawEmbMenu(COORD);
	void EraseMenu();
	void SetHighlightedState(CMenuItem*, BYTE, bool);

	void Regulate();
	void Run();
	void RunEmbMenu();

	void HideOverMsgs();
	void RegulateOverMsgs();
	void RunOverMsgs();

	CMenuItem* GetItem(BYTE);
	CMenuItem* GetLastItem();
	CMenuItem* GetPrevItem(CMenuItem*);

	CMenuItem* pItemListHead;
	CMenuObject* pNext;
	BYTE MenuID;
	string Title;
	BAR Button;

	CMenuObject* pDaddyMenu;

	BYTE nItems;

	ScrnShadow Shadow;
	bool bMenuUp;
	bool bEmbMenuUp;
};