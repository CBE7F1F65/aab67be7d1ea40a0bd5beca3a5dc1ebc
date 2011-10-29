#ifndef _BRESOURCE_H
#define _BRESOURCE_H

#include "MainDependency.h"
#include "DataStruct.h"

#define RSIZE_RESOURCE		(sizeof(resourceData))
#define RSIZE_STRINGDESC	(sizeof(char) * M_STRMAX * DATASTRUCT_STRINGDESCMAX)
#define RSIZE_CUSTOMCONST	(sizeof(customconstData) * SCR_CUSTOMCONSTMAX)
#define RSIZE_TEXTURE		(sizeof(textureData) * DATASTRUCT_TEXMAX)
#define RSIZE_MUSIC			(sizeof(musicData) * DATASTRUCT_MUSICMAX)
#define RSIZE_BULLET		(sizeof(bulletData) * DATASTRUCT_BULLETTYPEMAX)
#define RSIZE_ENEMY			(sizeof(enemyData) * DATASTRUCT_ENEMYTYPEMAX)
#define RSIZE_PLAYER		(sizeof(playerData) * DATASTRUCT_PLAYERTYPEMAX)
//#define RSIZE_SPRITE		(sizeof(spriteData) * SPRITEITEMMAX)
#define RSIZE_SPRITE		(sizeof(spriteData) * spritenumber)
#define RSIZE_SPRITENUMBER	(sizeof(int))
#define RSIZE_PLAYERSHOOT	(sizeof(playershootData) * DATASTRUCT_PLAYERSHOOTTYPEMAX)
#define RSIZE_PLAYERLASER	(sizeof(playerlaserData) * DATASTRUCT_PLAYERLASERTYPEMAX)
#define RSIZE_PLAYERSUB		(sizeof(playersubData) * DATASTRUCT_PLAYERGHOSTTYPEMAX)
#define RSIZE_STAGEAREA		(sizeof(stageareaData) * DATASTRUCT_STAGEAREAMAX)

class BResource
{
public:

	BResource();
	~BResource();

	bool Fill();
	bool Pack(void * pStrdesc, void * pCustomConstName);
	bool Gain(void * pStrdesc = NULL, void * pCustomConstName = NULL);
	bool LoadPackage(int packindex);
	bool LoadAllPackage();

	void InitTexinfo();
	bool LoadTexture(int texindex=-1);
	bool FreeTexture(int texindex=-1);

	void ReleaseCustomConst();
	void MallocCustomConst();
	void ReleaseSpriteData();
	void InitSpriteData();

public:

	resourceData resdata;
	seData sedata[DATASTRUCT_SEMAX];
	effectData effdata[DATASTRUCT_EFFECTMAX];
	itemData itemdata[DATASTRUCT_ITEMMAX];
	enemyData enemydata[DATASTRUCT_ENEMYMAX];
	musicData musdata[DATASTRUCT_MUSICMAX];
	bulletData bulletdata[DATASTRUCT_BULLETTYPEMAX];
	playerData playerdata[DATASTRUCT_PLAYERTYPEMAX];
//	spriteData spritedata[SPRITEITEMMAX];
	spriteData * spritedata;
	int spritenumber;
	playershootData playershootdata[DATASTRUCT_PLAYERSHOOTTYPEMAX];
	playerlaserData playerlaserdata[DATASTRUCT_PLAYERLASERTYPEMAX];
	playersubData playersubdata[DATASTRUCT_PLAYERGHOSTTYPEMAX];
	customconstData * customconstdata;
	textureData texturedata[DATASTRUCT_TEXMAX];
	stageareaData stageareadata[DATASTRUCT_STAGEAREAMAX];

	//texture
	HTEXTURE	tex[DATASTRUCT_TEXMAX];
	hgeTextureInfo texinfo[DATASTRUCT_TEXMAX];

	static BResource bres;
};

extern HGE * hge;

#endif