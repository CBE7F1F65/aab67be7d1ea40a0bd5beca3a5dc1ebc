/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** System layer API
*/


#ifndef HGE_H
#define HGE_H

#include "hge_defines.h"

/************************************************************************/
/* This header is added by h5nc (h5nc@yahoo.com.cn)                     */
/************************************************************************/
#ifdef __INTEL_COMPILER
	#ifdef __USE_INTEL_MATH_LAB
		#include <mathimf.h>
	#endif
#endif

/************************************************************************/
/* For h5nc use only                                                    */
/************************************************************************/
#define ZLIB_USEPSW

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#ifdef __WIN32
#ifdef WIN32
#ifdef _DEBUG
#include "../mmgr/mmgr.h"
#endif // _DEBUG
#endif // WIN32
#endif // __WIN32

#ifdef __WIN32

#include <windows.h>
#include <io.h>
#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>			//add by Thor/h5nc
#include <d3d9.h>			//add by Thor/h5nc
#include <d3dx9.h>			//add by Thor/h5nc
#pragma comment(lib,"dinput8.lib")

#endif

#define HGE_VERSION 0x180

#ifdef HGEDLL
#define EXPORT  __declspec(dllexport)
#else
#define EXPORT
#endif

#ifdef __WIN32
#define CALL  __stdcall
#else

#ifdef __PSP
#define CALL
#endif // __PSP

#ifdef __IPHONE
#define CALL
#include <ctype.h>
#include <wchar.h>
#endif // __IPHONE

#endif // __WIN32

#ifdef __BORLANDC__
 #define floorf (float)floor
 #define sqrtf (float)sqrt
 #define acosf (float)acos
 #define atan2f (float)atan2
 #define cosf (float)cos
 #define sinf (float)sin
 #define powf (float)pow
 #define fabsf (float)fabs

#endif
#ifndef min
#define min(x,y) ((x) < (y)) ? (x) : (y)
#endif
#ifndef max
#define max(x,y) ((x) > (y)) ? (x) : (y)
#endif

#ifndef ZeroMemory
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif

#ifndef __WIN32
typedef void *	LPDIRECTINPUT8;
#endif

/*
** Common data types
*/
#ifndef DWORD
#if defined __IPHONE
typedef unsigned int       DWORD;
#else
typedef unsigned long       DWORD;
#endif
typedef unsigned short      WORD;
typedef unsigned char       BYTE;
#endif

#ifndef QWORD
#if defined __WIN32
typedef unsigned __int64	QWORD;
#elif defined __PSP
typedef u64	QWORD;
#elif defined __IPHONE
typedef uint64_t QWORD;
#endif // __WIN32
#endif

#ifndef LONGLONG
#if defined __WIN32
typedef __int64			LONGLONG;
#elif __PSP
typedef s64	LONGLONG;
#elif __IPHONE
typedef int64_t LONGLONG;

#endif // __WIN32
typedef QWORD ULONGLONG;
#endif

#ifndef NULL
#define NULL	(0)
#endif

#ifndef isspace
#define isspace(X) ((X)==0x20 || (X)>=0x09&&(X)<=0x0D)
#endif
#ifndef iswspace
#define iswspace	isspace
#endif

#ifndef isdigit
#define isdigit(X) ((X)>='0' && (X)<='9')
#endif
#ifndef iswdigit
#define iswdigit	isdigit
#endif

#ifndef islower
#define islower(X) ((X)>='a' && (X)<='z')
#endif
#ifndef iswlower
#define iswlower	islower
#endif

#ifndef isupper
#define isupper(X) ((X)>='A' && (X)<='Z')
#endif
#ifndef iswupper
#define iswupper	isupper
#endif
/*
** Common math constants
*/
#ifndef M_PI
#define M_PI	3.14159265358979323846f
#define M_PI_2	1.57079632679489661923f
#define M_PI_4	0.785398163397448309616f
#define M_1_PI	0.318309886183790671538f
#define M_2_PI	0.636619772367581343076f
#endif

/************************************************************************/
/* These defines are added by h5nc (h5nc@yahoo.com.cn)                  */
/************************************************************************/
#ifndef M_E
#define M_E        2.71828182845904523536f
#define M_LOG2E    1.44269504088896340736f
#define M_LOG10E   0.434294481903251827651f
#define M_LN2      0.693147180559945309417f
#define M_LN10     2.30258509299404568402f
#define M_2_SQRTPI 1.12837916709551257390f
#define M_SQRT2    1.41421356237309504880f
#define M_SQRT1_2  0.707106781186547524401f
#endif

#ifndef __IPHONE
#define M_FOLDER_SLASH			'\\'
#define M_FOLDER_SLASH_WRONG	'/'
#else
#define M_FOLDER_SLASH			'/'
#define M_FOLDER_SLASH_WRONG	'\\'
#endif

/************************************************************************/
/* This define is added by h5nc (h5nc@yahoo.com.cn)                     */
/************************************************************************/
// Texture Offset
#define HGE_TEXTUREOFFSET	0.0f

/*
** HGE Handle types
*/
//typedef DWORD HTEXTURE;
typedef DWORD HTARGET;
typedef DWORD HSAMPLE;
typedef DWORD HEFFECT;
typedef DWORD HMUSIC;
typedef DWORD HSTREAM;
typedef DWORD HCHANNEL;

typedef struct tagHgeTextureInfo
{
	DWORD * tex;
	float texw;
	float texh;
}hgeTextureInfo;

class HTEXTURE
{
public:
	HTEXTURE()
	{
		_Init();
	};
	HTEXTURE(int _texindex, DWORD _tex)
	{
		_Init(_texindex, _tex);
	};
	HTEXTURE(DWORD _tex)
	{
		_Init(0, _tex);
	};

	HTEXTURE & operator = (DWORD _tex)
	{
		_Init(0, _tex);
		return *this;
	};
	DWORD GetTexture(int ntexinfo, hgeTextureInfo * texinfo)
	{
		if (!tex && texinfo && texindex<ntexinfo)
		{
			if (texinfo[texindex].tex)
			{
				return *texinfo[texindex].tex;
			}
			return NULL;
		}
		return tex;
	};
	int GetTextureWidthByInfo(int ntexinfo, hgeTextureInfo * texinfo)
	{
		if (!texinfo || texindex>=ntexinfo)
		{
			return 1;
		}
		return texinfo[texindex].texw;
	};
	int GetTextureHeightByInfo(int ntexinfo, hgeTextureInfo * texinfo)
	{
		if (!texinfo || texindex>=ntexinfo)
		{
			return 1;
		}
		return texinfo[texindex].texh;
	};
private:
	void _Init(int _texindex=0, DWORD _tex=NULL)
	{
		texindex=_texindex;
		tex = _tex;
	};
public:
	int texindex;
	DWORD tex;
};

/************************************************************************/
/* This define is added by Yuki                                         */
/* h5nc (h5nc@yahoo.com.cn) copied her codes with her permission        */
/************************************************************************/
/* add by Yuki */
typedef DWORD HD3DFONT;

/*
** Hardware color macros
*/
#define ARGB(a,r,g,b)	((DWORD(a)<<24) + (DWORD(r)<<16) + (DWORD(g)<<8) + DWORD(b))
#define GETA(col)		((col)>>24)
#define GETR(col)		(((col)>>16) & 0xFF)
#define GETG(col)		(((col)>>8) & 0xFF)
#define GETB(col)		((col) & 0xFF)
#define SETA(col,a)		(((col) & 0x00FFFFFF) + (DWORD(a)<<24))
#define SETR(col,r)		(((col) & 0xFF00FFFF) + (DWORD(r)<<16))
#define SETG(col,g)		(((col) & 0xFFFF00FF) + (DWORD(g)<<8))
#define SETB(col,b)		(((col) & 0xFFFFFF00) + DWORD(b))


/*
** HGE Blending constants
*/
#define	BLEND_COLORADD		1
#define	BLEND_COLORMUL		0
#define	BLEND_ALPHABLEND	2
#define	BLEND_ALPHAADD		0
#define	BLEND_ZWRITE		4
#define	BLEND_NOZWRITE		0

#define BLEND_DEFAULT		(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE)
#define BLEND_DEFAULT_Z		(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_ZWRITE)


/*
** HGE System state constants
*/

/************************************************************************/
/* This defines are added by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
#define HGE_STATE_MASK		0xff00
#define HGE_STATE_BOOLTEST		0x0100
#define HGE_STATE_FUNCTEST		0x0200
#define HGE_STATE_HWNDTEST		0x0300
#define HGE_STATE_INTTEST		0x0400
#define HGE_STATE_STRINGTEST	0x0500


/************************************************************************/
/* Thes defines are modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
enum hgeBoolState
{
	HGE_WINDOWED		= 0x0101,    // bool		run in window?		(default: false)
	HGE_ZBUFFER			= 0x0102,    // bool		use z-buffer?		(default: false)
	HGE_TEXTUREFILTER	= 0x0103,    // bool		texture filtering?	(default: true)
	
	HGE_USESOUND		= 0x0104,    // bool		use BASS for sound?	(default: true)
	
	HGE_DONTSUSPEND		= 0x0105,	// bool		focus lost:suspend?	(default: false)
	HGE_HIDEMOUSE		= 0x0106,	// bool		hide system cursor?	(default: true)
	
	HGE_2DMODE			= 0x0107,	// bool		2d mode? (default: true)
	
	HGE_MANAGELOOP		= 0x0108,	// bool		manage loop? (default: true)
	
	HGEBOOLSTATE_FORCE_DWORD = 0x7FFFFFFF
};

enum hgeFuncState
{
	HGE_FRAMEFUNC		= 0x0201,    // bool*()	frame function		(default: NULL) (you MUST set this)
	HGE_RENDERFUNC		= 0x0202,    // bool*()	render function		(default: NULL)
	HGE_FOCUSLOSTFUNC	= 0x0203,   // bool*()	focus lost function	(default: NULL)
	HGE_FOCUSGAINFUNC	= 0x0204,   // bool*()	focus gain function	(default: NULL)
	HGE_GFXRESTOREFUNC	= 0x0205,   // bool*()	graphics restore function		(default: NULL)
	HGE_EXITFUNC		= 0x0206,   // bool*()	exit function		(default: NULL)

	HGE_LOADTEXTUREFUNC	= 0x0211,	// bool*()	load texture function	(default: NULL)
	
	HGEFUNCSTATE_FORCE_DWORD = 0x7FFFFFFF
};

enum hgeHwndState
{
	HGE_HWND			= 0x0301,	// int		window handle: read only
	HGE_HWNDPARENT		= 0x0302,	// int		parent win handle	(default: 0)
	
	HGEHWNDSTATE_FORCE_DWORD = 0x7FFFFFFF
};

enum hgeIntState
{
	HGE_SCREENWIDTH		= 0x0401,   // int		screen width		(default: 800)
	HGE_SCREENHEIGHT	= 0x0402,   // int		screen height		(default: 600)
	HGE_SCREENBPP		= 0x0403,   // int		screen bitdepth		(default: 32) (desktop bpp in windowed mode)
	
	HGE_SAMPLERATE		= 0x0404,   // int		sample rate			(default: 44100)
	HGE_SAMPLEVOLUME	= 0x0405,	// int		global sample volume(default: 10000)
	HGE_FXVOLUME		= 0x0406,   // int		global fx volume	(default: 10000)
//	HGE_MUSVOLUME		= 0x0406,   // int		global music volume	(default: 10000)
	HGE_STREAMVOLUME	= 0x0407,   // int		global music volume	(default: 10000)	
	HGE_FPS				= 0x0408,	// int		fixed fps			(default: HGEFPS_UNLIMITED)

	/************************************************************************/
	/* These defines are added by h5nc (h5nc@yahoo.com.cn)                  */
	/************************************************************************/
	//Begin
	HGE_FRAMECOUNTER	= 0x0409,	//int		frame counter;	read only
	HGE_FRAMESKIP		= 0x040A,	//int		frame skip			(default: 0)
	HGE_RENDERSKIP		= 0x040B,	//int		render skip			(default: 0)
	//End
	
	HGEINTSTATE_FORCE_DWORD = 0x7FFFFFF
};

enum hgeStringState
{
	HGE_ICON			= 0x0501,   // char*	icon resource		(default: NULL)
	HGE_TITLE			= 0x0502,   // char*	window title		(default: "HGE")
	
	HGE_INIFILE			= 0x0503,   // char*	ini file			(default: NULL) (meaning no file)
	HGE_LOGFILE			= 0x0504,   // char*	log file			(default: NULL) (meaning no file)

	/************************************************************************/
	/* This define is added by h5nc (h5nc@yahoo.com.cn)                     */
	/************************************************************************/
	HGE_BASSDLLFILE		= 0x0505,	// char*	bass.dll file		(default: "BASS.dll")

	HGESTRINGSTATE_FORCE_DWORD = 0x7FFFFFFF
};

/*
** Callback protoype used by HGE
*/
typedef bool (*hgeCallback)();


/*
** HGE_FPS system state special constants
*/
#define HGEFPS_UNLIMITED	0
#define HGEFPS_VSYNC		-1
//
/************************************************************************/
/* This define is added by h5nc (h5nc@yahoo.com.cn)                     */
/************************************************************************/
#define HGEFPS_MAX			1000

/*
** HGE Primitive type constants
*/
#define HGEPRIM_POINTS		1
#define HGEPRIM_LINES		2
#define HGEPRIM_TRIPLES		3
#define HGEPRIM_QUADS		4


/*
** HGE Vertex structure
*/
struct hgeVertex
{
	float			x, y;		// screen position    
	float			z;			// Z-buffer depth 0..1
	DWORD			col;		// color
	float			tx, ty;		// texture coordinates
};

#ifdef __PSP
struct pspVertex
{
	unsigned int color;
	float x,y,z;
};

struct pspVertexUV
{
	float u, v;
	unsigned int color;
	float x,y,z;
};
#endif // __PSP


/*
** HGE Triple structure
*/
struct hgeTriple
{
	hgeVertex		v[3];
	HTEXTURE		tex;
	int				blend;
};


/*
** HGE Quad structure
*/
struct hgeQuad
{
	hgeVertex		v[4];
	HTEXTURE		tex;
	int				blend;
};


/*
** HGE Input Event structure
*/
struct hgeInputEvent
{
	int		type;			// event type
	int		key;			// key code
	int		flags;			// event flags
	int		chr;			// character code
	int		wheel;			// wheel shift
	float	x;				// mouse cursor x-coordinate
	float	y;				// mouse cursor y-coordinate
};


/*
** HGE Input Event type constants
*/
#define INPUT_KEYDOWN		1
#define INPUT_KEYUP			2
#define INPUT_MBUTTONDOWN	3
#define INPUT_MBUTTONUP		4
#define INPUT_MOUSEMOVE		5
#define INPUT_MOUSEWHEEL	6


/*
** HGE Input Event flags
*/
#define HGEINP_SHIFT		1
#define HGEINP_CTRL			2
#define HGEINP_ALT			4
#define HGEINP_CAPSLOCK		8
#define HGEINP_SCROLLLOCK	16
#define HGEINP_NUMLOCK		32
#define HGEINP_REPEAT		64

/************************************************************************/
/* This define is added by h5nc (h5nc@yahoo.com.cn)                     */
/************************************************************************/
/*
**HGE Memory File Info
*/
struct hgeMemoryFile
{
	char * filename;
	BYTE * data;
	DWORD size;
};

/************************************************************************/
/* This define is added by h5nc (h5nc@yahoo.com.cn)                     */
/************************************************************************/
/*
**HGE Channel Sync Info
*/

struct hgeChannelSyncInfo 
{
	QWORD startPos;
	QWORD allLength;
	QWORD introLength;
	DWORD/*HSYNC*/ sync;
};

/************************************************************************/
/* These defines are added by h5nc (h5nc@yahoo.com.cn)                  */
/************************************************************************/
/*
**HGE Point
*/

struct hge2DPoint 
{
	float x;
	float y;
};

struct hge3DPoint 
{
	float x;
	float y;
	union {
		float z;
		float scale;
	};
};

/************************************************************************/
/* These defines are added by h5nc (h5nc@yahoo.com.cn)                  */
/************************************************************************/
// begin
#define DIKEY_PRESSED	0x0
#define DIKEY_UP		0x10
#define DIKEY_DOWN		0x20

#define JOY_LEFT		0x40
#define JOY_RIGHT		0x50
#define JOY_UP			0x60
#define JOY_DOWN		0x70

#define DIJOY_MAXDEVICE	4

#define TOUCH_TOUCHMAX	5
// end

/*
** HGE Virtual-key codes
*/
#define HGEK_LBUTTON	0x01
#define HGEK_RBUTTON	0x02
#define HGEK_MBUTTON	0x04

#define HGEK_ESCAPE		0x1B
#define HGEK_BACKSPACE	0x08
#define HGEK_TAB		0x09
#define HGEK_ENTER		0x0D
#define HGEK_SPACE		0x20

#define HGEK_SHIFT		0x10
#define HGEK_CTRL		0x11
#define HGEK_ALT		0x12

#define HGEK_LWIN		0x5B
#define HGEK_RWIN		0x5C
#define HGEK_APPS		0x5D

#define HGEK_PAUSE		0x13
#define HGEK_CAPSLOCK	0x14
#define HGEK_NUMLOCK	0x90
#define HGEK_SCROLLLOCK	0x91

#define HGEK_PGUP		0x21
#define HGEK_PGDN		0x22
#define HGEK_HOME		0x24
#define HGEK_END		0x23
#define HGEK_INSERT		0x2D
#define HGEK_DELETE		0x2E

#define HGEK_LEFT		0x25
#define HGEK_UP			0x26
#define HGEK_RIGHT		0x27
#define HGEK_DOWN		0x28

#define HGEK_0			0x30
#define HGEK_1			0x31
#define HGEK_2			0x32
#define HGEK_3			0x33
#define HGEK_4			0x34
#define HGEK_5			0x35
#define HGEK_6			0x36
#define HGEK_7			0x37
#define HGEK_8			0x38
#define HGEK_9			0x39

#define HGEK_A			0x41
#define HGEK_B			0x42
#define HGEK_C			0x43
#define HGEK_D			0x44
#define HGEK_E			0x45
#define HGEK_F			0x46
#define HGEK_G			0x47
#define HGEK_H			0x48
#define HGEK_I			0x49
#define HGEK_J			0x4A
#define HGEK_K			0x4B
#define HGEK_L			0x4C
#define HGEK_M			0x4D
#define HGEK_N			0x4E
#define HGEK_O			0x4F
#define HGEK_P			0x50
#define HGEK_Q			0x51
#define HGEK_R			0x52
#define HGEK_S			0x53
#define HGEK_T			0x54
#define HGEK_U			0x55
#define HGEK_V			0x56
#define HGEK_W			0x57
#define HGEK_X			0x58
#define HGEK_Y			0x59
#define HGEK_Z			0x5A

#define HGEK_GRAVE		0xC0
#define HGEK_MINUS		0xBD
#define HGEK_EQUALS		0xBB
#define HGEK_BACKSLASH	0xDC
#define HGEK_LBRACKET	0xDB
#define HGEK_RBRACKET	0xDD
#define HGEK_SEMICOLON	0xBA
#define HGEK_APOSTROPHE	0xDE
#define HGEK_COMMA		0xBC
#define HGEK_PERIOD		0xBE
#define HGEK_SLASH		0xBF

#define HGEK_NUMPAD0	0x60
#define HGEK_NUMPAD1	0x61
#define HGEK_NUMPAD2	0x62
#define HGEK_NUMPAD3	0x63
#define HGEK_NUMPAD4	0x64
#define HGEK_NUMPAD5	0x65
#define HGEK_NUMPAD6	0x66
#define HGEK_NUMPAD7	0x67
#define HGEK_NUMPAD8	0x68
#define HGEK_NUMPAD9	0x69

#define HGEK_MULTIPLY	0x6A
#define HGEK_DIVIDE		0x6F
#define HGEK_ADD		0x6B
#define HGEK_SUBTRACT	0x6D
#define HGEK_DECIMAL	0x6E

#define HGEK_F1			0x70
#define HGEK_F2			0x71
#define HGEK_F3			0x72
#define HGEK_F4			0x73
#define HGEK_F5			0x74
#define HGEK_F6			0x75
#define HGEK_F7			0x76
#define HGEK_F8			0x77
#define HGEK_F9			0x78
#define HGEK_F10		0x79
#define HGEK_F11		0x7A
#define HGEK_F12		0x7B

/*
** HGE Interface class
*/
class HGE
{
public:
	virtual	void		CALL	Release() = 0;

	virtual bool		CALL	System_Initiate() = 0;
	virtual void		CALL	System_Shutdown() = 0;
	virtual bool		CALL	System_Start() = 0;
	virtual char*		CALL	System_GetErrorMessage() = 0;
	virtual	void		CALL	System_Log(const char *format, ...) = 0;
	virtual bool		CALL	System_Launch(const char *url) = 0;
	virtual void		CALL	System_Snapshot(const char *filename=0) = 0;
	virtual int			CALL	System_MessageBox(const char * text, const char * title, DWORD type) = 0;

private:
	virtual void		CALL	System_SetStateBool  (hgeBoolState   state, bool        value) = 0;
	virtual void		CALL	System_SetStateFunc  (hgeFuncState   state, hgeCallback value) = 0;
	virtual void		CALL	System_SetStateHwnd  (hgeHwndState   state, HWND        value) = 0;
	virtual void		CALL	System_SetStateInt   (hgeIntState    state, int         value) = 0;
	virtual void		CALL	System_SetStateString(hgeStringState state, const char *value) = 0;
	virtual bool		CALL	System_GetStateBool  (hgeBoolState   state) = 0;
	virtual hgeCallback	CALL	System_GetStateFunc  (hgeFuncState   state) = 0;
	virtual HWND		CALL	System_GetStateHwnd  (hgeHwndState   state) = 0;
	virtual int			CALL	System_GetStateInt   (hgeIntState    state) = 0;
	virtual const char*	CALL	System_GetStateString(hgeStringState state) = 0;

public:
	inline void					System_SetState(hgeBoolState   state, bool        value) { System_SetStateBool  (state, value); }
	inline void					System_SetState(hgeFuncState   state, hgeCallback value) { System_SetStateFunc  (state, value); }
	inline void					System_SetState(hgeHwndState   state, HWND        value) { System_SetStateHwnd  (state, value); }
	inline void					System_SetState(hgeIntState    state, int         value) { System_SetStateInt   (state, value); }
	inline void					System_SetState(hgeStringState state, const char *value) { System_SetStateString(state, value); }
	inline bool					System_GetState(hgeBoolState   state) { return System_GetStateBool  (state); }
	inline hgeCallback			System_GetState(hgeFuncState   state) { return System_GetStateFunc  (state); }
	inline HWND					System_GetState(hgeHwndState   state) { return System_GetStateHwnd  (state); }
	inline int					System_GetState(hgeIntState    state) { return System_GetStateInt   (state); }
	inline const char*			System_GetState(hgeStringState state) { return System_GetStateString(state); }

	/************************************************************************/
	/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	// begin
	virtual float		CALL	Math_Transform3DPoint(hge3DPoint * pt, hge3DPoint *ptfar=NULL) = 0;
	virtual float		CALL	Math_Transform3DPoint(float &x, float &y, float &z, hge3DPoint *ptfar=NULL) = 0;
	// end
	virtual char*		CALL	Math_itoa(int ival, char * buffer) = 0;
	virtual int			CALL	Math_atoi(const char * buffer) = 0;
	virtual char*		CALL	Math_ftoa(float fval, char * buffer) = 0;
	virtual float		CALL	Math_atof(const char * buffer) = 0;
	virtual LONGLONG	CALL	Math_atoll(const char * buffer) = 0;
	virtual D3DXMATRIX*	CALL	Math_MatrixIdentity( D3DXMATRIX * pOut ) = 0;
	virtual D3DXMATRIX*	CALL	Math_MatrixTranslation( D3DXMATRIX *pOut, float x, float y, float z ) = 0;
	virtual D3DXMATRIX*	CALL	Math_MatrixRotationX( D3DXMATRIX *pOut, float angle ) = 0;
	virtual D3DXMATRIX*	CALL	Math_MatrixRotationY( D3DXMATRIX *pOut, float angle ) = 0;
	virtual D3DXMATRIX*	CALL	Math_MatrixRotationZ( D3DXMATRIX *pOut, float angle ) = 0;
	virtual D3DXMATRIX*	CALL	Math_MatrixScaling( D3DXMATRIX *pOut, float sx, float sy, float sz ) = 0;
	virtual D3DXMATRIX*	CALL	Math_MatrixMultiply( D3DXMATRIX *pOut, const D3DXMATRIX *pM1, const D3DXMATRIX *pM2 ) = 0;
	virtual D3DXMATRIX*	CALL	Math_MatrixOrthoOffCenterLH(D3DXMATRIX *pOut, float l, float r, float b, float t, float zn, float zf) = 0;

	/************************************************************************/
	/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	virtual void		CALL	Resource_DeleteFile(const char *filename) = 0;
	virtual DWORD		CALL	Resource_FileSize(const char *filename, FILE * file=NULL) = 0;
	virtual void		CALL	Resource_SetCurrentDirectory(const char *filename) = 0;
	virtual BYTE*		CALL	Resource_Load(const char *filename, DWORD *size=0) = 0;
	virtual void		CALL	Resource_Free(void *res) = 0;
	/************************************************************************/
	/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	virtual bool		CALL	Resource_AttachPack(const char *filename, int password=0) = 0;
	virtual void		CALL	Resource_RemovePack(const char *filename) = 0;
	virtual void		CALL	Resource_RemoveAllPacks() = 0;
	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	virtual char*		CALL	Resource_SetPath(const char *filename) = 0;
	/************************************************************************/
	/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	virtual char*		CALL	Resource_MakePath(const char *filename) = 0;
	virtual char*		CALL	Resource_EnumFiles(const char *wildcard=0) = 0;
	virtual char*		CALL	Resource_EnumFolders(const char *wildcard=0) = 0;
	virtual bool		CALL	Resource_AccessFile(const char *filename) = 0;
	virtual bool		CALL	Resource_CreateDirectory(const char *filename) = 0;
	/************************************************************************/
	/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	// begin
	virtual bool		CALL	Resource_CreatePack(const char * filename, int password, hgeMemoryFile * first, ...) = 0;
	virtual bool		CALL	Resource_AddFileInPack(const char * filename, int password, hgeMemoryFile * memfile) = 0;
	virtual DWORD		CALL	Resource_GetCRC(const BYTE * content, DWORD size) = 0;
#ifdef ZLIB_USEPSW
	virtual int			CALL	Resource_GetPSW(int psw) = 0;
#else
	virtual char*		CALL	Resource_GetPSW(int psw) = 0;
#endif // ZLIB_USEPSW
	virtual char*		CALL	Resource_GetPackFirstFileName(const char * packfilename) = 0;
	// end

	virtual	void		CALL	Ini_SetInt(const char *section, const char *name, int value, char * inifilename=NULL) = 0;
	virtual	int			CALL	Ini_GetInt(const char *section, const char *name, int def_val, char * inifilename=NULL) = 0;
	virtual	void		CALL	Ini_SetFloat(const char *section, const char *name, float value, char * inifilename=NULL) = 0;
	virtual	float		CALL	Ini_GetFloat(const char *section, const char *name, float def_val, char * inifilename=NULL) = 0;
	virtual	void		CALL	Ini_SetString(const char *section, const char *name, const char *value, char * inifilename=NULL) = 0;
	virtual	char*		CALL	Ini_GetString(const char *section, const char *name, const char *def_val, char * inifilename=NULL) = 0;

	/************************************************************************/
	/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	virtual int			CALL	Random_Seed(int seed=0) = 0;
	virtual int			CALL	Random_Int(int min, int max, bool bSelf=false) = 0;
	virtual float		CALL	Random_Float(float min, float max, bool bSelf=false) = 0;

	virtual void		CALL	Timer_GetSystemTime(WORD *wYear=NULL, WORD *wMonth=NULL, WORD *wDayOfWeek=NULL, WORD *wDay=NULL, WORD *wHour=NULL, WORD *wMinute=NULL, WORD *wSecond=NULL, WORD *wMilliseconds=NULL) = 0;
	virtual LONGLONG	CALL	Timer_GetFileTime() = 0;
	virtual float		CALL	Timer_GetTime() = 0;
	virtual float		CALL	Timer_GetDelta() = 0;
	/************************************************************************/
	/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	virtual float		CALL	Timer_GetFPS(int mod = 0) = 0;
	/************************************************************************/
	/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	// begin
	virtual float		CALL	Timer_GetWorstFPS(int mod) = 0;
	virtual	LONGLONG	CALL	Timer_GetCurrentSystemTime() = 0;
	virtual LONGLONG	CALL	Timer_GetPerformanceFrequency() = 0;
	//end

	virtual HEFFECT		CALL	Effect_Load(const char *filename, DWORD size=0) = 0;
	virtual void		CALL	Effect_Free(HEFFECT eff) = 0;
	virtual HCHANNEL	CALL 	Effect_Play(HEFFECT eff) = 0;
	virtual HCHANNEL	CALL	Effect_PlayEx(HEFFECT eff, int volume=100, int pan=0, float pitch=1.0f, bool loop=false) = 0;

	/************************************************************************/
	/* These functions are deleted by h5nc (h5nc@yahoo.com.cn)              */
	/************************************************************************/
/*
	virtual HMUSIC		CALL	Music_Load(const char *filename, DWORD size=0) = 0;
	virtual void		CALL	Music_Free(HMUSIC mus) = 0;
	virtual HCHANNEL	CALL	Music_Play(HMUSIC mus, bool loop, int volume = 100, int order = -1, int row = -1) = 0;
	virtual void		CALL	Music_SetAmplification(HMUSIC music, int ampl) = 0;
	virtual int			CALL	Music_GetAmplification(HMUSIC music) = 0;
	virtual int			CALL	Music_GetLength(HMUSIC music) = 0;
	virtual void		CALL	Music_SetPos(HMUSIC music, int order, int row) = 0;
	virtual bool		CALL	Music_GetPos(HMUSIC music, int *order, int *row) = 0;
	virtual void		CALL	Music_SetInstrVolume(HMUSIC music, int instr, int volume) = 0;
	virtual int			CALL	Music_GetInstrVolume(HMUSIC music, int instr) = 0;
	virtual void		CALL	Music_SetChannelVolume(HMUSIC music, int channel, int volume) = 0;
	virtual int			CALL	Music_GetChannelVolume(HMUSIC music, int channel) = 0;
*/
	virtual HSTREAM		CALL	Stream_Load(const char *filename, DWORD size=0, bool bLoad=true) = 0;
	virtual void		CALL	Stream_Free(HSTREAM stream) = 0;
	virtual HCHANNEL	CALL	Stream_Play(HSTREAM stream, bool loop, int volume = 100) = 0;

	virtual void		CALL	Channel_SetPanning(HCHANNEL chn, int pan) = 0;
	virtual void		CALL 	Channel_SetVolume(HCHANNEL chn, int volume) = 0;
	virtual void		CALL 	Channel_SetPitch(HCHANNEL chn, float pitch) = 0;
	virtual void		CALL 	Channel_Pause(HCHANNEL chn) = 0;
	virtual void		CALL 	Channel_Resume(HCHANNEL chn) = 0;
	virtual void		CALL 	Channel_Stop(HCHANNEL chn) = 0;
	virtual void		CALL 	Channel_PauseAll() = 0;
	virtual void		CALL 	Channel_ResumeAll() = 0;
	virtual void		CALL 	Channel_StopAll() = 0;
	virtual bool		CALL	Channel_IsPlaying(HCHANNEL chn) = 0;
	virtual QWORD		CALL	Channel_GetLength(HCHANNEL chn) = 0;
	virtual QWORD		CALL	Channel_GetPos(HCHANNEL chn) = 0;
	virtual void		CALL	Channel_SetPos(HCHANNEL chn, QWORD pos) = 0;
	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	virtual void		CALL	Channel_SetStartPos(HCHANNEL chn, hgeChannelSyncInfo * pcsi) = 0;
	virtual void		CALL	Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan = -101, float pitch = -1) = 0;
	virtual bool		CALL	Channel_IsSliding(HCHANNEL channel) = 0;

	/************************************************************************/
	/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	// begin
	virtual void		CALL	Channel_SetLoop(HCHANNEL channel, hgeChannelSyncInfo * pcsi) = 0;
	virtual void		CALL	Channel_RemoveLoop(HCHANNEL channel, hgeChannelSyncInfo * pcsi) = 0;
	// end

	virtual void		CALL	Input_GetMousePos(float *x, float *y) = 0;
	virtual void		CALL	Input_SetMousePos(float x, float y) = 0;
	virtual int			CALL	Input_GetMouseWheel() = 0;
	virtual bool		CALL	Input_IsMouseOver() = 0;
	virtual bool		CALL	Input_KeyDown(int key) = 0;
	virtual bool		CALL	Input_KeyUp(int key) = 0;
	virtual bool		CALL	Input_GetKeyState(int key) = 0;
	virtual char*		CALL	Input_GetKeyName(int key) = 0;
	virtual int			CALL	Input_GetKey() = 0;
	virtual int			CALL	Input_GetChar() = 0;
	virtual bool		CALL	Input_GetEvent(hgeInputEvent *event) = 0;

	/************************************************************************/
	/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	// begin
	virtual LPDIRECTINPUT8 CALL Input_GetDevice() = 0;
	virtual bool		CALL	Input_GetDIKey(int key, BYTE stateType = DIKEY_PRESSED) = 0;
	virtual bool		CALL	Input_SetDIKey(int key, bool set = true) = 0;
	virtual bool		CALL	Input_GetDIJoy(int joy, BYTE stateType = DIKEY_PRESSED, int joydevice=0) = 0;
	virtual bool		CALL	Input_HaveJoy(int joydevice=0) = 0;

	virtual bool		CALL	Input_IsTouchDown(int touch) = 0;
	virtual bool		CALL	Input_IsTouchOn(int touch) = 0;
	virtual bool		CALL	Input_IsTouchUp(int touch) = 0;
	virtual void		CALL	Input_GetTouchPos(int touch, float *x, float *y) = 0;
	virtual void		CALL	Input_GetLastTouchPos(int touch, float *x, float *y) = 0;
	virtual void		CALL	Input_GetFirstTouchPos(int touch, float *x, float *y) = 0;
	virtual int			CALL	Input_GetTouchDuration(int touch) = 0;
	virtual int			CALL	Input_GetNoTouchDuration(int touch) = 0;
	virtual void		CALL	Input_SetTouchPos(int touch, float x, float y) = 0;
	// end

	virtual bool		CALL	Gfx_BeginScene(HTARGET target=0) = 0;
	virtual void		CALL	Gfx_EndScene() = 0;
	virtual void		CALL	Gfx_Clear(DWORD color) = 0;
	virtual void		CALL	Gfx_RenderPoint(float x, float y, float z=0.0f, DWORD color=0xFFFFFFFF) = 0;
	virtual void		CALL	Gfx_RenderLine(float x1, float y1, float x2, float y2, DWORD color=0xFFFFFFFF, float z=0) = 0;
	virtual void		CALL	Gfx_RenderTriple(const hgeTriple *triple) = 0;
	virtual void		CALL	Gfx_RenderQuad(const hgeQuad *quad) = 0;
	virtual hgeVertex*	CALL	Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend, int *max_prim) = 0;
	virtual void		CALL	Gfx_FinishBatch(int nprim) = 0;
	virtual void		CALL	Gfx_SetClipping(int x=0, int y=0, int w=0, int h=0) = 0;
	virtual void		CALL	Gfx_SetTransform(float x=0, float y=0, float dx=0, float dy=0, float rot=0, float hscale=0, float vscale=0) = 0;
	/************************************************************************/
	/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	virtual void		CALL	Gfx_SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX * pMatrix) = 0;
	virtual D3DMATRIX	CALL	Gfx_GetTransform(D3DTRANSFORMSTATETYPE State) = 0;

	virtual void	CALL	Gfx_SetTextureInfo(int nTexInfo, hgeTextureInfo * texInfo=NULL) = 0;

	virtual HTARGET		CALL	Target_Create(int width, int height, bool zbuffer) = 0;
	virtual void		CALL	Target_Free(HTARGET target) = 0;
	virtual HTEXTURE	CALL	Target_GetTexture(HTARGET target) = 0;

	virtual HTEXTURE	CALL	Texture_Create(int width, int height) = 0;
	virtual HTEXTURE	CALL	Texture_Load(const char *filename, DWORD size=0, bool bMipmap=false) = 0;
	virtual void		CALL	Texture_Free(HTEXTURE tex) = 0;
	virtual DWORD		CALL	Texture_GetTexture(HTEXTURE tex) = 0;
	virtual int			CALL	Texture_GetWidth(HTEXTURE tex, bool bOriginal=false) = 0;
	virtual int			CALL	Texture_GetHeight(HTEXTURE tex, bool bOriginal=false) = 0;
	virtual DWORD*		CALL	Texture_Lock(HTEXTURE tex, bool bReadOnly=true, int left=0, int top=0, int width=0, int height=0) = 0;
	virtual void		CALL	Texture_Unlock(HTEXTURE tex) = 0;
	virtual bool		CALL	Texture_Save(HTEXTURE tex, const char * filename, DWORD filetype) = 0;

	virtual bool		CALL	Texture_LoadTextureWhenNeeded(HTEXTURE * tex) = 0;
	virtual void		CALL	Texture_SetTextureToLoad(HTEXTURE * tex) = 0;
	virtual HTEXTURE *	CALL	Texture_GetTextureToLoad() = 0;

	/************************************************************************/
	/* These functions are added by Yuki                                    */
	/************************************************************************/
	/* add by Yuki */
	// begin
	virtual HD3DFONT    CALL	Font_Load(const char * fontStyle,int height) = 0;
	virtual void		CALL	Font_Free(HD3DFONT font) = 0;
	virtual int			CALL	Gfx_RenderText(HD3DFONT font, const char * text, float x, float y, float w, float h, DWORD color = 0xffffffff) = 0;
	virtual int			CALL	Gfx_RenderTextToTarget(HTEXTURE * tex, HTARGET tar, HD3DFONT font, const char * text, float x, float y, float w, float h, DWORD color = 0xffffffff) = 0;
	// end

};

extern "C" { EXPORT HGE * CALL hgeCreate(int ver); }

#endif

