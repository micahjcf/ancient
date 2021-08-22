#define MFAHashSize 32

typedef struct _MFAState
{
	DWORD	Intermediate_Hash[ 8 ];
	DWORD	C_High;
	DWORD	C_Low;
	BYTE	MsgBlock[ 80 ];
	UINT	MsgIndex;
	DWORD	Length_High;
	DWORD	Length_Low;
	DWORD	SequenceState;
} MFAState;

void MFAInit(MFAState* State);
void MFAUpdate(MFAState* State, BYTE* M, UINT nLen);
void MFAResult(MFAState* State, BYTE Hash[ MFAHashSize ]);
