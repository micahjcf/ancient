template <typename Type>
Type ArrayMax(Type* pData, WORD DataSize)
{
	Type CurMax = pData[0];

	for(int n = 1; n < DataSize; n++)
		if(CurMax < pData[n])
			CurMax = pData[n];

	return CurMax;
}

//Returns the Hamming distance of two arrays
//nElements should be set to the number of elements in the arrays
//the size of the arrays must be equal
template <typename Type>
unsigned int Hamming(Type* b1, Type* b2, UINT nElements)
{
	UINT diff = 0;

	for(UINT n = 0; n < nElements; n++)
		diff += bitdif(b1[n], b2[n]);

	return diff;
}