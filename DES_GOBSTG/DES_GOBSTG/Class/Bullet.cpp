#include "../Header/Bullet.h"
#include "../Header/Player.h"
#include "../Header/SE.h"
#include "../Header/Item.h"
#include "../Header/BossInfo.h"
#include "../Header/Scripter.h"
#include "../Header/Main.h"
#include "../Header/BResource.h"
#include "../Header/Target.h"
#include "../Header/Export.h"
#include "../Header/EventZone.h"
#include "../Header/EffectSp.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/ProcessDefine.h"
#include "../Header/GameAI.h"
#include "../Header/Process.h"

#define _BULLETRENDERFLAG_NONE	0
#define _BULLETRENDERFLAG_ROUND	1

#define _BULLETWOUNDINGSPEEDLOSS	0.2f
#define _BULLETWOUNDINGTIMEMAX		16

RenderDepth Bullet::renderDepth[DATASTRUCT_BULLETTYPEMAX];

int Bullet::_actionList[BULLETACTIONMAX];
hgeSprite * Bullet::sprite[BULLETTYPECOLORMAX];

VectorList<Bullet> Bullet::bu;

list<AppendingRenderInfo> Bullet::appendingrenderlist;

int Bullet::bulletcount;

WORD Bullet::index;

Bullet::Bullet()
{
	able	= false;
}

Bullet::~Bullet()
{
	eff.Clear();
}

void Bullet::Init()
{
	Release();

	ZeroMemory(renderDepth, sizeof(RenderDepth) * DATASTRUCT_BULLETTYPEMAX);
	bu.init(BULLETMAX);
	for (int i=0; i<DATASTRUCT_BULLETTYPEMAX; i++)
	{
		bulletData * tbd = &BResource::bres.bulletdata[i];
		int tnum = tbd->nRoll;
		if (tnum < 2)
		{
			tnum = BResource::bres.bulletdata[i].nColor;
		}
		int j=0;
		int index;
		for (j=0; j<tnum; j++)
		{
			index = i*BULLETCOLORMAX+j;
			sprite[index] = SpriteItemManager::CreateSprite(tbd->siid+j);
			sprite[index]->SetBlendMode(tbd->blendtype);
			if (BResource::bres.bulletdata[i].collisiontype != BULLET_COLLISION_ELLIPSE && BResource::bres.bulletdata[i].collisiontype != BULLET_COLLISION_RECT && tbd->collisionSub)
			{
				SpriteItemManager::SetSpriteHotSpot(sprite[index], SpriteItemManager::GetTexW(tbd->siid+j)/2.0f, SpriteItemManager::GetTexH(tbd->siid+j)/2.0f+tbd->collisionSub);
			}
		}
		for (; j<BULLETCOLORMAX; j++)
		{
			index = i*BULLETCOLORMAX+j;
			sprite[index] = SpriteItemManager::CreateNullSprite();
			HTEXTURE tex(TEX_BULLET, NULL);
			SpriteItemManager::SetSpriteData(sprite[index], tex, 0, 0, 0, 0);
		}
	}

	index = 0;
}

void Bullet::BuildCircle(DWORD _enguid, int num, int baseangle, float baser, float x, float y, float speed, BYTE type, BYTE color, int fadeinTime, float avoid)
{
	if (num <= 0)
	{
		return;
	}
	int anglestep = 36000 / num;
	for (int i=0; i<num; i++)
	{
		int tnowangle = baseangle + i * anglestep;
		float tx = x + cost(tnowangle) * baser;
		float ty = y + sint(tnowangle) * baser;
		Build(_enguid, tx, ty, tnowangle, speed, type, color, fadeinTime, avoid, 0xff);
	}
}

void Bullet::BuildLine(DWORD _enguid, int num, int baseangle, float space, int baseindex, float x, float y, int angle, float anglefactor, float speed, float speedfactor, BYTE type, BYTE color, int fadeinTime, float avoid)
{
	if (num <= 0)
	{
		return;
	}
	for (int i=0; i<num; i++)
	{
		int tindex = i - baseindex;
		float tx = x + tindex * cost(baseangle) * space;
		float ty = y + tindex * sint(baseangle) * space;
		Build(_enguid, tx, ty, angle + anglefactor * tindex, speed + speedfactor * abs(tindex), type, color, fadeinTime, avoid, 0xff);
	}
}

int Bullet::Build(DWORD _enguid, float x, float y, int angle, float speed, BYTE type, BYTE color, int fadeinTime, float avoid, BYTE tarID)
{
	if (bu.getSize() == BULLETMAX)
	{
		return -1;
	}
	if (bulletcount >= Process::mp.bulletcountmax)
	{
		return -1;
	}
	Bullet * _tbu = NULL;
	_tbu = bu.push_back();
	int _index = bu.getEndIndex();
	if (!_tbu->valueSet(_index, _enguid, x, y, angle, speed, type, color, fadeinTime, avoid, tarID))
	{
		bu.pop(_index);
		return -1;
	}
	bulletcount++;
	memcpy(_tbu->actionList, _actionList, BULLETACTIONMAX*sizeof(int));
	return _index;
}

void Bullet::Release()
{
	bu.clear();
	for(int i=0;i<BULLETTYPECOLORMAX;i++)
	{
		SpriteItemManager::FreeSprite(&sprite[i]);
	}
}

void Bullet::ClearItem()
{
	bu.clear_item();
	ZeroMemory(_actionList, sizeof(int) * BULLETACTIONMAX);
	index = 0;
	appendingrenderlist.clear();
}

void Bullet::Action()
{
	bulletcount = 0;
	if (bu.getSize())
	{
		ZeroMemory(Bullet::renderDepth, sizeof(RenderDepth) * DATASTRUCT_BULLETTYPEMAX);
		DWORD i = 0;
		DWORD size = bu.getSize();
		DWORD stopflag = Process::mp.GetStopFlag();
		bool binstop = FRAME_STOPFLAGCHECK_(stopflag, FRAME_STOPFLAG_BULLET);
		for (bu.toBegin(); i<size; bu.toNext(), i++)
		{
			if (!bu.isValid())
			{
				continue;
			}
			if ((*bu).exist)
			{
				DWORD _index = bu.getIndex();
				if (!binstop)
				{
					(*bu).action();
				}
				else
				{
					(*bu).actionInStop();
				}
				bu.toIndex(_index);
				GameAI::ai.CheckBulletCollision(&(*bu));
				bulletcount++;
			}
			else
			{
				bu.pop();
			}
		}
	}
}

void Bullet::RenderAll()
{
	if (bu.getSize())
	{
		for (int i=0; i<DATASTRUCT_BULLETTYPEMAX; i++)
		{
			if (Bullet::renderDepth[i].haveType)
			{
				bool bentered = false;
				for (bu.toIndex(Bullet::renderDepth[i].startIndex); !bentered || bu.getIndex() != Bullet::renderDepth[i].endIndex; bu.toNext())
				{
					bentered = true;
					if (bu.isValid() && (*bu).getRenderDepth() == i)
					{
						(*bu).Render();
					}
				}
			}
		}

		if (!appendingrenderlist.empty())
		{
			for (list<AppendingRenderInfo>::iterator it=appendingrenderlist.begin(); it!=appendingrenderlist.end(); ++it)
			{
				SpriteItemManager::RenderSpriteEx(sprite[it->index], it->x, it->y, it->arc);
			}
		}
		appendingrenderlist.clear();
	}
}

void Bullet::Render()
{
	int i = type*BULLETCOLORMAX + color;
	if (sprite[i])
	{
		sprite[i]->SetColor(alpha<<24 | diffuse);
		float arc = 0;
		if (!(BResource::bres.bulletdata[type].renderflag & _BULLETRENDERFLAG_ROUND))
		{
			arc = ARC(angle+headangle+BULLET_ANGLEOFFSET);
		}
		SpriteItemManager::RenderSpriteEx(sprite[i], x, y, arc, hscale);
		eff.Render();

		if ((frozen || woundingtimer) && able)
		{
			AppendingRenderInfo _frinfo;
			_frinfo.x = x;
			_frinfo.y = y;
			int tindex = index;
			int appendingtype;
			if (frozen)
			{
				appendingtype = BResource::bres.bulletdata[oldtype].frozentype;
				_frinfo.arc = x*y;
			}
			else
			{
				appendingtype = BResource::bres.bulletdata[oldtype].woundingtype;
				_frinfo.arc = ARC(angle);
			}
			int colorrand = index % BResource::bres.bulletdata[appendingtype].nColor;
			_frinfo.index = appendingtype*BULLETCOLORMAX+colorrand;
			appendingrenderlist.push_back(_frinfo);
		}
	}
}

BYTE Bullet::getRenderDepth()
{
	return BResource::bres.bulletdata[type].renderdepth;
}

void Bullet::matchFadeInColorType()
{
	if (fadeinTime < 0)
	{
		return;
	}
	if( BResource::bres.bulletdata[type].fadecolor < BULLETCOLORMAX)
	{
		color = BResource::bres.bulletdata[type].fadecolor;
		changeType(BULLET_FADEINTYPE);
//		type = BULLET_FADEINTYPE;
	}
	else if (BResource::bres.bulletdata[type].fadecolor == BULLET_FADECOLOR_16)
	{
		changeType(BULLET_FADEINTYPE);
//		type = BULLET_FADEINTYPE;
		if (color == 0)
		{
		}
		else if (color < 9)
		{
			color = (color+1)/2;
		}
		else
		{
			color = (color-9)/3+5;
		}
	}
	else if (BResource::bres.bulletdata[type].fadecolor == BULLET_FADECOLOR_8)
	{
		changeType(BULLET_FADEINTYPE);
//		type = BULLET_FADEINTYPE;
	}
}
void Bullet::matchFadeOutColorType()
{
	if (BResource::bres.bulletdata[type].fadecolor < BULLETCOLORMAX)
	{
		color = BResource::bres.bulletdata[type].fadecolor;
		changeType(BULLET_FADEOUTTYPE);
//		type = BULLET_FADEOUTTYPE;
	}
	else if (BResource::bres.bulletdata[type].fadecolor == BULLET_FADECOLOR_16)
	{
		changeType(BULLET_FADEOUTTYPE);
//		type = BULLET_FADEOUTTYPE;
		if (color == 0)
		{
		}
		else if (color < 9)
		{
			color = (color+1)/2;
		}
		else
		{
			color = (color-9)/3+5;
		}
	}
	else if (BResource::bres.bulletdata[type].fadecolor == BULLET_FADECOLOR_8)
	{
		type = BULLET_FADEOUTTYPE;
	}
}

bool Bullet::valueSet(WORD _ID, DWORD _enguid, float _x, float _y, int _angle, float _speed, BYTE _type, BYTE _color, int _fadeinTime, float avoid, BYTE _tarID)
{
	ID			=	_ID;
	enguid		=	_enguid;
	x			=	_x;
	y			=	_y;
	changeType(_type);
//	type		=	_type;
	if(avoid)
	{
		if(isInRect(Player::p.x, Player::p.y, avoid))
			return false;
	}
	angle		=	_angle;
	speed		=	_speed;
	oldtype		=	type;
	color		=	_color;
	oldcolor	=	color;
	fadeinTime	=	_fadeinTime;
	life		=	BResource::bres.bulletdata[type].life;

	for (int i=0; i<BULLET_EVENTMAX; i++)
	{
		eventID[i] = 0;
	}

	tarID	=	_tarID;

	matchFadeInColorType();

	timer			=	0;
	typechangetimer	=	0;
	exist			=	true;
	grazed			=	false;
	fadeout			=	false;
	able			=	true;
	remain			=	false;
	actionList[0]	=	SECTIONEND;
	hscale			=	1.0f;
	headangle		=	0;
	alpha			=	0xff;
	cancelable		=	true;
	bouncetime		=	0;
	woundingtimer	=	0;
	woundingcost	=	0;
	frozen			=	false;

	xplus = speed * cost(angle);
	yplus = speed * sint(angle);
	lastx = x;
	lasty = y;
	lastangle = angle;
	lastspeed = speed;

	return true;
}

float Bullet::DoHyper()
{
	if (PlayerBullet::havehyperbullet)
	{
		if (PlayerBullet::pb.getSize())
		{
			DWORD i = 0;
			DWORD size = PlayerBullet::pb.getSize();
			for (PlayerBullet::pb.toBegin(); i<size; PlayerBullet::pb.toNext(), i++)
			{
				if (!PlayerBullet::pb.isValid())
				{
					continue;
				}
				DWORD _index = PlayerBullet::pb.getIndex();
				if ((*PlayerBullet::pb).able)
				{
					if (isInRect((*PlayerBullet::pb).x, (*PlayerBullet::pb).y, 8))
					{
						woundingtimer = _BULLETWOUNDINGTIMEMAX;
						return Player::p.GetHyperCostLife((*PlayerBullet::pb).hyperpower);
					}
				}
			}
		}
	}
	return 0;
}

int Bullet::DoIze()
{
	if (cancelable || BossInfo::bossinfo.flag>=BOSSINFO_COLLAPSE)
	{
		for (list<EventZone>::iterator it=EventZone::ezone.begin(); it!=EventZone::ezone.end(); it++)
		{
			if (it->timer < 0)
			{
				continue;
			}
			if ((it->type) & EVENTZONE_TYPEMASK_BULLET)
			{
				if (it->isInRect(x, y, 0))
				{
					if (it->type & EVENTZONE_TYPE_BULLETFADEOUT)
					{
						fadeout = true;
						timer = 0;
					}
					if (it->type & EVENTZONE_TYPE_BULLETFREEZE)
					{
						if (!passedEvent(it->eventID) && timer >= fadeinTime)
						{
							timer = 0;
							speed = 0;
							fadeinTime = -1;
							EventZone::bulletActionList[0] = TIMEREQUAL;
							EventZone::bulletActionList[1] = it->maxtime;
							EventZone::bulletActionList[2] = BULLETDIE;
							EventZone::bulletActionList[3] = SECTIONEND;
							memcpy(actionList, EventZone::bulletActionList, BULLETACTIONMAX*sizeof(int));
							frozen = true;
							passEvent(it->eventID);
						}
					}
					if (it->type & EVENTZONE_TYPE_BULLETEVENT)
					{
						if (!passedEvent(it->eventID))
						{
							Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_BULLETENTERZONE, it->eventID);
							passEvent(it->eventID);
						}

					}
				}
			}
		}
	}
	return 0;
}

void Bullet::DoGraze()
{
	if(!grazed && BResource::bres.bulletdata[type].collisiontype != BULLET_COLLISION_NONE)
	{
		if (isInRect(Player::p.x, Player::p.y, PLAYER_GRAZE_R))
		{
			Player::p.DoGraze(x, y);
			grazed = true;
		}
	}
}

void Bullet::DoDead()
{
	fadeout = true;
	timer = 0;
	Player::p.DoBulletDead(x, y, frozen);
}

bool Bullet::DoCollision()
{
	if(isInRect(Player::p.x, Player::p.y, Player::p.r))
	{
		/*
		if (cancelable)
		{
			sendsetID = 0;
			fadeout = true;
			timer = 0;
		}
		*/
		Player::p.DoShot();
		return true;
	}
	return false;
}

void Bullet::DoUpdateRenderDepth()
{
	if (exist)
	{
		BYTE rdtype = getRenderDepth();
		if (!renderDepth[rdtype].haveType)
		{
			renderDepth[rdtype].haveType = true;
			renderDepth[rdtype].startIndex = index;
		}
		renderDepth[rdtype].endIndex = index + 1;
		if (renderDepth[rdtype].endIndex >= BULLETMAX)
		{
			renderDepth[rdtype].endIndex = 0;
		}
	}
}

bool Bullet::HaveGray()
{
	if (!(BResource::bres.bulletdata[type].nColor % 8))
	{
		return true;
	}
	return false;
}

void Bullet::actionInStop()
{
	index = ID;
	if (!fadeout)
	{
		life -= DoHyper();
		if (life < 0)
		{
			DoDead();
		}
		DoIze();
		if (timer > fadeinTime)
		{
			DoGraze();
		}
	}
	able = exist && !fadeout;
	DoUpdateRenderDepth();
}

bool Bullet::passedEvent(DWORD _eventID)
{
	for (int i=0; i<BULLET_EVENTMAX; i++)
	{
		if (eventID[i] == _eventID)
		{
			return true;
		}
		else if (eventID[i] == 0)
		{
			return false;
		}
	}
	return false;
}

void Bullet::passEvent(DWORD _eventID)
{
	for (int i=0; i<BULLET_EVENTMAX; i++)
	{
		if (eventID[i] == 0)
		{
			eventID[i] = _eventID;
			return;
		}
	}
	eventID[0] = _eventID;
}

void Bullet::changeType(BYTE totype)
{
	if (type != totype)
	{
		eff.Stop();
		type = totype;
		BYTE effID = BResource::bres.bulletdata[type].effID;
		if (effID)
		{
			eff.valueSet(effID, *this);
		}
	}
}

void Bullet::action()
{
	index = ID;
	if(angle != lastangle || lastspeed == 0)
	{
		xplus = speed * cost(angle);
		yplus = speed * sint(angle);
	}
	else if(speed != lastspeed)
	{
		xplus *= speed / lastspeed;
		yplus *= speed / lastspeed;
	}
	lastangle = angle;
	lastspeed = speed;
	
	timer++;

	lastx = x;
	lasty = y;


	if(!fadeout)
	{
		if(timer == 1 && fadeinTime > 1)
		{
			if(oldtype != type)
			{
				hscale *= (fadeinTime + 15.0f) * 0.0625f;
			}
			else
			{
				hscale /= fadeinTime;
			}
		}
		else if(fadeinTime > 0 && timer < (DWORD)fadeinTime)
		{
			if(oldtype != type)
			{
				hscale -= 0.0625f;
				alpha = 0x80;
			}
			else
			{
				hscale += 1.0f / fadeinTime;
			}
		}
		else if(timer == fadeinTime || fadeinTime < 0)
		{
			if (fadeinTime >= 0)
			{
				if(oldtype != type)
				{
					hscale -= 0.0625f;
				}
				else
				{
					hscale += 1.0f / fadeinTime;
				}
			}
			else
			{
				fadeinTime = 1;
			}
			changeType(oldtype);
//			type = oldtype;
			color = oldcolor;
			alpha = 0xff;
			eff.MoveTo(x, y, true);
			eff.Fire();
			SE::push(BResource::bres.bulletdata[type].seID, x);
		}
		else
		{

			if (able)
			{
				DoCollision();
				DoGraze();
				if (woundingtimer)
				{
					woundingtimer--;
					x -= xplus*_BULLETWOUNDINGSPEEDLOSS;
					y -= yplus*_BULLETWOUNDINGSPEEDLOSS;
					life -= woundingcost;
					if (life < 0)
					{
						DoDead();
					}
				}
				if (!woundingtimer && timer > fadeinTime)
				{
					woundingcost = DoHyper();
				}
			}
			x += xplus;
			y += yplus;

			if (able)
			{

				ChangeAction();

				if (BResource::bres.bulletdata[type].nRoll && !(timer % BULLET_ANIMATIONSPEED))
				{
					color++;
					if (color >= BResource::bres.bulletdata[type].nRoll)
					{
						color = 0;
					}
				}

				if(typechangetimer)
				{
					if(typechangetimer == 1)
					{
						hscale *= (BULLET_TYPECHANGETIME + 15.0f) * 0.0625f;
						matchFadeInColorType();
					}
					if(typechangetimer < BULLET_TYPECHANGETIME)
					{
						typechangetimer++;
						hscale -= 0.0625f;
						alpha = 0x80;
					}
					else
					{
						hscale -= 0.0625f;
						changeType(oldtype);
//						type = oldtype;
						color = oldcolor;
						typechangetimer = 0;
						alpha = 0xff;
					}
				}
			}
		}
		DoIze();
		headangle += SIGN(color) * BResource::bres.bulletdata[type].nTurnAngle;
		if(tarID != 0xff)
		{
			Target::SetValue(tarID, x, y);
		}

		//
		eff.MoveTo(x, y);
		eff.action();
		//

		if(!remain && timer > fadeinTime)
		{
			if(x > M_DELETECLIENT_RIGHT || x < M_DELETECLIENT_LEFT || y > M_DELETECLIENT_BOTTOM || y < M_DELETECLIENT_TOP)
				exist = false;
		}
		remain = false;
	}
	else
	{
		if(timer == 16)
		{
		}
		else if(timer == 32)
		{
			exist = false;
		}
		else if(timer == 96)
			exist = false;
		else if(timer < 32)
		{
			diffuse = 0xffffff;
			matchFadeOutColorType();
			hscale = timer / 40.0f + 1.0f;
			alpha = (BYTE)(32-timer) * 4 - 1;
		}
		else if(timer > 32 && timer < 96)
		{
			if(timer > 64)
				alpha = (BYTE)(96-timer) * 8 - 1;
			y -= 0.2f;
		}
	}
	able = exist && !fadeout;

	DoUpdateRenderDepth();
}

bool Bullet::isInRect(float aimx, float aimy, float r, int nextstep)
{
	bulletData * tbd = &(BResource::bres.bulletdata[type]);
	float _x = x;
	float _y = y;
	float collisionfactor = 1.0f;
	if (nextstep)
	{
		_x += xplus * nextstep;
		_y += yplus * nextstep;
		if (actionList[0] != SECTIONEND && ChangeAction(true))
		{
			collisionfactor = 1.1f;
		}
	}
	float rotCos;
	float rotSin;
	if (tbd->collisiontype ==  BULLET_COLLISION_ELLIPSE || tbd->collisiontype == BULLET_COLLISION_RECT)
	{
		if (speed)
		{
			if (!xplus && !yplus)
			{
				rotCos = cost(angle);
				rotSin = sint(angle);
			}
			else
			{
				rotCos = xplus / speed;
				rotSin = yplus / speed;
			}
		}
		else
		{
			rotCos = cost(angle);
			rotSin = sint(angle);
		}
	}
	switch (tbd->collisiontype)
	{
	case BULLET_COLLISION_NONE:
		return false;
	case BULLET_COLLISION_CIRCLE: 
		return CheckCollisionCircle(_x, _y, aimx, aimy, tbd->collisionMain * collisionfactor + r);
	case BULLET_COLLISION_SQURE: 
		return CheckCollisionSquare(_x, _y, aimx, aimy, tbd->collisionMain * collisionfactor, r);
	case BULLET_COLLISION_ELLIPSE:
		return CheckCollisionEllipse(_x, _y, aimx, aimy, tbd->collisionSub * collisionfactor, tbd->collisionMain * collisionfactor, rotCos, rotSin, r);
	case BULLET_COLLISION_RECT:
		return CheckCollisionRect(_x, _y, aimx, aimy, tbd->collisionSub * collisionfactor, tbd->collisionMain * collisionfactor, rotCos, rotSin, r);
	}
	return false;
}

bool Bullet::ChangeAction(int nextstep)
{
	bool doit = false;
	/*
	bool conbyval = true;
	bool exebyval = true;
#define _CONACL_(X)	(conbyval ? actionList[i+(X)]: Scripter::scr.GetIntValue(i+(X)))
#define _EXEACL_(X)	(exebyval ? actionList[i+(X)]: Scripter::scr.GetIntValue(i+(X)))
#define _ACL_(X)	(actionList[i+(X)])
#define _SAVECON_(X, V)	(conbyval ? actionList[i+(X)]=(V) : Scripter::scr.SetIntValue(i+(X), V))
#define _SAVEEXE_(X, V)	(exebyval ? actionList[i+(X)]=(V) : Scripter::scr.SetIntValue(i+(X), V))
	*/
	int usingtimer = timer + nextstep;
#define _CONACL_(X)	(actionList[i+(X)])
#define _EXEACL_(X)	(actionList[i+(X)])
#define _ACL_(X)	(actionList[i+(X)])
#define _SAVECON_(X, V)	(actionList[i+(X)]=(V))
#define _SAVEEXE_(X, V)	(actionList[i+(X)]=(V))
	for(int i=0;i<BULLETACTIONMAX;++i)
	{
		if (actionList[i] < BULA_SPECIALSTART)
		{
			switch (actionList[i])
			{
			case AND:
				if (!doit)
				{
					for (++i; i<BULLETACTIONMAX; ++i)
					{
						if (_ACL_(0) == THEN)
						{
							break;
						}
					}
				}
				else
				{
					doit = false;
				}
				break;
			case OR:
				if (doit)
				{
					for (++i; i<BULLETACTIONMAX; ++i)
					{
						if(_ACL_(0) == THEN)
						{
							break;
						}
					}
				}
				else
				{
					doit = false;
				}
				break;
			case NOT:
				doit = !doit;
				break;
//			case ANDSET:
//				doit = true;
//				break;
			case CONDITIONBYVAL:
//				conbyval = true;
				break;
			case CONDITIONBYINDEX:
//				conbyval = false;
				break;
			case EXECUTEBYVAL:
//				exebyval = true;
				break;
			case EXECUTEBYINDEX:
//				exebyval = false;
				break;
			}
		}
		else if (_ACL_(0) < BULA_EXECUTESTART)
		{
			switch (_ACL_(0) & BULAC_FILTER)
			{
			case BULAC_OTHER:
				switch (_ACL_(0))
				{
				case SECTIONEND:
					i = BULLETACTIONMAX-1;
					break;

				case EVERY:
					doit = true;
					break;
				case EVERYMOD:
					if(usingtimer % _CONACL_(1) == 0)
						doit = true;
					++i;
					break;
				}
				break;
			case BULAC_TIMER:
				switch (actionList[i])
				{
				case TIMERGREAT:
					if(usingtimer >= _CONACL_(1))
						doit = true;
					++i;
					break;
				case TIMEREQUAL:
					if(usingtimer == _CONACL_(1))
						doit = true;
					++i;
					break;
				case TIMERLESS:
					if(usingtimer <= _CONACL_(1))
						doit = true;
					++i;
					break;
				case TIMERRANGE:
					if(usingtimer >= _CONACL_(1) && usingtimer <= _CONACL_(2))
						doit = true;
					i+=2;
					break;
				}
				break;
			case BULAC_TYPE:
				switch (_ACL_(0))
				{
				case TYPEEQUAL:
					if(type == _CONACL_(1))
						doit = true;
					++i;
					break;
				}
				break;
			case BULAC_COLOR:
				switch (_ACL_(0))
				{
				case COLOREQUAL:
					if(color == _CONACL_(1))
						doit = true;
					++i;
					break;
				}
				break;
			case BULAC_ANGLE:
				switch (_ACL_(0))
				{
				case ANGLEGREAT:
					if(angle >= _CONACL_(1))
						doit = true;
					++i;
					break;
				case ANGLEEQUAL:
					if(angle == _CONACL_(1))
						doit = true;
					++i;
					break;
				case ANGLELESS:
					if(angle <= _CONACL_(1))
						doit = true;
					++i;
					break;
				case ANGLERANGE:
					if(angle >= _CONACL_(1) && angle <= _CONACL_(2))
						doit = true;
					i+=2;
					break;
				}
				break;
			case BULAC_POS:
				switch (_ACL_(0))
				{
				case XGREAT:
					if(x >= _CONACL_(1))
						doit = true;
					++i;
					break;
				case XLESS:
					if(x <= _CONACL_(1))
						doit = true;
					++i;
					break;
				case XRANGE:
					if(x >= _CONACL_(1) && x <= _CONACL_(2))
						doit = true;
					i+=2;
					break;
				case YGREAT:
					if(y >= _CONACL_(1))
						doit = true;
					++i;
					break;
				case YLESS:
					if(y <= _CONACL_(1))
						doit = true;
					++i;
					break;
				case YRANGE:
					if(y >= _CONACL_(1) && y <= _CONACL_(2))
						doit = true;
					i+=2;
					break;
				}
				break;
			case BULAC_VAL:
				switch (_ACL_(0))
				{
				case VALGREAT:
					if(CAST(Scripter::scr.d[(int)_CONACL_(1)]) >= _CONACL_(2))
						doit = true;
					i+=2;
					break;
				case VALEQUAL:
					if(CAST(Scripter::scr.d[(int)_CONACL_(1)]) == _CONACL_(2))
						doit = true;
					i+=2;
					break;
				case VALLESS:
					if(CAST(Scripter::scr.d[(int)_CONACL_(1)]) <= _CONACL_(2))
						doit = true;
					i+=2;
					break;
				case VALRANGE:
					if(CAST(Scripter::scr.d[(int)_CONACL_(1)]) >= _CONACL_(2) && CAST(Scripter::scr.d[(int)_CONACL_(1)]) <= _CONACL_(3))
						doit = true;
					i+=3;
					break;
				}
				break;
			case BULAC_SPEED:
				switch (_ACL_(0))
				{
				case SPEEDGREAT:
					if(speed*BULLETACT_FLOATSCALE >= _CONACL_(1))
						doit = true;
					++i;
					break;
				case SPEEDEQUAL:
					if(speed*BULLETACT_FLOATSCALE == _CONACL_(1))
						doit = true;
					++i;
					break;
				case SPEEDLESS:
					if(speed*BULLETACT_FLOATSCALE <= _CONACL_(1))
						doit = true;
					++i;
					break;
				case SPEEDRANGE:
					if(speed*BULLETACT_FLOATSCALE >= _CONACL_(1) && speed*BULLETACT_FLOATSCALE <= _CONACL_(2))
						doit = true;
					i+=2;
					break;
				}
				break;
			case BULAC_INDEX:
				switch (_ACL_(0))
				{
				case INDEXMODGREAT:
					if (index % _CONACL_(1) >= _CONACL_(2))
					{
						doit = true;
					}
					i+=2;
					break;
				case INDEXMODEQUAL:
					if (index % _CONACL_(1) == _CONACL_(2))
					{
						doit = true;
					}
					i+=2;
					break;
				case INDEXMODLESS:
					if (index % _CONACL_(1) <= _CONACL_(2))
					{
						doit = true;
					}
					i+=2;
					break;
				case INDEXMODRANGE:
					if (index % _CONACL_(1) >= _CONACL_(2) && index % _CONACL_(1) <= _CONACL_(3))
					{
						doit = true;
					}
					i+=3;
					break;
				}
				break;
			case BULAC_BOUNCE:
				switch (_ACL_(0))
				{
				case BOUNCEGREAT:
					if (bouncetime >= _CONACL_(1))
					{
						doit = true;
					}
					++i;
					break;
				case BOUNCEEQUAL:
					if (bouncetime == _CONACL_(1))
					{
						doit = true;
					}
					++i;
					break;
				case BOUNCELESS:
					if (bouncetime < _CONACL_(1))
					{
						doit = true;
					}
					++i;
					break;
				case BOUNCERANGE:
					if (bouncetime >= _CONACL_(1) && bouncetime <= _CONACL_(2))
					{
						doit = true;
					}
					i+=2;
					break;
				}
				break;
			}
		}
		else// if (!nextstep)
		{
			switch (_ACL_(0) & BULAE_FILTER)
			{
			case BULAE_TYPE:
				switch (_ACL_(0))
				{
				case TYPESET:
					if(doit)
					{
						if (oldtype != _EXEACL_(1))
						{
							oldtype = _EXEACL_(1);
							typechangetimer = 1;
							SE::push(SE_BULLET_CHANGE_2, x);
						}
					}
					++i;
					doit = false;
					break;
				}
				break;
			case BULAE_COLOR:
				switch (_ACL_(0))
				{
				case COLORSET:
					if(doit)
					{
						color = _EXEACL_(1);
						oldcolor = color;
//						SE::push(SE_BULLET_CHANGE_2, x);
					}
					++i;
					doit = false;
					break;
				}
				break;
			case BULAE_ANGLE:
				switch (_ACL_(0))
				{
				case ANGLESET:
					if(doit)
					{
						angle = _EXEACL_(1);
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					++i;
					doit = false;
					break;
				case ANGLESETADD:
					if(doit)
					{
						angle += _EXEACL_(1);
						if(_EXEACL_(1) > BULLETACT_ANGLECHANGESE || _EXEACL_(1) < -BULLETACT_ANGLECHANGESE)
							SE::push(SE_BULLET_CHANGE_1, x);
					}
					++i;
					doit = false;
					break;
				case ANGLESETRMA:
					if(doit)
					{
						angle = rMainAngle(_EXEACL_(1)*1.0f, _EXEACL_(2)*1.0f, _EXEACL_(3)*1.0f);
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					i+=3;
					doit = false;
					break;
				case ANGLESETRMAP:
					if(doit)
					{
						angle = rMainAngle(Player::p.x, Player::p.y, _EXEACL_(1)*1.0f);
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					++i;
					doit = false;
					break;
				case ANGLESETRMAT:
					if(doit)
					{
						angle = rMainAngle(Target::tar[(int)_EXEACL_(1)].x, Target::tar[(int)_EXEACL_(1)].y, _EXEACL_(2)*1.0f);
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					i+=2;
					doit = false;
					break;
				case ANGLESETAMA:
					if(doit)
					{
						angle = aMainAngle(_EXEACL_(1)*1.0f, _EXEACL_(2)*1.0f, _EXEACL_(3));
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					i+=3;
					doit = false;
					break;
				case ANGLESETAMAP:
					if(doit)
					{
						angle = aMainAngle(Player::p.x, Player::p.y, _EXEACL_(1));
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					++i;
					doit = false;
					break;
				case ANGLESETAMAT:
					if(doit)
					{
						angle = aMainAngle(Target::tar[(int)_EXEACL_(1)].x, Target::tar[(int)_EXEACL_(1)].y, _EXEACL_(2));
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					i+=2;
					doit = false;
					break;
				case ANGLESETRAND:
					if (doit)
					{
						angle = randt(_EXEACL_(1), _EXEACL_(2));
						SE::push(SE_BULLET_CHANGE_1, x);
					}
					i+=2;
					doit = false;
					break;
				case ANGLESETADDRAND:
					if (doit)
					{
						int addangle = randt(_EXEACL_(1), _EXEACL_(2));
						angle += addangle;
						if(addangle > BULLETACT_ANGLECHANGESE || addangle < -BULLETACT_ANGLECHANGESE)
							SE::push(SE_BULLET_CHANGE_1, x);
					}
					i+=2;
					doit = false;
					break;
				case ANGLEADJUST:
					if(doit)
						angle = aMainAngle(lastx, lasty) + 18000;
					doit = false;
					break;
				}
				break;
			case BULAE_HEADANGLE:
				switch (_ACL_(0))
				{
				case HEADANGLESET:
					if(doit)
						headangle = _EXEACL_(1);
					++i;
					doit = false;
					break;
				case HEADANGLESETADD:
					if(doit)
						headangle += _EXEACL_(1);
					++i;
					doit = false;
					break;
				}
				break;
			case BULAE_POS:
				switch (_ACL_(0))
				{
				case XSET:
					if(doit)
					{
						x = (float)_EXEACL_(1);
						SE::push(SE_BULLET_CHANGE_2, x);
					}
					++i;
					doit = false;
					break;
				case YSET:
					if(doit)
					{
						y = (float)_EXEACL_(1);
						SE::push(SE_BULLET_CHANGE_2, x);
					}
					++i;
					doit = false;
					break;
				case XSETADD:
					if(doit)
						x += _EXEACL_(1)/BULLETACT_FLOATSCALE;
					++i;
					doit = false;
					break;
				case YSETADD:
					if(doit)
						y += _EXEACL_(1)/BULLETACT_FLOATSCALE;
					++i;
					doit = false;
					break;
				case XSETACCADD:
					if(doit && usingtimer > (DWORD)_EXEACL_(1))
						x += (int)(usingtimer - _EXEACL_(1)) * _EXEACL_(2)/BULLETACT_FLOATSCALE;
					i+=2;
					doit = false;
					break;
				case YSETACCADD:
					if(doit && usingtimer > (DWORD)_EXEACL_(1))
						y += (int)(usingtimer - _EXEACL_(1)) * _EXEACL_(2)/BULLETACT_FLOATSCALE;
					i+=2;
					doit = false;
					break;
				}
				break;
			case BULAE_SPEED:
				switch (_ACL_(0))
				{
				case SPEEDSET:
					if(doit)
					{
						if (speed == 0)
						{
							SE::push(SE_BULLET_CHANGE_1, x);
						}
						speed = _EXEACL_(1)/BULLETACT_FLOATSCALE;
					}
					++i;
					doit = false;
					break;
				case SPEEDSETADD:
					if(doit)
					{
						if(speed == 0)
							SE::push(SE_BULLET_CHANGE_2, x);
						speed += _EXEACL_(1)/BULLETACT_FLOATSCALE;
					}
					++i;
					doit = false;
					break;
				case SPEEDSETMUL:
					if(doit)
					{
						speed *= _EXEACL_(1)/BULLETACT_FLOATSCALE;
					}
					++i;
					doit = false;
					break;
				}
				break;
			case BULAE_VAL:
				switch (_ACL_(0))
				{
				case VALSET:
					if(doit)
					{
						Scripter::scr.SetIntValue(_EXEACL_(1), _EXEACL_(2));
						Scripter::scr.d[(int)_EXEACL_(1)].bfloat = false;
					}
					i+=2;
					doit = false;
					break;
				case VALSETADD:
					if(doit)
					{
						Scripter::scr.SetIntValue(_EXEACL_(1), Scripter::scr.GetIntValue(_EXEACL_(1))+_EXEACL_(2));
						Scripter::scr.d[(int)_EXEACL_(1)].bfloat = false;
					}
					i+=2;
					doit = false;
					break;
				}
				break;
			case BULAE_OTHER:
				switch (_ACL_(0))
				{
				case CALLEVENT:
					if (doit)
					{
						Scripter::scr.Execute(SCR_EVENT, _EXEACL_(1), _EXEACL_(2));
					}
					i+=2;
					doit = false;
					break;
				case CHASE:
					if (doit)
					{
						_SAVEEXE_(2, chaseAim(Target::tar[(int)_EXEACL_(1)].x, Target::tar[(int)_EXEACL_(1)].y, _EXEACL_(2)));
					}
					i+=2;
					doit = false;
					break;

				case REMAIN:
					if(doit)
					{
						remain = true;
					}
					break;
				case DECANCEL:
					if (doit)
					{
						cancelable = false;
					}
					break;
				case FADEOUT:
					if(doit)
					{
						fadeout = true;
						timer = 0;
					}
					break;
				case BULLETDIE:
					if (doit)
					{
						DoDead();
					}
					break;
				case BOUNCE:
					if (doit)
					{
						if (bouncetime < _EXEACL_(2))
						{
							if (x < M_GAMESQUARE_LEFT + _EXEACL_(1) || x > M_GAMESQUARE_RIGHT - _EXEACL_(1))
							{
//								_SAVEEXE_(2, _EXEACL_(2)-1);
								bouncetime++;
								SE::push(SE_BULLET_CHANGE_2, x);
								angle = 18000 - angle;
							}
							if (y < M_GAMESQUARE_TOP + _EXEACL_(1) || y > M_GAMESQUARE_BOTTOM - _EXEACL_(1))
							{
//								_SAVEEXE_(2, _EXEACL_(2)-1);
								bouncetime++;
								SE::push(SE_BULLET_CHANGE_2, x);
								angle = -angle;
							}
						}
					}
					i+=2;
					doit = false;
					break;
				case BOUNCELR:
					if (doit)
					{
						if (bouncetime < _EXEACL_(2))
						{
							if (x < M_GAMESQUARE_LEFT + _EXEACL_(1) || x > M_GAMESQUARE_RIGHT - _EXEACL_(1))
							{
//								_SAVEEXE_(2, _EXEACL_(2)-1);
								bouncetime++;
								SE::push(SE_BULLET_CHANGE_2, x);
								angle = 18000 - angle;
							}
						}
					}
					i+=2;
					doit = false;
					break;
				case BOUNCETB:
					if (doit)
					{
						if (bouncetime < _EXEACL_(2))
						{
							if (y < M_GAMESQUARE_TOP + _EXEACL_(1) || y > M_GAMESQUARE_BOTTOM - _EXEACL_(1))
							{
//								_SAVEEXE_(2, _EXEACL_(2)-1);
								bouncetime++;
								SE::push(SE_BULLET_CHANGE_2, x);
								angle = -angle;
							}
						}
					}
					i+=2;
					doit = false;
					break;
				}
				break;
			}
		}
		if (nextstep)
		{
			if (doit)
			{
				return true;
			}
		}
	}
	return false;
}
