#ifndef _PLAYERBULLET_H
#define _PLAYERBULLET_H

#define PBLOCK_LOST		0xffff

#define PBFLAG_BEAM				0x0001
#define PBFLAG_CHASE			0x0002
#define PBFLAG_DELAY			0x0004
#define PBFLAG_RANDOMANGLE		0x0008
#define PBFLAG_TURN				0x0010
#define PBFLAG_TURNWHILEDELAY	0x0020
#define PBFLAG_RELATIVE			0x0040
#define PBFLAG_ANTISHOOTER		0x0080
#define PBFLAG_PREMASK			0x00ff

#define PBFLAG_OUTTURN			0x0100
#define PBFLAG_ANIMATION		0x0200
#define PBFLAG_REBOUND			0x0400
#define PBFLAG_EXPLODE			0x0800
#define PBFLAG_SCALEUP			0x1000
#define PBFLAG_ZONELIKE			0x2000
#define PBFLAG_POSTMASK			0xff00

#define PB_FADEOUTTIME		32

#include "BObject.h"
#include "Enemy.h"

class PlayerBullet : public BObject
{
public:
	PlayerBullet();
	~PlayerBullet();

	static void Init();
	static void BuildShoot(BYTE playerID, int usetimer, bool bhyper=false);
	static int Build(int shootdataID, bool explode=false, float xoffset=0, float yoffset=0);
	static void ClearItem();
	static void Action();
	static void RenderAll();
	static bool CheckShoot(Enemy * en, float aimx, float aimy, float aimw, float aimh=0.0f);

	void valueSet(WORD ID, BYTE arrange, float xbias, float ybias, float scale, int angle, int addangle, float speed, float accelspeed, float power, WORD flag, BYTE seID, int deletetime);

	void action();
	void Render();

	void hitOn();
	bool isInRange(float aimx, float aimy, float w, float h=0.0f);

	void Lock();

	void DelayShoot();
	void TurnBullet(float mul=1.0f);

	static void ClearLock();
	static bool CheckAndSetLock(BObject * pbobj, int lockedid);
	static bool GetLockAim(BObject ** ppbobj);
	static void Release();

public:
	float	oldspeed;
	float	accelspeed;
	float	xplus;
	float	yplus;

	float	xbias;
	float	ybias;
	float	scale;

	bool	fadeout;
	bool	able;
	float	power;

	int		locktimer;
	int		animation;

	int		addangle;
	int		deletetime;

	WORD	flag;

	BYTE	arrange;

	static hgeSprite * sprite[DATASTRUCT_PLAYERSHOOTTYPEMAX][DATASTRUCT_PLAYERBULLETTYPE];
	static int locked;
	static VectorList<PlayerBullet>pb;
};

#endif