typedef struct _Bitmap {
	BITMAPFILEHEADER    bmfh;
	BITMAPINFOHEADER    bmih;
	//RGBQUAD             aColors[];
	//BYTE*                aBitmapBits;
} Bitmap;

BOOL LoadBMP(Bitmap*, char*);