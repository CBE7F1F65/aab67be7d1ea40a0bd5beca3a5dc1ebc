#include "../Header/PlayerBullet.h"
#include "../Header/Player.h"
#include "../Header/Enemy.h"
#include "../Header/SE.h"
#include "../Header/Main.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/FrontDisplayName.h"
#include "../Header/BResource.h"
#include "../Header/Export.h"
#include "../Header/EventZone.h"
#include "../Header/ProcessDefine.h"
#include "../Header/Process.h"

VectorList<PlayerBullet> PlayerBullet::pb;

int PlayerBullet::locked;
bool PlayerBullet::havehyperbullet=false;

hgeSprite * PlayerBullet::sprite[DATASTRUCT_PLAYERSHOOTTYPEMAX][DATASTRUCT_PLAYERBULLETTYPE];

#define _PBLOCK_ACCSPEED		1.0f
#define _PBLOCK_MINSPEED		2.0f
#define _PBLOCK_TURNMAX			600
#define _PBLOCK_LOCKTIMERMAX	0x80

#define _PBBEAM_LASTINDEX		1

#define _PBCHASE_TURNSPEEDDOWN	0.8f
#define _PBDELAY_SPEEDDOWN		0.9f

#define _PB_DELETEBOLDER		M_GAMESQUARE_HEIGHT
#define _PB_DELETE_LEFT		M_DELETECLIENT_LEFT - _PB_DELETEBOLDER
#define _PB_DELETE_RIGHT	M_DELETECLIENT_RIGHT + _PB_DELETEBOLDER
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

	pb.init(PLAYERBULLETMAX);
	locked = PBLOCK_LOST;

	for (int i=0; i<DATASTRUCT_PLAYERSHOOTTYPEMAX; i++)
	{
		for (int j=0; j<DATASTRUCT_PLAYERBULLETTYPE; j++)
		{
			sprite[i][j] = SpriteItemManager::CreateSprite(BResource::bres.playershootdata[i].siid+(((BResource::bres.playershootdata[i].flag)&PBFLAG_ANIMATION)?j:0));
		}
	}
}

void PlayerBullet::Release()
{
	for (int i=0; i<DATASTRUCT_PLAYERSHOOTTYPEMAX; i++)
	{
		for (int j=0; j<DATASTRUCT_PLAYERBULLETTYPE; j++)
		{
			SpriteItemManager::FreeSprite(&sprite[i][j]);
		}

	}
	pb.clear();
}

void PlayerBullet::ClearItem()
{
	pb.clear_item();
	locked = PBLOCK_LOST;
}

void PlayerBullet::Action()
{
	DWORD stopflag = Process::mp.GetStopFlag();
	bool binstop = FRAME_STOPFLAGCHECK_(stopflag, FRAME_STOPFLAG_PLAYERBULLET);
	if (!binstop)
	{
		havehyperbullet = false;
		if (pb.getSize())
		{
			DWORD i = 0;
			DWORD size = pb.getSize();
			for (pb.toBegin(); i<size; pb.toNext(), i++)
			{
				if (!pb.isValid())
				{
					continue;
				}
				DWORD _index = pb.getIndex();
				if ((*pb).exist)
				{
					(*pb).action();
				}
				else
				{
					pb.pop();
				}
				pb.toIndex(_index);
			}
		}
	}
}

void PlayerBullet::RenderAll()
{
	if (pb.getSize())
	{
		DWORD i = 0;
		DWORD size = pb.getSize();
		for (pb.toBegin(); i<size; pb.toNext(), i++)
		{
			if (pb.isValid())
			{
				(*pb).Render();
			}

		}
	}
}

void PlayerBullet::BuildShoot(BYTE playerID, int usetimer, bool bhyper/* =false */)
{
	playershootData * item;
	for (int i=0; i<DATASTRUCT_PLAYERSHOOTTYPEMAX; i++)
	{
		item = &(BResource::bres.playershootdata[i]);
		if (item->userID == playerID)
		{
			if ((bhyper) ^ (item->bhypershoot))
			{
				continue;
			}
			if (item->timeMod && (item->timeMod == 1 || !((usetimer+item->timeoffset) % item->timeMod)))
			{
				Build(i);
			}
		}
	}
}

int PlayerBullet::Build(int shootdataID, bool explode/* =false */, float xoffset/* =0 */, float yoffset/* =0 */)
{
	if (pb.getSize() == PLAYERBULLETMAX)
	{
		return -1;
	}
	PlayerBullet _pb;
	playershootData * item = &(BResource::bres.playershootdata[shootdataID]);
	if (!(item->timeMod) && !explode)
	{
		return -1;
	}
	pb.push_back(_pb)->valueSet(shootdataID, item->arrange, item->xbias+xoffset, item->ybias+yoffset, 
		item->scale, item->angle, item->addangle, item->speed, item->accelspeed, 
		item->power, item->hyperpower, item->flag, item->seID, item->deletetime);
	return pb.getEndIndex();
}

void PlayerBullet::valueSet(WORD _ID, BYTE _arrange, float _xbias, float _ybias, float _scale, int _angle, int _addangle, float _speed, float _accelspeed, float _power, float _hyperpower, WORD _flag, BYTE seID, int _deletetime)
{
	ID		=	_ID;
	angle	=	_angle;
	addangle =	_addangle;
	speed	=	_speed;
	accelspeed = _accelspeed;
	oldspeed =	speed;
	power	=	_power;
	hyperpower	=	_hyperpower;
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
		angle += Player::p.pg[arrange-1].shootangle;
	}
	if (flag & PBFLAG_ANTISHOOTER)
	{
		if (!arrange)
		{
			angle += Player::p.aMainAngle(Player::p.lastmx[0], Player::p.lastmy[0]);
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
		for (int i=0; i<DATASTRUCT_PLAYERBULLETTYPE; i++)
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
		x = Player::p.pg[arrange-1].x;
		y = Player::p.pg[arrange-1].y;
	}
	else
	{
		x = Player::p.x;
		y = Player::p.y;
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
	locked = PBLOCK_LOST;
}

bool PlayerBullet::CheckAndSetLock(BObject * pbobj, int lockedid)
{
	if (locked != PBLOCK_LOST)
	{
		return false;
	}
	if (pbobj->x >= M_GAMESQUARE_LEFT && pbobj->y <= M_GAMESQUARE_RIGHT &&
		pbobj->y >= M_GAMESQUARE_TOP && pbobj->y <= M_GAMESQUARE_BOTTOM)
	{
		if (locked == PBLOCK_LOST)
		{
			locked = lockedid;
		}
		return true;
	}
	return false;
}

bool PlayerBullet::GetLockAim(BObject ** ppbobj)
{
	int lockedid = locked;
	if (lockedid == PBLOCK_LOST)
	{
		return false;
	}
	if (ppbobj)
	{
		*ppbobj = &(Enemy::en[lockedid]);
		return true;
	}
	return false;
}

void PlayerBullet::Lock()
{
	locktimer++;
	BObject * _tpbobj;

	if (!GetLockAim(&_tpbobj))
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
//	Player::p.DoPlayerBulletHit(hitonfactor);
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
//			Player::p.DoPlayerBulletHit(hitonfactor);
		}
		return true;
	}
	return false;
	
}

void PlayerBullet::DelayShoot()
{
	BObject * _tpbobj = NULL;
	GetLockAim(&_tpbobj);
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
				y = Player::p.pg[arrange-1].y;
			}
			else
			{
				y = Player::p.y;
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
						if (animation >= DATASTRUCT_PLAYERBULLETTYPE)
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
					basex = Player::p.pg[arrange-1].x;
					basey = Player::p.pg[arrange-1].y;
				}
				else
				{
					basex = Player::p.x;
					basex = Player::p.y;
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
		if (deletetime && timer >= deletetime || x < _PB_DELETE_LEFT || x > _PB_DELETE_RIGHT || y < _PB_DELETE_TOP || y > _PB_DELETE_BOTTOM)
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
				if (animation >= DATASTRUCT_PLAYERBULLETTYPE)
				{
					animation = DATASTRUCT_PLAYERBULLETTYPE-1;
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
				Build(ID+1, true, x-Player::p.x, y-Player::p.y);
//				SE::push(SE_PLAYER_EXPLODE, x);
			}

//			EventZone::Build(EVENTZONE_TYPE_ENEMYDAMAGE, x, y, 32/BResource::bres.playershootdata[ID].timeMod, SpriteItemManager::GetTexW(BResource::bres.playershootdata[ID].siid), power);
		}
		if (flag & PBFLAG_SCALEUP)
		{
			hscale = (timer * 0.05f + 1.0f) * scale;
			vscale = hscale;
		}
		if (flag & PBFLAG_BEAM)
		{
			float taimx = Player::p.x;
			if (arrange)
			{
				taimx = Player::p.pg[arrange-1].x;
			}
			float taimy = Player::p.y;
			if (arrange)
			{
				taimy = Player::p.pg[arrange-1].y;
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
	if (hyperpower && able)
	{
		havehyperbullet = true;
	}
}

bool PlayerBullet::CheckShoot(Enemy * en, float aimx, float aimy, float aimw, float aimh)
{
	bool hit = false;
	if (pb.getSize())
	{
		DWORD i = 0;
		DWORD size = pb.getSize();
		for (pb.toBegin(); i<size; pb.toNext(), i++)
		{
			if (pb.isValid() && (*pb).able)
			{
				if ((*pb).isInRange(aimx, aimy, aimw, aimh))
				{
					hit = true;
//					totalpower += (*pb).power;
					if (en->CostLife((*pb).power))
					{
						Player::p.DoPlayerBulletKill(en->type);
					}
				}
			}
		}
	}
	return hit;
}