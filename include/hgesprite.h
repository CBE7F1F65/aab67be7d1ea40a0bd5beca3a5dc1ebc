/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hgeSprite helper class header
*/


#ifndef HGESPRITE_H
#define HGESPRITE_H


#include "hge.h"
#include "hgerect.h"


/*
** HGE Sprite class
*/
class hgeSprite
{
public:
	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	hgeSprite();
	hgeSprite(HTEXTURE tex, float x, float y, float w, float h);
	hgeSprite(const hgeSprite &spr);
	~hgeSprite() { hge->Release(); }
	
	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	void		NewSprite(HTEXTURE tex, float x, float y, float w, float h);
	
	void		Render(float x, float y);
	void		RenderEx(float x, float y, float rot, float hscale=1.0f, float vscale=0.0f);
	void		RenderStretch(float x1, float y1, float x2, float y2);
	void		Render4V(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);

	void		SetTexture(HTEXTURE tex);
	void		SetTextureRect(float x, float y, float w, float h, bool adjSize = true);
	void		SetColor(DWORD col, int i=-1);
	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	void		SetColor(DWORD col0, DWORD col1, DWORD col2, DWORD col3);
	bool		SetZ(float z, int i = -1, hge3DPoint * ptfar=NULL);
	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	bool		SetZ(float z0, float z1, float z2, float z3, hge3DPoint *ptfar=NULL);
	void		SetBlendMode(int blend) { quad.blend=blend; }
	void		SetHotSpot(float x, float y) { hotX=x; hotY=y; }
	void		SetFlip(bool bX, bool bY, bool bHotSpot = false);

	HTEXTURE	GetTexture() const { return quad.tex; }
	/************************************************************************/
	/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	void		GetTextureRect(float *x, float *y, float *w, float *h) const { *x=tx-HGE_TEXTUREOFFSET; *y=ty-HGE_TEXTUREOFFSET; *w=width; *h=height; }
	DWORD		GetColor(int i=0) const { return quad.v[i].col; }
	float		GetZ(int i=0) const { return quad.v[i].z; }
	int			GetBlendMode() const { return quad.blend; }
	void		GetHotSpot(float *x, float *y) const { *x=hotX; *y=hotY; }
	void		GetFlip(bool *bX, bool *bY) const { *bX=bXFlip; *bY=bYFlip; }

	float		GetWidth() const { return width; }
	float		GetHeight() const { return height; }
	hgeRect*	GetBoundingBox(float x, float y, hgeRect *rect) const { rect->Set(x-hotX, y-hotY, x-hotX+width, y-hotY+height); return rect; }
	hgeRect*	GetBoundingBoxEx(float x, float y, float rot, float hscale, float vscale,  hgeRect *rect) const;

private:
	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	void		_SpriteInit();

public:
	static HGE	*hge;

	hgeQuad		quad;
	float		tx, ty, width, height;
	float		tex_width, tex_height;
	float		hotX, hotY;
	/************************************************************************/
	/* This member is added by h5nc (h5nc@yahoo.com.cn)                     */
	/************************************************************************/
	float		scale3d;
	bool		bXFlip, bYFlip, bHSFlip;
};


#endif

