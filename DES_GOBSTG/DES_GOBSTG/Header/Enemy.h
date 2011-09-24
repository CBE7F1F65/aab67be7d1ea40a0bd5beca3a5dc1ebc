#ifndef _ENEMY_H
#define _ENEMY_H

#include "BObject.h"
#include "EffectSp.h"
#include "Effectsys.h"
#include "Target.h"

#define ENEMYMAX			0x60

#define ENEMY_MAINBOSSINDEX	0

#define ENID_LEFTIDBEGIN	0x0
#define ENID_LEFTIDUNTIL	(ENEMYMAX/2)
#define ENID_RIGHTIDBEGIN	ENID_LEFTIDUNTIL
#define ENID_RIGHTIDUNTIL	ENEMYMAX

#define ENEMY_TEXMAX		4
#define ENEMY_PARAMAX		4

#define ENEMY_BOSSMAX		ENEMY_TEXMAX

#define ENEMY_ANIMATIONSPEED	8

#define ENEMY_BOSSINFITIMER		240
#define ENEMY_BOSSMOVELIMIT		0.01f
#define ENEMY_ENEMYMOVELIMIT	0.2f

#define ENEMY_FRAME_STAND		0
#define ENEMY_FRAME_RIGHTPRE	1
#define ENEMY_FRAME_RIGHT		2
#define ENEMY_FRAME_LEFTPRE		3
#define ENEMY_FRAME_LEFT		4
#define ENEMY_FRAME_ATTACKPRE	5
#define ENEMY_FRAME_ATTACK		6
#define ENEMY_FRAME_STOREPRE	7
#define ENEMY_FRAME_STORE		8

#define ENEMY_FRAME_STATEMAX	9

//#define ENEMY_COLLISIONR		8

#define ENEMY_BOSSX_FADERANGE	32

#define ENEMYACTION_NONE		0x00
#define	ENEMYACTION_ATTACK		0x01
#define	ENEMYACTION_STORE		0x02

#define ENAC_NONE			0x00

#define ENAC_DIRECTSET_XYSOAOOO		0x01
#define ENAC_CHASEPLAYER_OOSFATOO	0x02
#define ENAC_CHASEAIM_XYSOAOCO		0x03
#define ENAC_TURNANGLE_OOOOATOE		0x04

#define ENAC_FADEOUT_OOOOOTOO			0x40

#define ENAC_REPOSITION_OOOOOOCO		0x80
#define ENAC_OVERPLAYER_XYOOOTCE		0x81

#define ENAC_DELAY_OOOOOTOO			0xC0

#define ENAZTYPEMASK	0x0f
#define ENAZTYPE_NONE			0x00
#define ENAZTYPE_CIRCLE			0x01
#define ENAZTYPE_ELLIPSE		0x02
#define ENAZTYPE_RECT			0x04
#define ENAZTYPE_RIGHTANGLED	0x08

#define ENAZOPMASK	0xf0
#define ENAZOP_NONE		0x00
#define ENAZOP_AND		0x10
#define ENAZOP_OR		0x20
#define ENAZOP_NOTAND	0x40
#define ENAZOP_NOTOR	0x80

#define ENEMY_NMAXSETMAX	0x10

#define ENEMYFLAG_PBSHOTABLE	0x0001
#define ENEMYFLAG_BLASTSHOTABLE	0x0002
#define ENEMYFLAG_EZONESHOTABLE	0x0004
#define ENEMYFLAG_NOPLAYERCOLLISION	0x0100
#define ENEMYFLAG_STANDSHAKE	0x1000

struct EnemyActivationZone 
{
	float x;
	float y;
	float rPrep;
	float rParal;
	int angle;
	BYTE flag;
};

struct ScoreDisplay
{
	char	cScore[M_STRITOAMAX];
	float	x;
	float	y;
	bool	yellow;
	BYTE	timer;
};

class Enemy : public BObject
{
public:
	Enemy();
	~Enemy();

	static int Build(WORD eID, BYTE playerindex, float x, float y, int angle, float speed, BYTE type, float life, int infitimer=0);
	static void Init();
	static void Release();
	static void Action();
	static void ClearAll();
	static void RenderAll(BYTE playerindex);
	static void RenderScore(BYTE playerindex);

	static void BuildENAZ(BYTE playerindex, BYTE flag, float x, float y, float rPrep, float rParal=0, int angle=9000);

	static void BossFadeout(BYTE playerindex);

	void Clear();
	bool isInRect(float x, float y, float r, float w, float h, int nextstep=0);
	void Fadeout();

	void valueSet(BYTE playerindex, WORD eID, float x, float y, int angle, float speed, BYTE type, float life, int infitimer);

	void setTar(BYTE tarID=0xff);
	void setTake(DWORD take=0);
	void setAction(WORD ac=ENAC_NONE, float para_x=0, float para_y=0, float para_speed=0, float para_friction=0, int para_angle=0, int para_time=0, int para_counter=0, int para_endtime=0);
	void setLevelAim(int level=0, float aimx=0, float aimy=0, int aimangle=0);

	void initFrameIndex();
	void setFrame(BYTE frameenum);
	BYTE getFrameIndex(BYTE frameenum);
	void setIndexFrame(BYTE index);
	void updateFrame(BYTE frameenum, int usetimer = -1);
	void updateFrameAsMove();

	void DoShot();
	bool DoActivate();
	void ForceActive();
	bool checkActive();
	static bool CheckENAZ(BYTE playerindex, float x, float y, float rori=0);

	void action();
	void actionInStop();
	void matchAction();
	void updateAction();
	void ChangeType(BYTE type);

	void GetBlastInfo(BYTE * maxtime=NULL, float * r=NULL, float * power=NULL);

	void GetCollisionRect(float * w, float * h);
	bool CostLife(float power);

	void giveItem(BYTE playerindex);

	void Render();
	void RenderEffect();

	static void SendGhost(BYTE playerindex, float x, float y, BYTE setID, BYTE * sendtime=NULL, float * acceladd=NULL);
	void AddSendInfo(BYTE sendsetID, BYTE sendtime, float accel, float acceladd);
	void SetActiveInfo(BYTE activemaxtime, WORD eID, BYTE type, int angle, float accelspeed, float damagerate);

public:
	Effectsys	effCollapse;
	Effectsys	effShot;
	Effectsys	eff;

	union{
		struct{
			float para_x;
			float para_y;
			float para_speed;
			float para_friction;
		};
		float fpara[ENEMY_PARAMAX];
	};
	union{
		struct{
			int para_angle;
			int para_time;
			int para_counter;
			int para_endtime;
		};
		int ipara[ENEMY_PARAMAX];
	};
//	float	para[ENEMY_PARAMAX];
	Target	aim;
	int		aimangle;
	int	level;
	float	lastx;
	float	life;
	float	damagerate;
	int		take;

	float	accel;
	float	acceladd;

	float	xplus;
	float	yplus;
	float	lastspeed;
	int		lastangle;

	BYTE	playerindex;

	bool	fadeout;
	bool	able;
	bool	damage;
	int		infitimer;
	float	maxlife;
	bool	bturnhead;

	WORD	flag;

	WORD	ac;
	BYTE	type;
	BYTE	damagetimer;

	bool	flipx;
	BYTE	frameoffset;
	BYTE	nowstate;
	BYTE	faceindex;

	BYTE	sendtime;
	BYTE	sendsetID;
	BYTE	activetimer;
	BYTE	activemaxtime;

	BYTE	actionflag;
	BYTE	storetimer;

	BYTE	frameindex[ENEMY_FRAME_STATEMAX];

	static BYTE	bossindex[M_PL_MATCHMAXPLAYER];
	static BYTE nEnemyNow[M_PL_MATCHMAXPLAYER][ENEMY_NMAXSETMAX];

	hgeSprite * sprite;
	static VectorList<Enemy> en[M_PL_MATCHMAXPLAYER];
	static list<EnemyActivationZone> enaz[M_PL_MATCHMAXPLAYER];
	static VectorList<ScoreDisplay> scoredisplay[M_PL_MATCHMAXPLAYER];
};

#endif