/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hgeFont helper class header
*/


#ifndef HGEFONT_H
#define HGEFONT_H


#include "hge.h"
#include "hgesprite.h"


#define HGETEXT_LEFT		0
#define HGETEXT_RIGHT		1
#define HGETEXT_CENTER		2
#define HGETEXT_HORZMASK	0x03

#define HGETEXT_TOP			0
#define HGETEXT_BOTTOM		4
#define HGETEXT_MIDDLE		8
#define HGETEXT_VERTMASK	0x0C

/*
** HGE Font class
*/
class hgeFont
{
public:
	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	hgeFont(int size=256);
	hgeFont(const char *filename, bool bMipmap=false);
	~hgeFont();
#ifdef __WIN32
	static bool CreateFontFileByInfo(int * charcode, int num, const char * fontfilename, HD3DFONT d3dfont, int fontscale=1);
#endif

	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	void		NewFont(const char *filename, bool bMipmap=false);
	void		Render(float x, float y, int align, const char *string);
	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	void		RenderEx(float x, float y, int align, const char *string, float scale=1.0f, float properation=1.0f, float rotation=0, float tracking=0, float spacing=1.0f);
	void		printf(float x, float y, int align, const char *buffer);
	void		printfb(float x, float y, float w, float h, int align, const char *buffer);

	/************************************************************************/
	/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	void		SetColor(DWORD col, int i=-1);
	/************************************************************************/
	/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
	void		SetColor(DWORD col0, DWORD col1, DWORD col2, DWORD col3);
	void		SetZ(float z, hge3DPoint *ptfar=NULL);
	void		SetBlendMode(int blend);
	void		SetScale(float scale) {fScale=scale;}
	void		SetProportion(float prop) { fProportion=prop; }
	void		SetRotation(float rot) {fRot=rot;}
	void		SetTracking(float tracking) {fTracking=tracking;}
	void		SetSpacing(float spacing) {fSpacing=spacing;}

	/************************************************************************/
	/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	DWORD		GetColor(int i=0);
	float		GetZ() const {return fZ;}
	int			GetBlendMode() const {return nBlend;}
	float		GetScale() const {return fScale;}
	float		GetProportion() const { return fProportion; }
	float		GetRotation() const {return fRot;}
	float		GetTracking() const {return fTracking;}
	float		GetSpacing() const {return fSpacing;}

	/************************************************************************/
	/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	// begin
	void		ChangeSprite(int chr, HTEXTURE tex, float tex_x, float tex_y, float tex_w, float tex_h, float pre_a=-1, float post_c=-1, int wCh=-1);
	void		ChangeSprite(int chr, hgeSprite * sprite, float pre_a=-1, float post_c=-1);
	// end
	hgeSprite*	GetSprite(int chr) const { return letters[chr]; }
	float		GetPreWidth(int chr) const { return pre[chr]; }
	float		GetPostWidth(int chr) const { return post[chr]; }
	float		GetHeight() const { return fHeight; }
	float		GetStringWidth(const char *string, bool bMultiline=true) const;
	int			ChangeWideChar(int wchr);
private:
	hgeFont(const hgeFont &fnt);
	hgeFont&	operator= (const hgeFont &fnt);

	char*		_get_line(char *file, char *line);
	/************************************************************************/
	/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
	/************************************************************************/
	void		_FontInit(int size=256);
	void		_FontFree();
	void		_FontTexResize(int texnum=0);
	void		_FontResize(int size=256);

	static HGE	*hge;

public:
	HTEXTURE *	hTexture;
	int			texnum;
	int			size;

	hgeSprite**	letters;
	/************************************************************************/
	/* These members are added by h5nc (h5nc@yahoo.com.cn)                  */
	/************************************************************************/
	DWORD		col[4];
private:
	float *		pre;
	float *		post;
	int	*		wCh;

	float		fHeight;
	float		fScale;
	float		fProportion;
	float		fRot;
	float		fTracking;
	float		fSpacing;
	/************************************************************************/
	/* This member is deleted by h5nc (h5nc@yahoo.com.cn)                   */
	/************************************************************************/
//	DWORD		dwCol;
	float		fZ;
	int			nBlend;
	bool		bWide;
};


#endif

