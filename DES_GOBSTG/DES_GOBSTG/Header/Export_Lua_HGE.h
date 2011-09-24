#ifndef __NOTUSELUA

#ifndef _EXPORT_LUA_HGE_H
#define _EXPORT_LUA_HGE_H

#include "Export_Lua.h"

class Export_Lua_HGE : public Export_Lua
{
public:

	static bool _LuaRegistFunction(LuaObject * obj);
	static bool _LuaRegistConst(LuaObject * obj);

	/* HGE */
	static void _LuaHelper_GetVertex(LuaObject * obj, hgeVertex * vertex);
	static void _LuaHelper_GetTriple(LuaObject * obj, hgeTriple * triple);
	static void _LuaHelper_GetQuad(LuaObject * obj, hgeQuad * quad);

	static int LuaFn_hge_Struct_hgeQuad(LuaState * ls);

	static int LuaFn_hge_System_SetState(LuaState * ls);
	static int LuaFn_hge_System_GetState(LuaState * ls);
	static int LuaFn_hge_System_Log(LuaState * ls);

	static int LuaFn_hge_System_GetErrorMessage(LuaState * ls);
	static int LuaFn_hge_System_Launch(LuaState * ls);
	static int LuaFn_hge_System_Snapshot(LuaState * ls);

	static int LuaFn_hge_System_Transform3DPoint(LuaState * ls);

	static int LuaFn_hge_Resource_Load(LuaState * ls);
	static int LuaFn_hge_Resource_Free(LuaState * ls);
	static int LuaFn_hge_Resource_AttachPack(LuaState * ls);
	static int LuaFn_hge_Resource_RemovePack(LuaState * ls);
	static int LuaFn_hge_Resource_SetPath(LuaState * ls);
	static int LuaFn_hge_Resource_MakePath(LuaState * ls);
	static int LuaFn_hge_Resource_EnumFiles(LuaState * ls);
	static int LuaFn_hge_Resource_EnumFolders(LuaState * ls);
	static int LuaFn_hge_Resource_CreatePack(LuaState * ls);
	static int LuaFn_hge_Resource_AddFileInPack(LuaState * ls);
	static int LuaFn_hge_Resource_GetCRC(LuaState * ls);
	static int LuaFn_hge_Resource_GetPackFirstFileName(LuaState * ls);

	static int LuaFn_hge_Ini_SetInt(LuaState * ls);
	static int LuaFn_hge_Ini_GetInt(LuaState * ls);
	static int LuaFn_hge_Ini_SetFloat(LuaState * ls);
	static int LuaFn_hge_Ini_GetFloat(LuaState * ls);
	static int LuaFn_hge_Ini_SetString(LuaState * ls);
	static int LuaFn_hge_Ini_GetString(LuaState * ls);

	static int LuaFn_hge_Random_Seed(LuaState * ls);
	static int LuaFn_hge_Random_Int(LuaState * ls);
	static int LuaFn_hge_Random_Float(LuaState * ls);

	static int LuaFn_hge_Timer_GetTime(LuaState * ls);
	static int LuaFn_hge_Timer_GetDelta(LuaState * ls);
	static int LuaFn_hge_Timer_GetFPS(LuaState * ls);
	static int LuaFn_hge_Timer_GetWorstFPS(LuaState * ls);
	static int LuaFn_hge_Timer_GetCurrentSystemTime(LuaState * ls);

	static int LuaFn_hge_Effect_Load(LuaState * ls);
	static int LuaFn_hge_Effect_Free(LuaState * ls);
	static int LuaFn_hge_Effect_Play(LuaState * ls);

	static int LuaFn_hge_Stream_Load(LuaState * ls);
	static int LuaFn_hge_Stream_Free(LuaState * ls);
	static int LuaFn_hge_Stream_Play(LuaState * ls);

	static int LuaFn_hge_Channel_SetPanning(LuaState * ls);
	static int LuaFn_hge_Channel_SetVolume(LuaState * ls);
	static int LuaFn_hge_Channel_SetPitch(LuaState * ls);
	static int LuaFn_hge_Channel_Pause(LuaState * ls);
	static int LuaFn_hge_Channel_Resume(LuaState * ls);
	static int LuaFn_hge_Channel_Stop(LuaState * ls);
	static int LuaFn_hge_Channel_IsPlaying(LuaState * ls);
	static int LuaFn_hge_Channel_GetLength(LuaState * ls);
	static int LuaFn_hge_Channel_GetPos(LuaState * ls);
	static int LuaFn_hge_Channel_SetPos(LuaState * ls);
	static int LuaFn_hge_Channel_SetStartPos(LuaState * ls);
	static int LuaFn_hge_Channel_SlideTo(LuaState * ls);
	static int LuaFn_hge_Channel_IsSliding(LuaState * ls);
	static int LuaFn_hge_Channel_SetLoop(LuaState * ls);
	static int LuaFn_hge_Channel_RemoveLoop(LuaState * ls);

	static int LuaFn_hge_Input_GetMousePos(LuaState * ls);
	static int LuaFn_hge_Input_SetMousePos(LuaState * ls);
	static int LuaFn_hge_Input_GetMouseWheel(LuaState * ls);
	static int LuaFn_hge_Input_IsMouseOver(LuaState * ls);
	static int LuaFn_hge_Input_KeyDown(LuaState * ls);
	static int LuaFn_hge_Input_KeyUp(LuaState * ls);
	static int LuaFn_hge_Input_GetKeyState(LuaState * ls);
	static int LuaFn_hge_Input_GetKeyName(LuaState * ls);
	static int LuaFn_hge_Input_GetKey(LuaState * ls);
	static int LuaFn_hge_Input_GetChar(LuaState * ls);
	static int LuaFn_hge_Input_GetEvent(LuaState * ls);

	static int LuaFn_hge_Input_GetDIKey(LuaState * ls);
	static int LuaFn_hge_Input_SetDIKey(LuaState * ls);
	static int LuaFn_hge_Input_GetDIJoy(LuaState * ls);
	static int LuaFn_hge_Input_HaveJoy(LuaState * ls);

	static int LuaFn_hge_Gfx_BeginScene(LuaState * ls);
	static int LuaFn_hge_Gfx_EndScene(LuaState * ls);
	static int LuaFn_hge_Gfx_Clear(LuaState * ls);
	static int LuaFn_hge_Gfx_RenderLine(LuaState * ls);
	static int LuaFn_hge_Gfx_RenderTriple(LuaState * ls);
	static int LuaFn_hge_Gfx_RenderQuad(LuaState * ls);
	static int LuaFn_hge_Gfx_StartBatch(LuaState * ls);
	static int LuaFn_hge_Gfx_FinishBatch(LuaState * ls);
	static int LuaFn_hge_Gfx_SetClipping(LuaState * ls);
	static int LuaFn_hge_Gfx_SetTransform(LuaState * ls);

	static int LuaFn_hge_Target_Create(LuaState * ls);
	static int LuaFn_hge_Target_Free(LuaState * ls);
	static int LuaFn_hge_Target_GetTexture(LuaState * ls);

	static int LuaFn_hge_Texture_Create(LuaState * ls);
	static int LuaFn_hge_Texture_Load(LuaState * ls);
	static int LuaFn_hge_Texture_Free(LuaState * ls);
	static int LuaFn_hge_Texture_GetWH(LuaState * ls);
	static int LuaFn_hge_Texture_Lock(LuaState * ls);
	static int LuaFn_hge_Texture_Unlock(LuaState * ls);

	static int LuaFn_hge_Font_Load(LuaState * ls);
	static int LuaFn_hge_Font_Free(LuaState * ls);
	static int LuaFn_hge_Gfx_RenderText(LuaState * ls);
	static int LuaFn_hge_Gfx_RenderTextToTarget(LuaState * ls);

public:
	static hgeChannelSyncInfo channelsyncinfo;
};

#endif
#endif
