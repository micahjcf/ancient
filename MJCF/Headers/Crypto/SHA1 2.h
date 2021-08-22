#define SHA1HashSize 20

typedef struct _SHA1State
{
	BYTE	Message_Block[ 64 ];
	DWORD	Intermediate_Hash[ 5 ];
	DWORD	Length_Low;
	DWORD	Length_High;
} SHA1State;

typedef SHA1State SHA1IMEState;

void SHA1Init(SHA1State*);
void SHA1Update(SHA1State*, BYTE*, UINT);
void SHA1Result(SHA1State*, BYTE[ SHA1HashSize ]);

void SHA1_IME_Update(SHA1IMEState*, BYTE*, UINT);
void SHA1_IME_Result(SHA1IMEState*, BYTE[ SHA1HashSize ]);