#include "../Header/processPrep.h"

bool Process::reload()
{
	hge->Resource_SetCurrentDirectory(hge->Resource_MakePath(""));

	BGLayer::bglayer.Init();
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
	stage = 0;
	area = 0;
	SetShake(0, true);
	if (rendertar)
	{
		hge->Target_Free(rendertar);
	}
	if (sprendertar)
	{
		delete sprendertar;
		sprendertar = NULL;
	}
	rendertar = hge->Target_Create(M_CLIENT_WIDTH, M_CLIENT_HEIGHT, false);

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