#ifndef MJCF_UXENCODE
#define MJCF_UXENCODE

#include <FilePath.h>

namespace UXencode
{
	//Careful with these two
	void EncodeGroup(BYTE* Raw, BYTE* Encoded);
	void DecodeGroup(BYTE* Encoded, BYTE* Raw);

	UINT GetEndLineSize(UINT nRawBytes);

	void GetStopLine(BYTE StopLine[72], UINT nEndLineBytes);
	UINT DecodeStopLine(BYTE* StopLine);

	void EncodeFullLine(BYTE RawData[54], BYTE EncodedData[72]);
	void DecodeFullLine(BYTE EncodedData[72], BYTE RawData[54]);

	void EncodeEndLine(BYTE* RawData, BYTE* EncodedData, UINT nRawBytes);
	void DecodeEndLine(BYTE* EncodedData, BYTE* RawData, UINT nEncodedBytes);

} //UXencode

DWORD UXEncodeFile(CFilePath filename);
DWORD UXDecodeFile(CFilePath filename);

#endif
