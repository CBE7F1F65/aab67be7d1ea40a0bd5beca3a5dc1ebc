#ifndef __NOTUSELUA

#include "../Header/Export_Lua.h"
#include "../Header/Export_Lua_Const.h"
#include "../Header/BObject.h"

#include "../Header/Export_Lua_HGE.h"
#include "../Header/Export_Lua_HGEHelp.h"
#include "../Header/Export_Lua_HDSS.h"
#include "../Header/Export_Lua_Game.h"

bool Export_Lua::_LuaRegistFunction(LuaObject * obj)
{
	LuaObject _globalobj = obj->CreateTable("global");
	_globalobj.Register("Calculate", LuaFn_Global_Calculate);
	_globalobj.Register("AMA", LuaFn_Global_AMA);
	_globalobj.Register("RMA", LuaFn_Global_RMA);
	_globalobj.Register("SINT", LuaFn_Global_SINT);
	_globalobj.Register("COST", LuaFn_Global_COST);
	_globalobj.Register("DIST", LuaFn_Global_DIST);
	_globalobj.Register("DIST2", LuaFn_Global_DIST2);
	_globalobj.Register("SIGN", LuaFn_Global_SIGN);
	_globalobj.Register("ROLL", LuaFn_Global_ROLL);
	_globalobj.Register("INTER", LuaFn_Global_INTER);
	_globalobj.Register("ARGB", LuaFn_Global_ARGB);
	_globalobj.Register("HSVA", LuaFn_Global_HSVA);
	_globalobj.Register("GetARGB", LuaFn_Global_GetARGB);
	_globalobj.Register("SetARGB", LuaFn_Global_SetARGB);
	_globalobj.Register("GetLocalTime", LuaFn_Global_GetLocalTime);
	_globalobj.Register("GetClipBoard", LuaFn_Global_GetClipBoard);
	_globalobj.Register("GetPrivateProfileString", LuaFn_Global_GetPrivateProfileString);
	_globalobj.Register("WritePrivateProfileString", LuaFn_Global_WritePrivateProfileString);
	_globalobj.Register("MessageBox", LuaFn_Global_MessageBox);
	_globalobj.Register("SystemLog", LuaFn_Global_SystemLog);

	LuaObject _luastateobj = obj->CreateTable("luastate");
	_luastateobj.Register("DoFile", LuaFn_LuaState_DoFile);
	_luastateobj.Register("SetConst", LuaFn_LuaState_SetConst);
	_luastateobj.Register("GetConst", LuaFn_LuaState_GetConst);
	_luastateobj.Register("GetPointer", LuaFn_LuaState_GetPointer);
	_luastateobj.Register("IntToDWORD", LuaFn_LuaState_IntToDWORD);
	_luastateobj.Register("DWORDToInt", LuaFn_LuaState_DWORDToInt);
	_luastateobj.Register("And", LuaFn_LuaState_And);
	_luastateobj.Register("Or", LuaFn_LuaState_Or);
	_luastateobj.Register("Xor", LuaFn_LuaState_Xor);
	_luastateobj.Register("Not", LuaFn_LuaState_Not);
	_luastateobj.Register("LShift", LuaFn_LuaState_LShift);
	_luastateobj.Register("RShift", LuaFn_LuaState_RShift);
	_luastateobj.Register("ReadLineInContent", LuaFn_LuaState_ReadLineInContent);

	return true;
}

bool Export_Lua::LuaRegistFunction()
{
	LuaObject obj = state->GetGlobals();

	if (!_LuaRegistFunction(&obj))
	{
		return false;
	}
	if (!Export_Lua_HGE::_LuaRegistFunction(&obj))
	{
		return false;
	}
	if (!Export_Lua_HGEHelp::_LuaRegistFunction(&obj))
	{
		return false;
	}
#ifndef __NOTUSEHDSS
	if (!Export_Lua_HDSS::_LuaRegistFunction(&obj))
	{
		return false;
	}
#endif
#ifndef __NOTINTHISGAME
	if (!Export_Lua_Game::_LuaRegistFunction(&obj))
	{
		return false;
	}
#endif

	return true;
}

bool Export_Lua::LuaRegistConst()
{
	LuaObject obj = state->GetGlobals();

	if (!_LuaRegistConst(&obj))
	{
		return false;
	}
	if (!Export_Lua_HGE::_LuaRegistConst(&obj))
	{
		return false;
	}
	if (!Export_Lua_HGEHelp::_LuaRegistConst(&obj))
	{
		return false;
	}
#ifndef __NOTUSEHDSS
	if (!Export_Lua_HDSS::_LuaRegistConst(&obj))
	{
		return false;
	}
#endif
#ifndef __NOTINTHISGAME
	if (!Export_Lua_Game::_LuaRegistConst(&obj))
	{
		return false;
	}
#endif
	if (!_LuaRegistCustomConst(&obj))
	{
		return false;
	}
	if (!_LuaRegistTEX(&obj))
	{
		return false;
	}
	if (!_LuaRegistSIID(&obj))
	{
		return false;
	}
	if (!_LuaRegistMUSICID(&obj))
	{
		return false;
	}
	if (!_LuaRegistSEID(&obj))
	{
		return false;
	}
	if (!_LuaRegistEFFID(&obj))
	{
		return false;
	}

	return true;
}

DWORD Export_Lua::_LuaHelper_GetDWORD(LuaObject * obj)
{
	if (obj->IsNil())
	{
		ShowError(LUAERROR_NILVALUE, ERRORSTR_TITLE);
		return 0;
	}
	DWORD dret;
	if (obj->IsString())
	{
		sscanf(obj->GetString(), "%d", &dret);
	}
	else
	{
		lua_Number lnval = obj->GetNumber();
		dret = CUINTN(lnval);
	}
	return dret;
}

void Export_Lua::_LuaHelper_PushDWORD(LuaState * ls, DWORD dval)
{
	lua_Number lnval = CDOUBLEN(dval);
	ls->PushNumber(lnval);
}

LONGLONG Export_Lua::_LuaHelper_GetLONGLONG(LuaObject * obj)
{
	if (obj->IsNil())
	{
		ShowError(LUAERROR_NILVALUE, ERRORSTR_TITLE);
		return 0;
	}
	LONGLONG llret;
	if (obj->IsString())
	{
		sscanf(obj->GetString(), "%I64d", &llret);
	}
	else
	{
		lua_Number lnval = obj->GetNumber();
		llret = CLONGLONGN(lnval);
	}
	return llret;
}

void Export_Lua::_LuaHelper_PushLONGLONG(LuaState * ls, LONGLONG llval)
{
	lua_Number lnval = CDOUBLEN(llval);
	ls->PushNumber(lnval);
}

QWORD Export_Lua::_LuaHelper_GetQWORD(LuaObject * obj)
{
	if (obj->IsNil())
	{
		ShowError(LUAERROR_NILVALUE, ERRORSTR_TITLE);
		return 0;
	}
	QWORD qret;
	if (obj->IsString())
	{
		sscanf(obj->GetString(), "%I64u", &qret);
	}
	else
	{
		lua_Number lnval = obj->GetNumber();
		qret = CULONGLONGN(lnval);
	}
	return qret;
}

void Export_Lua::_LuaHelper_PushQWORD(LuaState * ls, QWORD qval)
{
	lua_Number lnval = CDOUBLEN(qval);
	ls->PushNumber(lnval);
}

void Export_Lua::_LuaHelper_PushString(LuaState * ls, const char * sval)
{
	if (!sval)
	{
		ls->PushString("");
	}
	else
	{
		ls->PushString(sval);
	}
}

void Export_Lua::_LuaHelper_PushTable(LuaState * ls, LuaStackObject tval)
{
	ls->PushValue(tval);
}

LuaStackObject Export_Lua::_LuaHelper_CreateTable(LuaState * ls)
{
	return ls->CreateTable();
}
DWORD Export_Lua::_LuaHelper_GetColor(LuaObject * obj)
{
	if (obj->IsNil())
	{
		ShowError(LUAERROR_NILVALUE, ERRORSTR_TITLE);
		return 0;
	}
	DWORD dret = 0;
	if (obj->IsTable())
	{
		BYTE _a = obj->GetByName("a").GetInteger();
		BYTE _r = obj->GetByName("r").GetInteger();
		BYTE _g = obj->GetByName("g").GetInteger();
		BYTE _b = obj->GetByName("b").GetInteger();
		dret = ARGB(_a, _r, _g, _b);
	}
	else
	{
		dret = _LuaHelper_GetDWORD(obj);
	}
	return dret;
}

void Export_Lua::_LuaHelper_GetCalculateValue(LuaObject * obj, char calchar, bool buseq, void * val)
{
	if (obj->IsNil() || !val)
	{
		ShowError(LUAERROR_NILVALUE, ERRORSTR_TITLE);
		return;
	}
	int _int;
	DWORD _dword;
	LONGLONG _longlong;
	QWORD _qword;

	switch (calchar)
	{
	case LUACALCULATESTR_INT:
		_int = obj->GetInteger();
		if (buseq)
		{
			if (_int < 0)
			{
				_int = 0;
			}
			CULONGLONG(val) = _int;
		}
		else
		{
			CLONGLONG(val) = _int;
		}
		break;
	case LUACALCULATESTR_DWORD:
		_dword = _LuaHelper_GetDWORD(obj);
		if (buseq)
		{
			CULONGLONG(val) = _dword;
		}
		else
		{
			CLONGLONG(val) = _dword;
		}
		break;
	case LUACALCULATESTR_LONGLONG:
		_longlong = _LuaHelper_GetLONGLONG(obj);
		if (buseq)
		{
			if (_longlong < 0)
			{
				_longlong = 0;
			}
			CULONGLONG(val) = _longlong;
		}
		else
		{
			CLONGLONG(val) = _longlong;
		}
		break;
	case LUACALCULATESTR_QWORD:
		_qword = _LuaHelper_GetQWORD(obj);
		if (buseq)
		{
			CULONGLONG(val) = _qword;
		}
		else
		{
			CLONGLONG(val) = _qword;
		}
		break;
	}
}

int Export_Lua::LuaFn_Global_Calculate(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(3);

	const char * calstr = 0;

//	calstr = args[1].GetString();
	calstr = node.sNextGet();

	if (!calstr || strlen(calstr) < 4)
	{
//		ls->PushInteger(0);
//		return 1;
		node.PInt(0);
		break;
	}

	LONGLONG l1 = 0;
	LONGLONG l2 = 0;
	LONGLONG lret;
	QWORD q1, q2, qret;

	bool buseq = false;
	if (calstr[3] == LUACALCULATESTR_QWORD)
	{
		buseq = true;
	}
//	LuaObject _obj;
//	_obj = args[2];

//	_LuaHelper_GetCalculateValue(&_obj, calstr[0], buseq, &l1);
//	_obj = args[3];
	//	_LuaHelper_GetCalculateValue(&_obj, calstr[2], buseq, &l2);
	node.CalculateValueNextGet(calstr[0], buseq, &l1);
	node.CalculateValueNextGet(calstr[2], buseq, &l2);

	if (buseq)
	{
		q1 = CULONGLONGN(l1);
		q2 = CULONGLONGN(l2);
	}

	switch (calstr[1])
	{
	case '+':
		if (buseq)
		{
			qret = q1 + q2;
		}
		else
		{
			lret = l1 + l2;
		}
		break;
	case '-':
		if (buseq)
		{
			qret = q1 - q2;
		}
		else
		{
			lret = l1 - l2;
		}
		break;
	case '*':
		if (buseq)
		{
			qret = q1 * q2;
		}
		else
		{
			lret = l1 * l2;
		}
		break;
	case '/':
		if (buseq)
		{
			qret = q1 / q2;
		}
		else
		{
			lret = l1 / l2;
		}
		break;
	case '%':
		if (buseq)
		{
			qret = q1 % q2;
		}
		else
		{
			lret = l1 % l2;
		}
		break;
	}
	if (buseq)
	{
//		_LuaHelper_PushQWORD(ls, qret);
		node.PQword(qret);
	}
	else
	{
//		_LuaHelper_PushLONGLONG(ls, lret);
		node.PLongLong(lret);
	}
//	return 1;
	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_AMA(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(4);
	int iret;

	float _orix = node.fNextGet();
	float _oriy = node.fNextGet();
	float _aimx = node.fNextGet();
	float _aimy = node.fNextGet();

	int _a = 0;
//	if (args.Count() > 4)
//	{
//		_a = args[5].GetInteger();
//	}
	node.jNextGet();
	if (node.bhavenext)
	{
		_a = node.iGet();
	}
	BObject _obj(_orix, _oriy);
	iret = _obj.aMainAngle(_aimx, _aimy, _a);
//	iret = aMainAngle(_orix, _oriy, _aimx, _aimy, _a);

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_RMA(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(4);
	int iret;

	float _orix = node.fNextGet();
	float _oriy = node.fNextGet();
	float _aimx = node.fNextGet();
	float _aimy = node.fNextGet();

	float _r = 0.0f;

//	if (args.Count() > 4)
//	{
//		_r = args[5].GetNumber();
//	}
	node.jNextGet();
	if (node.bhavenext)
	{
		_r = node.fGet();
	}
	BObject _obj(_orix, _oriy);
	iret = _obj.rMainAngle(_aimx, _aimy, _r);
//	iret = rMainAngle(_orix, _oriy, _aimx, _aimy, _r);

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_SINT(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	lua_Number lnret;

	int _angle = node.iNextGet();
//	lnret = sint(args[1].GetInteger());
	lnret = sint(_angle);

//	ls->PushNumber(lnret);
//	return 1;
	node.PLuaNumber(lnret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_COST(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	lua_Number lnret;

	int _angle = node.iNextGet();
//	lnret = cost(args[1].GetInteger());
	lnret = cost(_angle);

//	ls->PushNumber(lnret);
//	return 1;
	node.PLuaNumber(lnret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_DIST(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(4);
	lua_Number lnret;

	lua_Number _x1 = node.lnNextGet();
	lua_Number _y1 = node.lnNextGet();
	lua_Number _x2 = node.lnNextGet();
	lua_Number _y2 = node.lnNextGet();
//	lnret = DIST(args[1].GetNumber(), args[2].GetNumber(), args[3].GetNumber(), args[4].GetNumber());
	lnret = DIST(_x1, _y1, _x2, _y2);

//	ls->PushNumber(lnret);
//	return 1;
	node.PLuaNumber(lnret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_DIST2(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(4);
	lua_Number lnret;

	lua_Number _x1 = node.lnNextGet();
	lua_Number _y1 = node.lnNextGet();
	lua_Number _x2 = node.lnNextGet();
	lua_Number _y2 = node.lnNextGet();
//	lnret = DIST2(args[1].GetNumber(), args[2].GetNumber(), args[3].GetNumber(), args[4].GetNumber());
	lnret = DIST2(_x1, _y1, _x2, _y2);

//	ls->PushNumber(lnret);
//	return 1;
	node.PLuaNumber(lnret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_SIGN(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	int iret;

	int _Xval = node.iNextGet();
//	iret = SIGN(args[1].GetInteger());
	iret = SIGN(_Xval);

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_ROLL(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(2);
	int iret;

	int _Xval = node.iNextGet();
	int _Tval = node.iNextGet();
//	iret = ROLL(args[1].GetInteger(), args[2].GetInteger());
	iret = ROLL(_Xval, _Tval);

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_INTER(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(3);
	lua_Number lnret;

	lua_Number _Aval = node.lnNextGet();
	lua_Number _Bval = node.lnNextGet();
	lua_Number _Xval = node.lnNextGet();
//	lnret = INTER(args[1].GetNumber(), args[2].GetNumber(), args[3].GetNumber());
	lnret = INTER(_Aval, _Bval, _Xval);

//	ls->PushNumber(lnret);
//	return 1;
	node.PLuaNumber(lnret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_ARGB(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	DWORD dret;

//	if (args.Count() > 2)
	if (node.argscount > 2)
	{
		BYTE _a = node.iNextGet();
		BYTE _r = node.iNextGet();
		BYTE _g = node.iNextGet();
		BYTE _b = 0;
		node.jNextGet();
		if (node.bhavenext)
		{
			_b = node.iGet();
		}
		else
		{
			_b = _g;
			_g = _r;
			_r = _a;
			_a = 0;
		}
//		dret = ARGB(args[1].GetInteger(), args[2].GetInteger(), args[3].GetInteger(), args[4].GetInteger());
		dret = ARGB(_a, _r, _g, _b);
	}
	else
	{
//		if (args[1].IsTable())
		node.jNextGet();
		if (node.ObjIsTable())
		{
//			LuaObject _obj = args[1];
//			dret = _LuaHelper_GetColor(&_obj);
			dret = node.cGet();
		}
		else
		{
			BYTE _a = node.iGet();
			BYTE _r = 0;
			BYTE _g = 0;
			BYTE _b = 0;
			node.jNextGet();
			if (node.bhavenext)
			{
				int _diffuse = node.iGet();
				_r = GETR(_diffuse);
				_g = GETG(_diffuse);
				_b = GETB(_diffuse);
			}
//			dret = (((DWORD)(args[1].GetInteger()))<<24) + (DWORD)(args[2].GetInteger());
			dret = ARGB(_a, _r, _g, _b);
		}
	}

//	_LuaHelper_PushDWORD(ls, dret);
//	return 1;
	node.PDword(dret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_HSVA(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(3);
	DWORD dret;

	float _h = node.fNextGet();
	float _s = node.fNextGet();
	float _v = node.fNextGet();
	float _a = 0;
//	if (args.Count() > 3)
//	{
//		_a = args[4].GetFloat();
//	}
	node.jNextGet();
	if (node.bhavenext)
	{
		_a = node.fGet();
	}
	hgeColorHSV _hsv(_h, _s, _v, _a);
	dret = _hsv.GetHWColor();
//	dret = BIOInterface::getInstance()->Math_HSVAtoARGB(_h, _s, _v, _a);

//	_LuaHelper_PushDWORD(ls, dret);
//	return 1;
	node.PDword(dret);
	
	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_GetARGB(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	int a, r, g, b;

//	LuaObject _obj = args[1];
//	DWORD col = _LuaHelper_GetColor(&_obj);
	DWORD _col = node.cNextGet();
	a = GETA(_col);
	r = GETR(_col);
	g = GETG(_col);
	b = GETB(_col);

//	ls->PushInteger(a);
//	ls->PushInteger(r);
//	ls->PushInteger(g);
//	ls->PushInteger(b);
//	return 4;
	node.PInt(a);
	node.PInt(r);
	node.PInt(g);
	node.PInt(b);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_SetARGB(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	DWORD dret;
/*
	LuaObject _obj = args[1];
	dret = _LuaHelper_GetColor(&_obj);
	int argb=0;
	int argscount = args.Count();
	if (argscount > 1)
	{
		argb = args[2].GetInteger();
		if (argb >= 0 && argb < 0x100)
		{
			dret = SETA(dret, argb);
		}
		if (argscount > 2)
		{
			argb = args[3].GetInteger();
			if (argb >= 0 && argb < 0x100)
			{
				dret = SETR(dret, argb);
			}
			if (argscount > 3)
			{
				argb = args[4].GetInteger();
				if (argb >= 0 && argb < 0x100)
				{
					dret = SETG(dret, argb);
				}
				if (argscount > 4)
				{
					argb = args[5].GetInteger();
					if (argb >= 0 && argb < 0x100)
					{
						dret = SETB(dret, argb);
					}
				}
			}
		}
	}
*/
	dret = node.cNextGet();
	BYTE _argb = 0;
	node.jNextGet();
	if (node.bhavenext)
	{
		_argb = node.iGet();
		dret = SETA(dret, _argb);
		if (node.bhavenext)
		{
			_argb = node.iGet();
			dret = SETR(dret, _argb);
			if (node.bhavenext)
			{
				_argb = node.iGet();
				dret = SETG(dret, _argb);
				if (node.bhavenext)
				{
					_argb = node.iGet();
					dret = SETB(dret, _argb);
				}
			}
		}
	}
//	_LuaHelper_PushDWORD(ls, dret);
//	return 1;
	node.PDword(dret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_GetLocalTime(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(0);
	LuaStackObject table;
	QWORD qret;

/*
	SYSTEMTIME systime;
	FILETIME filetime;
	GetLocalTime(&systime);
	SystemTimeToFileTime(&systime, &filetime);*/


	WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds;
	hge->Timer_GetSystemTime(&wYear, &wMonth, &wDayOfWeek, &wDay, &wHour, &wMinute, &wSecond, &wMilliseconds);

//	table = ls->CreateTable();
	table = _LuaHelper_CreateTable(ls);
	table.SetInteger("wYear", wYear);
	table.SetInteger("wMonth", wMonth);
	table.SetInteger("wDayOfWeek", wDayOfWeek);
	table.SetInteger("wDay", wDay);
	table.SetInteger("wHour", wHour);
	table.SetInteger("wMinute", wMinute);
	table.SetInteger("wSecond", wSecond);
	table.SetInteger("wMilliseconds", wMilliseconds);
	qret = hge->Timer_GetFileTime();

//	ls->PushValue(table);
//	_LuaHelper_PushQWORD(ls, qret);
//	return 2;
	node.PTable(table);
	node.PQword(qret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_GetClipBoard(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(0);

#ifdef __WIN32
	if (OpenClipboard(NULL))
	{
		HANDLE hData = GetClipboardData(CF_TEXT);
		char * buffer = (char*)GlobalLock(hData);
//		_LuaHelper_PushString(ls, buffer);
		node.PString(buffer);
		GlobalUnlock(hData);
		CloseClipboard();
//		return 1;
	}
#endif // __WIN32
//	return 0;
	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_GetPrivateProfileString(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(3);
	char sret[M_STRMAX];

	const char * _section = node.sNextGet();
	const char * _name = node.sNextGet();
	const char * _defval = node.sNextGet();
	char * _inifilename = NULL;
	node.jNextGet();
	if (node.bhavenext)
	{
		_inifilename = (char *)node.sGet();
	}

	strcpy(sret, hge->Ini_GetString(_section, _name, _defval, _inifilename));

//	_LuaHelper_PushString(ls, sret);
//	return 1;
	node.PString(sret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_WritePrivateProfileString(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(3);

	const char * _section = node.sNextGet();
	const char * _name = node.sNextGet();
	const char * _value = node.sNextGet();
	char * _inifilename = NULL;
	node.jNextGet();
	if (node.bhavenext)
	{
		_inifilename = (char *)node.sGet();
	}

	hge->Ini_SetString(_section, _name, _value, _inifilename);

//	return 0;
	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_MessageBox(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(0);
	int iret;

	char _stext[M_MESSAGESTRMAX];
	strcpy(_stext, "");
	char _scaption[M_MESSAGESTRMAX];
	strcpy(_scaption, "");
	int _type = MB_OK;
	/*
	int argscount = args.Count();
	if (argscount > 0)
	{
		strcpy(stext, args[1].GetString());
		if (argscount > 1)
		{
			strcpy(scaption, args[2].GetString());
			if (argscount > 2)
			{
				type = args[3].GetInteger();
			}
		}
	}
	*/
	node.jNextGet();
	if (node.bhavenext)
	{
		strcpy(_stext, node.sGet());
		node.jNextGet();
		if (node.bhavenext)
		{
			strcpy(_scaption, node.sGet());
			node.jNextGet();
			if (node.bhavenext)
			{
				_type = node.iGet();
			}
		}
	}
	iret = hge->System_MessageBox(_stext, _scaption, (DWORD)_type);

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_Global_SystemLog(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);

	const char * _str = node.sNextGet();
	hge->System_Log(_str);

//	return 0;
	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_DoFile(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	int iret;

	const char * _filename = node.sNextGet();
//	iret = DoLuaFile(ls, args[1].GetString());
	iret = DoLuaFile(ls, _filename);
	if (iret != 0)
	{
		Export_Lua::ShowError(LUAERROR_LOADINGSCRIPT, ls->GetError(iret));
	}

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_SetConst(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(2);

	/*
	LuaObject _obj;
	if (args.Count() > 2)
	{
		_obj = args[3];
	}
	else
	{
		_obj = ls->GetGlobals();
	}
	const char * constname = args[1].GetString();

	switch (args[2].GetType())
	{
	case LUA_TBOOLEAN:
		_obj.SetBoolean(constname, args[2].GetBoolean());
		break;
	case LUA_TNUMBER:
		_obj.SetNumber(constname, args[2].GetNumber());
		break;
	case LUA_TSTRING:
		_obj.SetString(constname, args[2].GetString());
		break;
	default:
		_obj.SetNil(constname);
		break;
	}
	*/
	const char * _constname = node.sNextGet();
	node.jNextGet();
	int _type = node._obj->Type();

	bool _bval = false;
	lua_Number _lnval = 0;
	char * _sval = NULL;

	node.jNextGet();
	switch (_type)
	{
	case LUA_TBOOLEAN:
		_bval = node.bGet();
		break;
	case LUA_TNUMBER:
		_lnval = node.lnGet();
		break;
	case LUA_TSTRING:
		_sval = (char *)node.sGet();
		break;
	default:
		break;
	}

	LuaObject _obj;
	node.jNextGet();
	if (node.bhavenext)
	{
		_obj = *(node._obj);
	}
	else
	{
		_obj = ls->GetGlobals();
	}
	switch (_type)
	{
	case LUA_TBOOLEAN:
		_obj.SetBoolean(_constname, _bval);
		break;
	case LUA_TNUMBER:
		_obj.SetNumber(_constname, _lnval);
		break;
	case LUA_TSTRING:
		_obj.SetString(_constname, _sval);
		break;
	default:
		_obj.SetNil(_constname);
		break;
	}

//	return 0;
	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_GetConst(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	int iret;

	/*
	LuaObject _obj;
	if (args.Count() > 1)
	{
		_obj = args[2];
	}
	else
	{
		_obj = ls->GetGlobals();
	}
	_obj = _obj.GetByName(args[1].GetString());
	switch (_obj.Type())
	{
	case LUA_TBOOLEAN:
		ls->PushBoolean(_obj.GetBoolean());
		break;
	case LUA_TNUMBER:
		ls->PushNumber(_obj.GetNumber());
		break;
	case LUA_TSTRING:
		_LuaHelper_PushString(ls, _obj.GetString());
		break;
	default:
		ls->PushNil();
		break;
	}
	*/
	const char * _constname = node.sNextGet();

	LuaObject _obj;
	node.jNextGet();
	if (node.bhavenext)
	{
		_obj = *(node._obj);
	}
	else
	{
		_obj = ls->GetGlobals();
	}
	_obj = _obj.GetByName(_constname);
	switch (_obj.Type())
	{
	case LUA_TBOOLEAN:
		node.PBoolean(_obj.GetBoolean());
		break;
	case LUA_TNUMBER:
		node.PLuaNumber(_obj.GetNumber());
		break;
	case LUA_TSTRING:
		node.PString(_obj.GetString());
		break;
	default:
		node.PNil();
//		ls->PushNil();
		break;
	}
//	return 1;
	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_GetPointer(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	DWORD dret = 0;

	node.jNextGet();
//	if (args[1].IsString())
	if (node.ObjIsString())
	{
//		dret = (DWORD)(args[1].GetString());
		dret = (DWORD)node.sGet();
	}
	else
	{
		static lua_Number _number;
//		_number = args[1].GetNumber();
		_number = node.lnGet();
		dret = (DWORD)(&_number);
	}

//	_LuaHelper_PushDWORD(ls, dret);
//	return 1;
	node.PDword(dret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_IntToDWORD(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	DWORD dret;

//	dret = args[1].GetInteger();
	dret = node.iNextGet();

//	_LuaHelper_PushDWORD(ls, dret);
//	return 1;
	node.PDword(dret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_DWORDToInt(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	int iret;

//	LuaObject _obj = args[1];
//	iret = _LuaHelper_GetDWORD(&_obj);
	iret = node.dNextGet();

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_And(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(2);
	int iret;

//	iret = (args[1].GetInteger()) & (args[2].GetInteger());
	int _ileft = node.iNextGet();
	int _iright = node.iNextGet();
	iret = _ileft & _iright;

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_Or(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(2);
	int iret;

//	iret = (args[1].GetInteger()) | (args[2].GetInteger());
	int _ileft = node.iNextGet();
	int _iright = node.iNextGet();
	iret = _ileft | _iright;

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_Xor(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(2);
	int iret;

//	iret = (args[1].GetInteger()) ^ (args[2].GetInteger());
	int _ileft = node.iNextGet();
	int _iright = node.iNextGet();
	iret = _ileft ^ _iright;

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_Not(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(1);
	int iret;

//	iret = ~(args[1].GetInteger());
	int _ival = node.iNextGet();
	iret = ~_ival;

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_LShift(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(2);
	int iret;

//	iret = (args[1].GetInteger()) << (args[2].GetInteger());
	int _ileft = node.iNextGet();
	int _iright = node.iNextGet();
	iret = _ileft << _iright;

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_RShift(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(2);
	int iret;

//	iret = (args[1].GetInteger()) >> (args[2].GetInteger());
	int _ileft = node.iNextGet();
	int _iright = node.iNextGet();
	iret = _ileft >> _iright;

//	ls->PushInteger(iret);
//	return 1;
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua::LuaFn_LuaState_ReadLineInContent(LuaState * ls)
{
//	LuaStack args(ls);
	_ENTERFUNC_LUA(2);
#ifdef __WIN32
	string sret;
	DWORD dret;

//	LuaObject _obj = args[1];
//	DWORD content = _LuaHelper_GetDWORD(&_obj);
	DWORD _content = node.dNextGet();
	dret = _content;
//	_obj = args[2];
//	DWORD size = _LuaHelper_GetDWORD(&_obj);
	DWORD _size = node.dNextGet();
	int i=0;
	sret = "";
	if (dret < _content + _size)
	{
		char buffer = *(char*)dret;
		while (buffer != '\r' && buffer != '\n')
		{
			sret += buffer;
			i++;
			dret++;
			if (dret >= _content + _size)
			{
				dret = _content + _size;
				break;
			}
			buffer = *(char*)dret;
		}
		if (buffer == '\r')
		{
			if (*(((char*)dret)+1) == '\n')
			{
				dret++;
			}
		}
		if (dret < _content + _size)
		{
			dret++;
		}
		_size -= dret - _content;
	}
	node.PString(sret.data());
	node.PDword(dret);
	node.PDword(_size);

//	_LuaHelper_PushString(ls, sret.data());
//	_LuaHelper_PushDWORD(ls, dret);
//	_LuaHelper_PushDWORD(ls, _size);
//	return 3;

#else

//	return 0;

#endif // __WIN32
	_LEAVEFUNC_LUA;
}

#endif