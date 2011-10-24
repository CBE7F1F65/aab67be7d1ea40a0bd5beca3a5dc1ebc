#ifndef __EXPORT_LUA_H__
#define __EXPORT_LUA_H__

#include "_LObjNode.h"
#include "Export_Lua_Const.h"
#include "MainDependency.h"

#define ERRORSTR_TITLE				"Error!"


#ifndef __NOTUSEHDSS
#define HDSS_PREFIX	"HDSS_"
#define LUAFN_CONTROLEXECUTE	"ControlExecute"
#define LUAFN_STAGEEXECUTE		"StageExecute"
#define LUAFN_EDEFEXECUTE		"EdefExecute"
#define LUAFN_SCENEEXECUTE		"SceneExecute"
#define LUAFN_FUNCTIONEXECUTE	"FunctionExecute"
#define LUAFN_EVENTEXECUTE		"EventExecute"
#endif

#ifdef _DEBUG
#define _DEBUG_ENTERFUNC_LUA	state->GetStack(1, &debug_ar);\
	state->GetInfo("nSl", &debug_ar)
#else
#define _DEBUG_ENTERFUNC_LUA
#endif


#define _ENTERFUNC_LUA(X)	_DEBUG_ENTERFUNC_LUA; \
							LuaStack args(ls);\
							node._init(ls, NULL, &args, &node);\
							if (node.argscount >= (X))\
							{\
							do\
								{

#define _LEAVEFUNC_LUA			} while(false);\
							}\
							else\
							{\
							ShowError(LUAERROR_ARG, "");\
							return 0;\
							}\
							return node.retcount

class Export_Lua
{
public:
	Export_Lua();
	~Export_Lua();
public:

	static void Init();
	static void Release(LuaState * ls = NULL);

	static void InitHGE(HGE * hge = NULL);
	static void ReleaseHGE();

	static int LoadLuaFile(LuaState * ls, const char * filename, bool bDoFile = false, int * filecount = NULL, FILE * outputfile = NULL);
private:
	static int _LoadLuaFile(LuaState * ls, const char * filename, bool bDoFile = false, int * filecount = NULL, FILE * outputfile = NULL);
public:
	static int DoLuaFile(LuaState * ls, const char * filename){return LoadLuaFile(ls, filename, true);};

	static int DoLuaFileInMemroy(LuaState * ls, const char * buffer, DWORD size, const char * name);

	static bool CheckUseUnpackedFiles(LuaState * ls);
	static int PackLuaFiles(LuaState * ls = NULL);
	static int LoadPackedLuaFiles(LuaState * ls = NULL);

	static int LuaChunkWriter(lua_State *L, const void* p, size_t sz, void* ud);

	static int ReadLuaFileTable(LuaState * ls = NULL);

	static void ShowError(int errortype, const char * err);

	static void HeatUp(list<int> * charcodelist, LuaState * ls=NULL);
	static void HeatUp(list<int> * charcodelist, LuaState * ls, LuaObject * obj);

	static bool LuaRegistFunction();
	static bool _LuaRegistFunction(LuaObject * obj);

	static bool LuaRegistConst();
	static bool _LuaRegistConst(LuaObject * obj);
	static bool _LuaRegistCustomConst(LuaObject * obj);
	static bool _LuaRegistTEX(LuaObject * obj);
	static bool _LuaRegistSIID(LuaObject * obj);
	static bool _LuaRegistMUSICID(LuaObject * obj);
	static bool _LuaRegistSEID(LuaObject * obj);
	static bool _LuaRegistEFFID(LuaObject * obj);

	static DWORD _LuaHelper_GetColor(LuaObject * obj);
	static void _LuaHelper_PushDWORD(LuaState * ls, DWORD dval);
	static DWORD _LuaHelper_GetDWORD(LuaObject * obj);
	static void _LuaHelper_PushLONGLONG(LuaState * ls, LONGLONG llval);
	static LONGLONG _LuaHelper_GetLONGLONG(LuaObject * obj);
	static void _LuaHelper_PushQWORD(LuaState * ls, QWORD qval);
	static QWORD _LuaHelper_GetQWORD(LuaObject * obj);
	static void _LuaHelper_PushString(LuaState * ls, const char * sval);
	static void _LuaHelper_PushTable(LuaState * ls, LuaStackObject tval);
	static LuaStackObject _LuaHelper_CreateTable(LuaState * ls);

	static void _LuaHelper_GetCalculateValue(LuaObject * obj, char calchar, bool buseq, void * val);

	static int LuaFn_Global_Calculate(LuaState * ls);
	static int LuaFn_Global_AMA(LuaState * ls);
	static int LuaFn_Global_RMA(LuaState * ls);
	static int LuaFn_Global_SINT(LuaState * ls);
	static int LuaFn_Global_COST(LuaState * ls);
	static int LuaFn_Global_DIST(LuaState * ls);
	static int LuaFn_Global_DIST2(LuaState * ls);
	static int LuaFn_Global_SIGN(LuaState * ls);
	static int LuaFn_Global_ROLL(LuaState * ls);
	static int LuaFn_Global_INTER(LuaState * ls);
	static int LuaFn_Global_ARGB(LuaState * ls);
	static int LuaFn_Global_HSVA(LuaState * ls);
	static int LuaFn_Global_GetARGB(LuaState * ls);
	static int LuaFn_Global_SetARGB(LuaState * ls);
	static int LuaFn_Global_GetLocalTime(LuaState * ls);
	static int LuaFn_Global_GetClipBoard(LuaState * ls);
	static int LuaFn_Global_GetPrivateProfileString(LuaState * ls);
	static int LuaFn_Global_WritePrivateProfileString(LuaState * ls);
	static int LuaFn_Global_MessageBox(LuaState * ls);
	static int LuaFn_Global_SystemLog(LuaState * ls);

	static int LuaFn_LuaState_DoFile(LuaState * ls);
	static int LuaFn_LuaState_SetConst(LuaState * ls);
	static int LuaFn_LuaState_GetConst(LuaState * ls);
	static int LuaFn_LuaState_GetPointer(LuaState * ls);
	static int LuaFn_LuaState_IntToDWORD(LuaState * ls);
	static int LuaFn_LuaState_DWORDToInt(LuaState * ls);
	static int LuaFn_LuaState_And(LuaState * ls);
	static int LuaFn_LuaState_Or(LuaState * ls);
	static int LuaFn_LuaState_Xor(LuaState * ls);
	static int LuaFn_LuaState_Not(LuaState * ls);
	static int LuaFn_LuaState_LShift(LuaState * ls);
	static int LuaFn_LuaState_RShift(LuaState * ls);
	static int LuaFn_LuaState_ReadLineInContent(LuaState * ls);

public:
	static LuaStateOwner state;
#ifdef _DEBUG
	static lua_Debug debug_ar;
#endif
	static _LObjNode node;

	static HGE * hge;
};

#endif