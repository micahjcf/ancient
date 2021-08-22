#ifndef _MJCF_BASICUI_
#define _MJCF_BASICUI_

#define GUI_ROUTINE

#define GeneralMsgClr	Green_I
#define NoticeMsgClr	Yellow_I
#define ErrorMsgClr		Red_I

// Show styles
#define CMB_ALIGN_CENTER		0x01
#define CMB_ALIGN_LEFT			0x02

#define CMB_SCROLL_ALIGN		0x04 // OR with show styles

//***********************************************
//***********************************************
class CMessageBar
{
	public:
		void Setup(BAR pos, COLOR MsgBarColor);
		void Draw();
		void Clear();

		void PrintMsg(char* Msg, BYTE ShowStyle, COLOR EndColor, COLOR );
		void ClearMsg();
		void PrintOverMsg(char* OverMsg, BYTE ShowStyle, WORD Color);
		void ClearOverMsg();

		void Run();

		BAR Position;

	private:
		COLOR EndColor;	// the end < and > chars
		COLOR MainColor;
		int PrevTime;
		int Counter;

		bool bMsgUp;
		bool bOverMsgUp;

		char* Msg;
		COLOR MsgColor;
		BYTE DispStyle;
		SHORT ScrollDest;
		SHORT CurrentX;

		char* OverMsg;
		COLOR OverMsgColor;
		BYTE OverMsgDispStyle;
		SHORT OverMsgScrollDest;
		SHORT OverMsgCurrentX;
};

//***********************************************
//***********************************************
/*
class COverMsg
{
	public:
		COverMsg() {bEnabled = false;}

		void Setup(string OverMsg, COLOR MsgColor, BYTE ShowStyle, CMessageBar* pMsgBar);

		void SetHotSpot(SMALL_RECT SR){
			HotSpot = ReturnRect(SR.Left, SR.Top, SR.Right, SR.Bottom);
		}

		void SetHotSpot(BAR B){
			HotSpot = ReturnRect(B.Left, B.Y, B.Right, B.Y);
		}

		void Enable(){
			bEnabled = true;
		}

		void Disable();

		void Hide();
		void Regulate();
		void Run();

	private:
		SMALL_RECT HotSpot;
		CMessageBar* MyMsgBar;

		string Msg;
		COLOR Color;
		BYTE DispStyle;

		bool bOverMsgUp;
		bool bEnabled;
};

//***********************************************
//***********************************************
class CMarqueeBar
{
	public:
		CMarqueeBar() {}

		void Setup(BAR position, COLOR color, int speed, bool draw);
		void Draw(){Draw::BAR(Position, (char)219, BarColor);}

		void Run();

		void SetText(string NewText, COLOR Color){ScrollingText=NewText;TextColor=Color;}
		void SetSpeed(int NewSpeed){nSpeed=NewSpeed;}

		BAR GetPosition(){return Position;}

	private:
		BAR Position;
		int nSpeed;
		COLOR BarColor;
		COLOR TextColor;
		string ScrollingText;

		int PrevSec;
		int Counter;
		int Index;
		int Length;
		int xPos;
};
*/
#endif