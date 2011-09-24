#ifndef __NOTUSELUA

#include "../Header/Export_Lua_HGE.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/Export.h"
#include "../Header/SpriteItemManager.h"

hgeChannelSyncInfo Export_Lua_HGE::channelsyncinfo;

bool Export_Lua_HGE::_LuaRegistFunction(LuaObject * obj)
{
	LuaObject _hgeobj = obj->CreateTable("hge");

	_hgeobj.Register("System_SetState", LuaFn_hge_System_SetState);
	_hgeobj.Register("System_GetState", LuaFn_hge_System_GetState);
	_hgeobj.Register("System_Log", LuaFn_hge_System_Log);

	_hgeobj.Register("System_GetErrorMessage", LuaFn_hge_System_GetErrorMessage);
	_hgeobj.Register("System_Launch", LuaFn_hge_System_Launch);
	_hgeobj.Register("System_Snapshot", LuaFn_hge_System_Snapshot);

	_hgeobj.Register("System_Transform3DPoint", LuaFn_hge_System_Transform3DPoint);

	_hgeobj.Register("Resource_Load", LuaFn_hge_Resource_Load);
	_hgeobj.Register("Resource_Free", LuaFn_hge_Resource_Free);
	_hgeobj.Register("Resource_AttachPack", LuaFn_hge_Resource_AttachPack);
	_hgeobj.Register("Resource_RemovePack", LuaFn_hge_Resource_RemovePack);
	_hgeobj.Register("Resource_RemoveAllPacks", LuaFn_hge_Resource_RemovePack);
	_hgeobj.Register("Resource_SetPath", LuaFn_hge_Resource_SetPath);
	_hgeobj.Register("Resource_MakePath", LuaFn_hge_Resource_MakePath);
	_hgeobj.Register("Resource_EnumFiles", LuaFn_hge_Resource_EnumFiles);
	_hgeobj.Register("Resource_EnumFolders", LuaFn_hge_Resource_EnumFolders);
	_hgeobj.Register("Resource_CreatePack", LuaFn_hge_Resource_CreatePack);
	_hgeobj.Register("Resource_AddFileInPack", LuaFn_hge_Resource_AddFileInPack);
	_hgeobj.Register("Resource_GetCRC", LuaFn_hge_Resource_GetCRC);
	_hgeobj.Register("Resource_GetPackFirstFileName", LuaFn_hge_Resource_GetPackFirstFileName);

	_hgeobj.Register("Ini_SetInt", LuaFn_hge_Ini_SetInt);
	_hgeobj.Register("Ini_GetInt", LuaFn_hge_Ini_GetInt);
	_hgeobj.Register("Ini_SetFloat", LuaFn_hge_Ini_SetFloat);
	_hgeobj.Register("Ini_GetFloat", LuaFn_hge_Ini_GetFloat);
	_hgeobj.Register("Ini_SetString", LuaFn_hge_Ini_SetString);
	_hgeobj.Register("Ini_GetString", LuaFn_hge_Ini_GetString);

	_hgeobj.Register("Random_Seed", LuaFn_hge_Random_Seed);
	_hgeobj.Register("Random_Int", LuaFn_hge_Random_Int);
	_hgeobj.Register("Random_Float", LuaFn_hge_Random_Float);

	_hgeobj.Register("Timer_GetTime", LuaFn_hge_Timer_GetTime);
	_hgeobj.Register("Timer_GetDelta", LuaFn_hge_Timer_GetDelta);
	_hgeobj.Register("Timer_GetFPS", LuaFn_hge_Timer_GetFPS);
	_hgeobj.Register("Timer_GetWorstFPS", LuaFn_hge_Timer_GetWorstFPS);
	_hgeobj.Register("Timer_GetCurrentSystemTime", LuaFn_hge_Timer_GetCurrentSystemTime);

	_hgeobj.Register("Effect_Load", LuaFn_hge_Effect_Load);
	_hgeobj.Register("Effect_Free", LuaFn_hge_Effect_Free);
	_hgeobj.Register("Effect_Play", LuaFn_hge_Effect_Play);
	_hgeobj.Register("Effect_PlayEx", LuaFn_hge_Effect_Play);

	_hgeobj.Register("Stream_Load", LuaFn_hge_Stream_Load);
	_hgeobj.Register("Stream_Free", LuaFn_hge_Stream_Free);
	_hgeobj.Register("Stream_Play", LuaFn_hge_Stream_Play);

	_hgeobj.Register("Channel_SetPanning", LuaFn_hge_Channel_SetPanning);
	_hgeobj.Register("Channel_SetVolume", LuaFn_hge_Channel_SetVolume);
	_hgeobj.Register("Channel_SetPitch", LuaFn_hge_Channel_SetPitch);
	_hgeobj.Register("Channel_Pause", LuaFn_hge_Channel_Pause);
	_hgeobj.Register("Channel_Resume", LuaFn_hge_Channel_Resume);
	_hgeobj.Register("Channel_Stop", LuaFn_hge_Channel_Stop);
	_hgeobj.Register("Channel_PauseAll", LuaFn_hge_Channel_Pause);
	_hgeobj.Register("Channel_ResumeAll", LuaFn_hge_Channel_Resume);
	_hgeobj.Register("Channel_StopAll", LuaFn_hge_Channel_Stop);
	_hgeobj.Register("Channel_IsPlaying", LuaFn_hge_Channel_IsPlaying);
	_hgeobj.Register("Channel_GetLength", LuaFn_hge_Channel_GetLength);
	_hgeobj.Register("Channel_GetPos", LuaFn_hge_Channel_GetPos);
	_hgeobj.Register("Channel_SetPos", LuaFn_hge_Channel_SetPos);
	_hgeobj.Register("Channel_SetStartPos", LuaFn_hge_Channel_SetStartPos);
	_hgeobj.Register("Channel_SlideTo", LuaFn_hge_Channel_SlideTo);
	_hgeobj.Register("Channel_IsSliding", LuaFn_hge_Channel_IsSliding);
	_hgeobj.Register("Channel_SetLoop", LuaFn_hge_Channel_SetLoop);
	_hgeobj.Register("Channel_RemoveLoop", LuaFn_hge_Channel_RemoveLoop);

	_hgeobj.Register("Input_GetMousePos", LuaFn_hge_Input_GetMousePos);
	_hgeobj.Register("Input_SetMousePos", LuaFn_hge_Input_SetMousePos);
	_hgeobj.Register("Input_GetMouseWheel", LuaFn_hge_Input_GetMouseWheel);
	_hgeobj.Register("Input_IsMouseOver", LuaFn_hge_Input_IsMouseOver);
	_hgeobj.Register("Input_KeyDown", LuaFn_hge_Input_KeyDown);
	_hgeobj.Register("Input_KeyUp", LuaFn_hge_Input_KeyUp);
	_hgeobj.Register("Input_GetKeyState", LuaFn_hge_Input_GetKeyState);
	_hgeobj.Register("Input_GetKeyName", LuaFn_hge_Input_GetKeyName);
	_hgeobj.Register("Input_GetKey", LuaFn_hge_Input_GetKey);
	_hgeobj.Register("Input_GetChar", LuaFn_hge_Input_GetChar);
	_hgeobj.Register("Input_GetEvent", LuaFn_hge_Input_GetEvent);

	_hgeobj.Register("Input_GetDIKey", LuaFn_hge_Input_GetDIKey);
	_hgeobj.Register("Input_SetDIKey", LuaFn_hge_Input_SetDIKey);
	_hgeobj.Register("Input_GetDIJoy", LuaFn_hge_Input_GetDIJoy);
	_hgeobj.Register("Input_HaveJoy", LuaFn_hge_Input_HaveJoy);

	_hgeobj.Register("Gfx_BeginScene", LuaFn_hge_Gfx_BeginScene);
	_hgeobj.Register("Gfx_EndScene", LuaFn_hge_Gfx_EndScene);
	_hgeobj.Register("Gfx_Clear", LuaFn_hge_Gfx_Clear);
	_hgeobj.Register("Gfx_RenderLine", LuaFn_hge_Gfx_RenderLine);
	_hgeobj.Register("Gfx_RenderTriple", LuaFn_hge_Gfx_RenderTriple);
	_hgeobj.Register("Gfx_RenderQuad", LuaFn_hge_Gfx_RenderQuad);
	_hgeobj.Register("Gfx_StartBatch", LuaFn_hge_Gfx_StartBatch);
	_hgeobj.Register("Gfx_FinishBatch", LuaFn_hge_Gfx_FinishBatch);
	_hgeobj.Register("Gfx_SetClipping", LuaFn_hge_Gfx_SetClipping);
	_hgeobj.Register("Gfx_SetTransform", LuaFn_hge_Gfx_SetTransform);

	_hgeobj.Register("Target_Create", LuaFn_hge_Target_Create);
	_hgeobj.Register("Target_Free", LuaFn_hge_Target_Free);
	_hgeobj.Register("Target_GetTexture", LuaFn_hge_Target_GetTexture);

	_hgeobj.Register("Texture_Create", LuaFn_hge_Texture_Create);
	_hgeobj.Register("Texture_Load", LuaFn_hge_Texture_Load);
	_hgeobj.Register("Texture_Free", LuaFn_hge_Texture_Free);
	_hgeobj.Register("Texture_GetWH", LuaFn_hge_Texture_GetWH);
	_hgeobj.Register("Texture_Lock", LuaFn_hge_Texture_Lock);
	_hgeobj.Register("Texture_Unlock", LuaFn_hge_Texture_Unlock);

	_hgeobj.Register("Font_Load", LuaFn_hge_Font_Load);
	_hgeobj.Register("Font_Free", LuaFn_hge_Font_Free);
	_hgeobj.Register("Gfx_RenderText", LuaFn_hge_Gfx_RenderText);
	_hgeobj.Register("Gfx_RenderTextToTarget", LuaFn_hge_Gfx_RenderTextToTarget);

	LuaObject _hgestructobj = _hgeobj.CreateTable("struct");

	_hgestructobj.Register("hgeQuad", LuaFn_hge_Struct_hgeQuad);

	return true;
}

bool Export_Lua_HGE::_LuaRegistConst(LuaObject * obj)
{
	// Math
	obj->SetNumber("M_PI", M_PI);
	obj->SetNumber("M_PI_2", M_PI_2);
	obj->SetNumber("M_PI_4", M_PI_4);
	obj->SetNumber("M_1_PI", M_1_PI);
	obj->SetNumber("M_2_PI", M_2_PI);

	obj->SetNumber("M_E", M_E);
	obj->SetNumber("M_LOG2E", M_LOG2E);
	obj->SetNumber("M_LOG10E", M_LOG10E);
	obj->SetNumber("M_LN2", M_LN2);
	obj->SetNumber("M_LN10", M_LN10);
	obj->SetNumber("M_PI", M_PI);
	obj->SetNumber("M_PI_2", M_PI_2);
	obj->SetNumber("M_PI_4", M_PI_4);
	obj->SetNumber("M_1_PI", M_1_PI);
	obj->SetNumber("M_2_PI", M_2_PI);
	obj->SetNumber("M_2_SQRTPI", M_2_SQRTPI);
	obj->SetNumber("M_SQRT2", M_SQRT2);
	obj->SetNumber("M_SQRT1_2", M_SQRT1_2);

	// Blend
	obj->SetInteger("BLEND_COLORADD", BLEND_COLORADD);
	obj->SetInteger("BLEND_COLORMUL", BLEND_COLORMUL);
	obj->SetInteger("BLEND_ALPHABLEND", BLEND_ALPHABLEND);
	obj->SetInteger("BLEND_ALPHAADD", BLEND_ALPHAADD);
	obj->SetInteger("BLEND_ZWRITE", BLEND_ZWRITE);
	obj->SetInteger("BLEND_NOZWRITE", BLEND_NOZWRITE);

	obj->SetInteger("BLEND_DEFAULT", BLEND_DEFAULT);
	obj->SetInteger("BLEND_DEFAULT_Z", BLEND_DEFAULT_Z);

	// hgeState
	obj->SetInteger("HGE_WINDOWED", HGE_WINDOWED);
	obj->SetInteger("HGE_ZBUFFER", HGE_ZBUFFER);
	obj->SetInteger("HGE_TEXTUREFILTER", HGE_TEXTUREFILTER);

	obj->SetInteger("HGE_USESOUND", HGE_USESOUND);

	obj->SetInteger("HGE_DONTSUSPEND", HGE_DONTSUSPEND);
	obj->SetInteger("HGE_HIDEMOUSE", HGE_HIDEMOUSE);

	obj->SetInteger("HGE_3DMODE", HGE_2DMODE);

	obj->SetInteger("HGE_HWND", HGE_HWND);
	obj->SetInteger("HGE_HWNDPARENT", HGE_HWNDPARENT);
	obj->SetInteger("HGE_SCREENWIDTH", HGE_SCREENWIDTH);
	obj->SetInteger("HGE_SCREENHEIGHT", HGE_SCREENHEIGHT);
	obj->SetInteger("HGE_SCREENBPP", HGE_SCREENBPP);

	obj->SetInteger("HGE_SAMPLERATE", HGE_SAMPLERATE);
	obj->SetInteger("HGE_SAMPLEVOLUME", HGE_SAMPLEVOLUME);
	obj->SetInteger("HGE_FXVOLUME", HGE_FXVOLUME);
	obj->SetInteger("HGE_STREAMVOLUME", HGE_STREAMVOLUME);
	obj->SetInteger("HGE_FPS", HGE_FPS);

	obj->SetInteger("HGE_FRAMECOUNTER", HGE_FRAMECOUNTER);
	obj->SetInteger("HGE_FRAMESKIP", HGE_FRAMESKIP);
	obj->SetInteger("HGE_RENDERSKIP", HGE_RENDERSKIP);

	obj->SetInteger("HGE_ICON", HGE_ICON);
	obj->SetInteger("HGE_TITLE", HGE_TITLE);

	obj->SetInteger("HGE_INIFILE", HGE_INIFILE);
	obj->SetInteger("HGE_LOGFILE", HGE_LOGFILE);

	obj->SetInteger("HGE_BASSDLLFILE", HGE_BASSDLLFILE);

	// Input
	obj->SetInteger("INPUT_KEYDOWN", INPUT_KEYDOWN);
	obj->SetInteger("INPUT_KEYUP", INPUT_KEYUP);
	obj->SetInteger("INPUT_MBUTTONDOWN", INPUT_MBUTTONDOWN);
	obj->SetInteger("INPUT_MBUTTONUP", INPUT_MBUTTONUP);
	obj->SetInteger("INPUT_MOUSEMOVE", INPUT_MOUSEMOVE);
	obj->SetInteger("INPUT_MOUSEWHEEL", INPUT_MOUSEWHEEL);

	obj->SetInteger("HGEINP_SHIFT", HGEINP_SHIFT);
	obj->SetInteger("HGEINP_CTRL", HGEINP_CTRL);
	obj->SetInteger("HGEINP_ALT", HGEINP_ALT);
	obj->SetInteger("HGEINP_CAPSLOCK", HGEINP_CAPSLOCK);
	obj->SetInteger("HGEINP_SCROLLLOCK", HGEINP_SCROLLLOCK);
	obj->SetInteger("HGEINP_NUMLOCK", HGEINP_NUMLOCK);
	obj->SetInteger("HGEINP_REPEAT", HGEINP_REPEAT);

	obj->SetInteger("HGEK_LBUTTON", HGEK_LBUTTON);
	obj->SetInteger("HGEK_RBUTTON", HGEK_RBUTTON);
	obj->SetInteger("HGEK_MBUTTON", HGEK_MBUTTON);

	obj->SetInteger("HGEK_ESCAPE", HGEK_ESCAPE);
	obj->SetInteger("HGEK_BACKSPACE", HGEK_BACKSPACE);
	obj->SetInteger("HGEK_TAB", HGEK_TAB);
	obj->SetInteger("HGEK_ENTER", HGEK_ENTER);
	obj->SetInteger("HGEK_SPACE", HGEK_SPACE);

	obj->SetInteger("HGEK_SHIFT", HGEK_SHIFT);
	obj->SetInteger("HGEK_CTRL", HGEK_CTRL);
	obj->SetInteger("HGEK_ALT", HGEK_ALT);

	obj->SetInteger("HGEK_LWIN", HGEK_LWIN);
	obj->SetInteger("HGEK_RWIN", HGEK_RWIN);
	obj->SetInteger("HGEK_APPS", HGEK_APPS);

	obj->SetInteger("HGEK_PAUSE", HGEK_PAUSE);
	obj->SetInteger("HGEK_CAPSLOCK", HGEK_CAPSLOCK);
	obj->SetInteger("HGEK_NUMLOCK", HGEK_NUMLOCK);
	obj->SetInteger("HGEK_SCROLLLOCK", HGEK_SCROLLLOCK);

	obj->SetInteger("HGEK_PGUP", HGEK_PGUP);
	obj->SetInteger("HGEK_PGDN", HGEK_PGDN);
	obj->SetInteger("HGEK_HOME", HGEK_HOME);
	obj->SetInteger("HGEK_END", HGEK_END);
	obj->SetInteger("HGEK_INSERT", HGEK_INSERT);
	obj->SetInteger("HGEK_DELETE", HGEK_DELETE);

	obj->SetInteger("HGEK_LEFT", HGEK_LEFT);
	obj->SetInteger("HGEK_UP", HGEK_UP);
	obj->SetInteger("HGEK_RIGHT", HGEK_RIGHT);
	obj->SetInteger("HGEK_DOWN", HGEK_DOWN);

	obj->SetInteger("HGEK_0", HGEK_0);
	obj->SetInteger("HGEK_1", HGEK_1);
	obj->SetInteger("HGEK_2", HGEK_2);
	obj->SetInteger("HGEK_3", HGEK_3);
	obj->SetInteger("HGEK_4", HGEK_4);
	obj->SetInteger("HGEK_5", HGEK_5);
	obj->SetInteger("HGEK_6", HGEK_6);
	obj->SetInteger("HGEK_7", HGEK_7);
	obj->SetInteger("HGEK_8", HGEK_8);
	obj->SetInteger("HGEK_9", HGEK_9);

	obj->SetInteger("HGEK_A", HGEK_A);
	obj->SetInteger("HGEK_B", HGEK_B);
	obj->SetInteger("HGEK_C", HGEK_C);
	obj->SetInteger("HGEK_D", HGEK_D);
	obj->SetInteger("HGEK_E", HGEK_E);
	obj->SetInteger("HGEK_F", HGEK_F);
	obj->SetInteger("HGEK_G", HGEK_G);
	obj->SetInteger("HGEK_H", HGEK_H);
	obj->SetInteger("HGEK_I", HGEK_I);
	obj->SetInteger("HGEK_J", HGEK_J);
	obj->SetInteger("HGEK_K", HGEK_K);
	obj->SetInteger("HGEK_L", HGEK_L);
	obj->SetInteger("HGEK_M", HGEK_M);
	obj->SetInteger("HGEK_N", HGEK_N);
	obj->SetInteger("HGEK_O", HGEK_O);
	obj->SetInteger("HGEK_P", HGEK_P);
	obj->SetInteger("HGEK_Q", HGEK_Q);
	obj->SetInteger("HGEK_R", HGEK_R);
	obj->SetInteger("HGEK_S", HGEK_S);
	obj->SetInteger("HGEK_T", HGEK_T);
	obj->SetInteger("HGEK_U", HGEK_U);
	obj->SetInteger("HGEK_V", HGEK_V);
	obj->SetInteger("HGEK_W", HGEK_W);
	obj->SetInteger("HGEK_X", HGEK_X);
	obj->SetInteger("HGEK_Y", HGEK_Y);
	obj->SetInteger("HGEK_Z", HGEK_Z);

	obj->SetInteger("HGEK_GRAVE", HGEK_GRAVE);
	obj->SetInteger("HGEK_MINUS", HGEK_MINUS);
	obj->SetInteger("HGEK_EQUALS", HGEK_EQUALS);
	obj->SetInteger("HGEK_BACKSLASH", HGEK_BACKSLASH);
	obj->SetInteger("HGEK_LBRACKET", HGEK_LBRACKET);
	obj->SetInteger("HGEK_RBRACKET", HGEK_RBRACKET);
	obj->SetInteger("HGEK_SEMICOLON", HGEK_SEMICOLON);
	obj->SetInteger("HGEK_APOSTROPHE", HGEK_APOSTROPHE);
	obj->SetInteger("HGEK_COMMA", HGEK_COMMA);
	obj->SetInteger("HGEK_PERIOD", HGEK_PERIOD);
	obj->SetInteger("HGEK_SLASH", HGEK_SLASH);

	obj->SetInteger("HGEK_NUMPAD0", HGEK_NUMPAD0);
	obj->SetInteger("HGEK_NUMPAD1", HGEK_NUMPAD1);
	obj->SetInteger("HGEK_NUMPAD2", HGEK_NUMPAD2);
	obj->SetInteger("HGEK_NUMPAD3", HGEK_NUMPAD3);
	obj->SetInteger("HGEK_NUMPAD4", HGEK_NUMPAD4);
	obj->SetInteger("HGEK_NUMPAD5", HGEK_NUMPAD5);
	obj->SetInteger("HGEK_NUMPAD6", HGEK_NUMPAD6);
	obj->SetInteger("HGEK_NUMPAD7", HGEK_NUMPAD7);
	obj->SetInteger("HGEK_NUMPAD8", HGEK_NUMPAD8);
	obj->SetInteger("HGEK_NUMPAD9", HGEK_NUMPAD9);

	obj->SetInteger("HGEK_MULTIPLY", HGEK_MULTIPLY);
	obj->SetInteger("HGEK_DIVIDE", HGEK_DIVIDE);
	obj->SetInteger("HGEK_ADD", HGEK_ADD);
	obj->SetInteger("HGEK_SUBTRACT", HGEK_SUBTRACT);
	obj->SetInteger("HGEK_DECIMAL", HGEK_DECIMAL);

	obj->SetInteger("HGEK_F1", HGEK_F1);
	obj->SetInteger("HGEK_F2", HGEK_F2);
	obj->SetInteger("HGEK_F3", HGEK_F3);
	obj->SetInteger("HGEK_F4", HGEK_F4);
	obj->SetInteger("HGEK_F5", HGEK_F5);
	obj->SetInteger("HGEK_F6", HGEK_F6);
	obj->SetInteger("HGEK_F7", HGEK_F7);
	obj->SetInteger("HGEK_F8", HGEK_F8);
	obj->SetInteger("HGEK_F9", HGEK_F9);
	obj->SetInteger("HGEK_F10", HGEK_F10);
	obj->SetInteger("HGEK_F11", HGEK_F11);
	obj->SetInteger("HGEK_F12", HGEK_F12);

	// DI
	obj->SetInteger("DIKEY_PRESSED", DIKEY_PRESSED);
	obj->SetInteger("DIKEY_UP", DIKEY_UP);
	obj->SetInteger("DIKEY_DOWN", DIKEY_DOWN);

	obj->SetInteger("JOY_LEFT", JOY_LEFT);
	obj->SetInteger("JOY_RIGHT", JOY_RIGHT);
	obj->SetInteger("JOY_UP", JOY_UP);
	obj->SetInteger("JOY_DOWN", JOY_DOWN);

	return true;
}

void Export_Lua_HGE::_LuaHelper_GetVertex(LuaObject * obj, hgeVertex * vertex)
{
	if (obj->IsTable())
	{
		LuaObject _para;
		_para = obj->GetByName("col");
		if (_para.IsNumber() || _para.IsTable())
		{
			vertex->col = _LuaHelper_GetColor(&_para);
		}
		_para = obj->GetByName("tx");
		if (_para.IsNumber())
		{
			vertex->tx = _para.GetFloat();
		}
		_para = obj->GetByName("ty");
		if (_para.IsNumber())
		{
			vertex->ty = _para.GetFloat();
		}
		_para = obj->GetByName("x");
		if (_para.IsNumber())
		{
			vertex->x = _para.GetFloat();
		}
		_para = obj->GetByName("y");
		if (_para.IsNumber())
		{
			vertex->y = _para.GetFloat();
		}
		_para = obj->GetByName("z");
		if (_para.IsNumber())
		{
			vertex->z = _para.GetFloat();
		}
	}
}

void Export_Lua_HGE::_LuaHelper_GetTriple(LuaObject * obj, hgeTriple * triple)
{
	if (obj->IsTable())
	{
		LuaObject _para;
		_para = obj->GetByName("v");
		if (_para.IsTable())
		{
			LuaObject _ver;
			for (int i=0; i<HGEPRIM_TRIPLES; i++)
			{
				_ver = _para.GetByIndex(i+1);
				_LuaHelper_GetVertex(&_ver, &(triple->v[i]));
			}
		}
		_para = obj->GetByName("blend");
		if (_para.IsNumber())
		{
			triple->blend = _para.GetInteger();
		}
		_para = obj->GetByName("tex");
		if (_para.IsNumber())
		{
			triple->tex = _LuaHelper_GetDWORD(&_para);
		}
	}
}

void Export_Lua_HGE::_LuaHelper_GetQuad(LuaObject * obj, hgeQuad * quad)
{
	if (obj->IsTable())
	{
		LuaObject _para;
		_para = obj->GetByName("v");
		if (_para.IsTable())
		{
			LuaObject _ver;
			for (int i=0; i<HGEPRIM_QUADS; i++)
			{
				_ver = _para.GetByIndex(i+1);
				_LuaHelper_GetVertex(&_ver, &(quad->v[i]));
			}
		}
		_para = obj->GetByName("blend");
		if (_para.IsNumber())
		{
			quad->blend = _para.GetInteger();
		}
		_para = obj->GetByName("tex");
		if (_para.IsNumber())
		{
			quad->tex = _LuaHelper_GetDWORD(&_para);
		}
	}
}

int Export_Lua_HGE::LuaFn_hge_Struct_hgeQuad(LuaState * ls)
{
	LuaStack args(ls);

	LuaStackObject _table = ls->CreateTable();
	LuaStackObject _v = _table.CreateTable("v");
	DWORD _col = 0xffffffff;
	for (int i=0 ;i<HGEPRIM_QUADS; i++)
	{
		LuaStackObject _vobj = _v.CreateTable(i+1);
		_vobj.SetNumber("x", 0);
		_vobj.SetNumber("y", 0);
		_vobj.SetNumber("z", 0);
		_vobj.SetNumber("tx", 0);
		_vobj.SetNumber("ty", 0);
		_vobj.SetNumber("col", CDOUBLEN(_col));
	}
	_table.SetInteger("tex", 0);
	_table.SetInteger("blend", BLEND_DEFAULT);

	ls->PushValue(_table);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_System_SetState(LuaState * ls)
{
	LuaStack args(ls);

	int hgestate = args[1].GetInteger();
	LuaObject _obj = args[2];
	HWND _hwnd;
	switch (hgestate & HGE_STATE_MASK)
	{
	case HGE_STATE_BOOLTEST:
		hge->System_SetState((hgeBoolState)hgestate, args[2].GetBoolean());
		break;
	case HGE_STATE_FUNCTEST:
		break;
	case HGE_STATE_HWNDTEST:
		_hwnd = (HWND)(_LuaHelper_GetDWORD(&_obj));
		hge->System_SetState((hgeHwndState)hgestate, _hwnd);
		break;
	case HGE_STATE_INTTEST:
		hge->System_SetState((hgeIntState)hgestate, args[2].GetInteger());
		break;
	case HGE_STATE_STRINGTEST:
		hge->System_SetState((hgeStringState)hgestate, args[2].GetString());
		break;
	}

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_System_GetState(LuaState * ls)
{
	LuaStack args(ls);

	int hgestate = args[1].GetInteger();
	bool pushed = false;
	const char * sret = 0;
	switch (hgestate & HGE_STATE_MASK)
	{
	case HGE_STATE_BOOLTEST:
		ls->PushBoolean(hge->System_GetState((hgeBoolState)hgestate));
		pushed = true;
		break;
	case HGE_STATE_FUNCTEST:
		break;
	case HGE_STATE_HWNDTEST:
		_LuaHelper_PushDWORD(ls, (DWORD)hge->System_GetState((hgeHwndState)hgestate));
		pushed = true;
		break;
	case HGE_STATE_INTTEST:
		ls->PushInteger(hge->System_GetState((hgeIntState)hgestate));
		pushed = true;
		break;
	case HGE_STATE_STRINGTEST:
		_LuaHelper_PushString(ls, hge->System_GetState((hgeStringState)hgestate));
		pushed = true;
		break;
	}

	if (pushed)
	{
		return 1;
	}
	return 0;
}

int Export_Lua_HGE::LuaFn_hge_System_Log(LuaState * ls)
{
	LuaStack args(ls);

	hge->System_Log(args[1].GetString());

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_System_GetErrorMessage(LuaState * ls)
{
	LuaStack args(ls);

	_LuaHelper_PushString(ls, hge->System_GetErrorMessage());

	return 1;
}

int Export_Lua_HGE::LuaFn_hge_System_Launch(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;

	bret = hge->System_Launch(args[1].GetString());

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_System_Snapshot(LuaState * ls)
{
	LuaStack args(ls);
	char * filename = 0;

	if (args.Count())
	{
		filename = (char *)(args[1].GetString());
	}
	hge->System_Snapshot(filename);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_System_Transform3DPoint(LuaState * ls)
{
	LuaStack args(ls);
	float fret;

	hge3DPoint pt;
	BYTE _renderflag = M_RENDER_NULL;
	int argscount = args.Count();
	if (args[1].IsTable())
	{
		pt.x = args[1].GetByName("x").GetFloat();
		pt.y = args[1].GetByName("y").GetFloat();
		pt.z = args[1].GetByName("z").GetFloat();
		if (argscount > 1)
		{
			_renderflag = args[2].GetInteger();
		}
	}
	else
	{
		pt.x = args[1].GetFloat();
		pt.y = args[2].GetFloat();
		pt.z = args[3].GetFloat();
		if (argscount > 3)
		{
			_renderflag = args[4].GetInteger();
		}
	}
	fret = hge->Math_Transform3DPoint(&pt, Export::GetFarPoint(_renderflag));

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Resource_Load(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;
	DWORD size;

	dret = (DWORD)(hge->Resource_Load(args[1].GetString(), &size));

	_LuaHelper_PushDWORD(ls, dret);
	_LuaHelper_PushDWORD(ls, size);

	return 2;
}

int Export_Lua_HGE::LuaFn_hge_Resource_Free(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	DWORD _dword = _LuaHelper_GetDWORD(&_obj);
	hge->Resource_Free((void *)(_dword));

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Resource_AttachPack(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;
	int password = 0;

	if (args.Count() > 1)
	{
		password = args[2].GetInteger();
	}
	bret = hge->Resource_AttachPack(args[1].GetString(), password);

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Resource_RemovePack(LuaState * ls)
{
	LuaStack args(ls);

	if (args.Count() > 0)
	{
		hge->Resource_RemovePack(args[1].GetString());
	}
	else
	{
		hge->Resource_RemoveAllPacks();
	}

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Resource_SetPath(LuaState * ls)
{
	LuaStack args(ls);

	_LuaHelper_PushString(ls, hge->Resource_SetPath(args[1].GetString()));

	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Resource_MakePath(LuaState * ls)
{
	LuaStack args(ls);

	_LuaHelper_PushString(ls, hge->Resource_MakePath(args[1].GetString()));

	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Resource_EnumFiles(LuaState * ls)
{
	LuaStack args(ls);
	char * wildcard = 0;

	if (args.Count() > 0)
	{
		wildcard = (char *)(args[1].GetString());
	}
	_LuaHelper_PushString(ls, hge->Resource_EnumFiles(wildcard));

	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Resource_EnumFolders(LuaState * ls)
{
	LuaStack args(ls);
	char * sret;
	char * wildcard = 0;

	if (args.Count() > 0)
	{
		wildcard = (char *)(args[1].GetString());
	}
	_LuaHelper_PushString(ls, hge->Resource_EnumFolders(wildcard));

	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Resource_CreatePack(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;
	hgeMemoryFile memfile;

	LuaObject _obj = args[3].GetByName("data");
	DWORD _data = _LuaHelper_GetDWORD(&_obj);
	memfile.data = (BYTE *)(_data);
	memfile.filename = (char *)(args[3].GetByName("filename").GetString());
	_obj = args[3].GetByName("size");
	DWORD _size = _LuaHelper_GetDWORD(&_obj);
	memfile.size = _size;

	bret = hge->Resource_CreatePack(args[1].GetString(), args[2].GetInteger(), &memfile, NULL);

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Resource_AddFileInPack(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;
	hgeMemoryFile memfile;

	LuaObject _obj = args[3].GetByName("data");
	DWORD _data = _LuaHelper_GetDWORD(&_obj);
	memfile.data = (BYTE *)(_data);
	memfile.filename = (char *)(args[3].GetByName("filename").GetString());
	_obj = args[3].GetByName("size");
	DWORD _size = _LuaHelper_GetDWORD(&_obj);
	memfile.size = _size;

	bret = hge->Resource_AddFileInPack(args[1].GetString(), args[2].GetInteger(), &memfile);

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Resource_GetCRC(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	if (args[1].IsString())
	{
		const char * _string = args[1].GetString();
		iret = hge->Resource_GetCRC((BYTE *)_string, strlen(_string));
	}
	else
	{
		LuaObject _obj = args[1];
		DWORD _content = _LuaHelper_GetDWORD(&_obj);
		_obj = args[2];
		DWORD _size = _LuaHelper_GetDWORD(&_obj); 
		iret = hge->Resource_GetCRC((BYTE *)(_content), _size);
	}

	ls->PushInteger(iret);
	//	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Resource_GetPackFirstFileName(LuaState * ls)
{
	LuaStack args(ls);

	_LuaHelper_PushString(ls, hge->Resource_GetPackFirstFileName(args[1].GetString()));

	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Ini_SetInt(LuaState * ls)
{
	LuaStack args(ls);

	hge->Ini_SetInt(args[1].GetString(), args[2].GetString(), args[3].GetInteger());

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Ini_GetInt(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = hge->Ini_GetInt(args[1].GetString(), args[2].GetString(), args[3].GetInteger());

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Ini_SetFloat(LuaState * ls)
{
	LuaStack args(ls);

	hge->Ini_SetFloat(args[1].GetString(), args[2].GetString(), args[3].GetFloat());

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Ini_GetFloat(LuaState * ls)
{
	LuaStack args(ls);
	float fret;

	fret = hge->Ini_GetFloat(args[1].GetString(), args[2].GetString(), args[3].GetFloat());

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Ini_SetString(LuaState * ls)
{
	LuaStack args(ls);

	hge->Ini_SetString(args[1].GetString(), args[2].GetString(), args[3].GetString());

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Ini_GetString(LuaState * ls)
{
	LuaStack args(ls);

	_LuaHelper_PushString(ls, hge->Ini_GetString(args[1].GetString(), args[2].GetString(), args[3].GetString()));

	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Random_Seed(LuaState * ls)
{
	LuaStack args(ls);
	int seed = 0;

	if (args.Count() > 0)
	{
		seed = args[1].GetInteger();
	}
	seed = hge->Random_Seed(seed);

	ls->PushInteger(seed);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Random_Int(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = hge->Random_Int(args[1].GetInteger(), args[2].GetInteger());

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Random_Float(LuaState * ls)
{
	LuaStack args(ls);
	float fret;

	fret = hge->Random_Float(args[1].GetFloat(), args[2].GetFloat());

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Timer_GetTime(LuaState * ls)
{
	LuaStack args(ls);
	float fret;

	fret = hge->Timer_GetTime();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Timer_GetDelta(LuaState * ls)
{
	LuaStack args(ls);
	float fret;

	fret = hge->Timer_GetDelta();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Timer_GetFPS(LuaState * ls)
{
	LuaStack args(ls);
	float fret;
	int mod = 0;

	if (args.Count() > 0)
	{
		mod = args[1].GetInteger();
	}
	fret = hge->Timer_GetFPS(mod);

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Timer_GetWorstFPS(LuaState * ls)
{
	LuaStack args(ls);
	float fret;

	fret = hge->Timer_GetWorstFPS(args[1].GetInteger());

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Timer_GetCurrentSystemTime(LuaState * ls)
{
	LuaStack args(ls);
	LONGLONG _longlong;

	_longlong = hge->Timer_GetCurrentSystemTime();

	_LuaHelper_PushLONGLONG(ls, _longlong);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Effect_Load(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;
	DWORD size = 0;

	if (args.Count() > 1)
	{
		LuaObject _obj = args[2];
		size = _LuaHelper_GetDWORD(&_obj);
	}
	dret = (DWORD)(hge->Effect_Load(args[1].GetString(), size));

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Effect_Free(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HEFFECT _heffect = (HEFFECT)(_LuaHelper_GetDWORD(&_obj));
	hge->Effect_Free(_heffect);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Effect_Play(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;
	int volume = 100;
	int pan = 0;
	float pitch = 1.0f;
	bool loop = false;

	LuaObject _obj = args[1];
	HEFFECT _heffect = (HEFFECT)(_LuaHelper_GetDWORD(&_obj));
	int argscount = args.Count();
	if (argscount > 1)
	{
		volume = args[2].GetInteger();
		if (argscount > 2)
		{
			pan = args[3].GetInteger();
			if (argscount > 3)
			{
				pitch = args[4].GetFloat();
				if (argscount > 4)
				{
					loop = args[5].GetBoolean();
				}
			}
		}
	}
	if (argscount > 1)
	{
		dret = (DWORD)(hge->Effect_PlayEx(_heffect, volume, pan, pitch, loop));
	}
	else
	{
		dret = (DWORD)(hge->Effect_Play(_heffect));
	}

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Stream_Load(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;
	DWORD size = 0;
	bool bLoad = true;

	int argscount = args.Count();
	if (argscount > 1)
	{
		LuaObject _obj = args[2];
		size = _LuaHelper_GetDWORD(&_obj);
		if (argscount > 2)
		{
			bLoad = args[3].GetBoolean();
		}
	}
	dret = (DWORD)(hge->Stream_Load(args[1].GetString(), size, bLoad));

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Stream_Free(LuaState * ls)
{
	LuaStack args(ls);


	LuaObject _obj = args[1];
	HSTREAM _hstream = (HSTREAM)(_LuaHelper_GetDWORD(&_obj));
	hge->Stream_Free(_hstream);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Stream_Play(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;
	int volume = 100;

	if (args.Count() > 2)
	{
		volume = args[3].GetInteger();
	}
	LuaObject _obj = args[1];
	HSTREAM _hstream = (HSTREAM)(_LuaHelper_GetDWORD(&_obj));
	dret = (DWORD)(hge->Stream_Play(_hstream, args[2].GetBoolean(), volume));

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Channel_SetPanning(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	hge->Channel_SetPanning(_hchannel, args[2].GetInteger());

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_SetVolume(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	hge->Channel_SetVolume(_hchannel, args[2].GetInteger());

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_SetPitch(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	hge->Channel_SetPitch(_hchannel, args[2].GetFloat());

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_Pause(LuaState * ls)
{
	LuaStack args(ls);

	if (args.Count() > 0)
	{
		LuaObject _obj = args[1];
		HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
		hge->Channel_Pause(_hchannel);
	}
	else
	{
		hge->Channel_PauseAll();
	}

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_Resume(LuaState * ls)
{
	LuaStack args(ls);

	if (args.Count() > 0)
	{
		LuaObject _obj = args[1];
		HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
		hge->Channel_Resume(_hchannel);
	}
	else
	{
		hge->Channel_ResumeAll();
	}

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_Stop(LuaState * ls)
{
	LuaStack args(ls);
	if (args.Count() > 0)
	{
		LuaObject _obj = args[1];
		HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
		hge->Channel_Stop(_hchannel);
	}
	else
	{
		hge->Channel_StopAll();
	}

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_IsPlaying(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	hge->Channel_IsPlaying(_hchannel);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_GetLength(LuaState * ls)
{
	LuaStack args(ls);
	QWORD _qword;

	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	_qword = hge->Channel_GetLength(_hchannel);

	_LuaHelper_PushQWORD(ls, _qword);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Channel_GetPos(LuaState * ls)
{
	LuaStack args(ls);
	int _int;
	QWORD _qword;

	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	_qword = hge->Channel_GetPos(_hchannel);

	_LuaHelper_PushQWORD(ls, _qword);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Channel_SetPos(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	_obj = args[2];
	QWORD pos = _LuaHelper_GetQWORD(&_obj);

	hge->Channel_SetPos(_hchannel, pos);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_SetStartPos(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	hge->Channel_SetStartPos(_hchannel, &channelsyncinfo);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_SlideTo(LuaState * ls)
{
	LuaStack args(ls);
	int _int;
	int pan = -101;
	float pitch = -1;

	int argscount = args.Count();
	if (argscount > 3)
	{
		pan = args[4].GetInteger();
		if (argscount > 4)
		{
			pitch = args[5].GetFloat();
		}
	}
	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	hge->Channel_SlideTo(_hchannel, args[2].GetFloat(), args[3].GetInteger(), pan, pitch);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_IsSliding(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;

	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	bret = hge->Channel_IsSliding(_hchannel);

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Channel_SetLoop(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj;
	_obj = args[2];
	if (_obj.IsTable())
	{
		LuaObject _alllength = _obj.GetByName("alllength");
		channelsyncinfo.allLength = _LuaHelper_GetQWORD(&_alllength);
		LuaObject _introlength = _obj.GetByName("introlength");
		channelsyncinfo.introLength = _LuaHelper_GetQWORD(&_introlength);
		LuaObject _startpos = _obj.GetByName("startpos");
		channelsyncinfo.startPos = _LuaHelper_GetQWORD(&_startpos);
		LuaObject _sync = _obj.GetByName("sync");
		if (!_sync.IsNil())
		{
			channelsyncinfo.sync = _LuaHelper_GetDWORD(&_sync);
		}
	}
	else
	{
		_obj = args[2];
		channelsyncinfo.startPos = _LuaHelper_GetQWORD(&_obj);
		_obj = args[3];
		channelsyncinfo.introLength = _LuaHelper_GetQWORD(&_obj);
		_obj = args[4];
		channelsyncinfo.allLength = _LuaHelper_GetQWORD(&_obj);
		if (args.Count() > 4)
		{
			_obj = args[5];
			channelsyncinfo.sync = _LuaHelper_GetQWORD(&_obj);
		}
	}

	_obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	hge->Channel_SetLoop(_hchannel, &channelsyncinfo);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Channel_RemoveLoop(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HCHANNEL _hchannel = (HCHANNEL)(_LuaHelper_GetDWORD(&_obj));
	hge->Channel_RemoveLoop(_hchannel, &channelsyncinfo);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Input_GetMousePos(LuaState * ls)
{
	LuaStack args(ls);
	float x;
	float y;

	hge->Input_GetMousePos(&x, &y);

	ls->PushNumber(x);
	ls->PushNumber(y);
	return 2;
}

int Export_Lua_HGE::LuaFn_hge_Input_SetMousePos(LuaState * ls)
{
	LuaStack args(ls);

	hge->Input_SetMousePos(args[1].GetFloat(), args[2].GetFloat());

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Input_GetMouseWheel(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = hge->Input_GetMouseWheel();

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_IsMouseOver(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;

	bret = hge->Input_IsMouseOver();

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_KeyDown(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;

	bret = hge->Input_KeyDown(args[1].GetInteger());

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_KeyUp(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;

	bret = hge->Input_KeyUp(args[1].GetInteger());

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_GetKeyState(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;

	bret = hge->Input_GetKeyState(args[1].GetInteger());

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_GetKeyName(LuaState * ls)
{
	LuaStack args(ls);

	_LuaHelper_PushString(ls, hge->Input_GetKeyName(args[1].GetInteger()));

	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_GetKey(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = hge->Input_GetKey();

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_GetChar(LuaState * ls)
{
	LuaStack args(ls);
	int iret;

	iret = hge->Input_GetChar();

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_GetEvent(LuaState * ls)
{
	LuaStack args(ls);
	hgeInputEvent inputevent;

	hge->Input_GetEvent(&inputevent);
	LuaStackObject table = ls->CreateTable();
	table.SetInteger("chr", inputevent.chr);
	table.SetInteger("flags", inputevent.flags);
	table.SetInteger("key", inputevent.key);
	table.SetInteger("type", inputevent.type);
	table.SetInteger("wheel", inputevent.wheel);
	table.SetNumber("x", inputevent.x);
	table.SetNumber("y", inputevent.y);

	ls->PushValue(table);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_GetDIKey(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;
	BYTE statetype = DIKEY_PRESSED;

	if (args.Count() > 1)
	{
		statetype = args[2].GetInteger();
	}
	bret = hge->Input_GetDIKey(args[1].GetInteger(), statetype);

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_SetDIKey(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;
	bool set = true;

	if (args.Count() > 1)
	{
		set = args[2].GetBoolean();
	}
	bret = hge->Input_SetDIKey(args[1].GetInteger(), set);

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_GetDIJoy(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;
	BYTE statetype = DIKEY_PRESSED;

	if (args.Count() > 1)
	{
		statetype = args[2].GetInteger();
	}
	bret = hge->Input_GetDIJoy(args[1].GetInteger(), statetype);

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Input_HaveJoy(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;

	bret = hge->Input_HaveJoy();

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_BeginScene(LuaState * ls)
{
	LuaStack args(ls);
	bool bret;
	HTARGET target = 0;

	if (args.Count() > 0)
	{
		LuaObject _obj = args[1];
		target = (HTARGET)_LuaHelper_GetDWORD(&_obj);
	}
	bret = hge->Gfx_BeginScene(target);

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_EndScene(LuaState * ls)
{
	LuaStack args(ls);

	hge->Gfx_EndScene();

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_Clear(LuaState * ls)
{
	LuaStack args(ls);
	DWORD col;

	LuaObject obj = args[1];
	col = _LuaHelper_GetColor(&obj);
	hge->Gfx_Clear(col);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_RenderLine(LuaState * ls)
{
	LuaStack args(ls);
	DWORD col = 0xffffffff;
	float z = 0.5f;

	int argscount = args.Count();
	if (argscount > 4)
	{
		LuaObject obj = args[5];
		col = _LuaHelper_GetColor(&obj);
		if (argscount > 5)
		{
			z = args[6].GetFloat();
		}
	}
	hge->Gfx_RenderLine(args[1].GetFloat(), args[2].GetFloat(), args[3].GetFloat(), args[4].GetFloat(), col, z);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_RenderTriple(LuaState * ls)
{
	LuaStack args(ls);
	hgeTriple triple;

	LuaObject obj = args[1];
	_LuaHelper_GetTriple(&obj, &triple);
	hge->Gfx_RenderTriple(&triple);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_RenderQuad(LuaState * ls)
{
	LuaStack args(ls);
	hgeQuad quad;

	LuaObject obj = args[1];
	_LuaHelper_GetQuad(&obj, &quad);
	SpriteItemManager::RenderQuad(&quad);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_StartBatch(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;

	LuaObject _obj = args[1];
	HTEXTURE _htexture = (HTEXTURE)_LuaHelper_GetDWORD(&_obj);
	_obj = args[4];
	int * _max_prim = (int *)_LuaHelper_GetDWORD(&_obj);
	dret = (DWORD)(hge->Gfx_StartBatch(args[1].GetInteger(), _htexture, args[3].GetInteger(), _max_prim));

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_FinishBatch(LuaState * ls)
{
	LuaStack args(ls);

	hge->Gfx_FinishBatch(args[1].GetInteger());

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_SetClipping(LuaState * ls)
{
	LuaStack args(ls);
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	int argscount = args.Count();
	if (argscount > 0)
	{
		x = args[1].GetFloat();
		if (argscount > 1)
		{
			y = args[2].GetFloat();
			if (argscount > 2)
			{
				w = args[3].GetFloat();
				if (argscount > 3)
				{
					h = args[4].GetFloat();
				}
			}
		}
	}
	hge->Gfx_SetClipping(x, y, w, h);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_SetTransform(LuaState * ls)
{
	LuaStack args(ls);

	int argscount = args.Count();
	if (argscount > 1 && args[2].IsTable())
	{
		D3DMATRIX matrix;
		LuaObject _obj = args[2];
		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4;j++)
			{
				matrix.m[i][j] = _obj.GetByIndex(i+1).GetByIndex(j+1).GetNumber();
			}
		}
		hge->Gfx_SetTransform((D3DTRANSFORMSTATETYPE)(args[1].GetInteger()), &matrix);
	}
	else if (argscount > 0)
	{
		float x = 0;
		float y = 0;
		float dx = 0;
		float dy = 0;
		float rot = 0;
		float hscale = 0;
		float vscale = 0;

		x = args[1].GetFloat();
		if (argscount > 1)
		{
			y = args[2].GetFloat();
			if (argscount > 2)
			{
				dx = args[3].GetFloat();
				if (argscount > 3)
				{
					dy = args[4].GetFloat();
					if (argscount > 4)
					{
						rot = args[5].GetFloat();
						if (argscount > 5)
						{
							hscale = args[6].GetFloat();
							if (argscount > 6)
							{
								vscale = args[7].GetFloat();
							}
						}
					}
				}
			}
		}
		hge->Gfx_SetTransform(x, y, dx, dy, rot, hscale, vscale);
	}
	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Target_Create(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;

	dret = (DWORD)(hge->Target_Create(args[1].GetInteger(), args[2].GetInteger(), args[3].GetBoolean()));

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Target_Free(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HTARGET _htarget = (HTARGET)_LuaHelper_GetDWORD(&_obj);
	hge->Target_Free(_htarget);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Target_GetTexture(LuaState * ls)
{
	LuaStack args(ls);
	int iret;
	DWORD dret;

	LuaObject _obj = args[1];
	HTARGET _htarget = (HTARGET)_LuaHelper_GetDWORD(&_obj);

	HTEXTURE _tex = hge->Target_GetTexture(_htarget);
	iret = _tex.texindex;
	dret = hge->Texture_GetTexture(_tex);

	ls->PushInteger(iret);
	_LuaHelper_PushDWORD(ls, dret);
	return 2;
}

int Export_Lua_HGE::LuaFn_hge_Texture_Create(LuaState * ls)
{
	LuaStack args(ls);
	int iret;
	DWORD dret;

	HTEXTURE _tex = hge->Texture_Create(args[1].GetInteger(), args[2].GetInteger());
	iret = _tex.texindex;
	dret = hge->Texture_GetTexture(_tex);

	ls->PushInteger(iret);
	_LuaHelper_PushDWORD(ls, dret);
	return 2;
}

int Export_Lua_HGE::LuaFn_hge_Texture_Load(LuaState * ls)
{
	LuaStack args(ls);
	int iret;
	DWORD dret;
	DWORD size = 0;
	bool bMipmap = false;

	int argscount = args.Count();
	if (argscount > 1)
	{
		LuaObject _obj = args[2];
		size = _LuaHelper_GetDWORD(&_obj);
		if (argscount > 2)
		{
			bMipmap = args[3].GetBoolean();
		}
	}
	
	HTEXTURE _tex = hge->Texture_Load(args[1].GetString(), size, bMipmap);
	iret = _tex.texindex;
	dret = hge->Texture_GetTexture(_tex);

	ls->PushInteger(iret);
	_LuaHelper_PushDWORD(ls, dret);
	return 2;
}

int Export_Lua_HGE::LuaFn_hge_Texture_Free(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HTEXTURE _htexture = (HTEXTURE)_LuaHelper_GetDWORD(&_obj);
	hge->Texture_Free(_htexture);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Texture_GetWH(LuaState * ls)
{
	LuaStack args(ls);
	int width;
	int height;
	HTEXTURE tex;
	bool bOriginal = false;

	LuaObject _obj = args[1];
	tex = (HTEXTURE)_LuaHelper_GetDWORD(&_obj);
	if (args.Count() > 1)
	{
		bOriginal = args[2].GetBoolean();
	}
	width = hge->Texture_GetWidth(tex, bOriginal);
	height = hge->Texture_GetHeight(tex, bOriginal);

	ls->PushInteger(width);
	ls->PushInteger(height);
	return 2;
}

int Export_Lua_HGE::LuaFn_hge_Texture_Lock(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;
	bool bReadOnly = true;
	int left = 0;
	int top = 0;
	int width = 0;
	int height = 0;

	int argscount = args.Count();
	if (argscount > 1)
	{
		bReadOnly = args[2].GetBoolean();
		if (argscount > 2)
		{
			left = args[3].GetInteger();
			if (argscount > 3)
			{
				top = args[4].GetInteger();
				if (argscount > 4)
				{
					width = args[5].GetInteger();
					if (argscount > 5)
					{
						height = args[6].GetInteger();
					}
				}
			}
		}
	}
	LuaObject _obj = args[1];
	HTEXTURE _htexture = (HTEXTURE)_LuaHelper_GetDWORD(&_obj);
	dret = (DWORD)(hge->Texture_Lock(_htexture, bReadOnly, left, top, width, height));

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Texture_Unlock(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HTEXTURE _htexture = (HTEXTURE)_LuaHelper_GetDWORD(&_obj);
	hge->Texture_Unlock(_htexture);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Font_Load(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret;

	dret = (DWORD)(hge->Font_Load(args[1].GetString(), args[2].GetInteger()));

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGE::LuaFn_hge_Font_Free(LuaState * ls)
{
	LuaStack args(ls);

	LuaObject _obj = args[1];
	HD3DFONT _hd3dfont = (HD3DFONT)_LuaHelper_GetDWORD(&_obj);
	hge->Font_Free(_hd3dfont);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_RenderText(LuaState * ls)
{
	LuaStack args(ls);
	DWORD col = 0xffffffff;

	if (args.Count() > 6)
	{
		LuaObject obj = args[7];
		col = _LuaHelper_GetColor(&obj);
	}
	LuaObject _obj = args[1];
	HD3DFONT _hd3dfont = (HD3DFONT)_LuaHelper_GetDWORD(&_obj);
	hge->Gfx_RenderText(_hd3dfont, args[2].GetString(), args[3].GetFloat(), args[4].GetFloat(), args[5].GetFloat(), args[6].GetFloat(), col);

	return 0;
}

int Export_Lua_HGE::LuaFn_hge_Gfx_RenderTextToTarget(LuaState * ls)
{
	LuaStack args(ls);
	HTEXTURE tex;
	DWORD col = 0xffffffff;

	if (args.Count() > 7)
	{
		LuaObject obj = args[8];
		col = _LuaHelper_GetColor(&obj);
	}
	LuaObject _obj = args[1];
	HTARGET _htarget = (HTARGET)_LuaHelper_GetDWORD(&_obj);
	_obj = args[2];
	HD3DFONT _hd3dfont = (HD3DFONT)_LuaHelper_GetDWORD(&_obj);
	int height = hge->Gfx_RenderTextToTarget(&tex, _htarget, _hd3dfont, args[3].GetString(), args[4].GetFloat(), args[5].GetFloat(), args[6].GetFloat(), args[7].GetFloat(), col);

	ls->PushInteger(tex.texindex);
	_LuaHelper_PushDWORD(ls, tex.tex);
	ls->PushInteger(height);
	return 2;
}

#endif