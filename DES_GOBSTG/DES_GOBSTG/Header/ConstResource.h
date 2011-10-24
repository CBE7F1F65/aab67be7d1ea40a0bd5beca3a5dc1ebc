#ifndef _CONSTRESOURCE_H
#define _CONSTRESOURCE_H

#include "Const.h"

//consts

#define LOG_STR_FILENAME		"log.log"

#define DATA_DEFAULTSTR_WIDE	"������������"
#define DATA_DEFAULTSTR			"????"

#define CONFIG_STR_FILENAME				"Config.ini"

#define RESDATASTR_FOLDER_DATA		"Data/"
#define RESDATASTR_FOLDER_GRAPHIC	"Graphic/"
#define RESDATASTR_FOLDER_REPLAY	"Replay/"
#define RESDATASTR_FOLDER_EFFECTSYS	"EffectSys/"
#define RESDATASTR_FOLDER_MUSIC		"Music/"
#define RESDATASTR_FOLDER_SE		"Se/"
#define RESDATASTR_FOLDER_SNAPSHOT	"SnapShot/"

#define RESDATASTR_FONTFILENAME	RESDATASTR_FOLDER_DATA "font.fnt"
#define RESDATASTR_WIDEFONTNAME	"MS Gothic"
#define RESDATASTR_RESFILENAME	RESDATASTR_FOLDER_DATA "Res.databin"
#define RESDATASTR_BINFILENAME	RESDATASTR_FOLDER_DATA "Bin.databin"

#define RESDATASTR_TABLE_CUSTOMCONST	RESDATASTR_FOLDER_DATA "CustomConst.table"
#define RESDATASTR_TABLE_MUSIC			RESDATASTR_FOLDER_DATA "Music.table"
#define RESDATASTR_TABLE_BULLET			RESDATASTR_FOLDER_DATA "Bullet.table"
#define RESDATASTR_TABLE_ENEMY			RESDATASTR_FOLDER_DATA "Enemy.table"
#define RESDATASTR_TABLE_PLAYER			RESDATASTR_FOLDER_DATA "Player.table"
#define RESDATASTR_TABLE_SPRITE			RESDATASTR_FOLDER_DATA "Sprite.table"
#define RESDATASTR_TABLE_PLAYERSHOOT	RESDATASTR_FOLDER_DATA "PlayerShoot.table"
#define RESDATASTR_TABLE_PLAYERSUB		RESDATASTR_FOLDER_DATA "PlayerSub.table"
#define RESDATASTR_TABLE_AREA			RESDATASTR_FOLDER_DATA "StageArea.table"
#define RESDATASTR_TABLE_BLANKMAPTILE	RESDATASTR_FOLDER_DATA "BlankMapTile.table"
#define RESDATASTR_TABLE_PACKAGE		RESDATASTR_FOLDER_DATA "Package.table"
#define RESDATASTR_TABLE_TEXTURE		RESDATASTR_FOLDER_DATA "Texture.table"
#define RESDATASTR_TABLE_EFFECTSYS		RESDATASTR_FOLDER_DATA "EffectSys.table"
#define RESDATASTR_TABLE_SE				RESDATASTR_FOLDER_DATA "SE.table"

#define RESDATASTR_REPLAYEXTENSION		"rpy"

//CONFIG
#define RESCONFIGS_RESOURCE				"Resource"
#define RESCONFIGN_PASSWORD				"Password"
#define RESCONFIGDEFAULT_PASSWORD			"h5nc"
#define RESCONFIGN_BINMODE				"BinMode"
#define RESCONFIGDEFAULT_BINMODE			1


#ifdef __WIN32
#define RESCONFIGS_KEYSETTING	"KeySetting"
#else
#define RESCONFIGS_KEYSETTING	"KeySetting_PSP"
#endif // __WIN32

#define RESCONFIGN_JOYFIRE		"JoyFire"
#define RESCONFIGDEFAULT_JOYFIRE	3
#define RESCONFIGN_JOYQUICK		"JoyQuick"
#define RESCONFIGDEFAULT_JOYQUICK	2
#define RESCONFIGN_JOYSLOW		"JoySlow"
#define RESCONFIGDEFAULT_JOYSLOW	7
#define RESCONFIGN_JOYDRAIN		"JoyDrain"
#define RESCONFIGDEFAULT_JOYDRAIN	6
#define RESCONFIGN_JOYPAUSE		"JoyPause"
#define RESCONFIGDEFAULT_JOYPAUSE	1
#define RESCONFIGN_DEBUG_JOYSPEEDUP	"Debug_JoySpeedUp"
#define RESCONFIGDEFAULT_DEBUG_JOYSPEEDUP	5
#define RESCONFIGN_JOYCOMBINESLOWDRAIN	"JoyCombineSlowDrain"

#define RESCONFIGDEFAULT_JOYCOMBINESLOWDRAIN	1

#define RESCONFIGN_KEYUP		"KeyUp"
#define RESCONFIGN_KEYDOWN		"KeyDown"
#define RESCONFIGN_KEYLEFT		"KeyLeft"
#define RESCONFIGN_KEYRIGHT		"KeyRight"
#define RESCONFIGN_KEYFIRE		"KeyFire"
#define RESCONFIGN_KEYQUICK		"KeyQuick"
#define RESCONFIGN_KEYSLOW		"KeySlow"
#define RESCONFIGN_KEYDRAIN		"KeyDrain"
#define RESCONFIGN_KEYPAUSE		"KeyPause"
#define RESCONFIGN_KEYSKIP		"KeySkip"
#define RESCONFIGN_KEYENTER		"KeyEnter"
#define RESCONFIGN_KEYESCAPE	"KeyEscape"
#define RESCONFIGN_KEYCAPTURE	"KeyCapture"
#define RESCONFIGN_KEYCOMBINESLOWDRAIN	"KeyCombineSlowDrain"

#if defined __WIN32 || defined __IPHONE

#define RESCONFIGDEFAULT_KEYUP_1		DIK_UP
#define RESCONFIGDEFAULT_KEYDOWN_1		DIK_DOWN
#define RESCONFIGDEFAULT_KEYLEFT_1		DIK_LEFT
#define RESCONFIGDEFAULT_KEYRIGHT_1		DIK_RIGHT
#define RESCONFIGDEFAULT_KEYFIRE_1		DIK_Z
#define RESCONFIGDEFAULT_KEYQUICK_1		DIK_X
#define RESCONFIGDEFAULT_KEYSLOW_1		DIK_LSHIFT
#define RESCONFIGDEFAULT_KEYDRAIN_1		DIK_C

#define RESCONFIGDEFAULT_KEYPAUSE	DIK_SPACE
#define RESCONFIGDEFAULT_KEYSKIP	DIK_LCONTROL
#define RESCONFIGDEFAULT_KEYENTER	DIK_RETURN
#define RESCONFIGDEFAULT_KEYESCAPE	DIK_F4
#define RESCONFIGDEFAULT_KEYCAPTURE	DIK_HOME

#elif defined __PSP

#define         _PSP_CTRL_SELECT    0
#define         _PSP_CTRL_START     3
#define         _PSP_CTRL_UP        4
#define         _PSP_CTRL_RIGHT     5
#define         _PSP_CTRL_DOWN      6
#define         _PSP_CTRL_LEFT      7
#define         _PSP_CTRL_LTRIGGER  8
#define         _PSP_CTRL_RTRIGGER  9
#define         _PSP_CTRL_TRIANGLE  12
#define         _PSP_CTRL_CIRCLE    13
#define         _PSP_CTRL_CROSS     14
#define         _PSP_CTRL_SQUARE    15
#define         _PSP_CTRL_HOME      16
#define         _PSP_CTRL_HOLD      17
#define         _PSP_CTRL_NOTE      23
#define			_PSP_CTRL_SCREEN	22
#define			_PSP_CTRL_VOLUP		20
#define			_PSP_CTRL_VOLDOWN	21
#define			_PSP_CTRL_WLAN_UP	18
#define			_PSP_CTRL_REMOTE	19
#define			_PSP_CTRL_DISC		24
#define			_PSP_CTRL_MS		25

#define			_PSP_CTRL_NULL		31
#define			_PSP_CTRL_NULL_QUIT	28

#define RESCONFIGDEFAULT_KEYUP_1		_PSP_CTRL_UP
#define RESCONFIGDEFAULT_KEYDOWN_1		_PSP_CTRL_DOWN
#define RESCONFIGDEFAULT_KEYLEFT_1		_PSP_CTRL_LEFT
#define RESCONFIGDEFAULT_KEYRIGHT_1		_PSP_CTRL_RIGHT
#define RESCONFIGDEFAULT_KEYFIRE_1		_PSP_CTRL_SQUARE
#define RESCONFIGDEFAULT_KEYQUICK_1		_PSP_CTRL_CROSS
#define RESCONFIGDEFAULT_KEYSLOW_1		_PSP_CTRL_RTRIGGER
#define RESCONFIGDEFAULT_KEYDRAIN_1		_PSP_CTRL_LTRIGGER
#define RESCONFIGDEFAULT_KEYUP_2		_PSP_CTRL_NULL
#define RESCONFIGDEFAULT_KEYDOWN_2		_PSP_CTRL_NULL
#define RESCONFIGDEFAULT_KEYLEFT_2		_PSP_CTRL_NULL
#define RESCONFIGDEFAULT_KEYRIGHT_2		_PSP_CTRL_NULL
#define RESCONFIGDEFAULT_KEYFIRE_2		_PSP_CTRL_NULL
#define RESCONFIGDEFAULT_KEYQUICK_2		_PSP_CTRL_NULL
#define RESCONFIGDEFAULT_KEYSLOW_2		_PSP_CTRL_NULL
#define RESCONFIGDEFAULT_KEYDRAIN_2		_PSP_CTRL_NULL

#define RESCONFIGDEFAULT_KEYPAUSE	_PSP_CTRL_CIRCLE
#define RESCONFIGDEFAULT_KEYSKIP	_PSP_CTRL_TRIANGLE
#define RESCONFIGDEFAULT_KEYENTER	_PSP_CTRL_SQUARE
#define RESCONFIGDEFAULT_KEYESCAPE	_PSP_CTRL_NULL_QUIT
#define RESCONFIGDEFAULT_KEYCAPTURE	_PSP_CTRL_NULL

#endif	// __WIN32


#define RESCONFIGDEFAULT_KEYCOMBINESLOWDRAIN	1

#define RESCONFIGS_VOLUME		"Volume"
#define RESCONFIGN_VOLMUSIC		"Music"
#define RESCONFIGDEFAULT_VOLMUSIC	100
#define RESCONFIGN_VOLSE		"SE"
#define RESCONFIGDEFAULT_VOLSE		100

#define RESCONFIGS_CUSTOM		"Custom"
#define RESCONFIGN_SCREENMODE	"ScreenMode"
#define RESCONFIGDEFAULT_SCREENMODE	0

#define RESCONFIGN_SCREENSCALE	"ScreenScale"
#if defined __IPHONE
#define RESCONFIGDEFAULT_SCREENSCALE	0.9f
#else
#define RESCONFIGDEFAULT_SCREENSCALE	1.0f
#endif
#define RESCONFIGN_TOUCHMOVESCALE	"TouchMoveScale"
#define RESCONFIGDEFAULT_TOUCHMOVESCALE	1.0f
#define RESCONFIGN_INFODISPLAYSCALE	"InfoDisplayScale"
#define RESCONFIGDEFAULT_INFODISPLAYSCALE	1.0f

#define RESCONFIGN_USERNAME		"UserName"
#define RESCONFIGDEFAULT_USERNAME	"NoName"
#define RESCONFIGN_RENDERSKIP	"RenderSkip"
#define RESCONFIGDEFAULT_RENDERSKIP	0
#define RESCONFIGN_LASTMATCHCHARA	"LastMatchChara"
#define RESCONFIGDEFAULT_LASTMATCHCHARA	0

#define RESCONFIGN_BULLETCOUNTMAX	"BulletCountMax"
#define RESCONFIGDEFAULT_BULLETCOUNTMAX	INT_MAX

#define RESCONFIGS_CONNECT		"Connect"
#define RESCONFIGN_LASTIPX		"LastIPx"
#define RESCONFIGN_LASTIPPORT	"LastIPPort"

#define RESCONFIGS_CUSTOMWINDOW		"CustomWindow"
#define RESCONFIGN_DEFAULTWINDOW	"DefaultWindow"
#define RESCONFIGDEFAULT_DEFAULTWINDOW	1
#define RESCONFIGN_WINDOWLEFT		"WindowLeft"
#define RESCONFIGDEFAULT_WINDOWLEFT		0
#define RESCONFIGN_WINDOWTOP		"WindowTop"
#define RESCONFIGDEFAULT_WINDOWTOP		0
#define RESCONFIGN_WINDOWWIDTH		"WindowWidth"
#define RESCONFIGDEFAULT_WINDOWWIDTH	320
#define RESCONFIGN_WINDOWHEIGHT		"WindowHeight"
#define RESCONFIGDEFAULT_WINDOWHEIGHT	480
#define RESCONFIGN_WINDOWTOPMOST	"WindowTopMost"
#define RESCONFIGDEFAULT_WINDOWTOPMOST	0

#define RESCONFIGS_SYSTEM			"System"
#define RESCONFIGN_USE3DMODE		"Use3DMode"
#define RESCONFIGDEFAULT_USE3DMODE		0

#define RESLOADING_PCK	"Loading.pck"
#define RESLOADING_TEX	"Loading/loading.tex"

#define SNAPSHOT_PRIFIX		"SnapShot"
#define SNAPSHOT_EXTENSION	"bmp"

#endif