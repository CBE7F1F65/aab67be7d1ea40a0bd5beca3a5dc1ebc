#include "../header/BObject.h"

BObject BObject::bobj;
float BObject::newx=0;
float BObject::newy=0;

BObject::BObject()
{
	_Init();
}

BObject::BObject(float _x, float _y)
{
	_Init();
	x = _x;
	y = _y;
}

void BObject::_Init()
{
	exist	= false;
	alpha	= 0xff;
	diffuse	= 0xffffff;
	tarID	= 0xff;
}

BObject::~BObject()
{
}

int BObject::rMainAngle(float destx, float desty, float r)
{
	//r>0 clockwise
	//r<0 counterclockwise
	float dx = destx - x;
	float dy = desty - y;
	float atanA, atanB;

	if(dx == 0)
	{
		if(dy >= 0)
			atanA = M_PI_2;
		else
			atanA = -M_PI_2;
	}
	else
		atanA = atan2f(dy, dx);
//	if(dx < 0)
//		atanA += M_PI;
	if(r == 0)
		atanB = 0;
	else
		atanB = atan2f(r, sqrt(dx*dx + dy*dy));
	return ANGLE(atanA + atanB);
}

int BObject::aMainAngle(float destx, float desty, int a)
{
	//a>0 clockwise
	//a<0 counterclockwise
	float dx = destx - x;
	float dy = desty - y;
	float atanA;
	if(dx == 0)
	{
		if(dy >= 0)
			atanA = M_PI_2;
		else
			atanA = -M_PI_2;
	}
	else
		atanA = atan2f(dy, dx);
//	if(dx < 0)
//		atanA += M_PI;
	return ANGLE(atanA)+a;
}

int BObject::chaseAim(float destx, float desty, int chasetimer)
{
	angle = aMainAngle(destx, desty);
	if (chasetimer > 1)
	{
		speed = 2 * DIST(x, y, destx, desty) / chasetimer;
	}
	else
		speed = BOBJ_M_CHASEAIM_SPEEDMIN;
	return chasetimer - 1;
}

void BObject::updateMove()
{
	x += speed * cost(angle);
	y += speed * sint(angle);
}


bool BObject::checkCollisionCircle(float aimx, float aimy, float r)
{
	if((fabsf(x-aimx)>r)||(fabsf(y-aimy)>r))
		return false;

	if((x-aimx)*(x-aimx)+(y-aimy)*(y-aimy) <= r*r)
		return true;

	return false;
}

bool BObject::checkCollisionBigCircle(float aimx, float aimy, float r)
{
	if (!checkCollisionSquare(aimx, aimy, r, r))
		return false;
	if (checkCollisionSquare(aimx, aimy, r*M_SQRT1_2, r*M_SQRT1_2))
		return true;
	if((x-aimx)*(x-aimx)+(y-aimy)*(y-aimy) <= r*r)
		return true;
	return false;
}

bool BObject::checkCollisionRect(float aimx, float aimy, float rectPrep, float rectParal, float rotCos, float rotSin, float rOri)
{
	float longside = rectPrep > rectParal ? rectPrep : rectParal;

	if((fabsf(x-aimx)>longside*M_SQRT2+rOri)||(fabsf(y-aimy)>longside*M_SQRT2+rOri))
		return false;

	newx = (float)((rotSin*(aimx-x)-rotCos*(aimy-y)));
	newy = (float)((rotCos*(aimx-x)+rotSin*(aimy-y)));

	if (fabsf(newx) <= rectPrep+rOri && fabsf(newy) <= rectParal+rOri)
	{
		return true;
	}

	return false;
}

bool BObject::checkCollisionRightAngled(float aimx, float aimy, float rightPrep, float rightParal, float rotCos /* = 0 */, float rotSin /* = 1 */, float rOri /* = 0 */)
{
	if (!checkCollisionRect(aimx, aimy, rightPrep, rightParal, rotCos, rotSin, rOri))
	{
		return false;
	}

	float ryoffset = 0;
	if (rOri)
	{
		ryoffset = sqrtf(rightPrep*rightPrep + rightParal*rightParal) * rOri;
	}
	if (-rightParal*newx + ryoffset <= rightPrep*newy)
	{
		return true;
	}
	return false;
}

bool BObject::checkCollisionEllipse(float aimx, float aimy, float rPrep, float rParal, float rotCos, float rotSin, float rOri)
{
	float longr = rPrep > rParal ? rPrep : rParal;

	if((fabsf(x-aimx)>longr+rOri)||(fabsf(y-aimy)>longr+rOri))
		return false;

	newx = (float)((rotSin*(aimx-x)-rotCos*(aimy-y)));
	newy = (float)((rotCos*(aimx-x)+rotSin*(aimy-y)));

	if(newx*newx*(rParal+rOri)*(rParal+rOri)+newy*newy*(rPrep+rOri)*(rPrep+rOri) <= (rPrep+rOri)*(rPrep+rOri)*(rParal+rOri)*(rParal+rOri))
		return true;

	return false;
}

bool BObject::checkCollisionSquare(float aimx, float aimy, float length, float height, float rOri)
{
	if (!height)
	{
		height = length;
	}
	if (fabsf(x - aimx) <= length+rOri && fabsf(y - aimy) <= height+rOri)
	{
		return true;
	}

	return false;
}