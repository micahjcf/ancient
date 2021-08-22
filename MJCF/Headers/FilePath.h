#ifndef MJCF_FILEROUTINES
#define MJCF_FILEROUTINES

class CFilePath
{
public:
	CFilePath();
	CFilePath(char*);

	void ChangeExtension(char* ext);

	BOOL ThisFileExists();

	const char* GetPath();
	const char* GetFileName();
	const char* GetExtension();

	char* operator=(char* operand);
	operator char*();

private:
	char path[ MAX_PATH ];
};

BOOL FileExists(const char* filename);
//void ChangeFileExtension(char* filename, char* ext);
//char* GetFileExt(char* filename);

#endif