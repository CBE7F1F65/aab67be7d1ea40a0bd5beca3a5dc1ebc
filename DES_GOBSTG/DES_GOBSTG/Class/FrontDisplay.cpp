#include "../Header/FrontDisplay.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/BResource.h"
#include "../Header/FrontDisplayName.h"
#include "../Header/processPrep.h"
#include "../Header/BossInfo.h"
#include "../Header/Fontsys.h"
#include "../Header/EffectIDDefine.h"

#define FDISP_LIFEINDI_EMPTY	0
#define FDISP_LIFEINDI_HALF		1
#define FDISP_LIFEINDI_FULL		2

FrontDisplay FrontDisplay::fdisp;

FrontDisplay::FrontDisplay()
{
	ZeroMemory(&panel, sizeof(ftPanelSet));
	ZeroMemory(&info, sizeof(ftInfoSet));
	ZeroMemory(&bignum, sizeof(ftNumSet));
	ZeroMemory(&itemnum, sizeof(ftItemNumSet));
	ZeroMemory(&spellpointnum, sizeof(ftSpellPointNumSet));
	ZeroMemory(&gameinfodisplay, sizeof(ftGameInfoDisplaySet));
	ZeroMemory(&ascii, sizeof(ftAscIISet));
	postprintlist.clear();

	panelstate = FDISPSTATE_OFF;
	spellnamestate = FDISPSTATE_OFF;
	spellnameclass = 0;
	musicstate = FDISPSTATE_OFF;
}

FrontDisplay::~FrontDisplay()
{
}

void FrontDisplay::BuildPostPrint(hgeFont * font, float x, float y, const char * str, int align/* =HGETEXT_CENTER|HGETEXT_MIDDLE */, float scale, float properation, float rotation, float tracking, float spacing)
{
	fdPostPrint _postprint;
	postprintlist.push_back(_postprint);
	fdPostPrint * _ppostprint = &(*(postprintlist.rbegin()));
	if (!font)
	{
		font = info.asciifont;
	}
	_ppostprint->font = font;
	_ppostprint->x = x;
	_ppostprint->y = y;
	_ppostprint->align = align;
	_ppostprint->scale = scale;
	_ppostprint->properation = properation;
	_ppostprint->rotation = rotation;
	_ppostprint->tracking = tracking;
	_ppostprint->spacing = spacing;
	if (str)
	{
		if (strlen(str) >= M_STRMAX)
		{
			char buffer[M_STRMAX];
			strncpy(buffer, str, M_STRMAX);
			strcpy(_ppostprint->str, buffer);
		}
		else
		{
			strcpy(_ppostprint->str, str);
		}
	}
	else
	{
		strcpy(_ppostprint->str, "");
	}
}

void FrontDisplay::RenderPostPrint()
{
	if (postprintlist.size())
	{
		for (list<fdPostPrint>::iterator it=postprintlist.begin(); it!=postprintlist.end(); it++)
		{
			if (it->font)
			{
				it->font->RenderEx(it->x, it->y, it->align, it->str, it->scale, it->properation, it->rotation, it->tracking, it->spacing);
			}
		}
	}
	postprintlist.clear();
}

void FrontDisplay::SetValue(LONGLONG _llval, int _ival, float _fval, bool _bval)
{
	llval = _llval;
	ival = _ival;
	fval = _fval;
	bval = _bval;
}

void FrontDisplay::SetState(BYTE type, BYTE state/* =FDISPSTATE_ON */)
{
	switch (type)
	{
	case FDISP_PANEL:
		panelstate = state;
		break;
	case FDISP_SPELLNAME:
		spellnamestate = state;
		if (state == FDISPSTATE_OFF)
		{
			spellnameclass = 0;
		}
		break;
	case FDISP_MUSICNAME:
		musicstate = state;
		break;
	}
}

void FrontDisplay::OnChangeMusic(int musicID)
{
	SetState(FDISP_MUSICNAME, FDISPSTATE_ON);
	gameinfodisplay.fsMusic.SignUp(BResource::bres.musdata[musicID].musicname, 0.375f);
}

void FrontDisplay::action()
{
	if (musicstate)
	{
		if (musicstate < 180)
		{
			musicstate++;
		}
		else
		{
			SetState(FDISP_MUSICNAME, FDISPSTATE_OFF);
		}
	}
	panel.winindiheadangle += 400;
}

void FrontDisplay::RenderHeadInfo()
{
}

void FrontDisplay::RenderPanel()
{
	float displayscale = Process::mp.infodisplayscale/Process::mp.screenscale;
	if (panelstate)
	{
		char strbuffer[M_STRMAX];

		float scorexoffset = 120;
		float yoffset = 12;
		// Score
		sprintf(strbuffer, "Score");
		SpriteItemManager::FontPrintf(info.asciifont, M_GAMESQUARE_LEFT, M_GAMESQUARE_TOP, HGETEXT_LEFT|HGETEXT_TOP, strbuffer);
		sprintf(strbuffer, "%d", Player::p.nScore);
		SpriteItemManager::FontPrintf(info.asciifont, M_GAMESQUARE_LEFT+scorexoffset, M_GAMESQUARE_TOP+yoffset, HGETEXT_RIGHT|HGETEXT_TOP, strbuffer);

		// HiScore
		sprintf(strbuffer, "High-Score");
		SpriteItemManager::FontPrintf(info.asciifont, M_GAMESQUARE_RIGHT-scorexoffset, M_GAMESQUARE_TOP, HGETEXT_LEFT, strbuffer);
		sprintf(strbuffer, "%d", Player::p.nHiScore);
		SpriteItemManager::FontPrintf(info.asciifont, M_GAMESQUARE_RIGHT, M_GAMESQUARE_TOP+yoffset, HGETEXT_RIGHT|HGETEXT_TOP, strbuffer);

		yoffset += 12;

		// Combo
		spriteData * _spd = SpriteItemManager::CastSprite(panel.combobarindex);
		float fcombogage = ((float)Player::p.nComboGage) / PLAYER_COMBOGAGEMAX;
		float fcombolength = _spd->tex_h*fcombogage;
		SpriteItemManager::SetSpriteTextureRect(panel.combobar, _spd->tex_x, _spd->tex_y+_spd->tex_h-fcombolength, _spd->tex_w, fcombolength);
		SpriteItemManager::SetSpriteHotSpot(panel.combobar, 0, 0);
		SpriteItemManager::RenderSprite(panel.combobar, M_GAMESQUARE_LEFT, M_GAMESQUARE_TOP+yoffset+_spd->tex_h-fcombolength);

		SpriteItemManager::SetSpriteHotSpot(panel.comboframe, 0, 0);
		SpriteItemManager::RenderSprite(panel.comboframe, M_GAMESQUARE_LEFT, M_GAMESQUARE_TOP+yoffset);

		// Info
		SpriteItemManager::SetSpriteHotSpot(panel.infoframe, 0, 0);
		SpriteItemManager::RenderSprite(panel.infoframe, M_GAMESQUARE_LEFT, M_GAMESQUARE_TOP+yoffset);

		yoffset += 4;
		float infoxoffset = 76;
		info.asciifont->SetScale(0.5f);
		int displayhit = Player::p.nComboHit;
		if (Player::p.nComboHit > 0 || Player::p.hitdisplaykeeptimer && Player::p.nLastComboHit > 0)
		{
			if (Player::p.hitdisplaykeeptimer && Player::p.nLastComboHit > 0)
			{
				displayhit = Player::p.nLastComboHit;
				/*
				BYTE alpha = 0xff;
				if (Player::p.hitdisplaykeeptimer < PLAYER_HITDISPLAYFADE)
				{
					alpha = (int)Player::p.hitdisplaykeeptimer * 0xff / PLAYER_HITDISPLAYFADE;
				}
				*/
				info.asciifont->SetColor(0xffff0000);
			}
		}
		sprintf(strbuffer, "%dHit", displayhit);
		SpriteItemManager::FontPrintf(info.asciifont, M_GAMESQUARE_LEFT+infoxoffset, M_GAMESQUARE_TOP+yoffset, HGETEXT_RIGHT|HGETEXT_TOP, strbuffer);

		yoffset += 10;
		LONGLONG displayhitscore = Player::p.nHitScore;
		if (Player::p.hitdisplaykeeptimer && Player::p.nLastComboHit > 0)
		{
			displayhitscore = Player::p.nLastHitScore;
			info.asciifont->SetColor(0xffff0000);
		}
		sprintf(strbuffer, "+%d", displayhitscore);
		SpriteItemManager::FontPrintf(info.asciifont, M_GAMESQUARE_LEFT+76, M_GAMESQUARE_TOP+yoffset, HGETEXT_RIGHT|HGETEXT_TOP, strbuffer);

		info.asciifont->SetColor(0xffffffff);
		info.asciifont->SetScale(1.0f);

		yoffset += 10;
		// Life
		float lifexoffset = M_GAMESQUARE_LEFT+24;
		for (int i=0; i<Player::p.nLife-1; i++)
		{
			SpriteItemManager::RenderSprite(panel.lifeindi[FDISP_LIFEINDI_FULL], lifexoffset+i*16, M_GAMESQUARE_TOP+yoffset);
		}

		yoffset += 32;
		if (Player::p.fScoreMul > 1.0f || Player::p.hitdisplaykeeptimer && Player::p.fLastScoreMul > 1.0f)
		{
			float displayscoremul = Player::p.fScoreMul;

			BYTE alpha = 0xff;
			BYTE r = 0xff;
			BYTE g = 0xff;
			BYTE b = 0xff;
			if (Player::p.bhyper || Player::p.bfreeze)
			{
				g = 0;
			}
			else
			{
				g = b = (Player::p.nComboGage * 0xff / PLAYER_COMBOGAGEMAX);
			}

			if (Player::p.hitdisplaykeeptimer && Player::p.fLastScoreMul > 1.0f)
			{
				displayscoremul = Player::p.fLastScoreMul;

				if (Player::p.hitdisplaykeeptimer < PLAYER_HITDISPLAYFADE)
				{
					alpha = (int)Player::p.hitdisplaykeeptimer * 0xff / PLAYER_HITDISPLAYFADE;
					g = 0;
					b = 0;
				}
			}
			info.asciifont->SetColor(ARGB(alpha, r, g, b));
			sprintf(strbuffer, "x%.2f", displayscoremul);
			info.asciifont->SetScale(1.5f);
			SpriteItemManager::FontPrintf(info.asciifont, M_GAMESQUARE_LEFT+4, M_GAMESQUARE_TOP+yoffset, HGETEXT_LEFT|HGETEXT_TOP, strbuffer);
			info.asciifont->SetColor(0xffffffff);
			info.asciifont->SetScale(1.0f);
		}

		// Temper
		float temperx = M_GAMESQUARE_RIGHT - 136;
		yoffset = 32;

		SpriteItemManager::SetSpriteHotSpot(panel.temperback, 0, 0);
		SpriteItemManager::RenderSprite(panel.temperback, temperx, M_GAMESQUARE_TOP+yoffset);

		_spd = SpriteItemManager::CastSprite(panel.temperbarindex);
		float ftempergage = ((float)Player::p.nTemper) / PLAYER_TEMPERMAX;
		float ftemperlength = _spd->tex_w/2*ftempergage;
		float ftempertexxbegin = _spd->tex_x+_spd->tex_w/2;
		if (ftemperlength < 0)
		{
			ftempertexxbegin += ftemperlength;
		}
		SpriteItemManager::SetSpriteTextureRect(panel.temperbar, ftempertexxbegin, _spd->tex_y, fabsf(ftemperlength), _spd->tex_h);
		SpriteItemManager::SetSpriteHotSpot(panel.temperbar, 0, 0.5f);
		SpriteItemManager::RenderSprite(panel.temperbar, ftempertexxbegin-_spd->tex_x+temperx+4, M_GAMESQUARE_TOP+yoffset);

		SpriteItemManager::SetSpriteHotSpot(panel.temperframe, 0, 0);
		SpriteItemManager::RenderSprite(panel.temperframe, temperx, M_GAMESQUARE_TOP+yoffset);

#ifdef __DEBUG
		switch (Player::p.temperSelf)
		{
		case TEMPERSTATE_NULL:
			strcpy(strbuffer, "N/");
			break;
		case TEMPERSTATE_COLD:
			strcpy(strbuffer, "C/");
			break;
		case TEMPERSTATE_HOT:
			strcpy(strbuffer, "H/");
			break;
		}
		switch (Player::p.temperEnemy)
		{
		case TEMPERSTATE_NULL:
			strcat(strbuffer, "N");
			break;
		case TEMPERSTATE_COLD:
			strcat(strbuffer, "C");
			break;
		case TEMPERSTATE_HOT:
			strcat(strbuffer, "H");
			break;
		}

		sprintf(strbuffer, "%s:%05d", strbuffer, Player::p.nTemper);
		if (Player::p.bhyper)
		{
			strcat(strbuffer, " Hy");
		}
		else if (Player::p.bfreeze)
		{
			strcat(strbuffer, " Fr");
		}

		SpriteItemManager::FontPrintf(info.asciifont, temperx, yoffset+16, HGETEXT_LEFT|HGETEXT_TOP, strbuffer);
#endif

		// Bomb
		SpriteItemManager::RenderSprite(panel.bombback, M_GAMESQUARE_CENTER_X, M_GAMESQUARE_BOTTOM-8);
		for (int i=0; i<PLAYER_BOMBMAX; i++)
		{
			float renderx = M_GAMESQUARE_CENTER_X-(PLAYER_BOMBMAX-i)*16-8;
			float rendery = M_GAMESQUARE_BOTTOM-8;
			if (i < Player::p.nBomb)
			{
				SpriteItemManager::RenderSprite(panel.bombitem, renderx, rendery);
			}
			else if (i < Player::p.nBombMax)
			{
			}
			else
			{
				SpriteItemManager::RenderSprite(panel.bombblock, renderx, rendery);
			}
		}
		SpriteItemManager::RenderSprite(panel.bombframe, M_GAMESQUARE_CENTER_X, M_GAMESQUARE_BOTTOM-8);

		// Border
		SpriteItemManager::RenderSprite(panel.leftedge, M_GAMESQUARE_LEFT-M_GAMESQUARE_EDGE/2, M_GAMESQUARE_CENTER_Y);
		SpriteItemManager::RenderSprite(panel.rightedge, M_GAMESQUARE_RIGHT+M_GAMESQUARE_EDGE/2, M_GAMESQUARE_CENTER_Y);
		SpriteItemManager::RenderSprite(panel.topedge, M_GAMESQUARE_CENTER_X, M_GAMESQUARE_TOP-M_GAMESQUARE_EDGE/2);
		SpriteItemManager::RenderSprite(panel.bottomedge, M_GAMESQUARE_CENTER_X, M_GAMESQUARE_BOTTOM+M_GAMESQUARE_EDGE/2);

		// Costlife Effect
		if (Player::p.flag & PLAYER_COLLAPSE)
		{
			DWORD col = 0xffffffff;
			if (gametime % 2)
			{
				col = 0xffff0000;
			}
			hge->Gfx_RenderLine(M_GAMESQUARE_LEFT, M_GAMESQUARE_TOP, M_GAMESQUARE_RIGHT, M_GAMESQUARE_TOP, col);
			hge->Gfx_RenderLine(M_GAMESQUARE_RIGHT, M_GAMESQUARE_TOP, M_GAMESQUARE_RIGHT, M_GAMESQUARE_BOTTOM, col);
			hge->Gfx_RenderLine(M_GAMESQUARE_RIGHT, M_GAMESQUARE_BOTTOM, M_GAMESQUARE_LEFT, M_GAMESQUARE_BOTTOM, col);
			hge->Gfx_RenderLine(M_GAMESQUARE_LEFT, M_GAMESQUARE_BOTTOM, M_GAMESQUARE_LEFT, M_GAMESQUARE_TOP, col);
		}

		// Music
		if (musicstate)
		{
			float x = M_CLIENT_CENTER_X;
			float y = M_CLIENT_BOTTOM - 32;
			BYTE alpha = 0xff;
			if (musicstate > 120)
			{
				alpha = INTER(0xff, 0, (musicstate-120)/60.0f);
			}
			DWORD col = (alpha<<24)|0xffff00;
			gameinfodisplay.fsMusic.SetColor(col);
			gameinfodisplay.fsMusic.Render(x, y, 0, HGETEXT_CENTER|HGETEXT_TOP);
		}
	}
	if(info.asciifont)
	{
		char strbuffer[M_STRMAX];
#ifdef __DEBUG
		sprintf(strbuffer, 
			"%f %f",
			hge->Timer_GetWorstFPS(35)/M_DEFAULT_RENDERSKIP,
			hge->Timer_GetFPS()/M_DEFAULT_RENDERSKIP);
		SpriteItemManager::FontPrintf(info.asciifont, 
			400,
			465,
			0,
			strbuffer
			);
		sprintf(strbuffer, "%d %d", gametime, hge->System_GetState(HGE_FRAMECOUNTER));
		SpriteItemManager::FontPrintf(info.asciifont, 8, 465, 0, strbuffer);
		sprintf(strbuffer, "%f",	hge->Timer_GetTime());
		SpriteItemManager::FontPrintf(info.asciifont, 540, 1, 0, strbuffer);
#endif
		if (((Process::mp.IsInGame() && Player::p.CheckAble()) || Process::mp.state == STATE_OVER) && info.asciifont)
		{
			int usingtime = gametime;
			if ((Process::mp.state == STATE_CLEAR || Process::mp.state == STATE_OVER) && Process::mp.alltime)
			{
				usingtime = Process::mp.alltime;
			}
			if (Process::mp.replaymode)
			{
				sprintf(strbuffer, "%.2ffps(%.2f)", hge->Timer_GetFPS(35), Process::mp.replayFPS);
			}
			else
			{
				sprintf(strbuffer, "%.2ffps", hge->Timer_GetFPS(35));
			}
//			info.asciifont->Render(M_CLIENT_CENTER_X, M_CLIENT_BOTTOM-14, HGETEXT_CENTER, strfpsbuffer);
			SpriteItemManager::FontPrintf(info.asciifont, M_CLIENT_CENTER_X, M_CLIENT_BOTTOM-14, HGETEXT_CENTER, strbuffer);
			sprintf(strbuffer, "%02d:%02d", usingtime/3600, (usingtime/60)%60);
			SpriteItemManager::FontPrintf(info.asciifont, M_CLIENT_CENTER_X, M_CLIENT_TOP, HGETEXT_CENTER, strbuffer);
		}
	}
}

void FrontDisplay::RenderEnemyX()
{
	if (Enemy::bossindex != 0xff)
	{
		float bossx = Enemy::en[Enemy::bossindex].x;
		float px = Player::p.x;
		float xdiff = fabsf(bossx-px);
		if (xdiff < 48)
		{
			BYTE alpha = INTER(0x60, 0xff, xdiff/48.0);
			info.enemyx->SetColor((alpha<<24)|0xffffff);
		}
		else
		{
			info.enemyx->SetColor(0xffffffff);
		}
		SpriteItemManager::RenderSprite(info.enemyx, bossx, M_CLIENT_BOTTOM);
	}	
}

bool FrontDisplay::Init()
{
	Release();

	info.normalfont = hge->Font_Load(RESDATASTR_WIDEFONTNAME, 32);

	int idx = 0;

	//For SI
	SpriteItemManager::nullIndex = SpriteItemManager::GetIndexByName(SI_NULL);
	SpriteItemManager::yesIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM_YES);
	SpriteItemManager::noIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM_NO);
	SpriteItemManager::cancelIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM_CANCEL);
	SpriteItemManager::confirmIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM);

	//panel
	panel.leftedge = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LEFT_0);
	panel.rightedge = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_RIGHT_0);
	panel.topedge = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_TOP_0);
	panel.bottomedge = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_BOTTOM_0);
	/*
	panel.leftedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LEFT_1);
	panel.rightedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_RIGHT_1);
	panel.topedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_TOP_1);
	panel.bottomedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_BOTTOM_1);
	*/

	panel.spellpoint = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_SPELLPOINT);
//	panel.spellpoint->SetHotSpot(0, 0);
	SpriteItemManager::SetSpriteHotSpot(panel.spellpoint, 0, 0);
	panel.winindi = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_WININDI);
	panel.slotindex = SpriteItemManager::GetIndexByName(SI_FRONTPANEL_SLOT);
	panel.slot = SpriteItemManager::CreateSprite(panel.slotindex);
	panel.slotback = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_SLOTBACK);
//	panel.slotback->SetHotSpot(0, panel.slotback->GetHeight());
	SpriteItemManager::SetSpriteHotSpot(panel.slotback, 0, panel.slotback->GetHeight());
	panel.lifeindi[FDISP_LIFEINDI_EMPTY] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LIFEINDI_EMPTY);
	panel.lifeindi[FDISP_LIFEINDI_HALF] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LIFEINDI_HALF);
	panel.lifeindi[FDISP_LIFEINDI_FULL] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LIFEINDI_FULL);

	panel.combobarindex = SpriteItemManager::GetIndexByName(SI_FRONTPANEL_COMBOBAR);
	panel.combobar = SpriteItemManager::CreateSprite(panel.combobarindex);
	panel.temperbarindex = SpriteItemManager::GetIndexByName(SI_FRONTPANEL_TEMPERBAR);
	panel.temperbar = SpriteItemManager::CreateSprite(panel.temperbarindex);
	panel.comboframe = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_COMBOFRAME);
	panel.temperframe = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_TEMPERFRAME);
	panel.temperback = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_TEMPERBACK);
	panel.infoframe = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_INFOFRAME);
	panel.bombitem = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_BOMB);
	panel.bombframe = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_BOMBFRAME);
	panel.bombback = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_BOMBBACK);
	panel.bombblock = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_BOMBBLOCK);

	for (int i=0; i<FDISP_LIFEINDIMAX; i++)
	{
//		panel.lifeindi[i]->SetHotSpot(panel.lifeindi[i]->GetWidth()/2, 0);
		SpriteItemManager::SetSpriteHotSpot(panel.lifeindi[i], panel.lifeindi[i]->GetWidth()/2, 0);
	}

	/************************************************************************/

	idx = SpriteItemManager::GetIndexByName(SI_FACE_01);
	info.cutin = SpriteItemManager::CreateSprite(idx);
//	info.cutin = SpriteItemManager::CreateSpriteByName(SI_FACE_01);
	info.plchat_1 = SpriteItemManager::CreateSprite(idx);
	info.plchat_2 = SpriteItemManager::CreateSprite(idx);
	info.plchat_3 = SpriteItemManager::CreateSprite(idx);
	info.enchat_1 = SpriteItemManager::CreateSprite(idx);
	info.enchat_2 = SpriteItemManager::CreateSprite(idx);
	info.enchat_3 = SpriteItemManager::CreateSprite(idx);

	info.timecircle = SpriteItemManager::CreateSpriteByName(SI_BOSS_TIMECIRCLE);
	int enemyxsiid = SpriteItemManager::GetIndexByName(SI_ENEMY_X);
	info.enemyx = SpriteItemManager::CreateSprite(enemyxsiid);
//	info.enemyx->SetHotSpot(SpriteItemManager::GetTexW(enemyxsiid)/2, SpriteItemManager::GetTexH(enemyxsiid));
	SpriteItemManager::SetSpriteHotSpot(info.enemyx, SpriteItemManager::GetTexW(enemyxsiid)/2, SpriteItemManager::GetTexH(enemyxsiid));

	info.lifebar = SpriteItemManager::CreateSpriteByName(SI_WHITE);
	info.textbox = SpriteItemManager::CreateSpriteByName(SI_FRONT_TEXT);
	info.demo = SpriteItemManager::CreateSpriteByName(SI_FRONTINFO_DEMO);
	info.loading = SpriteItemManager::CreateSpriteByName(SI_LOADING_WORD);

	//num
	idx = SpriteItemManager::GetIndexByName(SI_ASCIIBIG_0);
	for (int i=0; i<10; i++)
	{
		bignum.num[i] = SpriteItemManager::CreateSprite(idx+i);
	}
	bignum.num_add = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X2B);
	bignum.num_sub = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X2D);
	bignum.num_mul = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X2A);
	bignum.num_div = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X2F);
	bignum.num_mod = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X25);
	bignum.num_dot = SpriteItemManager::CreateSpriteByName(SI_ASCIIBIG_X2E);

	idx = SpriteItemManager::GetIndexByName(SI_DIGITCHARACTER_0);
	for (int i=0; i<30; i++)
	{
		itemnum.itemnum[i] = SpriteItemManager::CreateSprite(idx+i);
	}
	itemnum.bonus = SpriteItemManager::CreateSpriteByName(SI_DIGITCHARACTER_BONUS);

	idx = SpriteItemManager::GetIndexByName(SI_SPELLPOINTDIGITCHARACTER_0);
	for (int i=0; i<22; i++)
	{
		spellpointnum.spellpointnum[i] = SpriteItemManager::CreateSprite(idx+i);
	}

	idx = SpriteItemManager::GetIndexByName(SI_GAMEINFO_0);
	for (int i=0; i<10; i++)
	{
		gameinfodisplay.gameinfodisplay[i] = SpriteItemManager::CreateSprite(idx+i);
	}
	gameinfodisplay.slash = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_SLASH);
	gameinfodisplay.colon = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_COLON);
	gameinfodisplay.space = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_SPACE);
	gameinfodisplay.charge = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_CHARGE);
	gameinfodisplay.chargemax = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_CHARGEMAX);
	gameinfodisplay.gaugefilled = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_GAUGEFILLED);
	gameinfodisplay.gaugelevel = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_GAUGELEVEL);
	gameinfodisplay.caution = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_CAUTION);
	gameinfodisplay.lastlife = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_LASTLIFE);
	gameinfodisplay.lily = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_LILY);
	gameinfodisplay.spellline = SpriteItemManager::CreateSpriteByName(SI_GAMEINFO_SPELLLINE);
	gameinfodisplay.fsMusic.SignUp("");

	//ascii

	idx = SpriteItemManager::GetIndexByName(SI_ASCIIBIG_X20);
	for (int i=0; i<FDISP_ASCII_MAX; i++)
	{
		ascii.ascii[i] = SpriteItemManager::CreateSprite(idx+i);
	}

	//font
	
	float displayscale = Process::mp.infodisplayscale/Process::mp.screenscale;

	info.itemfont = new hgeFont();
	for (int i='0'; i<30+'0'; i++)
	{
		info.itemfont->ChangeSprite(i, itemnum.itemnum[i-'0']);
	}
	info.itemfont->ChangeSprite('b', itemnum.bonus);
	info.itemfont->SetScale(displayscale);
	
	info.spellpointdigitfont = new hgeFont();
	for (int i='0'; i<22+'0'; i++)
	{
		info.spellpointdigitfont->ChangeSprite(i, spellpointnum.spellpointnum[i-'0']);
	}
	info.spellpointdigitfont->SetScale(displayscale);

	info.headdigitfont = new hgeFont();
	for (int i='0'; i<10+'0'; i++)
	{
		info.headdigitfont->ChangeSprite(i, gameinfodisplay.gameinfodisplay[i-'0']);
	}
	info.headdigitfont->ChangeSprite('/', gameinfodisplay.slash);
	info.headdigitfont->ChangeSprite(':', gameinfodisplay.colon);
	info.headdigitfont->ChangeSprite(' ', gameinfodisplay.space);
	info.headdigitfont->SetScale(displayscale);

	info.asciifont = new hgeFont();
	for (int i=FDISP_ASCII_BEGIN; i<=FDISP_ASCII_END; i++)
	{
		info.asciifont->ChangeSprite(i, ascii.ascii[i-FDISP_ASCII_BEGIN]);
	}
	info.asciifont->SetScale(displayscale);

	SetState(FDISP_PANEL, FDISPSTATE_OFF);

	return true;
}

void FrontDisplay::Release()
{
	SpriteItemManager::FreeSprite(&panel.leftedge);
	SpriteItemManager::FreeSprite(&panel.rightedge);
	SpriteItemManager::FreeSprite(&panel.topedge);
	SpriteItemManager::FreeSprite(&panel.bottomedge);

	SpriteItemManager::FreeSprite(&panel.spellpoint);
	SpriteItemManager::FreeSprite(&panel.winindi);
	SpriteItemManager::FreeSprite(&panel.slot);
	SpriteItemManager::FreeSprite(&panel.slotback);

	SpriteItemManager::FreeSprite(&panel.comboframe);
	SpriteItemManager::FreeSprite(&panel.combobar);
	SpriteItemManager::FreeSprite(&panel.infoframe);
	SpriteItemManager::FreeSprite(&panel.temperframe);
	SpriteItemManager::FreeSprite(&panel.temperback);
	SpriteItemManager::FreeSprite(&panel.temperbar);
	SpriteItemManager::FreeSprite(&panel.bombitem);
	SpriteItemManager::FreeSprite(&panel.bombframe);
	SpriteItemManager::FreeSprite(&panel.bombback);
	SpriteItemManager::FreeSprite(&panel.bombblock);
	for (int i=0; i<FDISP_LIFEINDIMAX; i++)
	{
		SpriteItemManager::FreeSprite(&panel.lifeindi[i]);
	}

	if (info.asciifont)
	{
		delete info.asciifont;
		info.asciifont = NULL;
	}
	if (info.itemfont)
	{
		delete info.itemfont;
		info.itemfont = NULL;
	}
	if (info.spellpointdigitfont)
	{
		delete info.spellpointdigitfont;
		info.spellpointdigitfont = NULL;
	}
	if (info.headdigitfont)
	{
		delete info.headdigitfont;
		info.headdigitfont = NULL;
	}
	if (info.normalfont)
	{
		hge->Font_Free(info.normalfont);
		info.normalfont = NULL;
	}
	SpriteItemManager::FreeSprite(&info.cutin);
	SpriteItemManager::FreeSprite(&info.plchat_1);
	SpriteItemManager::FreeSprite(&info.plchat_2);
	SpriteItemManager::FreeSprite(&info.plchat_3);
	SpriteItemManager::FreeSprite(&info.enchat_1);
	SpriteItemManager::FreeSprite(&info.enchat_2);
	SpriteItemManager::FreeSprite(&info.enchat_3);
	SpriteItemManager::FreeSprite(&info.timecircle);
	SpriteItemManager::FreeSprite(&info.enemyx);
	SpriteItemManager::FreeSprite(&info.lifebar);
	SpriteItemManager::FreeSprite(&info.textbox);
	SpriteItemManager::FreeSprite(&info.demo);
	SpriteItemManager::FreeSprite(&info.loading);

	for (int i=0; i<10; i++)
	{
		SpriteItemManager::FreeSprite(&bignum.num[i]);
	}
	SpriteItemManager::FreeSprite(&bignum.num_add);
	SpriteItemManager::FreeSprite(&bignum.num_sub);
	SpriteItemManager::FreeSprite(&bignum.num_mul);
	SpriteItemManager::FreeSprite(&bignum.num_div);
	SpriteItemManager::FreeSprite(&bignum.num_mod);
	SpriteItemManager::FreeSprite(&bignum.num_dot);

	for (int i=0; i<31; i++)
	{
		SpriteItemManager::FreeSprite(&itemnum.itemnum[i]);
	}

	for (int i=0; i<22; i++)
	{
		SpriteItemManager::FreeSprite(&spellpointnum.spellpointnum[i]);
	}

	for (int i=0; i<21; i++)
	{
		SpriteItemManager::FreeSprite(&gameinfodisplay.gameinfodisplay[i]);
	}

	for (int i=0; i<FDISP_ASCII_MAX; i++)
	{
		SpriteItemManager::FreeSprite(&ascii.ascii[i]);
	}
}