#include "../Header/Player.h"
#include "../Header/PlayerBullet.h"
#include "../Header/SE.h"
#include "../Header/Enemy.h"
#include "../Header/Chat.h"
#include "../Header/Process.h"
#include "../Header/BResource.h"
#include "../Header/SpriteItemManager.h"

#include "../Header/GameAI.h"

#define _PLAYER_ANIMATIONSPEED	4

#define _PLAYER_WINFLAG_1	0x01
#define _PLAYER_WINFLAG_2	0x02
#define _PLAYER_WINFLAG_3	0x04

void Player::Init()
{
	p.exist = false;
	p.ID = 0xffff;
	p.SetAble(false);
}

void Player::RenderAll()
{
	if (p.exist)
	{
		p.Render();
		p.RenderEffect();
	}
}

void Player::SetInitLife(BYTE _initlife)
{
	initlife = _initlife;
}

void Player::SetAble(bool setable)
{
	able = setable;
}

bool Player::CheckAble()
{
	return able;
}

int Player::IsEnd()
{
	return -1;
}

void Player::initFrameIndex()
{
	nowframeindex = 0;
	playerData * pdata = &(BResource::bres.playerdata[ID]);
	int tfi = 0;
	frameindex[PLAYER_FRAME_STAND] = tfi;

	bool bhr = pdata->rightPreFrame;
	bool bhl = pdata->leftPreFrame;

	tfi += pdata->standFrame;
	frameindex[PLAYER_FRAME_LEFTPRE] = tfi;
	if (bhr)
	{
		tfi += pdata->rightPreFrame;
	}
	else
	{
		tfi += pdata->leftPreFrame;
	}
	frameindex[PLAYER_FRAME_LEFT] = tfi;

	if (bhr)
	{
		tfi += pdata->rightFrame;
	}
	else
	{
		tfi += pdata->leftFrame;
	}
	if (!bhr || !bhl)
	{
		tfi -= pdata->leftPreFrame + pdata->rightPreFrame + pdata->leftFrame + pdata->rightFrame;
	}
	frameindex[PLAYER_FRAME_RIGHTPRE] = tfi;
	if (bhr)
	{
		tfi += pdata->rightPreFrame;
	}
	else
	{
		tfi += pdata->leftPreFrame;
	}
	frameindex[PLAYER_FRAME_RIGHT] = tfi;
	if (bhr)
	{
		tfi += pdata->rightFrame;
	}
	else
	{
		tfi += pdata->leftFrame;
	}
}

BYTE Player::getFrameIndex(BYTE frameenum)
{
	flipx = false;
	playerData * pdata = &(BResource::bres.playerdata[ID]);
	if ((frameenum == PLAYER_FRAME_RIGHTPRE || frameenum == PLAYER_FRAME_RIGHT) && (!pdata->rightPreFrame) ||
		(frameenum == PLAYER_FRAME_LEFTPRE || frameenum == PLAYER_FRAME_LEFT) && (!pdata->leftPreFrame))
	{
		flipx = true;
	}
	return frameindex[frameenum];
}

void Player::setFrame(BYTE frameenum)
{
	frameoffset = 0;
	setIndexFrame(getFrameIndex(frameenum));
	nowstate = frameenum;
}

void Player::setIndexFrame(BYTE index)
{
	playerData * pdata = &(BResource::bres.playerdata[ID]);
	nowframeindex = index;
	SpriteItemManager::ChangeSprite(BResource::bres.playerdata[ID].siid+index, sprite);
//	sprite->SetFlip(flipx, false);
	SpriteItemManager::SetSpriteFlip(sprite, flipx);
}


void Player::updateFrame(BYTE frameenum, int usetimer /* = -1*/)
{
	if (usetimer == -1)
	{
		usetimer = timer;
	}
	if (frameenum != nowstate && (frameenum == PLAYER_FRAME_STAND || frameenum+1 != nowstate))
	{
		setFrame(frameenum);
		return;
	}
	if ((usetimer % _PLAYER_ANIMATIONSPEED))
	{
		return;
	}
	playerData * pdata = &(BResource::bres.playerdata[ID]);
	frameoffset++;
	BYTE tbyte;
	switch (nowstate)
	{
	case PLAYER_FRAME_STAND:
		if (frameoffset >= pdata->standFrame)
		{
			setFrame(PLAYER_FRAME_STAND);
		}
		else
		{
			setIndexFrame(getFrameIndex(PLAYER_FRAME_STAND) + frameoffset);
		}
		break;
	case PLAYER_FRAME_LEFTPRE:
		if (!pdata->leftPreFrame)
		{
			tbyte = pdata->rightPreFrame;
		}
		else
		{
			tbyte = pdata->leftPreFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(PLAYER_FRAME_LEFT);
		}
		else
		{
			setIndexFrame(getFrameIndex(PLAYER_FRAME_LEFTPRE) + frameoffset);
		}
		break;
	case PLAYER_FRAME_LEFT:
		if (!pdata->leftFrame)
		{
			tbyte = pdata->rightFrame;
		}
		else
		{
			tbyte = pdata->leftFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(PLAYER_FRAME_LEFT);
		}
		else
		{
			setIndexFrame(getFrameIndex(PLAYER_FRAME_LEFT) + frameoffset);
		}
		break;
	case PLAYER_FRAME_RIGHTPRE:
		if (!pdata->rightPreFrame)
		{
			tbyte = pdata->leftPreFrame;
		}
		else
		{
			tbyte = pdata->rightPreFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(PLAYER_FRAME_RIGHT);
		}
		else
		{
			setIndexFrame(getFrameIndex(PLAYER_FRAME_RIGHTPRE) + frameoffset);
		}
		break;
	case PLAYER_FRAME_RIGHT:
		if (!pdata->rightFrame)
		{
			tbyte = pdata->leftFrame;
		}
		else
		{
			tbyte = pdata->rightFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(PLAYER_FRAME_RIGHT);
		}
		else
		{
			setIndexFrame(getFrameIndex(PLAYER_FRAME_RIGHT) + frameoffset);
		}
		break;
	}
}

void Player::UpdatePlayerData()
{
	playerData * pdata = &(BResource::bres.playerdata[ID]);
	r = pdata->collision_r;
	speed = pdata->fastspeed;
	slowspeed = pdata->slowspeed;
	shotdelay = pdata->shotdelay;
	if (sprite)
	{
		SpriteItemManager::ChangeSprite(pdata->siid, sprite);
	}
	else
	{
		sprite = SpriteItemManager::CreateSprite(pdata->siid);
	}
}

void Player::SetInfi(BYTE reasonflag, int _infitimer/* =PLAYER_INFIMAX */)
{
	infireasonflag |= reasonflag;
	if (_infitimer == PLAYER_INFIMAX)
	{
		infitimer = PLAYER_INFIMAX;
	}
	else if (_infitimer == PLAYER_INFIUNSET)
	{
		infitimer = 0;
	}

	if (infitimer == PLAYER_INFIMAX || infitimer >= _infitimer)
	{
		return;
	}
	infitimer = _infitimer;
}

void Player::SetChara(WORD id)
{
	ID = id;
}
