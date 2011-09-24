#ifndef _ITEM_H
#define _ITEM_H

#include "BObject.h"

class Player;

//#define ITEMINFOFONTMAX		0x40

#define ITEMTYPEMAX			0x04
#define ITEMSPRITEMAX		ITEMTYPEMAX

#define ITEM_STARTSPEED		-5

#define	ITEM_GAUGE			0x0
#define	ITEM_BULLET			0x1
#define	ITEM_EX				0x2
#define	ITEM_POINT			0x3


class Item : public BObject
{
public:
	Item();
	~Item();

	static void Init();
	static void ClearItem();
	static void Action();
	static void RenderAll(BYTE playerindex);

	static void SendBullet(BYTE playerindex, float x, float y, BYTE setID);

	static int Build(BYTE playerindex, WORD type, float x, float y, bool bDrained = false, int angle = 9000, float speed = ITEM_STARTSPEED);

	void valueSet(WORD type, float x, float y, bool bDrained = false, int angle = 9000, float speed = ITEM_STARTSPEED);

//	static void ChangeItemID(WORD oriID, WORD toID);
	static void Release();

	void Render();

//	void action();
	void action(BYTE playerindex);
/*
	static void undrainAll();
	static void drainAll();
*/
public:
	bool bDrained;
	bool bFast;

	static hgeSprite *sprite[ITEMSPRITEMAX];
//	static VectorList<infoFont>infofont;

	static VectorList<Item>mi[M_PL_MATCHMAXPLAYER];
};

#endif