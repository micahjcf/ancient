#ifndef MJCF_CMDARGS
#define MJCF_CMDARGS

BOOL cmdarg_FindString(char* ValName, string* str);
BOOL cmdarg_FindValue(char* ValName, int* pVal);
BOOL cmdarg_FindSwitch(char* SwitchString);

#endif