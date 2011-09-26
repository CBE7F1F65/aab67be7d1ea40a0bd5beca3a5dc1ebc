#include "../Header/processPrep.h"

void Process::clearPrep(bool bclearkey)
{
	gametime = 0;
	lasttime = 0;

	ClearAll();

	BGLayer::ubg[UBGID_BGMASK].valueSetByName(SI_WHITE, M_CLIENT_CENTER_X, M_CLIENT_CENTER_Y, M_CLIENT_WIDTH, M_CLIENT_HEIGHT, 0);
	BGLayer::ubg[UFGID_FGPAUSE].valueSetByName(SI_WHITE, M_CLIENT_CENTER_X, M_CLIENT_CENTER_Y, M_CLIENT_WIDTH, M_CLIENT_HEIGHT, 0);
	
	FrontDisplay::fdisp.SetState(FDISP_PANEL, FDISPSTATE_ON);
	for (int i=0; i<M_PL_ONESETPLAYER; i++)
	{
		FrontDisplay::fdisp.SetState(FDISP_SPELLNAME+i, FDISPSTATE_OFF);
	}

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
		Player::p.SetChara(Replay::rpy.rpyinfo.usingchara[0], Replay::rpy.rpyinfo.usingchara[1], Replay::rpy.rpyinfo.usingchara[2]);
		Player::p.SetInitLife(Replay::rpy.rpyinfo.initlife);
		SetScene(Replay::rpy.rpyinfo.scene);
		SetMatchMode(Replay::rpy.rpyinfo.matchmode);
	}
	else
	{
		seed = randt();//timeGetTime();
		SetLastMatchChara(Player::p.ID, Player::p.ID_sub_1, Player::p.ID_sub_2);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA_1, lastmatchchara[0]);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA_2, lastmatchchara[1]);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA_3, lastmatchchara[2]);
	}
	srandt(seed);
	hge->Random_Seed(seed);

	Replay::rpy.InitReplayIndex(replaymode, part);

	clearPrep();
	if (matchmode == M_MATCHMODE_C2C)
	{
		GameAI::ai.SetAble(true);
	}
	else
	{
		GameAI::ai.SetAble(false);
	}
	SetInputSwap();

	//set
	Player::p.valueSet();
	musicChange(BResource::bres.playerdata[scene].musicID);

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
//		if(scene < S1200)
//		part = data.getStage(scene) - 1;
		if (part)
		{
			Player::p.changePlayerID(Replay::rpy.partinfo[part].nowID);
		}
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
		Scripter::scr.Execute(SCR_STAGE, SCRIPT_CON_POST, scene);
	}
}