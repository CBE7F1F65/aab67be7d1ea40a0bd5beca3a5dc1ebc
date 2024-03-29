#ifndef _PLAYER_H
#define _PLAYER_H

#include "BObject.h"
#include "EffectSp.h"
#include "PlayerGhost.h"
#include "PlayerBullet.h"
#include "Effectsys.h"

// add
#define PLAYER_DEFAULTINITLIFE	10

#define PLAYER_FRAME_STAND		0
#define PLAYER_FRAME_LEFTPRE	1
#define PLAYER_FRAME_LEFT		2
#define PLAYER_FRAME_RIGHTPRE	3
#define PLAYER_FRAME_RIGHT		4

#define PLAYER_FRAME_STATEMAX	5

#define PL_MOVABLEDGE_X		4
#define PL_MOVABLEDGE_Y		24
#define PL_MOVABLE_LEFT		(M_GAMESQUARE_LEFT-(M_MAPBOARDER_WIDTH-M_GAMESQUARE_WIDTH)/2+PL_MOVABLEDGE_X)
#define PL_MOVABLE_RIGHT	(M_GAMESQUARE_RIGHT+(M_MAPBOARDER_WIDTH-M_GAMESQUARE_WIDTH)/2-PL_MOVABLEDGE_X)
#define PL_MOVABLE_TOP		(M_GAMESQUARE_TOP+PL_MOVABLEDGE_Y*2)
#define PL_MOVABLE_BOTTOM	(M_GAMESQUARE_BOTTOM-PL_MOVABLEDGE_Y)

#define PL_MERGEPOS_X	(M_GAMESQUARE_CENTER_X/2)
#define PL_MERGEPOS_Y		(M_GAMESQUARE_BOTTOM)

#define PL_SAVELASTMAX		0x20

#define	PLAYER_MERGE				0x0001
#define	PLAYER_SHOT					0x0002
#define PLAYER_COSTLIFE				0x0004
#define	PLAYER_COLLAPSE				0x0008
#define	PLAYER_SHOOT				0x0010
#define PLAYER_LASER				0x0020
#define	PLAYER_BOMB					0x0040
#define	PLAYER_SLOWCHANGE			0x0100
#define	PLAYER_FASTCHANGE			0x0200
#define PLAYER_HYPER				0x0400
#define PLAYER_FREEZE				0x0800
#define	PLAYER_GRAZE				0x1000

#define PLAYER_INFIMAX		-1
#define PLAYER_INFIUNSET	0
#define PLAYERINFI_MERGE		0x01
#define PLAYERINFI_OVER			0x02
#define PLAYERINFI_CHAT			0x04
#define PLAYERINFI_COSTLIFE		0x08
#define PLAYERINFI_COLLAPSE		0x10
#define PLAYERINFI_BOMB			0x20
#define PLAYERINFI_HYPER		0x40
#define PLAYERINFI_FREEZE		0x80

#define PLAYER_CHARGEONE	100.0f
#define PLAYER_CHARGENMAX	4
#define PLAYER_CHARGEMAX	(PLAYER_CHARGEONE*PLAYER_CHARGENMAX)

#define PLAYER_COMBOGAGEMAX	10000

#define PLAYER_GRAZE_R	40

#define PLAYER_NCOMBOHITMAX		999
#define PLAYER_NSPELLPOINTMAX	999990

#define PL_SHOOTINGCHARGE_STOPTIME	32

#define PLAYER_SHOOTPUSHOVER	9

#define PLAYER_TEMPERMAX	10000
#define PLAYER_TEMPEREDGE	2000
#define PLAYER_TEMPERCOLDEDGE	(-PLAYER_TEMPERMAX+PLAYER_TEMPEREDGE)
#define PLAYER_TEMPERHOTEDGE	(PLAYER_TEMPERMAX-PLAYER_TEMPEREDGE)

#define PLAYER_HITDISPLAYTIMEMAX	120
#define PLAYER_HITDISPLAYFADE		60

#define PLAYER_BOMBMAX	6

#define PLAYER_HYPERTIMEMAX		360
#define PLAYER_HYPERINFITIMEMAX	60
#define PLAYER_FREEZETIMEMAX	60

#define TEMPERSTATE_NULL	0x00
#define TEMPERSTATE_COLD	0x01
#define TEMPERSTATE_HOT		0x02

class Player : public BObject
{
public:
	Player();
	~Player();

	void valueSet(BYTE round = 0);
	void ClearSet(BYTE round=0);
	void UpdatePlayerData();       
	void ResetPlayerGhost(bool move = false);

	void action();
	void actionInStop();

	void RenderEffect();

	bool Merge();
	bool Shot();
	bool CostLife();
	bool Collapse();
	bool Shoot();
	bool Laser();
	bool Bomb();
	bool SlowChange();
	bool FastChange();
	bool Graze();
	bool Hyper();
	bool Freeze();

	void changePlayerID(WORD toID, bool moveghost=false);

	void AddComboGage(int gage);
	void KeepComboGage();
	void AddComboHit(int combo);
	void AddScore(LONGLONG score);
	void AddScoreMul(float scoremul);
	void AddHitScore(LONGLONG score);
	void AddTemper(int temper);

	void DoEnemyCollapse(float x, float y, BYTE type);
	void DoItemGet(WORD itemtype, float x, float y);
	void DoGraze(float x, float y);
	void DoPlayerBulletKill(BYTE type);
	void DoPlayerLaserHit(BYTE type, bool hitprotect);
	void DoPlayerLaserKill(BYTE type);
	void DoShot();
	void DoBulletDead(float x, float y, bool frozen);

	void Render();

	void initFrameIndex();
	void setFrame(BYTE frameenum);
	BYTE getFrameIndex(BYTE frameenum);
	void setIndexFrame(BYTE index);
	void updateFrame(BYTE frameenum, int usetimer = -1);

	void callCollapse();
	bool callBomb(bool bpassive=false);
	void callSlowFastChange(bool toslow);
	void callFreeze();
	void callHyper();

	void SetInitLife(BYTE initlife);
	void SetChara(WORD id);
	void SetInfi(BYTE reasonflag, int infitimer=PLAYER_INFIMAX);

	void SetAble(bool setable);
	bool CheckAble();

	void SetEnemyTemper(BYTE temperstate);

	float GetHyperCostLife(float hyperpower);

	static void Init();
	static bool Action();
	static void RenderAll();
	static int IsEnd();

public:
	WORD	ID;

	bool	flipx;
	BYTE	frameoffset;
	BYTE	nowstate;

	float	lastx[PL_SAVELASTMAX];
	float	lasty[PL_SAVELASTMAX];
	float	lastmx[PL_SAVELASTMAX];
	float	lastmy[PL_SAVELASTMAX];

	PlayerGhost pg[DATASTRUCT_PLAYERSUBMAX];

	EffectSp	esShot;
	EffectSp	esPoint;
	EffectSp	esCollapse;

	Effectsys	effGraze;
	Effectsys	effCollapse;

	float	slowspeed;
	float	speedfactor;
	float	r;

	int		infitimer;

	bool	bSlow;
	bool	bInfi;
	bool	bLaser;

	hgeSprite * sprite;
	BYTE	frameindex[PLAYER_FRAME_STATEMAX];
	BYTE	nowframeindex;

	WORD	flag;

	WORD	mergetimer;
	WORD	collapsetimer;
	WORD	shoottimer;
	WORD	lasertimer;
	WORD	bombtimer;
	WORD	slowtimer;
	WORD	fasttimer;
	WORD	costlifetimer;
	WORD	hypertimer;
	WORD	freezetimer;

	BYTE	shootpushtimer;
	BYTE	shootnotpushtimer;

	BYTE	shotdelay;

	BYTE	infireasonflag;

	int		nComboGage;

	int		nTemper;
	BYTE	temperSelf;
	BYTE	temperEnemy;
	BYTE	lastWeapon;
	BYTE	lastStableWeapon;

	bool	bhyper;
	bool	bfreeze;

	LONGLONG	nScore;
	LONGLONG	nHiScore;
	LONGLONG	nHitScore;
	LONGLONG	nLastHitScore;
	float	fScoreMul;
	float	fLastScoreMul;

	int nComboHit;
	int nComboHitMax;
	int nLastComboHit;

	BYTE	nBomb;
	BYTE	nBombMax;
	bool	bPassiveBomb;

	BYTE	hitdisplaykeeptimer;

	// add
	BYTE	initlife;
	BYTE	nLife;
	bool	able;


	static BYTE rank;


	static DWORD alltime;
	static BYTE round;

	static Player p;

};
#endif