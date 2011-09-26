#include "../Header/GameInput.h"
#include "../Header/ConstResource.h"
#include "../Header/Process.h"

GameInput GameInput::gameinput;
HGE * GameInput::hge = NULL;

GameInput::GameInput()
{
	KS_UP		= RESCONFIGDEFAULT_KEYUP_1;
	KS_DOWN		= RESCONFIGDEFAULT_KEYDOWN_1;
	KS_LEFT		= RESCONFIGDEFAULT_KEYLEFT_1;
	KS_RIGHT	= RESCONFIGDEFAULT_KEYRIGHT_1;
	KS_FIRE		= RESCONFIGDEFAULT_KEYFIRE_1;
	KS_QUICK	= RESCONFIGDEFAULT_KEYQUICK_1;
	KS_SLOW		= RESCONFIGDEFAULT_KEYSLOW_1;
	KS_DRAIN	= RESCONFIGDEFAULT_KEYDRAIN_1;
	KS_PAUSE	= RESCONFIGDEFAULT_KEYPAUSE;
	KS_SKIP		= RESCONFIGDEFAULT_KEYSKIP;
	KS_ENTER	= RESCONFIGDEFAULT_KEYENTER;
	KS_ESCAPE	= RESCONFIGDEFAULT_KEYESCAPE;
	KS_CAPTURE	= RESCONFIGDEFAULT_KEYCAPTURE;

	gameinput.keycombineslowdrain = RESCONFIGDEFAULT_KEYCOMBINESLOWDRAIN;
	gameinput.joycombineslowdrain = RESCONFIGDEFAULT_JOYCOMBINESLOWDRAIN;
}

GameInput::~GameInput()
{

}

bool GameInput::InitInput(HGE * _hge)
{
	hge = _hge;

	KS_UP		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYUP, RESCONFIGDEFAULT_KEYUP_1);
	KS_DOWN		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYDOWN, RESCONFIGDEFAULT_KEYDOWN_1);
	KS_LEFT		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYLEFT, RESCONFIGDEFAULT_KEYLEFT_1);
	KS_RIGHT	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYRIGHT, RESCONFIGDEFAULT_KEYRIGHT_1);
	KS_FIRE		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYFIRE, RESCONFIGDEFAULT_KEYFIRE_1);
	KS_QUICK	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYQUICK, RESCONFIGDEFAULT_KEYQUICK_1);
	KS_SLOW		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYSLOW, RESCONFIGDEFAULT_KEYSLOW_1);
	KS_DRAIN	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYDRAIN, RESCONFIGDEFAULT_KEYDRAIN_1);
	KS_PAUSE	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYPAUSE, RESCONFIGDEFAULT_KEYPAUSE);
	KS_SKIP		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYSKIP, RESCONFIGDEFAULT_KEYSKIP);
	KS_ENTER	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYENTER, RESCONFIGDEFAULT_KEYENTER);
	KS_ESCAPE	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYESCAPE, RESCONFIGDEFAULT_KEYESCAPE);
	KS_CAPTURE	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYCAPTURE, RESCONFIGDEFAULT_KEYCAPTURE);

	gameinput.keycombineslowdrain = hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYCOMBINESLOWDRAIN, RESCONFIGDEFAULT_KEYCOMBINESLOWDRAIN);

	JS_FIRE		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYFIRE, RESCONFIGDEFAULT_JOYFIRE);
	JS_QUICK	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYQUICK, RESCONFIGDEFAULT_JOYQUICK);
	JS_SLOW		= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYSLOW, RESCONFIGDEFAULT_JOYSLOW);
	JS_DRAIN	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYDRAIN, RESCONFIGDEFAULT_JOYDRAIN);
	JS_PAUSE	= hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYPAUSE, RESCONFIGDEFAULT_JOYPAUSE);


	gameinput.joycombineslowdrain = hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYCOMBINESLOWDRAIN, RESCONFIGDEFAULT_JOYCOMBINESLOWDRAIN);

#ifdef __DEBUG
	JS_DEBUG_SPEEDUP = hge->Ini_GetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_DEBUG_JOYSPEEDUP, RESCONFIGDEFAULT_DEBUG_JOYSPEEDUP);
#endif
	for (int i=0; i<13; i++)
	{
		if (gameinput.keyKey[i] < 0 || gameinput.keyKey[i] >= M_KEYKEYMAX)
		{
			return false;
		}
	}
	for (int i=0; i<5; i++)
	{
		if(gameinput.joyKey[i] < 0 || gameinput.joyKey[i] >= M_JOYKEYMAX)
		{
			return false;
		}
	}
#ifdef __DEBUG
	if(JS_DEBUG_SPEEDUP < 0 || JS_DEBUG_SPEEDUP >= M_JOYKEYMAX)
		return false;
#endif
	return true;
}

bool GameInput::ReleaseInput()
{
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYUP, KS_UP);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYDOWN, KS_DOWN);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYLEFT, KS_LEFT);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYRIGHT, KS_RIGHT);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYFIRE, KS_FIRE);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYQUICK, KS_QUICK);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYSLOW, KS_SLOW);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYDRAIN, KS_DRAIN);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYPAUSE, KS_PAUSE);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYSKIP, KS_SKIP);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYENTER, KS_ENTER);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYESCAPE, KS_ESCAPE);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYCAPTURE, KS_CAPTURE);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYCOMBINESLOWDRAIN, gameinput.keycombineslowdrain);

	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYFIRE, JS_FIRE);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYQUICK, JS_QUICK);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYSLOW, JS_SLOW);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYDRAIN, JS_DRAIN);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYPAUSE, JS_PAUSE);
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYCOMBINESLOWDRAIN, gameinput.joycombineslowdrain);

#ifdef __DEBUG
	hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_DEBUG_JOYSPEEDUP, JS_DEBUG_SPEEDUP);
#endif
	return true;
}

bool GameInput::UpdateInput(bool startstate)
{
	if (!hge)
	{
		return false;
	}
	gameinput.lastInput = gameinput.input;
	gameinput.input = 0;
	for (int i=0; i<GAMEINPUTKEYMAX; i++)
	{
		gameinput.input |= (hge->Input_GetDIKey(gameinput.keyKey[i])?1:0)<<i;
	}
	if (startstate && gameinput.keycombineslowdrain)
	{
		if (hge->Input_GetDIKey(KS_SLOW))
		{
			gameinput.input |= 1<<KSI_DRAIN;
		}
	}
	if (hge->Input_GetDIJoy(JOY_UP, DIKEY_PRESSED))
	{
		gameinput.input |= 1<<KSI_UP;
	}
	if (hge->Input_GetDIJoy(JOY_DOWN, DIKEY_PRESSED))
	{
		gameinput.input |= 1<<KSI_DOWN;
	}
	if (hge->Input_GetDIJoy(JOY_LEFT, DIKEY_PRESSED))
	{
		gameinput.input |= 1<<KSI_LEFT;
	}
	if (hge->Input_GetDIJoy(JOY_RIGHT, DIKEY_PRESSED))
	{
		gameinput.input |= 1<<KSI_RIGHT;
	}
	if (hge->Input_GetDIJoy(JS_FIRE, DIKEY_PRESSED))
	{
		gameinput.input |= 1<<KSI_FIRE;
	}
	if (hge->Input_GetDIJoy(JS_QUICK, DIKEY_PRESSED))
	{
		gameinput.input |= 1<<KSI_QUICK;
	}
	if (hge->Input_GetDIJoy(JS_SLOW, DIKEY_PRESSED))
	{
		gameinput.input |= 1<<KSI_SLOW;
		if (startstate && gameinput.joycombineslowdrain)
		{
			gameinput.input |= 1<<KSI_DRAIN;
		}
	}
	if (hge->Input_GetDIJoy(JS_DRAIN, DIKEY_PRESSED))
	{
		gameinput.input |= 1<<KSI_DRAIN;
	}
	if (hge->Input_GetDIJoy(JS_PAUSE, DIKEY_PRESSED))
	{
		gameinput.input |= 1<<KSI_PAUSE;
	}
	if (hge->Input_GetDIJoy(JS_DEBUG_SPEEDUP, DIKEY_PRESSED))
	{
		gameinput.input |= 1<<KSI_SKIP;
	}
#ifdef __PSP
#endif // __PSP

	//
	SyncControlInputSelf();
	//

	return true;
}

void GameInput::SyncControlInputSelf()
{
	if (GetKey(KSI_PAUSE) || GetKey(KSI_PAUSE))
	{
		SetKey(KSI_PAUSE);
		SetKey(KSI_PAUSE);
	}
	if (GetKey(KSI_SKIP) || GetKey(KSI_SKIP))
	{
		SetKey(KSI_SKIP);
		SetKey(KSI_SKIP);
	}
	if (GetKey(KSI_ENTER) || GetKey(KSI_ENTER))
	{
		SetKey(KSI_ENTER);
		SetKey(KSI_ENTER);
	}
	if (GetKey(KSI_ESCAPE) || GetKey(KSI_ESCAPE))
	{
		SetKey(KSI_ESCAPE);
		SetKey(KSI_ESCAPE);
	}
	if (GetKey(KSI_CAPTURE) || GetKey(KSI_CAPTURE))
	{
		SetKey(KSI_CAPTURE);
		SetKey(KSI_CAPTURE);
	}
}

void GameInput::SyncControlInput()
{
	if (hge)
	{
		if (hge->Input_GetDIKey(KS_PAUSE) || hge->Input_GetDIJoy(JS_PAUSE, DIKEY_PRESSED, 0))
		{
			hge->Input_SetDIKey(KS_PAUSE);
		}
		if (hge->Input_GetDIKey(KS_SKIP) || hge->Input_GetDIJoy(JS_DEBUG_SPEEDUP, DIKEY_PRESSED, 0))
		{
			hge->Input_SetDIKey(KS_SKIP);
		}
		if (hge->Input_GetDIKey(KS_ENTER))
		{
			hge->Input_SetDIKey(KS_ENTER);
		}
		if (hge->Input_GetDIKey(KS_ESCAPE))
		{
			hge->Input_SetDIKey(KS_ESCAPE);
		}
		if (hge->Input_GetDIKey(KS_CAPTURE))
		{
			hge->Input_SetDIKey(KS_CAPTURE);
		}
	}
}

void GameInput::SyncForActiveInput()
{
	for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
	{
		WORD testi = 1<<i;
		if (gameinput.input & testi/* || gameinput[1].input & testi*/)
		{
			gameinput.input |= testi;
//			gameinput[1].input |= testi;
		}
	}
}

void GameInput::SwapInput(bool setswap)
{
//	swapinput = setswap;
}

WORD GameInput::updateActiveInput(bool copylast/* =false */)
{
	if (copylast)
	{
		activeInput = lastActiveInput;
		for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
		{
			BYTE seti = 1<<i;
			input &= ~seti;
			input |= activeInput & seti;
		}
	}
	else
	{
		lastActiveInput = activeInput;
		activeInput = 0;
		for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
		{
			activeInput |= (input&(1<<i));
		}
	}
	return activeInput;
}

bool GameInput::GetKey(int ksi, int type/* =DIKEY_PRESSED */)
{
	return gameinput.getKey(ksi, type);
}

void GameInput::SetKey(int ksi, bool set/* =true */)
{
	gameinput.setKey(ksi, set);
}

bool GameInput::getKey(int ksi, int type/* =DIKEY_PRESSED */)
{
	bool bnow = input & (1<<ksi);
	bool blast = lastInput & (1<<ksi);
	switch (type)
	{
	case DIKEY_DOWN:
		if (bnow && !blast)
		{
			return true;
		}
		break;
	case DIKEY_UP:
		if (!bnow && blast)
		{
			return true;
		}
		break;
	default:
		if (bnow)
		{
			return true;
		}
		break;
	}
	return false;
}

void GameInput::setKey(int ksi, bool set/* =true */)
{
	if (set)
	{
		input |= 1<<ksi;
	}
	else
	{
		input &= ~(1<<ksi);
	}
}

WORD GameInput::GetNowInput()
{
	WORD wret = 0;
	for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
	{
		wret |= (GetKey(i)<<i);
	}
	return wret;
}

void GameInput::SetNowInput(WORD nowinput)
{
	WORD seti = 0;
	int usingindex = 0;
	for (int i=0; i<GAMEACTIVEINPUTMAX; i++)
	{
		seti = (1<<i);
		gameinput.input &= ~seti;
		gameinput.input |= (nowinput & seti);
	}
}