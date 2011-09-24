#ifndef _PUSHKEY_H
#define _PUSHKEY_H

#include "Const.h"
#include "MainDependency.h"

#define PUSHKEY_IDMAX	8
#define PUSHKEY_KEYCHECKMAX	4

#define PUSHKEY_ID_SELUSE_0	0
#define PUSHKEY_ID_SELUSE_1	1
#define PUSHKEY_ID_SELUSE_2	2
#define PUSHKEY_ID_SELUSE_3	3
#define PUSHKEY_ID_UIUSE_0	4
#define PUSHKEY_ID_UIUSE_1	5
#define PUSHKEY_ID_GAMEUSE_0	6
#define PUSHKEY_ID_GAMEUSE_1	7

#define PUSHKEY_KEYNULL	-1

struct pushkeyEvent
{
	int timer;
	int pushkey[PUSHKEY_KEYCHECKMAX];
	int pushfirst;
	int pushrollto;
	BYTE playerindex;
};

class PushKey
{
public:
	static bool SetPushEvent(BYTE ID, BYTE playerindex, int pushkey_1=PUSHKEY_KEYNULL, int pushkey_2=PUSHKEY_KEYNULL, int pushkey_3=PUSHKEY_KEYNULL, int pushkey_4=PUSHKEY_KEYNULL, int pushfirst=M_PUSH_FIRST, int pushrollto=M_PUSH_ROLLTO);
	static bool UpdatePushEvent(BYTE ID, BYTE playerindex=0xff);
public:
	static pushkeyEvent pushkeyevent[PUSHKEY_IDMAX];
};

#endif