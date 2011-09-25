#ifndef ___LOBJNODE_H__
#define ___LOBJNODE_H__

#include "../Header/MainDependency.h"
#include "../../../LuaPlus/LuaPlus/LuaPlus.h"
using namespace LuaPlus;

class _LObjNode
{
public:
	_LObjNode();
	_LObjNode(LuaState * ls, LuaStack *args);
	_LObjNode(LuaState * ls, LuaObject *obj, _LObjNode *root);
	~_LObjNode();

	bool NilCheck();

	int iGet();
	int iNextGet();
	float fGet();
	float fNextGet();
	lua_Number lnGet();
	lua_Number lnNextGet();
	bool bGet();
	bool bNextGet();
	const char * sGet();
	const char * sNextGet();
	DWORD cGet();
	DWORD cNextGet();
	DWORD dGet();
	DWORD dNextGet();
	LONGLONG llGet();
	LONGLONG llNextGet();
	QWORD qGet();
	QWORD qNextGet();

	void CalculateValueGet(char calchar, bool buseq, void * val);
	void CalculateValueNextGet(char calchar, bool buseq, void * val);

	LuaObject * jNextGet();

	void PInt(int ival);
	void PFloat(float fval);
	void PLuaNumber(lua_Number lnval);
	void PBoolean(bool bval);
	void PString(const char * sval);
	void PDword(DWORD dval);
	void PLongLong(LONGLONG llval);
	void PQword(QWORD qval);
	void PNil();

	void PTable(LuaStackObject tval);

	bool _isStack();
	void _init(LuaState * ls, LuaObject *obj, LuaStack *args, _LObjNode *root);

	bool ObjIsTable();
	bool ObjIsString();

public:
	bool bhavenext;
	int ii;
	int argscount;
	int retcount;

	LuaObject * _obj;
	LuaObject _objtemp;
	LuaState * ls;
	LuaObject * objbase;
	LuaStack * argsbase;
	_LObjNode *root;
};

#endif