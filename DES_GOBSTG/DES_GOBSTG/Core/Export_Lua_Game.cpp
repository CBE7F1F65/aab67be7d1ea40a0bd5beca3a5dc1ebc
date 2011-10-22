#ifndef __NOTUSELUA
#ifndef __NOTINTHISGAME

#include "../Header/Export_Lua_Game.h"
#include "../Header/processPrep.h"

bool Export_Lua_Game::_LuaRegistConst(LuaObject * obj)
{
	return true;
}

bool Export_Lua_Game::_LuaRegistFunction(LuaObject * obj)
{
	LuaObject _gameobj;
	_gameobj = obj->CreateTable("game");

	_gameobj.Register("Random_Int", LuaFn_Game_Random_Int);
	_gameobj.Register("Random_Float", LuaFn_Game_Random_Float);
	_gameobj.Register("SetGameMode", LuaFn_Game_SetGameMode);
	_gameobj.Register("GetGameMode", LuaFn_Game_GetGameMode);
	_gameobj.Register("GetPlayerContentTable", LuaFn_Game_GetPlayerContentTable);
	_gameobj.Register("GetPlayerStopInfo", LuaFn_Game_GetPlayerStopInfo);
	_gameobj.Register("GetEnumReplayInfo", LuaFn_Game_GetEnumReplayInfo);
	_gameobj.Register("SetEnumReplayByIndex", LuaFn_Game_SetEnumReplayByIndex);
	_gameobj.Register("GetEdefInfo", LuaFn_Game_GetEdefInfo);
	_gameobj.Register("GetPlayerMoveInfo", LuaFn_Game_GetPlayerMoveInfo);
	_gameobj.Register("FreeTexture", LuaFn_Game_LoadTexture);
	_gameobj.Register("FreeTexture", LuaFn_Game_FreeTexture);

	return true;
}

int Export_Lua_Game::LuaFn_Game_Random_Int(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int _imin = 0;
	int _imax = RAND_MAX;
	int _seed;
	int * _pseed = NULL;

	node.jNextGet();
	if (node.bhavenext)
	{
		_imin = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_imax = node.iGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				_seed = node.iGet();
				_pseed = &_seed;
			}
		}
	}

	int _iret = randt(_imin, _imax, _pseed);
	node.PInt(_iret);
	if (_pseed)
	{
		node.PInt(_seed);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_Random_Float(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	float _fmin = 0.0f;
	float _fmax = 1.0f;
	int _seed;
	int * _pseed = NULL;

	node.jNextGet();
	if (node.bhavenext)
	{
		_fmin = node.fGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_fmax = node.fGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				_seed = node.iGet();
				_pseed = &_seed;
			}
		}
	}

	float _fret = randtf(_fmin, _fmax, _pseed);
	node.PFloat(_fret);
	if (_pseed)
	{
		node.PInt(_seed);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetGameMode(LuaState * ls)
{
	LuaStack args(ls);

	BYTE _mode = args[1].GetInteger();
	Process::mp.SetMatchMode(_mode);
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetGameMode(LuaState * ls)
{
	BYTE _mode = Process::mp.GetMatchMode();
	ls->PushInteger(_mode);
	return 1;
}

int Export_Lua_Game::LuaFn_Game_GetPlayerContentTable(LuaState * ls)
{
	LuaStack args(ls);
	if (!args.Count())
	{
		int _playercount = DATASTRUCT_PLAYERTYPEMAX;
		for (int i=0; i<DATASTRUCT_PLAYERTYPEMAX; i++)
		{
			if (!strlen(BResource::bres.playerdata[i].name))
			{
				_playercount = i;
				break;
			}
		}
		ls->PushInteger(_playercount);
		return 1;
	}
	else
	{
		int _index = args[1].GetInteger();
		ls->PushInteger(BResource::bres.playerdata[_index].faceSIID);
		_LuaHelper_PushString(ls, BResource::bres.playerdata[_index].name);
		_LuaHelper_PushString(ls, BResource::bres.playerdata[_index].ename);
		return 3;
	}
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetPlayerStopInfo(LuaState * ls)
{
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetEnumReplayInfo(LuaState * ls)
{
	LuaStack args(ls);

	int _index = args[1].GetInteger();
	_index = Replay::nenumrpy - _index - 1;
	if (_index >= RPYENUMMAX || _index < 0)
	{
		ls->PushString("");
		return 1;
	}

	LuaStackObject _table = ls->CreateTable();
	_table.SetInteger("year", Replay::enumrpy[_index].rpyinfo.year);
	_table.SetInteger("month", Replay::enumrpy[_index].rpyinfo.month);
	_table.SetInteger("day", Replay::enumrpy[_index].rpyinfo.day);
	LuaStackObject _usernametable = _table.CreateTable("username");
	LuaStackObject _usingcharatable = _table.CreateTable("usingchara");
	_usernametable.SetString(1, Replay::enumrpy[_index].rpyinfo.username);
	LuaStackObject _usingcharasubtable = _usingcharatable.CreateTable(1);
	for (int j=0; j<M_PL_ONESETPLAYER; j++)
	{
		_usingcharasubtable.SetString(j+1, Data::data.getPlayerName(Replay::enumrpy[_index].rpyinfo.usingchara[j]));
	}
	ls->PushString(Replay::enumrpy[_index].filename);
	ls->PushValue(_table);
	return 2;
}

int Export_Lua_Game::LuaFn_Game_SetEnumReplayByIndex(LuaState * ls)
{
	LuaStack args(ls);

	int _index = args[1].GetInteger();
	_index = Replay::nenumrpy - _index - 1;
	if (_index >= RPYENUMMAX || _index < 0)
	{
		return 0;
	}

	if (strlen(Replay::enumrpy[_index].filename))
	{
		strcpy(Process::mp.rpyfilename, Replay::enumrpy[_index].filename);
		Process::mp.replaymode = true;
	}
	return 0;
}

int Export_Lua_Game::LuaFn_Game_GetEdefInfo(LuaState * ls)
{
	LuaStack args(ls);
	int _name = args[1].GetInteger();
//	 = 0;
	WORD _eID = _name & 0xffff;
	ls->PushInteger(0);
	ls->PushInteger(_eID);
	ls->PushInteger((*Enemy::en).level);
	ls->PushNumber((*Enemy::en).x);
	ls->PushNumber((*Enemy::en).y);
	ls->PushNumber(Player::p.x);
	ls->PushNumber(Player::p.y);
	return 7;
}

int Export_Lua_Game::LuaFn_Game_GetPlayerMoveInfo(LuaState * ls)
{
	LuaStack args(ls);
	int argscount = args.Count();
	int _lastindex = 0;
	if (argscount > 1)
	{
		_lastindex = args[2].GetInteger();
	}
	float _lastx = Player::p.lastx[_lastindex];
	float _lasty = Player::p.lasty[_lastindex];
	float _lastmx = Player::p.lastmx[_lastindex];
	float _lastmy = Player::p.lastmy[_lastindex];
	int _moveangle = BObject::AMainAngle(_lastmx, _lastmy, Player::p.x, Player::p.y);
	bool _moved = true;
	if (_lastmx == Player::p.x && _lastmy == Player::p.y)
	{
		_moved = false;
	}
	ls->PushNumber(_lastx);
	ls->PushNumber(_lasty);
	ls->PushNumber(_lastmx);
	ls->PushNumber(_lastmy);
	ls->PushInteger(_moveangle);
	ls->PushBoolean(_moved);
	return 6;
}

int Export_Lua_Game::LuaFn_Game_LoadTexture(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int _texindex = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_texindex = node.iGet();
	}

	bool bret = BResource::bres.LoadTexture(_texindex);
	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_FreeTexture(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

#ifndef __WIN32

	int _texindex = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_texindex = node.iGet();
	}

	bool bret = BResource::bres.FreeTexture(_texindex);
	node.PBoolean(bret);

#else
	ls->PushBoolean(true);
#endif // __WIN32

	_LEAVEFUNC_LUA;
}

#endif
#endif