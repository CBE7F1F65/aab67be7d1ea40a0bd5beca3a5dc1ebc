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
				GameInput::SetKey(i, KSI_FIRE, false);
				GameInput::SetKey(i, KSI_QUICK, false);
				GameInput::SetKey(i, KSI_SLOW, false);
				GameInput::SetKey(i, KSI_DRAIN, false);
			}
		}*/

		if (!Player::Action())
		{
//			SetState(STATE_CLEAR, -1);
//			return;
			Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_ONEMATCHOVER, SCRIPT_CON_INIT);
			if (Player::IsMatchEnd() >= 0)
			{
				SetState(STATE_CLEAR, -1);
				return;
			}
			else
			{
				Player::ClearRound(Player::round+1);
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
	if(active || !Player::CheckAble() && state != STATE_CONTINUE)
	{
		BGLayer::Action(active);
		Effectsys::Action();
	}
	BGLayer::ActionSpecial();
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