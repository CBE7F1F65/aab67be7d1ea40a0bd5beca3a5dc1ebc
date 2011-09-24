#include "../header/Beam.h"
#include "../header/Bullet.h"
#include "../header/Player.h"
#include "../header/SE.h"
#include "../header/Chat.h"
#include "../header/BossInfo.h"
#include "../header/Item.h"
#include "../header/Target.h"
#include "../header/Export.h"
#include "../header/ProcessDefine.h"
#include "../header/Process.h"
#include "../header/GameAI.h"
#include "../header/SpriteItemManager.h"
#include "../header/BResource.h"

#define	BEAMMAX				0x50

#define BEAM_DELAYTIME	32

VectorList<Beam> Beam::be[M_PL_MATCHMAXPLAYER];

Beam::Beam()
{
	able	= false;
}

Beam::~Beam()
{
}

void Beam::Init()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		be[i].init(BEAMMAX);
	}
}

void Beam::ClearItem()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		be[i].clear_item();
	}
}

void Beam::Action()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		DWORD stopflag = Process::mp.GetStopFlag();
		bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, j, FRAME_STOPFLAG_BEAM);
		if (!binstop)
		{
			if (be[j].getSize())
			{
				DWORD i = 0;
				DWORD size = be[j].getSize();
				for (be[j].toBegin(); i<size; be[j].toNext(), i++)
				{
					if (!be[j].isValid())
					{
						continue;
					}
					if ((*be[j]).exist)
					{
						(*be[j]).action(j);
						GameAI::ai[j].CheckBeamCollision(&(*be[j]));
					}
					else
					{
						be[j].pop();
					}
				}
			}
		}
	}
}

void Beam::RenderAll(BYTE playerindex)
{
	if (be[playerindex].getSize())
	{
		DWORD i = 0;
		DWORD size = be[playerindex].getSize();
		for (be[playerindex].toBegin(); i<size; be[playerindex].toNext(), i++)
		{
			if (be[playerindex].isValid())
			{
				(*be[playerindex]).Render();
			}
		}
	}
}

int Beam::Build(BYTE playerindex, float x, float y, int angle, float speed, BYTE type, BYTE color, float length, float width, BYTE flag, int fadeintime, int fadeouttime, BYTE tarID)
{
	if (be[playerindex].getSize() == BEAMMAX)
	{
		return NULL;
	}
	Beam * _tbe;
	_tbe = be[playerindex].push_back();
	int beindex = be[playerindex].getEndIndex();
	_tbe->valueSet(beindex, x, y, angle, speed, type, color, length, width, flag, fadeintime, fadeouttime, tarID);
	return beindex;
}

void Beam::Render()
{
	int i = type*BULLETCOLORMAX+color;
	if (Bullet::sprite[i])
	{
		int tblend = Bullet::sprite[i]->GetBlendMode();
		Bullet::sprite[i]->SetBlendMode(BLEND_ALPHAADD);
		Bullet::sprite[i]->SetColor(alpha<<24|diffuse);
		SpriteItemManager::RenderSpriteEx(Bullet::sprite[i], x, y, ARC(angle+headangle+BULLET_ANGLEOFFSET), hscale, vscale);
		Bullet::sprite[i]->SetBlendMode(tblend);
	}
}

void Beam::valueSet(WORD _ID, float _x, float _y, int _angle, float _speed, BYTE _type, BYTE _color, float _length, float _width, BYTE _flag, int _fadeintime, int _fadeouttime, BYTE _tarID)
{
	ID			=	_ID;
	x			=	_x;
	y			=	_y;
	angle		=	_angle;
	speed		=	_speed;
	type		=	_type;
	color		=	_color;
	length		=	_length;
	width		=	_width;
	flag		=	_flag;
	fadeintime	=	_fadeintime;
	fadeouttime	=	_fadeouttime;

	tarID		=	_tarID;
	holdtar		=	0xff;
	pintar		=	0xff;
	holdoffset	=	0;

	if (flag & BEAMFLAG_DELAY)
	{
		delaytimer = BEAM_DELAYTIME;
	}
	else
	{
		delaytimer	=	0;
	}

	timer			=	0;
	grazetimer		=	0;
	exist			=	true;
	fadeout			=	false;
	able			=	true;
	headangle		=	0;
	alpha			=	0xff;

	lastangle = angle;

	xplus = cost(angle);
	yplus = sint(angle);

	spriteData * spdata = SpriteItemManager::CastSprite(BResource::bres.bulletdata[type].siid);
	texw	=	spdata->tex_w;
	texh	=	spdata->tex_h;

	if (!width)
	{
		width = texw;
	}

	hscale = width / texh;
	if(flag & BEAMFLAG_HORIZON)
	{
//		hscale = length / 16.0f;
//		vscale = 0.1f;
		/*
		if (fadeintime > 0)
		{
			hscale = hscale / fadeintime;
		}
		*/
		hscale = 0;
		vscale = length / texh;
		x += length * cost(angle) / 2;
		y += length * sint(angle) / 2;
		speed /= 100.0f;
	}
	else
	{
		hscale = 1;
		vscale = 0;
		xplus *= speed;
		yplus *= speed;
	}
}

void Beam::SetVector(const BObject &ori, const BObject &aim)
{
	SetVector(ori.x, ori.y, aim.x, aim.y);
}

void Beam::SetVector(float orix, float oriy, float aimx, float aimy)
{
	length = DIST(orix, oriy, aimx, aimy) + holdoffset;
	x = (orix + aimx) / 2;
	y = (oriy + aimy) / 2;
	vscale = length / texh;
	angle = aMainAngle(aimx, aimy);
}

void Beam::SetHold(BYTE _holdtar, float _holdoffset)
{
	holdtar = _holdtar;
	holdoffset = _holdoffset;
}

void Beam::SetHold(BYTE _holdtar, BYTE _pintar, float holdoffset)
{
	SetHold(_holdtar, holdoffset);
	pintar = _pintar;
}

void Beam::action(BYTE playerindex)
{
	if (delaytimer)
	{
		delaytimer--;
		return;
	}
	if(angle != lastangle)
	{
		xplus = speed * cost(angle);
		yplus = speed * sint(angle);
		lastangle = angle;
		lastspeed = speed;
	}
	timer++;

	if(!fadeout)
	{
		if(BossInfo::flag >> 2)
		{
			fadeout = true;
			timer = 0;
		}
		if(timer == 1)
		{
			SE::push(SE_BEAM_1, x);
		}

		if (!Player::p[playerindex].bInfi)
		{
			if (isInRect(Player::p[playerindex].x, Player::p[playerindex].y, Player::p[playerindex].r))
			{
				Player::p[playerindex].DoShot();
			}
		}
		if(!(flag & BEAMFLAG_HORIZON))
		{
			if(vscale * texh < length)
			{
				x += xplus / 2;
				y += yplus / 2;
				vscale += speed / texh;
			}
			else if(!(flag & BEAMFLAG_STOP))
			{
				x += xplus;
				y += yplus;
			}
		}
		else
		{
			if(timer < fadeintime)
			{
				hscale += width / texw / fadeintime;
			}
		}
		if ((flag & BEAMFLAG_HORIZON) || (flag & BEAMFLAG_STOP))
		{
			if(timer > (DWORD)fadeouttime)
			{
				fadeout = true;
				timer = 0;
			}
		}
		if (holdtar != 0xff)
		{
			if (pintar != 0xff)
			{
				SetVector(Target::tar[holdtar].x, Target::tar[holdtar].y, Target::tar[pintar].x, Target::tar[pintar].y);
			}
			else
			{
				float factor = (vscale * texh - holdoffset) / speed;
				SetVector(Target::tar[holdtar].x, Target::tar[holdtar].y, Target::tar[holdtar].x + factor * xplus, Target::tar[holdtar].y + factor * yplus);
			}
		}

		if(tarID != 0xff)
		{
			Target::SetValue(tarID, x, y);
		}

		if(Chat::chatitem.IsChatting())
		{
			fadeout = true;
			timer = 0;
		}

		if (!(flag & BEAMFLAG_NOGRAZE))
		{
			if(grazetimer)
			{
				grazetimer++;
				if(grazetimer == 6)
					grazetimer = 0;
			}
			else
			{
				grazetimer++;
				if(isInRect(Player::p[playerindex].x, Player::p[playerindex].y, PLAYER_GRAZE_R))
				{
					float itemx;
					float itemy;
					float tk = 0;
					if (xplus || yplus)
					{
						tk = - ((x - Player::p[playerindex].x) * xplus + (y - Player::p[playerindex].y) * yplus) / (xplus * xplus + yplus * yplus);
						itemx = x + xplus * tk;
						itemy = y + yplus * tk;
					}
					else
					{
						itemx = Player::p[playerindex].x;
						itemy = Player::p[playerindex].y;
					}
					Player::p[playerindex].DoGraze(itemx, itemy);
				}
			}

		}
		float nowlength = vscale * texh;
		float nowwidth = hscale * texw;
		float longside = nowlength > nowwidth ? nowlength : nowwidth;
		if(	x - longside > M_DELETECLIENT_RIGHT_(playerindex) ||
			x + longside < M_DELETECLIENT_LEFT_(playerindex) ||
			y - longside > M_DELETECLIENT_BOTTOM ||
			y + longside < M_DELETECLIENT_TOP)
			exist = false;
	}
	else
	{
		if(timer == 1)
		{
			SE::push(SE_BEAM_FADEOUT, x);
		}
		if(timer == 32)
			exist = false;
		else
		{
			vscale -= width / texw / 32;//0.03125;
			alpha = (BYTE)(32-timer) * 8 - 1;
		}
	}
	able = exist && !fadeout;
}

bool Beam::isInRect(float aimx, float aimy, float r, int nextstep)
{
	if(vscale < BEAM_INVALIDSCALE)
		return false;

	float _x = x;
	float _y = y;

	float rl = BResource::bres.bulletdata[type].collisionMain;
	float rs = BResource::bres.bulletdata[type].collisionSub;

	float nowrl = vscale * rl;
	if (nextstep)
	{
		_x += xplus * nextstep;
		_y += yplus * nextstep;
//		nowrl += 4;
	}

	float cx = _x;
	float cy = _y;

//	nowlength *= 0.3125f;

	float rotCos;
	float rotSin;
	if (!(flag & BEAMFLAG_HORIZON) && speed != 0)
	{
		rotCos = xplus / speed;
		rotSin = yplus / speed;
	}
	else
	{
		rotCos = cost(angle);
		rotSin = sint(angle);
	}
	float nowrs = hscale * rs;
	return CheckCollisionEllipse(_x, _y, aimx, aimy, nowrs, nowrl, rotCos, rotSin, r);

}