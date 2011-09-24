#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#ifndef _EXPORT_LUA_HDSS_CALLGETDEFINE_H
#define _EXPORT_LUA_HDSS_CALLGETDEFINE_H

#define _NEXT_HDSS_LUAPARA		(_para.GetByIndex(++ii))
#define _INEXT_HDSS_LUAPARA		(_NEXT_HDSS_LUAPARA.GetInteger())
#define _FNEXT_HDSS_LUAPARA		(_NEXT_HDSS_LUAPARA.GetFloat())
#define _BNEXT_HDSS_LUAPARA		(_NEXT_HDSS_LUAPARA.GetBoolean())
#define _LNNEXT_HDSS_LUAPARA	(_NEXT_HDSS_LUAPARA.GetNumber())
#define _SNEXT_HDSS_LUAPARA		((char *)(_NEXT_HDSS_LUAPARA.GetString()))
#define _ONEXT_HDSS_LUAPARA		(_obj = _NEXT_HDSS_LUAPARA)

#define _IOBJ_HDSS_LUA		(_obj.GetInteger())
#define _FOBJ_HDSS_LUA		(_obj.GetFloat())
#define _BOBJ_HDSS_LUA		(_obj.GetBoolean())
#define _LNOBJ_HDSS_LUA		(_obj.GetNumber())
#define _SOBJ_HDSS_LUA		((char *)_obj.GetString())
#define _COBJ_HDSS_LUA		(Export_Lua::_LuaHelper_GetColor(&_obj))
#define _DOBJ_HDSS_LUA		(Export_Lua::_LuaHelper_GetDWORD(&_obj))

#define _NILCHECK_HDSS_LUA		(!_obj.IsNil())
#define _JNEXT_HDSS_LUAPARA		_ONEXT_HDSS_LUAPARA;\
								bhavenext = _NILCHECK_HDSS_LUA
#define _GETPARAS_HDSS_LUAPARA(X)		if (!Export_Lua_HDSS::_Helper_HDSS_GetPara(&args, (X), &_para))\
										{\
											return false;\
										}\
										ii = 0

#define _ENTERCALL_HDSS_LUA		LuaStack args(ls);\
								argscount = args.Count();\
								if (argscount > 1)\
								{\
									_GETPARAS_HDSS_LUAPARA(2);\
								}\
								else\
								{\
									return 0;\
								}
#define _ENTERGET_HDSS_LUA		LuaStack args(ls);\
								argscount = args.Count();\
								ii = 1

#define _NEXT_HDSS_LUAFUNC	(args[++ii])
#define _INEXT_HDSS_LUAFUNC	(_NEXT_HDSS_LUAFUNC.GetInteger())
#define _FNEXT_HDSS_LUAFUNC	(_NEXT_HDSS_LUAFUNC.GetFloat())
#define _BNEXT_HDSS_LUAFUNC	(_NEXT_HDSS_LUAFUNC.GetBoolean())
#define _SNEXT_HDSS_LUAFUNC	((char *)(_NEXT_HDSS_LUAFUNC.GetString()))
#define _ONEXT_HDSS_LUAFUNC	(_obj = _NEXT_HDSS_LUAFUNC)

#define _JNEXT_HDSS_LUAFUNC		_ONEXT_HDSS_LUAFUNC;\
								bhavenext = _NILCHECK_HDSS_LUA

#define _PI_HDSS_LUA(X)	(ls->PushInteger(X))
#define _PF_HDSS_LUA(X)	(ls->PushNumber(X))
#define _PB_HDSS_LUA(X)	(ls->PushBoolean(X))
#define _PS_HDSS_LUA(X)	(Export_Lua::_LuaHelper_PushString(ls, X))
#define _PD_HDSS_LUA(X)	(Export_Lua::_LuaHelper_PushDWORD(ls, X))

#endif

#endif
#endif