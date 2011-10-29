#include "../Header/Process.h"
#include "../Header/Scripter.h"
#include "../Header/BGLayer.h"
#include "../Header/SelectSystem.h"
#include "../Header/Player.h"

int Process::processStart()
{
	if (replaymode && (!Player::able/* || scene == S1*/))
	{
		replayend = true;
		replaymode = false;
		gametime = 0;
		BGLayer::bglayer.Release();
		SelectSystem::ClearAll();
//		FrontDisplay::fdisp.SetState(FDISP_PANEL, 0);
		Player::p.exist = false;
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
