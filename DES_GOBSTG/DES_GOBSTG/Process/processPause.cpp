#include "../Header/Process.h"
#include "../Header/Scripter.h"
#include "../Header/SelectSystem.h"
#include "../Header/Player.h"
#include "../Header/SE.h"
#include "../Header/BGLayer.h"
#include "../Header/BossInfo.h"
#include "../Header/FrontDisplay.h"
#include "../Header/GameInput.h"

int Process::processPause()
{
	if (replaymode && replayend)
	{
		if (!alltime)
		{
			alltime = gametime;
		}
		musicChange(-1);
		ClearAll();
		SetState(STATE_OVER);
		return PTURN;
	}
	BYTE tstate = state;
	if(!pauseinit)
	{
		hge->Channel_Pause(channel);

//		scr.d[SCR_RESERVEBEGIN].bfloat = false;
//		scr.SetIntValue(SCR_RESERVEBEGIN, 0x00);
		pauseinit = true;

		if(replaymode)
		{
			if (replayend)
			{
				gametime = 0;
			}
		}
		Scripter::scr.Execute(SCR_CONTROL, STATE_PAUSE, SCRIPT_CON_INIT);
	}
	else
	{
		Scripter::scr.Execute(SCR_CONTROL, STATE_PAUSE, ((replaymode && replayend) ? STATE_TITLE : STATE_START) | 0xff00);
		if (state != STATE_PAUSE)
		{
			for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
			{
				GameInput::gameinput[i].updateActiveInput(true);
			}
			pauseinit = false;
			if (state != STATE_START)
			{
				FrontDisplay::fdisp.SetState(FDISP_PANEL, FDISPSTATE_OFF);
				for (int i=0; i<M_PL_ONESETPLAYER; i++)
				{
					FrontDisplay::fdisp.SetState(FDISP_SPELLNAME_0+i, FDISPSTATE_OFF);
				}
				FrontDisplay::fdisp.SetState(FDISP_MUSICNAME, FDISPSTATE_OFF);
				GameInput::SwapInput(false);
				return PTURN;
			}
			else
			{
				if (musicID >= 0)
				{
					hge->Channel_SetVolume(channel, 0);
					hge->Channel_Resume(channel);
					musicSlide(1.5f, -1);
				}
			}
		}
	}
	/*
	if(GameInput::GetKey(0, KSI_PAUSE, DIKEY_DOWN))
	{
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			BGLayer::ubg[i][UBGID_FGPAUSE].SetFlag(FG_PAUSEOUT, FGMT_PAUSE);
		}
		SelectSystem::ClearAll();
//		scr.SetIntValue(SCR_RESERVEBEGIN, 0xff);
		SE::push(SE_SYSTEM_CANCEL);
		if(replaymode && replayend)
			state = STATE_TITLE;
		else
			state = STATE_START;
		pauseinit = false;
		return PTURN;
	}
	*/
/*
	if(selsys[scr.GetIntValue(SCR_RESERVEBEGIN+1)].sel.size() && hge->Input_GetDIKey(KS_QUICK, DIKEY_UP))
	{
		SelectSystem::ClearAll();
		if(scr.GetIntValue(SCR_RESERVEBEGIN) == 0x10)
		{
			scr.SetIntValue(SCR_RESERVEBEGIN, 0xff);
			if(replaymode && replayend || spellmode && !replaymode && gametime == 0)
				state = STATE_TITLE;
			else
				state = STATE_START;
		}
		else
			scr.SetIntValue(SCR_RESERVEBEGIN, 0x01);
		SE::push(SE_SYSTEM_CANCEL);
//		state = STATE_START;
	}

	if(scr.GetIntValue(SCR_RESERVEBEGIN) == 0xff)
	{
		BGLayer::ubg[UBGID_FGPAUSE].SetFlag(FG_PAUSEOUT, FGMT_PAUSE);
		scr.SetIntValue(SCR_RESERVEBEGIN, 0x100|state);
		state = STATE_PAUSE;
	}
	else if(scr.GetIntValue(SCR_RESERVEBEGIN) >= 0x100 && !BGLayer::ubg[UBGID_FGPAUSE].flag)
	{
		BGLayer::ubg[UBGID_FGPAUSE].exist = false;
		pauseinit = false;
		state = scr.GetIntValue(SCR_RESERVEBEGIN) & 0xff;
		if(state == STATE_START)
		{
			if(gametime == 0)
			{
				scene = startscene;
				startPrep();
				return PTURN;
			}
			hge->Input_SetDIKey(KS_LEFT_(0), (bool)(saveInput & 0x0100));
			hge->Input_SetDIKey(KS_RIGHT_(0), (bool)(saveInput & 0x0200));
			hge->Input_SetDIKey(KS_UP_(0), (bool)(saveInput & 0x0400));
			hge->Input_SetDIKey(KS_DOWN_(0), (bool)(saveInput & 0x0800));
			hge->Input_SetDIKey(KS_FIRE_(0), (bool)(saveInput & 0x1000));
			hge->Input_SetDIKey(KS_QUICK_(0), (bool)(saveInput & 0x2000));
			hge->Input_SetDIKey(KS_CHARGE_(0), (bool)(saveInput & 0x4000));
			hge->Input_SetDIKey(KS_SLOW_(0), (bool)(saveInput & 0x8000));

			hge->Input_SetDIKey(KS_LEFT_(1), (bool)(saveInput & 0x0001));
			hge->Input_SetDIKey(KS_RIGHT_(1), (bool)(saveInput & 0x0002));
			hge->Input_SetDIKey(KS_UP_(1), (bool)(saveInput & 0x0004));
			hge->Input_SetDIKey(KS_DOWN_(1), (bool)(saveInput & 0x0008));
			hge->Input_SetDIKey(KS_FIRE_(1), (bool)(saveInput & 0x0010));
			hge->Input_SetDIKey(KS_QUICK_(1), (bool)(saveInput & 0x0020));
			hge->Input_SetDIKey(KS_CHARGE_(1), (bool)(saveInput & 0x0040));
			hge->Input_SetDIKey(KS_SLOW_(1), (bool)(saveInput & 0x0080));

			if (musicID >= 0)
			{
				hge->Channel_SetVolume(channel, 0);
				hge->Channel_Resume(channel);
				musicSlide(1.5f, -1);
			}

			return PTURN;
		}
		else if(state == STATE_TITLE)
		{
			gametime = 0;
			if(replaymode)
			{
				BGLayer::KillOtherLayer();
				SelectSystem::ClearAll();
//				InfoSelect::Clear();
				BGLayer::ubg[UBGID_BGMASK].exist = false;
				Fdisp.SetState(FDISP_PANEL, 0);
				Player::p[0].exist = false;
				BossInfo::Clear();
				getInput();
				replaymode = false;
				state = STATE_REPLAY;
				return PTURN;
			}
			if(practicemode || spellmode)
			{
				BGLayer::KillOtherLayer();
				SelectSystem::ClearAll();
//				InfoSelect::Clear();
				BGLayer::ubg[UBGID_BGMASK].exist = false;
				Fdisp.SetState(FDISP_PANEL, 0);
				BossInfo::Clear();
				if(spellmode && !replaymode && gametime == 0)
					state = STATE_CONTINUE;
				else
					state = STATE_MATCH_SELECT;
			}
			scene = startscene;
			Player::p[0].exist = false;
//			startPrep();
			return PTURN;
		}
	}
*/
	return PGO;
}
