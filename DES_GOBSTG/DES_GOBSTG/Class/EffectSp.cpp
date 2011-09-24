#include "../header/EffectSp.h"
#include "../header/Player.h"
#include "../header/Enemy.h"
#include "../header/SpriteItemManager.h"
#include "../header/FrontDisplayName.h"
#include "../header/Bullet.h"
#include "../header/Scripter.h"
#include "../header/ProcessDefine.h"
#include "../header/Process.h"

#define EFFSPMAX	(BULLETMAX)

VectorList<EffectSp> EffectSp::effsp[M_PL_MATCHMAXPLAYER];
hgeSprite * EffectSp::sprite = NULL;

int EffectSp::senditemsiid[EFFSPSEND_COLORMAX][EFFSPSEND_ANIMATIONMAX];
int EffectSp::senditemexsiid;

EffectSp::EffectSp()
{
}

EffectSp::~EffectSp()
{
}

void EffectSp::Init()
{
	Release();
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		effsp[i].init(EFFSPMAX);
	}
	int senditemsiidbegin = SpriteItemManager::GetIndexByName(SI_SENDITEM_00);
	for (int i=0; i<EFFSPSEND_COLORMAX; i++)
	{
		for (int j=0; j<EFFSPSEND_ANIMATIONMAX; j++)
		{
			senditemsiid[i][j] = senditemsiidbegin + i*EFFSPSEND_ANIMATIONMAX + j;
		}
	}
	senditemexsiid = SpriteItemManager::GetIndexByName(SI_SENDITEM_EX);
	sprite = SpriteItemManager::CreateNullSprite();
}

void EffectSp::Release()
{
	if (sprite)
	{
		SpriteItemManager::FreeSprite(&sprite);
	}
	ClearItem();
}

void EffectSp::ClearItem()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		effsp[i].clear_item();
	}
}

void EffectSp::Render()
{
	if (sprite)
	{
		SpriteItemManager::ChangeSprite(siidnow, sprite);
		sprite->SetColor((alpha<<24)|diffuse);
		sprite->SetBlendMode(blend);
		SpriteItemManager::RenderSpriteEx(sprite, x, y, ARC(angle+headangle), hscale, vscale);
	}
}

void EffectSp::Action()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		DWORD stopflag = Process::mp.GetStopFlag();
		bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, j, FRAME_STOPFLAG_EFFECTSP);
		if (!binstop)
		{
			if (effsp[j].getSize())
			{
				DWORD i = 0;
				DWORD size = effsp[j].getSize();
				for (effsp[j].toBegin(); i<size; effsp[j].toNext(), i++)
				{
					if (effsp[j].isValid())
					{
						if ((*effsp[j]).exist)
						{
							(*effsp[j]).action();
						}
						else
						{
							effsp[j].pop();
						}
					}
				}
			}
		}
	}
}

void EffectSp::RenderAll()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		if (effsp[j].getSize())
		{
			DWORD i = 0;
			DWORD size = effsp[j].getSize();
			for (effsp[j].toBegin(); i<size; effsp[j].toNext(), i++)
			{
				if (effsp[j].isValid())
				{
					if ((*effsp[j]).exist)
					{
						(*effsp[j]).Render();
					}
				}
			}
		}
	}
}


void EffectSp::EffectSpOff(BYTE _playerindex, int _setID, int _ID)
{
	if (_setID < EFFSPSET_LISTBEGIN || _setID >= EFFSPSET_LISTUNTIL)
	{
		return;
	}
	DWORD nowindex = effsp[_playerindex].getIndex();
	if (effsp[_playerindex].getSize())
	{
		DWORD i = 0;
		DWORD size = effsp[_playerindex].getSize();
		for (effsp[_playerindex].toBegin(); i<size; effsp[_playerindex].toNext(), i++)
		{
			if (effsp[_playerindex].isValid())
			{
				if ((*effsp[_playerindex]).exist)
				{
					if ((*effsp[_playerindex]).setID == _setID)
					{
						if (_ID < 0 || (*effsp[_playerindex]).ID == _ID)
						{
							effsp[_playerindex].pop();
						}
					}
				}
			}
		}
	}
	effsp[_playerindex].toIndex(nowindex);
}

void EffectSp::actionSet(int _angle, float _speed, int _headangleadd/* =0 */)
{
	angle = _angle;
	speed = _speed;
	headangleadd = _headangleadd;
}

void EffectSp::chaseSet(BYTE _chaseflag, float _aimx, float _aimy, int _chasetimer/* =-1 */, BYTE _chaseaim/* =0xff */)
{
	if (chaseflag != _chaseflag || _chasetimer != -1)
	{
		chasetimer = _chasetimer;
	}
	if (chaseflag != chaseflag || _chaseaim != 0xff)
	{
		chaseaim = _chaseaim;
	}
	chaseflag = _chaseflag;
	aimx = _aimx;
	aimy = _aimy;
}

int EffectSp::Build(int setID, WORD ID, int siid, float x, float y, int headangle/* =0 */, float hscale/* =1.0f */, float vscale/* =0.0f */)
{
	if (effsp[ID].getSize() == EFFSPMAX)
	{
		return -1;
	}
	int esindex = -1;
	EffectSp _effsp;
	EffectSp * _peffsp = effsp[ID].push_back(_effsp);
	esindex = effsp[ID].getEndIndex();
	_peffsp->valueSet(setID, ID, siid, x, y, headangle, hscale, vscale);
	return esindex;
}

void EffectSp::valueSet(int _setID, WORD _ID, int _siid, float _x, float _y, int _headangle/*=0*/, float _hscale/*=1.0f*/, float _vscale/*=0.0f*/)
{
	ID			= _ID;
	setID		= _setID;
	x			= _x;
	y			= _y;
	headangle	= _headangle;
	hscale = _hscale;
	vscale = _vscale;
	siid = _siid;
	siidnow = _siid;
	bAppend = false;
	nAppend = 0;
	fAppend = 0;

	blend = BLEND_DEFAULT;
	chaseflag = EFFSP_CHASE_NULL;
	chaseaim = 0xff;
	chasetimer = 0;
	aimx = 0;
	aimy = 0;
	angle = 0;
	speed = 0;
	timer = 0;
	exist = true;
	headangleadd = 0;
	animation = 0;
	animationinterval = 0;

	colorSet(0xffffffff);
}

void EffectSp::animationSet(BYTE _animation, BYTE _animationinterval)
{
	animation = _animation;
	animationinterval = _animationinterval;
}

void EffectSp::colorSet(DWORD color, int _blend)
{
	alpha = GETA(color);
	diffuse = color & 0xffffff;
	blend = _blend;
}

void EffectSp::AppendData(int ival, float fval)
{
	nAppend = ival;
	fAppend = fval;
	bAppend = true;
}

void EffectSp::action()
{
	timer++;

	switch (chaseflag)
	{
	case EFFSP_CHASE_PLAYER_0:
		aimx = Player::p[0].x;
		aimy = Player::p[0].y;
		break;
	case EFFSP_CHASE_PLAYER_1:
		aimx = Player::p[1].x;
		aimy = Player::p[1].y;
		break;
	case EFFSP_CHASE_TARGET:
		aimx = Target::tar[chaseaim].x;
		aimy = Target::tar[chaseaim].y;
		break;
	}

	if (animation > 1)
	{
		if (timer % animationinterval == 0)
		{
			siidnow = siid + (timer/animationinterval)%animation;
		}
	}

	if (chaseflag != EFFSP_CHASE_NULL)
	{
		if (chasetimer > 0)
		{
			chasetimer = chaseAim(aimx, aimy, chasetimer);
		}
		else
		{
			x = aimx;
			y = aimy;
			if (setID >= EFFSPSET_LISTBEGIN && setID < EFFSPSET_LISTUNTIL)
			{
				Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_EFFSPCHASE, ID);
				if (setID >= EFFSPSET_SYSTEMBEGIN && setID < EFFSPSET_SYSTEMUNTIL)
				{
					exist = false;
				}
			}
		}
	}
	headangle += headangleadd;

	updateMove();
}