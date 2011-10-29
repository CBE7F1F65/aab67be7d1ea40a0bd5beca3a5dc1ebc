#ifndef _PLAYERLASER_H
#define _PLAYERLASER_H

#include "BObject.h"
#include "Enemy.h"

#define PLAYERLASER_BODYMAX			10
#define PLAYERLASER_ANIMATIONMAX	4

class PlayerLaser : public BObject
{
public:
	PlayerLaser();
	~PlayerLaser();

	static void Init();
	void Release();

	static void Shoot();
	static void StopFire();
	void shoot();
	void stopfire();

	static void Action();
	static void RenderAll();

	static bool CheckShoot(Enemy * en, float aimx, float aimy, float aimw, float aimh=0.0f);
	bool checkshoot(Enemy * en, float aimx, float aimy, float aimw, float aimh=0.0f);

	void init(int playerID);
	void action();
	void render();

	void hitOn(float ypos);
	BYTE isInRange(float aimx, float aimy, float w, float h=0.0f);

	hgeSprite * spbody[PLAYERLASER_BODYMAX];
	hgeSprite * spprotect[PLAYERLASER_ANIMATIONMAX];
	hgeSprite * sphead[PLAYERLASER_ANIMATIONMAX];
	hgeSprite * spbegin[PLAYERLASER_ANIMATIONMAX];
	hgeSprite * spstop[PLAYERLASER_ANIMATIONMAX];

	float headypos;
	bool bshooting;
	bool bstopped;

	static PlayerLaser plaser[DATASTRUCT_PLAYERLASERTYPEMAX];
};

#endif