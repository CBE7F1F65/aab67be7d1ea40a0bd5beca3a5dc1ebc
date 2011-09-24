#ifndef _EFFECTSP_H
#define _EFFECTSP_H

#include "BObject.h"

#define EFFSPSET_LISTBEGIN	0x0
#define EFFSPSET_LISTUNTIL	0x100
#define EFFSPSET_FREEBEGIN	EFFSPSET_LISTBEGIN
#define EFFSPSET_FREEUNTIL	0x80
#define EFFSPSET_SYSTEMBEGIN	EFFSPSET_FREEUNTIL
#define EFFSPSET_SYSTEMUNTIL	EFFSPSET_LISTUNTIL

#define EFFSPSET_SYSTEM_SENDREDBULLET		0x80
#define EFFSPSET_SYSTEM_SENDBLUEBULLET		0x81
#define EFFSPSET_SYSTEM_SENDREDBIGBULLET	0x82
#define EFFSPSET_SYSTEM_SENDBLUEBIGBULLET	0x83
#define EFFSPSET_SYSTEM_SENDITEMBULLET	0x88
#define EFFSPSET_SYSTEM_SENDGHOST		0x90
#define EFFSPSET_SYSTEM_SENDEXATTACK	0x98

#define EFFSPSET_PLAYERUSE	0x100

#define	EFFSP_PLAYERCHANGE		0x01
#define	EFFSP_PLAYERSHOT		0x02
#define	EFFSP_PLAYERBORDER		0x03
#define EFFSP_PLAYERBORDERZONE	0x04
#define	EFFSP_PLAYERPOINT		0x05
#define	EFFSP_PLAYERCOLLAPSE	0x06

#define EFFSP_CHASE_NULL		0x00
#define EFFSP_CHASE_PLAYER_0	0x01
#define EFFSP_CHASE_PLAYER_1	0x02
#define EFFSP_CHASE_PLAYER_(X)	((X)?EFFSP_CHASE_PLAYER_1:EFFSP_CHASE_PLAYER_0)
#define EFFSP_CHASE_TARGET		0x10
#define EFFSP_CHASE_FREE		0x20

#define EFFSPSEND_COLOR_WHITE	0
#define EFFSPSEND_COLOR_RED		1
#define EFFSPSEND_COLOR_GREEN	2
#define EFFSPSEND_COLOR_BLUE	3

#define EFFSPSEND_COLORMAX	4
#define EFFSPSEND_ANIMATIONMAX	4

#define EFFSP_DEFAULTANIMATIONINTERVAL	8

class EffectSp : public BObject
{
public:
	EffectSp();
	~EffectSp();

	static void Init();
	static void ClearItem();
	static void Release();
	static int Build(int setID, WORD ID, int siid, float x, float y, int headangle=0, float hscale=1.0f, float vscale=0.0f);
	static void Action();
	static void RenderAll();

	void valueSet(int setID, WORD ID, int siid, float x, float y, int headangle=0, float hscale=1.0f, float vscale=0.0f);
	void actionSet(int angle, float speed, int headangleadd=0);
	void chaseSet(BYTE chaseflag, float aimx, float aimy, int chasetimer=-1, BYTE chaseaim=0xff);
	void colorSet(DWORD color, int blend=BLEND_DEFAULT);
	void animationSet(BYTE animation, BYTE animationinterval=EFFSP_DEFAULTANIMATIONINTERVAL);

	void AppendData(int ival, float fval);

	void EffectSpOff(BYTE playerindex, int setID, int ID=-1);

	void action();
	void Render();

public:
//	hgeSprite * sprite;

	WORD setID;

	int chasetimer;
	int headangleadd;
	float aimx;
	float aimy;
	int siid;
	int siidnow;
	int blend;
	BYTE animation;
	BYTE chaseflag;
	BYTE chaseaim;
	BYTE animationinterval;

	int nAppend;
	float fAppend;
	bool bAppend;

	static int senditemsiid[EFFSPSEND_COLORMAX][EFFSPSEND_ANIMATIONMAX];
	static int senditemexsiid;
	static hgeSprite * sprite;

	static VectorList<EffectSp> effsp[M_PL_MATCHMAXPLAYER];
};

#endif