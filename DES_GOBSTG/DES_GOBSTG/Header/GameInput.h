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

#define KS_UP_(X)		gameinput[(X)].keyKS.keyUp
#define KS_DOWN_(X)		gameinput[(X)].keyKS.keyDown
#define KS_LEFT_(X)		gameinput[(X)].keyKS.keyLeft
#define KS_RIGHT_(X)	gameinput[(X)].keyKS.keyRight
#define KS_FIRE_(X)		gameinput[(X)].keyKS.keyFire
#define KS_QUICK_(X)	gameinput[(X)].keyKS.keyQuick
#define KS_SLOW_(X)		gameinput[(X)].keyKS.keySlow
#define KS_DRAIN_(X)	gameinput[(X)].keyKS.keyDrain
#define KS_PAUSE_(X)	gameinput[(X)].keyKS.keyPause
#define KS_SKIP_(X)		gameinput[(X)].keyKS.keySkip
#define KS_ENTER_(X)	gameinput[(X)].keyKS.keyEnter
#define KS_ESCAPE_(X)	gameinput[(X)].keyKS.keyEscape
#define KS_CAPTURE_(X)	gameinput[(X)].keyKS.keyCapture

#define KS_UP		KS_UP_(0)
#define KS_DOWN		KS_DOWN_(0)
#define KS_LEFT		KS_LEFT_(0)
#define KS_RIGHT	KS_RIGHT_(0)
#define KS_FIRE		KS_FIRE_(0)
#define KS_QUICK	KS_QUICK_(0)
#define KS_SLOW		KS_SLOW_(0)
#define KS_DRAIN	KS_DRAIN_(0)
#define KS_PAUSE	KS_PAUSE_(0)
#define KS_SKIP		KS_SKIP_(0)
#define KS_ENTER	KS_ENTER_(0)
#define KS_ESCAPE	KS_ESCAPE_(0)
#define KS_CAPTURE	KS_CAPTURE_(0)

#define JS_FIRE_(X)				gameinput[(X)].keyJS.joyFire
#define JS_QUICK_(X)			gameinput[(X)].keyJS.joyQuick
#define JS_SLOW_(X)				gameinput[(X)].keyJS.joySlow
#define JS_DRAIN_(X)			gameinput[(X)].keyJS.joyDrain
#define JS_PAUSE_(X)			gameinput[(X)].keyJS.joyPause
#define JS_DEBUG_SPEEDUP_(X)	gameinput[(X)].keyJS.debug_joySpeedUp

#define JS_FIRE		JS_FIRE_(0)
#define JS_QUICK	JS_QUICK_(0)
#define JS_SLOW		JS_SLOW_(0)
#define JS_DRAIN	JS_DRAIN_(0)
#define JS_PAUSE	JS_PAUSE_(0)
#define JS_DEBUG_SPEEDUP	JS_DEBUG_SPEEDUP_(0)

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
	static bool GetKey(BYTE playerindex, int ksi, int type=DIKEY_PRESSED);
	static void SetKey(BYTE playerindex, int ksi, bool set=true);

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
	static GameInput gameinput[M_PL_MATCHMAXPLAYER];
	static bool swapinput;
};

#endif