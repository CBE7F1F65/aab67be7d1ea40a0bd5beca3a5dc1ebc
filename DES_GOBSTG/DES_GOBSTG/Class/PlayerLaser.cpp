#include "../Header/PlayerLaser.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/Player.h"
#include "../Header/ProcessDefine.h"
#include "../Header/Process.h"
#include "../Header/BResource.h"

#define PLAYERLASER_LASERYOFFSET	-32
#define PLAYERLASER_LASERHEADYSPEED	-16.0f
#define PLAYERLASER_LASERYSPEED		-12.0f

#define PLAYERLASER_LASERHEADYMAX	-64

#define PLAYERLASER_ANIMATIONINTERVAL	4

#define PLAYERLASER_BODYTILELENGTH	16.0f

#define PLAYERLASER_HITFLAG_NULL	0x00
#define PLAYERLASER_HITFLAG_BODY	0x01
#define PLAYERLASER_HITFLAG_PROTECT	0x02

#define PLAYERLASER_STOPPLUS	40

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

int PlayerLaser::GetIndex(bool invert)
{
	int indexn = Player::p.ID;
	int indexh = indexn + DATASTRUCT_PLAYERTYPEMAX;
	int retval = indexn;
	if (Player::p.bhyper ^ invert)
	{
		retval = indexh;
	}
	return retval;
}

void PlayerLaser::Action()
{
	DWORD stopflag = Process::mp.GetStopFlag();
	bool binstop = FRAME_STOPFLAGCHECK_(stopflag, FRAME_STOPFLAG_PLAYERBULLET);
	if (!binstop)
	{
		plaser[GetIndex()].action();
	}
}

void PlayerLaser::action()
{
	if (bshooting)
	{
		timer++;
		if (!bstopped)
		{
			stoptimer = 0;
			headypos += PLAYERLASER_LASERHEADYSPEED;
			if (headypos < PLAYERLASER_LASERHEADYMAX)
			{
				headypos = PLAYERLASER_LASERHEADYMAX;
			}
		}
		else
		{
			stoptimer++;
			if (stoptimer >= PLAYERLASER_STOPPLUS)
			{
				Player::p.AddComboHit(1);
				stoptimer = 0;
			}
		}
	}
}

void PlayerLaser::RenderAll()
{
	plaser[GetIndex()].render();
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
			SpriteItemManager::RenderSpriteEx(spbody[nowtileID], px, ystart-i*PLAYERLASER_BODYTILELENGTH-yoffset, ARC(-9000));
		}

		//
		BYTE animation = (timer / PLAYERLASER_ANIMATIONINTERVAL)%PLAYERLASER_ANIMATIONMAX;
		SpriteItemManager::RenderSprite(spprotect[animation], px, py);
		SpriteItemManager::RenderSprite(spbegin[animation], px, py+PLAYERLASER_LASERYOFFSET);


		if (!bstopped)
		{
			BYTE headanimation = animation;
			if (timer >= PLAYERLASER_ANIMATIONINTERVAL*PLAYERLASER_ANIMATIONMAX)
			{
				headanimation = headanimation%(PLAYERLASER_ANIMATIONMAX/2)+(PLAYERLASER_ANIMATIONMAX/2);
			}
			SpriteItemManager::RenderSprite(sphead[headanimation], px, headypos);
		}
		else
		{
			SpriteItemManager::RenderSprite(spstop[animation], px, headypos);
		}
	}
}

bool PlayerLaser::CheckShoot(Enemy * en, float aimx, float aimy, float aimw, float aimh/* =0.0f */)
{
	int index = GetIndex();
	return plaser[index].checkshoot(index, en, aimx, aimy, aimw, aimh);
}

bool PlayerLaser::checkshoot(int index, Enemy * en, float aimx, float aimy, float aimw, float aimh/* =0.0f */)
{
	if (!bshooting)
	{
		return false;
	}

	BYTE hitflag = isInRange(aimx, aimy, aimw, aimh);
	if (hitflag)
	{
		playerlaserData * pldata = &(BResource::bres.playerlaserdata[index]);
		float power = pldata->power;
		bool hitprotect = false;
		if (hitflag & PLAYERLASER_HITFLAG_PROTECT)
		{
			hitprotect = true;
			power *= pldata->protectpowermul;
			// Play Effect
		}
		Player::p.DoPlayerLaserHit(en->type, hitprotect);
		if (en->CostLife(power))
		{
			Player::p.DoPlayerLaserKill(en->type);
		}
		else if (hitflag & PLAYERLASER_HITFLAG_BODY)
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
	float useheadypos = headypos;
	if (useheadypos < 0)
	{
		useheadypos = 0;
	}
	if (useheadypos > Player::p.y+PLAYERLASER_LASERYOFFSET)
	{
		useheadypos = Player::p.y+PLAYERLASER_LASERYOFFSET;
	}
	float oHeight = ((_bobj.y+PLAYERLASER_LASERYOFFSET)-useheadypos)/2;
	_bobj.y -= oHeight-PLAYERLASER_LASERYOFFSET;
	if (_bobj.checkCollisionRightRect(aimx, aimy, w, h, pldata->width, oHeight+1))
	{
		ret |= PLAYERLASER_HITFLAG_BODY;
	}
	return ret;
}

void PlayerLaser::Shoot()
{
	plaser[GetIndex()].shoot();
	plaser[GetIndex(true)].stopfire();
}

void PlayerLaser::StopFire()
{
	plaser[GetIndex()].stopfire();
	plaser[GetIndex(true)].stopfire();
}

void PlayerLaser::ClearStop()
{
	plaser[GetIndex()].bstopped = false;
	plaser[GetIndex(true)].bstopped = false;
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
//		spbody[i]->SetBlendMode(BLEND_ALPHAADD);
		++siid;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::CreateSprite(siid, &(spprotect[i]));
//		spprotect[i]->SetBlendMode(BLEND_ALPHAADD);
		++siid;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::CreateSprite(siid, &(sphead[i]));
//		sphead[i]->SetBlendMode(BLEND_ALPHAADD);
		++siid;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::CreateSprite(siid, &(spbegin[i]));
//		spbegin[i]->SetBlendMode(BLEND_ALPHAADD);
		++siid;
	}
	for (int i=0; i<PLAYERLASER_ANIMATIONMAX; i++)
	{
		SpriteItemManager::CreateSprite(siid, &(spstop[i]));
//		spstop[i]->SetBlendMode(BLEND_ALPHAADD);
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