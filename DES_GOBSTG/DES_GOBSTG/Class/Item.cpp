#include "../header/Item.h"
#include "../header/Player.h"
#include "../header/Bullet.h"
#include "../header/SE.h"
#include "../header/SpriteItemManager.h"
#include "../header/FrontDisplayName.h"
#include "../header/FrontDisplay.h"
#include "../header/Export.h"
#include "../header/ProcessDefine.h"
#include "../header/Process.h"

hgeSprite * Item::sprite[ITEMSPRITEMAX];

//VectorList<infoFont> Item::infofont;
VectorList<Item> Item::mi;

#define ITEMMAX				0x10

#define _ITEM_GETR				8
#define _ITEM_DRAINDELAY		24
#define _ITEM_DRAINFASTSPEED	8.8f
#define _ITEM_DRAINSLOWSPEED	5.0f
#define _ITEM_UPSPEED		-1.0f
#define _ITEM_DROPSPEEDMAX		2.8f
#define _ITEM_DROPSPEEDACC		0.1f
#define _ITEM_RETHROWSPEED		-3.0f

Item::Item()
{
}

Item::~Item()
{
}

void Item::ClearItem()
{
	mi.clear_item();
//	infofont.clear_item();
}

void Item::Action()
{
	DWORD stopflag = Process::mp.GetStopFlag();
	bool binstop = FRAME_STOPFLAGCHECK_(stopflag, FRAME_STOPFLAG_ITEM);
	if (!binstop)
	{
		if (mi.getSize())
		{
			DWORD i = 0;
			DWORD size = mi.getSize();
			for (mi.toBegin(); i<size; mi.toNext(), i++)
			{
				if (!mi.isValid())
				{
					continue;
				}
				if ((*mi).exist)
				{
					(*mi).action();
				}
				else
				{
					mi.pop();
				}
			}
		}
	}
}

void Item::RenderAll()
{
	if (mi.getSize())
	{
		DWORD i = 0;
		DWORD size = mi.getSize();
		for (mi.toBegin(); i<size; mi.toNext(), i++)
		{
			if (mi.isValid())
			{
				(*mi).Render();
			}
		}
	}
}

void Item::Init()
{
	Release();
	mi.init(ITEMMAX);
//	infofont.init(ITEMINFOFONTMAX);
	int tidx = SpriteItemManager::GetIndexByName(SI_ITEM_GUARD);
	for(int i=0;i<ITEMTYPEMAX;i++)
	{
		sprite[i] = SpriteItemManager::CreateSprite(tidx+i);
	}
}

void Item::valueSet(WORD type, float _x, float _y, bool _bDrained, int _angle, float _speed)
{
	ID			=	type;
	x			=	_x;
	y			=	_y;
	bDrained	=	_bDrained;

	bFast	=	true;

	timer	=	0;
	speed	=	_speed;
	angle	=	_angle;
	headangle =	0;
	hscale	=	1.0f;
	vscale	=	1.0f;
	alpha	=	0xff;
	exist	=	true;
}

int Item::Build(WORD type, float _x, float _y, bool _bDrained /* = false */, int _angle, float _speed)
{
	if (mi.getSize() == ITEMMAX)
	{
		return -1;
	}
	mi.push_back()->valueSet(type, _x, _y, _bDrained, _angle, _speed);
	return mi.getEndIndex();
}

void Item::Release()
{
	for (int i=0; i<ITEMSPRITEMAX; i++)
	{
		if(sprite[i])
			SpriteItemManager::FreeSprite(&sprite[i]);
	}
	mi.clear();
//	infofont.clear();
}

void Item::Render()
{
	if (sprite[ID])
	{
		SpriteItemManager::RenderSpriteEx(sprite[ID], x, y, ARC(headangle));
	}
}

void Item::action()
{
	if(Player::p.bSlow && !bDrained && !(Player::p.flag & PLAYER_COLLAPSE || Player::p.flag & PLAYER_SHOT))
	{
//		float rdrain = (Player::p.bSlow) ? 64 : 48;
		float rdrain = 64;
		if (checkCollisionSquare(Player::p.x, Player::p.y, rdrain))
		{
			bDrained = true;
			bFast = false;
		}
	}
	if(bDrained)
	{
		if(timer > _ITEM_DRAINDELAY)
		{
			if(bFast)
				speed = _ITEM_DRAINFASTSPEED;
			else
				speed = _ITEM_DRAINSLOWSPEED;
			float dist = DIST(x, y, Player::p.x, Player::p.y);
			x += speed * (Player::p.x - x) / dist;
			y += speed * (Player::p.y - y) / dist;
		}
		else
		{
			speed = _ITEM_UPSPEED;
			y += speed;
		}
	}
	else if(speed > 0)
	{
		angle = 9000;
	}

	if (speed > 0)
	{
		headangle = 0;
	}
	else
	{
		headangle += SIGN((int)mi.getIndex()) * 600 * speed;
	}

	timer++;
	if(speed < _ITEM_DROPSPEEDMAX)
		speed += _ITEM_DROPSPEEDACC;
	if(!bDrained)
	{
		if(angle != 9000)
		{
			updateMove();
		}
		else
		{
			y += speed;
		}
	}

	if (checkCollisionSquare(Player::p.x, Player::p.y, _ITEM_GETR)
		&& !(Player::p.flag & PLAYER_COLLAPSE))
	{
		SE::push(SE_ITEM_POWERUP, x);

		Player::p.DoItemGet(ID, x, y);

		exist = false;
	}
	if(y > M_DELETECLIENT_BOTTOM)
		exist = false;
}