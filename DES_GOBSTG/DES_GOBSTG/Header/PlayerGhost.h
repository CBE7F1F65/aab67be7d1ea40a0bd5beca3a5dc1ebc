#ifndef _PLAYERGHOST_H
#define _PLAYERGHOST_H

#include "BObject.h"

#define PGFLAG_SYNCPLAYER	0x0001
#define PGFLAG_STANDSHAKE	0x0002
#define PGFLAG_SCALESHAKE	0x0004
#define PGFLAG_REMAINSHOOTANGLE	0x0008
#define PGFLAG_TURN			0x0010
#define PGFLAG_NEGATIVE		0x0020
#define PGFLAG_ROLL			0x0040
#define PGFLAG_ANTISHOOTER	0x0080
#define PGFLAG_ATTRIBUTEMASK	0x00ff

#define PGFLAG_TRACE		0x0100
#define PGFLAG_STAY			0x0200
#define PGFLAG_CHASE		0x0400
#define PGFLAG_ABSSTAY		0x0800
#define PGFLAG_SELFMOVEMASK		0x0f00
#define PGFLAG_ACTIVEWHENCHARGE	0x1000
#define PGFLAG_STAYWHENCHARGE	0x2000
#define PGFLAG_ACTIVEMASK		0xf000

class PlayerGhost : public BObject
{
public:
	PlayerGhost();
	~PlayerGhost();

	void valueSet(BYTE playerindex, WORD ID, bool move=false);

	void Render();

	void AntiShooter(float aimx, float aimy);

	void action();

public:
	hgeSprite * sprite;
	float scale;
	float yshake;
	bool lastchasing;
	bool active;
	int shootangle;
	WORD flag;
	BYTE playerindex;
};

#endif