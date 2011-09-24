#include "../header/Selector.h"
#include "../header/SE.h"
#include "../header/Main.h"
#include "../header/Process.h"
#include "../header/SpriteItemManager.h"
#include "../header/BObject.h"

Selector::Selector()
{
	sprite = NULL;
	flag	= SEL_NONE;
	sub = false;
}

Selector::~Selector()
{
}

void Selector::Complete()
{
}

void Selector::valueSet(BYTE _ID, int siID, float cenx, float ceny, float _hscale, float _vscale, BYTE _flag /* = SEL_NULL */)
{
	ID		=	_ID;
	x		=	cenx;
	y		=	ceny;
	hscale	=	_hscale;
	vscale	=	_vscale;

	timer	=	0;
	flag	=	SEL_NONE;
	sub		=	false;

	if(sprite)
	{
		SpriteItemManager::FreeSprite(&sprite);
	}
	if (siID >= 0)
	{
		sprite = SpriteItemManager::CreateSprite(siID);
	}

	alpha = 0xff;

	for(int i=0;i<SEL_STATEMAX;i++)
	{
		adj[i].xadj = x;
		adj[i].yadj = y;
	}
}

void Selector::infoSet(char * info, DWORD ucol /* = 0xffffffff */, DWORD dcol /* = 0xffffffff */, float shadow, float xoffset/* =0 */, float yoffset/* =0 */, float hscale/* =1.0f */, float vscale/* =0.0f */, BYTE alignflag/* =HGETEXT_CENTER|HGETEXT_MIDDLE */, bool sync /* = false*/)
{
	if (!info || !strlen(info))
	{
		return;
	}
	fsinfo.SignUp(info, hscale);
	infoucol = ucol;
	infodcol = dcol;
	infoshadow = shadow;
	infoxoffset = xoffset;
	infoyoffset = yoffset;
	infohscale = hscale;
	infovscale = vscale;
	infoalignflag = alignflag;
	infosync = sync;
}

void Selector::setAdj(int i, float xadj, float yadj)
{
	adj[i].xadj = xadj;
	adj[i].yadj = yadj;
}

void Selector::actionSet(BYTE setflag, float xadj, float yadj)
{
	setAdj(setflag, xadj, yadj);
}

void Selector::actionSet(BYTE setflag, seladj * adj)
{
	if (!adj)
	{
		return;
	}
	setAdj(setflag, adj[setflag].xadj, adj[setflag].yadj);
}

void Selector::Render()
{
	if (sprite)
	{
		SpriteItemManager::RenderSpriteEx(sprite, x, y, 0, hscale, vscale);
	}
}

void Selector::RenderInfo()
{
	if (infosync && (!(flag & SEL_OVER) && !(flag & SEL_ENTER)))
	{
		return;
	}
	fsinfo.SetColor(infoucol, infoucol, infodcol, infodcol);
	fsinfo.Render(x+infoxoffset, y+infoyoffset, infoshadow, infoalignflag);
}

void Selector::ChangeState(BYTE state, BYTE op)
{
	BYTE _tflag = flag;
	switch (op)
	{
	case SELOP_EQUAL:
		flag = state;
		break;
	case SELOP_SET:
		flag |= state;
		break;
	case SELOP_UNSET:
		flag &= ~state;
		break;
	}
	if (flag != _tflag)
	{
		timer = 0;
	}
}

bool Selector::checkSub()
{
	if((flag & SEL_GRAY) && !(flag & SEL_NONACTIVE))
	{
		sub = true;
		return true;
	}
	return false;
}

bool Selector::checkFVState()
{
	if (!(flag>>1) && !checkSub())
	{
		return true;
	}
	return false;
}

void Selector::PreAction(int nselect, int select, int * fvID, Selector ** fvselector)
{
	if (checkSub())
	{
		flag &= ~SEL_GRAY;
	}

	if(!((flag & SEL_INFOMASK)>>1) && ID < nselect)
	{
		if(ID == select)
		{
			ChangeState(SEL_OVER, SELOP_SET);
		}
		else
		{
			ChangeState(SEL_OVER, SELOP_UNSET);
		}
	}

	if(!(flag>>1) && !sub && *fvID < 0)
	{
		*fvID = ID;
	}

	if (ID == *fvID && !(*fvselector) && checkFVState())
	{
		*fvselector = this;
	}
}

bool Selector::PostAction(int * select, int sellock, int nPageNum, float fadebegin, float offset, int shiftangle, float * selectframex, float * selectframey)
{
	bool ret = false;
	int tindex = SELINFO_NONE;
	switch (flag & SEL_INFOMASK)
	{
	case SEL_OVER:
		tindex = SELINFO_OVER;
		break;
	case SEL_ENTER:
		tindex = SELINFO_ENTER;
		break;
	case SEL_LEAVE:
		tindex = SELINFO_LEAVE;
		break;
	}

	bool changeselectframe = false;
	if (ID == *select && flag == SEL_OVER)
	{
		changeselectframe = true;
	}

	if (timer < maxtime)
	{
		x += (adj[tindex].xadj - x) / (maxtime-timer);
		y += (adj[tindex].yadj - y) / (maxtime-timer);
		switch (tindex)
		{
		case SELINFO_NONE:
			alpha = 0x30 * (maxtime-timer) / maxtime + 0xcf;
			break;
		case SELINFO_OVER:
			alpha = 0x10 * timer / maxtime + 0xef;
			break;
		case SELINFO_ENTER:
			alpha = 0xff;
			break;
		case SELINFO_LEAVE:
			alpha = 0x80 * (maxtime - timer) / maxtime;
			break;
		}
		if (changeselectframe)
		{
			BObject _bobj(*selectframex, *selectframey);
			_bobj.chaseAim(x, y, maxtime-timer);
			_bobj.updateMove();
			*selectframex = _bobj.x;
			*selectframey = _bobj.y;
		}
		timer++;
	}
	else
	{
		x = adj[tindex].xadj;
		y = adj[tindex].yadj;
		switch (tindex)
		{
		case SELINFO_NONE:
			alpha = ROLL(gametime, 0x3f) + 0x80;
			break;
		case SELINFO_OVER:
			alpha = ROLL(gametime, 0x3f) / 0x10 + 0xf0;
			break;
		case SELINFO_ENTER:
			alpha = 0xff;
			break;
		case SELINFO_LEAVE:
			alpha = 0;
			break;
		}
		if (changeselectframe)
		{
			*selectframex = x;
			*selectframey = y;
		}
	}

	if(flag & SEL_ENTER)
	{
		*select = sellock;
		if(flag & ~SEL_ENTER)
		{
			timer = maxtime;
			ChangeState(SEL_ENTER, SELOP_EQUAL);
		}
		if(timer == maxtime)
		{
			Complete();
			ret = true;
		}
	}
	if(flag & SEL_LEAVE)
	{
		if(flag & ~SEL_LEAVE)
		{
			timer = 0;
			ChangeState(SEL_LEAVE, SELOP_EQUAL);
			alpha = 0x80;
		}
	}
	
	if(flag & SEL_NONACTIVE)
	{
		if(flag & SEL_GRAY)
			alpha = 0x40;
		else
			alpha = 0xff;
	}

	//
	BYTE fademode = 0;
	if (nPageNum && !(flag & SEL_STAY))
	{
		float fadeend = fadebegin + (nPageNum+2) * offset;
		float fadeoffbegin = fadebegin + offset / 2;
		float fadeoffend = fadeend - offset / 2;
		while (shiftangle > 18000)
		{
			shiftangle -= 18000;
		}
		while (shiftangle <= 0)
		{
			shiftangle += 18000;
		}
		if (shiftangle > 4500 && shiftangle <= 13500)
		{
			if (y < fadebegin || y > fadeend)
			{
				alpha = 0;
			}
			else if (y <= fadeoffbegin)
			{
				fademode = SELFADE_UP;
			}
			else if (y >= fadeoffend)
			{
				fademode = SELFADE_DOWN;
			}
		}
		else
		{
			if (x < fadebegin || x > fadeend)
			{
				alpha = 0;
			}
			else if (x <= fadeoffbegin)
			{
				fademode = SELFADE_LEFT;
			}
			else if (x >= fadeoffend)
			{
				fademode = SELFADE_RIGHT;
			}
		}
	}

	if (sprite)
	{
		sprite->SetColor((alpha << 24) | (0xffffff));
	}
/*
	fsinfo.SetColor((alpha << 24) | (infoucol & 0xFFFFFF), 0);
	fsinfo.SetColor((alpha << 24) | (infoucol & 0xFFFFFF), 1);
	fsinfo.SetColor((alpha << 24) | (infodcol & 0xFFFFFF), 2);
	fsinfo.SetColor((alpha << 24) | (infodcol & 0xFFFFFF), 3);*/


	if (fademode)
	{
		switch (fademode)
		{
		case SELFADE_UP:
			if (sprite)
			{
				sprite->SetColor(0, 0);
				sprite->SetColor(0, 1);
			}
/*
			fsinfo.SetColor(0, 0);
			fsinfo.SetColor(0, 1);*/

			break;
		case SELFADE_DOWN:
			if (sprite)
			{
				sprite->SetColor(0, 2);
				sprite->SetColor(0, 3);
			}
/*
			fsinfo.SetColor(0, 2);
			fsinfo.SetColor(0, 3);*/

			break;
		case SELFADE_LEFT:
			if (sprite)
			{
				sprite->SetColor(0, 0);
				sprite->SetColor(0, 3);
			}
/*
			fsinfo.SetColor(0, 0);
			fsinfo.SetColor(0, 3);*/

			break;
		case SELFADE_RIGHT:
			if (sprite)
			{
				sprite->SetColor(0, 1);
				sprite->SetColor(0, 2);
			}
/*
			fsinfo.SetColor(0, 1);
			fsinfo.SetColor(0, 2);*/

			break;
		}
	}

	if(sub)
	{
		flag |= SEL_GRAY;
		sub = false;
	}

	return ret;
}

void Selector::SetMaxtime(int _maxtime)
{
	maxtime = _maxtime;
}