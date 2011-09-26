#ifndef _GAMEINPUT_H
#define _GAMEINPUT_H

#include "MainDependency.h"

#define GAMEINPUTKEYMAX	13
#define GAMEINPUTJOYMAX	5
#define GAMEACTIVEINPUTMAX	8

#define KSI_UP		0
#define KSI_DOWN	1
#define KSI_LEFT	2
#define KSI_RIGHT	3
#define KSI_FIRE	4
#define KSI_QUICK	5
#define KSI_SLOW	6
#define KSI_DRAIN	7
#define KSI_PAUSE	8
#define KSI_SKIP	9
#define KSI_ENTER	10
#define KSI_ESCAPE	11
#define KSI_CAPTURE	12

#define KS_UP		gameinput.keyKS.keyUp
#define KS_DOWN		gameinput.keyKS.keyDown
#define KS_LEFT		gameinput.keyKS.keyLeft
#define KS_RIGHT	gameinput.keyKS.keyRight
#define KS_FIRE		gameinput.keyKS.keyFire
#define KS_QUICK	gameinput.keyKS.keyQuick
#define KS_SLOW		gameinput.keyKS.keySlow
#define KS_DRAIN	gameinput.keyKS.keyDrain
#define KS_PAUSE	gameinput.keyKS.keyPause
#define KS_SKIP		gameinput.keyKS.keySkip
#define KS_ENTER	gameinput.keyKS.keyEnter
#define KS_ESCAPE	gameinput.keyKS.keyEscape
#define KS_CAPTURE	gameinput.keyKS.keyCapture

#define JS_FIRE				gameinput.keyJS.joyFire
#define JS_QUICK			gameinput.keyJS.joyQuick
#define JS_SLOW				gameinput.keyJS.joySlow
#define JS_DRAIN			gameinput.keyJS.joyDrain
#define JS_PAUSE			gameinput.keyJS.joyPause
#define JS_DEBUG_SPEEDUP	gameinput.keyJS.debug_joySpeedUp

class GameInput
{
public:
	GameInput();
	~GameInput();
	static bool InitInput(HGE * hge);
	static bool ReleaseInput();
	static bool UpdateInput(bool startstate=false);
	WORD updateActiveInput(bool copylast=false);
	static void SyncControlInput();
	static void SyncControlInputSelf();
	static void SyncForActiveInput();
	static void SwapInput(bool setswap);
private:
	bool getKey(int ksi, int type=DIKEY_PRESSED);
	void setKey(int ksi, bool set=true);
public:
	static bool GetKey(int ksi, int type=DIKEY_PRESSED);
	static void SetKey(int ksi, bool set=true);

	static WORD GetNowInput();
	static void SetNowInput(WORD nowinput);
public:

	union{
		struct{
			int keyUp;
			int keyDown;
			int keyLeft;
			int keyRight;
			int keyFire;
			int keyQuick;
			int keySlow;
			int keyDrain;
			int keyPause;
			int keySkip;
			int keyEnter;
			int keyEscape;
			int keyCapture;
		}		keyKS;
		int		keyKey[GAMEINPUTKEYMAX];
	};
	union{
		struct{
			int	joyFire;
			int	joyQuick;
			int	joySlow;
			int	joyDrain;
			int	joyPause;
			int debug_joySpeedUp;
		}		keyJS;
		int		joyKey[GAMEINPUTJOYMAX];
	};
	bool keycombineslowdrain;
	bool joycombineslowdrain;

	WORD activeInput;
	WORD lastActiveInput;
	WORD input;
	WORD lastInput;

	static HGE * hge;
	static GameInput gameinput;
};

#endif