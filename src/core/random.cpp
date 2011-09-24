/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: random number generation
*/


#include "hge_impl.h"


unsigned int g_seed=0;
unsigned int g_seed_self=0;

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
int CALL HGE_Impl::Random_Seed(int seed)
{
	if (!seed)
	{
		g_seed=Timer_GetCurrentSystemTime();
		g_seed_self=g_seed;
	}
	else
	{
		g_seed=seed;
	}
	return g_seed;
}

int CALL HGE_Impl::Random_Int(int min, int max, bool bSelf)
{
	unsigned int * usingseed = bSelf ? (&g_seed_self) : (&g_seed);
	*usingseed=214013*(*usingseed)+2531011;
	if (max-min+1 == 0)
	{
		return min;
	}
	return min+((*usingseed) ^ (*usingseed)>>15)%(max-min+1);
}

float CALL HGE_Impl::Random_Float(float min, float max, bool bSelf)
{
	unsigned int * usingseed = bSelf ? (&g_seed_self) : (&g_seed);
	*usingseed=214013*(*usingseed)+2531011;
	//return min+g_seed*(1.0f/4294967295.0f)*(max-min);
	if (max == min)
	{
		return min;
	}
	return min+(((*usingseed)>>16)*(max-min))*(1.0f/65535.0f);
}
