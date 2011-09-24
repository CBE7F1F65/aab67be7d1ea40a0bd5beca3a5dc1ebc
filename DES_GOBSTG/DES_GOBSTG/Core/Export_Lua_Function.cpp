#ifndef __NOTUSELUA

#include "../Header/Export_Lua.h"
#include "../Header/LuaConstDefine.h"

#include "../Header/Export_Lua_HGE.h"
#include "../Header/Export_Lua_HGEHelp.h"
#include "../Header/Export_Lua_HDSS.h"
#include "../Header/Export_Lua_Game.h"

bool Export_Lua::_LuaRegistFunction(LuaObject * obj)
{
	LuaObject _globalobj = obj->CreateTable("global");
	_globalobj.Register("Calculate", LuaFn_Global_Calculate);
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

	return true;
}

DWORD Export_Lua::_LuaHelper_GetDWORD(LuaObject * obj)
{
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

DWORD Export_Lua::_LuaHelper_GetColor(LuaObject * obj)
{
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
	LuaStack args(ls);
	const char * calstr = 0;

	calstr = args[1].GetString();
	if (!calstr || strlen(calstr) < 4)
	{
		ls->PushInteger(0);
		return 1;
	}

	LONGLONG l1, l2, lret;
	QWORD q1, q2, qret;

	bool buseq = false;
	if (calstr[3] == LUACALCULATESTR_QWORD)
	{
		buseq = true;
	}
	LuaObject _obj;
	_obj = args[2];

	_LuaHelper_GetCalculateValue(&_obj, calstr[0], buseq, &l1);
	_obj = args[3];
	_LuaHelper_GetCalculateValue(&_obj, calstr[2], buseq, &l2);

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
		_LuaHelper_PushQWORD(ls, qret);
	}
	else
	{
		_LuaHelper_PushLONGLONG(ls, lret);
	}
	return 1;
}

int Export_Lua::LuaFn_Global_DIST(LuaState * ls)
{
	LuaStack args(ls);
	lua_Number lnret;

	lnret = DIST(args[1].GetNumber(), args[2].GetNumber(), args[3].GetNumber(), args[4].GetNumber());

	ls->PushNumber(lnret);
	return 1;
}

int Export_Lua::LuaFn_Global_DIST2(LuaState * ls)
{
	LuaStack args(ls);
	lua_Number lnret;

	lnret = DIST2(args[1].GetNumber(), args[2].GetNumber(), args[3].GetNumber(), args[4].GetNumber());

	ls->PushNumber(lnret);
	return 1;
}

int Export_Lua::LuaFn_Global_SIGN(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = SIGN(args[1].GetInteger());

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_Global_ROLL(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = ROLL(args[1].GetInteger(), args[2].GetInteger());

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_Global_INTER(LuaState * ls)
{
	LuaStack args(ls);
	lua_Number lnret;

	lnret = INTER(args[1].GetNumber(), args[2].GetNumber(), args[3].GetNumber());

	ls->PushNumber(lnret);
	return 1;
}

int Export_Lua::LuaFn_Global_ARGB(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;

	if (args.Count() > 2)
	{
		dret = ARGB(args[1].GetInteger(), args[2].GetInteger(), args[3].GetInteger(), args[4].GetInteger());
	}
	else
	{
		if (args[1].IsTable())
		{
			LuaObject _obj = args[1];
			dret = _LuaHelper_GetColor(&_obj);
		}
		else
		{
			dret = (((DWORD)(args[1].GetInteger()))<<24) + (DWORD)(args[2].GetInteger());
		}
	}

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua::LuaFn_Global_HSVA(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;
	
	float _a = 0;
	if (args.Count() > 3)
	{
		_a = args[4].GetFloat();
	}
	hgeColorHSV _hsv(args[1].GetFloat(), args[2].GetFloat(), args[3].GetFloat(), _a);
	dret = _hsv.GetHWColor();

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua::LuaFn_Global_GetARGB(LuaState * ls)
{
	LuaStack args(ls);
	int a, r, g, b;

	LuaObject _obj = args[1];
	DWORD col = _LuaHelper_GetColor(&_obj);
	a = GETA(col);
	r = GETR(col);
	g = GETG(col);
	b = GETB(col);

	ls->PushInteger(a);
	ls->PushInteger(r);
	ls->PushInteger(g);
	ls->PushInteger(b);
	return 4;
}

int Export_Lua::LuaFn_Global_SetARGB(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;

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

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua::LuaFn_Global_GetLocalTime(LuaState * ls)
{
	LuaStack args(ls);
	LuaStackObject table;
	QWORD qret;

/*
	SYSTEMTIME systime;
	FILETIME filetime;
	GetLocalTime(&systime);
	SystemTimeToFileTime(&systime, &filetime);*/


	WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds;
	hge->Timer_GetSystemTime(&wYear, &wMonth, &wDayOfWeek, &wDay, &wHour, &wMinute, &wSecond, &wMilliseconds);

	table = ls->CreateTable();
	table.SetInteger("wYear", wYear);
	table.SetInteger("wMonth", wMonth);
	table.SetInteger("wDayOfWeek", wDayOfWeek);
	table.SetInteger("wDay", wDay);
	table.SetInteger("wHour", wHour);
	table.SetInteger("wMinute", wMinute);
	table.SetInteger("wSecond", wSecond);
	table.SetInteger("wMilliseconds", wMilliseconds);
	qret = hge->Timer_GetFileTime();

	ls->PushValue(table);
	_LuaHelper_PushQWORD(ls, qret);
	return 2;
}

int Export_Lua::LuaFn_Global_GetClipBoard(LuaState * ls)
{
	LuaStack args(ls);

#ifdef __WIN32
	if (OpenClipboard(NULL))
	{
		HANDLE hData = GetClipboardData(CF_TEXT);
		char * buffer = (char*)GlobalLock(hData);
		_LuaHelper_PushString(ls, buffer);
		GlobalUnlock(hData);
		CloseClipboard();
		return 1;
	}
#endif // __WIN32
	return 0;
}

int Export_Lua::LuaFn_Global_GetPrivateProfileString(LuaState * ls)
{
	LuaStack args(ls);
	char sret[M_STRINGMAX];

	strcpy(sret, hge->Ini_GetString(args[1].GetString(), args[2].GetString(), args[3].GetString(), (char *)args[4].GetString()));
//	GetPrivateProfileString(args[1].GetString(), args[2].GetString(), args[3].GetString(), sret, M_STRINGMAX, args[4].GetString());

	_LuaHelper_PushString(ls, sret);
	return 1;
}

int Export_Lua::LuaFn_Global_WritePrivateProfileString(LuaState * ls)
{
	LuaStack args(ls);

	hge->Ini_SetString(args[1].GetString(), args[2].GetString(), args[3].GetString(), (char *)args[4].GetString());
//	WritePrivateProfileString(args[1].GetString(), args[2].GetString(), args[3].GetString(), args[4].GetString());

	return 0;
}

int Export_Lua::LuaFn_Global_MessageBox(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	char stext[M_MESSAGESTRMAX];
	strcpy(stext, "");
	char scaption[M_MESSAGESTRMAX];
	strcpy(scaption, "");
	int type = MB_OK;
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
	iret = hge->System_MessageBox(stext, scaption, (DWORD)type);

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_DoFile(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = Export_Lua::DoLuaFile(ls, args[1].GetString());
	if (iret != 0)
	{
		Export_Lua::ShowError(LUAERROR_LOADINGSCRIPT, ls->GetError(iret));
	}

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_SetConst(LuaState * ls)
{
	LuaStack args(ls);

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

	return 0;
}

int Export_Lua::LuaFn_LuaState_GetConst(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

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

	return 1;
}

int Export_Lua::LuaFn_LuaState_GetPointer(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret = 0;

	if (args[1].IsString())
	{
		dret = (DWORD)(args[1].GetString());
	}
	else if (args[1].IsNumber())
	{
		static lua_Number _number;
		_number = args[1].GetNumber();
		dret = (DWORD)(&_number);
	}

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_IntToDWORD(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;

	dret = args[1].GetInteger();

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_DWORDToInt(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	LuaObject _obj = args[1];
	iret = _LuaHelper_GetDWORD(&_obj);

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_And(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = (args[1].GetInteger()) & (args[2].GetInteger());

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_Or(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = (args[1].GetInteger()) | (args[2].GetInteger());

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_Xor(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = (args[1].GetInteger()) ^ (args[2].GetInteger());

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_Not(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = ~(args[1].GetInteger());

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_LShift(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = (args[1].GetInteger()) << (args[2].GetInteger());

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_RShift(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = (args[1].GetInteger()) >> (args[2].GetInteger());

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua::LuaFn_LuaState_ReadLineInContent(LuaState * ls)
{
	LuaStack args(ls);
#ifdef __WIN32
	string sret;
	DWORD dret;

	LuaObject _obj = args[1];
	DWORD content = _LuaHelper_GetDWORD(&_obj);
	dret = content;
	_obj = args[2];
	DWORD size = _LuaHelper_GetDWORD(&_obj);
	int i=0;
	sret = "";
	if (dret < content + size)
	{
		char buffer = *(char*)dret;
		while (buffer != '\r' && buffer != '\n')
		{
			sret += buffer;
			i++;
			dret++;
			if (dret >= content + size)
			{
				dret = content + size;
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
		if (dret < content + size)
		{
			dret++;
		}
		size -= dret - content;
	}

	_LuaHelper_PushString(ls, sret.data());
	_LuaHelper_PushDWORD(ls, dret);
	_LuaHelper_PushDWORD(ls, size);
	return 3;

#else

	return 0;

#endif // __WIN32
}

#endif