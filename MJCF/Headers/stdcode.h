#ifndef MJCF_BASIC
#define MJCF_BASIC

#include <type.h>
#include <string>

using std::string;

#define bitsize(x) (sizeof(x) << 3)

#define MALLOC(type, n)  ((type*) malloc((n) * sizeof(type)))

//Use this when you know that n will be less than the bitsize of x
#define rotl_fast(x, n) (((x) << (n)) | ((x) >> (bitsize(x) - (n))))
#define rotr_fast(x, n) (((x) >> (n)) | ((x) << (bitsize(x) - (n))))

//Safe cyclic rotations
#define rotl_safe(x, n) (((x) << (n & (bitsize(x) - 1))) | ((x) >> (bitsize(x) - (n & (bitsize(x) - 1)))))
#define rotr_safe(x, n) (((x) >> (n & (bitsize(x) - 1))) | ((x) << (bitsize(x) - (n & (bitsize(x) - 1)))))

#define rotl rotl_safe
#define rotr rotr_safe

#define isEven(x) (!((x) & 1))
#define isOdd(x) ((x) & 1)

#ifndef NOMINMAX
	#ifndef max
	#define max(a,b)	(((a) > (b)) ? (a) : (b))
	#endif
	#ifndef min
	#define min(a,b)	(((a) < (b)) ? (a) : (b))
	#endif
#endif

//Rounds integer n up to a power of 2 (x)
#define RoundUpToPwrOf2(n, x)	((n + x - 1) & (~(x - 1)))

//returns 1 if n is a multiple of x; 0 otherwise
//NOTE: x MUST be a power of 2
#define isMultOf(n, x)		( ((n) > 0) ? ( ((x)-1 & (n)) ? 0 : 1 ) : 0 )

//n is rounded up to next multiple of x
//if n is a multiple of x then n is returned
//NOTE: x MUST be a power of 2
#define roundUpToMult(n, x)		( (isMultOf(n, x)) ? (n) : ( (n) < (x) ? (x) : ((n) & ~((x)-1)) + (x)) )

//Returns the number of set bits
inline UINT weight(DWORD n) {
	UINT res = 0;

	if(n) do res++; while(n &= (n-1));

	return res;
}

// returns the number of different bits of its arguments
unsigned int inline bitdif(int a, int b) {
	return weight(a ^ b);
}

template <typename Type>
Type mirror(Type Data)
{
	Type res = 0;
	for(int n = 0; n < bitsize(Type); n++)
		if(Data & (1 << ((bitsize(Type) - 1) - n)))
			res |= (1 << n);
	return res;
}

template <typename Type>
std::string ntoh(Type Number)
{
	std::string res = "";
	static char hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	BYTE c;

	for(int n = 0; n < sizeof(Number); n++)
	{
		c = (BYTE)(Number >> ((sizeof(Number)-n-1)*8));

		res += hex[ (c & 240) >> 4 ];
		res += hex[ c & 15 ];
	}

	return res;
}

template <> __forceinline std::string ntoh<double>(double d)
{
	return ntoh( *(unsigned __int64*)&d );
}

template <> __forceinline std::string ntoh<float>(float f)
{
	return ntoh( *(unsigned __int32*)&f );
}

//Now works will all known types except pointers
template <typename Type>
std::string ntob(Type a)
{
	std::string res = "";

	for(UINT n = bitsize(Type); n; n--)
		if(((Type)1 << (n - 1)) & a)
			res += '1';
		else
			res += '0';
	return res;
	/*
	std::string res = "";

	for(UINT n = 0; n < bitsize(Type); n++)
		if(((Type)1 << ((bitsize(Type) - 1) - n)) & a)
			res += '1';
		else
			res += '0';
	return res;
	*/
}

template <> __forceinline std::string ntob<double>(double d)
{
	return ntob( *(unsigned __int64*)&d );
}

template <> __forceinline std::string ntob<float>(float f)
{
	return ntob( *(unsigned __int32*)&f );
}

#endif //_MJCF_BASIC_
