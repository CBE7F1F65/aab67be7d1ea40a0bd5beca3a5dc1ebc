#ifndef _DATA_H
#define _DATA_H

#include "MainDependency.h"
#include "Const.h"

#define DATA_MEMORYHEADER		0x20
//#define DATA_SPELLACCESSFILE	0x21
//#define DATA_SCRIPTFILE			0x22

#define DATA_TABLEHEADER		0x40
#define DATA_CUSTOMCONSTFILE	0x41
//#define DATA_SPELLDEFINEFILE	0x42
#define DATA_MUSICDEFINEFILE	0x44

#define DATA_BULLETDEFINEFILE	0x48
#define DATA_ENEMYDEFINEFILE	0x49
#define DATA_PLAYERDEFINEFILE	0x4A
#define DATA_SPRITEDEFINEFILE	0x4B
#define DATA_PLAYERSHOOTDEFINE	0x4C
#define DATA_PLAYERGHOSTDEFINE	0x4D

#define DATA_DATATABLEDEFINE	0x51
#define DATA_PACKAGETABLEDEFINE	0x52
#define DATA_TEXTURETABLEDEFINE	0x53
#define DATA_EFFECTTABLEDEFINE	0x54
#define DATA_SETABLEDEFINE		0x55

#define DATA_RESOURCEFILE		0x81
#define DATA_BINFILE			0x82

#define DATA_HEADEROFFSET		0x40

#define DATA_NTOP10FILESAVE		10

#define DATABIN_TYPE_INT		0x01
#define DATABIN_TYPE_FLOAT		0x02
#define DATABIN_TYPE_LONGLONG	0x04
#define DATABIN_TYPE_STRING		0x08

//#define DATARA_INDI_SIZE		0x02
//#define DATARA_INDIMAX			(S1-S0)

/*
Section Align
Type[2]_Diffi[1]_Chara[1]_Num[4]
*/

#define DATASBINMASK_TYPE	0x00ffffff
#define DATASBINMASK_DIFF	0xff0fffff
#define DATASBINMASK_CHARA	0xfff0ffff
#define DATASBINMASK_NUM	0xffff0000

#define DATANBINMASK_TYPE	0x0000ffff
#define DATANBINMASK_NUM	0xffff0000

enum{
	//FFFF GP MP GG MG for ABCD
	DATAMAPENUM_DATASTART,

	DATATDIFF_E,
	DATATDIFF_N,
	DATATDIFF_H,
	DATATDIFF_D,
	DATATDIFF_X1,
	DATATDIFF_X2,
	DATATDIFF_X3,
	DATATDIFF_X4,
	DATATDIFF_X5,
	DATATDIFF_X6,

	DATAS_HEADER,
	DATAN_GAMEVERSION,
	DATAN_SIGNATURE,
	DATAN_FILETYPE,

	DATAS_TOP,
	//Top_E_1

	DATAN_SCORE,
	DATAN_LASTSTAGE,
	DATAN_USERNAME,
	DATAN_TIME_YEAR,
	DATAN_TIME_MONTH,
	DATAN_TIME_DAY,
	DATAN_TIME_HOUR,
	DATAN_TIME_MINUTE,
	DATAN_LOST,
	DATAN_BORDERRATE,
	DATAN_FASTRATE,
	DATAN_ALLTIME,
	DATAN_SPELLGET,
	DATAN_MAXPLAYER,
	DATAN_POINT,
	DATAN_FAITH,
	DATAN_MISS,
	DATAN_BOMB,
	DATAN_CONTINUE,
	DATAN_PAUSE,
	DATAN_GETSPELL,
	DATAN_CHARA,

	DATAS_SPELL,
	//Spell_100

	DATAN_GETGAME,
	DATAN_MEETGAME,
	DATAN_GETPRACTICE,
	DATAN_MEETPRACTICE,
	DATAN_TOPBONUS,

	DATAS_STAGEPRACTICE,
	//StagePractice_E_1

	DATAN_TRYTIME,
	DATAN_TOPSCORE,

	DATAS_TOTAL,
	//Total_E

	DATAN_PLAYTIME,
	DATAN_CLEARTIME,
	DATAN_PRACTICETIME,

	//Total

	DATAN_FIRSTRUNTIME,
	DATAN_TOTALPLAYTIME,

	//
	DATAS_FLAG,

	DATAMAPENUM_RESOURCESTART,
	////////////RESOURCE/////////////

	RESDATAN_FILENAME,
	RESDATAN_TYPE,

	RESDATAS_FONT,
	RESDATAN_FONT,

	RESDATAS_DATAFILE,

	RESDATAN_BINFILE,
//	RESDATAN_SPELLACCESSFILE,
//	RESDATAN_SCRIPTFILE,

	RESDATAN_CUSTOMCONSTFILE,
//	RESDATAN_SPELLDEFINEFILE,
	RESDATAN_MUSICDEFINEFILE,
	RESDATAN_SCENEDEFINEFILE,
	RESDATAN_BULLETDEFINEFILE,
	RESDATAN_ENEMYDEFINEFILE,
	RESDATAN_PLAYERDEFINEFILE,
	RESDATAN_SPRITEDEFINEFILE,
//	RESDATAN_PLAYERBULLETDEFINEFILE,
	RESDATAN_PLAYERSHOOTDEFINEFILE,
	RESDATAN_PLAYERGHOSTDEFINEFILE,
	RESDATAN_DATADEFINEFILE,
	RESDATAN_PACKAGEDEFINEFILE,
	RESDATAN_TEXTUREDEFINEFILE,
	RESDATAN_EFFECTDEFINEFILE,
	RESDATAN_SEDEFINEFILE,

	RESDATAS_PACKAGE,
	RESDATAS_TEXTURE,
	RESDATAS_SE,
	RESDATAS_EFFECTSYS,

	RESDATAS_FOLDER,
/*
	RESDATAN_SCRIPTFOLDER_1,
	RESDATAN_SCRIPTFOLDER_2,
	RESDATAN_SCRIPTFOLDER_3,
	RESDATAN_SCRIPTFOLDER_4,
	RESDATAN_SCRIPTFOLDER_5,
	RESDATAN_SCRIPTFOLDER_6,
	RESDATAN_SCRIPTFOLDER_7,
	RESDATAN_SCRIPTFOLDER_8,
*/	RESDATAN_SNAPSHOTFOLDER,
	RESDATAN_REPLAYFOLDER,
	RESDATAN_DATAFOLDER,
	RESDATAN_EFFECTSYSFOLDER,

	RESDATAS_EXTENSION,
	RESDATAN_SCRIPTEXT7,
	RESDATAN_REPLAYEXT7,

	RESDATAS_REPLAYHEADER,
	RESDATAN_RPYSIGNATURE11,
	RESDATAN_RPYTEMPSIGN3,
	RESDATAN_RPYCOMPLETESIGN3,
	RESDATAN_RPYTAG3,

	RESDATAS_UISTRING,
	RESDATAN_UISTR_FILENAME,
	RESDATAN_UISTR_USERNAME,
	RESDATAN_UISTR_SCORE,
	RESDATAN_UISTR_POINT,
	RESDATAN_UISTR_FAITH,
	RESDATAN_UISTR_ALLTIME,
	RESDATAN_UISTR_DATE,
	RESDATAN_UISTR_LOST,
	RESDATAN_UISTR_BORDERRATE,
	RESDATAN_UISTR_FASTRATE,
	RESDATAN_UISTR_MODEFLAG,
	RESDATAN_UISTR_MODE_NONE,
	RESDATAN_UISTR_MODE_PRACTICE,
	RESDATAN_UISTR_MODE_SPELL,
	RESDATAN_UISTR_USINGCHARA,
//	RESDATAN_UISTR_MAXPLAYER,
	RESDATAN_UISTR_MISSTIME,
	RESDATAN_UISTR_BORDERTIME,
	RESDATAN_UISTR_CONTINUETIME,
	RESDATAN_UISTR_GETTIME,
	RESDATAN_UISTR_PAUSETIME,
	RESDATAN_UISTR_DIFFLV,
	RESDATAN_UISTR_LASTSTAGE,
	RESDATAN_UISTR_GRAZE,
	RESDATAN_UISTR_CONFIRM,

	DATAMAPENUM_END
};

struct dataMapTable{
	char * textname;
	DWORD binname;
};

struct dataName{
	LONGLONG value;
	DWORD name;
};

struct dataSection{
	vector<dataName> data;
	DWORD section;
};

struct dataBin{
	LONGLONG value;
	DWORD section;
	DWORD name;
//	BYTE type;
};

extern dataMapTable dataMap[];

class Data
{
public:
	Data();
	~Data();

	bool Init(BYTE type);
	void GetIni();
	bool SetFile(const char * filename, BYTE type);

	bool SaveBin();

	bool iWrite(BYTE type, DWORD section, DWORD name, int value);
	int iRead(BYTE type, DWORD section, DWORD name, int def_val);
	bool lWrite(BYTE type, DWORD section, DWORD name, LONGLONG value);
	LONGLONG lRead(BYTE type, DWORD section, DWORD name, LONGLONG def_val);
	bool fWrite(BYTE type, DWORD section, DWORD name, float value);
	float fRead(BYTE type, DWORD section, DWORD name, float def_val);
	bool sWrite(BYTE type, DWORD section, DWORD name, const char * value);
	char * sRead(BYTE type, DWORD section, DWORD name, const char * def_val);

	DWORD sLinkType(DWORD type);
	DWORD sLinkDiff(DWORD sec, BYTE diff);
	DWORD sLinkNum(DWORD sec, DWORD num);

	DWORD nLinkType(DWORD type);
	DWORD nLinkNum(DWORD name, DWORD num);

	char * translateSection(DWORD sec);
	char * translateName(DWORD name);

	bool MemToList(BYTE * memcontent, DWORD size);
	BYTE * ListToMem(DWORD * size);

	LONGLONG * AttachValue(DWORD section, DWORD name, LONGLONG def_val = 0);

	void getFile(BYTE type);
	FILE * checkTableFile(BYTE type);

	BYTE * CreateMemHeader(BYTE type);
	bool CheckMemHeader(const BYTE * memdata, DWORD size, BYTE type);
	bool CheckHeader(BYTE type);

	char * getEnemyName(int type);
	char * getEnemyEName(int type);
	char * getPlayerName(int type);
	char * getPlayerEName(int type);

	void MoveDown(DWORD sec, BYTE i);
/*
	WORD raGetIndi(int sno);
	void raSetIndi(int sno, WORD indi);
*/
	int nMeet(int sno, bool bSpell = false);
	int nGet(int sno, bool bSpell = false);
	LONGLONG nHighScore(int sno, BYTE difflv, bool bSpell = false, bool bPractice = false);
	int nTryStageTime(int stage, BYTE difflv);

	LONGLONG getTotalRunTime();
	//
	
	bool SetEffectSystemResourceName(int effi, const char * filename);
	bool GetEffectSystemResourceName(int effi, char * filename);

	bool GetTableFile(BYTE type);
	bool GetAllTable();


public:
//	WORD indi[DATARA_INDIMAX];
	char buf[M_STRMAX];
	char transbufs[M_STRMAX];
	char transbufn[M_STRMAX];

	vector<dataSection> bin;

	bool binmode;

	int password;

	char * nowfilename;
	char * binfilename;
	char * binname;
//	char * spellaccessfilename;
//	char * rabinname;
//	char * scriptfilename;
//	char * scrbinname;
	char * resourcefilename;
	char * resbinname;

	char * customconstfilename;
//	char * spelldefinefilename;
	char * musicdefinefilename;
	char * bulletdefinefilename;
	char * enemydefinefilename;
	char * playerdefinefilename;
	char * spritedefinefilename;
	char * playershootdefinefilename;
	char * playerghostdefinefilename;

	char * datadefinefilename;
	char * packagedefinefilename;
	char * texturedefinefilename;
	char * effectdefinefilename;
	char * sedefinefilename;

	static Data data;
};

extern HGE * hge;

#endif