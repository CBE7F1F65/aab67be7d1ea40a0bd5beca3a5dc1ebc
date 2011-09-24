#ifndef _EVENTZONE_H
#define _EVENTZONE_H

#include "MainDependency.h"
#include "Bullet.h"

#define EVENTZONE_EVENT_NULL	0x0

#define EVENTZONE_TYPE_NULL			0x0000
#define EVENTZONE_TYPE_BULLETFADEOUT	0x0001
#define EVENTZONE_TYPE_SENDBULLET	0x0002
#define EVENTZONE_TYPE_ENEMYDAMAGE	0x0004
#define EVENTZONE_TYPE_ENEMYBLAST	0x0008
#define EVENTZONE_TYPE_NOSEND		0x0010
#define EVENTZONE_TYPE_PLAYERSPEED	0x0020
#define EVENTZONE_TYPE_PLAYERDAMAGE	0x0040

#define EVENTZONE_TYPE_BULLETPERFECTFREEZE	0x0100
#define EVENTZONE_TYPE_BULLETSTUPA			0x0200
#define EVENTZONE_TYPE_BULLETWARP			0x0400

#define EVENTZONE_TYPE_BULLETEVENT	0x00010000
#define EVENTZONE_TYPE_PLAYEREVENT	0x00020000
#define EVENTZONE_TYPE_ENEMYEVENT	0x00040000

#define EVENTZONE_CHECKTYPE_CIRCLE		0x01000000
#define EVENTZONE_CHECKTYPE_SQUARE		0x02000000

#define EVENTZONE_CHECK_CONTINUEFLAG	0x80000000

#define EVENTZONE_OVERZONE	((M_GAMESQUARE_WIDTH + M_GAMESQUARE_HEIGHT) / 2)

#define EVENTZONE_TYPEMASK_BULLET	(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_SENDBULLET|EVENTZONE_TYPE_BULLETPERFECTFREEZE|EVENTZONE_TYPE_BULLETSTUPA|EVENTZONE_TYPE_BULLETWARP|EVENTZONE_TYPE_BULLETEVENT)
#define EVENTZONE_TYPEMASK_PLAYER	(EVENTZONE_TYPE_PLAYERSPEED|EVENTZONE_TYPE_PLAYERDAMAGE|EVENTZONE_TYPE_PLAYEREVENT)
#define EVENTZONE_TYPEMASK_ENEMY	(EVENTZONE_TYPE_ENEMYDAMAGE|EVENTZONE_TYPE_ENEMYBLAST|EVENTZONE_TYPE_ENEMYEVENT)

class EventZone
{
public:
	EventZone();
	~EventZone();

	static void Clear();
	static void RenderAll(BYTE playerindex);
	static void Build(DWORD type, BYTE playerindex, float x, float y, int maxtime=1, float rx=EVENTZONE_OVERZONE, float ry=EVENTZONE_OVERZONE, float power=0, DWORD eventID=EVENTZONE_EVENT_NULL, float rspeed=0, int inittimer=0, int siid=-1, int turnangle=0);
	static void Action();

	bool action();
	void Render();
	bool isInRect(float aimx, float aimy, float r, float oriw=0, float orih=0, int nextstep=0);

public:
	BYTE playerindex;
	float x;
	float y;
	float rx;
	float ry;
	float rspeed;
	float power;
	float width;
	int timer;
	int maxtime;
	int turnangle;
	DWORD type;
	DWORD eventID;
	hgeSprite * sprite;

	static int bulletActionList[M_PL_MATCHMAXPLAYER][BULLETACTIONMAX];
	static list<EventZone>ezone[M_PL_MATCHMAXPLAYER];
};

#endif