#include "../Header/processPrep.h"

int Process::processPreInitial()
{
	bool rebuilddone = false;
	if(!hge->Resource_AccessFile(hge->System_GetState(HGE_INIFILE)))
	{
rebuild:
		if (rebuilddone)
		{
			errorcode = PROC_ERROR_INIFILE;
			return PQUIT;
		}
		hge->Resource_DeleteFile(hge->System_GetState(HGE_INIFILE));

		hge->	Ini_SetInt(Data::data.translateSection(Data::data.sLinkType(DATAS_HEADER)), Data::data.translateName(Data::data.nLinkType(DATAN_GAMEVERSION)), GAME_VERSION);
		hge->	Ini_SetString(Data::data.translateSection(Data::data.sLinkType(DATAS_HEADER)), Data::data.translateName(Data::data.nLinkType(DATAN_SIGNATURE)), GAME_SIGNATURE);

		hge->	Ini_SetString(RESCONFIGS_RESOURCE, RESCONFIGN_PASSWORD, RESCONFIGDEFAULT_PASSWORD);

		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYUP, RESCONFIGDEFAULT_KEYUP_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYDOWN, RESCONFIGDEFAULT_KEYDOWN_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYLEFT, RESCONFIGDEFAULT_KEYLEFT_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYRIGHT, RESCONFIGDEFAULT_KEYRIGHT_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYFIRE, RESCONFIGDEFAULT_KEYFIRE_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYQUICK, RESCONFIGDEFAULT_KEYQUICK_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYSLOW, RESCONFIGDEFAULT_KEYSLOW_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYDRAIN, RESCONFIGDEFAULT_KEYDRAIN_1);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYPAUSE, RESCONFIGDEFAULT_KEYPAUSE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYSKIP, RESCONFIGDEFAULT_KEYSKIP);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYENTER, RESCONFIGDEFAULT_KEYENTER);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYESCAPE, RESCONFIGDEFAULT_KEYESCAPE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYCAPTURE, RESCONFIGDEFAULT_KEYCAPTURE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_KEYCOMBINESLOWDRAIN, RESCONFIGDEFAULT_KEYCOMBINESLOWDRAIN);

		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYFIRE, RESCONFIGDEFAULT_JOYFIRE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYQUICK, RESCONFIGDEFAULT_JOYQUICK);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYSLOW, RESCONFIGDEFAULT_JOYSLOW);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYDRAIN, RESCONFIGDEFAULT_JOYDRAIN);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYPAUSE, RESCONFIGDEFAULT_JOYPAUSE);
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_JOYCOMBINESLOWDRAIN, RESCONFIGDEFAULT_JOYCOMBINESLOWDRAIN);

		hge->	Ini_SetInt(RESCONFIGS_VOLUME, RESCONFIGN_VOLMUSIC, RESCONFIGDEFAULT_VOLMUSIC);
		hge->	Ini_SetInt(RESCONFIGS_VOLUME, RESCONFIGN_VOLSE, RESCONFIGDEFAULT_VOLSE);

		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_SCREENMODE, RESCONFIGDEFAULT_SCREENMODE);
#if defined __IPHONE
		hge->	Ini_SetFloat(RESCONFIGS_CUSTOM, RESCONFIGN_SCREENSCALE, RESCONFIGDEFAULT_SCREENSCALE);
		hge->	Ini_SetFloat(RESCONFIGS_CUSTOM, RESCONFIGN_INFODISPLAYSCALE, RESCONFIGDEFAULT_INFODISPLAYSCALE);
#endif
		hge->	Ini_SetString(RESCONFIGS_CUSTOM, RESCONFIGN_USERNAME, RESCONFIGDEFAULT_USERNAME);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_RENDERSKIP, RESCONFIGDEFAULT_RENDERSKIP);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA, RESCONFIGDEFAULT_LASTMATCHCHARA);
		
		hge->	Ini_SetInt(RESCONFIGS_CUSTOM, RESCONFIGN_BULLETCOUNTMAX, RESCONFIGDEFAULT_BULLETCOUNTMAX);

		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_DEFAULTWINDOW, RESCONFIGDEFAULT_DEFAULTWINDOW);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_WINDOWLEFT, RESCONFIGDEFAULT_WINDOWLEFT);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_WINDOWTOP, RESCONFIGDEFAULT_WINDOWTOP);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_WINDOWWIDTH, RESCONFIGDEFAULT_WINDOWWIDTH);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_WINDOWHEIGHT, RESCONFIGDEFAULT_WINDOWHEIGHT);
		hge->	Ini_SetInt(RESCONFIGS_CUSTOMWINDOW, RESCONFIGN_WINDOWTOPMOST, RESCONFIGDEFAULT_WINDOWTOPMOST);
#ifdef __DEBUG
		hge->	Ini_SetInt(RESCONFIGS_KEYSETTING, RESCONFIGN_DEBUG_JOYSPEEDUP, RESCONFIGDEFAULT_DEBUG_JOYSPEEDUP);
#endif
#ifdef __DEBUG_LOG
		HGELOG("Succeeded in rebuilding Config File.");
#endif

		rebuilddone = true;
	}

	if (!GameInput::InitInput(hge))
	{
		goto rebuild;
	}

	bgmvol			= hge->Ini_GetInt(RESCONFIGS_VOLUME, RESCONFIGN_VOLMUSIC, RESCONFIGDEFAULT_VOLMUSIC);
	sevol			= hge->Ini_GetInt(RESCONFIGS_VOLUME, RESCONFIGN_VOLSE, RESCONFIGDEFAULT_VOLSE);

	screenmode		= hge->Ini_GetInt(RESCONFIGS_CUSTOM, RESCONFIGN_SCREENMODE, RESCONFIGDEFAULT_SCREENMODE);
	screenscale		= hge->Ini_GetFloat(RESCONFIGS_CUSTOM, RESCONFIGN_SCREENSCALE, RESCONFIGDEFAULT_SCREENSCALE);
	touchmovescale	= hge->Ini_GetFloat(RESCONFIGS_CUSTOM, RESCONFIGN_TOUCHMOVESCALE, RESCONFIGDEFAULT_TOUCHMOVESCALE);
	infodisplayscale= hge->Ini_GetFloat(RESCONFIGS_CUSTOM, RESCONFIGN_INFODISPLAYSCALE, RESCONFIGDEFAULT_INFODISPLAYSCALE);
	strcpy(username, hge->Ini_GetString(RESCONFIGS_CUSTOM, RESCONFIGN_USERNAME, RESCONFIGDEFAULT_USERNAME));
	renderskip		= hge->Ini_GetInt(RESCONFIGS_CUSTOM, RESCONFIGN_RENDERSKIP, RESCONFIGDEFAULT_RENDERSKIP);

	lastmatchchara	= hge->Ini_GetInt(RESCONFIGS_CUSTOM, RESCONFIGN_LASTMATCHCHARA, RESCONFIGDEFAULT_LASTMATCHCHARA);
	
	bulletcountmax		= hge->Ini_GetInt(RESCONFIGS_CUSTOM, RESCONFIGN_BULLETCOUNTMAX, RESCONFIGDEFAULT_BULLETCOUNTMAX);

	//

	if(hge->Ini_GetInt(Data::data.translateSection(Data::data.sLinkType(DATAS_HEADER)), Data::data.translateName(Data::data.nLinkType(DATAN_GAMEVERSION)), -1) != GAME_VERSION)
		goto rebuild;
	
	if(screenmode < 0 || screenmode > 1)
		goto rebuild;
	if (screenscale <= 0 || screenscale > 1) {
		goto rebuild;
	}
	else
	{
#if defined __IPHONE
		Export::clientResetMatrix(screenscale);
#endif
	}

	if (infodisplayscale <= 0 || infodisplayscale > 1.5f) {
		goto rebuild;
	}
	if(bgmvol < 0 || bgmvol > 100)
		goto rebuild;
	if(sevol < 0 || sevol > 100)
		goto rebuild;
	if (renderskip < 0 || renderskip > 3)
	{
		goto rebuild;
	}
	else
	{
		if (renderskip == 0)
		{
			renderskip = 1;
		}
		hge->System_SetState(HGE_RENDERSKIP, renderskip * M_DEFAULT_RENDERSKIP);
	}

#ifdef __DEBUG_LOG
	HGELOG("Succeeded in gaining data from Config File.");
#endif
	hge->Resource_AttachPack(RESLOADING_PCK, Export::GetPassword());
	texInit = hge->Texture_Load(RESLOADING_TEX);
	hge->Resource_RemovePack(RESLOADING_PCK);

	return PGO;
}

int Process::processInit()
{
	gametime++;

	if (gametime == 1)
	{
		int iret = processPreInitial();
		return iret;
	}

	if (texInit.tex)
	{
		hge->Texture_Free(texInit);
		texInit = NULL;
	}
//	hge->Resource_RemovePack(RESLOADING_PCK);

	bool binmode = Export::GetResourceFile();

	Data::data.GetIni();

	if(binmode)
	{
		Data::data.binmode = true;
		Scripter::scr.binmode = true;
#ifdef __RELEASE
//		hge->System_SetState(HGE_LOGFILE, "");
#endif // __RELEASE
	}
	else
	{
		if(!BResource::bres.Fill())
		{
#ifdef __DEBUG_LOG
			HGELOG("Error in Filling Resource Data.");
#endif
			errorcode = PROC_ERROR_RESOURCE;
			return PQUIT;
		}
		if(!Scripter::scr.LoadAll())
		{
			errorcode = PROC_ERROR_SCRIPT;
			return PQUIT;
		}
		if(!BResource::bres.Pack(Scripter::strdesc, BResource::bres.customconstdata))
		{
#ifdef __DEBUG_LOG
			HGELOG("Error in Packing Resource Data.");
#endif
			errorcode = PROC_ERROR_TRANSLATE;
			return PQUIT;
		}
	}
	if (binmode)
	{
		BResource::bres.MallocCustomConst();
	}
	if(!BResource::bres.Gain(Scripter::strdesc, /*binmode?*/BResource::bres.customconstdata/*:NULL*/))
	{
#ifdef __DEBUG_LOG
		HGELOG("Error in Gaining Resource Data.");
#endif
		errorcode = PROC_ERROR_DATA;
		return PQUIT;
	}
#ifdef __DEBUG_LOG
	else
	{
		HGELOG("Succeeded in Gaining Resource Data.");
	}
#endif

	BResource::bres.InitTexinfo();

	if(Scripter::scr.binmode && !Scripter::scr.LoadAll())
	{
		errorcode = PROC_ERROR_SCRIPT;
		return PQUIT;
	}

	for (int i=0; i<DATASTRUCT_PACKAGEMAX; i++)
	{
		if(!BResource::bres.LoadPackage(i))
		{
//			errorcode = PROC_ERROR_PACKAGE;
//			return PQUIT;
		}
	}

	BGLayer::bglayer.Init();

	SE::vol = sevol;
	if(!SE::Initial())
	{
		errorcode = PROC_ERROR_SOUND;
		return PQUIT;
	}

#ifdef __WIN32
#ifndef _DEBUG
	BResource::bres.LoadTexture();
#endif // _DEBUG
#endif // __WIN32

	SpriteItemManager::Init();

	Fontsys::Init(FrontDisplay::fdisp.info.normalfont);
	if(!Effectsys::Init(BResource::bres.tex, RESDATASTR_FOLDER_EFFECTSYS, BResource::bres.resdata.effectsysfilename))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in Initializing Effectsys.", HGELOG_ERRSTR);
#endif
		return false;
	}

#ifdef __DEBUG_LOG
	HGELOG("Succeeded in loading all resources.\n");
#endif

	hge->System_SetState(HGE_WINDOWED, !(bool)screenmode);
	hge->System_SetState(HGE_HIDEMOUSE, (bool)screenmode);

	if(!screenmode)
	{
		Export::clientAdjustWindow();
	}

	Chat::chatitem.Init();

	SelectSystem::ClearAll();

	errorcode = PROC_ERROR_NONE;
	titleselect = 0;

	nowdifflv = DIFFI_EASY;
	practicemode = false;
	replaymode = false;

	playing = false;
	playtimeStart = 0;

	gametime = 0;
	state = STATE_TITLE;
	return PTURN;
}