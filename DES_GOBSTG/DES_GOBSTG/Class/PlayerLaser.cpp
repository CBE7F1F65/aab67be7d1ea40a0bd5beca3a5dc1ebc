#include "../Header/PlayerLaser.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/Player.h"
#include "../Header/ProcessDefine.h"
#include "../Header/Process.h"
#include "../Header/BResource.h"

#define PLAYERLASER_LASERYOFFSET	-32
#define PLAYERLASER_LASERHEADYSPEED	-16.0f
#define PLAYERLASER_LASERYSPEED		-12.0f

#define PLAYERLASER_ANIMATIONINTERVAL	4

#define PLAYERLASER_BODYTILELENGTH	16.0f

#define PLAYERLASER_HITFLAG_NULL	0x00
#define PLAYERLASER_HITFLAG_BODY	0x01
#define PLAYERLASER_HITFLAG_PROTECT	0x02

PlayerLaser PlayerLaser::plaser[DATASTRUCT_PLAYERLASERTYPEMAX];

PlayerLaser::PlayerLaser()
{
	for (int i=0; i<PLAYERLASER_BODYMAX; i++)
	{
		spbody[i] = NULL;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		spprotect[i] = NULL;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		sphead[i] = NULL;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		spbegin[i] = NULL;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		spstop[i] = NULL;
	}
}

PlayerLaser::~PlayerLaser()
{
	Release();
}

void PlayerLaser::Init()
{
	for (int i=0; i<DATASTRUCT_PLAYERLASERTYPEMAX; i++)
	{
		plaser[i].init(i);
	}
}

void PlayerLaser::Action()
{
	DWORD stopflag = Process::mp.GetStopFlag();
	bool binstop = FRAME_STOPFLAGCHECK_(stopflag, FRAME_STOPFLAG_PLAYERBULLET);
	if (!binstop)
	{
		plaser[Player::p.ID].action();
	}
}

void PlayerLaser::action()
{
	if (bshooting)
	{
		timer++;
		if (!bstopped)
		{
			headypos += PLAYERLASER_LASERHEADYSPEED;
		}
	}
}

void PlayerLaser::RenderAll()
{
	plaser[Player::p.ID].render();
}

void PlayerLaser::render()
{
	if (bshooting)
	{
		float px = Player::p.x;
		float py = Player::p.y;
		if (headypos > py+PLAYERLASER_LASERYOFFSET)
		{
			headypos = py+PLAYERLASER_LASERYOFFSET;
		}
		// Render Body

		float ystart = py + PLAYERLASER_LASERYOFFSET;
		float yend = headypos;
		int tilecount = (int)((ystart-yend)/PLAYERLASER_BODYTILELENGTH+0.5f);
		float ypostemp = timer*(-PLAYERLASER_LASERYSPEED);
		int begintileID = PLAYERLASER_BODYMAX-((int)((ypostemp/PLAYERLASER_BODYTILELENGTH)))%PLAYERLASER_BODYMAX-1;
		float yoffset = ypostemp - ((int)(ypostemp))/((int)PLAYERLASER_BODYTILELENGTH)*((int)PLAYERLASER_BODYTILELENGTH);

		for (int i=0; i<tilecount; i++)
		{
			int nowtileID = (begintileID+i)%PLAYERLASER_BODYMAX;
			spbody[nowtileID]->RenderEx(px, ystart-i*PLAYERLASER_BODYTILELENGTH-yoffset, ARC(-9000));
		}

		//
		BYTE animation = (timer / PLAYERLASER_ANIMATIONINTERVAL)%PLAYERLASER_ANIMATIONMAX;
		spprotect[animation]->Render(px, py);
		spbegin[animation]->Render(px, py+PLAYERLASER_LASERYOFFSET);


		if (!bstopped)
		{
			BYTE headanimation = animation;
			if (timer >= PLAYERLASER_ANIMATIONINTERVAL*PLAYERLASER_ANIMATIONMAX)
			{
				headanimation = headanimation%(PLAYERLASER_ANIMATIONMAX/2)+(PLAYERLASER_ANIMATIONMAX/2);
			}
			sphead[headanimation]->Render(px, headypos);
		}
		else
		{
			sphead[animation]->Render(px, headypos);
		}
		bstopped = false;
	}
}

bool PlayerLaser::CheckShoot(Enemy * en, float aimx, float aimy, float aimw, float aimh/* =0.0f */)
{
	return plaser[Player::p.ID].checkshoot(en, aimx, aimy, aimw, aimh);
}

bool PlayerLaser::checkshoot(Enemy * en, float aimx, float aimy, float aimw, float aimh/* =0.0f */)
{
	if (!bshooting)
	{
		return false;
	}

	BYTE hitflag = isInRange(aimx, aimy, aimw, aimh);
	if (hitflag)
	{
		playerlaserData * pldata = &(BResource::bres.playerlaserdata[Player::p.ID]);
		float power = pldata->power;
		bool hitprotect = false;
		if (hitflag & PLAYERLASER_HITFLAG_PROTECT)
		{
			hitprotect = true;
			power *= pldata->protectpowermul;
			// Play Effect
		}
		Player::p.DoPlayerLaserHit(hitprotect);
		if (en->CostLife(power))
		{
			Player::p.DoPlayerLaserKill();
		}
		else
		{
			hitOn(en->y+aimh);
		}
	}

	return false;
}

void PlayerLaser::hitOn(float ypos)
{
	headypos = ypos;
	bstopped = true;
}

BYTE PlayerLaser::isInRange(float aimx, float aimy, float w, float h/* =0.0f */)
{
	BYTE ret = PLAYERLASER_HITFLAG_NULL;
	playerlaserData * pldata = &(BResource::bres.playerlaserdata[Player::p.ID]);
	BObject _bobj;
	_bobj.x = Player::p.x;
	_bobj.y = Player::p.y;
	if (_bobj.checkCollisionRightRect(aimx, aimy, w, h, pldata->protectwidth, pldata->protectheight))
	{
		ret |= PLAYERLASER_HITFLAG_PROTECT;
	}
	float oHeight = ((_bobj.y+PLAYERLASER_LASERYOFFSET)-headypos)/2;
	_bobj.y -= oHeight;
	if (_bobj.checkCollisionRightRect(aimx, aimy, w, h, pldata->width, oHeight))
	{
		ret |= PLAYERLASER_HITFLAG_BODY;
	}
	return ret;
}

void PlayerLaser::Shoot()
{
	plaser[Player::p.ID].shoot();
}

void PlayerLaser::StopFire()
{
	plaser[Player::p.ID].stopfire();
}

void PlayerLaser::shoot()
{
	bstopped = false;
	bshooting = true;
	timer = 0;
	headypos = Player::p.y+PLAYERLASER_LASERYOFFSET;
}

void PlayerLaser::stopfire()
{
	bstopped = false;
	bshooting = false;
	timer = 0;
	headypos = 0;
}

void PlayerLaser::init(int playerID)
{
	Release();

	int siid = BResource::bres.playerlaserdata[playerID].siid;
	for (int i=0; i<PLAYERLASER_BODYMAX; i++)
	{
		SpriteItemManager::CreateSprite(siid, &(spbody[i]));
		++siid;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::CreateSprite(siid, &(spprotect[i]));
		++siid;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::CreateSprite(siid, &(sphead[i]));
		++siid;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::CreateSprite(siid, &(spbegin[i]));
		++siid;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::CreateSprite(siid, &(spstop[i]));
		++siid;
	}
}

void PlayerLaser::Release()
{
	timer = 0;

	bstopped = false;
	headypos = 0;

	for (int i=0; i<PLAYERLASER_BODYMAX; i++)
	{
		SpriteItemManager::FreeSprite(&(spbody[i]));
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::FreeSprite(&(spprotect[i]));
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::FreeSprite(&(sphead[i]));
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::FreeSprite(&(spbegin[i]));
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::FreeSprite(&(spstop[i]));
	}
}