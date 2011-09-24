/*

#include "../header/Ghost.h"
#include "../header/Player.h"
#include "../header/Enemy.h"
#include "../header/Item.h"
#include "../header/SE.h"
#include "../header/Bullet.h"
#include "../header/Scripter.h"
#include "../header/Chat.h"
#include "../header/BossInfo.h"
#include "../header/Main.h"
#include "../header/EffectIDDefine.h"
#include "../header/EventZone.h"

Ghost Ghost::gh[GHOSTMAX];

WORD Ghost::index;

#define PB_SHOOTGHOST_ENEMYCOST 0.25f

Ghost::Ghost()
{
	able			= false;
	effghost.exist	= false;
	gID				= 0;
}

Ghost::~Ghost()
{
}

bool Ghost::Build(WORD _gID, BYTE _tarID, BYTE _belong, float x, float y, int angle, float speed, BYTE type, float life, int ac)
{
	bool rv = false;
	for(int i=0;i<GHOSTMAX;i++)
	{
		index++;
		if(index == GHOSTMAX)
		{
			index = 0;
		}
		if(!gh[index].exist)
		{
			rv = true;
			break;
		}
	}
	if(!rv)
		return false;
	gh[index].gID = _gID;
	gh[index].valueSet(index, x, y, angle, speed, type, life, ac);
	gh[index].belong = _belong;
	gh[index].tarID = _tarID;

	return true;
}

void Ghost::valueSet(WORD _ID, float _x, float _y, int _angle, float _speed, BYTE _type, float _life, int _ac)
{
	ID		=	_ID;
	x		=	_x;
	y		=	_y;
	speed	=	_speed;
	type	=	_type;
	life	=	_life;
	ac		=	_ac;
	angle	=	_angle;

	tarID	=	0xff;

	timer	=	0;
	cenx	=	x;
	ceny	=	y;
	maxlife	=	life;
	exist	=	true;
	fadeout	=	false;
	able	=	true;
	damage	=	false;
	half	=	false;
	gave	=	false;
	hscale	=	1.0f;
	vscale	=	1.0f;
	headangle =	0;
	alpha	=	0xff;
	belong	=	0xff;

	aim.x	=	0;
	aim.y	=	0;

	// TODO:
	effghost.valueSet(EFF_GH_TYPEBEGIN + type, M_RENDER_LEFT, *this);

	effghost.Fire();
}

void Ghost::CostLife(float power)
{
	life -= power;
	if (life < 0)
	{
		life = maxlife / 4;
	}
	damage = true;
	if (belong < ENEMYMAX)
	{
		Enemy::en[getPlayerIndex()][belong].CostLife(power * PB_SHOOTGHOST_ENEMYCOST);
	}
}

void Ghost::valueSet(WORD ID, BYTE _belong, int angle, float speed, BYTE type, float life, int ac)
{
	valueSet(ID, Enemy::en[getPlayerIndex()][_belong].x, Enemy::en[getPlayerIndex()][_belong].y,angle, speed, type, life, ac);
	belong = _belong;
}

void Ghost::Render()
{
	effghost.Render();
}

void Ghost::actionInStop()
{
	BYTE playerindex = getPlayerIndex();
	if (!fadeout && !half)
	{
		DoShot(playerindex);
	}
}

void Ghost::SendGhost(BYTE playerindex, float x, float y, bool bythis/ * =true * /)
{
	// TODO:
}

BYTE Ghost::getPlayerIndex()
{
	if (ID >= GHID_LEFTIDBEGIN && ID < GHID_LEFTIDUNTIL)
	{
		return 0;
	}
	else if (ID >= GHID_RIGHTIDBEGIN && ID < GHID_RIGHTIDUNTIL)
	{
		return 1;
	}
	return 0;
}

void Ghost::DoShot(BYTE playerindex)
{
	float costpower = PlayerBullet::CheckShoot(playerindex, x, y, 32);
	if (costpower)
	{
		CostLife(costpower);
	}

	for (list<EventZone>::iterator it=EventZone::ezone[playerindex].begin(); it!=EventZone::ezone[playerindex].end(); it++)
	{
		if (it->type & EVENTZONE_TYPE_ENEMYDAMAGE)
		{
			if (checkCollisionCircle(it->x, it->y, it->r))
			{
				CostLife(it->power);
				// TODO:
				Player::p[playerindex].DoPlayerBulletHit();
			}
		}
	}
}

void Ghost::ClearAll()
{
	for (int i=0; i<GHOSTMAX; i++)
	{
		gh[i].Clear();
	}
	index = 0;
}

void Ghost::Clear()
{
	exist = false;
	able = false;
	timer = 0;
}

void Ghost::Action(bool notinstop)
{
	for (int i=0; i<GHOSTMAX; i++)
	{
		if (gh[i].exist)
		{
			if (notinstop)
			{
				gh[i].action();
			}
			else
			{
				gh[i].actionInStop();
			}
		}
	}
}

void Ghost::RenderAll(BYTE renderflag)
{
	if (renderflag == M_RENDER_LEFT)
	{
		for (int i=GHID_LEFTIDBEGIN; i<GHID_LEFTIDUNTIL; i++)
		{
			if (gh[i].exist)
			{
				gh[i].Render();
			}
		}
	}
	else if (renderflag == M_RENDER_RIGHT)
	{
		for (int i=GHID_RIGHTIDBEGIN; i<GHID_RIGHTIDUNTIL; i++)
		{
			if (gh[i].exist)
			{
				gh[i].Render();
			}
		}
	}
}

void Ghost::action()
{
	timer++;

	BYTE playerindex = getPlayerIndex();
	if(life < maxlife / 2 && life > 0)
	{
		if (!half)
		{
			SE::push(SE_GHOST_HALF, x);
			half = true;
		}
	}

	if(!fadeout && !gave && half)
	{
		Item::Build(playerindex, ITEM_FAITH, x, y, true);

		gave = true;
	}

	if(!fadeout)
	{
		if(timer == 1)
		{
			SE::push(SE_GHOST_MERGE, x);
		}

		if(Chat::chatitem.IsChatting() || BossInfo::flag >= BOSSINFO_COLLAPSE)
		{
			life = 0;
			fadeout = true;
			timer = 0;
		}

		if(gID && !Scripter::stopEdefScript)
		{
			WORD tindex = index;
			index = ID;
			scr.Execute(SCR_EDEF, gID, timer);
			index = tindex;
		}

		if (checkCollisionSquare(Player::p[playerindex], GHOST_COLLISIONR))
		{
			Player::p[playerindex].DoShot();
		}
		DoShot(playerindex);

		if(belong != 0xff)
		{
			if(Enemy::en[getPlayerIndex()][belong].exist)
			{
				cenx = Enemy::en[getPlayerIndex()][belong].x;
				ceny = Enemy::en[getPlayerIndex()][belong].y;
			}
			else
			{
				if(Enemy::en[getPlayerIndex()][belong].life >= 0)
				{
					life = 0;
				}
				timer = 0;
				fadeout = true;
			}
		}

		if(life < 0)
		{
			WORD tindex = index;
			index = ID;
			scr.Execute(SCR_EDEF, gID, SCRIPT_CON_POST);
			index = tindex;

			if (life < 0)
			{
				fadeout = true;
				timer = 0;
			}
		}
		else if(ac && belong != 0xff)
		{
			angle += ANGLE(speed / ac);

			float tr2 = DIST2(x, y, cenx, ceny);
			float trac2 = ac * ac;
			float tac = fabsf(ac);
			float trac = tac;
			if(tr2 < trac2)
			{
				trac = sqrtf(tr2) + fabsf(speed);
				if(trac > tac)
					trac = tac;
			}
			else if(tr2 > trac2)
			{
				trac = sqrtf(tr2) - fabsf(speed);
				if(trac < tac)
					trac = tac;
			}
			if(ac < 0)
				trac = -trac;

			x = cenx + trac * cost(angle);
			y = ceny + trac * sint(angle);
		}
		else
		{
			updateMove();
		}

		if(tarID != 0xff)
		{
			Target::SetValue(tarID, x, y);
		}

		effghost.MoveTo(x, y);
		effghost.action();

		if(belong == 0xff)
		{
			if(timer > (DWORD)ac)
			{
				life = 0;
				fadeout = true;
				timer = 0;
			}
		}
	}
	else
	{
		effghost.action();
		if(timer == 32)
		{
			effghost.Stop();
			exist = false;
		}
	}

	damage = false;
	able = exist && !fadeout;
}*/
