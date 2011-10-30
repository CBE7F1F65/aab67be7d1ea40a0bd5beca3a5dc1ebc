#ifndef _BGLAYER_H
#define _BGLAYER_H

#include "MainDependency.h"
#include "Const.h"
#include "BObject.h"
#include "DataStruct.h"

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

#define BGTILE_SUBTILE_XCOUNT	4
#define BGTILE_SUBTILE_YCOUNT	BGTILE_SUBTILE_XCOUNT
#define BGTILE_SUBTILE_TOTALCOUNT	(BGTILE_SUBTILE_XCOUNT*BGTILE_SUBTILE_YCOUNT)

#define BGTILE_SUBTILE_XTILECOUNT	8
#define BGTILE_SUBTILE_YTILECOUNT	BGTILE_SUBTILE_XTILECOUNT
#define BGTILE_SUBTILE_TOTALTILECOUNT	(BGTILE_SUBTILE_XTILECOUNT*BGTILE_SUBTILE_YTILECOUNT)

#define BGTILE_TEXWIDTH		(BGTILE_WIDTH*BGTILE_SUBTILE_XCOUNT*BGTILE_SUBTILE_XTILECOUNT)
#define BGTILE_TEXHEIGHT	(BGTILE_HEIGHT*BGTILE_SUBTILE_YCOUNT*BGTILE_SUBTILE_YTILECOUNT)

#define BGTILE_TOTALTILECOUNT	(BGTILE_SUBTILE_TOTALCOUNT*BGTILE_SUBTILE_TOTALTILECOUNT)

/************************************************************************/
/* TileMapDefine                                                        */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* 56 57 58 59 60 61 62 63                                              */
/* 48 49 50 51 52 53 54 55                                              */
/* 40 41 42 43 44 45 46 47                                              */
/* 32 33 34 35 36 37 38 39                                              */
/* 24 25 26 27 28 29 30 31                                              */
/* 16 17 18 19 20 21 22 23                                              */
/* 08 09 10 11 12 13 14 15                                              */
/* 00 01 02 03 04 05 06 07                                              */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* 96                                                                   */
/* 88                                                                   */
/* 80                                                                   */
/* 72                                                                   */
/* 64 65 66 67 68 69 70 71                                              */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/************************************************************************/

#define BGTILE_XCOUNTMAX	((BYTE)((M_GAMESQUARE_WIDTH/BGTILE_WIDTH)+2))
#define BGTILE_YCOUNTMAX	((BYTE)((M_GAMESQUARE_HEIGHT/BGTILE_HEIGHT)+2))
#define BGTILEMAX			(BGTILE_XCOUNTMAX * BGTILE_YCOUNTMAX)


class BGTile : public BObject
{
public:
	BGTile();
	~BGTile();

	void init();
	void Release();
	void Render();
	void action();
	void SetSpriteByXY(int largetilex, int largetiley);

public:
	hgeSprite * sprite;
	int largetilex;
	int largetiley;
};

struct BGTileMapping 
{
	BYTE texoffset;
	int textilex;
	int textiley;
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
	void action();
	static void RenderAll();
	void BGLayerSetup(float begincenx);

	void SetMapSpeedInfo(float xspeed, float yspeed, float mapxoffset);

//	bool CheckBlank(int *tilenum, int *texoffset);

	void UpdateTileSprite();

	void Render();

public:

	DWORD timer;
	BYTE areaid;
	BGTile bgtiles[BGTILEMAX];

	float xspeed;
	float yspeed;

	bool bSetup;

	stageareaData * adatabegin;

	int texbegin;
	BGTileMapping * tilemapping;
	int largemapxtile;
	int largemapytile;

	float mapcenx;
	float mapxoffset;
	float mapceny;

	float tilesxoffset;
	float tilesyoffset;

	static BGLayer bglayer;
};

#endif