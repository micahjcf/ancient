//Color Schemes:		// Off Colors			// On Colors
#define ButtonScheme1 (B_Red    | Red_I  ),(B_Green  | Green_I)	//Normal Red\Green
#define ButtonScheme2 (B_Blue_I | White_I),(B_Teal   | White_I)	//Blue\Dark Teal
#define ButtonScheme3 (B_Teal   | White_I),(B_Blue   | White_I)	//D.Teal\D.Blue
#define ButtonScheme4 (B_Teal   | White_I),(B_Blue_I | White_I)	//D.Teal\D.Blue
#define ButtonScheme5 (B_Blue_I | White_I),(B_Teal   | Teal_I )	//Blue\Dark Teal

//***********************************************
//***********************************************
class CButton
{
	public:
		CButton(){bIsInit=false;}
		~CButton(){}

		void Setup(char* ButtonText, int xLeft, int Y, WORD offColor, WORD onColor, bool bDraw);
		void SetupOverMsg(char* MsgTxt, WORD Color, CMessageBar* pMsgBar);
		void SetState(bool Pushed){bPushedIn = Pushed;Draw();}
		void Enable(){bEnabled = true; Draw();}
		void Disable(){bEnabled = false; Draw();}
		void Draw();

		void Regulate(){OverMsg.Regulate();}
		void Run();

		BAR Position;

		bool bEnabled;
		bool bPushedIn;
		bool bChanged; //Has the button just been toggled

	private:
		COverMsg OverMsg;

		char* szText;
		WORD OffColor;
		WORD OnColor;
		bool bIsInit;
};

//***********************************************
void CButton::Setup(char* ButtonText, int xLeft, int Y, WORD offColor, WORD onColor, bool bDraw)
{
	if(bIsInit)return;

	szText = ButtonText;
	OffColor = offColor;
	OnColor = onColor;
	Position = ReturnBar(Y,xLeft,xLeft + LengthOf(szText) - 1);

	bEnabled = true;

	if(bDraw)
		Draw();
}

//***********************************************
void CButton::SetupOverMsg(char* MsgTxt, WORD Color, CMessageBar* pMsgBar)
{
	OverMsg.SetHotSpot(Position);
	OverMsg.Setup(MsgTxt, Color, CMB_ALIGN_CENTER, pMsgBar);
}

//***********************************************
void CButton::Draw()
{
	if(bEnabled)
		Text(Position.Left, Position.Y, szText, (bPushedIn?OnColor:OffColor));
	else
		Text(Position.Left, Position.Y, szText, B_Grey | White);
}

//***********************************************
void CButton::Run()
{
	if(!bEnabled)return;

	if(bChanged)
		bChanged = false;

	OverMsg.Run();

	if(Mouse.Clicked(Position))
	{
		bPushedIn = (bPushedIn?false:true);	//Toggle
		Draw();
		bChanged = true;
	}
}

//***********************************************
//***********************************************
class CCheckBox
{
	public:
		CCheckBox();
		~CCheckBox(){}

		void Setup(int xLeft, int Y, WORD color, bool bDraw);
		void SetupOverMsg(char* MsgTxt, WORD Color, CMessageBar* pMsgBar);
		void SetState(bool Checked){bChecked = Checked; Draw();}
		void Enable(){bEnabled = true; Draw();}
		void Disable(){bEnabled = false; Draw();}
		void Draw();
		void Run();

		bool isChecked(){return bChecked;}
		bool isEnabled(){return bEnabled;}

		COverMsg OverMsg;
		BAR Position;

	private:
		bool bEnabled;
		bool bChecked;
		bool bHalfClicked;

		WORD Color;
};

CCheckBox::CCheckBox()
{
	bEnabled = true;
	bChecked = false;
	bHalfClicked = false;
}

void CCheckBox::Setup(int xLeft, int Y, WORD color, bool bDraw)
{
	Position = ReturnBar(Y, xLeft, xLeft + 2);
	Color = color;

	if(bDraw)
		Draw();
}

void CCheckBox::SetupOverMsg(char* MsgTxt, WORD Color, CMessageBar* pMsgBar)
{
	OverMsg.SetHotSpot(Position);
	OverMsg.Setup(MsgTxt, Color, CMB_ALIGN_CENTER, pMsgBar);
}

void CCheckBox::Draw()
{
	if(!bEnabled)
	{
		Text(Position.Left, Position.Y, "[ ]", Grey);
		Text(Position.Left+1, Position.Y, (char)176, Grey);
		return;
	}

	if(bChecked)
		Text(Position.Left, Position.Y, "[*]", Color);
	else
		Text(Position.Left, Position.Y, "[ ]", Color);
}

void CCheckBox::Run()
{
	if(!bEnabled)return;

	OverMsg.Run();

	if(Mouse.OverBar(Position) && Mouse.bLeftClicked)
		bHalfClicked = true;

	if(Mouse.OverBar(Position) && Mouse.bLeftReleased && bHalfClicked)
	{
		bChecked = (bChecked?false:true);
		Draw();
	}

	if(Mouse.bLeftReleased)
		bHalfClicked = false;
}