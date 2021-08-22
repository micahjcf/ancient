#ifndef _MJCF_HASHING_
#define _MJCF_HASHING_

#ifndef _INC_MATH
#error math.h needed
#endif

#define HASH_SIZE		24
#define HASH_BIT_SIZE	192

void CalcHash(BYTE* pData, int nDataSize, BYTE pHashValue[])
{
	int i;

	for(int n = 0; n < nDataSize; n++)
	{
		//i = (n - (HASH_SIZE * (floor(n/HASH_SIZE))));	// Loops i forewards
		i = (HASH_SIZE - (n - (HASH_SIZE * (floor(n/HASH_SIZE)))) - 1);	// Loops i backwards

		pHashValue[i] ^= pData[n];
		pHashValue[i] ^= (((~pData[n])>>4) ^ (pHashValue[i]<<4));
		pHashValue[i] ^= (pData[n]<<4) & (pHashValue[i]>>1);
		pHashValue[i] ^= ((pData[n]<<(pHashValue[i]%4) & (~pData[n])) & (pHashValue[i] % 128));

		for(int u = 0; u < HASH_SIZE; u++)
			pHashValue[i] ^= (((~pHashValue[u]<<4) | (pHashValue[i]>>4)) ^ (~pData[i]));
	}
}

bool CompHash(BYTE* pHash1, BYTE* pHash2)
{
	for(int n = 0; n < HASH_SIZE; n++)
		if(pHash1[n] != pHash2[n])
			return false;

	return true;
}

bool GetFileHashValue(const char* szFilePath, BYTE pHash[])
{
	memset(pHash, 0, HASH_SIZE);

	if(IsDirectory(szFilePath))
		return false;

	HANDLE hFile = CreateFile(szFilePath, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL)
		return false;

	DWORD nReadBytes;
	BYTE Buffer[1024];

	while(true)
	{
		ReadFile(hFile, Buffer, 1024, &nReadBytes, NULL);

		CalcHash(Buffer, nReadBytes, pHash);

		if(nReadBytes < 1024)
			break;
	}

	CloseHandle(hFile);

	return true;
}

#endif