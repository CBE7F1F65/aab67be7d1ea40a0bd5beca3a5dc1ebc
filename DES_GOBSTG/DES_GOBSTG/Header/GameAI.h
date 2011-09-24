#ifndef _GAMEAI_H
#define _GAMEAI_H

#include "MainDependency.h"
#include "BObject.h"
#include "Bullet.h"
#include "Beam.h"
#include "Enemy.h"
#include "Item.h"
#include "EventZone.h"

#define GAMEAI_ABLEPOSITION_N		16

#define GAMEAI_ABLEPOSITION_U		0
#define GAMEAI_ABLEPOSITION_RU		1
#define GAMEAI_ABLEPOSITION_R		2
#define GAMEAI_ABLEPOSITION_RD		3
#define GAMEAI_ABLEPOSITION_D		4
#define GAMEAI_ABLEPOSITION_LD		5
#define GAMEAI_ABLEPOSITION_L		6
#define GAMEAI_ABLEPOSITION_LU		7

#define GAMEAI_ABLEPOSITION_US		8
#define GAMEAI_ABLEPOSITION_RUS		9
#define GAMEAI_ABLEPOSITION_RS		10
#define GAMEAI_ABLEPOSITION_RDS		11
#define GAMEAI_ABLEPOSITION_DS		12
#define GAMEAI_ABLEPOSITION_LDS		13
#define GAMEAI_ABLEPOSITION_LS		14
#define GAMEAI_ABLEPOSITION_LUS		15

#define GAMEAI_ABLEPOSITIONNUM	17

#ifndef INT_MAX
#define INT_MAX 2147483647 
#endif // INT_MAX
#define GAMEAI_RISK_DEATH	INT_MAX

#define GAMEAI_RISK_FULL	1000
#define GAMEAI_RISK_QUITE	750
#define GAMEAI_RISK_MEDIUM	500
#define GAMEAI_RISK_SOME	250
#define GAMEAI_RISK_NONE	0

struct GameAIPosition{
	float x;
	float y;
	int risk;
};

class GameAI : public BObject
{
public:
	GameAI();
	~GameAI();

	static void Init();
	static void ClearAll();

	void SetAble(bool able);

	bool UpdateBasicInfo(float x, float y, float speed, float slowspeed, float r, int aidraintime);
	bool SetAim(float aimx, float aimy, bool tobelow=false);
	bool UpdateMoveAbleInfo();
	void UpdateMoveAbleInfoOne(GameAIPosition * ppos, float basex, float basey);
	bool IsPlayerSafe();
	bool CheckBulletCollision(Bullet * bulletitem);
	bool CheckBeamCollision(Beam * beamitem);
	bool CheckEnemyCollision(Enemy * enemyitem, float w, float h);
	bool CheckEventZoneCollision(EventZone * ezoneitem);
	bool SetMove();
	void SetKeyByIndex(int index);
	void ClearRisk();

	void AnalyzeCheckOrder(float tox, float toy, float neutral, float randxprop, float randyprop);
	int AnalyzeCheckOrderXY(float toxy, float neutral, float randxyprop);
	void AnalyzeCheckOrderFinal(float tox, float toy, int xtend, int ytend);
	void UpdateCheckOrder(int xtend, int ytend, int neutralpos);

public:

	BYTE playerindex;
	float slowspeed;
	float r;
	GameAIPosition moveablepos[GAMEAI_ABLEPOSITIONNUM];
	GameAIPosition lastmoveablepos[GAMEAI_ABLEPOSITIONNUM];
	GameAIPosition nextmoveablepos[GAMEAI_ABLEPOSITIONNUM][GAMEAI_ABLEPOSITIONNUM];

	int drainpushtimer;
	int drainmaxpushtime;
	int aidraintime;

	float aimx;
	float aimy;
	bool aimtobelow;

	bool inrisk;

	bool able;

	int checkorderlist[GAMEAI_ABLEPOSITIONNUM];

	static GameAI ai[M_PL_MATCHMAXPLAYER];
};

#endif