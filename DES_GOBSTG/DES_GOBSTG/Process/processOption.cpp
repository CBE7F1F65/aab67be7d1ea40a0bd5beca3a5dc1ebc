#include "../Header/Process.h"
#include "../Header/Scripter.h"
#include "../Header/SelectSystem.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/FrontDisplayName.h"
#include "../Header/SE.h"
#include "../Header/PushKey.h"
#include "../Header/ConstResource.h"

int Process::processOption()
{
	gametime++;
	/*
	if(gametime == 1)
	{
		scr.SetIntValue(SCR_RESERVEBEGIN, 0);
		scr.SetIntValue(SCR_RESERVEBEGIN+1, 0);
		PushKey::SetPushEvent(PUSHKEY_ID_UIUSE_0, KS_LEFT, KS_RIGHT);
	}
	scr.Execute(SCR_CONTROL, STATE_OPTION, gametime);
	//-> pushtimer sel depth
	int tsel = scr.GetIntValue(SCR_RESERVEBEGIN);
	int tdepth = scr.GetIntValue(SCR_RESERVEBEGIN+1);
	int tselsys = scr.GetIntValue(SCR_RESERVEBEGIN+2);

	tsel = selsys[tselsys].select;
	if(!tdepth)
	{
		if(hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN))
		{
			SE::push(SE_SYSTEM_CANCEL);
			selsys[tselsys].select = selsys[tselsys].nselect-1;
		}
		if((hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN) || hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN)) && tsel == selsys[tselsys].nselect-1)
		{
			SE::push(SE_SYSTEM_CANCEL);
			SelectSystem::ClearAll();
			gametime = 0;
			state = STATE_TITLE;
			return PTURN;
		}

		PushKey::UpdatePushEvent(PUSHKEY_ID_UIUSE_0);

		if(hge->Input_HaveJoy() &&
			(hge->Input_GetDIKey(DIK_TAB, DIKEY_DOWN) ||
			!tsel && (hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN) || hge->Input_GetDIKey(KS_RIGHT, DIKEY_DOWN))))
		{
			SE::push(SE_SYSTEM_OK);
			tdepth = 1;

			for(list<Selector>::iterator it=selsys[tselsys].sel.begin();it!=selsys[tselsys].sel.end();it++)
			{
				if(it->ID < 0x10)
				{
					it->ChangeState(SEL_NONACTIVE|SEL_GRAY, SELOP_SET);
					it->ID += 0x10;
				}
				else if(it->ID < 0x20)
				{
					it->ChangeState(SEL_NONACTIVE|SEL_GRAY, SELOP_UNSET);
					it->ID -= 0x10;
				}
			}
			selsys[tselsys].Setup(tselsys, 6, 0, KS_UP, KS_DOWN, KS_FIRE, KS_QUICK);
		}
		else if(tsel == 1)
		{
			if(hge->Input_GetDIKey(KS_LEFT, DIKEY_DOWN) ||
				hge->Input_GetDIKey(KS_RIGHT, DIKEY_DOWN) ||
				hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_OK);
				screenmode = 1 - screenmode;
				hge->System_SetState(HGE_WINDOWED, !(bool)screenmode);
				hge->System_SetState(HGE_HIDEMOUSE, (bool)screenmode);
			}
		}
		else if(tsel == 2 || tsel == 3)
		{
			int tvol;
			if(tsel == 2)
			{
				tvol = bgmvol;
			}
			else
			{
				tvol = sevol;
				if(!hge->Channel_IsPlaying(SE::se[SE_BOSS_TIMEOUT].chn))
					SE::push(SE_BOSS_TIMEOUT);
			}

			if(hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN))
			{
				tvol += 5;
				if(tvol > 100)
					tvol = 0;
			}
			else if(hge->Input_GetDIKey(KS_LEFT, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_SELECT);
				tvol -= 5;
				if(tvol < 0)
					tvol = 0;
			}
			else if(hge->Input_GetDIKey(KS_RIGHT, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_SELECT);
				tvol += 5;
				if(tvol > 100)
					tvol = 100;
			}

			if(tsel == 2)
			{
				bgmvol = tvol;
			}
			else
			{
				sevol = tvol;
			}
		}
		else if(tsel == 4 && hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN))
		{
			JS_FIRE_(0) = RESCONFIGDEFAULT_JOYFIRE;
			JS_QUICK_(0) = RESCONFIGDEFAULT_JOYQUICK;
			JS_SLOW_(0) = RESCONFIGDEFAULT_JOYSLOW;
			JS_CHARGE_(0) = RESCONFIGDEFAULT_JOYCHARGE;
			JS_PAUSE_(0) = RESCONFIGDEFAULT_JOYPAUSE;
			JS_FIRE_(1) = RESCONFIGDEFAULT_JOYFIRE;
			JS_QUICK_(1) = RESCONFIGDEFAULT_JOYQUICK;
			JS_SLOW_(1) = RESCONFIGDEFAULT_JOYSLOW;
			JS_CHARGE_(1) = RESCONFIGDEFAULT_JOYCHARGE;
			JS_PAUSE_(1) = RESCONFIGDEFAULT_JOYPAUSE;
			screenmode = RESCONFIGDEFAULT_SCREENMODE;
			bgmvol = RESCONFIGDEFAULT_VOLMUSIC;
			sevol = RESCONFIGDEFAULT_VOLSE;
		}
	}
	else
	{
		if (tsel != 5)
		{
			for(int i=0;i<M_JOYKEYMAX;i++)
			{
				if(hge->Input_GetDIJoy(i, DIKEY_DOWN) &&
					!hge->Input_GetDIJoy(JOY_LEFT, DIKEY_DOWN) &&
					!hge->Input_GetDIJoy(JOY_RIGHT, DIKEY_DOWN) &&
					!hge->Input_GetDIJoy(JOY_UP, DIKEY_DOWN) &&
					!hge->Input_GetDIJoy(JOY_DOWN, DIKEY_DOWN))
				{
					SE::push(SE_SYSTEM_OK);

					for (int l=0; l<M_PL_MATCHMAXPLAYER; l++)
					{
						joyKey[l][tsel] = i;
						for(int j = 0;j < 5;j++)
						{
							if(j == tsel)
								continue;
							if(joyKey[l][j] == i)
							{
								for(int k = 0;k < M_JOYKEYMAX;k++)
								{
									if(joyKey[l][0]!=k && 
										joyKey[l][1]!=k && 
										joyKey[l][2]!=k && 
										joyKey[l][3]!=k && 
										joyKey[l][4]!=k)
									{
										joyKey[l][j] = k;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
		if(hge->Input_GetDIKey(KS_ENTER, DIKEY_DOWN) ||
			hge->Input_GetDIKey(DIK_TAB, DIKEY_DOWN) ||
			hge->Input_GetDIKey(KS_LEFT, DIKEY_DOWN) ||
			tsel == 5 && (hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN) || hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN)) ||
			hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN) && !hge->Input_GetDIJoy(JS_QUICK, DIKEY_DOWN) ||
			hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN) && !hge->Input_GetDIJoy(JS_FIRE, DIKEY_DOWN))
		{
			SE::push(SE_SYSTEM_OK);
			tdepth = 0;
			for(list<Selector>::iterator it=selsys[tselsys].sel.begin();it!=selsys[tselsys].sel.end();it++)
			{
				if(it->ID < 0x10)
				{
					it->ChangeState(SEL_NONACTIVE|SEL_GRAY, SELOP_SET);
					it->ID += 0x10;
				}
				else if(it->ID < 0x20)
				{
					it->ChangeState(SEL_NONACTIVE|SEL_GRAY, SELOP_UNSET);
					it->ID -= 0x10;
				}
			}
			selsys[tselsys].Setup(tselsys, 6, 0, KS_UP, KS_DOWN, KS_FIRE, KS_QUICK);

			InfoSelect::Clear();
		}
	}

	SE::vol = sevol;
	hge->Channel_SetVolume(channel, bgmvol);

	for(list<Selector>::iterator it=selsys[tselsys].sel.begin();it!=selsys[tselsys].sel.end();it++)
	{
		if((it->ID & 0xf0) == 0x80)
		{
			int tjk = joyKey[0][(it->ID & 0x0f) >> 1];
			if(it->ID & 1)
				SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+tjk%10, it->sprite, tex);
			else
				SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+tjk/10, it->sprite, tex);
		}
		else if(it->ID == 0x90)
		{
			if (screenmode)
			{
				SpriteItemManager::SetSprite(SpriteItemManager::GetIndexByName(SI_OPTIONGRAPH_FULL), it->sprite, tex);
			}
			else
			{
				SpriteItemManager::SetSprite(SpriteItemManager::GetIndexByName(SI_OPTIONGRAPH_WINDOW), it->sprite, tex);
			}
		}
		else if(it->ID == 0xA0)
		{
		}
		else if((it->ID & 0xf0) == 0xB0 || (it->ID & 0xf0) == 0xC0)
		{
			int tvol;
			if((it->ID & 0xf0) == 0xB0)
			{
				tvol = bgmvol;
			}
			else
			{
				tvol = sevol;
			}
			switch(it->ID & 0x0f)
			{
			case 0x00:
				if(tvol < 100)
					SpriteItemManager::SetSprite(-1, it->sprite, tex);
				else
					SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+1, it->sprite, tex);
				break;
			case 0x01:
				if(tvol < 10)
					SpriteItemManager::SetSprite(-1, it->sprite, tex);
				else
					SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+((tvol / 10) % 10), it->sprite, tex);
				break;
			case 0x02:
				SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(tvol % 10), it->sprite, tex);
				break;
			case 0x03:
				SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+SIDIGITUI_MODPLUS, it->sprite, tex);
				break;
			}
		}

		if(it->ID < 0x10)
		{
			if(it->flag & SEL_ENTER)
			{
				it->ChangeState(SEL_ENTER, SELOP_UNSET);
				it->ChangeState(SEL_OVER, SELOP_SET);
			}
			else if(it->flag & SEL_LEAVE)
			{
				it->ChangeState(SEL_LEAVE, SELOP_UNSET);
				it->ChangeState(SEL_NONE, SELOP_SET);
			}
		}
		else if (it->ID < 0x20 || !(tdepth ^ ((it->ID & 0xf0) != 0x80)))
		{
			it->ChangeState(SEL_NONACTIVE|SEL_GRAY, SELOP_EQUAL);
		}
		else
		{
			it->ChangeState(SEL_NONACTIVE, SELOP_EQUAL);
		}
	}

	scr.SetIntValue(SCR_RESERVEBEGIN, tsel);
	scr.SetIntValue(SCR_RESERVEBEGIN+1, tdepth);
	*/
	return PGO;
}