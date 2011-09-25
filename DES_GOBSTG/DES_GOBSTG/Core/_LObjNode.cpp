#include "../Header/_LObjNode.h"

#include "../Header/Export_Lua.h"
#include "../Header/Export_Lua_Const.h"

_LObjNode::_LObjNode()
{
	_init(NULL, NULL, NULL, NULL);
}

_LObjNode::_LObjNode(LuaState * _ls, LuaStack * args)
{
	_init(_ls, NULL, args, this);
}

_LObjNode::_LObjNode(LuaState * _ls, LuaObject * obj, _LObjNode *root)
{
	_init(_ls, obj, NULL, root);
}


_LObjNode::~_LObjNode()
{

}

void _LObjNode::_init(LuaState * _ls, LuaObject * obj, LuaStack * args, _LObjNode *_root)
{
	objbase = obj;
	argsbase = args;
	root = _root;
	bhavenext = false;
	ii = 0;
	argscount = 0;
	retcount = 0;
	ls = _ls;
	if (_isStack())
	{
		argscount = argsbase->Count();
	}
	else
	{
		if (objbase)
		{
			argscount = objbase->GetCount();
		}
	}
	_obj = NULL;
}

bool _LObjNode::ObjIsTable()
{
	if (!_obj)
	{
		return false;
	}
	return _obj->IsTable();
}

bool _LObjNode::ObjIsString()
{
	if (!_obj)
	{
		return false;
	}
	return _obj->IsString();
}

bool _LObjNode::_isStack()
{
	if (argsbase)
	{
		return true;
	}
	return false;
}

bool _LObjNode::NilCheck()
{
	if (!_obj)
	{
		return true;
	}
	return _obj->IsNil();
}

LuaObject * _LObjNode::jNextGet()
{
	++ii;
	if (ii > argscount)
	{
		_obj = NULL;
	}
	else
	{
		if (_isStack())
		{
			_objtemp = (*argsbase)[ii];
			_obj = &_objtemp;
		}
		else if (objbase)
		{
			_objtemp = (*objbase).GetByIndex(ii);
			_obj = &_objtemp;
		}
	}
	bhavenext = !NilCheck();
	return _obj;
}

int _LObjNode::iGet()
{
	if (NilCheck())
	{
//		BIOInterface::getInstance()->System_MessageBox(ERRORSTR_NILCHECK, ERRORSTR_TITLE);
		Export_Lua::ShowError(LUAERROR_NILVALUE, ERRORSTR_TITLE);
		return 0;
	}
	return _obj->GetInteger();
}

int _LObjNode::iNextGet()
{
	jNextGet();
	return iGet();
}

float _LObjNode::fGet()
{
	if (NilCheck())
	{
//		BIOInterface::getInstance()->System_MessageBox(ERRORSTR_NILCHECK, ERRORSTR_TITLE);
		Export_Lua::ShowError(LUAERROR_NILVALUE, ERRORSTR_TITLE);
		return 0.0f;
	}
	return _obj->GetFloat();
}

float _LObjNode::fNextGet()
{
	jNextGet();
	return fGet();
}

lua_Number _LObjNode::lnGet()
{
	if (NilCheck())
	{
		Export_Lua::ShowError(LUAERROR_NILVALUE, ERRORSTR_TITLE);
		return 0.0;
	}
	return _obj->GetNumber();
}

lua_Number _LObjNode::lnNextGet()
{
	jNextGet();
	return lnGet();
}

bool _LObjNode::bGet()
{
	if (NilCheck())
	{
//		BIOInterface::getInstance()->System_MessageBox(ERRORSTR_NILCHECK, ERRORSTR_TITLE);
		Export_Lua::ShowError(LUAERROR_NILVALUE, ERRORSTR_TITLE);
		return false;
	}
	return _obj->GetBoolean();
}

bool _LObjNode::bNextGet()
{
	jNextGet();
	return bGet();
}

const char * _LObjNode::sGet()
{
	if (NilCheck())
	{
//		BIOInterface::getInstance()->System_MessageBox(ERRORSTR_NILCHECK, ERRORSTR_TITLE);
		Export_Lua::ShowError(LUAERROR_NILVALUE, ERRORSTR_TITLE);
		return NULL;
	}
	return _obj->GetString();
}

const char * _LObjNode::sNextGet()
{
	jNextGet();
	return sGet();
}

DWORD _LObjNode::cGet()
{
	return Export_Lua::_LuaHelper_GetColor(_obj);
}

DWORD _LObjNode::cNextGet()
{
	jNextGet();
	return cGet();
}

DWORD _LObjNode::dGet()
{
	return Export_Lua::_LuaHelper_GetDWORD(_obj);
}

DWORD _LObjNode::dNextGet()
{
	jNextGet();
	return dGet();
}

LONGLONG _LObjNode::llGet()
{
	return Export_Lua::_LuaHelper_GetLONGLONG(_obj);
}

LONGLONG _LObjNode::llNextGet()
{
	jNextGet();
	return llGet();
}

QWORD _LObjNode::qGet()
{
	return Export_Lua::_LuaHelper_GetQWORD(_obj);
}

QWORD _LObjNode::qNextGet()
{
	jNextGet();
	return qGet();
}

void _LObjNode::CalculateValueGet(char calchar, bool buseq, void * val)
{
	return Export_Lua::_LuaHelper_GetCalculateValue(_obj, calchar, buseq, val);
}

void _LObjNode::CalculateValueNextGet(char calchar, bool buseq, void * val)
{
	jNextGet();
	return CalculateValueGet(calchar, buseq, val);
}

void _LObjNode::PInt(int ival)
{
	if (ls && root)
	{
		ls->PushInteger(ival);
		root->retcount++;
	}
}

void _LObjNode::PFloat(float fval)
{
	if (ls && root)
	{
		ls->PushNumber(fval);
		root->retcount++;
	}
}

void _LObjNode::PLuaNumber(lua_Number lnval)
{
	if (ls && root)
	{
		ls->PushNumber(lnval);
		root->retcount++;
	}
}

void _LObjNode::PBoolean(bool bval)
{
	if (ls && root)
	{
		ls->PushBoolean(bval);
		root->retcount++;
	}
}

void _LObjNode::PString(const char * sval)
{
	if (ls && root)
	{
		Export_Lua::_LuaHelper_PushString(ls, sval);
		root->retcount++;
	}
}

void _LObjNode::PDword(DWORD dval)
{
	if (ls && root)
	{
		Export_Lua::_LuaHelper_PushDWORD(ls, dval);
		root->retcount++;
	}
}

void _LObjNode::PLongLong(LONGLONG llval)
{
	if (ls && root)
	{
		Export_Lua::_LuaHelper_PushLONGLONG(ls, llval);
		root->retcount++;
	}
}

void _LObjNode::PQword(QWORD qval)
{
	if (ls && root)
	{
		Export_Lua::_LuaHelper_PushQWORD(ls, qval);
		root->retcount++;
	}
}

void _LObjNode::PNil()
{
	if (ls && root)
	{
		ls->PushNil();
		root->retcount++;
	}
}

void _LObjNode::PTable(LuaStackObject tval)
{
	if (ls && root)
	{
		Export_Lua::_LuaHelper_PushTable(ls, tval);
		root->retcount++;
	}
}