#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#ifndef _EXPORT_LUA_HDSS_H
#define _EXPORT_LUA_HDSS_H

#include "Export_Lua.h"

class Export_Lua_HDSS : public Export_Lua
{
public:
	static bool _LuaRegistConst(LuaObject * obj);
	static bool _LuaRegistFunction(LuaObject * obj);
	static int LuaFn_HDSS_Call(LuaState * ls);
	static int LuaFn_HDSS_Get(LuaState * ls);
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
};

#endif
#endif
#endif