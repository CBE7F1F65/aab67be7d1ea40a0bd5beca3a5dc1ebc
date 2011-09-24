#include "../header/InfoQuad.h"

InfoQuad::InfoQuad()
{
}

InfoQuad::~InfoQuad()
{
}

void InfoQuad::Init()
{
}

void InfoQuad::valueSet(
		BYTE _type, float _x, float _y,
		float x0, float y0, DWORD col0,
		float x1, float y1, DWORD col1,
		float x2, float y2, DWORD col2,
		float x3, float y3, DWORD col3
		)
{
	type		=	_type;
	x			=	_x;
	y			=	_y;

	HTEXTURE tex(TEX_WHITE, NULL);
	quad.tex	=	tex;

	quad.v[0].tx = 0;	quad.v[0].ty = 0;
	quad.v[0].x = x0;	quad.v[0].y = y0;	quad.v[0].z = 0;
	quad.v[0].col = col0;

	quad.v[1].tx = 1;	quad.v[1].ty = 0;
	quad.v[1].x = x1;	quad.v[1].y = y1;	quad.v[1].z = 0;
	quad.v[1].col = col1;

	quad.v[2].tx = 1;	quad.v[2].ty = 1;
	quad.v[2].x = x2;	quad.v[2].y = y2;	quad.v[2].z = 0;
	quad.v[2].col = col2;

	quad.v[3].tx = 0;	quad.v[3].ty = 1;
	quad.v[3].x = x3;	quad.v[3].y = y3;	quad.v[3].z = 0;
	quad.v[3].col = col3;
	
	quad.blend = BLEND_DEFAULT;
}
