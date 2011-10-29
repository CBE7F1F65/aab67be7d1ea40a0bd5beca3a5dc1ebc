#include "../Header/Effectsys.h"
#include "../Header/Main.h"
#include "../Header/Export.h"
#include "../Header/Player.h"
#include "../Header/Target.h"
#include "../Header/ProcessDefine.h"
#include "../Header/Process.h"
#include "../Header/SpriteItemManager.h"

VectorList<Effectsys> Effectsys::effsys;
hgeEffectSystem Effectsys::efftype[DATASTRUCT_EFFECTMAX];

Effectsys::Effectsys()
{
	exist = false;
}

Effectsys::~Effectsys()
{
	Clear();
	eff.FreeList();
}

void Effectsys::Clear(bool erase)
{
	exist = false;
	eff.Stop(true);
	if (erase)
	{
		effsys.pop();
	}
}

void Effectsys::ClearAll()
{
	for (int i=0; i<EFFECTSYSMAX; i++)
	{
		effsys[i].Clear();
	}
	effsys.clear_item();
}

void Effectsys::Action()
{
	DWORD stopflag = Process::mp.GetStopFlag();
	bool binstop = FRAME_STOPFLAGCHECK_(stopflag, FRAME_STOPFLAG_EFFECTSYS);
	if (!binstop)
	{
		DWORD i = 0;
		DWORD size = effsys.getSize();
		for (effsys.toBegin(); i<size; effsys.toNext(), i++)
		{
			if ((*effsys).exist)
			{
				(*effsys).action(true);
			}
		}
	}
}


void Effectsys::RenderAll()
{
	DWORD i = 0;
	DWORD size = effsys.getSize();
	for (effsys.toBegin(); i<size; effsys.toNext(), i++)
	{
		if ((*effsys).exist)
		{
			(*effsys).Render();
		}
	}
}

void Effectsys::Release()
{
	for (int i=0; i<DATASTRUCT_EFFECTMAX; i++)
	{
		efftype[i].FreeList();
	}
}

bool Effectsys::Init(HTEXTURE * tex, const char * foldername, char name[][M_PATHMAX])
{
	Release();
	char buffer[M_STRMAX];
	for(int i=0;i<DATASTRUCT_EFFECTMAX;i++)
	{
		if (!strlen(name[i]))
		{
			hgeEffectBasicInfo ebi;
			ZeroMemory(&ebi, sizeof(hgeEffectBasicInfo));
			efftype[i].SetBasicInfo(&ebi);
			continue;
		}
		strcpy(buffer, foldername);
		strcat(buffer, name[i]);
		
		if(Export::effLoad(buffer, &efftype[i], tex) < 0)
		{
#ifdef __DEBUG_LOG
			HGELOG("%s\nFailed in loading Effect System File %s.", HGELOG_ERRSTR, buffer);
#endif
			hgeEffectBasicInfo ebi;
			ZeroMemory(&ebi, sizeof(hgeEffectBasicInfo));
			efftype[i].SetBasicInfo(&ebi);
		}
		else 
		{
#ifdef __DEBUG_LOG
			HGELOG("Succeeded in loading Effect System file %s", buffer);
#endif
		}

	}
	effsys.init(EFFECTSYSMAX);
	return true;
}

int Effectsys::Build(WORD ID, float x, float y, float z, int lifetime/* =-1 */, BYTE tarID/* =0xff */, int angle/* =9000 */, float speed/* =0.0f */, float zSpeed/* =0.0f */)
{
	Effectsys _effsys;
	Effectsys * _peffsys = NULL;
	if (effsys.getSize() < EFFECTSYSMAX)
	{
		_peffsys = effsys.push_back(_effsys);
	}
	else
	{
		DWORD i = 0;
		DWORD size = effsys.getSize();
		for (effsys.toEnd(); i<size; effsys.toNext(), i++)
		{
			if (!effsys.isValid())
			{
				_peffsys = effsys.push(_effsys);
			}
		}
	}
	if (_peffsys)
	{
		_peffsys->valueSet(ID, x, y, z, lifetime, tarID, angle, speed, zSpeed);
		return effsys.getIndex();
	}
	else
	{
		return -1;
	}
}


void Effectsys::valueSet(WORD ID, BObject & owner)
{
	valueSet(ID, owner.x, owner.y);
}

void Effectsys::chaseSet(int _chasetimer, BYTE _tarAim)
{
	chasetimer = _chasetimer;
	tarAim = _tarAim;
}

void Effectsys::valueSet(WORD _ID, float _x, float _y, float _z, int _lifetime, BYTE _tarID, int _angle, float _speed, float _zSpeed)
{
	ID			= _ID;
	tarID		= _tarID;
	x			= _x;
	y			= _y;
	z			= _z;
	lifetime	= _lifetime;
	angle		= _angle;
	speed		= _speed;
	zSpeed		= _zSpeed;
	headangle	= 0;
	hscale		= 1.0f;
	vscale		= 1.0f;
	timer		= 0;
	SetColorMask(0xffffffff);
	chaseSet(0, 0xff);
	Clear();

	exist = true;

	if(ID >= DATASTRUCT_EFFECTMAX)
		ID = 0;

	eff.InitEffectSystem(efftype[ID]);

	MoveTo(x, y, z, true);
	Fire();
}

void Effectsys::Stop(bool bKill /* = false */)
{
	eff.Stop(bKill);
}

void Effectsys::Fire()
{
	eff.Fire();
}

void Effectsys::SetColorMask(DWORD color)
{
	alpha = GETA(color);
	diffuse = color & 0xffffff;
}

void Effectsys::Render()
{
	SpriteItemManager::EffectSystemRender(&eff, Export::GetFarPoint(), (alpha<<24)|diffuse);
}

void Effectsys::MoveTo(float _x, float _y, float _z, bool bForce)
{
	x = _x;
	y = _y;
	z = _z;
	eff.MoveTo(x, y, z, bForce);
}

void Effectsys::action(bool byself)
{
	timer++;

	if (lifetime > 0)
	{
		if (timer == lifetime)
		{
			Stop();
		}
		else if (timer == lifetime + EFFSYS_AUTOFADEOUT_TIME)
		{
			Clear(byself);
			return;
		}
	}

	if (chasetimer)
	{
		chasetimer--;
		if (tarAim < TARGETMAX)
		{
			chaseAim(Target::tar[tarAim].x, Target::tar[tarAim].y, chasetimer);
		}
	}

	if (speed)
	{
		updateMove();
	}
	z += zSpeed;

	MoveTo(x, y, z);
	if (tarID != 0xff)
	{
		Target::SetValue(tarID, x, y);
	}
	eff.Update();
}