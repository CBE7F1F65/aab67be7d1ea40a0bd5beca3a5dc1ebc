#ifndef _BULLET_H
#define _BULLET_H

#include "BObject.h"
#include "BulletListActionConst.h"
#include "Effectsys.h"

#define BULLETMAX			0x1000
#define BULLETCOLORMAX		0x10
#define BULLETTYPECOLORMAX	(BULLETTYPEMAX * BULLETCOLORMAX)

#define BULLETACTIONMAX		0x20
#define BULLETIZELISTMAX	0x04

#define BULLET_FADEINTYPE	(BULLETTYPEMAX - 3)
#define BULLET_FADEOUTTYPE	(BULLETTYPEMAX - 2)
#define BULLET_BONUSTYPE	(BULLETTYPEMAX - 1)
#define BULLET_ANGLEOFFSET	9000

#define BULLET_FADECOLOR_16	160
#define BULLET_FADECOLOR_8	80

#define BULLET_COLLISION_NONE		0
#define BULLET_COLLISION_CIRCLE		1
#define BULLET_COLLISION_ELLIPSE	2
#define BULLET_COLLISION_RECT		3
#define BULLET_COLLISION_SQURE		4

#define BULLET_ANIMATIONSPEED	4

#define BULLET_FADEINTIME	8
#define BULLET_TYPECHANGETIME 16

#define BULLETZONE_ERASE	0
#define BULLETZONE_SEND		1
#define BULLETZONE_EVENT	2

#define BULLET_EVENTMAX		4

#define BULLETACT_FLOATSCALE	100.0f
#define BULLETACT_ANGLECHANGESE	3000

typedef struct tagRenderDepth{
	int startIndex;
	int endIndex;
	bool haveType;
}RenderDepth;

class Bullet : public BObject
{
public:
	Bullet();
	~Bullet();

	static void Init();
	static void Release();
	static void ClearItem();
	static void Action();
	static void RenderAll(BYTE playerindex);
	void Render();

	void action();
	void actionInStop();

	int DoIze();
	bool DoCollision();
	void DoGraze();
	void DoUpdateRenderDepth();

	bool HaveGray();

	BYTE getRenderDepth();

	bool isInRect(float aimx, float aimy, float r, int nextstep=0);

	bool valueSet(BYTE playerindex, WORD ID, float x, float y, int angle, float speed, BYTE type, BYTE color, int fadeinTime, float avoid = 0, BYTE tarID = 0xff);

	static int Build(BYTE playerindex, float x, float y, int angle, float speed, BYTE type, BYTE color, int fadeinTime=BULLET_FADEINTIME, float avoid=0, BYTE tarID=0xff);
	static void BuildCircle(BYTE playerindex, int num, int baseangle, float baser, float x, float y, float speed, BYTE type, BYTE color, int fadeinTime=BULLET_FADEINTIME, float avoid=0);
	static void BuildLine(BYTE playerindex, int num, int baseangle, float space, int baseindex, float x, float y, int angle, float anglefactor, float speed, float speedfactor, BYTE type, BYTE color, int fadeinTime=BULLET_FADEINTIME, float avoid=0);

	void matchFadeInColorType();
	void matchFadeOutColorType();

	static void SendBullet(BYTE playerindex, float x, float y, BYTE setID, BYTE * sendtime=NULL, float * speed = NULL, int sendbonus=1);
	void AddSendInfo(BYTE sendsetID, BYTE _sendtime);

	bool passedEvent(DWORD eventID);
	void passEvent(DWORD eventID);

	bool ChangeAction(int nextstep=0);
	void changeType(BYTE totype);

public:
	int		actionList[BULLETACTIONMAX];

	DWORD	eventID[BULLET_EVENTMAX];

	float	xplus;
	float	yplus;
	float	lastx;
	float	lasty;
	float	lastspeed;
	int		lastangle;
	int		fadeinTime;

	bool	fadeout;
	bool	able;
	bool	grazed;
	bool	remain;
	bool	cancelable;

	BYTE	type;
	BYTE	oldtype;
	BYTE	color;
	BYTE	oldcolor;
	BYTE	playerindex;
	BYTE	typechangetimer;

	BYTE	sendtime;
	BYTE	sendsetID;
	int		sendbonus;

	BYTE	bouncetime;

	Effectsys	eff;

	static int _actionList[M_PL_MATCHMAXPLAYER][BULLETACTIONMAX];

	static RenderDepth renderDepth[M_PL_MATCHMAXPLAYER][BULLETTYPEMAX];
	static hgeSprite * sprite[BULLETTYPECOLORMAX];
	static WORD index;
	static VectorList<Bullet>bu[M_PL_MATCHMAXPLAYER];
	
	static int bulletcount[M_PL_MATCHMAXPLAYER];
};

#endif