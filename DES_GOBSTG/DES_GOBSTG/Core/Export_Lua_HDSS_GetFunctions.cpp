#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "../Header/Export_Lua_HDSS_CallGet.h"
#include "../Header/processPrep.h"

#include "../Header/Export_Lua_HDSS_CallGetDefine.h"

int _HDSSCallGet::Get_D(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _index = _INEXT_HDSS_LUAFUNC;
		if (Scripter::scr.d[_index].bfloat)
		{
			_PD_HDSS_LUA(CUINT(Scripter::scr.d[_index].value));
		}
		else
		{
			_PI_HDSS_LUA(CAST(Scripter::scr.d[_index]));
		}
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_Du(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _index = _INEXT_HDSS_LUAFUNC;
		_PD_HDSS_LUA(UCAST(Scripter::scr.d[_index]));
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_RANK(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (true)
	{
		_PI_HDSS_LUA(Player::rank);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_CHARA(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;
		_PI_HDSS_LUA(Player::p.ID);
		_PI_HDSS_LUA(Process::mp.lastmatchchara);
		return 2;
	}
	return 0;
}

int _HDSSCallGet::Get_SCENE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (true)
	{
		_PI_HDSS_LUA(Process::mp.stage);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_REPLAYMODE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (true)
	{
		_PB_HDSS_LUA(Process::mp.replaymode);
		_PB_HDSS_LUA(Process::mp.replayend);
		return 2;
	}
	return 0;
}

int _HDSSCallGet::Get_SELCOMPLETE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _selsys = _INEXT_HDSS_LUAFUNC;

		bool _bclearaftercomplete = true;
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_bclearaftercomplete = _IOBJ_HDSS_LUA;
		}

		if (_selsys >= 0 && _selsys < SELSYSTEMMAX)
		{
			_PB_HDSS_LUA(SelectSystem::selsys[_selsys].complete);
			_PI_HDSS_LUA(SelectSystem::selsys[_selsys].select);
			if (SelectSystem::selsys[_selsys].complete && _bclearaftercomplete)
			{
				SelectSystem::selsys[_selsys].Clear();
			}
			return 2;
		}
	}
	return 0;
}

int _HDSSCallGet::Get_ENX(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _enindex = Enemy::en.getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_enindex].x);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ENY(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _enindex = Enemy::en.getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_enindex].y);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ENSPEED(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _enindex = Enemy::en.getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_enindex].speed);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ENLEVEL(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _enindex = Enemy::en.getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_enindex].level);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ENAIMX(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _enindex = Enemy::en.getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_enindex].aim.x);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ENAIMY(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _enindex = Enemy::en.getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_enindex].aim.y);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ENAIMANGLE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _enindex = Enemy::en.getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_enindex].aimangle);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ENLIFE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _enindex = Enemy::en.getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_enindex].life);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ENI(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		_PI_HDSS_LUA(Enemy::en.getIndex());
		_PI_HDSS_LUA(Enemy::bossindex);
		return 2;
	}
	return 0;
}

int _HDSSCallGet::Get_ENANGLE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _enindex = Enemy::en.getIndex();
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_enindex = _IOBJ_HDSS_LUA;
		}
		_PF_HDSS_LUA(Enemy::en[_enindex].angle);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ENNUM(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 2)
	{
		_INEXT_HDSS_LUAFUNC;

		int _set = _INEXT_HDSS_LUAFUNC;
		int iret = 0;
		if (_set < 0 || _set >= ENEMY_NMAXSETMAX)
		{
			for (int i=0; i<ENEMY_NMAXSETMAX; i++)
			{
				iret += Enemy::nEnemyNow[i];
			}
		}
		else
		{
			iret = Enemy::nEnemyNow[_set];
		}
		_PI_HDSS_LUA(iret);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_SEED(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (true)
	{
		_PI_HDSS_LUA(Process::mp.seed);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_SINA(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _angle = _INEXT_HDSS_LUAFUNC;
		_PF_HDSS_LUA(sint(_angle));
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_COSA(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _angle = _INEXT_HDSS_LUAFUNC;
		_PF_HDSS_LUA(cost(_angle));
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_TANA(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _angle = _INEXT_HDSS_LUAFUNC;
		_PF_HDSS_LUA(tant(_angle));
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ASINA2(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 2)
	{
		float _x = _FNEXT_HDSS_LUAFUNC;
		float _y = _FNEXT_HDSS_LUAFUNC;
		_PI_HDSS_LUA(asin2t(_x, _y));
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ACOSA2(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 2)
	{
		float _x = _FNEXT_HDSS_LUAFUNC;
		float _y = _FNEXT_HDSS_LUAFUNC;
		_PI_HDSS_LUA(acos2t(_x, _y));
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ATAN2(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 2)
	{
		float _x = _FNEXT_HDSS_LUAFUNC;
		float _y = _FNEXT_HDSS_LUAFUNC;
		_PI_HDSS_LUA(atan2t(_x, _y));
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_SIGN(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _x = _INEXT_HDSS_LUAFUNC;
		_PI_HDSS_LUA(SIGN(_x));
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_ROLL(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 2)
	{
		int _x = _INEXT_HDSS_LUAFUNC;
		int _t = _INEXT_HDSS_LUAFUNC;
		_PI_HDSS_LUA(ROLL(_x, _t));
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_REGANGLE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _angle = _INEXT_HDSS_LUAFUNC;
		while(_angle > 18000)
		{
			_angle -= 36000;
		}
		while(_angle < -18000)
		{
			_angle += 36000;
		}
		_PI_HDSS_LUA(_angle);
		return 1;
	}
	return 0;
}


int _HDSSCallGet::Get_CHECKKEY(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 2)
	{
		int _ksi = _INEXT_HDSS_LUAFUNC;
		int _type = DIKEY_PRESSED;
		_JNEXT_HDSS_LUAFUNC;
		if (bhavenext)
		{
			_type = _IOBJ_HDSS_LUA;
		}
		bool bret = GameInput::GetKey(_ksi, _type);
		_PB_HDSS_LUA(bret);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_PX(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		_PF_HDSS_LUA(Player::p.x);
		_PI_HDSS_LUA(Player::p.ID);
		return 2;
	}
	return 0;
}

int _HDSSCallGet::Get_PY(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		_PF_HDSS_LUA(Player::p.y);
		_PI_HDSS_LUA(Player::p.ID);
		return 2;
	}
	return 0;
}

int _HDSSCallGet::Get_PLIFE(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		_PI_HDSS_LUA(Player::p.nLife);
		_PI_HDSS_LUA(Player::p.initlife);
		return 2;
	}
	return 0;
}

int _HDSSCallGet::Get_PBDRAIN(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		_PB_HDSS_LUA(Player::p.bDrain);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_PBINFI(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_PB_HDSS_LUA(Player::p.bInfi);
		_PI_HDSS_LUA(Player::p.infireasonflag);
		_PI_HDSS_LUA(Player::p.infitimer);
		return 3;
	}
	return 0;
}

int _HDSSCallGet::Get_PGX(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _index = _INEXT_HDSS_LUAFUNC;
		_PF_HDSS_LUA(Player::p.pg[_index].x);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_PGY(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		_INEXT_HDSS_LUAFUNC;

		BYTE _index = _INEXT_HDSS_LUAFUNC;
		_PF_HDSS_LUA(Player::p.pg[_index].y);
		return 1;
	}
	return 0;
}

int _HDSSCallGet::Get_BGSINDEX(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 2)
	{
		_INEXT_HDSS_LUAFUNC;

		int _set = _INEXT_HDSS_LUAFUNC;
//		_PI_HDSS_LUA(BGLayer::bglayerset[_set].sID);
//		_PI_HDSS_LUA(BGLayer::bglayerset[_set].timer);
		return 2;
	}
	return 0;
}

int _HDSSCallGet::Get_SEL(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _selsys = _INEXT_HDSS_LUAFUNC;
		if (_selsys >= 0 && _selsys < SELSYSTEMMAX)
		{
			_PI_HDSS_LUA(SelectSystem::selsys[_selsys].select);
			return 1;
		}
	}
	return 0;
}

int _HDSSCallGet::Get_SELFIRSTID(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (argscount > 1)
	{
		int _selsys = _INEXT_HDSS_LUAFUNC;
		if (_selsys >= 0 && _selsys < SELSYSTEMMAX)
		{
			_PI_HDSS_LUA(SelectSystem::selsys[_selsys].firstID);
			return 1;
		}
	}
	return 0;
}

int _HDSSCallGet::Get_CHATI(LuaState * ls)
{
	_ENTERGET_HDSS_LUA;
	if (true)
	{
		_PI_HDSS_LUA(Chat::chatitem.chati);
		return 1;
	}
	return 0;
}

#endif
#endif