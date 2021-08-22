typedef unsigned int	UINT;
typedef unsigned long	DWORD;
typedef unsigned char	BYTE;

#define bitsize(x) (sizeof(x) << 3)
#define rotl(x, n) (((x) << (n)) | ((x) >> (bitsize(x) - (n))))

#include <Crypto/MD4.h>

static void MD4Transform (DWORD state[4], BYTE block[64]);
static void Encode (BYTE *output, DWORD *input, DWORD len);
static void Decode (DWORD *output, BYTE *input, DWORD len);
static void MD4_memcpy (BYTE* output, BYTE* input, DWORD len);
static void MD4_memset (BYTE* output, DWORD value, DWORD len);

/* Constants for MD4Transform routine.
*/
#define S11 3
#define S12 7
#define S13 11
#define S14 19
#define S21 3
#define S22 5
#define S23 9
#define S24 13
#define S31 3
#define S32 9
#define S33 11
#define S34 15

static BYTE PADDING[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// basic MD4 functions.
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))

// transformations for rounds 1, 2 and 3
// Rotation is separate from addition to prevent recomputation
#define FF(a, b, c, d, x, s) { \
	(a) += F ((b), (c), (d)) + (x); \
	(a) = rotl ((a), (s)); \
	}
#define GG(a, b, c, d, x, s) { \
	(a) += G ((b), (c), (d)) + (x) + (DWORD)0x5a827999; \
	(a) = rotl ((a), (s)); \
	}
#define HH(a, b, c, d, x, s) { \
	(a) += H ((b), (c), (d)) + (x) + (DWORD)0x6ed9eba1; \
	(a) = rotl ((a), (s)); \
	}

void MD4Init(MD4State* State)
{
	State->Length[0] = State->Length[1] = 0;

	State->Intermediate_Hash[0] = 0x67452301;
	State->Intermediate_Hash[1] = 0xefcdab89;
	State->Intermediate_Hash[2] = 0x98badcfe;
	State->Intermediate_Hash[3] = 0x10325476;
}

void MD4Update(MD4State* State, BYTE *M, UINT nLen)
{
	DWORD i, index, partLen;

	/* Compute number of bytes mod 64 */
	index = (DWORD)((State->Length[0] >> 3) & 0x3F);
	/* Update number of bits */
	if ((State->Length[0] += (nLen << 3))
		< (nLen << 3))
		State->Length[1]++;
	State->Length[1] += (nLen >> 29);

	partLen = 64 - index;

	/* Transform as many times as possible.
	*/
	if (nLen >= partLen) {
		MD4_memcpy
			(&State->MsgBlock[index], M, partLen);
		MD4Transform (State->Intermediate_Hash, State->MsgBlock);

		for (i = partLen; i + 63 < nLen; i += 64)
			MD4Transform (State->Intermediate_Hash, &M[i]);

		index = 0;
	}
	else
		i = 0;

	/* Buffer remaining input */
	MD4_memcpy(&State->MsgBlock[index], &M[i], nLen-i);
}

/* MD4 finalization. Ends an MD4 message-digest operation, writing the
the message digest and zeroizing the State.
*/
void MD4Result(MD4State* State, BYTE digest[ MD4HashSize ])
{
	BYTE bits[8];
	DWORD index, padLen;

	/* Save number of bits */
	Encode (bits, State->Length, 8);

	/* Pad out to 56 mod 64.
	*/
	index = (DWORD)((State->Length[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD4Update (State, PADDING, padLen);

	/* Append length (before padding) */
	MD4Update (State, bits, 8);
	/* Store state in digest */
	Encode (digest, State->Intermediate_Hash, 16);

	/* Zeroize sensitive information.
	*/
	MD4_memset ((BYTE*)State, 0, sizeof (*State));

}

/* MD4 basic transformation. Transforms state based on block.
*/
static void MD4Transform (DWORD state[4], BYTE block[64])
{
	DWORD a = state[0], b = state[1], c = state[2], d = state[3], x[16];

	Decode (x, block, 64);

	/* Round 1 */
	FF (a, b, c, d, x[ 0], S11); /* 1 */
	FF (d, a, b, c, x[ 1], S12); /* 2 */
	FF (c, d, a, b, x[ 2], S13); /* 3 */
	FF (b, c, d, a, x[ 3], S14); /* 4 */
	FF (a, b, c, d, x[ 4], S11); /* 5 */
	FF (d, a, b, c, x[ 5], S12); /* 6 */
	FF (c, d, a, b, x[ 6], S13); /* 7 */
	FF (b, c, d, a, x[ 7], S14); /* 8 */
	FF (a, b, c, d, x[ 8], S11); /* 9 */
	FF (d, a, b, c, x[ 9], S12); /* 10 */
	FF (c, d, a, b, x[10], S13); /* 11 */
	FF (b, c, d, a, x[11], S14); /* 12 */
	FF (a, b, c, d, x[12], S11); /* 13 */
	FF (d, a, b, c, x[13], S12); /* 14 */
	FF (c, d, a, b, x[14], S13); /* 15 */
	FF (b, c, d, a, x[15], S14); /* 16 */

	/* Round 2 */
	GG (a, b, c, d, x[ 0], S21); /* 17 */
	GG (d, a, b, c, x[ 4], S22); /* 18 */
	GG (c, d, a, b, x[ 8], S23); /* 19 */
	GG (b, c, d, a, x[12], S24); /* 20 */
	GG (a, b, c, d, x[ 1], S21); /* 21 */
	GG (d, a, b, c, x[ 5], S22); /* 22 */
	GG (c, d, a, b, x[ 9], S23); /* 23 */
	GG (b, c, d, a, x[13], S24); /* 24 */
	GG (a, b, c, d, x[ 2], S21); /* 25 */
	GG (d, a, b, c, x[ 6], S22); /* 26 */
	GG (c, d, a, b, x[10], S23); /* 27 */
	GG (b, c, d, a, x[14], S24); /* 28 */
	GG (a, b, c, d, x[ 3], S21); /* 29 */
	GG (d, a, b, c, x[ 7], S22); /* 30 */
	GG (c, d, a, b, x[11], S23); /* 31 */
	GG (b, c, d, a, x[15], S24); /* 32 */

	/* Round 3 */
	HH (a, b, c, d, x[ 0], S31); /* 33 */
	HH (d, a, b, c, x[ 8], S32); /* 34 */
	HH (c, d, a, b, x[ 4], S33); /* 35 */
	HH (b, c, d, a, x[12], S34); /* 36 */
	HH (a, b, c, d, x[ 2], S31); /* 37 */
	HH (d, a, b, c, x[10], S32); /* 38 */
	HH (c, d, a, b, x[ 6], S33); /* 39 */
	HH (b, c, d, a, x[14], S34); /* 40 */
	HH (a, b, c, d, x[ 1], S31); /* 41 */
	HH (d, a, b, c, x[ 9], S32); /* 42 */
	HH (c, d, a, b, x[ 5], S33); /* 43 */
	HH (b, c, d, a, x[13], S34); /* 44 */
	HH (a, b, c, d, x[ 3], S31); /* 45 */
	HH (d, a, b, c, x[11], S32); /* 46 */
	HH (c, d, a, b, x[ 7], S33); /* 47 */
	HH (b, c, d, a, x[15], S34); /* 48 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	/* Zeroize sensitive information.
	*/
	MD4_memset ((BYTE*)x, 0, sizeof (x));
}

/* Encodes input (DWORD) DWORDo output (BYTE). Assumes len is
a multiple of 4.
*/
static void Encode (BYTE *output, DWORD *input, DWORD len)
{
	DWORD i, j;

	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = (BYTE)(input[i] & 0xff);
		output[j+1] = (BYTE)((input[i] >> 8) & 0xff);
		output[j+2] = (BYTE)((input[i] >> 16) & 0xff);
		output[j+3] = (BYTE)((input[i] >> 24) & 0xff);
	}
}

/* Decodes input (BYTE) DWORDo output (DWORD). Assumes len is
a multiple of 4.

*/
static void Decode (DWORD *output, BYTE *input, DWORD len)
{
	DWORD i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((DWORD)input[j]) | (((DWORD)input[j+1]) << 8) |
		(((DWORD)input[j+2]) << 16) | (((DWORD)input[j+3]) << 24);
}

/* Note: Replace "for loop" with standard memcpy if possible.
*/
static void MD4_memcpy (BYTE* output, BYTE* input, DWORD len)
{
	DWORD i;

	for (i = 0; i < len; i++)
		output[i] = input[i];
}

/* Note: Replace "for loop" with standard memset if possible.
*/
static void MD4_memset (BYTE* output, DWORD value, DWORD len)
{
	DWORD i;

	for (i = 0; i < len; i++)
		((BYTE *)output)[i] = (BYTE)value;
}