#ifndef _SPRITEITEMMANAGER_H
#define _SPRITEITEMMANAGER_H

#include "MainDependency.h"
#include "DataStruct.h"

#define FRONTSPRITEMAX		0x40

struct FrontSprite
{
	hgeSprite * sprite;
	float x;
	float y;
	float rot;
	float hscale;
	float vscale;
	DWORD col;
	int blend;
	int fadeoutmaxtime;
	int fadeouttimer;
};

#if defined __IPHONE

#define FRONTTOUCH_HIDDEN	0x00
#define FRONTTOUCH_NORMAL	0x01
#define FRONTTOUCH_TOUCHED	0x02

#define FTBUTTON_LEFT	0
#define FTBUTTON_RIGHT	1
#define FTBUTTON_UP		2
#define FTBUTTON_DOWN	3
#define FTBUTTON_OK		4
#define FTBUTTON_CANCEL	5
#define FTBUTTON_PAUSE	6
#define FTBUTTON_SHOOT	7
#define FTBUTTON_CHARGE	8
#define FTBUTTON_DRAIN	9
#define FTBUTTON_QUICK	10

#define FTBUTTON_MAX	11

struct FrontTouchButton {
	hgeSprite * sprite;
	float x;
	float y;
	float xrange;
	float yrange;
	BYTE flag;
};

#endif

class SpriteItemManager
{
public:
	SpriteItemManager();
	~SpriteItemManager();

	static void Init();
	static void Release();
	static hgeSprite * CreateSprite(int index);
	static bool CreateSprite(int index, hgeSprite ** sprite);
	static bool ChangeSprite(int index, hgeSprite * sprite);
	static int GetIndexByName(const char * spritename);
	static hgeSprite * CreateSpriteByName(const char * spritename);
	static bool CreateSpriteByName(const char * spritename, hgeSprite ** sprite);
	static void FreeSprite(hgeSprite ** sprite);
	static spriteData * CastSprite(int index);

	static hgeSprite * CreateNullSprite();
	static bool SetSpriteData(hgeSprite * sprite, HTEXTURE tex, float texx, float texy, float texw, float texh, bool flipx=false, bool flipy=false);
	static bool SetSpriteTextureRect(hgeSprite * sprite, float texx, float texy, float texw, float texh);
	static bool SetSpriteFlip(hgeSprite * sprite, bool flipx=false, bool flipy=false);
	static bool SetSpriteHotSpot(hgeSprite * sprite, float hotx, float hoty);

	static bool HaveFrontSprite(int ID);
	static void ClearFrontSpriteVale(int ID);
	static hgeSprite * ChangeFrontSprite(int ID, int index);
	static hgeSprite * BuildFrontSprite(int ID, int index);
	static hgeSprite * BuildFrontSpriteByName(int ID, const char * spritename);
	static void SetFrontSpriteValue(int ID, float x, float y, int angle=0, float hscale=1.0f, float vscale=0.0f, DWORD col=0xffffffff, int blend=BLEND_DEFAULT);
	static void SetFrontSpriteFadeoutTime(int ID, int fadeouttime);
	static void FrontSpriteAction();
	static void FreeFrontSprite(int ID=-1);
	static void RenderFrontSprite();

	static bool SetSprite(int index, hgeSprite * sprite);

	static HTEXTURE GetTexture(int index);
	static float GetTexX(int index);
	static float GetTexY(int index);
	static float GetTexW(int index);
	static float GetTexH(int index);

	static bool ptFace(int index, hgeSprite * sprite);

	static bool LoadTextureWhenNeeded(HTEXTURE tex);
	static bool LoadTextureWhenNeededCallBack();

	static void RenderSprite(hgeSprite * sprite, float x, float y);
	static void RenderSpriteEx(hgeSprite * sprite, float x, float y, float rot, float hscale=1.0f, float vscale=0.0f);
	static void FontPrintf(hgeFont * font, float x, float y, int align, const char * str);
	static void FontPrintfb(hgeFont * font, float x, float y, float w, float h, int align, const char * str);
	static void EffectSystemRender(hgeEffectSystem * eff, hge3DPoint *ptfar=NULL, DWORD colormask=0xffffffff);
	static void RenderQuad(hgeQuad * quad);

public:
	static int yesIndex;
	static int noIndex;
	static int cancelIndex;
	static int confirmIndex;
	static int nullIndex;

	static FrontSprite frontsprite[FRONTSPRITEMAX];
	
#if defined __IPHONE
public:
	static void InitFrontTouchButton();
	static void ReleaseFrontTouchButton();
	static void RenderFrontTouchButton();
	static FrontTouchButton * GetFrontTouchButton(BYTE playerindex, BYTE buttontype);
	static void FrontTouchButtonHide();
	static FrontTouchButton ftbutton[M_PL_MATCHMAXPLAYER][FTBUTTON_MAX];
#endif
};

#endif