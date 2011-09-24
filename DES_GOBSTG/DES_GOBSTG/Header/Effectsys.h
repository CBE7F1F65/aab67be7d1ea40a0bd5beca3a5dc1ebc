#ifndef _EFFECTSYS_H
#define _EFFECTSYS_H

#include "MainDependency.h"
#include "Const.h"
#include "BObject.h"

#define EFFECTSYSMAX		0x100
#define EFFID_LEFTIDBEGIN	0x0
#define EFFID_LEFTIDUNTIL	(EFFECTSYSMAX/2)
#define EFFID_RIGHTIDBEGIN	EFFID_LEFTIDUNTIL
#define EFFID_RIGHTIDUNTIL	EFFECTSYSMAX

#define EFFSYS_AUTOFADEOUT_TIME	120

class Effectsys : public BObject
{
public:
	Effectsys();
	~Effectsys();

	static bool Init(HTEXTURE * tex, const char * foldername, char name[][M_PATHMAX]);
	static void Release();
	static void ClearAll();
	static void Action();
	static void RenderAll(BYTE playerindex);
	static int Build(WORD ID, BYTE playerindex, float x, float y, float z=0, int lifetime=-1, BYTE tarID=0xff, int angle=9000, float speed=0.0f, float zSpeed=0.0f);

	void Clear(bool erase=false);
	void valueSet(WORD ID, BYTE playerindex, float x, float y, float z=0, int lifetime=-1, BYTE tarID=0xff, int angle=9000, float speed=0.0f, float zSpeed=0.0f);
	void valueSet(WORD ID, BYTE playerindex, BObject & owner);
	void chaseSet(int chasetimer, BYTE tarAim);

	void SetColorMask(DWORD color);

	void MoveTo(float x, float y, float z = 0, bool bForce = false);
	void Fire();
	void Stop(bool bKill = false);
	void action(bool byself=false);

	void Render();

public:
	hgeEffectSystem eff;

	int lifetime;
	int chasetimer;
	float z;
	float zSpeed;

	BYTE tarAim;
	BYTE playerindex;

	static hgeEffectSystem efftype[EFFECTSYSTYPEMAX];
	static VectorList<Effectsys> effsys[M_PL_MATCHMAXPLAYER];
};

#endif