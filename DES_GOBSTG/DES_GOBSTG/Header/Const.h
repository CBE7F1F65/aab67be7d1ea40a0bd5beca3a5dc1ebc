#ifndef _CONST_H
#define _CONST_H

#define GAME_VERSION		0x073
#define GAME_VERSION_STR	"ver.0x073"
#define GAME_VERSION_SUB		0.98
#define GAME_VERSION_SUB_STR	"-0.98"
#define GAME_SIGNATURE		"h5nc"
#define GAME_TITLE			"–|·½»¨Ó³‰V Phantasmagoria of Flower View."
#define GAME_TITLE_STR		GAME_TITLE " " GAME_SIGNATURE " " GAME_VERSION_STR " " GAME_VERSION_SUB_STR

#define GAMEVERSION_CORE		0x08
#define GAMEVERSION_ALGORITHM	0x04
#define GAMEVERSION_RESOURCE	0x00

#define ARC(X)		((X) * 0.0001745329251994329f)
#define ANGLE(X)	(int)((X) * 5729.577951308232f)

#define DIST(X1, Y1, X2, Y2)	(sqrtf(((X1)-(X2))*((X1)-(X2)) + ((Y1)-(Y2))*((Y1)-(Y2))))
#define DIST2(X1, Y1, X2, Y2)	(((X1)-(X2))*((X1)-(X2)) + ((Y1)-(Y2))*((Y1)-(Y2)))
#define SIGN(X)					((((X)&1)<<1)-1)
#define ROLL(X, T)				(((X)%(2*(T)))/(T)*(T) - SIGN((X)%(2*(T))/(T)) * ((X)%(T)))
#define INTER(A, B, X)			(((B)-(A))*(X)+(A))
#define RANDA					((LONG)(randt()) * 36000 / RAND_MAX)

/*
//////////ROTATIONX//////////
//y = y * cosf(rotx) - z * sinf(rotx);
//z = y * sinf(rotx) + z * cosf(rotx);
//////////ROTATIONY//////////
//x = x * cosf(roty) - z * sinf(roty);
//z = x * sinf(roty) + z * cosf(roty);
//////////ROTATIONZ//////////
//x = x * cosf(rotz) - y * sinf(rotz);
//y = x * sinf(rotz) + y * cosf(rotz);
*/
#define ROTATION1(F1, F2, A)	((F1) * cost(A) - (F2) * sint(A))
#define ROTATION2(F1, F2, A)	((F1) * sint(A) + (F2) * cost(A))

#ifdef __DEBUG
#ifndef __DEBUG_LOG
#define __DEBUG_LOG
#endif
#endif

#define HGELOG			hge->System_Log
#define HGELOG_ERRSTR	"**********ERROR**********"


#define M_PROJECTIONMATRIX_OFFSET	0.5f

#define M_DEFAULT_FPS			60
#define M_DEFAULT_FRAMESKIP		1
#define M_DEFAULT_RENDERSKIP	1
#define M_FRAMESKIP_FASTSKIP	-3
#define M_FRAMESKIP_SLOWSKIP	2

#define M_CLIENT_LEFT			0.0f
#define M_CLIENT_RIGHT			640.0f
#define M_CLIENT_TOP			0.0f
#define M_CLIENT_BOTTOM			480.0f
#define M_CLIENT_WIDTH			(M_CLIENT_RIGHT-M_CLIENT_LEFT)
#define M_CLIENT_HEIGHT			(M_CLIENT_BOTTOM-M_CLIENT_TOP)
#define M_CLIENT_CENTER_X		((M_CLIENT_LEFT+M_CLIENT_RIGHT)/2)
#define M_CLIENT_CENTER_Y		((M_CLIENT_TOP+M_CLIENT_BOTTOM)/2)

#define M_GAMESQUARE_EDGE		16.0f
#define M_GAMESQUARE_WIDTH		(M_CLIENT_WIDTH/2-M_GAMESQUARE_EDGE*2)
#define M_GAMESQUARE_HEIGHT		(M_CLIENT_HEIGHT-M_GAMESQUARE_EDGE*2)
#define M_GAMESQUARE_TOP		(M_CLIENT_TOP+M_GAMESQUARE_EDGE)
#define M_GAMESQUARE_BOTTOM		(M_CLIENT_BOTTOM-M_GAMESQUARE_EDGE)
#define M_GAMESQUARE_LEFT_0		(M_CLIENT_LEFT+M_GAMESQUARE_EDGE)
#define M_GAMESQUARE_RIGHT_0	(M_CLIENT_CENTER_X-M_GAMESQUARE_EDGE)
#define M_GAMESQUARE_LEFT_1		(M_CLIENT_CENTER_X+M_GAMESQUARE_EDGE)
#define M_GAMESQUARE_RIGHT_1	(M_CLIENT_RIGHT-M_GAMESQUARE_EDGE)
#define	M_GAMESQUARE_LEFT_(X)	((X)?(M_GAMESQUARE_LEFT_1):(M_GAMESQUARE_LEFT_0))
#define	M_GAMESQUARE_RIGHT_(X)	((X)?(M_GAMESQUARE_RIGHT_1):(M_GAMESQUARE_RIGHT_0))
#define M_GAMESQUARE_CENTER_Y	((M_GAMESQUARE_TOP+M_GAMESQUARE_BOTTOM)/2)
#define M_GAMESQUARE_CENTER_X_0	((M_GAMESQUARE_LEFT_0+M_GAMESQUARE_RIGHT_0)/2)
#define M_GAMESQUARE_CENTER_X_1	((M_GAMESQUARE_LEFT_1+M_GAMESQUARE_RIGHT_1)/2)
#define	M_GAMESQUARE_CENTER_X_(X)	((X)?(M_GAMESQUARE_CENTER_X_1):(M_GAMESQUARE_CENTER_X_0))

#define M_GAMESQUARE_BOSSX_(X)	M_GAMESQUARE_CENTER_X_(X)
#define M_GAMESQUARE_BOSSY	(M_GAMESQUARE_CENTER_Y/2)

#if defined __PSP
#define M_SIDE_EDGE_FULL	(SCREEN_WIDTH/2*M_CLIENT_HEIGHT/SCREEN_HEIGHT-M_CLIENT_WIDTH/2)
#define M_SIDE_EDGE	(SCREEN_WIDTH/2-M_CLIENT_WIDTH*SCREEN_HEIGHT/M_CLIENT_HEIGHT/2)
#elif defined __IPHONE
#define M_SIDE_EDGE_FULL	(SCREEN_HEIGHT/2*M_CLIENT_HEIGHT/SCREEN_WIDTH-M_CLIENT_HEIGHT/2)
#define M_SIDE_EDGE	(SCREEN_HEIGHT/2-M_CLIENT_WIDTH*SCREEN_WIDTH/M_CLIENT_HEIGHT/2)
#define M_SIDE_EDGE_FULL_SCALED	(SCREEN_HEIGHT-M_CLIENT_WIDTH*SCREEN_WIDTH/M_CLIENT_HEIGHT)
#define M_SIDE_EDGE_SCALED	(M_SIDE_EDGE_FULL_SCALED/2)
#endif

#define M_DELETEBOLDER			36.0f
#define M_DELETECLIENT_LEFT_(X)		(M_GAMESQUARE_LEFT_(X)-M_DELETEBOLDER)
#define M_DELETECLIENT_RIGHT_(X)	(M_GAMESQUARE_RIGHT_(X)+M_DELETEBOLDER)
#define M_DELETECLIENT_TOP		(M_GAMESQUARE_TOP-M_DELETEBOLDER)
#define M_DELETECLIENT_BOTTOM	(M_GAMESQUARE_BOTTOM+M_DELETEBOLDER)

#define BTYPE_BULLET	0x10
#define BTYPE_BEAM		0x20
#define BTYPE_ENEMY		0x30
#define BTYPE_GHOST		0x40

#define BINDEX_NULL		0x100000

#define M_KEYKEYMAX			0x100
#define M_JOYKEYMAX			0x20

#define M_PL_CONTINUEMAX	5
#define M_PL_ONESETPLAYER	3
#define M_PL_MATCHMAXPLAYER	2

#define M_NDIFFI			6
#define M_NSTAGEDIFFI		11
#define M_DIFFI_EASY		0
#define M_DIFFI_NORMAL		1
#define M_DIFFI_HARD		2
#define M_DIFFI_DESTINY		3
#define M_DIFFI_EXTRA_START	4
#define M_DIFFI_EXTRA_1		M_DIFFI_EXTRA_START
#define M_DIFFI_EXTRA_2		(M_DIFFI_EXTRA_START+1)
#define M_DIFFI_EXTRA_3		(M_DIFFI_EXTRA_START+2)
#define M_DIFFI_EXTRA_4		(M_DIFFI_EXTRA_START+3)
#define M_DIFFI_EXTRA_5		(M_DIFFI_EXTRA_START+4)
#define M_DIFFI_EXTRA_6		(M_DIFFI_EXTRA_START+5)

#define M_LASTSTAGESTR_1		"1"
#define M_LASTSTAGESTR_2		"2"
#define M_LASTSTAGESTR_3		"3"
#define M_LASTSTAGESTR_4		"4"
#define M_LASTSTAGESTR_5		"5"
#define M_LASTSTAGESTR_6		"6"
#define M_LASTSTAGESTR_EX		"Ex"
#define M_LASTSTAGESTR_C		"C"

#define M_DIFFISTR_EASY		"Easy"
#define M_DIFFISTR_NORMAL	"Normal"
#define M_DIFFISTR_HARD		"Hard"
#define M_DIFFISTR_DESTINY	"Destiny"
#define M_DIFFISTR_EXTRA	"Extra"
#define M_DIFFISTR_EXTRA_1	"Extra_1"
#define M_DIFFISTR_EXTRA_2	"Extra_2"
#define M_DIFFISTR_EXTRA_3	"Extra_3"
#define M_DIFFISTR_EXTRA_4	"Extra_4"
#define M_DIFFISTR_EXTRA_5	"Extra_5"
#define M_DIFFISTR_EXTRA_6	"Extra_6"

#define M_DIFFISTR_EASY_S		"E"
#define M_DIFFISTR_NORMAL_S		"N"
#define M_DIFFISTR_HARD_S		"H"
#define M_DIFFISTR_DESTINY_S	"Des"
#define M_DIFFISTR_EXTRA_S		"Ex"

#define M_STAGESTR_PRE			"S-"
#define M_STAGESTR_STAGEPRE		"Stage "
#define M_REPLAY_SAVEFILEPRE	"DES_"

#define	M_RPYMODE_SPELL		1
#define	M_RPYMODE_PRACTICE	2

#define M_MODE_NORMAL	0
#define M_MODE_STAGE	M_RPYMODE_PRACTICE
#define M_MODE_SPELL	(M_RPYMODE_PRACTICE | M_RPYMODE_SPELL)

#define M_MATCHMODE_N2N	0x01
#define M_MATCHMODE_P2P	0x02
#define M_MATCHMODE_P2C	0x04
#define M_MATCHMODE_C2P	0x08
#define M_MATCHMODE_C2C	0x10

#define M_PATHMAX		_MAX_PATH
#define M_STRMAX		0x80
#define M_STRITOAMAX	0x10

#define	M_LATENCY_NULL	0
#define	M_LATENCY_MIN	1
#define	M_LATENCY_MAX	9

#define M_STAGENSCENE	100

#define M_STAGESCENE_1_E	1
#define M_STAGESCENE_1_N	2
#define M_STAGESCENE_1_H	3
#define M_STAGESCENE_2_E	4
#define M_STAGESCENE_2_N	5
#define M_STAGESCENE_2_H	5
#define M_STAGESCENE_3_E	6
#define M_STAGESCENE_3_N	6
#define M_STAGESCENE_3_H	6
#define M_STAGESCENE_4_E	7
#define M_STAGESCENE_4_N	7
#define M_STAGESCENE_4_H	8
#define M_STAGESCENE_5_E	9
#define M_STAGESCENE_5_N	10
#define M_STAGESCENE_5_H	10
#define M_STAGESCENE_6_E	11
#define M_STAGESCENE_6_N	11
#define M_STAGESCENE_6_H	11

#define M_SQUARE_2			0.70710678f

#define M_BINHEADER_OFFSET	0x40

#define M_KAILLERMAXPLAYER	8

#define PLAYERTYPEMAX		0x20
#define SCENEMAX			PLAYERTYPEMAX
//#define SPRITEITEMMAX		0x1000
#define SPELLDATAMAX		PLAYERTYPEMAX
#define BULLETTYPEMAX		0x40
#define PLAYERGHOSTMAX		4
#define PLAYERGHOSTTYPEMAX	(PLAYERGHOSTMAX * PLAYERTYPEMAX * 2)
#define PLAYERBULLETTYPE		4
#define PLAYERSHOOTTYPEMAX		(PLAYERTYPEMAX * (PLAYERGHOSTMAX + 2))
#define ENEMYTYPEMAX		0x50
#define EFFECTSYSTYPEMAX	0x100
#define TEXMAX				0x300
#define TEX_WHITE		0
#define TEX_WORD		1
#define TEX_BULLET		2//7
#define TEX_GHOST		3//8
#define PACKAGEMAX			0x20
#define MUSICMAX			0x40
#define SEMAX				0x80
#define FONTSYSMAX			0x40
#define STRINGDESCMAX		0x400
#define M_SAVEINPUTMAX		0x36000
#define M_SCRIPTFOLDERMAX	8

#if defined __RELEASE || defined __IPHONE
	#define DEFAULT_RESOURCEPATH	"Resource"
#else
	#define DEFAULT_RESOURCEPATH	"../../Resource"
#endif

#if defined __RELEASE || defined __IPHONE
	#define DEFAULT_RESOURCEPATH_BASE	"Resource"
#else
	#define DEFAULT_RESOURCEPATH_BASE	"../../Resource_Base"
#endif

#if defined _WIN32 && defined __RESOURCE_BASE
	#undef DEFAULT_RESOURCEPATH
	#define DEFAULT_RESOURCEPATH DEFAULT_RESOURCEPATH_BASE
#endif

#ifdef __RELEASE
	#define DEFAULT_HGEDLLPATH		"Resource/hge.dll"
#else
	#ifdef _DEBUG
		#define DEFAULT_HGEDLLPATH		"../../Resource/Debug/hge_d.dll"
	#else
		#define DEFAULT_HGEDLLPATH		"../../Resource/hge.dll"
	#endif // _DEBUG
#endif // __RELEASE

//pushtimer
#define M_PUSH_FIRST	40
#define M_PUSH_ROLLTO	32
#define M_PUSH_SKIP		5
#define M_NOPUSH_SKIP	240

//script

#define SCR_CUSTOMCONSTMAX	0x400

//
#define M_RENDER_NULL		0x00
#define M_RENDER_LEFT		0x01
#define	M_RENDER_RIGHT		0x02
#define M_RENDER_SUPER		0x03


enum{
	S0 = 100,
	S100 = 100,
	S700 = 700,
	S1200 = 1200,
	S1 = 1800,

	SCLEAR = 100000
};


#define CINT(p)		(*(int *)(p))
#define CUINT(p)	(*(DWORD *)(p))
#define CFLOAT(p)	(*(float *)(p))
#define CLONGLONG(p)	(*(LONGLONG *)(p))
#define CULONGLONG(p)	(*(QWORD *)(p))
#define CDOUBLE(p)		(*(double *)(p))

#define CINTN(p)		(*(int *)(&(p)))
#define CUINTN(p)		(*(DWORD *)(&(p)))
#define CLONGLONGN(p)	(*(LONGLONG *)(&(p)))
#define CULONGLONGN(p)	(*(QWORD *)(&(p)))
#define CFLOATN(p)		(*(float *)(&(p)))
#define CDOUBLEN(p)		(*(double *)(&(p)))

#if defined __IPHONE
#define TOUCHPOINT_MAX	6
#endif

#endif