#ifndef _PLAYERLASER_H
#define _PLAYERLASER_H

#include "BObject.h"
#include "Enemy.h"

class PlayerLaser : public BObject
{
public:
	static void Init();
	static void Build();

	static void Action();
	static void RenderAll();
	static bool CheckShoot(Enemy * en, float aimx, float aimy, float aimw, float aimh=0.0f);

	void action();
	void Render();

	void hitOn();
	bool isInRange(float aimx, float aimy, float w, float h=0.0f);

	static hgeSprite * sprite[DATASTRUCT_PLAYERLASERTYPEMAX][DATASTRUCT_PLAYERLASERTYPE];
};

#endif