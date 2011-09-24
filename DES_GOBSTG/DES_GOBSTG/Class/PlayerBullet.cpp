#include "../header/PlayerBullet.h"
#include "../header/Player.h"
#include "../header/Enemy.h"
#include "../header/SE.h"
#include "../header/Main.h"
#include "../header/SpriteItemManager.h"
#include "../header/FrontDisplayName.h"
#include "../header/BResource.h"
#include "../header/Export.h"
#include "../header/EventZone.h"
#include "../header/ProcessDefine.h"
#include "../header/Process.h"

VectorList<PlayerBullet> PlayerBullet::pb[M_PL_MATCHMAXPLAYER];

int PlayerBullet::locked[M_PL_MATCHMAXPLAYER];
int PlayerBullet::activelocked[M_PL_MATCHMAXPLAYER];

hgeSprite * PlayerBullet::sprite[PLAYERSHOOTTYPEMAX][PLAYERBULLETTYPE];

DWORD PlayerBullet::bcol0;
DWORD PlayerBullet::bcol1;
DWORD PlayerBullet::bcol2;
DWORD PlayerBullet::bcol3;
WORD PlayerBullet::beams;

#define _PBLOCK_ACCSPEED		1.0f
#define _PBLOCK_MINSPEED		2.0f
#define _PBLOCK_TURNMAX			600
#define _PBLOCK_LOCKTIMERMAX	0x80

#define _PBBEAM_LASTINDEX		1

#define _PBCHASE_TURNSPEEDDOWN	0.8f
#define _PBDELAY_SPEEDDOWN		0.9f

#define _PB_DELETEBOLDER		M_GAMESQUARE_HEIGHT
#define _PB_DELETE_LEFT_(X)		M_DELETECLIENT_LEFT_(X) - _PB_DELETEBOLDER
#define _PB_DELETE_RIGHT_(X)	M_DELETECLIENT_RIGHT_(X) + _PB_DELETEBOLDER
#define _PB_DELETE_TOP			M_DELETECLIENT_TOP - _PB_DELETEBOLDER
#define _PB_DELETE_BOTTOM		M_DELETECLIENT_BOTTOM + _PB_DELETEBOLDER

#define _PB_HEADARCPLUS			10

#define PLAYERBULLETMAX		0x100

#define _PBTEX_PLAYERBEGIN		10

PlayerBullet::PlayerBullet()
{
	able	= false;
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Init()
{
	Release();

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		pb[i].init(PLAYERBULLETMAX);
		locked[i] = PBLOCK_LOST;
		activelocked[i] = PBLOCK_LOST;
	}

	for (int i=0; i<PLAYERSHOOTTYPEMAX; i++)
	{
		for (int j=0; j<PLAYERBULLETTYPE; j++)
		{
			sprite[i][j] = SpriteItemManager::CreateSprite(BResource::bres.playershootdata[i].siid+(((BResource::bres.playershootdata[i].flag)&PBFLAG_ANIMATION)?j:0));
		}
	}
}

void PlayerBullet::Release()
{
	for (int i=0; i<PLAYERSHOOTTYPEMAX; i++)
	{
		for (int j=0; j<PLAYERBULLETTYPE; j++)
		{
			SpriteItemManager::FreeSprite(&sprite[i][j]);
		}

	}
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		pb[i].clear();
	}
}

void PlayerBullet::ClearItem()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		pb[i].clear_item();
		locked[i] = PBLOCK_LOST;
		activelocked[i] = PBLOCK_LOST;
	}
}

void PlayerBullet::Action()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		DWORD stopflag = Process::mp.GetStopFlag();
		bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, j, FRAME_STOPFLAG_PLAYERBULLET);
		if (!binstop)
		{
			if (pb[j].getSize())
			{
				DWORD i = 0;
				DWORD size = pb[j].getSize();
				for (pb[j].toBegin(); i<size; pb[j].toNext(), i++)
				{
					if (!pb[j].isValid())
					{
						continue;
					}
					DWORD _index = pb[j].getIndex();
					if ((*pb[j]).exist)
					{
						(*pb[j]).action();
					}
					else
					{
						pb[j].pop();
					}
					pb[j].toIndex(_index);
				}
			}
		}
	}
}

void PlayerBullet::RenderAll(BYTE playerindex)
{
	if (pb[playerindex].getSize())
	{
		DWORD i = 0;
		DWORD size = pb[playerindex].getSize();
		for (pb[playerindex].toBegin(); i<size; pb[playerindex].toNext(), i++)
		{
			if (pb[playerindex].isValid())
			{
				(*pb[playerindex]).Render();
			}

		}
	}
}

void PlayerBullet::BuildShoot(BYTE playerindex, BYTE playerID, int usetimer, bool bchargeshoot/* =false */)
{
	playershootData * item;
	for (int i=0; i<PLAYERSHOOTTYPEMAX; i++)
	{
		item = &(BResource::bres.playershootdata[i]);
		if (item->userID == playerID)
		{
			if ((bchargeshoot) ^ (item->bchargeshoot))
			{
				continue;
			}
			if (item->timeMod && (item->timeMod == 1 || !(usetimer % item->timeMod)))
			{
				Build(playerindex, i);
			}
		}
	}
}

int PlayerBullet::Build(BYTE playerindex, int shootdataID, bool explode/* =false */, float xoffset/* =0 */, float yoffset/* =0 */)
{
	if (pb[playerindex].getSize() == PLAYERBULLETMAX)
	{
		return -1;
	}
	PlayerBullet _pb;
	playershootData * item = &(BResource::bres.playershootdata[shootdataID]);
	if (!(item->timeMod) && !explode)
	{
		return -1;
	}
	pb[playerindex].push_back(_pb)->valueSet(playerindex, shootdataID, item->arrange, item->xbias+xoffset, item->ybias+yoffset, 
		item->scale, item->angle, item->addangle, item->speed, item->accelspeed, 
		item->power, item->hitonfactor, item->flag, item->seID, item->deletetime);
	return pb[playerindex].getEndIndex();
}

void PlayerBullet::valueSet(BYTE _playerindex, WORD _ID, BYTE _arrange, float _xbias, float _ybias, float _scale, int _angle, int _addangle, float _speed, float _accelspeed, float _power, int _hitonfactor, WORD _flag, BYTE seID, int _deletetime)
{
	playerindex = _playerindex;
	ID		=	_ID;
	angle	=	_angle;
	addangle =	_addangle;
	speed	=	_speed;
	accelspeed = _accelspeed;
	oldspeed =	speed;
	power	=	_power;
	hitonfactor = _hitonfactor;
	arrange	=	_arrange;
	flag	=	_flag;
	xbias	=	_xbias;
	ybias	=	_ybias;
	scale	=	_scale;
	deletetime = _deletetime;

	timer	=	0;
	exist	=	true;
	able	=	true;
	fadeout	=	false;
	hscale	=	1.0f;
	vscale	=	1.0f;
	headangle =	0;
	animation	=	0;

	diffuse	=	0xffffff;
	alpha	=	0xC0;

	if (flag & PBFLAG_RANDOMANGLE)
	{
		angle = randt(0, angle*2) - angle;
	}
	if (arrange)
	{
		angle += Player::p[playerindex].pg[arrange-1].shootangle;
	}
	if (flag & PBFLAG_ANTISHOOTER)
	{
		if (!arrange)
		{
			angle += Player::p[playerindex].aMainAngle(Player::p[playerindex].lastmx[0], Player::p[playerindex].lastmy[0]);
		}
	}
	else
	{
		angle += 27000;
	}

	if (!(flag & PBFLAG_ZONELIKE))
	{
		xplus	=	speed * cost(angle);
		yplus	=	speed * sint(angle);
	}
	else
	{
		xplus = 0;
		yplus = 0;
	}

	if (flag & PBFLAG_BEAM)
	{
		hscale = M_CLIENT_HEIGHT / SpriteItemManager::GetTexW(BResource::bres.playershootdata[ID].siid);
		vscale = scale / SpriteItemManager::GetTexH(BResource::bres.playershootdata[ID].siid);
		angle = -9000;
		for (int i=0; i<PLAYERBULLETTYPE; i++)
		{
			sprite[ID][i]->SetBlendMode(BLEND_ALPHAADD);
		}
	}
	else
	{
		if (flag & PBFLAG_ZONELIKE)
		{
			hscale = 0;
			vscale = 0;
		}
		else
		{
			hscale *= scale;
			vscale *= scale;
		}
	}
	locktimer = 0;

	if(arrange)
	{
		x = Player::p[playerindex].pg[arrange-1].x;
		y = Player::p[playerindex].pg[arrange-1].y;
	}
	else
	{
		x = Player::p[playerindex].x;
		y = Player::p[playerindex].y;
	}

	x += xbias;
	y += ybias;

	SE::push(seID, x);
}

void PlayerBullet::Render()
{
	if (sprite[ID][animation])
	{
		/*
		if (flag & PBFLAG_BEAM)
		{
			spriteData * spdata = SpriteItemManager::CastSprite(BResource::bres.playershootdata[ID].siid);
			sprite[ID][animation]->SetTextureRect(spdata->tex_x+timer*speed, spdata->tex_y, spdata->tex_w, spdata->tex_h);
		}
		*/
		sprite[ID][animation]->SetColor((alpha<<24)|diffuse);
		SpriteItemManager::RenderSpriteEx(sprite[ID][animation], x, y, ARC(angle+headangle), hscale, vscale);
	}
}

void PlayerBullet::ClearLock()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		locked[i] = PBLOCK_LOST;
		activelocked[i] = PBLOCK_LOST;
	}
}

bool PlayerBullet::CheckAndSetLock(BObject * pbobj, BYTE playerindex, int lockedid, bool active)
{
	if (locked[playerindex] != PBLOCK_LOST && activelocked[playerindex] != PBLOCK_LOST)
	{
		return false;
	}
	if (pbobj->x >= M_GAMESQUARE_LEFT_(playerindex) && pbobj->y <= M_GAMESQUARE_RIGHT_(playerindex) &&
		pbobj->y >= M_GAMESQUARE_TOP && pbobj->y <= M_GAMESQUARE_BOTTOM)
	{
		if (locked[playerindex] == PBLOCK_LOST)
		{
			locked[playerindex] = lockedid;
		}
		if (activelocked[playerindex] == PBLOCK_LOST && active && pbobj->y <= M_GAMESQUARE_BOTTOM-64)
		{
			activelocked[playerindex] = lockedid;
		}
		return true;
	}
	return false;
}

bool PlayerBullet::GetLockAim(BObject ** ppbobj, BYTE playerindex)
{
	int lockedid = activelocked[playerindex];
	if (activelocked[playerindex] == PBLOCK_LOST)
	{
		lockedid = locked[playerindex];
	}
	if (lockedid == PBLOCK_LOST)
	{
		return false;
	}
	if (ppbobj)
	{
		*ppbobj = &(Enemy::en[playerindex][lockedid]);
		return true;
	}
	return false;
}

void PlayerBullet::Lock()
{
	locktimer++;
	BObject * _tpbobj;

	if (!GetLockAim(&_tpbobj, playerindex))
	{
		if(speed < oldspeed)
			speed += _PBLOCK_ACCSPEED;
		if(speed > oldspeed)
			speed = oldspeed;
		return;
	}

	int aimangle = aMainAngle(_tpbobj->x, _tpbobj->y);
	bool clockwise = false;

	if(locktimer >= _PBLOCK_LOCKTIMERMAX)
	{
		locktimer = _PBLOCK_LOCKTIMERMAX;
		angle = aimangle;
	}

	while(angle > 18000)
		angle -= 36000;
	while(angle < -18000)
		angle += 36000;
	while(aimangle > 18000)
		aimangle -= 36000;
	while(aimangle < -18000)
		aimangle += 36000;

	int incangle = aimangle - angle;
	if(incangle > 18000)
		incangle = incangle - 36000;
	else if(incangle < -18000)
		incangle = 36000 + incangle;

	if(incangle > 0 && incangle < 18000)
		clockwise = true;

	incangle = abs(incangle);

	if(timer == 1 && incangle > 9000 && _tpbobj->y > y)
	{
		if(_tpbobj->x > x)
			angle = aimangle - 9000;
		else
			angle = aimangle + 9000;
	}

	if (speed < 0)
	{
		speed *= _PBDELAY_SPEEDDOWN;
	}
	else
	{
		if(incangle < _PBLOCK_TURNMAX)
		{
			angle = aimangle;
			if(speed < oldspeed)
			{
				speed += _PBLOCK_ACCSPEED;
			}
			if(speed > oldspeed)
				speed = oldspeed;
		}
		else
		{
			if(speed > _PBLOCK_MINSPEED)
				speed -= _PBLOCK_ACCSPEED;
			if(speed < _PBLOCK_MINSPEED)
				speed = _PBLOCK_MINSPEED;
			if(clockwise)
				angle += _PBLOCK_TURNMAX;
			else
				angle -= _PBLOCK_TURNMAX;
		}
	}
}

void PlayerBullet::hitOn()
{
//	Player::p[playerindex].DoPlayerBulletHit(hitonfactor);
	if (flag & PBFLAG_ZONELIKE)
	{
		return;
	}
	fadeout = true;
	able = false;
	timer = 0;
}

bool PlayerBullet::isInRange(float aimx, float aimy, float w, float h)
{
	bool hiton = true;
	if (flag & PBFLAG_BEAM)
	{
		hiton = false;
		w += scale / 2;
		if (timer == 0)
		{
			aimy += M_CLIENT_HEIGHT / 2;
		}
		h = M_CLIENT_HEIGHT / 2;
	}
	float rOri = BResource::bres.playershootdata[ID].collisionr * hscale;
	if (checkCollisionSquare(aimx, aimy, w, h, rOri))
	{
		if (hiton)
		{
			if (!(flag & PBFLAG_ZONELIKE) && (flag & PBFLAG_OUTTURN))
			{
				xplus = aimx - x;
			}
			hitOn();
		}
		else if ((flag & PBFLAG_BEAM)/* && !(timer % 24)*/)
		{
//			Player::p[playerindex].DoPlayerBulletHit(hitonfactor);
		}
		return true;
	}
	return false;
	
}

void PlayerBullet::DelayShoot()
{
	BObject * _tpbobj = NULL;
	GetLockAim(&_tpbobj, playerindex);
	if(timer == 1)
	{
		speed = -speed;
	}
	if(timer < PB_FADEOUTTIME)
	{
		if (flag & PBFLAG_TURNWHILEDELAY)
		{
			TurnBullet(oldspeed/6.0f);
		}
		speed *= _PBCHASE_TURNSPEEDDOWN;
	}
	else if(timer == PB_FADEOUTTIME)
	{
		headangle = 0;
		speed = oldspeed;
	}
	if (_tpbobj)
	{
		angle = aMainAngle(_tpbobj->x, _tpbobj->y);
	}
}

void PlayerBullet::TurnBullet(float mul)
{
	headangle += (xplus<0?1:-1)*_PBLOCK_TURNMAX * mul;
}

void PlayerBullet::action()
{
	timer++;

	if(!fadeout)
	{
		if (flag & PBFLAG_BEAM)
		{
			if (arrange)
			{
				y = Player::p[playerindex].pg[arrange-1].y;
			}
			else
			{
				y = Player::p[playerindex].y;
			}
			y += - M_CLIENT_HEIGHT / 2 + ybias;
			xplus = 0;
			yplus = 0;
			if (timer == 8)
			{
				timer = PB_FADEOUTTIME - 16;
				fadeout = true;
			}
		}

		else
		{
			speed += accelspeed;
			if ((flag & PBFLAG_DELAY) || (flag & PBFLAG_CHASE) || (flag & PBFLAG_TURNWHILEDELAY) || accelspeed)
			{
				if (flag & PBFLAG_DELAY)
				{
					DelayShoot();
				}
				if (flag & PBFLAG_CHASE)
				{
					Lock();
				}
				angle += addangle;
				xplus = speed * cost(angle);
				yplus = speed * sint(angle);
			}
			else
			{
				locktimer = 0;
				if (accelspeed && !(flag & PBFLAG_ZONELIKE))
				{
					xplus = speed * cost(angle);
					yplus = speed * sint(angle);
				}
			}

			if (flag & PBFLAG_ZONELIKE)
			{
				if (flag & PBFLAG_ANIMATION)
				{
					if (timer % (PB_FADEOUTTIME / 3 + 1) == 1)
					{
						animation++;
						if (animation >= PLAYERBULLETTYPE)
						{
							animation = 0;
						}
					}
				}
				if (hscale < scale)
				{
					hscale += speed;
				}
				if (hscale > scale)
				{
					hscale = scale;
				}
				vscale = hscale;
			}

			if (flag & PBFLAG_RELATIVE)
			{
				float basex;
				float basey;
				if (arrange)
				{
					basex = Player::p[playerindex].pg[arrange-1].x;
					basey = Player::p[playerindex].pg[arrange-1].y;
				}
				else
				{
					basex = Player::p[playerindex].x;
					basex = Player::p[playerindex].y;
				}
				x = basex + xplus*timer;
				y = basey + yplus*timer;
			}
			else
			{
				x += xplus;
				y += yplus;
			}

			if (flag & PBFLAG_TURN)
			{
				TurnBullet(speed/4.0f);
			}
		}
		if (deletetime && timer >= 16 && timer > deletetime-16)
		{
			alpha = (deletetime-timer)*0x0C;
		}
		if (deletetime && timer >= deletetime || x < _PB_DELETE_LEFT_(playerindex) || x > _PB_DELETE_RIGHT_(playerindex) || y < _PB_DELETE_TOP || y > _PB_DELETE_BOTTOM)
		{
			exist = false;
		}
	}
	else
	{
		if(timer == PB_FADEOUTTIME)
		{
			exist = false;
		}
		if (flag & PBFLAG_OUTTURN)
		{
			TurnBullet();
		}
		if (flag & PBFLAG_ANIMATION)
		{
			if (timer % (PB_FADEOUTTIME / 3 + 1) == 1)
			{
				animation++;
				if (animation >= PLAYERBULLETTYPE)
				{
					animation = PLAYERBULLETTYPE-1;
				}
			}
		}
		if (flag & PBFLAG_REBOUND)
		{
			if (xplus < 0)
			{
				x += 1;
			}
			else
			{
				x -= 1;
			}
			y -= 0.5f;
		}
		if (flag & PBFLAG_EXPLODE)
		{
			if (timer == 1)
			{
				Build(playerindex, ID+1, true, x-Player::p[playerindex].x, y-Player::p[playerindex].y);
//				SE::push(SE_PLAYER_EXPLODE, x);
			}

//			EventZone::Build(EVENTZONE_TYPE_ENEMYDAMAGE, playerindex, x, y, 32/BResource::bres.playershootdata[ID].timeMod, SpriteItemManager::GetTexW(BResource::bres.playershootdata[ID].siid), power);
		}
		if (flag & PBFLAG_SCALEUP)
		{
			hscale = (timer * 0.05f + 1.0f) * scale;
			vscale = hscale;
		}
		if (flag & PBFLAG_BEAM)
		{
			float taimx = Player::p[playerindex].x;
			if (arrange)
			{
				taimx = Player::p[playerindex].pg[arrange-1].x;
			}
			float taimy = Player::p[playerindex].y;
			if (arrange)
			{
				taimy = Player::p[playerindex].pg[arrange-1].y;
			}
			taimx += xbias;
			taimy += -M_CLIENT_HEIGHT / 2 + ybias;
			chaseAim(taimx, taimy, (64-timer));
			updateMove();
			angle = -9000;
		}
		alpha = (32 - timer) * 0x06;
	}
	able = exist && !fadeout;
}

bool PlayerBullet::CheckShoot(BYTE playerindex, Enemy * en, float aimx, float aimy, float aimw, float aimh)
{
//	float totalpower = 0.0f;
	bool hit = false;
	if (pb[playerindex].getSize())
	{
		DWORD i = 0;
		DWORD size = pb[playerindex].getSize();
		for (pb[playerindex].toBegin(); i<size; pb[playerindex].toNext(), i++)
		{
			if (pb[playerindex].isValid() && (*pb[playerindex]).able)
			{
				if ((*pb[playerindex]).isInRange(aimx, aimy, aimw, aimh))
				{
					hit = true;
//					totalpower += (*pb[playerindex]).power;
					if (en->CostLife((*pb[playerindex]).power))
					{
						Player::p[playerindex].DoPlayerBulletHit((*pb[playerindex]).hitonfactor);
						if ((*pb[playerindex]).hitonfactor >= 0)
						{
							en->ForceActive();
						}
					}
				}
			}
		}
	}
	return hit;
}