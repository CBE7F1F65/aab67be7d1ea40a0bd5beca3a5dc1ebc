#ifndef _EXPORT_H
#define _EXPORT_H

#include "MainDependency.h"
#include "Const.h"

#define RPYPARTMAX		7
#define RPYPREFIXMAX	8
#define RPYENUMMAX		0x40

#define RPYFILENAME_CONTENTMAX	7

#define RPYINFO_USERNAMEMAX		0x08
#define RPYINFO_SPELLNAMEMAX	0x40

#define RPYOFFSET_SIGNATURE		0x00
#define RPYSIZE_SIGNATURE		0x0C
#define RPYOFFSET_VERSION		(RPYOFFSET_SIGNATURE + RPYSIZE_SIGNATURE)
#define RPYSIZE_VERSION			0x04
#define RPYOFFSET_COMPLETESIGN	(RPYOFFSET_VERSION + RPYSIZE_VERSION)
#define RPYSIZE_COMPLETESIGN	0x04
#define RPYOFFSET_TAG			(RPYOFFSET_COMPLETESIGN + RPYSIZE_COMPLETESIGN)
#define RPYSIZE_TAG				0x04
#define RPYOFFSET_INFOOFFSET	(RPYOFFSET_TAG + RPYSIZE_TAG)
#define RPYSIZE_INFOOFFSET		0x04
#define RPYOFFSET_APPEND		(RPYOFFSET_INFOOFFSET + RPYSIZE_INFOOFFSET)
#define RPYSIZE_APPEND			0x04
#define RPYOFFSET_RPYINFO		(RPYOFFSET_APPEND + RPYOFFSET_APPEND)
#define RPYSIZE_RPYINFO			sizeof(replayInfo)
#define RPYOFFSET_PARTINFO		(RPYOFFSET_RPYINFO + RPYSIZE_RPYINFO)
#define RPYSIZE_PARTINFO		sizeof(partInfo)
#define RPYOFFSET_INPUTDATA		(RPYOFFSET_PARTINFO + (RPYPARTMAX * RPYSIZE_PARTINFO))
#define RPYSIZE_FRAME			sizeof(replayFrame)

#define REPLAYPASSWORD_XORMAGICNUM	0x45A61920

struct replayInfo
{
	char username[M_PL_MATCHMAXPLAYER][RPYINFO_USERNAMEMAX];

	DWORD alltime;
	DWORD offset;

	WORD year;
	WORD month;
	WORD day;
	WORD hour;
	WORD minute;

	float lost;

	BYTE matchmode;
	BYTE scene;

	BYTE usingchara[M_PL_MATCHMAXPLAYER][M_PL_ONESETPLAYER];
	BYTE initlife[M_PL_MATCHMAXPLAYER];
};

struct partInfo
{
	DWORD offset;
	DWORD seed;
	WORD nowID[M_PL_MATCHMAXPLAYER];
};

struct replayFrame{
	WORD input;
	BYTE bias;
};

class Export
{
public:
	Export();
	~Export();

	static bool clientInitial(bool usesound = false, bool extuse = false);
	static bool clientAfterInitial(float screenscale);
	static bool clientResetMatrix(float screenscale);
	static hge3DPoint * GetFarPoint(BYTE renderflag);
	static void clientSetMatrix(float worldx = 0, float worldy = 0, float worldz = 0, BYTE renderflag=M_RENDER_NULL);
	static void clientSetMatrixUser(D3DXMATRIX matWorld, D3DXMATRIX matView, D3DXMATRIX matProj);
	static bool clientSet2DMode();
	static bool clientSet3DMode();
	static void clientAdjustWindow();
	static void Release();
	static BYTE GetPlayerIndexByRenderFlag(BYTE renderflag);
	static BYTE GetRenderFlagByPlayerIndex(BYTE playerindex);
	static bool SetIni(bool extuse = false);
	static bool GetResourceFile(bool readbin = false);
	static int GetPassword();
	static void SetLastIP(DWORD ipx, WORD ipport);
	static bool GetLastIP(DWORD * ipx, WORD * ipport);
	static bool rpyLoad(const char * filename, replayInfo * _rpyinfo = NULL, partInfo * _partinfo = NULL, replayFrame * _replayframe = NULL);
	static bool rpyFree(const char * filename);
	static bool rpySetBias(replayFrame * _replayframe);
	static float rpyGetReplayFPS(replayFrame _replayframe);
	static bool packFile(const char * zipname, const char * filename);
	static bool packFolder(const char * zipname, const char * foldername, const char * filterstr, int * initcount = 0);
#ifdef __UNPACK
	#define UNPACK_INIFILENAME	"Unpack.ini"
	#define UNPACK_SECTION	"Package_"
	#define UNPACK_PACKNAME	"FileName"
	#define UNPACK_TYPE		"Type_"
	static bool unpackFile(const char * zipname, const char * filename);
	static bool unpackFromIni(const char * inifilename);
#endif
	static bool effSave(const char * filename, hgeEffectSystem * eff, int texnum);
	static int effLoad(const char * filename, hgeEffectSystem * eff, HTEXTURE * tex);

public:
	static char resourcefilename[M_PATHMAX];
	static char resbinname[M_PATHMAX];
	static partInfo partinfo[RPYPARTMAX];
	static replayInfo rpyinfo;
	static int password;

	static D3DXMATRIX matView2DMode;
	static D3DXMATRIX matProj2DMode;
	static D3DXMATRIX matView[M_PL_MATCHMAXPLAYER];
	static D3DXMATRIX matProj[M_PL_MATCHMAXPLAYER];
	static D3DXMATRIX matViewSuper;
	static D3DXMATRIX matProjSuper;
	static hge3DPoint ptfar;
};

#ifndef _MAIN_H
extern HGE * hge;
#endif

#endif