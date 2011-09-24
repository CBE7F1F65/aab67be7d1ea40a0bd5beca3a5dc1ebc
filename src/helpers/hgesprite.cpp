/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hgeSprite helper class implementation
*/


#include "../../include/hgesprite.h"


HGE *hgeSprite::hge=0;

/************************************************************************/
/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
void hgeSprite::_SpriteInit()
{
	hge=hgeCreate(HGE_VERSION);

	tx=0;	ty=0;
	width=0;	height=0;
	hotX=0;	hotY=0;
	tex_width = 1.0f;
	tex_height = 1.0f;

	scale3d = 1.0f;
	bXFlip=false; bYFlip=false;
	bHSFlip=false;

	ZeroMemory(&quad, sizeof(hgeQuad));

	quad.v[0].col = 
		quad.v[1].col = 
		quad.v[2].col = 
		quad.v[3].col = 0xffffffff;

	quad.blend=BLEND_DEFAULT;

}

/************************************************************************/
/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
void hgeSprite::NewSprite(HTEXTURE texture, float texx, float texy, float w, float h)
{
	float texx1, texy1, texx2, texy2;

	tex_width = (float)hge->Texture_GetWidth(texture);
	tex_height = (float)hge->Texture_GetHeight(texture);

	if (!tex_width)
	{
		tex_width = 1;
	}
	if (!tex_height)
	{
		tex_height = 1;
	}

	if (w < 0 || h < 0)
	{
		w = tex_width;
		h = tex_height;
	}
	quad.tex=texture;
	SetTextureRect(texx, texy, w, h);
/*
	tx=texx; ty=texy;
	width=w; height=h;

	hotX=w/2; hotY=h/2;

	texx1=texx/tex_width;
	texy1=texy/tex_height;
	texx2=(texx+w)/tex_width;
	texy2=(texy+h)/tex_height;

	quad.v[0].tx = texx1; quad.v[0].ty = texy1;
	quad.v[1].tx = texx2; quad.v[1].ty = texy1;
	quad.v[2].tx = texx2; quad.v[2].ty = texy2;
	quad.v[3].tx = texx1; quad.v[3].ty = texy2;
*/
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
hgeSprite::hgeSprite()
{
	_SpriteInit();
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
hgeSprite::hgeSprite(HTEXTURE texture, float texx, float texy, float w, float h)
{
	_SpriteInit();
	NewSprite(texture, texx, texy, w, h);
}

hgeSprite::hgeSprite(const hgeSprite &spr)
{
	memcpy(this, &spr, sizeof(hgeSprite));
	hge=hgeCreate(HGE_VERSION);
}

void hgeSprite::Render(float x, float y)
{
	/************************************************************************/
	/* This condition is added by h5nc (h5nc@yahoo.com.cn)                  */
	/************************************************************************/
	
	if (hge->System_GetState(HGE_2DMODE))
	{
		RenderEx(x, y, 0);
		return;
	}
	
	float tempx1, tempy1, tempx2, tempy2;

	tempx1 = x-hotX;
	tempy1 = y-hotY;
	tempx2 = x+width-hotX;
	tempy2 = y+height-hotY;

	quad.v[0].x = tempx1; quad.v[0].y = tempy1;
	quad.v[1].x = tempx2; quad.v[1].y = tempy1;
	quad.v[2].x = tempx2; quad.v[2].y = tempy2;
	quad.v[3].x = tempx1; quad.v[3].y = tempy2;

	hge->Gfx_RenderQuad(&quad);
}


void hgeSprite::RenderEx(float x, float y, float rot, float hscale, float vscale)
{
	float tx1, ty1, tx2, ty2;
	float sint, cost;

	if(vscale==0) vscale=hscale;

	if (hge->System_GetState(HGE_2DMODE))
	{
		hscale *= scale3d;
		vscale *= scale3d;
	}

	tx1 = -hotX*hscale;
	ty1 = -hotY*vscale;
	tx2 = (width-hotX)*hscale;
	ty2 = (height-hotY)*vscale;

	if (rot != 0.0f)
	{
		cost = cosf(rot);
		sint = sinf(rot);
			
		quad.v[0].x  = tx1*cost - ty1*sint + x;
		quad.v[0].y  = tx1*sint + ty1*cost + y;	

		quad.v[1].x  = tx2*cost - ty1*sint + x;
		quad.v[1].y  = tx2*sint + ty1*cost + y;	

		quad.v[2].x  = tx2*cost - ty2*sint + x;
		quad.v[2].y  = tx2*sint + ty2*cost + y;	

		quad.v[3].x  = tx1*cost - ty2*sint + x;
		quad.v[3].y  = tx1*sint + ty2*cost + y;	
	}
	else
	{
		quad.v[0].x = tx1 + x; quad.v[0].y = ty1 + y;
		quad.v[1].x = tx2 + x; quad.v[1].y = ty1 + y;
		quad.v[2].x = tx2 + x; quad.v[2].y = ty2 + y;
		quad.v[3].x = tx1 + x; quad.v[3].y = ty2 + y;
	}

	hge->Gfx_RenderQuad(&quad);
}


void hgeSprite::RenderStretch(float x1, float y1, float x2, float y2)
{
	quad.v[0].x = x1; quad.v[0].y = y1;
	quad.v[1].x = x2; quad.v[1].y = y1;
	quad.v[2].x = x2; quad.v[2].y = y2;
	quad.v[3].x = x1; quad.v[3].y = y2;

	hge->Gfx_RenderQuad(&quad);
}


void hgeSprite::Render4V(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
{
	quad.v[0].x = x0; quad.v[0].y = y0;
	quad.v[1].x = x1; quad.v[1].y = y1;
	quad.v[2].x = x2; quad.v[2].y = y2;
	quad.v[3].x = x3; quad.v[3].y = y3;

	hge->Gfx_RenderQuad(&quad);
}


hgeRect* hgeSprite::GetBoundingBoxEx(float x, float y, float rot, float hscale, float vscale, hgeRect *rect) const
{
	float tx1, ty1, tx2, ty2;
	float sint, cost;

	rect->Clear();
	
	tx1 = -hotX*hscale;
	ty1 = -hotY*vscale;
	tx2 = (width-hotX)*hscale;
	ty2 = (height-hotY)*vscale;

	if (rot != 0.0f)
	{
		cost = cosf(rot);
		sint = sinf(rot);
			
		rect->Encapsulate(tx1*cost - ty1*sint + x, tx1*sint + ty1*cost + y);	
		rect->Encapsulate(tx2*cost - ty1*sint + x, tx2*sint + ty1*cost + y);	
		rect->Encapsulate(tx2*cost - ty2*sint + x, tx2*sint + ty2*cost + y);	
		rect->Encapsulate(tx1*cost - ty2*sint + x, tx1*sint + ty2*cost + y);	
	}
	else
	{
		rect->Encapsulate(tx1 + x, ty1 + y);
		rect->Encapsulate(tx2 + x, ty1 + y);
		rect->Encapsulate(tx2 + x, ty2 + y);
		rect->Encapsulate(tx1 + x, ty2 + y);
	}

	return rect;
}

void hgeSprite::SetFlip(bool bX, bool bY, bool bHotSpot)
{
	float tx, ty;

	if(bHSFlip && bXFlip) hotX = width - hotX;
	if(bHSFlip && bYFlip) hotY = height - hotY;

	bHSFlip = bHotSpot;
	
	if(bHSFlip && bXFlip) hotX = width - hotX;
	if(bHSFlip && bYFlip) hotY = height - hotY;

	if(bX != bXFlip)
	{
		tx=quad.v[0].tx; quad.v[0].tx=quad.v[1].tx; quad.v[1].tx=tx;
		ty=quad.v[0].ty; quad.v[0].ty=quad.v[1].ty; quad.v[1].ty=ty;
		tx=quad.v[3].tx; quad.v[3].tx=quad.v[2].tx; quad.v[2].tx=tx;
		ty=quad.v[3].ty; quad.v[3].ty=quad.v[2].ty; quad.v[2].ty=ty;

		bXFlip=!bXFlip;
	}

	if(bY != bYFlip)
	{
		tx=quad.v[0].tx; quad.v[0].tx=quad.v[3].tx; quad.v[3].tx=tx;
		ty=quad.v[0].ty; quad.v[0].ty=quad.v[3].ty; quad.v[3].ty=ty;
		tx=quad.v[1].tx; quad.v[1].tx=quad.v[2].tx; quad.v[2].tx=tx;
		ty=quad.v[1].ty; quad.v[1].ty=quad.v[2].ty; quad.v[2].ty=ty;

		bYFlip=!bYFlip;
	}
}


void hgeSprite::SetTexture(HTEXTURE tex)
{
	float tx1,ty1,tx2,ty2;
	float tw,th;

	quad.tex=tex;

	tw = (float)hge->Texture_GetWidth(tex);
	th = (float)hge->Texture_GetHeight(tex);
	if (!tw)
	{
		tw = 1;
	}
	if (!th)
	{
		th = 1;
	}

	if(tw!=tex_width || th!=tex_height)
	{
		tx1=quad.v[0].tx*tex_width;
		ty1=quad.v[0].ty*tex_height;
		tx2=quad.v[2].tx*tex_width;
		ty2=quad.v[2].ty*tex_height;

		tex_width=tw;
		tex_height=th;

		tx1/=tw; ty1/=th;
		tx2/=tw; ty2/=th;

		quad.v[0].tx=tx1; quad.v[0].ty=ty1; 
		quad.v[1].tx=tx2; quad.v[1].ty=ty1; 
		quad.v[2].tx=tx2; quad.v[2].ty=ty2; 
		quad.v[3].tx=tx1; quad.v[3].ty=ty2; 
	}
}


/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
void hgeSprite::SetTextureRect(float x, float y, float w, float h, bool adjSize)
{
	float tx1, ty1, tx2, ty2;
	bool bX,bY,bHS;

	tx=x+HGE_TEXTUREOFFSET;
	ty=y+HGE_TEXTUREOFFSET;

	if (w < 0 || h < 0)
	{
		w = tex_width;
		h = tex_height;
	}
	
	if(adjSize)
	{
		width=w;
		height=h;
	}

	tx1=tx/tex_width; ty1=ty/tex_height;
	tx2=(tx+w)/tex_width; ty2=(ty+h)/tex_height;

	quad.v[0].tx=tx1; quad.v[0].ty=ty1; 
	quad.v[1].tx=tx2; quad.v[1].ty=ty1; 
	quad.v[2].tx=tx2; quad.v[2].ty=ty2; 
	quad.v[3].tx=tx1; quad.v[3].ty=ty2; 

	bX=bXFlip; bY=bYFlip; bHS=bHSFlip;
	bXFlip=false; bYFlip=false;
	SetFlip(bX,bY,bHS);
	hotX = w / 2; hotY = h / 2;

/////////////////// consider animation frame somehow! ////////////////
}


/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
void hgeSprite::SetColor(DWORD col, int i)
{
	if(i!=-1) quad.v[i].col=col;
	else { quad.v[0].col=quad.v[1].col=quad.v[2].col=quad.v[3].col=col; }
}

/************************************************************************/
/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
void hgeSprite::SetColor(DWORD col0, DWORD col1, DWORD col2, DWORD col3)
{
	quad.v[0].col = col0;
	quad.v[1].col = col1;
	quad.v[2].col = col2;
	quad.v[3].col = col3;
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
bool hgeSprite::SetZ(float z, int i, hge3DPoint * ptfar)
{
	if(i == -1 || hge->System_GetState(HGE_2DMODE))
	{
		if (ptfar == NULL)
		{
			return false;
		}
		return SetZ(z, z, z, z, ptfar);
	}
	else
	{
		quad.v[i].z = z;
	}
	return true;
}

/************************************************************************/
/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
bool hgeSprite::SetZ(float z0, float z1, float z2, float z3, hge3DPoint *ptfar)
{
	quad.v[0].z = z0;
	quad.v[1].z = z1;
	quad.v[2].z = z2;
	quad.v[3].z = z3;

	if (ptfar)
	{
		for (int i=0; i<4; i++)
		{
			//use z0
			float zscale = hge->Math_Transform3DPoint(quad.v[i].x, quad.v[i].y, quad.v[0].z, ptfar);
			if (i == 0)
			{
				scale3d = zscale;
			}
			quad.v[i].z = 0;
		}
	}
	return true;
}
