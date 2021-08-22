typedef unsigned int	UINT;
typedef unsigned long	DWORD;
typedef unsigned char	BYTE;

#define bitsize(x) (sizeof(x) << 3)
#define rotl(x, n) (((x) << (n)) | ((x) >> (bitsize(x) - (n))))

#include <Crypto\dllMFCryptic.h>

// Padding
static BYTE MD5_PADDING[64] = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// MD5_F, MD5_G and MD5_H are basic MD5 functions: selection, majority, parity
#define MD5_F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define MD5_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define MD5_H(x, y, z) ((x) ^ (y) ^ (z))
#define MD5_I(x, y, z) ((y) ^ ((x) | (~z)))

// MD5_FF, MD5_GG, MD5_HH, and MD5_II transformations for rounds 1, 2, 3, and 4
// Rotation is separate from addition to prevent recomputation
#define MD5_FF(A, B, C, D, x, s, ac) {(A) += MD5_F ((B), (C), (D)) + (x) + (DWORD)(ac); (A) = rotl ((A), (s)); (A) += (B); }
#define MD5_GG(A, B, C, D, x, s, ac) {(A) += MD5_G ((B), (C), (D)) + (x) + (DWORD)(ac); (A) = rotl ((A), (s)); (A) += (B); }
#define MD5_HH(A, B, C, D, x, s, ac) {(A) += MD5_H ((B), (C), (D)) + (x) + (DWORD)(ac); (A) = rotl ((A), (s)); (A) += (B); }
#define MD5_II(A, B, C, D, x, s, ac) {(A) += MD5_I ((B), (C), (D)) + (x) + (DWORD)(ac); (A) = rotl ((A), (s)); (A) += (B); }

/* Constants for transformation */
#define MD5_S11 7  // Round 1
#define MD5_S12 12
#define MD5_S13 17
#define MD5_S14 22
#define MD5_S21 5  // Round 2
#define MD5_S22 9
#define MD5_S23 14
#define MD5_S24 20
#define MD5_S31 4  // Round 3
#define MD5_S32 11
#define MD5_S33 16
#define MD5_S34 23
#define MD5_S41 6  // Round 4
#define MD5_S42 10
#define MD5_S43 15
#define MD5_S44 21

//****************************************************************
void MD5Init(MD5State* State)
{
	State->Intermediate_Hash[0] = (DWORD)0x67452301;
	State->Intermediate_Hash[1] = (DWORD)0xEFCDAB89;
	State->Intermediate_Hash[2] = (DWORD)0x98BADCFE;
	State->Intermediate_Hash[3] = (DWORD)0x10325476;

	State->Length_Low = 0;
	State->Length_High = 0;
}

//****************************************************************
// Compression function, takes in a block and updates the intermediate hash
static void MD5_Transform(DWORD *Intermediate_Hash, DWORD *M)
{
	DWORD A = Intermediate_Hash[0];
	DWORD B = Intermediate_Hash[1];
	DWORD C = Intermediate_Hash[2];
	DWORD D = Intermediate_Hash[3];

	MD5_FF ( A, B, C, D, M[ 0], MD5_S11, (DWORD) 0xD76AA478); /* 1 */
	MD5_FF ( D, A, B, C, M[ 1], MD5_S12, (DWORD) 0xE8C7B756); /* 2 */
	MD5_FF ( C, D, A, B, M[ 2], MD5_S13, (DWORD) 0x242070DB); /* 3 */
	MD5_FF ( B, C, D, A, M[ 3], MD5_S14, (DWORD) 0xC1BDCEEE); /* 4 */
	MD5_FF ( A, B, C, D, M[ 4], MD5_S11, (DWORD) 0xF57C0FAF); /* 5 */
	MD5_FF ( D, A, B, C, M[ 5], MD5_S12, (DWORD) 0x4787C62A); /* 6 */
	MD5_FF ( C, D, A, B, M[ 6], MD5_S13, (DWORD) 0xA8304613); /* 7 */
	MD5_FF ( B, C, D, A, M[ 7], MD5_S14, (DWORD) 0xFD469501); /* 8 */
	MD5_FF ( A, B, C, D, M[ 8], MD5_S11, (DWORD) 0x698098D8); /* 9 */
	MD5_FF ( D, A, B, C, M[ 9], MD5_S12, (DWORD) 0x8B44F7AF); /* 10 */
	MD5_FF ( C, D, A, B, M[10], MD5_S13, (DWORD) 0xFFFF5BB1); /* 11 */
	MD5_FF ( B, C, D, A, M[11], MD5_S14, (DWORD) 0x895CD7BE); /* 12 */
	MD5_FF ( A, B, C, D, M[12], MD5_S11, (DWORD) 0x6B901122); /* 13 */
	MD5_FF ( D, A, B, C, M[13], MD5_S12, (DWORD) 0xFD987193); /* 14 */
	MD5_FF ( C, D, A, B, M[14], MD5_S13, (DWORD) 0xA679438E); /* 15 */
	MD5_FF ( B, C, D, A, M[15], MD5_S14, (DWORD) 0x49B40821); /* 16 */

	MD5_GG ( A, B, C, D, M[ 1], MD5_S21, (DWORD) 0xF61E2562); /* 17 */
	MD5_GG ( D, A, B, C, M[ 6], MD5_S22, (DWORD) 0xC040B340); /* 18 */
	MD5_GG ( C, D, A, B, M[11], MD5_S23, (DWORD) 0x265E5A51); /* 19 */
	MD5_GG ( B, C, D, A, M[ 0], MD5_S24, (DWORD) 0xE9B6C7AA); /* 20 */
	MD5_GG ( A, B, C, D, M[ 5], MD5_S21, (DWORD) 0xD62F105D); /* 21 */
	MD5_GG ( D, A, B, C, M[10], MD5_S22, (DWORD) 0x02441453); /* 22 */
	MD5_GG ( C, D, A, B, M[15], MD5_S23, (DWORD) 0xD8A1E681); /* 23 */
	MD5_GG ( B, C, D, A, M[ 4], MD5_S24, (DWORD) 0xE7D3FBC8); /* 24 */
	MD5_GG ( A, B, C, D, M[ 9], MD5_S21, (DWORD) 0x21E1CDE6); /* 25 */
	MD5_GG ( D, A, B, C, M[14], MD5_S22, (DWORD) 0xC33707D6); /* 26 */
	MD5_GG ( C, D, A, B, M[ 3], MD5_S23, (DWORD) 0xF4D50D87); /* 27 */
	MD5_GG ( B, C, D, A, M[ 8], MD5_S24, (DWORD) 0x455A14ED); /* 28 */
	MD5_GG ( A, B, C, D, M[13], MD5_S21, (DWORD) 0xA9E3E905); /* 29 */
	MD5_GG ( D, A, B, C, M[ 2], MD5_S22, (DWORD) 0xFCEFA3F8); /* 30 */
	MD5_GG ( C, D, A, B, M[ 7], MD5_S23, (DWORD) 0x676F02D9); /* 31 */
	MD5_GG ( B, C, D, A, M[12], MD5_S24, (DWORD) 0x8D2A4C8A); /* 32 */

	MD5_HH ( A, B, C, D, M[ 5], MD5_S31, (DWORD) 0xFFFA3942); /* 33 */
	MD5_HH ( D, A, B, C, M[ 8], MD5_S32, (DWORD) 0x8771F681); /* 34 */
	MD5_HH ( C, D, A, B, M[11], MD5_S33, (DWORD) 0x6D9D6122); /* 35 */
	MD5_HH ( B, C, D, A, M[14], MD5_S34, (DWORD) 0xFDE5380C); /* 36 */
	MD5_HH ( A, B, C, D, M[ 1], MD5_S31, (DWORD) 0xA4BEEA44); /* 37 */
	MD5_HH ( D, A, B, C, M[ 4], MD5_S32, (DWORD) 0x4BDECFA9); /* 38 */
	MD5_HH ( C, D, A, B, M[ 7], MD5_S33, (DWORD) 0xF6BB4B60); /* 39 */
	MD5_HH ( B, C, D, A, M[10], MD5_S34, (DWORD) 0xBEBFBC70); /* 40 */
	MD5_HH ( A, B, C, D, M[13], MD5_S31, (DWORD) 0x289B7EC6); /* 41 */
	MD5_HH ( D, A, B, C, M[ 0], MD5_S32, (DWORD) 0xEAA127FA); /* 42 */
	MD5_HH ( C, D, A, B, M[ 3], MD5_S33, (DWORD) 0xD4EF3085); /* 43 */
	MD5_HH ( B, C, D, A, M[ 6], MD5_S34, (DWORD) 0x04881D05); /* 44 */
	MD5_HH ( A, B, C, D, M[ 9], MD5_S31, (DWORD) 0xD9D4D039); /* 45 */
	MD5_HH ( D, A, B, C, M[12], MD5_S32, (DWORD) 0xE6DB99E5); /* 46 */
	MD5_HH ( C, D, A, B, M[15], MD5_S33, (DWORD) 0x1FA27CF8); /* 47 */
	MD5_HH ( B, C, D, A, M[ 2], MD5_S34, (DWORD) 0xC4AC5665); /* 48 */

	MD5_II ( A, B, C, D, M[ 0], MD5_S41, (DWORD) 0xF4292244); /* 49 */
	MD5_II ( D, A, B, C, M[ 7], MD5_S42, (DWORD) 0x432AFF97); /* 50 */
	MD5_II ( C, D, A, B, M[14], MD5_S43, (DWORD) 0xAB9423A7); /* 51 */
	MD5_II ( B, C, D, A, M[ 5], MD5_S44, (DWORD) 0xFC93A039); /* 52 */
	MD5_II ( A, B, C, D, M[12], MD5_S41, (DWORD) 0x655B59C3); /* 53 */
	MD5_II ( D, A, B, C, M[ 3], MD5_S42, (DWORD) 0x8F0CCC92); /* 54 */
	MD5_II ( C, D, A, B, M[10], MD5_S43, (DWORD) 0xFFEFF47D); /* 55 */
	MD5_II ( B, C, D, A, M[ 1], MD5_S44, (DWORD) 0x85845DD1); /* 56 */
	MD5_II ( A, B, C, D, M[ 8], MD5_S41, (DWORD) 0x6FA87E4F); /* 57 */
	MD5_II ( D, A, B, C, M[15], MD5_S42, (DWORD) 0xFE2CE6E0); /* 58 */
	MD5_II ( C, D, A, B, M[ 6], MD5_S43, (DWORD) 0xA3014314); /* 59 */
	MD5_II ( B, C, D, A, M[13], MD5_S44, (DWORD) 0x4E0811A1); /* 60 */
	MD5_II ( A, B, C, D, M[ 4], MD5_S41, (DWORD) 0xF7537E82); /* 61 */
	MD5_II ( D, A, B, C, M[11], MD5_S42, (DWORD) 0xBD3AF235); /* 62 */
	MD5_II ( C, D, A, B, M[ 2], MD5_S43, (DWORD) 0x2AD7D2BB); /* 63 */
	MD5_II ( B, C, D, A, M[ 9], MD5_S44, (DWORD) 0xEB86D391); /* 64 */

	Intermediate_Hash[0] += A;
	Intermediate_Hash[1] += B;
	Intermediate_Hash[2] += C;
	Intermediate_Hash[3] += D;
}

//****************************************************************
void MD5Update(MD5State* State, BYTE* M, UINT nBytes)
{
	if(! nBytes)
		return;

	// Compute number of bytes mod 64
	UINT mdi = (UINT)((State->Length_Low >> 3) & 0x3F);

	if((State->Length_Low + ((DWORD)nBytes << 3)) < State->Length_Low)
		State->Length_High++;

	State->Length_Low += (nBytes << 3);
	State->Length_High += (nBytes >> 29);

	do {
		State->MsgBlock[mdi++] = *M++;

		if(mdi & 64)
		{
			DWORD M_Transform[16];
			//little-big endian swap
			for(UINT i = 0, ii = 0; i < 16; i++, ii += 4)
				M_Transform[i] = (((DWORD)State->MsgBlock[ii+3]) << 24) |
					(((DWORD)State->MsgBlock[ii+2]) << 16) |
					(((DWORD)State->MsgBlock[ii+1]) << 8) |
					((DWORD)State->MsgBlock[ii]);

			mdi = 0;
			MD5_Transform(State->Intermediate_Hash, M_Transform);
		}
	} while(nBytes--);
}

//****************************************************************
void MD5Result(MD5State* State, BYTE digest[ MD5HASHSIZE ])
{
	DWORD M_Transform[16];

	// Save number of bits
	M_Transform[14] = State->Length_Low;
	M_Transform[15] = State->Length_High;

	// Compute number of bytes mod 64
	UINT mdi = (int)((State->Length_Low >> 3) & 0x3F);

	// Pad out to 56 mod 64
	UINT padLen = (mdi < 56) ? (56 - mdi) : (120 - mdi);

	MD5Update(State, MD5_PADDING, padLen);

	// Append length in bits and transform
	for(UINT i = 0, ii = 0; i < 14; i++, ii += 4)
		M_Transform[i] = (((DWORD)State->MsgBlock[ii+3]) << 24) |
			(((DWORD)State->MsgBlock[ii+2]) << 16) |
			(((DWORD)State->MsgBlock[ii+1]) <<  8) |
			((DWORD)State->MsgBlock[ii]);

	MD5_Transform(State->Intermediate_Hash, M_Transform);

	// Store Intermediate_Hashfer in digest
	for(UINT i = 0, ii = 0; i < 4; i++, ii += 4)
	{
		digest[ii]   = (BYTE)( State->Intermediate_Hash[i]        & 0xFF);
		digest[ii+1] = (BYTE)((State->Intermediate_Hash[i] >>  8) & 0xFF);
		digest[ii+2] = (BYTE)((State->Intermediate_Hash[i] >> 16) & 0xFF);
		digest[ii+3] = (BYTE)((State->Intermediate_Hash[i] >> 24) & 0xFF);
	}
}
