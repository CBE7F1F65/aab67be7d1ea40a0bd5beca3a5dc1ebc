#include "../Header/processPrep.h"
#include "../Header/GameInput.h"

Process Process::mp;

Process::Process()
{
	active		= false;
	stream		= NULL;
	channel		= NULL;
	latency		= M_LATENCY_NULL;
	matchmode	= 0;
	ZeroMemory(&channelsyncinfo, sizeof(hgeChannelSyncInfo));
	retvalue	= PGO;
	errorcode	= PROC_ERROR_INIFILE;

	musicID = -1;
	screenmode = RESCONFIGDEFAULT_SCREENMODE;
	screenscale = RESCONFIGDEFAULT_SCREENSCALE;
	touchmovescale = RESCONFIGDEFAULT_TOUCHMOVESCALE;
	infodisplayscale = RESCONFIGDEFAULT_INFODISPLAYSCALE;
	bulletcountmax = RESCONFIGDEFAULT_BULLETCOUNTMAX;

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		rendertar[i] = NULL;
		sprendertar[i] = NULL;
		SetShake(i, 0, true);
				
#if defined __IPHONE
		touchMoveID[i] = 0xff;
		shootTriger[i] = false;
		drainTriger[i] = false;
		tapTimer[i] = 0;
#endif
	}
#if defined __IPHONE
	ZeroMemory(touchinfo, sizeof(TouchInfo)*TOUCHPOINT_MAX);
	ZeroMemory(touchdirectmove, sizeof(TouchDirectMove)*M_PL_MATCHMAXPLAYER);
#endif

	texInit = NULL;
}

Process::~Process()
{
}

void Process::Release()
{
	if (!errorcode)
	{
		GameInput::ReleaseInput();

		hge->	Ini_SetInt(RESCONFIGS_VOLUME, RESCONFIGN_VOLMUSIC, bgmvol);
		hge->	Ini_SetInt(RESCONFIGS_VOLUME, RESCONFIGN_VOLSE, sevol);

		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_SCREENMODE, screenmode);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA_1_1, lastmatchchara[0][0]);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA_1_2, lastmatchchara[0][1]);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA_1_3, lastmatchchara[0][2]);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA_2_1, lastmatchchara[1][0]);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA_2_2, lastmatchchara[1][1]);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA_2_3, lastmatchchara[1][2]);

		if(playing)
			DataConnector::addPlayTime();

		if (!Data::data.bin.empty())
		{
			Data::data.SaveBin();
		}
	}

	//
	Fontsys::Release();
	SelectSystem::ClearAll();
	Bullet::Release();
	PlayerBullet::Release();
	Item::Release();
	BossInfo::Release();
	Chat::chatitem.Release();
	EffectSp::Release();
	FrontDisplay::fdisp.Release();
	Enemy::Release();
	SpriteItemManager::Release();
	Effectsys::Release();
	hgeEffectSystem::Release();
	Replay::Release();

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		if (rendertar[i])
		{
			hge->Target_Free(rendertar[i]);
		}
		if (sprendertar[i])
		{
			delete sprendertar[i];
			sprendertar[i] = NULL;
		}
	}
	BResource::bres.FreeTexture();
	if (texInit.tex)
	{
		hge->Texture_Free(texInit);
		texInit = NULL;
	}
	hge->Stream_Free(stream);
}

void Process::ClearAll()
{
	SelectSystem::ClearAll();
	Effectsys::ClearAll();
	BGLayer::Init();
	Enemy::ClearAll();
//	Ghost::ClearAll();
	Target::ClearAll();
	Bullet::ClearItem();
	Item::ClearItem();
	PlayerBullet::ClearItem();
	Beam::ClearItem();
	Chat::chatitem.Clear();
	BossInfo::Clear();
	EffectSp::ClearItem();
	EventZone::Clear();
	GameAI::ClearAll();
	SpriteItemManager::FreeFrontSprite();
	for (int i=0; i<FRAME_STOPINFOMAX; i++)
	{
		stopflag[i] = 0;
		stoptimer[i] = 0;
	}
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		SetShake(i, 0, true);
	}
	replayFPS = 0;

//	matchmode = 0;
	SetInputSwap();

	pauseinit = false;
	frameskip = M_DEFAULT_FRAMESKIP;
}


void Process::musicSlide(float slidetime, int tovol, int pan, float pitch)
{
	if (hge->Channel_IsPlaying(channel))
	{
		hge->Channel_SlideTo(channel, slidetime, tovol < 0 ? bgmvol : tovol, pan, pitch);
	}
}

void Process::SetShake(BYTE playerindex, BYTE round, bool force/* =false */)
{
	if (force || worldshaketimer[playerindex] == 0)
	{
		worldshakeround[playerindex] = round;
		worldshaketimer[playerindex] = worldshakeround[playerindex] * 15;
		worldx[playerindex] = 0;
		worldy[playerindex] = 0;
		worldz[playerindex] = 0;
	}
}

void Process::WorldShake()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		DWORD stopflag = mp.GetStopFlag();
		bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, i, FRAME_STOPFLAG_WORLDSHAKE);
		if (!binstop)
		{
			if (worldshaketimer[i])
			{
				worldshaketimer[i]--;
				if (!worldshaketimer[i])
				{
					worldshakeround[i] = 0;
					worldx[i] = 0;
					worldy[i] = 0;
				}
				else
				{
					int tangle = (worldshakeround[i]*15-worldshaketimer[i]) * 4800;
					worldx[i] = sint(tangle) * 10;
					worldy[i] = cost(tangle) * 10;
				}
			}
		}
	}
}

void Process::musicChange(int ID, bool force)
{
	if (ID < 0)
	{
		hge->Channel_RemoveLoop(channel, &channelsyncinfo);
		ZeroMemory(&channelsyncinfo, sizeof(hgeChannelSyncInfo));
		hge->Channel_Stop(channel);
		musicID = -1;
		return;
	}
	if(!hge->Channel_IsPlaying(channel) || musicID != ID || force)
	{
		if (musicID < 0 || strcmp(BResource::bres.musdata[ID].musicfilename, BResource::bres.musdata[musicID].musicfilename))
		{
			if(stream)
				hge->Stream_Free(stream);
			stream = hge->Stream_Load(BResource::bres.musdata[ID].musicfilename, 0, false);
		}
		musicID = ID;
		channelsyncinfo.startPos = BResource::bres.musdata[musicID].startpos;
		channelsyncinfo.introLength = BResource::bres.musdata[musicID].introlength;
		channelsyncinfo.allLength = BResource::bres.musdata[musicID].alllength;
		if (channel)
		{
			musicSlide(0, bgmvol);
			hge->Channel_Stop(channel);
		}
		if (IsInGame())
		{
			FrontDisplay::fdisp.OnChangeMusic(musicID);
		}
		if (!stream)
		{
			return;
		}
		channel = hge->Stream_Play(stream, true, bgmvol);
		hge->Channel_SetPitch(channel, 1.0f);
		hge->Channel_SetLoop(channel, &channelsyncinfo);
		hge->Channel_SetStartPos(channel, &channelsyncinfo);
	}
}

void Process::SnapShot()
{
	WORD wYear, wMonth, wDay, wHour, wMinute, wSecond, wMilliseconds;
	hge->Timer_GetSystemTime(&wYear, &wMonth, NULL, &wDay, &wHour, &wMinute, &wSecond, &wMilliseconds);
	
	char snapshotfilename[M_PATHMAX];
	strcpy(snapshotfilename, "");
	sprintf(snapshotfilename, "%s%s_%04d_%02d_%02d_%02d_%02d_%02d_%04d.%s",
		BResource::bres.resdata.snapshotfoldername,
		SNAPSHOT_PRIFIX,
		wYear, wMonth, wDay, wHour, wMinute, wSecond, wMilliseconds,
		SNAPSHOT_EXTENSION);
	hge->System_Snapshot(snapshotfilename);
}

char Process::getInputNowChar(bool wide)
{
	char nowchar = -1;
	if(hge->Input_GetDIKey(GameInput::KS_FIRE) && hge->Input_GetDIJoy(GameInput::JS_FIRE))
	{
		hge->Input_SetDIKey(GameInput::KS_FIRE, false);
	}
	if(hge->Input_GetDIKey(GameInput::KS_QUICK) && hge->Input_GetDIJoy(GameInput::JS_QUICK))
	{
		hge->Input_SetDIKey(GameInput::KS_QUICK, false);
	}
	if(hge->Input_GetDIKey(GameInput::KS_SLOW) && hge->Input_GetDIJoy(GameInput::JS_SLOW))
	{
		hge->Input_SetDIKey(GameInput::KS_SLOW, false);
	}
	if(hge->Input_GetDIKey(GameInput::KS_DRAIN) && hge->Input_GetDIJoy(GameInput::JS_DRAIN))
	{
		hge->Input_SetDIKey(GameInput::KS_DRAIN, false);
	}
	if(hge->Input_GetDIKey(GameInput::KS_PAUSE) && hge->Input_GetDIJoy(GameInput::JS_PAUSE))
	{
		hge->Input_SetDIKey(GameInput::KS_PAUSE, false);
	}
#ifdef __DEBUG
	if(hge->Input_GetDIKey(GameInput::KS_SKIP) && hge->Input_GetDIJoy(GameInput::JS_DEBUG_SPEEDUP))
	{
		hge->Input_SetDIKey(GameInput::KS_SKIP, false);
	}
#endif

	if(hge->Input_GetDIKey(DIK_1, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD1, DIKEY_DOWN))
	{
		nowchar = '1';
	}
	else if(hge->Input_GetDIKey(DIK_2, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD2, DIKEY_DOWN))
	{
		nowchar = '2';
	}
	else if(hge->Input_GetDIKey(DIK_3, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD3, DIKEY_DOWN))
	{
		nowchar = '3';
	}
	else if(hge->Input_GetDIKey(DIK_4, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD4, DIKEY_DOWN))
	{
		nowchar = '4';
	}
	else if(hge->Input_GetDIKey(DIK_5, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD5, DIKEY_DOWN))
	{
		nowchar = '5';
	}
	else if(hge->Input_GetDIKey(DIK_6, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD6, DIKEY_DOWN))
	{
		nowchar = '6';
	}
	else if(hge->Input_GetDIKey(DIK_7, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD7, DIKEY_DOWN))
	{
		nowchar = '7';
	}
	else if(hge->Input_GetDIKey(DIK_8, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD8, DIKEY_DOWN))
	{
		nowchar = '8';
	}
	else if(hge->Input_GetDIKey(DIK_9, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD9, DIKEY_DOWN))
	{
		nowchar = '9';
	}
	else if(hge->Input_GetDIKey(DIK_0, DIKEY_DOWN) || hge->Input_GetDIKey(DIK_NUMPAD0, DIKEY_DOWN))
	{
		nowchar = '0';
	}
	else if(hge->Input_GetDIKey(DIK_Q, DIKEY_DOWN))
	{
		nowchar = 'q';
	}
	else if(hge->Input_GetDIKey(DIK_W, DIKEY_DOWN))
	{
		nowchar = 'w';
	}
	else if(hge->Input_GetDIKey(DIK_E, DIKEY_DOWN))
	{
		nowchar = 'e';
	}
	else if(hge->Input_GetDIKey(DIK_R, DIKEY_DOWN))
	{
		nowchar = 'r';
	}
	else if(hge->Input_GetDIKey(DIK_T, DIKEY_DOWN))
	{
		nowchar = 't';
	}
	else if(hge->Input_GetDIKey(DIK_Y, DIKEY_DOWN))
	{
		nowchar = 'y';
	}
	else if(hge->Input_GetDIKey(DIK_U, DIKEY_DOWN))
	{
		nowchar = 'u';
	}
	else if(hge->Input_GetDIKey(DIK_I, DIKEY_DOWN))
	{
		nowchar = 'i';
	}
	else if(hge->Input_GetDIKey(DIK_O, DIKEY_DOWN))
	{
		nowchar = 'o';
	}
	else if(hge->Input_GetDIKey(DIK_P, DIKEY_DOWN))
	{
		nowchar = 'p';
	}
	else if(hge->Input_GetDIKey(DIK_A, DIKEY_DOWN))
	{
		nowchar = 'a';
	}
	else if(hge->Input_GetDIKey(DIK_S, DIKEY_DOWN))
	{
		nowchar = 's';
	}
	else if(hge->Input_GetDIKey(DIK_D, DIKEY_DOWN))
	{
		nowchar = 'd';
	}
	else if(hge->Input_GetDIKey(DIK_F, DIKEY_DOWN))
	{
		nowchar = 'f';
	}
	else if(hge->Input_GetDIKey(DIK_G, DIKEY_DOWN))
	{
		nowchar = 'g';
	}
	else if(hge->Input_GetDIKey(DIK_H, DIKEY_DOWN))
	{
		nowchar = 'h';
	}
	else if(hge->Input_GetDIKey(DIK_J, DIKEY_DOWN))
	{
		nowchar = 'j';
	}
	else if(hge->Input_GetDIKey(DIK_K, DIKEY_DOWN))
	{
		nowchar = 'k';
	}
	else if(hge->Input_GetDIKey(DIK_L, DIKEY_DOWN))
	{
		nowchar = 'l';
	}
	else if(hge->Input_GetDIKey(DIK_Z, DIKEY_DOWN))
	{
		nowchar = 'z';
	}
	else if(hge->Input_GetDIKey(DIK_X, DIKEY_DOWN))
	{
		nowchar = 'x';
	}
	else if(hge->Input_GetDIKey(DIK_C, DIKEY_DOWN))
	{
		nowchar = 'c';
	}
	else if(hge->Input_GetDIKey(DIK_V, DIKEY_DOWN))
	{
		nowchar = 'v';
	}
	else if(hge->Input_GetDIKey(DIK_B, DIKEY_DOWN))
	{
		nowchar = 'b';
	}
	else if(hge->Input_GetDIKey(DIK_N, DIKEY_DOWN))
	{
		nowchar = 'n';
	}
	else if(hge->Input_GetDIKey(DIK_M, DIKEY_DOWN))
	{
		nowchar = 'm';
	}
	else if(hge->Input_GetDIKey(DIK_MINUS, DIKEY_DOWN))
	{
		nowchar = '-';
	}

	if(wide)
	{
		if(hge->Input_GetDIKey(DIK_EQUALS, DIKEY_DOWN))
		{
			nowchar = '=';
		}
		else if(hge->Input_GetDIKey(DIK_LBRACKET, DIKEY_DOWN))
		{
			nowchar = '[';
		}
		else if(hge->Input_GetDIKey(DIK_RBRACKET, DIKEY_DOWN))
		{
			nowchar = ']';
		}
		else if(hge->Input_GetDIKey(DIK_SEMICOLON, DIKEY_DOWN))
		{
			nowchar = ';';
		}
		else if(hge->Input_GetDIKey(DIK_APOSTROPHE, DIKEY_DOWN))
		{
			nowchar = '\'';
		}
		else if(hge->Input_GetDIKey(DIK_GRAVE, DIKEY_DOWN))
		{
			nowchar = '`';
		}
		else if(hge->Input_GetDIKey(DIK_BACKSLASH, DIKEY_DOWN))
		{
			nowchar = '\\';
		}
		else if(hge->Input_GetDIKey(DIK_COMMA, DIKEY_DOWN))
		{
			nowchar = ',';
		}
		else if(hge->Input_GetDIKey(DIK_PERIOD, DIKEY_DOWN))
		{
			nowchar = '.';
		}
		else if(hge->Input_GetDIKey(DIK_SLASH, DIKEY_DOWN))
		{
			nowchar = '/';
		}
		else if(hge->Input_GetDIKey(DIK_SPACE, DIKEY_DOWN))
		{
			nowchar = ' ';
		}
		
		else if(hge->Input_GetDIKey(DIK_ADD, DIKEY_DOWN))
		{
			nowchar = '+';
		}
		else if(hge->Input_GetDIKey(DIK_SUBTRACT, DIKEY_DOWN))
		{
			nowchar = '-';
		}
		else if(hge->Input_GetDIKey(DIK_MULTIPLY, DIKEY_DOWN))
		{
			nowchar = '*';
		}
		else if(hge->Input_GetDIKey(DIK_DIVIDE, DIKEY_DOWN))
		{
			nowchar = '/';
		}
		else if(hge->Input_GetDIKey(DIK_DECIMAL, DIKEY_DOWN))
		{
			nowchar = '.';
		}
	}
	if(hge->Input_GetDIKey(DIK_LSHIFT) || hge->Input_GetDIKey(DIK_RSHIFT))
	{
		if(nowchar >= 'a' && nowchar <= 'z')
		{
			nowchar += 'A' - 'a';
		}
		else if(hge->Input_GetDIKey(DIK_MINUS, DIKEY_DOWN))
		{
			nowchar = '_';
		}
	
		if(wide)
		{
			if(nowchar == '1')
			{
				nowchar = '!';
			}
			else if(nowchar == '2')
			{
				nowchar = '@';
			}
			else if(nowchar == '3')
			{
				nowchar = '#';
			}
			else if(nowchar == '4')
			{
				nowchar = '$';
			}
			else if(nowchar == '5')
			{
				nowchar = '%';
			}
			else if(nowchar == '6')
			{
				nowchar = '^';
			}
			else if(nowchar == '7')
			{
				nowchar = '&';
			}
			else if(nowchar == '8')
			{
				nowchar = '*';
			}
			else if(nowchar == '9')
			{
				nowchar = '(';
			}
			else if(nowchar == '0')
			{
				nowchar = ')';
			}
			else if(nowchar == '=')
			{
				nowchar = '+';
			}
			else if(nowchar == '[')
			{
				nowchar = '{';
			}
			else if(nowchar == ']')
			{
				nowchar = '}';
			}
			else if(nowchar == ';')
			{
				nowchar = ':';
			}
			else if(nowchar == '\'')
			{
				nowchar = '\"';
			}
			else if(nowchar == '`')
			{
				nowchar = '~';
			}
			else if(nowchar == '\\')
			{
				nowchar = '|';
			}
			else if(nowchar == ',')
			{
				nowchar = '<';
			}
			else if(nowchar == '.')
			{
				nowchar = '>';
			}
			else if(nowchar == '/')
			{
				nowchar = '?';
			}
		}
	}
	return nowchar;
}

void Process::SetState(int _state, int _time /* = 0 */)
{
	state = _state;
	if (_time >= 0)
	{
		gametime = _time;
	}
}

void Process::SetScene(BYTE _scene)
{
	scene = _scene;
}

void Process::SetReturnValue(int _retval)
{
	retvalue = _retval;
}

int Process::AccessIP()
{
	DWORD ipx;
	WORD ipport;
	Export::GetLastIP(&ipx, &ipport);
	//TODO:
	return 3;
}

bool Process::SetLatency(int _latency)
{
	latency = _latency;
	if (latency < M_LATENCY_MIN || latency > M_LATENCY_MAX)
	{
		return false;
	}
	return true;
}

void Process::SetMatchMode(BYTE mode)
{
	matchmode = mode;
}

BYTE Process::GetMatchMode()
{
	return matchmode;
}

bool Process::IsInGame()
{
	if (state == STATE_START ||
		state == STATE_PAUSE ||
		state == STATE_CONTINUE ||
		state == STATE_CLEAR)
	{
		return true;
	}
	return false;
}

void Process::SetStop(DWORD _stopflag, int _stoptime)
{
	int useindex = 0;
	int minstoptimer = 0;
	for (int i=0; i<FRAME_STOPINFOMAX; i++)
	{
		if (!stopflag[i])
		{
			useindex = i;
			break;
		}
		if (!minstoptimer || stoptimer[i] < minstoptimer)
		{
			useindex = i;
		}
	}
	stopflag[useindex] = _stopflag;
	stoptimer[useindex] = _stoptime;
}

DWORD Process::GetStopFlag(int index)
{
	if (index >= 0 && index < FRAME_STOPINFOMAX)
	{
		if (stoptimer[index])
		{
			return stopflag[index];
		}
		return 0;
	}
	DWORD _stopflag = 0;
	for (int i=0; i<FRAME_STOPINFOMAX; i++)
	{
		if (stoptimer[i])
		{
			_stopflag |= stopflag[i];
		}
	}
	return _stopflag;	
}

void Process::SetLastMatchChara(BYTE playerindex, WORD ID, WORD ID_sub_1, WORD ID_sub_2)
{
	lastmatchchara[playerindex][0] = ID;
	lastmatchchara[playerindex][1] = ID_sub_1;
	lastmatchchara[playerindex][2] = ID_sub_2;
}

#if defined __IPHONE

void _TranslateTouchPoint(float *x, float *y)
{
	float scaleval = M_CLIENT_HEIGHT / SCREEN_WIDTH;
	float orix = *x;
	float oriy = *y;
	*x = oriy;
	*y = (SCREEN_WIDTH-orix);
//	*x = (oriy-SCREEN_HEIGHT/2)*scaleval+M_CLIENT_WIDTH/2;
//	*y = (SCREEN_WIDTH-orix)*scaleval;
}

void Process::TouchCallback_ButtonDown(float x, float y, int ID)
{
	_TranslateTouchPoint(&x, &y);
	touchinfo[ID].x = x;
	touchinfo[ID].y = y;
	touchinfo[ID].initx = x;
	touchinfo[ID].inity = y;
	touchinfo[ID].lastx = x;
	touchinfo[ID].lasty = y;
	touchinfo[ID].toupdate = false;
	touchinfo[ID].touched = true;
}

void Process::TouchCallback_ButtonUp(float x, float y, int ID)
{
	_TranslateTouchPoint(&x, &y);
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++) {
		if (touchMoveID[i] == ID) {
			touchMoveID[i] = 0xff;
			break;
		}
	}
	ZeroMemory(&(touchinfo[ID]), sizeof(TouchInfo));
}


void Process::TouchCallback_Move(float x, float y, int ID)
{
	_TranslateTouchPoint(&x, &y);
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++) {
		if (ID == touchMoveID[i]) {
			if (touchinfo[ID].toupdate) {
				touchinfo[ID].lastx = touchinfo[ID].x;
				touchinfo[ID].lasty = touchinfo[ID].y;
				touchinfo[ID].toupdate = false;
			}
			touchinfo[ID].x = x;
			touchinfo[ID].y = y;
			break;
		}
	}
}
#endif