#ifndef _SCRIPTER_H
#define _SCRIPTER_H

#include "MainDependency.h"
#include "Const.h"
#include "keytable.h"

#ifndef __NOTUSELUA
#include "Export_Lua.h"
#endif

#define SCRIPT_DATAMAX		0x400000
#define SCR_MAXDESC			0x100

#ifdef __DEBUG
	#define __COUNT_SCRIPTSIZE
#endif

#define SCRIPT_GETTINGTEXT	0x10
#define SCRIPT_GETTINGBIN	0x20

#define SCRIPT_CON_INIT		0x0000
#define SCRIPT_CON_QUIT		0xffff
#define SCRIPT_CON_POST		0x0000

#define SCR_VARBEGIN		0x30
#define SCR_FREEBEGIN		0x70
#define SCR_RESERVEBEGIN	0x90
#define SCR_VARDESCNUM		(SCR_FREEBEGIN - SCR_VARBEGIN)

#define CAST(p)		(((p).bfloat) ? (CFLOAT((p).value)) : (CINT((p).value)))
#define UCAST(p)	(*(DWORD *)(p).value)

#define SCRVECALL_FILE_SMALL	0x20
#define SCRVECALL_FILE_NORMAL	0x100
#define SCRVECALL_FILE_LARGE	0x400
#define SCRVECALL_BLOCK			0x60


enum{
	SCR_TOKEN_VALUE		= 0x0001,
	SCR_TOKEN_HANDLE	= 0x0002,
	SCR_TOKEN_COMMAND	= 0x0004,
	SCR_TOKEN_TYPE		= 0x0008,
	SCR_TOKEN_VARIABLE	= 0x0010,
	
	SCR_TOKEN_FLOAT		= 0x0100,
	SCR_TOKEN_OPERATOR	= 0x0200,
	SCR_TOKEN_KEYWORD	= 0x0400,
	SCR_TOKEN_EOF		= 0x0800,
	SCR_TOKEN_NULL		= 0x1000,

	SCR_TOKEN_ERROR		= 0x8000,
};

enum{
	SCR_FORCE_INT		= 0x01,
	SCR_FORCE_FLOAT		= 0x02,
};

enum{
	SCR_ERROR_INVALIDSTRING,
	SCR_ERROR_STRINGTOOLONG,
	SCR_ERROR_STRINGTOOMUCH,
	SCR_ERROR_VAROVER,
	SCR_ERROR_FREEVAROVER,
	SCR_ERROR_RESERVEVAROVER,
};

typedef struct tagToken
{
	DWORD value;
	DWORD type;
}Token;

typedef Token Script;

typedef struct tagBlock		//time, depth
{
	vector<Script> block;
	DWORD con;				//condition
	int varcount;
#ifdef __COUNT_SCRIPTSIZE
	DWORD _size;
#endif
}Block;

typedef struct tagFile		//each file
{
	vector<Block> file;
	DWORD name;
#ifdef __COUNT_SCRIPTSIZE
	DWORD _size;
#endif
}File;

typedef struct tagTData
{
	void * value;
	bool bfloat;
}TData;

class Scripter
{
public:
	Scripter();
	~Scripter();

	Token GetToken();

	void FillCustomConstDesc();

	bool LoadAll();
	bool LoadScript(const char * filename);
	bool Resize();

	bool SetValue(int index, void * value, bool bfloat);
	void * GetValue(int index);

	bool SetIntValue(int index, int ival)
	{
		return SetValue(index, &ival, false);
	}
	int GetIntValue(int index)
	{
		return CINT(GetValue(index));
	}
	bool SetDWORDValue(int index, DWORD uval)
	{
		return SetValue(index, &uval, false);
	}
	DWORD GetDWORDValue(int index)
	{
		return CUINT(GetValue(index));
	}
	bool SetFloatValue(int index, float fval)
	{
		return SetValue(index, &fval, true);
	}
	int GetFloatValue(int index)
	{
		return CFLOAT(GetValue(index));
	}

	bool SetString(int index, char * str);
	char * GetString(int index);
	char * GetStringSp(int descindex);

	void LogOut();

private:
	bool Execute(vector<File> * ptype, DWORD name, DWORD con);
public:
	bool Execute(DWORD typeflag, DWORD name, DWORD con)
	{
#ifndef __NOTUSELUA
		return Execute_Lua(typeflag, name, con);
#endif
		switch(typeflag)
		{
		case SCR_CONTROL:
			return Execute(&control, name, con);
		case SCR_STAGE:
			return Execute(&stage, name, con);
		case SCR_EDEF:
			return Execute(&edef, name, con);
		case SCR_SCENE:
			return Execute(&scene, name, con);
		case SCR_FUNCTION:
			return Execute(&function, name, con);
		case SCR_EVENT:
			return Execute(&event, name, con);
		}
		return false;
	}
private:
	bool controlExecute(DWORD name, DWORD con)
	{
		return Execute(&control, name, con);
	};
	bool stageExecute(DWORD name, DWORD con)
	{
		return Execute(&stage, name, con);
	};
	bool edefExecute(DWORD name, DWORD con)
	{
		return Execute(&edef, name, con);
	};
	bool sceneExecute(DWORD name, DWORD con)
	{
		return Execute(&scene, name, con);
	};
	bool functionExecute(DWORD name, DWORD con)
	{
		return Execute(&function, name, con);
	};
	bool eventExecute(DWORD name, DWORD con)
	{
		return Execute(&event, name, con);
	}
public:

	bool Parse(int varcount);

	bool Copy(vector<Script>::iterator * p, BYTE num, BYTE dstart = 0);
	void * Value(vector<Script>::iterator * p, int i, BYTE force);
	void * ValueI(vector<Script>::iterator * p, int i){return Value(p, i, SCR_FORCE_INT);};
	void * ValueF(vector<Script>::iterator * p, int i){return Value(p, i, SCR_FORCE_FLOAT);};

	void ReleaseVarName();

public:

//	char varName[SCR_FREEBEGIN-SCR_VARBEGIN][M_STRMAX];
	char ** varName;

	TData d[SCR_MAXDESC];
	union
	{
		int idesc[SCR_MAXDESC];
		float fdesc[SCR_MAXDESC];
	};

	vector<File> control;
	vector<File> stage;
	vector<File> edef;
	vector<File> scene;
	vector<File> function;
	vector<File> event;
	FILE * file;

#ifdef __COUNT_SCRIPTSIZE
	DWORD _controlsize;
	DWORD _stagesize;
	DWORD _edefsize;
	DWORD _scenesize;
	DWORD _functionsize;
	DWORD _eventsize;
#endif

	DWORD binsize;
	DWORD binoffset;
	bool binmode;
	BYTE * bincontent;
	vector<Script> * pnow;

	DWORD nowName;
	DWORD nowCon;

	int tdi;
	DWORD tdu;
	float tdf;

	int varIndex;
	DWORD strdescIndex;

	static char strdesc[STRINGDESCMAX][M_STRMAX*2];

	static Scripter scr;

#ifndef __NOTUSELUA
public:
	bool LoadAll_Lua();
	bool Execute_Lua(DWORD typeflag, DWORD name, DWORD con);
#endif
};

#endif