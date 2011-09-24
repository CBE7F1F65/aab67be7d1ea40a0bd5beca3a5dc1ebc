#ifndef __NOTUSELUA

#include "../Header/Export_Lua.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/BResource.h"

bool Export_Lua::_LuaRegistConst(LuaObject * obj)
{
	// System
	obj->SetInteger("NULL",	NULL);
#ifdef __DEBUG
	obj->SetBoolean("_DEBUG", true);
#else
	obj->SetBoolean("_DEBUG", false);
#endif // __DEBUG

	// D3D
	obj->SetInteger("D3DTS_WORLD", D3DTS_WORLD);
	obj->SetInteger("D3DTS_VIEW", D3DTS_VIEW);
	obj->SetInteger("D3DTS_PROJECTION", D3DTS_PROJECTION);

	// DI
	obj->SetInteger("DIK_ESCAPE", DIK_ESCAPE);
	obj->SetInteger("DIK_1", DIK_1);
	obj->SetInteger("DIK_2", DIK_2);
	obj->SetInteger("DIK_3", DIK_3);
	obj->SetInteger("DIK_4", DIK_4);
	obj->SetInteger("DIK_5", DIK_5);
	obj->SetInteger("DIK_6", DIK_6);
	obj->SetInteger("DIK_7", DIK_7);
	obj->SetInteger("DIK_8", DIK_8);
	obj->SetInteger("DIK_9", DIK_9);
	obj->SetInteger("DIK_0", DIK_0);
	obj->SetInteger("DIK_MINUS", DIK_MINUS);
	obj->SetInteger("DIK_EQUALS", DIK_EQUALS);
	obj->SetInteger("DIK_BACK", DIK_BACK);
	obj->SetInteger("DIK_TAB", DIK_TAB);
	obj->SetInteger("DIK_Q", DIK_Q);
	obj->SetInteger("DIK_W", DIK_W);
	obj->SetInteger("DIK_E", DIK_E);
	obj->SetInteger("DIK_R", DIK_R);
	obj->SetInteger("DIK_T", DIK_T);
	obj->SetInteger("DIK_Y", DIK_Y);
	obj->SetInteger("DIK_U", DIK_U);
	obj->SetInteger("DIK_I", DIK_I);
	obj->SetInteger("DIK_O", DIK_O);
	obj->SetInteger("DIK_P", DIK_P);
	obj->SetInteger("DIK_LBRACKET", DIK_LBRACKET);
	obj->SetInteger("DIK_RBRACKET", DIK_RBRACKET);
	obj->SetInteger("DIK_RETURN", DIK_RETURN);
	obj->SetInteger("DIK_LCONTROL", DIK_LCONTROL);
	obj->SetInteger("DIK_A", DIK_A);
	obj->SetInteger("DIK_S", DIK_S);
	obj->SetInteger("DIK_D", DIK_D);
	obj->SetInteger("DIK_F", DIK_F);
	obj->SetInteger("DIK_G", DIK_G);
	obj->SetInteger("DIK_H", DIK_H);
	obj->SetInteger("DIK_J", DIK_J);
	obj->SetInteger("DIK_K", DIK_K);
	obj->SetInteger("DIK_L", DIK_L);
	obj->SetInteger("DIK_SEMICOLON", DIK_SEMICOLON);
	obj->SetInteger("DIK_APOSTROPHE", DIK_APOSTROPHE);
	obj->SetInteger("DIK_GRAVE", DIK_GRAVE);
	obj->SetInteger("DIK_LSHIFT", DIK_LSHIFT);
	obj->SetInteger("DIK_BACKSLASH", DIK_BACKSLASH);
	obj->SetInteger("DIK_Z", DIK_Z);
	obj->SetInteger("DIK_X", DIK_X);
	obj->SetInteger("DIK_C", DIK_C);
	obj->SetInteger("DIK_V", DIK_V);
	obj->SetInteger("DIK_B", DIK_B);
	obj->SetInteger("DIK_N", DIK_N);
	obj->SetInteger("DIK_M", DIK_M);
	obj->SetInteger("DIK_COMMA", DIK_COMMA);
	obj->SetInteger("DIK_PERIOD", DIK_PERIOD);
	obj->SetInteger("DIK_SLASH", DIK_SLASH);
	obj->SetInteger("DIK_RSHIFT", DIK_RSHIFT);
	obj->SetInteger("DIK_MULTIPLY", DIK_MULTIPLY);
	obj->SetInteger("DIK_LMENU", DIK_LMENU);
	obj->SetInteger("DIK_SPACE", DIK_SPACE);
	obj->SetInteger("DIK_CAPITAL", DIK_CAPITAL);
	obj->SetInteger("DIK_F1", DIK_F1);
	obj->SetInteger("DIK_F2", DIK_F2);
	obj->SetInteger("DIK_F3", DIK_F3);
	obj->SetInteger("DIK_F4", DIK_F4);
	obj->SetInteger("DIK_F5", DIK_F5);
	obj->SetInteger("DIK_F6", DIK_F6);
	obj->SetInteger("DIK_F7", DIK_F7);
	obj->SetInteger("DIK_F8", DIK_F8);
	obj->SetInteger("DIK_F9", DIK_F9);
	obj->SetInteger("DIK_F10", DIK_F10);
	obj->SetInteger("DIK_NUMLOCK", DIK_NUMLOCK);
	obj->SetInteger("DIK_SCROLL", DIK_SCROLL);
	obj->SetInteger("DIK_NUMPAD7", DIK_NUMPAD7);
	obj->SetInteger("DIK_NUMPAD8", DIK_NUMPAD8);
	obj->SetInteger("DIK_NUMPAD9", DIK_NUMPAD9);
	obj->SetInteger("DIK_SUBTRACT", DIK_SUBTRACT);
	obj->SetInteger("DIK_NUMPAD4", DIK_NUMPAD4);
	obj->SetInteger("DIK_NUMPAD5", DIK_NUMPAD5);
	obj->SetInteger("DIK_NUMPAD6", DIK_NUMPAD6);
	obj->SetInteger("DIK_ADD", DIK_ADD);
	obj->SetInteger("DIK_NUMPAD1", DIK_NUMPAD1);
	obj->SetInteger("DIK_NUMPAD2", DIK_NUMPAD2);
	obj->SetInteger("DIK_NUMPAD3", DIK_NUMPAD3);
	obj->SetInteger("DIK_NUMPAD0", DIK_NUMPAD0);
	obj->SetInteger("DIK_DECIMAL", DIK_DECIMAL);
	obj->SetInteger("DIK_OEM_102", DIK_OEM_102);
	obj->SetInteger("DIK_F11", DIK_F11);
	obj->SetInteger("DIK_F12", DIK_F12);
	obj->SetInteger("DIK_F13", DIK_F13);
	obj->SetInteger("DIK_F14", DIK_F14);
	obj->SetInteger("DIK_F15", DIK_F15);
	obj->SetInteger("DIK_KANA", DIK_KANA);
	obj->SetInteger("DIK_ABNT_C1", DIK_ABNT_C1);
	obj->SetInteger("DIK_CONVERT", DIK_CONVERT);
	obj->SetInteger("DIK_NOCONVERT", DIK_NOCONVERT);
	obj->SetInteger("DIK_YEN", DIK_YEN);
	obj->SetInteger("DIK_ABNT_C2", DIK_ABNT_C2);
	obj->SetInteger("DIK_NUMPADEQUALS", DIK_NUMPADEQUALS);
	obj->SetInteger("DIK_PREVTRACK", DIK_PREVTRACK);
	obj->SetInteger("DIK_AT", DIK_AT);
	obj->SetInteger("DIK_COLON", DIK_COLON);
	obj->SetInteger("DIK_UNDERLINE", DIK_UNDERLINE);
	obj->SetInteger("DIK_KANJI", DIK_KANJI);
	obj->SetInteger("DIK_STOP", DIK_STOP);
	obj->SetInteger("DIK_AX", DIK_AX);
	obj->SetInteger("DIK_UNLABELED", DIK_UNLABELED);
	obj->SetInteger("DIK_NEXTTRACK", DIK_NEXTTRACK);
	obj->SetInteger("DIK_NUMPADENTER", DIK_NUMPADENTER);
	obj->SetInteger("DIK_RCONTROL", DIK_RCONTROL);
	obj->SetInteger("DIK_MUTE", DIK_MUTE);
	obj->SetInteger("DIK_CALCULATOR", DIK_CALCULATOR);
	obj->SetInteger("DIK_PLAYPAUSE", DIK_PLAYPAUSE);
	obj->SetInteger("DIK_MEDIASTOP", DIK_MEDIASTOP);
	obj->SetInteger("DIK_VOLUMEDOWN", DIK_VOLUMEDOWN);
	obj->SetInteger("DIK_VOLUMEUP", DIK_VOLUMEUP);
	obj->SetInteger("DIK_WEBHOME", DIK_WEBHOME);
	obj->SetInteger("DIK_NUMPADCOMMA", DIK_NUMPADCOMMA);
	obj->SetInteger("DIK_DIVIDE", DIK_DIVIDE);
	obj->SetInteger("DIK_SYSRQ", DIK_SYSRQ);
	obj->SetInteger("DIK_RMENU", DIK_RMENU);
	obj->SetInteger("DIK_PAUSE", DIK_PAUSE);
	obj->SetInteger("DIK_HOME", DIK_HOME);
	obj->SetInteger("DIK_UP", DIK_UP);
	obj->SetInteger("DIK_PRIOR", DIK_PRIOR);
	obj->SetInteger("DIK_LEFT", DIK_LEFT);
	obj->SetInteger("DIK_RIGHT", DIK_RIGHT);
	obj->SetInteger("DIK_END", DIK_END);
	obj->SetInteger("DIK_DOWN", DIK_DOWN);
	obj->SetInteger("DIK_NEXT", DIK_NEXT);
	obj->SetInteger("DIK_INSERT", DIK_INSERT);
	obj->SetInteger("DIK_DELETE", DIK_DELETE);
	obj->SetInteger("DIK_LWIN", DIK_LWIN);
	obj->SetInteger("DIK_RWIN", DIK_RWIN);
	obj->SetInteger("DIK_APPS", DIK_APPS);
	obj->SetInteger("DIK_POWER", DIK_POWER);
	obj->SetInteger("DIK_SLEEP", DIK_SLEEP);
	obj->SetInteger("DIK_WAKE", DIK_WAKE);
	obj->SetInteger("DIK_WEBSEARCH", DIK_WEBSEARCH);
	obj->SetInteger("DIK_WEBFAVORITES", DIK_WEBFAVORITES);
	obj->SetInteger("DIK_WEBREFRESH", DIK_WEBREFRESH);
	obj->SetInteger("DIK_WEBSTOP", DIK_WEBSTOP);
	obj->SetInteger("DIK_WEBFORWARD", DIK_WEBFORWARD);
	obj->SetInteger("DIK_WEBBACK", DIK_WEBBACK);
	obj->SetInteger("DIK_MYCOMPUTER", DIK_MYCOMPUTER);
	obj->SetInteger("DIK_MAIL", DIK_MAIL);
	obj->SetInteger("DIK_MEDIASELECT", DIK_MEDIASELECT);

	return true;
}

bool Export_Lua::_LuaRegistCustomConst(LuaObject * obj)
{
	// CustomConst
	for (int i=0; i<SCR_CUSTOMCONSTMAX; i++)
	{
		if (strlen(BResource::bres.customconstdata[i].name))
		{
			obj->SetInteger(BResource::bres.customconstdata[i].name, BResource::bres.customconstdata[i].value);
		}
	}

	return true;
}

#endif