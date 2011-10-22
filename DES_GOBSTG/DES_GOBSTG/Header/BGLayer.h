#ifndef _BGLAYER_H
#define _BGLAYER_H

#include "MainDependency.h"
#include "Const.h"
#include "BObject.h"

#define BG_NONE			0x00

#define BG_FLAGMASK		0xf0

#define BG_FLASHFLAG	0x10
#define BG_WHITEFLASH	0x10
#define BG_REDFLASH		0x11
#define BG_YELLOWFLASH	0x12
#define BGMT_FLASH		0x20

#define BG_OUTFLAG		0x20
#define BG_WHITEOUT		0x20
#define BG_REDOUT		0x21
#define BGMT_OUT		0x80

#define BG_FADEFLAG		0x40
#define BG_FADEIN		0x40
#define BG_FADEINHALF	0x41
#define BG_FADEOUT		0x42
#define BGMT_FADE		0x40

#define BG_LIGHTFLAG		0x80
#define BG_LIGHTUP			0x80
#define BG_LIGHTRED			0x81
#define BG_LIGHTUPNORMAL	0x82
#define BGMT_LIGHT			0x40

#define FG_PAUSEFLAG	0xf0
#define FG_PAUSEIN		0xf0
#define FG_PAUSEOUT		0xf1
#define FGMT_PAUSE		0x18



#define BGTILE_WIDTH	32
#define BGTILE_HEIGHT	BGTILE_WIDTH

#define BGTILE_XCOUNTMAX	((BYTE)((M_MAINVIEW_WIDTH/BGTILE_WIDTH)+2))
#define BGTILE_YCOUNTMAX	((BYTE)((M_MAINVIEW_HEIGHT/BGTILE_HEIGHT)+2))
#define BGTILEMAX			(BGTILE_XCOUNTMAX * BGTILE_YCOUNTMAX)

struct BGLayerSet
{
	DWORD timer;
	WORD sID;
};

class BGTile : public BObject
{
public:
	BGTile();
	~BGTile();

	void Release();
	void Render();
	void action();

public:
	hgeSprite * sprite;
};

#define BGLAYERSET_NONE	0xffff

class BGLayer
{
public:
	BGLayer();
	~BGLayer();

	void Init();
	void Release();
	static void Action(bool active);
	static void RenderAll();
	void BGLayerSetup();

	void Render();

public:

	DWORD timer;
	BYTE areaid;
	BGTile bgtiles[BGTILEMAX];

	float xspeed;
	float yspeed;

	static BGLayer bglayer;
};

#endif