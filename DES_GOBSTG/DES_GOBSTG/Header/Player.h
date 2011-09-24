#ifndef _PLAYER_H
#define _PLAYER_H

#include "BObject.h"
#include "EffectSp.h"
#include "PlayerGhost.h"
#include "PlayerBullet.h"
#include "Effectsys.h"

// add
#define PLAYER_DEFAULTINITLIFE	10

#define PL_HITONFACTORDEFAULT	-1

#define PLAYER_FRAME_STAND		0
#define PLAYER_FRAME_LEFTPRE	1
#define PLAYER_FRAME_LEFT		2
#define PLAYER_FRAME_RIGHTPRE	3
#define PLAYER_FRAME_RIGHT		4

#define PLAYER_FRAME_STATEMAX	5

#define PL_MOVABLEDGE_X		8
#define PL_MOVABLEDGE_Y		16
#define PL_MOVABLE_LEFT_(X)		(M_GAMESQUARE_LEFT_(X)+PL_MOVABLEDGE_X)
#define PL_MOVABLE_RIGHT_(X)	(M_GAMESQUARE_RIGHT_(X)-PL_MOVABLEDGE_X)
#define PL_MOVABLE_TOP		(M_GAMESQUARE_TOP+PL_MOVABLEDGE_Y)
#define PL_MOVABLE_BOTTOM	(M_GAMESQUARE_BOTTOM-PL_MOVABLEDGE_Y)

#define PL_MERGEPOS_X_(X)	((X)?M_GAMESQUARE_RIGHT_(X):M_GAMESQUARE_LEFT_(X))
#define PL_MERGEPOS_Y		(M_GAMESQUARE_BOTTOM)

#define PL_SAVELASTMAX		0x20

#define	PLAYER_MERGE				0x0001
#define	PLAYER_SHOT					0x0002
#define PLAYER_COSTLIFE				0x0004
#define	PLAYER_COLLAPSE				0x0008
#define	PLAYER_SHOOT				0x0010
#define	PLAYER_DRAIN				0x0020
#define	PLAYER_BOMB					0x0040
#define	PLAYER_SLOWCHANGE			0x0080
#define	PLAYER_FASTCHANGE			0x0100
#define PLAYER_CHARGE				0x0200
#define	PLAYER_PLAYERCHANGE			0x0400
#define	PLAYER_GRAZE				0x1000

#define PLAYER_INFIMAX		-1
#define PLAYER_INFIUNSET	0
#define PLAYERINFI_MERGE		0x01
#define PLAYERINFI_SHOOTCHARGE	0x02
#define PLAYERINFI_OVER			0x04
#define PLAYERINFI_CHAT			0x08
#define PLAYERINFI_COSTLIFE			0x10
#define PLAYERINFI_COLLAPSE		0x20

#define PLAYER_CHARGEONE	100.0f
#define PLAYER_CHARGENMAX	4
#define PLAYER_CHARGEMAX	(PLAYER_CHARGEONE*PLAYER_CHARGENMAX)

#define PLAYER_COMBOGAGEMAX	105
#define PLAYER_COMBORESET	45
#define PLAYER_COMBOALERT	65

#define PLAYER_GRAZE_R	40

#define PLAYER_NCOMBOHITMAX		999
#define PLAYER_NSPELLPOINTMAX	999990

#define PL_SHOOTINGCHARGE_STOPTIME	32

#define PLAYER_SHOOTPUSHOVER	9

class Player : public BObject
{
public:
	Player();
	~Player();

	void valueSet(BYTE playerindex, BYTE round = 0);
	void ClearSet(BYTE round=0);
	void UpdatePlayerData();       
	void ResetPlayerGhost(bool move = false);
	static void ClearRound(BYTE round=0);

	void action();
	void actionInStop();
	void actionInSpellStop();

	void RenderEffect();

	bool Merge();
	bool Shot();
	bool CostLife();
	bool Collapse();
	bool Shoot();
	bool Drain();
	bool Bomb();
	bool SlowChange();
	bool FastChange();
	bool Charge();
	bool PlayerChange();
	bool Graze();

	void changePlayerID(WORD toID, bool moveghost=false);
	BYTE shootCharge(BYTE nChargeLevel, bool nodelete=false);
	void setShootingCharge(BYTE shootingchargeflag);

	void AddComboHit(int combo, bool ori);
	void AddSpellPoint(int spellpoint);
	void AddExPoint(float expoint, float x, float y);
	void AddGhostPoint(int ghostpoint, float x, float y);
	void AddBulletPoint(int bulletpoint, float x, float y);
	static void AddLilyCount(int lilycount, bool bytime=false);
	void AddCardBossLevel(int cardlevel, int bosslevel);

	void DoEnemyCollapse(float x, float y, BYTE type);
	void DoItemGet(WORD itemtype, float x, float y);
	void DoGraze(float x, float y);
	void DoPlayerBulletHit(int hitonfactor = PL_HITONFACTORDEFAULT);
	void DoSendBullet(float x, float y, int sendbonus=1);
	void DoShot();

	void Render();

	void initFrameIndex();
	void setFrame(BYTE frameenum);
	BYTE getFrameIndex(BYTE frameenum);
	void setIndexFrame(BYTE index);
	void updateFrame(BYTE frameenum, int usetimer = -1);

	void callCollapse();
	bool callBomb();
	void callSlowFastChange(bool toslow);
	void callPlayerChange();

	void SetInitLife(BYTE initlife);
	void SetChara(WORD id, WORD id_sub_1=0xffff, WORD id_sub_2=0xffff);
	void SetInfi(BYTE reasonflag, int infitimer=PLAYER_INFIMAX);
	bool HavePlayer(WORD ID);
	void GetNCharge(BYTE * ncharge=NULL, BYTE * nchargemax=NULL);
	void GetSpellClassAndLevel(BYTE * spellclass, BYTE * spelllevel, int _shootingchargeflag=-1);
	BYTE AddCharge(float addcharg=0, float addchargemaxe=0);

	void SetDrainSpriteInfo(float x, float y, int headangle=0, float hscale=1.0f, float vscale=0.0f, int copyspriteangle=0);

	static void AddLostStack();
	static void SetAble(bool setable);
	static bool CheckAble();
	static void SendEx(BYTE playerindex, float x, float y);

	static void Init();
	static bool Action();
	static void RenderAll(BYTE playerindex);
	static int IsMatchEnd();

public:
	WORD	ID_sub_1;
	WORD	ID_sub_2;
	WORD	nowID;

	bool	flipx;
	BYTE	frameoffset;
	BYTE	nowstate;

	float	lastx[PL_SAVELASTMAX];
	float	lasty[PL_SAVELASTMAX];
	float	lastmx[PL_SAVELASTMAX];
	float	lastmy[PL_SAVELASTMAX];

	PlayerGhost pg[PLAYERGHOSTMAX];

	EffectSp	esChange;
	EffectSp	esShot;
	EffectSp	esPoint;
	EffectSp	esCollapse;

	Effectsys	effGraze;
	Effectsys	effChange;
	Effectsys	effInfi;
	Effectsys	effCollapse;
	Effectsys	effMerge;
	Effectsys	effBorder;
	Effectsys	effBorderOn;
	Effectsys	effBorderOff;

	float	slowspeed;
	float	speedfactor;
	float	r;

	float	chargespeed;
	int		infitimer;

	bool	bSlow;
	bool	bCharge;
	bool	bDrain;
	bool	bInfi;

	float fExPoint;
	int nGhostPoint;
	int nBulletPoint;
	int	nSpellPoint;
	int nComboHit;
	int nComboHitOri;
	float fCharge;
	float fChargeMax;

	float fExSendParaB;
	float fExSendParaA;
	float fExSendMax;

	int nBounceAngle;

	hgeSprite * sprite;
	hgeSprite * spdrain;
	BYTE	frameindex[M_PL_ONESETPLAYER][PLAYER_FRAME_STATEMAX];
	BYTE	faceindex[M_PL_ONESETPLAYER];
	BYTE	nowframeindex;

	float	drainx;
	float	drainy;
	int		drainheadangle;
	float	drainhscale;
	float	drainvscale;
	int		draincopyspriteangle;

	WORD	flag;

	WORD	mergetimer;
	WORD	shottimer;
	WORD	collapsetimer;
	WORD	shoottimer;
	WORD	draintimer;
	WORD	chargetimer;
	WORD	slowtimer;
	WORD	fasttimer;
	WORD	playerchangetimer;
	WORD	costlifetimer;
	WORD	spellstoptimer;

	BYTE	shootingchargeflag;
	BYTE	nowshootingcharge;
	BYTE	shootchargetimer;

	BYTE	shootpushtimer;
	BYTE	shootnotpushtimer;

	BYTE	shotdelay;

	BYTE	rechargedelay;
	BYTE	rechargedelaytimer;

	BYTE	infireasonflag;

	BYTE	nLife;
	int		nLifeCost;
	BYTE	nComboGage;

	// add
	BYTE	initlife;
	BYTE	playerindex;

	BYTE	winflag;

	BYTE cardlevel;
	BYTE bosslevel;
	BYTE nowcardlevel;
	BYTE nowbosslevel;

	static BYTE rank;
	static int lilycount;

	static float lostStack;
	static bool able;

	static DWORD alltime;
	static BYTE	raisespellstopplayerindex;
	static BYTE round;

	static Player p[M_PL_MATCHMAXPLAYER];

};
#endif