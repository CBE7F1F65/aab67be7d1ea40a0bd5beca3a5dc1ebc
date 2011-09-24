/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hgeVector helper class
*/


#ifndef HGEVECTOR_H
#define HGEVECTOR_H


#include "hge.h"
/************************************************************************/
/* This header is deleted by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
//#include <math.h>

/*
** Fast 1.0/sqrtf(float) routine
*/
float InvSqrt(float x);

class hgeVector
{
public:
	float	x,y,z;

	hgeVector(float _x, float _y, float _z)	{ x=_x; y=_y; z=_z; }
	hgeVector()						{ x=0; y=0; z=0; }

	hgeVector	operator-  ()					const { return hgeVector(-x, -y, -z);		}
	hgeVector	operator-  (const hgeVector &v) const { return hgeVector(x-v.x, y-v.y, z-v.z); }
	hgeVector	operator+  (const hgeVector &v) const { return hgeVector(x+v.x, y+v.y, z+v.z); }
	hgeVector&	operator-= (const hgeVector &v)		  { x-=v.x; y-=v.y; z-=v.z; return *this;	}
	hgeVector&	operator+= (const hgeVector &v)		  { x+=v.x; y+=v.y;; z+=v.z; return *this;	}
	bool		operator== (const hgeVector &v)	const { return (x==v.x && y==v.y && z==v.z);		}
	bool		operator!= (const hgeVector &v)	const { return (x!=v.x || y!=v.y || z!=v.z);		}

	hgeVector	operator/  (const float scalar)	const { return hgeVector(x/scalar, y/scalar, z/scalar); }
	hgeVector	operator*  (const float scalar) const { return hgeVector(x*scalar, y*scalar, z*scalar); }
	hgeVector&	operator*= (const float scalar)		  { x*=scalar; y*=scalar; z*=scalar; return *this;   }

	float		Dot(const hgeVector *v) const { return x*v->x + y*v->y + z*v->z; }
	float		Length() const { return sqrtf(Dot(this)); }
	float		Angle(const hgeVector *v = 0) const;
	
	void		Clamp(const float max) { if(Length() > max)	{ Normalize(); x *= max; y *= max; z *= max; } }
	hgeVector*	Normalize() { float rc=InvSqrt(Dot(this)); x*=rc; y*=rc; z*=rc; return this; }
	hgeVector	Cross(const hgeVector * v) const
		{ return hgeVector(y*(v->z)-z*(v->y), z*(v->x)-x*(v->z), x*(v->y)-y*(v->x)); }
	hgeVector*	Rotate(float a);
};

inline hgeVector operator* (const float s, const hgeVector &v)		{ return v*s; }
inline float operator^ (const hgeVector &v, const hgeVector &u) { return v.Angle(&u); }
inline float operator% (const hgeVector &v, const hgeVector &u) { return v.Dot(&u); }


#endif


