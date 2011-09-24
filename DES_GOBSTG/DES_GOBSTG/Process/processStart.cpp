#include "../Header/Process.h"
#include "../Header/Scripter.h"
#include "../Header/BGLayer.h"
#include "../Header/SelectSystem.h"
#include "../Header/BGLayer.h"
#include "../Header/Player.h"
#include "../Header/SE.h"
#include "../Header/BossInfo.h"
#include "../Header/FrontDisplay.h"
#include "../Header/GameInput.h"

int Process::processStart()
{
	if (replaymode && (!Player::able/* || scene == S1*/))
	{
		replayend = true;
		replaymode = false;
		gametime = 0;
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			BGLayer::KillOtherLayer(i);
			BGLayer::ubg[i][UBGID_BGMASK].exist = false;
		}
		SelectSystem::ClearAll();
//		FrontDisplay::fdisp.SetState(FDISP_PANEL, 0);
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			Player::p[i].exist = false;
		}
		state = STATE_REPLAY;
		return PTURN;
	}
	if(!Player::able && !replaymode)
	{
		state = STATE_CONTINUE;
		return PTURN;
	}
	else
	{
		frameStart();
		if (state == STATE_START)
		{
			Scripter::scr.Execute(SCR_CONTROL, STATE_START, gametime);
		}
	}

// Script::Stage

	return PGO;
}
