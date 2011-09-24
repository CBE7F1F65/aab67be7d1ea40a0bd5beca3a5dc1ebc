#ifndef __NOTUSELUA

#ifndef _EXPORT_LUA_HGEHELP_H
#define _EXPORT_LUA_HGEHELP_H

#include "Export_Lua.h"

class Export_Lua_HGEHelp : public Export_Lua
{
public:
	static bool _LuaRegistFunction(LuaObject * obj);
	static bool _LuaRegistConst(LuaObject * obj);

	static hgeFont * _Helper_New_hgeFont();
	static hgeFont * _Helper_New_hgeFont(const char * filename, bool bMipmap=false);
	static hgeSprite * _Helper_New_hgeSprite();
	static hgeSprite * _Helper_New_hgeSprite(HTEXTURE tex, float x, float y, float w, float h);
	static hgeSprite * _Helper_New_hgeSprite(const hgeSprite & spr);
	static hgeEffectSystem * _Helper_New_hgeES();
	static hgeEffectSystem * _Helper_New_hgeES(const char * filename, HTEXTURE tex = 0);
	static hgeEffectSystem * _Helper_New_hgeES(const hgeEffectSystem & eff);

	// Font
	static hgeFont * _LuaHelper_hgeFont_Get(LuaStack * args);
	static void _LuaHelper_hgeFont_DeleteFont(hgeFont * _font);
	static void _LuaHelper_hgeFont_DeleteAllFont();
	static int LuaFn_hgeFont_NewFont(LuaState * ls);
	static int LuaFn_hgeFont_DeleteFont(LuaState * ls);

	static int LuaFn_hgeFont_Render(LuaState * ls);
	static int LuaFn_hgeFont_printfb(LuaState * ls);

	static int LuaFn_hgeFont_SetColor(LuaState * ls);
	static int LuaFn_hgeFont_SetZ(LuaState * ls);
	static int LuaFn_hgeFont_SetBlendMode(LuaState * ls);
	static int LuaFn_hgeFont_SetScale(LuaState * ls);
	static int LuaFn_hgeFont_SetProportion(LuaState * ls);
	static int LuaFn_hgeFont_SetRotation(LuaState * ls);
	static int LuaFn_hgeFont_SetTracking(LuaState * ls);
	static int LuaFn_hgeFont_SetSpacing(LuaState * ls);

	static int LuaFn_hgeFont_GetColor(LuaState * ls);
	static int LuaFn_hgeFont_GetZ(LuaState * ls);
	static int LuaFn_hgeFont_GetBlendMode(LuaState * ls);
	static int LuaFn_hgeFont_GetScale(LuaState * ls);
	static int LuaFn_hgeFont_GetProportion(LuaState * ls);
	static int LuaFn_hgeFont_GetRotation(LuaState * ls);
	static int LuaFn_hgeFont_GetTracking(LuaState * ls);
	static int LuaFn_hgeFont_GetSpacing(LuaState * ls);

	static int LuaFn_hgeFont_ChangeSprite(LuaState * ls);
	static int LuaFn_hgeFont_GetSprite(LuaState * ls);
	static int LuaFn_hgeFont_GetPreWidth(LuaState * ls);
	static int LuaFn_hgeFont_GetPostWidth(LuaState * ls);
	static int LuaFn_hgeFont_GetHeight(LuaState * ls);
	static int LuaFn_hgeFont_GetStringWidth(LuaState * ls);


	// Sprite
	static hgeSprite * _LuaHelper_hgeSprite_Get(LuaStack * args);
	static void _LuaHelper_hgeSprite_DeleteSprite(hgeSprite * _sprite);
	static void _LuaHelper_hgeSprite_DeleteAllSprite();
	static int LuaFn_hgeSprite_NewSprite(LuaState * ls);
	static int LuaFn_hgeSprite_DeleteSprite(LuaState * ls);

	static int LuaFn_hgeSprite_Render(LuaState * ls);
	static int LuaFn_hgeSprite_RenderStretch(LuaState * ls);
	static int LuaFn_hgeSprite_Render4V(LuaState * ls);

	static int LuaFn_hgeSprite_SetTexture(LuaState * ls);
	static int LuaFn_hgeSprite_SetTextureRect(LuaState * ls);
	static int LuaFn_hgeSprite_SetColor(LuaState * ls);
	static int LuaFn_hgeSprite_SetZ(LuaState * ls);
	static int LuaFn_hgeSprite_SetBlendMode(LuaState * ls);
	static int LuaFn_hgeSprite_SetHotSpot(LuaState * ls);
	static int LuaFn_hgeSprite_SetFlip(LuaState * ls);

	static int LuaFn_hgeSprite_GetTexture(LuaState * ls);
	static int LuaFn_hgeSprite_GetTextureRect(LuaState * ls);
	static int LuaFn_hgeSprite_GetColor(LuaState * ls);
	static int LuaFn_hgeSprite_GetZ(LuaState * ls);
	static int LuaFn_hgeSprite_GetBlendMode(LuaState * ls);
	static int LuaFn_hgeSprite_GetHotSpot(LuaState * ls);
	static int LuaFn_hgeSprite_GetFlip(LuaState * ls);

	static int LuaFn_hgeSprite_GetWidth(LuaState * ls);
	static int LuaFn_hgeSprite_GetHeight(LuaState * ls);
	static int LuaFn_hgeSprite_GetBoundingBox(LuaState * ls);


	// EffectSystem
	static hgeEffectSystem * _LuaHelper_hgeES_Get(LuaStack * args);
	static void _LuaHelper_hgeES_DeleteES(hgeEffectSystem * _es);
	static void _LuaHelper_hgeES_DeleteAllES();
	static int LuaFn_hgeES_NewES(LuaState * ls);
	static int LuaFn_hgeES_DeleteES(LuaState * ls);

	static int LuaFn_hgeES_Load(LuaState * ls);
	static int LuaFn_hgeES_Save(LuaState * ls);

	static int LuaFn_hgeES_Render(LuaState * ls);
	static int LuaFn_hgeES_MoveTo(LuaState * ls);
	static int LuaFn_hgeES_Fire(LuaState * ls);
	static int LuaFn_hgeES_Stop(LuaState * ls);
	static int LuaFn_hgeES_Update(LuaState * ls);

public:
	static list<hgeFont *>fontList;
	static list<hgeSprite *>spriteList;
	static list<hgeEffectSystem *>esList;
};

#endif
#endif