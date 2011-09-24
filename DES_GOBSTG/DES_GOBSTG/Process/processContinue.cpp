#include "../Header/Process.h"
#include "../Header/Bullet.h"
#include "../Header/Player.h"
#include "../Header/Scripter.h"
#include "../Header/BGLayer.h"
#include "../Header/SelectSystem.h"
#include "../Header/Replay.h"

int Process::processContinue()
{
/*

	if(Player::p[0].ncCont >= M_PL_CONTINUEMAX || practicemode)
		goto exit;

	if(!scr.GetIntValue(SCR_RESERVEBEGIN))
	{
		BGLayer::ubg[UBGID_FGPAUSE].exist = true;
		BGLayer::ubg[UBGID_FGPAUSE].SetFlag(FG_PAUSEIN, FGMT_PAUSE);
		scr.SetIntValue(SCR_RESERVEBEGIN+1, M_PL_CONTINUEMAX-Player::p[0].ncCont);

		hge->Channel_Pause(channel);
	}

	scr.Execute(SCR_CONTROL, STATE_CONTINUE, SCRIPT_CON_INIT);
	//60 sec
	int tsec = scr.GetIntValue(SCR_RESERVEBEGIN);
	int tselsys = scr.GetIntValue(SCR_RESERVEBEGIN+2);

	if(hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN))
	{
		BGLayer::ubg[UBGID_FGPAUSE].SetFlag(FG_PAUSEOUT, FGMT_PAUSE);
	}
	else if(hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN))
	{
		selsys[tselsys].select = 1;
	}

	if(tsec == 0x10)
	{
		BGLayer::ubg[UBGID_FGPAUSE].exist = false;
		if(/ *!spellmode &&* / scene < S1200)
		{
			for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
			{
				Player::p[i].valueSet(i, true);
				Player::p[i].ncCont++;

				Bullet::IzeBuild(i, BULLETIZE_FADEOUT, Player::p[i].x, Player::p[i].y);
			}

			hge->Channel_Resume(channel);
			hge->Channel_SetVolume(channel, 0);
			musicSlide(1.5f, -1);
			state = STATE_START;
			return PTURN;
		}
		else
		{
			scene = startscene;
			startPrep();
			/ *
			if(spellmode)
			{
				hge->Channel_Resume(channel);
				hge->Channel_SetVolume(channel, 0);
				musicSlide(1.5f, -1);
			}
			* /
			state = STATE_START;
			return PTURN;
		}
	}
	else if(tsec == 0x11)
	{
exit:
		rpy.partFill(0xff);
		BGLayer::ubg[UBGID_FGPAUSE].exist = false;
//		musicChange(0);
		time = 0;
		state = STATE_OVER;
		return PTURN;
	}

	scr.SetIntValue(SCR_RESERVEBEGIN, tsec);
*/

	return PGO;
}