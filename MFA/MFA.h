#define MFAHASHSIZE 32

typedef struct _MFAState
{
	BYTE	MsgBlock[ 80 ];
	DWORD	Intermediate_Hash[ 8 ];
	DWORD	Length_High;
	DWORD	Length_Low;
	DWORD	C_High;
	DWORD	C_Low;
	DWORD	SequenceState;
} MFAState;

void MFAInit(MFAState* State);
void MFAUpdate(MFAState* State, BYTE* M, UINT nBytes);
void MFAResult(MFAState* State, BYTE Hash[ MFAHASHSIZE ]);

#define MFACustomStart(state, a, b, c, d, e, f, g, h) \
	{ \
	(state)->Intermediate_Hash[0] = a; \
	(state)->Intermediate_Hash[1] = b; \
	(state)->Intermediate_Hash[2] = c; \
	(state)->Intermediate_Hash[3] = d; \
	(state)->Intermediate_Hash[4] = e; \
	(state)->Intermediate_Hash[5] = f; \
	(state)->Intermediate_Hash[6] = g; \
	(state)->Intermediate_Hash[7] = h; \
	}