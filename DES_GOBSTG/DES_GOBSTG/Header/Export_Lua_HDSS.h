#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#ifndef _EXPORT_LUA_HDSS_H
#define _EXPORT_LUA_HDSS_H

#include "Export_Lua.h"


class Export_Lua_HDSS : public Export_Lua
{
public:
	static bool _LuaRegistConst(LuaObject * obj);

	static bool _Helper_HDSS_GetPara(LuaStack * args, int i, LuaObject * _para);
	static void _ChangeSpecialChar(char * str);

	static bool InitCallbacks();
	static bool Execute(DWORD typeflag, DWORD name, DWORD con);

public:
	static LuaFunction<bool> * controlExecute;
	static LuaFunction<bool> * stageExecute;
	static LuaFunction<bool> * edefExecute;
	static LuaFunction<bool> * sceneExecute;
	static LuaFunction<bool> * functionExecute;
	static LuaFunction<bool> * eventExecute;


public:

	// hdss func
#define _HDSSFUNC_REGISTER(func)	static int LuaFn_HDSS_##func(LuaState * ls)

	_HDSSFUNC_REGISTER(Call);
	_HDSSFUNC_REGISTER(Get);

	_HDSSFUNC_REGISTER(SetDesc);
	_HDSSFUNC_REGISTER(SetDescFloat);
	_HDSSFUNC_REGISTER(GetDesc);

	_HDSSFUNC_REGISTER(SetChara);
	_HDSSFUNC_REGISTER(GetChara);

	_HDSSFUNC_REGISTER(ClearAll);

	_HDSSFUNC_REGISTER(SetStage);
	_HDSSFUNC_REGISTER(GetStage);

	_HDSSFUNC_REGISTER(CallStartPrep);
	_HDSSFUNC_REGISTER(SetupBG);

	_HDSSFUNC_REGISTER(BuildSelect);
	_HDSSFUNC_REGISTER(BuildSelectConfirm);
	_HDSSFUNC_REGISTER(SetupSelect);
	_HDSSFUNC_REGISTER(ReleaseSelect);
	_HDSSFUNC_REGISTER(CheckSelect);

	_HDSSFUNC_REGISTER(CheckInput);

	_HDSSFUNC_REGISTER(ChangeMusic);
	_HDSSFUNC_REGISTER(ToggleMusicSlide);

	_HDSSFUNC_REGISTER(PlaySE);

	_HDSSFUNC_REGISTER(SetPlayerInitData);
	_HDSSFUNC_REGISTER(TogglePlayerInfi);
	_HDSSFUNC_REGISTER(CheckPlayerInfi);

	_HDSSFUNC_REGISTER(BuildEnemy);
	_HDSSFUNC_REGISTER(GetAllEnemiesInfo);

	_HDSSFUNC_REGISTER(SetState);
	_HDSSFUNC_REGISTER(GetState);

	_HDSSFUNC_REGISTER(GetReplayMode);

#undef _HDSSFUNC_REGISTER

	static bool _LuaRegistFunction(LuaObject * obj)
	{
		LuaObject _hdssobj = obj->CreateTable("hdss");

#define _HDSSFUNC_REGISTER(func)	_hdssobj.Register(###func, LuaFn_HDSS_##func)

//		_HDSSFUNC_REGISTER(Call);
//		_HDSSFUNC_REGISTER(Get);

		_HDSSFUNC_REGISTER(SetDesc);
		_HDSSFUNC_REGISTER(SetDescFloat);
		_HDSSFUNC_REGISTER(GetDesc);

		_HDSSFUNC_REGISTER(SetChara);
		_HDSSFUNC_REGISTER(GetChara);

		_HDSSFUNC_REGISTER(ClearAll);

		_HDSSFUNC_REGISTER(SetStage);
		_HDSSFUNC_REGISTER(GetStage);

		_HDSSFUNC_REGISTER(CallStartPrep);
		_HDSSFUNC_REGISTER(SetupBG);

		_HDSSFUNC_REGISTER(BuildSelect);
		_HDSSFUNC_REGISTER(BuildSelectConfirm);
		_HDSSFUNC_REGISTER(SetupSelect);
		_HDSSFUNC_REGISTER(ReleaseSelect);
		_HDSSFUNC_REGISTER(CheckSelect);

		_HDSSFUNC_REGISTER(CheckInput);

		_HDSSFUNC_REGISTER(ChangeMusic);
		_HDSSFUNC_REGISTER(ToggleMusicSlide);

		_HDSSFUNC_REGISTER(PlaySE);

		_HDSSFUNC_REGISTER(SetPlayerInitData);
		_HDSSFUNC_REGISTER(TogglePlayerInfi);
		_HDSSFUNC_REGISTER(CheckPlayerInfi);

		_HDSSFUNC_REGISTER(BuildEnemy);
		_HDSSFUNC_REGISTER(GetAllEnemiesInfo);

		_HDSSFUNC_REGISTER(SetState);
		_HDSSFUNC_REGISTER(GetState);

		_HDSSFUNC_REGISTER(GetReplayMode);

#undef  _HDSSFUNC_REGISTER

		return true;
	};
};

#endif
#endif
#endif