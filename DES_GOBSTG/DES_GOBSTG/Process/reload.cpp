#include "../Header/processPrep.h"

bool Process::reload()
{
	hge->Resource_SetCurrentDirectory(hge->Resource_MakePath(""));

	BGLayer::Init();
	Enemy::ClearAll();
//	Ghost::ClearAll();
	Target::ClearAll();
	SelectSystem::Init();
	Effectsys::ClearAll();
	Chat::chatitem.Clear();
	BossInfo::Clear();
	Player::Init();
	EventZone::Clear();

	frameskip = M_DEFAULT_FRAMESKIP;
	strcpy(rpyfilename, "");
	Replay::rpy.InitReplayIndex();
	pauseinit = false;
	replaymode = false;
	replayFPS = 0;
	matchmode = 0;
	scene = 0;
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		SetShake(i, 0, true);
		if (rendertar[i])
		{
			hge->Target_Free(rendertar[i]);
		}
		if (sprendertar[i])
		{
			delete sprendertar[i];
			sprendertar[i] = NULL;
		}
		rendertar[i] = hge->Target_Create(M_CLIENT_WIDTH, M_CLIENT_HEIGHT, false);
	}

	GameAI::Init();
	Bullet::Init();
	Enemy::Init();
	Item::Init();
	Beam::Init();
	PlayerBullet::Init();
	SpriteItemManager::Init();
	EffectSp::Init();

	BossInfo::Init();
	InfoQuad::Init();


	FrontDisplay::fdisp.Init();
	Fontsys::Init(FrontDisplay::fdisp.info.normalfont);
	Fontsys::HeatUp();
	Replay::ReleaseEnumReplay();

	Replay::Release();

	GameInput::SwapInput(false);

#ifdef __DEBUG_LOG
	HGELOG("\nCleared up.\n");
#endif

	hge->Resource_SetCurrentDirectory(hge->Resource_MakePath(""));

	return true;
}