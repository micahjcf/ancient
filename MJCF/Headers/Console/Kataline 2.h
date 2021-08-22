#include <type.h>

/************************************************************
*                                                           *
*  .=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.       *
*   |                     ______                     |      *
*   |                  .-"      "-.                  |      *
*   |                 /            \                 |      *
*   |     _          |              |          _     |      *
*   |    ( \         |,  .-.  .-.  ,|         / )    |      *
*   |     > "=._     | )(__/  \__)( |     _.=" <     |      *
*   |    (_/"=._"=._ |/     /\     \| _.="_.="\_)    |      *
*   |           "=._"(_     ^^     _)"_.="           |      *
*   |               "=\__|IIIIII|__/="               |      *
*   |              _.="| \IIIIII/ |"=._              |      *
*   |    _     _.="_.="\          /"=._"=._     _    |      *
*   |   ( \_.="_.="     `--------`     "=._"=._/ )   |      *
*   |    > _.="                            "=._ <    |      *
*   |   (_/                                    \_)   |      *
*   |                                                |      *
*   '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-='      *
*                                                           *
*      LASCIATE OGNI SPERANZA, VOI CH'ENTRATE               *
*************************************************************/

#include <Console\stdcon.h>
#include <Console\graphics.h>
#include <Console\keyboard.h>
#include <Console\basic_mouse.h>
#include <Console\input.h>

BOOL SetConsoleWindowAlwaysOnTop(BOOL);

#ifdef USE_CUSTOM_CTRL_HANDLER
BOOL CtrlHandler( DWORD CtrlType );
#endif

extern SMALL_RECT gWindowRect;

void SetupKatalineConsole(char* title, COORD size);
inline COORD GetConsoleSize() {return coord(gWindowRect.Right, gWindowRect.Bottom);}

const char* GetLastErrorMsg();
void SetLastErrorMsg(std::string);
void ClearLastErrorMsg();