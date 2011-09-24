#ifndef _BOSSINFO_H
#define _BOSSINFO_H

#include "MainDependency.h"
#include "InfoQuad.h"
#include "Const.h"
#include "Effectsys.h"
#include "Fontsys.h"

#define BOSSINFO_ENABLE		1
#define BOSSINFO_UP			2
#define BOSSINFO_COLLAPSE	4
#define BOSSINFO_TIMEOVER	8

#define BISF_NONE			0x00
#define BISF_SHOT			0x01
#define BISF_BOMB			0x02
#define BISF_WAIT			0x04
#define BISF_NOBOMBDAMAGE	0x10
#define BISF_NOTSPELL		0x80

class BossInfo
{
public:
	BossInfo(){};
	~BossInfo(){};

	void bossUp();
	void bossCollapse();

	bool action();
	void quit();

	bool Fill(int sno);

	bool isSpell();

	static void Clear();
	static bool Init();
	static void Release();

public:
	char enemyname[M_STRMAX];
	char enemyename[M_STRMAX];
	char spellname[M_STRMAX];
	InfoQuad blood;
	int get;
	int meet;
	int itemstack;
	bool exist;
	WORD timer;
	BYTE limit;
	BYTE remain;

	static bool failed;
	static bool allover;
	static int sno;
	static int turntoscene;

	static BYTE flag;
	static BYTE spellflag;
	static Fontsys fsspellname;

	static BossInfo bossinfo;
};


#endif