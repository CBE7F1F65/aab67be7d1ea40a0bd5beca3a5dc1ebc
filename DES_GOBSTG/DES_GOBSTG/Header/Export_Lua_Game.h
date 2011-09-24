#ifndef __NOTUSELUA
#ifndef __NOTINTHISGAME

#ifndef _EXPORT_LUA_GAME_H
#define _EXPORT_LUA_GAME_H

#include "Export_Lua.h"

class Export_Lua_Game : Export_Lua
{
public:
	static bool _LuaRegistConst(LuaObject * obj);
	static bool _LuaRegistFunction(LuaObject * obj);

	static int LuaFn_Game_Random_Int(LuaState * ls);
	static int LuaFn_Game_Random_Float(LuaState * ls);
	static int LuaFn_Game_SetLastIP(LuaState * ls);
	static int LuaFn_Game_GetLastIP(LuaState * ls);
	static int LuaFn_Game_AccessIP(LuaState * ls);
	static int LuaFn_Game_SetLatency(LuaState * ls);
	static int LuaFn_Game_SetMatchMode(LuaState * ls);
	static int LuaFn_Game_GetMatchMode(LuaState * ls);
	static int LuaFn_Game_GetPlayerContentTable(LuaState * ls);
	static int LuaFn_Game_GetSceneContentTable(LuaState * ls);
	static int LuaFn_Game_GetSendItemInfo(LuaState * ls);
	static int LuaFn_Game_AddSendBulletInfo(LuaState * ls);
	static int LuaFn_Game_AddSendGhostInfo(LuaState * ls);
	static int LuaFn_Game_GetPlayerDrainInfo(LuaState * ls);
	static int LuaFn_Game_SetPlayerDrainSpriteInfo(LuaState * ls);
	static int LuaFn_Game_GetPlayerShotInfo(LuaState * ls);
	static int LuaFn_Game_SetGhostActiveInfo(LuaState * ls);
	static int LuaFn_Game_GetPlayerSendExInfo(LuaState * ls);
	static int LuaFn_Game_PlayerSendEx(LuaState * ls);
	static int LuaFn_Game_GetPlayerStopInfo(LuaState * ls);
	static int LuaFn_Game_GetEnumReplayInfo(LuaState * ls);
	static int LuaFn_Game_SetEnumReplayByIndex(LuaState * ls);
	static int LuaFn_Game_GetPlayerShootChargeInfo(LuaState * ls);
	static int LuaFn_Game_GetPlayerShootChargeOneInfo(LuaState * ls);
	static int LuaFn_Game_GetEdefInfo(LuaState * ls);
	static int LuaFn_Game_SendItemBullet(LuaState * ls);
	static int LuaFn_Game_GetPlayerMoveInfo(LuaState * ls);
	static int LuaFn_Game_SetPerfectFreezeParam(LuaState * ls);
	static int LuaFn_Game_GetOneMatchOverInfo(LuaState * ls);
	static int LuaFn_Game_LoadTexture(LuaState * ls);
	static int LuaFn_Game_FreeTexture(LuaState * ls);
};

#endif
#endif

#endif