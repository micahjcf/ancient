#ifndef _MJCF_CFILEVIEW_
#define _MJCF_CFILEVIEW_

struct CFV_FILE
{
	DWORD dwFileAttributes;
	char FileName[50];
};

class CFileView
{
public:
	CFileView(){Files = NULL;}
	~CFileView(){delete[] Files;}

	void Setup(COORD Pos, COORD FieldSize, const char* szStartDir);
	void SetDirectory(const char* szNewDir);
	void Refresh();
	void OpenFolder();

	void DOS_GUI_ROUTINE Run();

	char* GetCurrentDirectory(){return szDir;}
	bool IsFileHighlighted(){return bItemHighlighted;}
	DWORD GetHighlightedFileAttributes(){return ((bItemHighlighted)?(Files[nHighlightedItem].dwFileAttributes):(0));}
	char* GetHighlightedFileName(){return ((bItemHighlighted)?(Files[nHighlightedItem].FileName):(""));}

private:
	bool GetFileList();
	void SortList();

	void ClearView();
	void ShowScrollPos(int ScrollIndex);
	void Raise();

	void HighlightItem(int ItemIndex);
	void ShowFileAttributes();
	void ClearHighlightedItem();

	char szDir[MAX_PATH];
	CFV_FILE* Files;
	int nFolders;
	int nFiles;

	COORD Position;
	BAR RaiseButton;
	BAR RefreshButton;
	COORD ScrollUp;
	COORD ScrollDown;
	COORD ScrollTop;
	COORD ScrollBottom;
	SHORT FieldWidth;
	SHORT FieldHeight;

	int ViewIndex;
	bool bItemHighlighted;
	int nHighlightedItem; // Indexed;
};

//**********************************************
void CFileView::Setup(COORD Pos, COORD FieldSize, const char* szStartDir)
{
	Position = Pos;

	FieldWidth = FieldSize.X;
	FieldHeight = FieldSize.Y;

	// Minimum Size
	if(FieldHeight < 11)
		FieldHeight = 11;

	if(FieldWidth < 19)
		FieldWidth = 19;

	if(FieldWidth > 50)
		FieldWidth = 50;

	RaiseButton = ReturnBar(Pos.Y, (Pos.X - 4 + (FieldWidth / 2)),
		(Pos.X - 4 + (FieldWidth / 2) + 11));

	RefreshButton = ReturnBar(Pos.Y + FieldHeight + 1, (Pos.X - 2 + (FieldWidth / 2)),
		(Pos.X - 3 + (FieldWidth / 2) + 7));

	ScrollUp = ReturnCoord(Pos.X + FieldWidth + 1, ((Pos.Y + 2 + FieldHeight)/2) + 1);
	ScrollDown = ReturnCoord(Pos.X + FieldWidth + 1, (Pos.Y + 2 + FieldHeight) / 2);
	ScrollTop = ReturnCoord(Pos.X + FieldWidth + 1, ((Pos.Y + 2 + FieldHeight)/2) - 1);
	ScrollBottom = ReturnCoord(Pos.X + FieldWidth + 1, ((Pos.Y + 2 + FieldHeight)/2) + 2);

	ViewIndex = 0;
	bItemHighlighted = false;
	nHighlightedItem = 0;

	ScrnBuffer Box;
	Box.SetSize(FieldWidth + 14, FieldHeight + 2);
	Box.FillBuffer((char)219, B_White_I | Blue);
	Box.DrawAt(Pos.X, Pos.Y);

	Draw::BorderBox(Pos.X, Pos.Y, FieldWidth + 14, FieldHeight + 2, (B_Blue | Teal_I), LinesDouble);
	Draw::BorderBox(Pos.X + FieldWidth + 1, Pos.Y, 1, FieldHeight + 2, (B_Blue | Teal_I), LinesDouble);

	Text(Pos.X + FieldWidth + 1, ScrollTop.Y, (char)24, B_Blue | Teal_I);
	Text(Pos.X + FieldWidth + 1, ScrollBottom.Y, (char)25, B_Blue | Teal_I);

	Text(Pos.X + FieldWidth + 1, ScrollDown.Y, (char)30, B_Blue | Teal_I);
	Text(Pos.X + FieldWidth + 1, ScrollUp.Y, (char)31, B_Blue | Teal_I);

	Text(RaiseButton.Left, RaiseButton.Y, "Up One Level", B_Blue | Teal_I);
	Text(RefreshButton.Left, RefreshButton.Y, "Refresh", B_Blue | Teal_I);

	Text(Pos.X + FieldWidth + 2, Pos.Y + 1, "Attributes:", B_Blue | Teal_I);
	Draw::HorizLine(Pos.Y + 2, Pos.X + FieldWidth + 2, 11, '-', B_Blue | Teal_I);
	Draw::HorizLine(Pos.Y + 9, Pos.X + FieldWidth + 2, 11, '-', B_Blue | Teal_I);

	if(FileExists(szStartDir) && IsDirectory(szStartDir))
		strcpy(szDir, szStartDir);
	else
		strcpy(szDir, "C:");

	GetFileList();
	ShowScrollPos(0);
}

//**********************************************
// Sets szDir and updates the view
void CFileView::SetDirectory(const char* szNewDir)
{
	if(FileExists(szNewDir) && IsDirectory(szNewDir))
		strcpy(szDir, szNewDir);
	else
		return;

	GetFileList();

	bItemHighlighted = false;

	ShowScrollPos(0);
}

//**********************************************
// Refreshes the current file list
void CFileView::Refresh()
{
	GetFileList();

	bool bWasHighlighted = bItemHighlighted;

	bItemHighlighted = false;

	ShowScrollPos(ViewIndex);

	if(bWasHighlighted)
		HighlightItem(nHighlightedItem);
}

//**********************************************
// Opens the highlighted item if it is a folder
void CFileView::OpenFolder()
{
	if((!Files) || (!bItemHighlighted))
		return;

	if(!(Files[nHighlightedItem].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		return;

	strcat(szDir, "\\");
	strcat(szDir, Files[nHighlightedItem].FileName);

	GetFileList();

	bItemHighlighted = false;

	ShowScrollPos(0);
}

//**********************************************
void DOS_GUI_ROUTINE CFileView::Run()
{
	if(Mouse.Clicked(RaiseButton))
		Raise();

	if(Mouse.Clicked(RefreshButton))
		Refresh();

	if(Files == NULL)
		return;

	// Only activate the scrolling buttons if you can't see all the files at once
	if(nFiles > FieldHeight)
	{
		if(Mouse.Clicked(ScrollDown))
			ShowScrollPos(ViewIndex - (FieldHeight / 2));

		if(Mouse.Clicked(ScrollUp))
			ShowScrollPos(ViewIndex + (FieldHeight / 2));

		if(Mouse.Clicked(ScrollTop))
			ShowScrollPos(0);

		if(Mouse.Clicked(ScrollBottom))
			ShowScrollPos(nFiles);
	}

	if(Mouse.Clicked(ReturnRect(Position.X + 1, Position.Y + 1, Position.X + FieldWidth, Position.Y + FieldHeight)))
	{
		ClearHighlightedItem();
		HighlightItem(Mouse.Position.Y - Position.Y + ViewIndex - 1);
	}

	if(Mouse.bDoubleClicked && Mouse.OverRectangle(ReturnRect(Position.X + 1, Position.Y + 1, Position.X + FieldWidth, Position.Y + FieldHeight)))
		OpenFolder();
}

//**********************************************
// Gets the list of files in the current directory
bool CFileView::GetFileList()
{
	if(Files)
		delete[] Files;

	nFiles = GetFileCount(szDir, 0, false);
	nFolders = GetFileCount(szDir, FILE_ATTRIBUTE_DIRECTORY, false);

	nFolders = nFiles - nFolders;

	if(nFiles == 0)
	{
		Files = NULL;
		return true;
	}

	Files = new CFV_FILE[ nFiles ];

	//could not allocate memory
	if(!Files)
		return false;

	HANDLE hFind;  // file handle
	WIN32_FIND_DATA FindFileData;

	TCHAR DirPath[MAX_PATH];
	TCHAR FileName[MAX_PATH];

	strcpy(DirPath,szDir);
	strcat(DirPath,"\\*");    // searching all files
	strcpy(FileName,szDir);
	strcat(FileName,"\\");

	hFind = FindFirstFile(DirPath,&FindFileData); // find the first file
	if(hFind == INVALID_HANDLE_VALUE) return FALSE;
	strcpy(DirPath,FileName);

	bool bSearch = true;
	int n = 0;

	while(bSearch) // until we finds an entry
	{
		if(FindNextFile(hFind,&FindFileData))
		{
			if(IsDots(FindFileData.cFileName))
				continue;

			strcat(FileName,FindFileData.cFileName);

			Files[n].dwFileAttributes = FindFileData.dwFileAttributes;
			strcpy(Files[n].FileName, FindFileData.cFileName);

			n++;

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

	SortList();

	return true;
}

//**********************************************
// Sorts the list so folders are at the beginning and files are at the end
void CFileView::SortList()
{
	CFV_FILE* Temp = new CFV_FILE[ nFiles ];

	if(!Temp)
		return;

	int i = 0;

	for(int n = 0; n < nFiles; n++)
	{
		if(Files[n].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			Temp[i++] = Files[n];
	}

	for(n = 0; n < nFiles; n++)
	{
		if(!(Files[n].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			Temp[i++] = Files[n];
	}

	for(n = 0; n < nFiles; n++)
	{
		Files[n] = Temp[n];
	}

	delete[] Temp;
}

//**********************************************
// Clears the view of files and folders
void CFileView::ClearView()
{
	ScrnBuffer Clear;
	Clear.SetSize(FieldWidth, FieldHeight);
	Clear.FillBuffer((char)219, B_White_I | Blue);
	Clear.DrawAt(Position.X + 1, Position.Y + 1);

	Text(Position.X + FieldWidth + 3, Position.Y + 3, "Hidden", B_Blue | Black);
	Text(Position.X + FieldWidth + 3, Position.Y + 4, "Encrypted", B_Blue | Black);
	Text(Position.X + FieldWidth + 3, Position.Y + 5, "Compressed", B_Blue | Black);
	Text(Position.X + FieldWidth + 3, Position.Y + 6, "Read Only", B_Blue | Black);
	Text(Position.X + FieldWidth + 3, Position.Y + 7, "Folder", B_Blue | Black);
	Text(Position.X + FieldWidth + 3, Position.Y + 8, "System", B_Blue | Black);
	Text(Position.X + FieldWidth + 2, Position.Y + 10, "Files:0    ", B_Blue | Teal_I);
	Text(Position.X + FieldWidth + 2, Position.Y + 11, "Folders:0  ", B_Blue | Teal_I);
}

//**********************************************
// Shows a certain position in the list; 0 = top
void CFileView::ShowScrollPos(int ScrollIndex)
{
	ClearView();

	if(Files == NULL)
	{
		Text(Position.X + 1, Position.Y + 1, "<Folder Empty>", B_Blue | White);
		return;
	}

	if(ScrollIndex > nFiles - FieldHeight)
		ScrollIndex = nFiles - FieldHeight;

	if(ScrollIndex < 0)
		ScrollIndex = 0;

	ViewIndex = ScrollIndex;

	// Show the number of files and folders in this directory
	Text(Position.X + FieldWidth + 8, Position.Y + 10, nFiles - nFolders, B_Blue | Teal);
	Text(Position.X + FieldWidth + 10, Position.Y + 11, nFolders, B_Blue | Teal);

	int n = 0;
	int Len;
	ULONG N;
	WORD Color;

	// Display each item name
	while(true)
	{
		Color = B_Blue | (Files[n + ScrollIndex].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY?White_I:White);

		Len = LengthOf(Files[n + ScrollIndex].FileName);

		if(Len > FieldWidth)
			Len = FieldWidth;

		WriteConsoleOutputCharacter(hOutput, Files[n + ScrollIndex].FileName, Len, ReturnCoord(Position.X + 1, Position.Y + 1 + n), &N);

		for(int i = 0; i < Len; i++)
		{
			WriteConsoleOutputAttribute(hOutput, &Color, 1, ReturnCoord(Position.X + 1 + i, Position.Y + 1 + n), &N);
		}

		if((n + ScrollIndex + 1 == nFiles) || (n == FieldHeight - 1))
			break;

		n++;
	}

	if(bItemHighlighted)
		HighlightItem(nHighlightedItem);
}

//**********************************************
// Goes up one level
void CFileView::Raise()
{
	char temp[MAX_PATH];

	strcpy(szDir, GetFilePath(szDir, temp));

	GetFileList();

	bItemHighlighted = false;

	ShowScrollPos(0);
}

//**********************************************
// Highlights a file
void CFileView::HighlightItem(int ItemIndex)
{
	if(Files == NULL)
		return;

	// If you clicked below the last file it selects the last file
	if(ItemIndex > nFiles - 1)
		ItemIndex = nFiles - 1;

	ULONG N;
	WORD Color = B_Teal | White_I;

	if(ItemIndex < ViewIndex)
		ItemIndex = ViewIndex;

	if(ItemIndex > ViewIndex + FieldHeight - 1)
		ItemIndex = ViewIndex + FieldHeight - 1;

	bItemHighlighted = true;
	nHighlightedItem = ItemIndex;

	int NameLength = LengthOf(Files[nHighlightedItem].FileName);

	if(NameLength > FieldWidth)
		NameLength = FieldWidth;

	for(int n = 0; n < NameLength; n++)
	{
		WriteConsoleOutputAttribute(hOutput, &Color, 1, ReturnCoord(Position.X + 1 + n, Position.Y + ItemIndex - ViewIndex + 1), &N);
	}

	ShowFileAttributes();
}

//**********************************************
// Shows the attributes of the highlighted file
void CFileView::ShowFileAttributes()
{
	if(Files == NULL)
		return;

	DWORD dwCurAttrib = Files[nHighlightedItem].dwFileAttributes;

	if(dwCurAttrib & FILE_ATTRIBUTE_HIDDEN)
		Text(Position.X + FieldWidth + 3, Position.Y + 3, "Hidden", B_Blue | Teal_I);
	else
		Text(Position.X + FieldWidth + 3, Position.Y + 3, "Hidden", B_Blue | Black);

	if(dwCurAttrib & FILE_ATTRIBUTE_ENCRYPTED)
		Text(Position.X + FieldWidth + 3, Position.Y + 4, "Encrypted", B_Blue | Red_I);
	else
		Text(Position.X + FieldWidth + 3, Position.Y + 4, "Encrypted", B_Blue | Black);

	if(dwCurAttrib & FILE_ATTRIBUTE_COMPRESSED)
		Text(Position.X + FieldWidth + 3, Position.Y + 5, "Compressed", B_Blue | Green_I);
	else
		Text(Position.X + FieldWidth + 3, Position.Y + 5, "Compressed", B_Blue | Black);

	if(dwCurAttrib & FILE_ATTRIBUTE_READONLY)
		Text(Position.X + FieldWidth + 3, Position.Y + 6, "Read Only", B_Blue | White_I);
	else
		Text(Position.X + FieldWidth + 3, Position.Y + 6, "Read Only", B_Blue | Black);

	if(dwCurAttrib & FILE_ATTRIBUTE_DIRECTORY)
		Text(Position.X + FieldWidth + 3, Position.Y + 7, "Folder", B_Blue | Yellow_I);
	else
		Text(Position.X + FieldWidth + 3, Position.Y + 7, "Folder", B_Blue | Black);

	if(dwCurAttrib & FILE_ATTRIBUTE_SYSTEM)
		Text(Position.X + FieldWidth + 3, Position.Y + 8, "System", B_Blue | Purple_I);
	else
		Text(Position.X + FieldWidth + 3, Position.Y + 8, "System", B_Blue | Black);
}

//**********************************************
// Clears the highlighted item
void CFileView::ClearHighlightedItem()
{
	if(!bItemHighlighted)
		return;

	if(Files == NULL)
		return;

	bItemHighlighted = false;

	ULONG N;
	WORD Color = B_Blue | (Files[nHighlightedItem].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY?White_I:White);

	int NameLength = LengthOf(Files[nHighlightedItem].FileName);

	if(NameLength > FieldWidth)
		NameLength = FieldWidth;

	for(int n = 0; n < NameLength; n++)
	{
		WriteConsoleOutputAttribute(hOutput, &Color, 1, ReturnCoord(Position.X + 1 + n, Position.Y + nHighlightedItem - ViewIndex + 1), &N);
	}
}

class CFileViewControlPanel
{
public:
	CFileViewControlPanel(){MyCFileView = NULL;}
	~CFileViewControlPanel(){}

	void Setup(COORD Pos, CFileView* pCFileView);

	void Run();

private:
	CFileView* MyCFileView;
	COORD Position;
};

void CFileViewControlPanel::Setup(COORD Pos, CFileView* pCFileView)
{
	Position = Pos;

	MyCFileView = pCFileView;

	ScrnBuffer Box;
	Box.SetSize(14, 12);
	Box.FillBuffer((char)219, B_White_I | Blue);
	Box.DrawAt(Pos.X, Pos.Y);

	Draw::BorderBox(Pos.X, Pos.Y, 14, 12, (B_Blue | Teal_I), LinesDouble);

}

void CFileViewControlPanel::Run()
{
	/*if(Mouse.bClicked)
	{
		if(MyCFileView->IsFileHighlighted())
		{
			DWORD Size;
			_GetFileSize(MyCFileView->GetHighlightedFileName(), &Size);
			Text(Position.X + 1, Position.Y + 1, BtoKB(Size), B_Blue | Teal_I);
		}
	}*/
}

#endif