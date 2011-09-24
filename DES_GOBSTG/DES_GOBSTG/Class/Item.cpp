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
VectorList<Item> Item::mi[M_PL_MATCHMAXPLAYER];

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
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		mi[i].clear_item();
	}
//	infofont.clear_item();
}

void Item::Action()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		DWORD stopflag = Process::mp.GetStopFlag();
		bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, j, FRAME_STOPFLAG_ITEM);
		if (!binstop)
		{
			if (mi[j].getSize())
			{
				DWORD i = 0;
				DWORD size = mi[j].getSize();
				for (mi[j].toBegin(); i<size; mi[j].toNext(), i++)
				{
					if (!mi[j].isValid())
					{
						continue;
					}
					if ((*mi[j]).exist)
					{
						(*mi[j]).action(j);
					}
					else
					{
						mi[j].pop();
					}
				}
			}
		}
	}
}

void Item::RenderAll(BYTE playerindex)
{
	if (mi[playerindex].getSize())
	{
		DWORD i = 0;
		DWORD size = mi[playerindex].getSize();
		for (mi[playerindex].toBegin(); i<size; mi[playerindex].toNext(), i++)
		{
			if (mi[playerindex].isValid())
			{
				(*mi[playerindex]).Render();
			}
		}
	}
}

void Item::Init()
{
	Release();
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		mi[i].init(ITEMMAX);
	}
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

int Item::Build(BYTE playerindex, WORD type, float _x, float _y, bool _bDrained /* = false */, int _angle, float _speed)
{
	if (mi[playerindex].getSize() == ITEMMAX)
	{
		return -1;
	}
	mi[playerindex].push_back()->valueSet(type, _x, _y, _bDrained, _angle, _speed);
	return mi[playerindex].getEndIndex();
}

void Item::Release()
{
	for (int i=0; i<ITEMSPRITEMAX; i++)
	{
		if(sprite[i])
			SpriteItemManager::FreeSprite(&sprite[i]);
	}
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		mi[i].clear();
	}
//	infofont.clear();
}

void Item::Render()
{
	if (sprite[ID])
	{
		SpriteItemManager::RenderSpriteEx(sprite[ID], x, y, ARC(headangle));
	}
}

void Item::SendBullet(BYTE playerindex, float x, float y, BYTE setID)
{
	int siidindex = EFFSPSEND_COLOR_RED;
	if (playerindex)
	{
		siidindex = EFFSPSEND_COLOR_BLUE;
	}
	float _hscale = randtf(1.2f, 1.4f);
	int esindex = EffectSp::Build(setID, playerindex, EffectSp::senditemsiid[siidindex][0], x, y, 0, _hscale);
	if (esindex >= 0)
	{
		EffectSp * _peffsp = &(EffectSp::effsp[playerindex][esindex]);
		_peffsp->colorSet(0x80ffffff, BLEND_ALPHAADD);
		float aimx;
		float aimy;
		aimx = randtf(M_GAMESQUARE_LEFT_(playerindex) + 8, M_GAMESQUARE_RIGHT_(playerindex) - 8);
		aimy = randtf(M_GAMESQUARE_TOP, M_GAMESQUARE_TOP + 128);
		_peffsp->chaseSet(EFFSP_CHASE_FREE, aimx, aimy, randt(45, 60));
		_peffsp->animationSet(EFFSPSEND_ANIMATIONMAX);
		_peffsp->AppendData(0, 0);
	}
}

void Item::action(BYTE playerindex)
{
	if(Player::p[playerindex].bSlow && !bDrained && !(Player::p[playerindex].flag & PLAYER_COLLAPSE || Player::p[playerindex].flag & PLAYER_SHOT))
	{
//		float rdrain = (Player::p[playerindex].bSlow) ? 64 : 48;
		float rdrain = 64;
		if (checkCollisionSquare(Player::p[playerindex].x, Player::p[playerindex].y, rdrain))
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
			float dist = DIST(x, y, Player::p[playerindex].x, Player::p[playerindex].y);
			x += speed * (Player::p[playerindex].x - x) / dist;
			y += speed * (Player::p[playerindex].y - y) / dist;
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
		headangle += SIGN((int)mi[playerindex].getIndex()) * 600 * speed;
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

	if (checkCollisionSquare(Player::p[playerindex].x, Player::p[playerindex].y, _ITEM_GETR)
		&& !(Player::p[playerindex].flag & PLAYER_COLLAPSE))
	{
		SE::push(SE_ITEM_POWERUP, x);

		Player::p[playerindex].DoItemGet(ID, x, y);

		exist = false;
	}
	if(y > M_DELETECLIENT_BOTTOM)
		exist = false;
}