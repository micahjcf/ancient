class CMenuItem
{
public:
	CMenuItem();
	~CMenuItem();

	void Setup(BYTE, string, pFunc);
	void SetupOverMsg(string, COLOR, BYTE, CMessageBar*);
	void SetupAsSeparator();
	void SetupAsEmbedded(CEmbMenuObject*, CMenuObject*);

	void Call(){CallFunction();}

	CMenuItem* pNext;
	string Text;
	BYTE ItemID;
	pFunc CallFunction;
	bool isBar;
	bool isEmb;

	CEmbMenuObject* pEmbMenu;

	COverMsg OverMsg;

	bool bHighlighted;
};