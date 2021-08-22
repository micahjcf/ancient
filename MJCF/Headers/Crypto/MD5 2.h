#define MD5HashSize	16

typedef struct _MD5State
{
	BYTE	MsgBlock[ 64 ];
	DWORD	Intermediate_Hash[ 4 ];
	DWORD	Length_Low;
	DWORD	Length_High;
} MD5State;

void MD5Init(MD5State* State);
void MD5Update(MD5State* State, BYTE* inBuf, UINT nLen);
void MD5Result(MD5State* State, BYTE digest[ MD5HashSize ]);