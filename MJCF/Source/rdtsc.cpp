/*
	Micah JC Fullerton
	
	(~) Part of the C++ Kataline Project
	
	Abstract:
		Enables use of the x86 instruction rdtsc
*/

typedef unsigned long		DWORD;

//Nullable parameters
__declspec(naked) void rdtsc(DWORD* hi, DWORD* lo)
{
	__asm
	{
		push ebp
		mov ebp, esp
		sub esp, __LOCAL_SIZE
		push ebx
		push ecx
		push edx
		push eax

		rdtsc	//value returned in edx:eax
		mov ebx, hi
		mov ecx, lo

		cmp ebx, 0 //hi is null
		je hinull
		mov [ebx], edx

hinull:	cmp ecx, 0 //lo is null
		je lonull
		mov [ecx], eax

lonull:	pop eax
		pop edx
		pop ecx
		pop ebx
		mov esp, ebp
		pop ebp

		ret
	}
}