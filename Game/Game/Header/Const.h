#ifndef _CONST_H
#define _CONST_H

#define GAME_VERSION		0x090
#define GAME_VERSION_STR	"ver.0x090"
#define GAME_SIGNATURE		"h5nc"
#define GAME_TITLE			"Game"

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

#define HGELOG			hge->System_Log
#define HGELOG_ERRSTR	"**********ERROR**********"

#define M_DEFAULT_FPS			60
#define M_DEFAULT_FRAMESKIP		1
#define M_DEFAULT_RENDERSKIP	1
#define M_FRAMESKIP_FASTSKIP	-3
#define M_FRAMESKIP_SLOWSKIP	2

#define M_PROJECTIONMATRIX_OFFSET	0.5f

#define M_CLIENT_LEFT			(0.0f)
#define M_CLIENT_RIGHT			(640.0f)
#define M_CLIENT_TOP			(0.0f)
#define M_CLIENT_BOTTOM			(480.0f)
#define M_CLIENT_WIDTH			(M_CLIENT_RIGHT-M_CLIENT_LEFT)
#define M_CLIENT_HEIGHT			(M_CLIENT_BOTTOM-M_CLIENT_TOP)
#define M_CLIENT_CENTER_X		((M_CLIENT_LEFT+M_CLIENT_RIGHT)/2)
#define M_CLIENT_CENTER_Y		((M_CLIENT_TOP+M_CLIENT_BOTTOM)/2)

#define M_ACTIVECLIENT_LEFT		M_CLIENT_LEFT
#define M_ACTIVECLIENT_RIGHT	M_CLIENT_RIGHT
#define M_ACTIVECLIENT_TOP		M_CLIENT_TOP
#define M_ACTIVECLIENT_BOTTOM	M_CLIENT_BOTTOM
#define M_ACTIVECLIENT_WIDTH	(M_ACTIVECLIENT_RIGHT-M_ACTIVECLIENT_LEFT)
#define M_ACTIVECLIENT_HEIGHT	(M_ACTIVECLIENT_BOTTOM-M_ACTIVECLIENT_TOP)
#define M_ACTIVECLIENT_CENTER_X	((M_ACTIVECLIENT_LEFT+M_ACTIVECLIENT_RIGHT)/2)
#define M_ACTIVECLIENT_CENTER_Y	((M_ACTIVECLIENT_BOTTOM+M_ACTIVECLIENT_TOP)/2)

#define M_KEYKEYMAX			0x100
#define M_JOYKEYMAX			0x20

#define M_PATHMAX		_MAX_PATH
#define M_STRMAX		0x80
#define M_STRITOAMAX	0x10

#define M_FONTWIDTH		11
#define M_FONTHEIGHT	20

#define M_SECONDPERFRAME	0.01666667f

#define TEXMAX				0x100

#define TEX_WHITE		0

#ifdef __WIN32
#ifdef __RELEASE
	#define DEFAULT_RESOURCEPATH	"Resource"
#else
	#define DEFAULT_RESOURCEPATH	"../../Resource"
#endif

#else

#define DEFAULT_RESOURCEPATH	"Resource"

#endif // __WIN32

#ifdef __RELEASE
	#define DEFAULT_HGEDLLPATH		"Resource/hge.dll"
#else
	#ifdef _DEBUG
		#define DEFAULT_HGEDLLPATH		"../../Resource/Debug/hge_d.dll"
	#else
		#define DEFAULT_HGEDLLPATH		"../../Resource/hge.dll"
	#endif // _DEBUG
#endif // __RELEASE

//pan coefficient
#define M_SE_PAN 0.35f

//pushtimer
#define M_PUSH_FIRST	40
#define M_PUSH_ROLLTO	32
#define M_PUSH_SKIP		5
#define M_NOPUSH_SKIP	240

#endif