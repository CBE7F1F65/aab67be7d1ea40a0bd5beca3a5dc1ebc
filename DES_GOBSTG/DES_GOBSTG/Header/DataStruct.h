#ifndef _DATASTRUCT_H
#define _DATASTRUCT_H

#include "Const.h"

#define DATASTRUCT_CUSTOMCONSTMAX	0x100
#define DATASTRUCT_TEXMAX			0x300
#define DATASTRUCT_MUSICMAX			0x10
#define DATASTRUCT_EFFECTMAX		0x100
#define DATASTRUCT_SPRITEMAX		0x400
#define DATASTRUCT_ITEMMAX			0x20
#define DATASTRUCT_ENEMYMAX			0x100
#define DATASTRUCT_BULLETTYPEMAX	0x40
#define DATASTRUCT_ENEMYTYPEMAX		0x50
#define DATASTRUCT_PLAYERTYPEMAX	4
#define DATASTRUCT_PLAYERGHOSTMAX		4
#define DATASTRUCT_PLAYERSHOOTTYPEMAX	(DATASTRUCT_PLAYERTYPEMAX * (DATASTRUCT_PLAYERGHOSTMAX + 2))
#define DATASTRUCT_PLAYERGHOSTTYPEMAX	(DATASTRUCT_PLAYERGHOSTMAX * DATASTRUCT_PLAYERTYPEMAX * 2)
#define DATASTRUCT_PLAYERLASERTYPEMAX	(DATASTRUCT_PLAYERTYPEMAX)
#define DATASTRUCT_PLAYERLASERTYPE		4
#define DATASTRUCT_SCENEMAX			DATASTRUCT_PLAYERTYPEMAX
#define DATASTRUCT_PLAYERBULLETTYPE		4
#define DATASTRUCT_PACKAGEMAX			0x20
#define DATASTRUCT_SEMAX				0x80
#define DATASTRUCT_FONTSYSMAX			0x40
#define DATASTRUCT_STRINGDESCMAX		0x400

struct customconstData{
	char name[M_STRKEYMAX];
	int value;
};

struct textureData
{
	char texfilename[M_STRMAX];
	char texname[M_STRKEYMAX];
	int width;
	int height;
};

struct musicData{
	char musicfilename[M_PATHMAX];
	char musicname[M_STRKEYMAX];
#ifdef __IPHONE
	char _unused[4];
#endif
	LONGLONG startpos;
	LONGLONG introlength;
	LONGLONG alllength;
};

struct spriteData 
{
	char spritename[M_STRKEYMAX];
	float tex_x;
	float tex_y;
	float tex_w;
	float tex_h;
	int tex;
};

struct seData
{
	char sefilename[M_STRMAX];
	char sename[M_STRKEYMAX];
};

struct effectData
{
	char efffilename[M_STRMAX];
	char effname[M_STRKEYMAX];
};

struct itemData
{
	int siid;
};

struct spellData{
	char spellname[M_STRMAX];
	LONGLONG bonus;
	int spellnumber;
	int turntoscene;
	BYTE timelimit;
	BYTE remain;
	BYTE userID;
	BYTE spellflag;
	BYTE battleID;
};

struct uiStringData 
{
	char filename[M_STRMAX];
	char username[M_STRMAX];
	char score[M_STRMAX];
	char point[M_STRMAX];
	char faith[M_STRMAX];
	char alltime[M_STRMAX];
	char date[M_STRMAX];
	char lost[M_STRMAX];
	char borderrate[M_STRMAX];
	char fastrate[M_STRMAX];
	char modeflag[M_STRMAX];
	char mode_none[M_STRMAX];
	char mode_practice[M_STRMAX];
	char mode_spell[M_STRMAX];
	char usingchara[M_STRMAX];
//	char maxplayer[M_STRMAX];
	char misstime[M_STRMAX];
	char bordertime[M_STRMAX];
	char continuetime[M_STRMAX];
	char gettime[M_STRMAX];
	char pausetime[M_STRMAX];
	char difflv[M_STRMAX];
	char laststage[M_STRMAX];
	char graze[M_STRMAX];
	char confirm[M_STRMAX];
};

struct resourceData
{
	//resource file
	char sefilename[DATASTRUCT_SEMAX][M_PATHMAX];
	char effectsysfilename[DATASTRUCT_EFFECTMAX][M_PATHMAX];
	char packagefilename[DATASTRUCT_PACKAGEMAX][M_PATHMAX];

	//font
	char fontfilename[M_STRMAX];
	char widefontname[M_STRMAX];

	//datafile

	char binfilename[M_PATHMAX];
	char binname[M_PATHMAX];
//	char spellaccessfilename[M_PATHMAX];
	char rabinname[M_STRMAX];
	char scriptfilename[M_PATHMAX];
	char scrbinname[M_PATHMAX];

	char customconstfilename[M_PATHMAX];
//	char spelldefinefilename[M_PATHMAX];
	char musicdefinefilename[M_PATHMAX];
	char bulletdefinefilename[M_PATHMAX];
	char enemydefinefilename[M_PATHMAX];
	char playerdefinefilename[M_PATHMAX];
	char spritedefinefilename[M_PATHMAX];
	char playershootdefinefilename[M_PATHMAX];
	char playerghostdefinefilename[M_PATHMAX];
	char datadefinefilename[M_PATHMAX];
	char packagedefinefilename[M_PATHMAX];
	char texturedefinefilename[M_PATHMAX];
	char effectdefinefilename[M_PATHMAX];
	char sedefinefilename[M_PATHMAX];

	//folder
	char scriptfoldername[M_SCRIPTFOLDERMAX][M_PATHMAX];
	char snapshotfoldername[M_PATHMAX];
	char replayfoldername[M_PATHMAX];
	char datafoldername[M_PATHMAX];
	char effectsysfoldername[M_PATHMAX];

	//extension
	char scriptextensionname7[8];
	char replayextensionname7[8];

	//replay header
	char replaysignature11[12];
	char replaytempsign3[4];
	char replaycompletesign3[4];
	char replaytag3[4];

	bool binmode;

	uiStringData uistr;
};

struct bulletData 
{
	int nTurnAngle;
	int siid;
	float collisionMain;
	float collisionSub;
	BYTE nRoll;
	BYTE nColor;
	BYTE whitecolor;
	BYTE seID;
	BYTE effID;
	BYTE blendtype;
	BYTE collisiontype;
	BYTE fadecolor;
	BYTE autosendsetID;
	BYTE renderdepth;
	BYTE renderflag;
};

struct enemyData 
{
	char name[M_STRMAX];
	char ename[M_STRMAX];
	int siid;
	int effid;
	int shotEffid;
	int collapseEffid;
	float collision_w;
	float collision_h;
	float blastr;
	float blastpower;
	float blastdamagerate;
	float expoint;
	int ghostpoint;
	int bulletpoint;
	int spellpoint;
	WORD flag;
	BYTE faceIndex;
	BYTE standFrame;
	BYTE rightPreFrame;
	BYTE rightFrame;
	BYTE leftPreFrame;
	BYTE leftFrame;
	BYTE attackPreFrame;
	BYTE attackFrame;
	BYTE storePreFrame;
	BYTE storeFrame;
	BYTE nmaxset;
	BYTE nmax;
	BYTE blastmaxtime;
};

struct playerData 
{
	char name[M_STRMAX];
	char ename[M_STRMAX];
	char spellname[3][M_STRMAX];
	char scenename[M_STRMAX];
	float collision_r;
	float fastspeed;
	float slowspeed;
	float chargespeed;
	float addchargerate;
	float exsendparab;
	float exsendparaa;
	float exsendmax;
	int siid;
	int faceSIID;
	int spellcutinSIID;
	int drainzoneSIID;
	int aidraintime;
	WORD infinmaxset;
	BYTE musicID;
	BYTE shotdelay;
	BYTE rechargedelay;
	BYTE shootchargetime;
	BYTE standFrame;
	BYTE leftPreFrame;
	BYTE leftFrame;
	BYTE rightPreFrame;
	BYTE rightFrame;
};

struct playershootData 
{
	int angle;
	int addangle;
	int deletetime;
	int siid;
	int hitonfactor;
	bool bchargeshoot;
	float xbias;
	float ybias;
	float collisionr;
	float scale;
	float speed;
	float accelspeed;
	float power;
	WORD flag;
	BYTE userID;
	BYTE seID;
	BYTE timeMod;
	BYTE arrange;
};

struct playerghostData 
{
	int siid;
	int shootangle;
	int startangle;
	float mover;
	float xadj;
	float yadj;
	float speed;
	WORD flag;
	BYTE rolltime;
	BYTE blend;
};

#endif