#include "../Header/Process.h"
#include "../Header/Scripter.h"
#include "../Header/Chat.h"
#include "../Header/DataConnector.h"
#include "../Header/BossInfo.h"
#include "../Header/GameInput.h"

int Process::frame()
{
	if(hge->Input_GetKeyState(HGEK_ALT) && hge->Input_GetKeyState(HGEK_ENTER)) 
	{
		screenmode = 1 - screenmode;
		hge->System_SetState(HGE_WINDOWED, !(bool)screenmode);
		hge->System_SetState(HGE_HIDEMOUSE, (bool)screenmode);
		if(!screenmode)
		{
			Export::clientAdjustWindow();
		}
		return PSKIP;
	}
#ifdef __DEBUG
	if(hge->Input_GetKeyState(HGEK_BACKSPACE))
	{
		Scripter::scr.LoadAll();
		state = STATE_TITLE;
		gametime = 0;
		return PTURN;
	}
#endif
	if (GameInput::GetKey(0, KSI_SKIP))
	{
		if (!replaymode)
		{
			if (Chat::chatitem.IsChatting())
			{
				hge->Input_SetDIKey(GameInput::KS_FIRE, (bool)(gametime%5 == 0));
			}
		}
#ifndef __DEBUG
		else
#endif
			frameskip = M_FRAMESKIP_FASTSKIP;
	}
	else if(frameskip < M_DEFAULT_FRAMESKIP)
	{
		frameskip = M_DEFAULT_FRAMESKIP;
	}
	else if (BossInfo::allover)
	{
		frameskip = M_FRAMESKIP_SLOWSKIP;
	}
	hge->System_SetState(HGE_FRAMESKIP, frameskip);

	getInput();
	lasttime = gametime;

	playing = false;

	int rv = 0xffffffff;
	switch(state)
	{
		
	case STATE_START:
		rv = processStart();
		break;
	case STATE_PAUSE:
		rv = processPause();
		break;
	case STATE_CONTINUE:
		rv = processContinue();
		break;
	case STATE_CLEAR:
		rv = processClear();
		break;
	case STATE_ENDING:
		rv = processEnding();
		break;
	case STATE_TITLE:
		rv = processTitle();
		break;
	case STATE_MATCH_SELECT:
		rv = processMatchSelect();
		break;
	case STATE_PLAYER_SELECT:
		rv = processPlayerSelect();
		break;
	case STATE_SCENE_SELECT:
		rv = processSceneSelect();
		break;
	case STATE_OVER:
		rv = processOver();
		break;
	case STATE_SPELL:
		rv = processSpell();
		break;
	case STATE_REPLAY:
		rv = processReplay();
		break;
	case STATE_RESULT:
		rv = processResult();
		break;
	case STATE_OPTION:
		rv = processOption();
		break;
	case STATE_MUSIC:
		rv = processMusic();
		break;
	case STATE_INIT:
		rv = processInit();
		break;
	}

	if(playing && !playtimeStart)
	{
		playtimeStart = hge->Timer_GetFileTime();
	}
	else if(!playing && playtimeStart)
	{
		DataConnector::addPlayTime();
	}
	
	if(rv == 0xffffffff)
	{
		gametime = 0;
		state = STATE_TITLE;
		rv = PTURN;
	}

	if (rv == PTURN)
	{
		return PTURN;
	}

	if(rv == PQUIT)
		return PQUIT;

	frameEnd();

	return PGO;
}