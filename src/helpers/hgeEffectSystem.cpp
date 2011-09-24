#include "../../include/hgeEffectSystem.h"
#include "../../include/hgevector.h"
#include <stdio.h>

HGE * hgeEffectSystem::hge = NULL;

void hgeEffectSystem::InitEffectSystem()
{
	FreeList();
	if (!hge)
	{
		hge = hgeCreate(HGE_VERSION);
	}

	nAge = HGEEFFECT_AGE_STOP;
	texnum = -1;
}

void hgeEffectSystem::Release()
{
	if (hge)
	{
		hge->Release();
		hge = NULL;
	}
}

void hgeEffectSystem::InitEffectSystem(const hgeEffectSystem &eff)
{
	InitEffectSystem();

	memcpy(&ebi, &(eff.ebi), sizeof(hgeEffectBasicInfo));

	CEmitterList * emitterItem = eff.eiList;
	while (emitterItem)
	{
		hgeEffectEmitterInfo eei;
		memcpy(&eei, &(emitterItem->emitter.eei), sizeof(hgeEffectEmitterInfo));
		AddEmitter(emitterItem->emitter.ID, &eei);

		CAffectorList * affectorItem = emitterItem->emitter.eaiList;
		while (affectorItem)
		{
			hgeEffectAffectorInfo eai;
			memcpy(&eai, &(affectorItem->affector.eai), sizeof(hgeEffectAffectorInfo));
			AddAffector(emitterItem->emitter.ID, affectorItem->affector.ID, &eai);
			affectorItem = affectorItem->next;
		}
		emitterItem = emitterItem->next;
	}
}

void hgeEffectSystem::InitEffectSystem(const char * filename, HTEXTURE tex, HTEXTURE * texset)
{
	InitEffectSystem();
	texnum = Load(filename, tex, texset);
}

hgeEffectSystem::hgeEffectSystem()
{
	ZeroMemory(this, sizeof(hgeEffectSystem));
	InitEffectSystem();
}

hgeEffectSystem::hgeEffectSystem(const hgeEffectSystem &eff)
{
	ZeroMemory(this, sizeof(hgeEffectSystem));
	InitEffectSystem(eff);
}

hgeEffectSystem::hgeEffectSystem(const char * filename, HTEXTURE tex, HTEXTURE * texset)
{
	ZeroMemory(this, sizeof(hgeEffectSystem));
	InitEffectSystem(filename, tex, texset);
}

hgeEffectSystem::~hgeEffectSystem()
{
	FreeList();
}

int hgeEffectSystem::Load(const char * filename, HTEXTURE tex /* = 0 */, HTEXTURE * texset /* = 0 */)
{
	if (!filename)
	{
		return -1;
	}
	BYTE * _content;
	DWORD _size;
	DWORD _offset = 0;
	WORD _ID = 0;
	_content = hge->Resource_Load(filename, &_size);
	if(!_content)
		return -1;
	memcpy(&(ebi), _content + _offset, sizeof(hgeEffectBasicInfo));
	texnum = ebi.tex.texindex;
/*
	if (tex.tex == 0)
	{*/

		if(texnum < 0/* || !texset[texnum].tex*/)
		{
			hge->Resource_Free(_content);
			return texnum;
		}
		HTEXTURE ttex(texnum, NULL);
		ebi.tex = ttex;
//		ebi.tex = texset[texnum];
/*
	}
	else
	{
		ebi.tex = tex;
	}*/

	_offset += sizeof(hgeEffectBasicInfo);
	while(_offset < _size)
	{
		memcpy(&_ID, _content + _offset, sizeof(WORD));
		_offset += sizeof(WORD);
		if((_ID & 0xff) == 0)
		{			
			hgeEffectEmitterInfo emitterInfo;
			memcpy(&emitterInfo, (hgeEffectEmitterInfo *)(_content + _offset), sizeof(hgeEffectEmitterInfo));

			AddEmitter(_ID>>8, &emitterInfo);
			_offset += sizeof(hgeEffectEmitterInfo);
		}
		else
		{
			hgeEffectAffectorInfo affectorInfo;
			memcpy(&affectorInfo, (hgeEffectAffectorInfo *)(_content + _offset), sizeof(hgeEffectAffectorInfo));
			
			AddAffector(_ID>>8, _ID & 0xff, &affectorInfo);
			_offset += sizeof(hgeEffectAffectorInfo);
		}
	}
	hge->Resource_Free(_content);
	return texnum;
}

bool hgeEffectSystem::Save(const char * filename, int _texnum /* = -1 */)
{
	if (_texnum >= 0)
	{
		texnum = _texnum;
	}
	if(!filename || texnum < 0)
		return false;
	FILE * efffile = fopen(hge->Resource_MakePath(filename), "wb");
	HTEXTURE _tex = ebi.tex;
	ebi.tex = (HTEXTURE)texnum;
	fwrite(&(ebi), sizeof(hgeEffectBasicInfo), 1, efffile);
	ebi.tex = _tex;

	WORD _eID = 0;
	WORD _aID = 0;

	CEmitterList * emitterItem = eiList;
	while(emitterItem)
	{
		_eID = (emitterItem->emitter.ID) << 8;
		fwrite(&_eID, sizeof(WORD), 1, efffile);
		fwrite(&(emitterItem->emitter.eei), sizeof(hgeEffectEmitterInfo), 1, efffile);

		CAffectorList * affectorItem = emitterItem->emitter.eaiList;
		while(affectorItem)
		{
			_aID = _eID | (affectorItem->affector.ID);
			fwrite(&_aID, sizeof(WORD), 1, efffile);
			fwrite(&(affectorItem->affector.eai), sizeof(hgeEffectAffectorInfo), 1, efffile);
			affectorItem = affectorItem->next;
		}
		emitterItem = emitterItem->next;
	}

	fclose(efffile);
	return true;
}

void hgeEffectSystem::FreeList()
{
	CEmitterList * emitterItem = eiList, *emitterNextItem;

	while(emitterItem)
	{
		if(emitterItem->emitter.sprite)
		{
			delete emitterItem->emitter.sprite;
			emitterItem->emitter.sprite = NULL;
		}
		if (emitterItem->emitter.nObj)
		{
			if (emitterItem->emitter.obj)
			{
				free(emitterItem->emitter.obj);
				emitterItem->emitter.obj = NULL;
			}
			emitterItem->emitter.nObj = 0;
		}
		CAffectorList * affectorItem = emitterItem->emitter.eaiList, *affectorNextItem;

		while(affectorItem)
		{
			affectorNextItem = affectorItem->next;
			delete affectorItem;
			affectorItem = affectorNextItem;
		}

		emitterNextItem = emitterItem->next;
		delete emitterItem;
		emitterItem = emitterNextItem;
	}

	eiList = NULL;
}

void hgeEffectSystem::Render(hge3DPoint *ptfar, DWORD colormask)
{
	CEmitterList * emitterItem = eiList;

	while(emitterItem)
	{
		hgeEffectObject * obj = emitterItem->emitter.obj;
		for(int i=0; i<emitterItem->emitter.nEffectObjectsAlive; i++)
		{
			hgeSprite * _sprite = emitterItem->emitter.sprite;
			if (_sprite)
			{
				_sprite->SetColor((/**(DWORD *)&*/(obj->color))&colormask);
				_sprite->SetZ(obj->z, obj->z + obj->zStretch, obj->z + obj->zStretch, obj->z, ptfar);
				_sprite->RenderEx(obj->x, obj->y, obj->fHeadDirection, obj->fScaleX, obj->fScaleY);
			}
			obj++;
		}
		emitterItem = emitterItem->next;
	}
}

void hgeEffectSystem::MoveTo(float _x, float _y, float _z, bool bForce)
{
	x = _x;
	y = _y;
	z = _z;
	if(bForce)
	{
		lastx = x;
		lasty = y;
		lastz = z;

		CEmitterList * emitterItem = eiList;

		while(emitterItem)
		{
			hgeEffectObject * obj = emitterItem->emitter.obj;
			for(int i=0; i<emitterItem->emitter.nEffectObjectsAlive; i++)
			{
				obj->x = _x;
				obj->y = _y;
				obj->z = _z;
				obj++;
			}
			emitterItem = emitterItem->next;
		}
	}
}

void hgeEffectSystem::Fire()
{
	Stop();
	nAge = HGEEFFECT_AGE_START;
	lastx = x;
	lasty = y;
	lastz = z;
}

void hgeEffectSystem::Stop(bool bKill)
{
	nAge = HGEEFFECT_AGE_STOP;

	CEmitterList * emitterItem = eiList;
	while (emitterItem)
	{
		emitterItem->emitter.nAge = HGEEFFECT_AGE_START;

		CAffectorList * affectorItem = emitterItem->emitter.eaiList;
		while (affectorItem)
		{
			affectorItem->affector.nAge = HGEEFFECT_AGE_START;
			affectorItem = affectorItem->next;
		}
		emitterItem = emitterItem->next;
	}

	if(bKill)
	{
		emitterItem = eiList;

		while(emitterItem)
		{
			emitterItem->emitter.nEffectObjectsAlive = 0;
			emitterItem = emitterItem->next;
		}
	}
}

void hgeEffectSystem::Update()
{
	if(nAge != HGEEFFECT_AGE_FOREVER && nAge != HGEEFFECT_AGE_STOP)
	{
		nAge++;
		if(nAge > ebi.nLifeTime)
		{
			if (ebi.nRepeatDelay > HGEEFFECT_AGE_ONCE)
			{
				Stop();
			}
			nDelayCounter++;
			if(nDelayCounter > ebi.nRepeatDelay)
			{
				nDelayCounter = 0;
				nAge = 0;
			}
		}
	}

	CEmitterList * emitterItem = eiList;
	while(emitterItem)
	{
		//Emitter
		hgeEffectEmitter * emitter = &(emitterItem->emitter);
		if(nAge == HGEEFFECT_AGE_START || nAge == HGEEFFECT_AGE_STOP)
		{
			emitter->nAge = HGEEFFECT_AGE_START;
			emitter->fEmissionResidue = 0;
		}
		else
			emitter->nAge++;
		hgeEffectObject * obj = emitterItem->emitter.obj;
		if(emitter->nAge > emitter->eei.nStartTime && emitter->nAge <= emitter->eei.nEndTime)
		{
			emitter->fEmissionResidue += emitter->eei.fEmitNum;
			while(emitter->fEmissionResidue >= 1.0f)
			{
				if(emitter->nEffectObjectsAlive >= emitter->nObj)
					break;
				hgeEffectObject * _obj = obj + emitter->nEffectObjectsAlive;
				ZeroMemory(_obj, sizeof(hgeEffectObject));
				//
				_obj->fScaleX = 1.0f;
				_obj->fScaleY = 1.0f;
				_obj->nLifeTime = hge->Random_Int(emitter->eei.nLfieTimeMin, emitter->eei.nLifeTimeMax, true);
				float _x, _y, _z;
				if(emitter->eei.fThetaStep)
				{
					float _r = (emitter->eei.fRadius - emitter->eei.fRadiusInner) / 2.0f;
					float _arc = emitter->eei.fThetaStart + (emitter->eei.fThetaStep) * (emitter->nAge);
					_x = hge->Random_Float(-_r, _r, true);
					_y = hge->Random_Float(-_r, _r, true);
					_r += emitter->eei.fRadiusInner;
					_x += _r * cosf(_arc);
					_y += _r * sinf(_arc);
				}
				else
				{
					if(emitter->eei.fRadiusInner)
					{
						float _r = hge->Random_Float(emitter->eei.fRadiusInner, emitter->eei.fRadius, true);
						float _arc = hge->Random_Float(0, M_PI * 2, true);
						_x = _r * cosf(_arc);
						_y = _r * sinf(_arc);
					}
					else
					{
						_x = hge->Random_Float(-emitter->eei.fRadius, emitter->eei.fRadius, true);
						_y = hge->Random_Float(-emitter->eei.fRadius, emitter->eei.fRadius, true);
					}
				}
				_z = 0;
				////////////////////////ROTATIONX////////////////////////
				if(emitter->eei.fRotationX)
				{
					_y = _y * cosf(emitter->eei.fRotationX);
					_z = - _y * sinf(emitter->eei.fRotationX);
				}
				////////////////////////ROTATIONY////////////////////////
				if(emitter->eei.fRotationY)
				{
					float _cosf = cosf(emitter->eei.fRotationY);
					float _sinf = sinf(emitter->eei.fRotationY);
					_x = _x * _cosf + _z * _sinf;
					_z = _x * _sinf - _z * _cosf;
				}
				_x += x;
				_y += y;
				_z += z;

				_obj->x = _x;
				_obj->y = _y;
				_obj->z = _z;
				emitter->nEffectObjectsAlive++;
				emitter->fEmissionResidue -= 1.0f;
			}
		}
		//Obj
		for(int i=0; i<emitter->nEffectObjectsAlive; i++)
		{
			float xmove = obj->x;
			float ymove = obj->y;
			obj->nAge++;
			if(obj->nAge > obj->nLifeTime)
			{
				emitter->nEffectObjectsAlive--;
				memcpy(obj, &(emitter->obj[emitter->nEffectObjectsAlive]), sizeof(hgeEffectObject));
				i--;
				continue;
			}
			//Affector
			CAffectorList * affectorItem = emitterItem->emitter.eaiList;

			while(affectorItem)
			{
				hgeEffectAffector * affector = &(affectorItem->affector);
				if(emitter->nAge == HGEEFFECT_AGE_START)
					affector->nAge = HGEEFFECT_AGE_START;
				else
					affector->nAge++;
				if(obj->nAge > affector->eai.nAffectorStartTime && obj->nAge <= affector->eai.nAffectorEndTime)
				{
					//Affect
					Affect(obj, affector);
				}
				affectorItem = affectorItem->next;
			}
			//Update
			obj->x += obj->fSpeedX;
			obj->y += obj->fSpeedY;
			obj->z += obj->fSpeedZ;
			//Trace
			if(emitter->eei.bTrace)
			{
				obj->x += (x - lastx) * (1.0f - emitter->eei.fTraceResistance);
				obj->y += (y - lasty) * (1.0f - emitter->eei.fTraceResistance);
				obj->z += (z - lastz) * (1.0f - emitter->eei.fTraceResistance);
			}
			//Raditial & Tangential
			if(obj->fSpeedRaditial || obj->fSpeedTangential)
			{
				hgeVector _obj3(obj->x, obj->y, obj->z);
				hgeVector _ori3(x, y, z);
				hgeVector _vec3 = _ori3 - _obj3;
				_vec3.Normalize();
				if(obj->fSpeedRaditial)
				{
					_obj3 += _vec3 * obj->fSpeedRaditial;
				}
				if(obj->fSpeedTangential)
				{
					float _x = 0.0f;
					float _y = 0.0f;
					float _z = 1.0f;
					////////////////////////ROTATIONX////////////////////////
					if(emitter->eei.fRotationX)
					{
						_y = sinf(emitter->eei.fRotationX);
						_z = - cosf(emitter->eei.fRotationX);
					}
					////////////////////////ROTATIONY////////////////////////
					if(emitter->eei.fRotationY)
					{
						_x = _z * sinf(emitter->eei.fRotationY);
						_z = - _z * cosf(emitter->eei.fRotationY);
					}
					hgeVector _up(_x, _y, _z);
					_vec3 = _vec3.Cross(&_up);
					_vec3.Normalize();
//					D3DXVec3Cross(&_vec3, &_vec3, &_up);
//					D3DXVec3Normalize(&_vec3, &_vec3);
					_obj3 += _vec3 * obj->fSpeedTangential;
				}
				obj->x = _obj3.x;
				obj->y = _obj3.y;
				obj->z = _obj3.z;
			}
			xmove = obj->x - xmove;
			ymove = obj->y - ymove;
			//Zvalue
//			if(obj->z > 0)
//				obj->z = - obj->z;
			//Adjust
			if(emitter->eei.bAdjustDirection)
			{
				if(xmove == 0)
				{
					if(ymove > 0)
					{
						obj->fHeadDirection = M_PI_2;
					}
					else if(ymove < 0)
					{
						obj->fHeadDirection = -M_PI_2;
					}
				}
				else
				{
					obj->fHeadDirection = atanf(ymove / xmove);
					if(xmove < 0)
						obj->fHeadDirection += M_PI;
				}
			}
			obj++;
		}
		emitterItem = emitterItem->next;
	}
	lastx = x;
	lasty = y;
	lastz = z;
}

void hgeEffectSystem::UpdateValue(float * value, float * bufferValue, hgeEffectAffectorInfo * eai, int nAge)
{
	bool updateBuffer = false;

	if(nAge == eai->nAffectorStartTime + 1)
	{
		*bufferValue = 0;
		updateBuffer = true;
		if(eai->bUseStartValue)
		{
			*value = hge->Random_Float(eai->fStartValueMin, eai->fStartValueMax, true);
		}
	}

	if (eai->nRandomPickInterval > 0 && (eai->nRandomPickInterval == 1 || (nAge % eai->nRandomPickInterval) == 1))
	{
		updateBuffer = true;
	}

	if(eai->bUseEndValue)
	{
		if(updateBuffer)
		{
			*bufferValue = hge->Random_Float(eai->fEndValueMin, eai->fEndValueMax, true);
		}
		if(eai->nAffectorEndTime > nAge)
		{
			*value += ((*bufferValue) - (*value)) / (eai->nAffectorEndTime - nAge);
		}
		else
		{
			*value = *bufferValue;
		}
	}
	else
	{
		if (updateBuffer)
		{
			*bufferValue = hge->Random_Float(eai->fIncrementValueMin, eai->fIncrementValueMax, true);
		}
		*value += (eai->fIncrementScale) * (*bufferValue) + eai->fAcceleration * (nAge - eai->nAffectorStartTime);
	}
}

void hgeEffectSystem::UpdateColorValue(DWORD * value, DWORD * bufferValue, hgeEffectAffectorInfo * eai, int nAge)
{
	DWORD * col = (DWORD *)value;
	DWORD * buffercol = (DWORD *)bufferValue;

	int _a = GETA(*col);
	int _r = GETR(*col);
	int _g = GETG(*col);
	int _b = GETB(*col);
	int _buffera = GETA(*buffercol);
	int _bufferr = GETR(*buffercol);
	int _bufferg = GETG(*buffercol);
	int _bufferb = GETB(*buffercol);

	bool updateBuffer = false;
	if(nAge == eai->nAffectorStartTime + 1)
	{
		*(DWORD *)bufferValue = 0;
		updateBuffer = true;
		if (eai->bUseStartValue)
		{
			DWORD scolmin = *(DWORD *)(&eai->fStartValueMin);
			DWORD scolmax = *(DWORD *)(&eai->fStartValueMax);

			_a = hge->Random_Int(GETA(scolmin), GETA(scolmax), true);
			_r = hge->Random_Int(GETR(scolmin), GETR(scolmax), true);
			_g = hge->Random_Int(GETG(scolmin), GETG(scolmax), true);
			_b = hge->Random_Int(GETB(scolmin), GETB(scolmax), true);
		}
	}

	if (eai->nRandomPickInterval > 0 && (eai->nRandomPickInterval == 1 || (nAge % eai->nRandomPickInterval) == 1))
	{
		updateBuffer = true;
	}
	if(eai->bUseEndValue)
	{
		if(updateBuffer)
		{
			DWORD ecolmin = *(DWORD *)(&eai->fEndValueMin);
			DWORD ecolmax = *(DWORD *)(&eai->fEndValueMax);
			_buffera = hge->Random_Int(GETA(ecolmin), GETA(ecolmax), true);
			_bufferr = hge->Random_Int(GETR(ecolmin), GETR(ecolmax), true);
			_bufferg = hge->Random_Int(GETG(ecolmin), GETG(ecolmax), true);
			_bufferb = hge->Random_Int(GETB(ecolmin), GETB(ecolmax), true);
		}		
		if(eai->nAffectorEndTime > nAge)
		{
			int divisor = eai->nAffectorEndTime - nAge;
			_a += (_buffera - (int)(GETA(*col))) / divisor;
			_r += (_bufferr - (int)(GETR(*col))) / divisor;
			_g += (_bufferg - (int)(GETG(*col))) / divisor;
			_b += (_bufferb - (int)(GETB(*col))) / divisor;
		}
		else
		{
			_a = _buffera;
			_r = _bufferr;
			_g = _bufferg;
			_b = _bufferb;
		}
	}
	else
	{
		if (updateBuffer)
		{
			DWORD acolmin = *(DWORD *)(&eai->fIncrementValueMin);
			DWORD acolmax = *(DWORD *)(&eai->fIncrementValueMax);

			_buffera = hge->Random_Int(GETA(acolmin), GETA(acolmax), true);
			_bufferr = hge->Random_Int(GETR(acolmin), GETR(acolmax), true);
			_bufferg = hge->Random_Int(GETG(acolmin), GETG(acolmax), true);
			_bufferb = hge->Random_Int(GETB(acolmin), GETB(acolmax), true);
		}
		DWORD * accelcol = (DWORD *)&(eai->fAcceleration);
		int _age = nAge - eai->nAffectorStartTime;
		_a += (int)((eai->fIncrementScale) * _buffera + GETA(*accelcol) * _age);
		_r += (int)((eai->fIncrementScale) * _bufferr + GETR(*accelcol) * _age);
		_g += (int)((eai->fIncrementScale) * _bufferg + GETG(*accelcol) * _age);
		_b += (int)((eai->fIncrementScale) * _bufferb + GETB(*accelcol) * _age);

	}
	if(_a > 0xff)
		_a = 0xff;
	else if(_a < 0)
		_a = 0;
	if(_r > 0xff)
		_r = 0xff;
	else if(_r < 0)
		_r = 0;
	if(_g > 0xff)
		_g = 0xff;
	else if(_g < 0)
		_g = 0;
	if(_b > 0xff)
		_b = 0xff;
	else if(_b < 0)
		_b = 0;

	if(_buffera > 0xff)
		_buffera = 0xff;
	else if(_buffera < 0)
		_buffera = 0;
	if(_bufferr > 0xff)
		_bufferr = 0xff;
	else if(_bufferr < 0)
		_bufferr = 0;
	if(_bufferg > 0xff)
		_bufferg = 0xff;
	else if(_bufferg < 0)
		_bufferg = 0;
	if(_bufferb > 0xff)
		_bufferb = 0xff;
	else if(_bufferb < 0)
		_bufferb = 0;

	*col = (_a<<24) | (_r<<16) | (_g<<8) | _b;
	*buffercol = (_buffera<<24) | (_bufferr<<16) | (_bufferg<<8) | _bufferb;
}

void hgeEffectSystem::Affect(hgeEffectObject * obj, hgeEffectAffector * affector)
{
	//value
	float nullValue = 0;
	hgeEffectAffectorInfo * eai = &(affector->eai);
	//
	switch(affector->eai.type)
	{
	case HGEEFFECT_AFFECTORTYPE_SPIN:
		UpdateValue(&(obj->fHeadDirection), &(obj->fHeadDirectionBuffer), eai, obj->nAge);
		break;
	case HGEEFFECT_AFFECTORTYPE_SPEEDRADIAL:
		UpdateValue(&(obj->fSpeedRaditial), &(obj->fSpeedRaditialBuffer), eai, obj->nAge);
		break;
	case HGEEFFECT_AFFECTORTYPE_SPEEDTANGENTIAL:
		UpdateValue(&(obj->fSpeedTangential), &(obj->fSpeedTangentialBuffer), eai, obj->nAge);
		break;
	case HGEEFFECT_AFFECTORTYPE_SPEED_X:
		UpdateValue(&(obj->fSpeedX), &(obj->fSpeedXBuffer), eai, obj->nAge);
		break;
	case HGEEFFECT_AFFECTORTYPE_SPEED_Y:
		UpdateValue(&(obj->fSpeedY), &(obj->fSpeedYBuffer), eai, obj->nAge);
		break;
	case HGEEFFECT_AFFECTORTYPE_SPEED_Z:
		UpdateValue(&(obj->fSpeedZ), &(obj->fSpeedZBuffer), eai, obj->nAge);
		break;
	case HGEEFFECT_AFFECTORTYPE_SCALE:
		nullValue = obj->fScaleX;
		UpdateValue(&(obj->fScaleX), &(obj->fScaleXBuffer), eai, obj->nAge);
		if(nullValue != 0)
		{
			obj->fScaleY *= obj->fScaleX / nullValue;
		}
		else
			obj->fScaleY = obj->fScaleX;
		break;
	case HGEEFFECT_AFFECTORTYPE_SCALE_X:
		UpdateValue(&(obj->fScaleX), &(obj->fScaleXBuffer), eai, obj->nAge);
		break;
	case HGEEFFECT_AFFECTORTYPE_SCALE_Y:
		UpdateValue(&(obj->fScaleY), &(obj->fScaleYBuffer), eai, obj->nAge);
		break;
	case HGEEFFECT_AFFECTORTYPE_ZSTRETCH:
		UpdateValue(&(obj->zStretch), &(obj->zStretchBuffer), eai, obj->nAge);
		break;
	case HGEEFFECT_AFFECTORTYPE_COLOR:
		UpdateColorValue(&(obj->color), &(obj->colorBuffer), eai, obj->nAge);
		break;
	}
}

bool hgeEffectSystem::SetBasicInfo(hgeEffectBasicInfo * _ebi)
{
	memcpy(&ebi, _ebi, sizeof(hgeEffectBasicInfo));
	return true;
}

bool hgeEffectSystem::AddEmitter(hgeEffectEmitter * emitter)
{
	DeleteEmitter(emitter->ID);

	CEmitterList * emitterItem = new CEmitterList;

	memcpy(&(emitterItem->emitter), emitter, sizeof(hgeEffectEmitter));

	emitter = &(emitterItem->emitter);

	emitter->sprite = new hgeSprite(ebi.tex, emitter->eei.fTextureX, emitter->eei.fTextureY, emitter->eei.fTextureW, emitter->eei.fTextureH);
	emitter->sprite->SetBlendMode(emitter->eei.blend);
	emitter->sprite->SetHotSpot(emitter->eei.fHotX, emitter->eei.fHotY);

	emitter->nObj = emitter->eei.fEmitNum * emitter->eei.nLifeTimeMax + 1;
	if (emitter->nObj > MAX_EFFECTS || emitter->nObj <= 1)
	{
		emitter->nObj = MAX_EFFECTS;
	}
	emitter->obj = (hgeEffectObject *)malloc(sizeof(hgeEffectObject) * emitter->nObj);

	emitterItem->next = eiList;
	eiList = emitterItem;

	return true;
}

bool hgeEffectSystem::AddEmitter(BYTE emitterID, hgeEffectEmitterInfo * emitterInfo)
{
	hgeEffectEmitter emitter;
	ZeroMemory(&emitter, sizeof(hgeEffectEmitter));
	emitter.ID = emitterID;
	memcpy(&(emitter.eei), emitterInfo, sizeof(hgeEffectEmitterInfo));
	return AddEmitter(&emitter);
}

bool hgeEffectSystem::DeleteEmitter(BYTE emitterID)
{
	CEmitterList * emitterItem = eiList, *emitterPrevItem = NULL;

	while(emitterItem)
	{
		if(emitterItem->emitter.ID != emitterID)
		{
			emitterPrevItem = emitterItem;
			emitterItem = emitterItem->next;
			continue;
		}

		if(emitterItem->emitter.sprite)
		{
			delete emitterItem->emitter.sprite;
			emitterItem->emitter.sprite = NULL;
		}
		if (emitterItem->emitter.nObj)
		{
			if (emitterItem->emitter.obj)
			{
				free(emitterItem->emitter.obj);
				emitterItem->emitter.obj = NULL;
			}
			emitterItem->emitter.nObj = 0;
		}
		CAffectorList * affectorItem = emitterItem->emitter.eaiList, *affectorNextItem;

		while(affectorItem)
		{
			affectorNextItem = affectorItem->next;
			delete affectorItem;
			affectorItem = affectorNextItem;
		}

		if(emitterPrevItem == NULL)
			eiList = emitterItem->next;
		else
			emitterPrevItem->next = emitterItem->next;
		delete emitterItem;

		return true;
	}

	return false;
}

bool hgeEffectSystem::AddAffector(BYTE emitterID, hgeEffectAffector * affector)
{
	DeleteAffector(emitterID, affector->ID);

	CEmitterList * emitterItem = eiList;

	while(emitterItem)
	{
		if(emitterItem->emitter.ID == emitterID)
		{
			CAffectorList * affectorItem = new CAffectorList;

			memcpy(&(affectorItem->affector), affector, sizeof(hgeEffectAffector));
			affectorItem->next = emitterItem->emitter.eaiList;
			emitterItem->emitter.eaiList = affectorItem;
			return true;
		}
		emitterItem = emitterItem->next;
	}
	return false;
}

bool hgeEffectSystem::AddAffector(BYTE emitterID, BYTE affectorID, hgeEffectAffectorInfo * affectorInfo)
{
	hgeEffectAffector affector;
	ZeroMemory(&affector, sizeof(hgeEffectAffector));
	affector.ID = affectorID;
	memcpy(&(affector.eai), affectorInfo, sizeof(hgeEffectAffectorInfo));
	return AddAffector(emitterID, &affector);
}

bool hgeEffectSystem::DeleteAffector(BYTE emitterID, BYTE affectorID)
{
	CEmitterList * emitterItem = eiList;

	while(emitterItem)
	{
		if(emitterItem->emitter.ID == emitterID)
		{
			CAffectorList * affectorItem = emitterItem->emitter.eaiList, *affectorPrevItem = NULL;

			while(affectorItem)
			{
				if(affectorItem->affector.ID != affectorID)
				{
					affectorPrevItem = affectorItem;
					affectorItem = affectorItem->next;
					continue;
				}
				if(affectorPrevItem == NULL)
					emitterItem->emitter.eaiList = affectorItem->next;
				else
					affectorPrevItem->next = affectorItem->next;
				delete affectorItem;
				return true;
			}
		}
		emitterItem = emitterItem->next;
	}
	return false;
}

void * hgeEffectSystem::GetEmitterInfoValuePointer(BYTE emitterID, BYTE type)
{
	if(type >= HGEEFFECT_EI_END)
		return NULL;

	CEmitterList * emitterItem = eiList;

	while(emitterItem)
	{
		if(emitterItem->emitter.ID == emitterID)
		{
			hgeEffectEmitterInfo * eei = &(emitterItem->emitter.eei);
			switch(type)
			{
			case HGEEFFECT_EI_NSTARTTIME:
				return &(eei->nStartTime);
			case HGEEFFECT_EI_NENDTIME:
				return &(eei->nEndTime);
			case HGEEFFECT_EI_NLIFETIMEMIN:
				return &(eei->nLfieTimeMin);
			case HGEEFFECT_EI_NLIFETIMEMAX:
				return &(eei->nLifeTimeMax);
			case HGEEFFECT_EI_FEMITNUM:
				return &(eei->fEmitNum);
			case HGEEFFECT_EI_FROTATIONX:
				return &(eei->fRotationX);
			case HGEEFFECT_EI_FROTATIONY:
				return &(eei->fRotationY);
			case HGEEFFECT_EI_FRADIUS:
				return &(eei->fRadius);
			case HGEEFFECT_EI_FRADIUSINNER:
				return &(eei->fRadiusInner);
			case HGEEFFECT_EI_FTHETASTART:
				return &(eei->fThetaStart);
			case HGEEFFECT_EI_FTHETASTEP:
				return &(eei->fThetaStep);
			case HGEEFFECT_EI_FTRACERESISTANCE:
				return &(eei->fTraceResistance);
			case HGEEFFECT_EI_FTEXTUREX:
				return &(eei->fTextureX);
			case HGEEFFECT_EI_FTEXTUREY:
				return &(eei->fTextureY);
			case HGEEFFECT_EI_FTEXTUREW:
				return &(eei->fTextureW);
			case HGEEFFECT_EI_FTEXTUREH:
				return &(eei->fTextureH);
			case HGEEFFECT_EI_FHOTX:
				return &(eei->fHotX);
			case HGEEFFECT_EI_FHOTY:
				return &(eei->fHotY);
			case HGEEFFECT_EI_BLEND:
				return &(eei->blend);
			case HGEEFFECT_EI_BTRACE:
				return &(eei->bTrace);
			case HGEEFFECT_EI_BADJUSTDIRECTION:
				return &(eei->bAdjustDirection);
			}
			return NULL;
		}
		emitterItem = emitterItem->next;
	}
	return NULL;
}

void * hgeEffectSystem::GetAffectorInfoValuePointer(BYTE emitterID, BYTE affectorID, BYTE type)
{
	if(type >= HGEEFFECT_AI_END)
		return NULL;

	CEmitterList * emitterItem = eiList;

	while(emitterItem)
	{
		if(emitterItem->emitter.ID == emitterID)
		{
			CAffectorList * affectorItem = emitterItem->emitter.eaiList;

			while(affectorItem)
			{
				if(affectorItem->affector.ID == affectorID)
				{
					hgeEffectAffectorInfo * eai = &(affectorItem->affector.eai);
					switch(type)
					{
					case HGEEFFECT_AI_NAFFECTORSTARTTIME:
						return &(eai->nAffectorStartTime);
					case HGEEFFECT_AI_NAFFECTORENDTIME:
						return &(eai->nAffectorEndTime);
					case HGEEFFECT_AI_NRANDOMPICKINTERVAL:
						return &(eai->nRandomPickInterval);
					case HGEEFFECT_AI_FSTARTVALUEMIN:
						return &(eai->fStartValueMin);
					case HGEEFFECT_AI_FSTARTVALUEMAX:
						return &(eai->fStartValueMax);
					case HGEEFFECT_AI_FENDVALUEMIN:
						return &(eai->fEndValueMin);
					case HGEEFFECT_AI_FENDVALUEMAX:
						return &(eai->fEndValueMax);
					case HGEEFFECT_AI_FINCREMENTVALUEMIN:
						return &(eai->fIncrementValueMin);
					case HGEEFFECT_AI_FINCREMENTVALUEMAX:
						return &(eai->fIncrementValueMax);
					case HGEEFFECT_AI_FINCREMENTSCALE:
						return &(eai->fIncrementScale);
					case HGEEFFECT_AI_FACCELERATION:
						return &(eai->fAcceleration);
					case HGEEFFECT_AI_BUSESTARTVALUE:
						return &(eai->bUseStartValue);
					case HGEEFFECT_AI_BUSEENDVALUE:
						return &(eai->bUseEndValue);
					case HGEEFFECT_AI_TYPE:
						return &(eai->type);
					}
					return NULL;
				}
				affectorItem = affectorItem->next;
			}
		}
		emitterItem = emitterItem->next;
	}
	return NULL;
}

int hgeEffectSystem::GetEmitterAge(BYTE emitterID)
{
	CEmitterList * emitterItem = eiList;

	while(emitterItem)
	{
		if(emitterItem->emitter.ID == emitterID)
		{
			return emitterItem->emitter.nAge;
		}
		emitterItem = emitterItem->next;
	}
	return 0;
}

int hgeEffectSystem::GetAffectorAge(BYTE emitterID, BYTE affectorID)
{
	CEmitterList * emitterItem = eiList;

	while(emitterItem)
	{
		if(emitterItem->emitter.ID == emitterID)
		{
			CAffectorList * affectorItem = emitterItem->emitter.eaiList;

			while(affectorItem)
			{
				if(affectorItem->affector.ID == affectorID)
				{
					return affectorItem->affector.nAge;
				}
				affectorItem = affectorItem->next;
			}
		}
		emitterItem = emitterItem->next;
	}
	return 0;
}

int hgeEffectSystem::GetEffectObjectAlive(BYTE emitterID, int * nobj)
{
	int nAlive = 0;
	if (nobj)
	{
		*nobj = 0;
	}

	CEmitterList * emitterItem = eiList;

	while(emitterItem)
	{
		if(!emitterID)
		{
			if (nobj)
			{
				*nobj += emitterItem->emitter.nObj;
			}
			nAlive += emitterItem->emitter.nEffectObjectsAlive;
		}
		else if(emitterItem->emitter.ID == emitterID)
		{
			if (nobj)
			{
				*nobj = emitterItem->emitter.nObj;
			}
			return emitterItem->emitter.nEffectObjectsAlive;
		}
		emitterItem = emitterItem->next;
	}
	return nAlive;
}
