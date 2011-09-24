#ifndef _OBJECT_H
#define _OBJECT_H

#include "MainDependency.h"
#include "Const.h"
#include "BMath.h"

#define BOBJ_M_CHASEAIM_SPEEDMIN	0.1f

class BObject
{
public:
	BObject();
	BObject(float x, float y);
	void _Init();
	~BObject();

	int rMainAngle(float destx, float desty, float r = 0);
	int aMainAngle(float destx, float desty, int a = 0);

	static int RMainAngle(float x, float y, float destx, float desty, float r = 0)
	{
		bobj.x = x;
		bobj.y = y;
		return bobj.rMainAngle(destx, desty, r);
	}
	static int AMainAngle(float x, float y, float destx, float desty, int a = 0)
	{
		bobj.x = x;
		bobj.y = y;
		return bobj.aMainAngle(destx, desty, a);
	}

	int chaseAim(float destx, float desty, int chasetimer);
	static int ChaseAim(float x, float y, float destx, float desty, int chasetimer)
	{
		bobj.x = x;
		bobj.y = y;
		return bobj.chaseAim(destx, desty, chasetimer);
	};

	bool checkCollisionCircle(float aimx, float aimy, float r);
	bool checkCollisionBigCircle(float aimx, float aimy, float r);
	bool checkCollisionEllipse(float aimx, float aimy, float rPrep, float rParal, float rotCos = 0, float rotSin = 1, float rOri = 0);
	bool checkCollisionEllipse(float aimx, float aimy, float rPrep, float rParal, int angle=9000, float rOri=0)
	{
		return checkCollisionEllipse(aimx, aimy, rPrep, rParal, cost(angle), sint(angle), rOri);
	};
	bool checkCollisionRect(float aimx, float aimy, float rectPrep, float rectParal, float rotCos = 0, float rotSin = 1, float rOri = 0);
	bool checkCollisionRect(float aimx, float aimy, float rectPrep, float rectParal, int angle=9000, float rOri=0)
	{
		return checkCollisionRect(aimx, aimy, rectPrep, rectParal, cost(angle), sint(angle), rOri);
	};
	bool checkCollisionRightAngled(float aimx, float aimy, float rightPrep, float rightParal, float rotCos = 0, float rotSin = 1, float rOri = 0);
	bool checkCollisionRightAngled(float aimx, float aimy, float rightPrep, float rightParal, int angle=9000, float rOri=0)
	{
		return checkCollisionRightAngled(aimx, aimy, rightPrep, rightParal, cost(angle), sint(angle), rOri);
	};
	bool checkCollisionSquare(float aimx, float aimy, float length, float height = 0, float rOri=0);

	static bool CheckCollisionCircle(float x, float y, float aimx, float aimy, float r)
	{
		bobj.x = x;
		bobj.y = y;
		return bobj.checkCollisionCircle(aimx, aimy, r);
	};
	static bool CheckCollisionBigCircle(float x, float y, float aimx, float aimy, float r)
	{
		bobj.x = x;
		bobj.y = y;
		return bobj.checkCollisionBigCircle(aimx, aimy, r);
	};
	static bool CheckCollisionEllipse(float x, float y, float aimx, float aimy, float rPrep, float rParal, float rotCos = 0, float rotSin = 1, float rOri = 0)
	{
		bobj.x = x;
		bobj.y = y;
		return bobj.checkCollisionEllipse(aimx, aimy, rPrep, rParal, rotCos, rotSin, rOri);
	};
	static bool CheckCollisionEllipse(float x, float y, float aimx, float aimy, float rPrep, float rParal, int angle=9000, float rOri=0)
	{
		return CheckCollisionEllipse(x, y, aimx, aimy, rPrep, rParal, cost(angle), sint(angle), rOri);
	};
	static bool CheckCollisionRect(float x, float y, float aimx, float aimy, float rectPrep, float rectParal, float rotCos = 0, float rotSin = 1, float rOri = 0)
	{
		bobj.x = x;
		bobj.y = y;
		return bobj.checkCollisionRect(aimx, aimy, rectPrep, rectParal, rotCos, rotSin, rOri);
	};
	static bool CheckCollisionRect(float x, float y, float aimx, float aimy, float rectPrep, float rectParal, int angle=9000, float rOri=0)
	{
		return CheckCollisionRect(x, y, aimx, aimy, rectPrep, rectParal, cost(angle), sint(angle), rOri);
	};
	static bool CheckCollisionRightAngled(float x, float y, float aimx, float aimy, float rightPrep, float rightParal, float rotCos = 0, float rotSin = 1, float rOri = 0)
	{
		bobj.x = x;
		bobj.y = y;
		return bobj.checkCollisionRightAngled(aimx, aimy, rightPrep, rightParal, rotCos, rotSin, rOri);
	};
	static bool CheckCollisionRightAngled(float x, float y, float aimx, float aimy, float rightPrep, float rightParal, int angle=9000, float rOri=0)
	{
		return CheckCollisionRightAngled(x, y, aimx, aimy, rightPrep, rightParal, cost(angle), sint(angle), rOri);
	};
	static bool CheckCollisionSquare(float x, float y, float aimx, float aimy, float length, float height = 0, float rOri=0)
	{
		bobj.x = x;
		bobj.y = y;
		return bobj.checkCollisionSquare(aimx, aimy, length, height, rOri);
	};

	void updateMove();

public:
	float	x;
	float	y;
	int		angle;
	int		headangle;
	float	speed;
	float	vscale;
	float	hscale;
	DWORD	diffuse;
	DWORD	timer;
	bool	exist;

	WORD	ID;
	BYTE	alpha;
	BYTE	tarID;
private:
	static BObject bobj;
	static float newx;
	static float newy;
};

#endif