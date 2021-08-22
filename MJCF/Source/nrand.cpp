#include <type.h>

#include <CRC32.h>
#include <rdtsc.h>

DWORD nstate = 0;

DWORD getstate(){return nstate;}

//Keep this function out of tight loops
void seednrand(QWORD seed, BOOL ChaosMode)
{
	GenerateMemBlockCRC32((void*) &seed, sizeof( seed ), nstate);

	if(ChaosMode)
	{
		DWORD TimeStampLo;

		rdtsc(NULL, &TimeStampLo);

		nstate ^= TimeStampLo;
	}
}

//This is tight loop safe
DWORD nrand()
{
	DWORD res;

	GenerateMemBlockCRC32((void*) &nstate, sizeof( nstate ), res);

	//Swap the high and low 16 bits after incrementing the low 16 bits
	DWORD t = (nstate + 1) << 16;
	nstate = t | (nstate >> 16);

	return res;
}

double nrand_double()
{
	return (double)(nrand()) / DWORD_MAX;
}

DWORD nrand(DWORD min, DWORD max)
{
	return min + (nrand() % (max - min + 1));
}