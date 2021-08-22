#ifndef MJCF_CRC32
#define MJCF_CRC32

extern DWORD CRC32Table[256];

//"offline" CRC-ing
inline void CRC32Init(DWORD* dwCrc32) {
	*dwCrc32 = 0xFFFFFFFF;
}

void CRC32Update(void* pInput, UINT nBytes, DWORD *dwCrc32);

inline void CRC32Result(DWORD *dwCrc32) {
	*dwCrc32 = ~*dwCrc32;
}

//All in one CRC-ing
void GenerateStringCRC32(char* szString, DWORD &dwCrc32);
void GenerateMemBlockCRC32(void* pBlock, UINT nBytes, DWORD &dwCrc32);
DWORD GenerateFileCRC32(char* szFilename, DWORD &dwCrc32);

#endif
