/*
	From: Basic.cpp
  */

template <typename Type>
Type mirror(Type Data)
{
	Type temp = 0;
	for(int n = 0; n < (sizeof(Type) * 8); n++)
		if(Data & (Type)(pow(2, -((unsigned)(n-((sizeof(Type) * 8) - 1))))))
			temp |= (Type)pow(2, n);
	return temp;
}

template <typename Type>
string ntob(Type Number)
{
	string res = "";

	Type tb; //test bit

	for(int n = 0; (n < sizeof(Number) * 8); n++)
	{
		tb = (Type)(pow(2, -((unsigned)(n-((sizeof(Type) * 8) - 1)))));

		if(has(Number, tb))
			res += '1';
		else
			res += '0';
	}

	return res;
}

int LengthOf(const char* Array)
{
	bool flag = false;
	int Length = 0;

	for(int n = 0; flag == false; n++)
	{
		if(Array[n] == '\0')
			flag = true;
		else
			Length++;
	}

	return Length;
}

template <typename Type>
unsigned int weight(Type a)
{
	UINT diff = 0;
	Type mask = 1;

	for(int n = 1; n < bitsize(Type) + 1; n++, mask <<= 1)
		if((mask & a))
			diff++;

	return diff;
}

template <typename Type>
unsigned int bitdif(Type a, Type b)
{
	UINT diff = 0;
	Type mask = 1;

	for(int n = 1; n < bitsize(Type) + 1; n++, mask <<= 1)
		if((mask & a) ^ (mask & b))
			diff++;

	return diff;
}

char btoh(BYTE Char, int nibble)
{
	static char hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

	if(nibble == 1)
		Char = (Char & 240) >> 4;
	else
		Char &= 15;

	return hex[Char];
}

template <typename Type>
string ntoh(Type Number)
{
	string res = "";

	for(int n = 0; n < sizeof(Number); n++)
	{
		res += btoh((BYTE)(Number >> ((sizeof(Number)-n-1)*8)), 1);
		res += btoh((BYTE)(Number >> ((sizeof(Number)-n-1)*8)), 2);
	}

	return res;
}