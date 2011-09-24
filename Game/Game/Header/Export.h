#ifndef _EXPORT_H
#define _EXPORT_H

#include "MainDependency.h"
#include "Const.h"

class Export
{
public:
	Export();
	~Export();

	static bool clientInitial(bool usesound = false, bool extuse = false);
	static void clientSetMatrix(float worldx = 0, float worldy = 0, float worldz = 0);
	static void clientAdjustWindow();
	static void Release();
	static bool SetIni(bool extuse = false);
	static bool GetResourceFile(bool readbin = false);
	static int GetPassword();
	static bool packFile(const char * zipname, const char * filename);
#ifdef __WIN32
	static bool packFolder(const char * zipname, const char * foldername, const char * filterstr, int * initcount = 0);
	#ifdef __UNPACK
	#define UNPACK_INIFILENAME	"Unpack.ini"
	#define UNPACK_SECTION	"Package_"
	#define UNPACK_PACKNAME	"FileName"
	#define UNPACK_TYPE		"Type_"
	static bool unpackFile(const char * zipname, const char * filename);
	static bool unpackFromIni(const char * inifilename);
	#endif
#endif
	static bool effSave(const char * filename, hgeEffectSystem * eff, int texnum);
	static int effLoad(const char * filename, hgeEffectSystem * eff, HTEXTURE * tex);

public:
	static char resourcefilename[M_PATHMAX];
	static char resbinname[M_PATHMAX];
	static int password;
};

#ifndef _MAIN_H
extern HGE * hge;
#endif

#endif