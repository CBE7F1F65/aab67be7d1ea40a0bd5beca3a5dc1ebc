#include "../Header/PlayerGhost.h"
#include "../Header/Player.h"
#include "../Header/Main.h"
#include "../Header/Process.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/BResource.h"
#include "../Header/GameInput.h"

#define _PLAYERGHOST_ADJUSTTIME	0x10
#define _PLAYERGHOST_LASTINDEX	0

#define _PLAYERGHOST_TRACEEDGEANGLE	200

PlayerGhost::PlayerGhost()
{
	sprite	= NULL;
}

PlayerGhost::~PlayerGhost()
{
	if(sprite)
		SpriteItemManager::FreeSprite(&sprite);
	sprite = NULL;
}

void PlayerGhost::valueSet(WORD _ID, bool move)
{
	ID		=	_ID;

	timer	=	0;
	headangle =	0;
	alpha	=	0xff;
	diffuse	=	0xffffff;
	scale	=	1.0f;
	yshake	=	0.0f;
	lastchasing	=	false;
	active = true;

	playersubData * _pgd = &(BResource::bres.playersubdata[ID]);

	if (_pgd->siid)
	{
		exist	=	true;
	}
	else
	{
		exist = false;
		return;
	}
	
	speed	=	0;
	flag	=	_pgd->flag;
	angle	=	_pgd->startangle;
	if (!(flag & PGFLAG_REMAINSHOOTANGLE))
	{
		shootangle	=	_pgd->shootangle;
	}

	if (move)
	{
		x = PL_MERGEPOS_X;
		y = PL_MERGEPOS_Y;
	}

	if(!sprite)
	{
		sprite = SpriteItemManager::CreateSprite(_pgd->siid);
	}
	else
	{
		SpriteItemManager::ChangeSprite(_pgd->siid, sprite);
	}
}

void PlayerGhost::Render()
{
	if (active && sprite)
	{
		sprite->SetColor((alpha<<24)|diffuse);
		SpriteItemManager::RenderSpriteEx(sprite, x, y, ARC(headangle), scale);
	}
}

void PlayerGhost::AntiShooter(float aimx, float aimy)
{
	while(shootangle >= 27000)
		shootangle -=36000;
	while(shootangle < -9000)
		shootangle += 36000;
	if(aimx == x)
	{
		if(GameInput::GetKey(KSI_UP) && shootangle != 9000)
		{
			if(shootangle > 9000)
			{
				shootangle -= _PLAYERGHOST_TRACEEDGEANGLE;
				if(shootangle < 9000)
					shootangle = 9000;
			}
			else if(shootangle < 9000)
			{
				shootangle += _PLAYERGHOST_TRACEEDGEANGLE;
				if(shootangle > 9000)
					shootangle = 9000;
			}
		}
		if(GameInput::GetKey(KSI_DOWN) && shootangle != -9000)
		{
			if(shootangle < 9000)
			{
				shootangle -= _PLAYERGHOST_TRACEEDGEANGLE;
				if(shootangle < -9000)
					shootangle = -9000;
			}
			else if(shootangle > 9000)
			{
				shootangle += _PLAYERGHOST_TRACEEDGEANGLE;
				if(shootangle > 27000)
					shootangle = -9000;
			}
		}
	}
	while(shootangle >= 18000)
		shootangle -= 36000;
	while(shootangle < -18000)
		shootangle += 36000;
	if(aimy == y)
	{
		if(GameInput::GetKey(KSI_LEFT) && shootangle != 0)
		{
			if(shootangle < 0)
			{
				shootangle += _PLAYERGHOST_TRACEEDGEANGLE;
				if(shootangle > 0)
					shootangle = 0;
			}
			else if(shootangle > 0)
			{
				shootangle -= _PLAYERGHOST_TRACEEDGEANGLE;
				if(shootangle < 0)
					shootangle = 0;
			}
		}
		if(GameInput::GetKey(KSI_RIGHT) && shootangle != 18000)
		{
			if(shootangle > 0)
			{
				shootangle += _PLAYERGHOST_TRACEEDGEANGLE;
				if(shootangle > 18000)
					shootangle = 18000;
			}
			else if(shootangle < 0)
			{
				shootangle -= _PLAYERGHOST_TRACEEDGEANGLE;
				if(shootangle < -18000)
					shootangle = 18000;
			}
		}
	}
	if((aimx != x || aimy != y) || timer < _PLAYERGHOST_ADJUSTTIME)
		shootangle = aMainAngle(Player::p.x, Player::p.y, 18000);
}

void PlayerGhost::action()
{
	timer++;

	if (flag & PGFLAG_ACTIVEWHENCHARGE)
	{
		active = true;
	}

	float aimx = x;
	float aimy = y;

	int chasetime = 2;
	bool chasing = false;
	bool shooting = Player::p.flag & PLAYER_SHOOT;

	DWORD ownertimer = Player::p.timer;

	playersubData * _pgd = &(BResource::bres.playersubdata[ID]);

	if (flag & PGFLAG_TRACE)
	{
		int _tindex = (ID%DATASTRUCT_PLAYERSUBMAX+1)*8-1;
		aimx = Player::p.lastmx[_tindex];
		aimy = Player::p.lastmy[_tindex];
	}

	if (flag & PGFLAG_CHASE)
	{
		chasetime = 8;
		BObject * _tpbobj;
		if (PlayerBullet::GetLockAim(&_tpbobj) && (shooting))
		{
			aimx = _tpbobj->x - _pgd->xadj;
			aimy = _tpbobj->y - _pgd->yadj;
			shootangle = _tpbobj->aMainAngle(x, y, -9000);
			chasing = true;
		}
		else
		{
			aimx = Player::p.lastx[_PLAYERGHOST_LASTINDEX] + _pgd->xadj;
			aimy = Player::p.lasty[_PLAYERGHOST_LASTINDEX] + _pgd->yadj;
		}
	}
	if (chasing != lastchasing)
	{
		timer = 0;
	}

	if (flag & PGFLAG_ABSSTAY)
	{
		aimx = M_GAMESQUARE_CENTER_X + _pgd->xadj;
		aimy = M_GAMESQUARE_CENTER_Y + _pgd->yadj;
	}

	if (!(flag & PGFLAG_SELFMOVEMASK))
	{
		aimx = Player::p.lastx[_PLAYERGHOST_LASTINDEX];
		aimy = Player::p.lasty[_PLAYERGHOST_LASTINDEX];
	}

	if (_pgd->mover)
	{
		int tangle = _pgd->speed * 100 * ownertimer + _pgd->startangle;
		if (flag & PGFLAG_NEGATIVE)
		{
			tangle = 36000 - tangle;
		}
		float txoffset = cost(tangle) * _pgd->mover;
		float tyoffset = sint(tangle) * _pgd->mover;
		aimx += txoffset;
		aimy += tyoffset;
	}

	if (!(flag & PGFLAG_ABSSTAY) && !(flag & PGFLAG_STAY) && !(flag & PGFLAG_CHASE))
	{
		aimx += _pgd->xadj;
		aimy += _pgd->yadj;
	}


	if(flag & PGFLAG_ANTISHOOTER)
	{
		if (flag & PGFLAG_STAY)
		{
			shootangle = aMainAngle(Player::p.x, Player::p.y, 18000);
		}
		else
		{
			AntiShooter(aimx, aimy);
		}
	}

	if (flag & PGFLAG_ROLL)
	{
		int troll = (ROLL(ownertimer, (_pgd->rolltime)*2)-_pgd->rolltime)*_pgd->shootangle;
		if (flag & PGFLAG_NEGATIVE)
		{
			shootangle = troll;
		}
		else
		{
			shootangle = troll;
		}
	}

	if (timer < _PLAYERGHOST_ADJUSTTIME)
	{
		chasetime = _PLAYERGHOST_ADJUSTTIME - timer;
	}

	bool stay = (flag & PGFLAG_STAYWHENCHARGE);

	if (aimx != x || aimy != y)
	{
		if (!stay)
		{
			chaseAim(aimx, aimy, chasetime);
			updateMove();
		}
		else
		{
			timer = 0;
		}
	}
	if (flag & PGFLAG_STANDSHAKE)
	{
		yshake = sint(ownertimer*512)*4.8f-2.4f;
	}
	else
	{
		yshake = 0;
	}
	if (flag & PGFLAG_SCALESHAKE)
	{
		scale = ROLL(ownertimer, 10)/20.0f+0.8f;
	}

	if (flag & PGFLAG_TURN)
	{
		if (flag & PGFLAG_NEGATIVE)
		{
			headangle = -1;
		}
		else
		{
			headangle = 1;
		}
		headangle *= ownertimer * 1000;
	}
	else
	{
		headangle = 0;
	}

	SpriteItemManager::SetSprite(_pgd->siid, sprite);
	if (flag & PGFLAG_SYNCPLAYER)
	{
		int siidoffset = Player::p.nowframeindex;
		if (stay)
		{
			siidoffset = 0;
		}
		SpriteItemManager::ChangeSprite(_pgd->siid+siidoffset, sprite);
		SpriteItemManager::SetSpriteFlip(sprite, Player::p.flipx);
	}
	lastchasing = chasing;
	sprite->SetBlendMode(_pgd->blend);
	float hotx = sprite->GetWidth()/2;
	float hoty = sprite->GetHeight()/2;
	if (headangle && yshake)
	{
		hotx += yshake * sint(headangle);
		hoty += yshake * cost(headangle);
	}
	else
	{
		hoty += yshake;
	}
//	sprite->SetHotSpot(hotx, hoty);
	SpriteItemManager::SetSpriteHotSpot(sprite, hotx, hoty);
}
