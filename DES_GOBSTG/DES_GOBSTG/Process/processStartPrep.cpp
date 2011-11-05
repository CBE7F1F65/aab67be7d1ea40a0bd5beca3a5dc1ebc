#include "../Header/processPrep.h"

void Process::clearPrep(bool bclearkey)
{
	gametime = 0;
	lasttime = 0;

	ClearAll();
	
	FrontDisplay::fdisp.SetState(FDISP_PANEL, FDISPSTATE_ON);
	FrontDisplay::fdisp.SetState(FDISP_SPELLNAME, FDISPSTATE_OFF);

	if(!bclearkey)
		return;

	hge->Input_SetDIKey(GameInput::KS_UP, false);
	hge->Input_SetDIKey(GameInput::KS_DOWN, false);
	hge->Input_SetDIKey(GameInput::KS_LEFT, false);
	hge->Input_SetDIKey(GameInput::KS_RIGHT, false);
	hge->Input_SetDIKey(GameInput::KS_FIRE, false);
	hge->Input_SetDIKey(GameInput::KS_QUICK, false);
	hge->Input_SetDIKey(GameInput::KS_DRAIN, false);
	hge->Input_SetDIKey(GameInput::KS_SLOW, false);

	GameInput::SetKey(KSI_UP, false);
	GameInput::SetKey(KSI_DOWN, false);
	GameInput::SetKey(KSI_LEFT, false);
	GameInput::SetKey(KSI_RIGHT, false);
	GameInput::SetKey(KSI_FIRE, false);
	GameInput::SetKey(KSI_QUICK, false);
	GameInput::SetKey(KSI_SLOW, false);
	GameInput::SetKey(KSI_DRAIN, false);

	alltime = 0;
}

void Process::startPrep(bool callinit)
{
	replayend = false;
	SetState(STATE_START);

	hge->Resource_SetCurrentDirectory(hge->Resource_MakePath(""));

	BYTE part = 0;
	if (replaymode)
	{
		Replay::rpy.Load(rpyfilename, true);
		seed = Replay::rpy.partinfo[part].seed;
		Player::p.SetChara(Replay::rpy.rpyinfo.usingchara);
		Player::p.SetInitLife(Replay::rpy.rpyinfo.initlife);
		SetStage(Replay::rpy.rpyinfo.stage);
	}
	else
	{
		seed = randt();//timeGetTime();
		SetLastMatchChara(Player::p.ID);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA, lastmatchchara);
	}
	srandt(seed);
	hge->Random_Seed(seed);

	Replay::rpy.InitReplayIndex(replaymode, part);

	clearPrep();
	GameAI::ai.SetAble(false);
	SetInputSwap();

	//set
	Player::p.valueSet();
	musicChange(BResource::bres.playerdata[stage].musicID);

	if(!replaymode)
	{
		ZeroMemory(&Replay::rpy.rpyinfo, sizeof(replayInfo));

		//partinfo
		BYTE part = 0;
//		if(scene < S1200)
//			part = scene / M_STAGENSCENE - 1;
		for(int i=0;i<RPYPARTMAX;i++)
		{
			if(i != part)
			{
				ZeroMemory(&Replay::rpy.partinfo[i], sizeof(partInfo));
			}
			else
			{
				Replay::rpy.partFill(part);
			}
		}
	}
	else
	{
		BYTE part = 0;
	}

	for (int i=0; i<FRAME_STOPINFOMAX; i++)
	{
		SetStop(0, 0);
	}

	framecounter = 0;
	gametime = 0;
	
#if defined __IPHONE
	shootTriger = true;
	drainTriger = false;
	tapTimer = 0;
#endif

	if (callinit)
	{
		Scripter::scr.Execute(SCR_STAGE, SCRIPT_CON_POST, stage);
	}
}