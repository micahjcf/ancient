#define MD4HashSize	16

typedef struct _MD4State
{
	DWORD Intermediate_Hash[4];
	DWORD Length[2];
	BYTE MsgBlock[64];
} MD4State;

void MD4Init(MD4State* State);
void MD4Update(MD4State* State, BYTE* M, UINT nLen);
void MD4Result(MD4State* State, BYTE digest[ MD4HashSize ]);