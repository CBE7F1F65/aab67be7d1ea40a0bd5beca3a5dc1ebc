#include "../Header/processPrep.h"

void Process::frameEnd()
{
	if(active)
	{
		framecounter++;

		WorldShake();
/*

		if (state == STATE_CLEAR)
		{
			for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
			{
				GameInput::SetKey(KSI_FIRE, false);
				GameInput::SetKey(KSI_QUICK, false);
				GameInput::SetKey(KSI_SLOW, false);
				GameInput::SetKey(KSI_DRAIN, false);
			}
		}*/

		if (!Player::Action())
		{
//			SetState(STATE_CLEAR, -1);
//			return;
			Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_ONEMATCHOVER, SCRIPT_CON_INIT);
			if (Player::IsEnd() >= 0)
			{
				SetState(STATE_CLEAR, -1);
				return;
			}
			else
			{
				clearPrep();
				SetInputSwap();
				return;
			}
		}
		Enemy::Action();
		Bullet::Action();
		EffectSp::Action();
		Beam::Action();
		PlayerBullet::Action();
		PlayerLaser::Action();
		Item::Action();
		EventZone::Action();

		/*
		if(BossInfo::flag)
		{
			if(BossInfo::bossinfo.action())
			{
				time = 0;
			}
		}
		*/
	}
	if(active || !Player::p.CheckAble() && state != STATE_CONTINUE)
	{
		BGLayer::Action(active);
		Effectsys::Action();
	}
	SelectSystem::Action();

	SpriteItemManager::FrontSpriteAction();
	FrontDisplay::fdisp.action();

	SE::play();
	if (active)
	{
		for (int i=0; i<FRAME_STOPINFOMAX; i++)
		{
			if (stopflag[i])
			{
				stoptimer[i]--;
				if (stoptimer[i] == 0)
				{
					stopflag[i] = 0;
				}
			}
		}
	}
	active = false;
}