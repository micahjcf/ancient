void RemoveExtension(const char* szFilePath, char* szTarget)
{
	int LastDot = 0;
	int n;

	//###################################
	//strrchr <--- use this!!!!
	//####################################

	//Buffer overflow prevention.  szTarget must be MAX_PATH chars long!
	strncpy(szTarget, szFilePath, MAX_PATH);

	for(n = 0; n < LengthOf(szFilePath); n++)
		if(szFilePath[n] == '.')
			LastDot = n;

	if(LastDot != 0)
		szTarget[LastDot] = '\0';
}

char* GetFilePath(const char* szFullPath, char* szPath)
{
	int LastSlash = 0;
	int n;

	strcpy(szPath, szFullPath);

	for(n = 0; n < LengthOf(szPath); n++)
	{
		if(szFullPath[n] == '\\')
			LastSlash = n;
	}

	if(LastSlash == 0)
		return szPath;

	szPath[LastSlash] = '\0';

	return szPath;
}

char* GetFileName(const char* szPath, char* szFileName)
{
	char FileName[255];
	int LastSlash = -1;
	int n;

	for(n = 0; n < LengthOf(szPath); n++)
	{
		if(szPath[n] == '\\')
			LastSlash = n;
	}

	for(n = 0; n < 255; n++)
	{
		FileName[n] = szPath[n+LastSlash+1];
	}
	FileName[n] = '\0';

	strcpy(szFileName, FileName);

	return szFileName;
}

char* GetFileExtension(const char* szFile, char* szExtension)
{
	strcpy(szExtension, "\0");

	int LastDot = 0;

	for(int n = 0; n < LengthOf(szFile); n++)
	{
		if(szFile[n] == '.')
			LastDot = n;
	}

	if(LastDot == 0)
		return "\0";

	int i = 0;
	for(n = LastDot + 1; n < LengthOf(szFile); n++)
	{
		szExtension[i++] = szFile[n];
	}

	szExtension[i] = '\0';

	return szExtension;
}

char* GetPureFileName(const char* szPath, char* szFileName)
{
	char FileName[255];
	int LastSlash = 0;
	int n;

	for(n = 0; n < LengthOf(szPath); n++)
		if(szPath[n] == '\\')
			LastSlash = n;

	for(n = 0; n < 255; n++)
		FileName[n] = szPath[n+LastSlash+1];

	FileName[n] = '\0';

	RemoveExtension(FileName, szFileName);

	return szFileName;
}

bool inline IsDirectory(const char* szFilePath)
{
	if(GetFileAttributes(szFilePath) & FILE_ATTRIBUTE_DIRECTORY)
		return true;
	else
		return false;
}

bool FileExists(const char* szFilePath)
{
	SetLastError(0);

	HANDLE hFile = CreateFile(szFilePath, NULL, NULL, NULL, OPEN_EXISTING, NULL, NULL);

	bool bExists = (GetLastError() == 0);

	CloseHandle(hFile);

	return bExists;
}

//DEPRECATED!
DWORD _GetFileSize(const char* szFilePath, DWORD* dwFileSize)
{
	*dwFileSize = 0;

	SetLastError(0);

	HANDLE hFile = CreateFile(szFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);

	if(GetLastError() != ERROR_SUCCESS)
		return GetLastError();

	DWORD dwSize = GetFileSize(hFile, NULL);

	if(dwSize == INVALID_FILE_SIZE)
	{
		CloseHandle(hFile);
		return GetLastError();
	}

	*dwFileSize = dwSize;
	CloseHandle(hFile);

	return ERROR_SUCCESS;
}

//Source code from: http://www.codeproject.com/useritems/deletedir.asp
BOOL inline IsDots(const TCHAR* str)
{
	if(strcmp(str,".") && strcmp(str,"..")) return FALSE;
    return TRUE;
}

// Returns the number of files and/or folders in a given directory
unsigned long GetFileCount(const TCHAR* sPath, DWORD dwAttribIgnore, bool bSearchSubFolders)
{
	HANDLE hFind;  // file handle
	WIN32_FIND_DATA FindFileData;

	TCHAR DirPath[MAX_PATH];
	TCHAR FileName[MAX_PATH];

	unsigned long nFiles = 0;

	strcpy(DirPath,sPath);
	strcat(DirPath,"\\*");    // searching all files
	strcpy(FileName,sPath);
	strcat(FileName,"\\");

	hFind = FindFirstFile(DirPath,&FindFileData); // find the first file
	if(hFind == INVALID_HANDLE_VALUE) return FALSE;
	strcpy(DirPath,FileName);

	bool bSearch = true;
	while(bSearch) // until we finds an entry
	{
		if(FindNextFile(hFind,&FindFileData))
		{
			if(IsDots(FindFileData.cFileName))
				continue;

			strcat(FileName,FindFileData.cFileName);

			// we have found a directory, so recurse
			if(bSearchSubFolders && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				nFiles += GetFileCount(FileName, dwAttribIgnore, true);

			if(!(FindFileData.dwFileAttributes & dwAttribIgnore))
				nFiles++;

			strcpy(FileName,DirPath);
        }
        else
		{
            if(GetLastError() == ERROR_NO_MORE_FILES) // no more files there
				bSearch = false;
            else
			{
                // some error occured, close the handle and return FALSE
                FindClose(hFind);
                return 0;
            }
        }
    }

    FindClose(hFind);  // closing file handle
    return nFiles;
}

//Source code from: http://www.codeproject.com/useritems/deletedir.asp
BOOL DeleteDirectory(const TCHAR* sPath)
{
    HANDLE hFind;  // file handle
    WIN32_FIND_DATA FindFileData;

    TCHAR DirPath[MAX_PATH];
    TCHAR FileName[MAX_PATH];

	strcpy(DirPath,sPath);
    strcat(DirPath,"\\*");    // searching all files
    strcpy(FileName,sPath);
    strcat(FileName,"\\");

    hFind = FindFirstFile(DirPath,&FindFileData); // find the first file
    if(hFind == INVALID_HANDLE_VALUE) return FALSE;
    strcpy(DirPath,FileName);

    bool bSearch = true;
    while(bSearch) { // until we finds an entry
        if(FindNextFile(hFind,&FindFileData)) {
            if(IsDots(FindFileData.cFileName)) continue;
            strcat(FileName,FindFileData.cFileName);
            if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

                // we have found a directory, recurse
                if(!DeleteDirectory(FileName)) {
                    FindClose(hFind);
                    return FALSE; // directory couldn't be deleted
                }
                RemoveDirectory(FileName); // remove the empty directory
                strcpy(FileName,DirPath);
            }
            else {
                //if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
                    //_chmod(FileName, _S_IWRITE); // change read-only file mode
                if(!DeleteFile(FileName)) {  // delete the file
                    FindClose(hFind);
                    return FALSE; 
                }
                strcpy(FileName,DirPath);
            }
        }
        else {
            if(GetLastError() == ERROR_NO_MORE_FILES) // no more files there
            bSearch = false;
            else {
                // some error occured, close the handle and return FALSE
                FindClose(hFind);
                return FALSE;
            }
        }
    }
    FindClose(hFind);  // closing file handle

    return RemoveDirectory(sPath); // remove the empty directory
}
