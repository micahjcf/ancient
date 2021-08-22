class CMenuBar
{
public:
	CMenuBar();
	~CMenuBar();

	void Setup(BAR);
	void SetDefaultMsgBar(CMessageBar*);

	void AddMenu(BYTE, string);
	void AddEmbeddedMenu(BYTE, BYTE, string);
	void AddEmbeddedItem(BYTE, BYTE, BYTE, string, pFunc);
	void AddEmbeddedSeparator(BYTE, BYTE);

	void RemoveMenu(BYTE);

	void AddItem(BYTE, BYTE, string, pFunc);
	void AddItemOverMsg(BYTE, BYTE, string, COLOR, BYTE);
	void AddEmbeddedItemOverMsg(BYTE, BYTE, BYTE, string, COLOR, BYTE);
	void AddSeparator(BYTE);

	void Draw();

	void Run();

private:

	CMenuObject* GetMenu(BYTE);
	CMenuObject* GetLastMenu();
	CMenuObject* GetPrevMenu(CMenuObject*);

	COORD GetNextMenuButtonCoords();
	bool CheckForRoom(BYTE);
	void RepositionAllButtons();
	void TurnOffAllMenus();

	CMenuObject* pMenuListHead;
	CMessageBar* pMyMsgBar;

	BAR	Position;
	int nMenus;
};