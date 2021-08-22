#include <windows.h>
#include <iostream>

#include <Crypto\dllAchillea.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		printf("new process\n");
		break;
	case DLL_THREAD_ATTACH:
		printf("new thread\n");
		break;
	case DLL_THREAD_DETACH:
		printf("exit thread\n");
		break;
	case DLL_PROCESS_DETACH:
		printf("exit process\n");
		break;
	}
    return TRUE;
}

void ACHILLEA_API use()
{
	return;
}