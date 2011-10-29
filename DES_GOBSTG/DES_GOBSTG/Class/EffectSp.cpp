#include "../Header/EffectSp.h"
#include "../Header/Player.h"
#include "../Header/Enemy.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/FrontDisplayName.h"
#include "../Header/Bullet.h"
#include "../Header/Scripter.h"
#include "../Header/ProcessDefine.h"
#include "../Header/Process.h"

#define EFFSPMAX	(BULLETMAX)

VectorList<EffectSp> EffectSp::effsp;
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
	effsp.init(EFFSPMAX);
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
	effsp.clear_item();
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
	DWORD stopflag = Process::mp.GetStopFlag();
	bool binstop = FRAME_STOPFLAGCHECK_(stopflag, FRAME_STOPFLAG_EFFECTSP);
	if (!binstop)
	{
		if (effsp.getSize())
		{
			DWORD i = 0;
			DWORD size = effsp.getSize();
			for (effsp.toBegin(); i<size; effsp.toNext(), i++)
			{
				if (effsp.isValid())
				{
					if ((*effsp).exist)
					{
						(*effsp).action();
					}
					else
					{
						effsp.pop();
					}
				}
			}
		}
	}
}

void EffectSp::RenderAll()
{
	if (effsp.getSize())
	{
		DWORD i = 0;
		DWORD size = effsp.getSize();
		for (effsp.toBegin(); i<size; effsp.toNext(), i++)
		{
			if (effsp.isValid())
			{
				if ((*effsp).exist)
				{
					(*effsp).Render();
				}
			}
		}
	}
}


void EffectSp::EffectSpOff(int _setID, int _ID)
{
	if (_setID < EFFSPSET_LISTBEGIN || _setID >= EFFSPSET_LISTUNTIL)
	{
		return;
	}
	DWORD nowindex = effsp.getIndex();
	if (effsp.getSize())
	{
		DWORD i = 0;
		DWORD size = effsp.getSize();
		for (effsp.toBegin(); i<size; effsp.toNext(), i++)
		{
			if (effsp.isValid())
			{
				if ((*effsp).exist)
				{
					if ((*effsp).setID == _setID)
					{
						if (_ID == 0xff || (*effsp).ID == _ID)
						{
							effsp.pop();
						}
					}
				}
			}
		}
	}
	effsp.toIndex(nowindex);
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
	if (effsp.getSize() == EFFSPMAX)
	{
		return -1;
	}
	int esindex = -1;
	EffectSp _effsp;
	EffectSp * _peffsp = effsp.push_back(_effsp);
	esindex = effsp.getEndIndex();
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
	case EFFSP_CHASE_PLAYER:
		aimx = Player::p.x;
		aimy = Player::p.y;
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