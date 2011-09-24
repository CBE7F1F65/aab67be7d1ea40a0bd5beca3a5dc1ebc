#include "../header/FrontDisplay.h"
#include "../header/SpriteItemManager.h"
#include "../header/BResource.h"
#include "../header/FrontDisplayName.h"
#include "../header/processPrep.h"
#include "../header/BossInfo.h"
#include "../header/Fontsys.h"
#include "../header/EffectIDDefine.h"

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
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		spellnamestate[i] = FDISPSTATE_OFF;
		spellnameclass[i] = 0;
	}
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
	case FDISP_SPELLNAME_0:
		spellnamestate[0] = state;
		if (state == FDISPSTATE_OFF)
		{
			spellnameclass[0] = 0;
		}
		break;
	case FDISP_SPELLNAME_1:
		spellnamestate[1] = state;
		if (state == FDISPSTATE_OFF)
		{
			spellnameclass[1] = 0;
		}
		break;
	case FDISP_MUSICNAME:
		musicstate = state;
		break;
	}
}

void FrontDisplay::SignUpSpell()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		for (int i=0; i<3; i++)
		{
			gameinfodisplay.fsSpell[j][i].SignUp(BResource::bres.playerdata[Player::p[j].nowID].spellname[i], 0.5f);
		}
	}
}

void FrontDisplay::OnShootCharge(BYTE playerindex, BYTE nowshootingcharge)
{
	BYTE spellclass;
	BYTE spelllevel;
	Player::p[playerindex].GetSpellClassAndLevel(&spellclass, &spelllevel, nowshootingcharge);
	if (spellclass)
	{
		if (spellclass > 3)
		{
			spellclass = 3;
		}
		if (spellnameclass[playerindex] < 3)
		{
			spellnameclass[playerindex] = spellclass;
			SetState(FDISP_SPELLNAME_0+playerindex, FDISPSTATE_ON);
		}
	}
}

void FrontDisplay::OnChangeMusic(int musicID)
{
	SetState(FDISP_MUSICNAME, FDISPSTATE_ON);
	gameinfodisplay.fsMusic.SignUp(BResource::bres.musdata[musicID].musicname, 0.375f);
}

void FrontDisplay::action()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		if (gameinfodisplay.lastlifecountdown[i])
		{
			gameinfodisplay.lastlifecountdown[i]--;
		}
		if (gameinfodisplay.gaugefilledcountdown[i])
		{
			gameinfodisplay.gaugefilledcountdown[i]--;
		}
	}
	if (gameinfodisplay.lilycountdown)
	{
		gameinfodisplay.lilycountdown--;
	}
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		if (spellnamestate[i])
		{
			if (spellnamestate[i] < 180)
			{
				spellnamestate[i]++;
			}

			if (spellnameclass[i] < 3 && spellnamestate[i] >= 180/*
			 ||
							spellnameclass[i] >= 3 && Enemy::bossindex[1-i] == 0xff && spellnamestate[i] >= 60*/
			)
			{
				SetState(FDISP_SPELLNAME_0+i, FDISPSTATE_OFF);
			}
		}
	}
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

void FrontDisplay::RenderHeadInfo(BYTE playerindex)
{
	if (!Player::CheckAble() || !Player::p[playerindex].exist)
	{
		return;
	}
	float displayscale = Process::mp.infodisplayscale/Process::mp.screenscale;
	float yoffset = 24.0f*displayscale;
	float ybottomoffset = 32.0f*displayscale;
	float yoffsetadd = 22.0f*displayscale;
	float px = Player::p[playerindex].x;
	float py = Player::p[playerindex].y;
	DWORD color = 0xffffffff;
	BYTE alpha = 0xff;
	if (Player::p[playerindex].bCharge)
	{
		float tyoffset = yoffset;
		yoffset += yoffsetadd;
		if (py-tyoffset < M_GAMESQUARE_TOP)
		{
			tyoffset = -ybottomoffset;
			ybottomoffset += yoffsetadd;
		}
		BYTE ncharge;
		BYTE nchargemax;
		if (Player::p[playerindex].chargetimer < 16)
		{
			alpha = Player::p[playerindex].chargetimer * 16;
		}
		Player::p[playerindex].GetNCharge(&ncharge, &nchargemax);
		if (Player::p[playerindex].chargetimer % 16 < 8)
		{
			color = (alpha<<24)+0xA0ffA0;
		}
		else
		{
			color = (alpha<<24)+0xffffff;
		}
		gameinfodisplay.charge->SetColor(color);
		SpriteItemManager::RenderSpriteEx(gameinfodisplay.charge, px, py-tyoffset-10*displayscale, 0, displayscale);
		info.headdigitfont->SetColor(color);
		char tbuff[M_STRMAX];
		sprintf(tbuff, "%d / %d", ncharge, nchargemax);
		SpriteItemManager::FontPrintf(info.headdigitfont, px, py-tyoffset-6, HGETEXT_CENTER, tbuff);
	}
	if (gameinfodisplay.lastlifecountdown[playerindex])
	{
		float tyoffset = yoffset;
		yoffset += yoffsetadd;
		if (py-tyoffset < M_GAMESQUARE_TOP)
		{
			tyoffset = -ybottomoffset;
			ybottomoffset += yoffsetadd;
		}
		alpha = 0xff;
		if (gameinfodisplay.lastlifecountdown[playerindex] < 16)
		{
			alpha = gameinfodisplay.lastlifecountdown[playerindex] * 16;
		}
		color = (alpha<<24)+0xffffff;
		gameinfodisplay.caution->SetColor(color);
		SpriteItemManager::RenderSpriteEx(gameinfodisplay.caution, px, py-tyoffset-8*displayscale, 0, displayscale);
		gameinfodisplay.lastlife->SetColor(color);
		SpriteItemManager::RenderSpriteEx(gameinfodisplay.lastlife, px, py-tyoffset, 0, displayscale);
	}
	if (gameinfodisplay.gaugefilledcountdown[playerindex])
	{
		float tyoffset = yoffset;
		yoffset += yoffsetadd;
		if (py-tyoffset < M_GAMESQUARE_TOP)
		{
			tyoffset = -ybottomoffset;
			ybottomoffset += yoffsetadd;
		}
		BYTE ncharge;
		BYTE nchargemax;
		Player::p[playerindex].GetNCharge(&ncharge, &nchargemax);
		alpha = 0xff;
		if (gameinfodisplay.gaugefilledcountdown[playerindex] < 16)
		{
			alpha = gameinfodisplay.gaugefilledcountdown[playerindex] * 16;
		}
		color = (alpha<<24)+0xffffff;
		gameinfodisplay.gaugefilled->SetColor(color);
		SpriteItemManager::RenderSpriteEx(gameinfodisplay.gaugefilled, px, py-tyoffset-10*displayscale, 0, displayscale);
		gameinfodisplay.gaugelevel->SetColor(color);
		SpriteItemManager::RenderSpriteEx(gameinfodisplay.gaugelevel, px-16*displayscale, py-tyoffset, 0, displayscale);
		info.headdigitfont->SetColor(color);
		char tbuff[M_STRMAX];
		sprintf(tbuff, "%d", nchargemax);
		SpriteItemManager::FontPrintf(info.headdigitfont, px+16*displayscale, py-tyoffset-8*displayscale, HGETEXT_CENTER, tbuff);
	}
	if (gameinfodisplay.lilycountdown)
	{
		float tyoffset = yoffset;
		yoffset += yoffsetadd;
		if (py-tyoffset < M_GAMESQUARE_TOP)
		{
			tyoffset = -ybottomoffset;
			ybottomoffset += yoffsetadd;
		}
		alpha = 0xff;
		if (gameinfodisplay.lilycountdown < 16)
		{
			alpha = gameinfodisplay.lilycountdown * 16;
		}
		color = (alpha<<24)+0xffffff;
		gameinfodisplay.caution->SetColor(color);
		SpriteItemManager::RenderSpriteEx(gameinfodisplay.caution, px, py-tyoffset-8*displayscale, 0, displayscale);
		gameinfodisplay.lily->SetColor(color);
		SpriteItemManager::RenderSpriteEx(gameinfodisplay.lily, px, py-tyoffset, 0, displayscale);
	}
}

void FrontDisplay::RenderPanel()
{
	float displayscale = Process::mp.infodisplayscale/Process::mp.screenscale;
	if (panelstate)
	{
		float spellpointx[M_PL_MATCHMAXPLAYER];
		spellpointx[0] = M_GAMESQUARE_RIGHT_0-panel.spellpoint->GetWidth()*displayscale;
		spellpointx[1] = M_GAMESQUARE_LEFT_1;
		float winindix[M_PL_MATCHMAXPLAYER][2];
		float winindiw = panel.winindi->GetWidth();
		float winindih = panel.winindi->GetHeight();
		for (int i=0; i<2; i++)
		{
			winindix[0][i] = M_GAMESQUARE_LEFT_0 + winindiw * (i+1);
			winindix[1][i] = M_GAMESQUARE_RIGHT_1 - winindiw * (i+1);
		}

		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			SpriteItemManager::RenderSpriteEx(panel.spellpoint, spellpointx[i], M_GAMESQUARE_TOP, 0, displayscale);
			spriteData * _spd = SpriteItemManager::CastSprite(panel.combobarindex);
			float fcombogage = ((float)Player::p[i].nComboGage) / PLAYER_COMBOGAGEMAX;
			SpriteItemManager::SetSpriteTextureRect(panel.combobar, _spd->tex_x, _spd->tex_y, _spd->tex_w*fcombogage, _spd->tex_h);
			SpriteItemManager::SetSpriteHotSpot(panel.combobar, 0, 0);
			SpriteItemManager::RenderSpriteEx(panel.combobar, spellpointx[i]+2*displayscale, M_GAMESQUARE_TOP+30*displayscale, 0, displayscale);

			bool usered = true;
			if (Player::p[i].nComboGage < PLAYER_COMBOALERT && Player::p[i].nComboGage > PLAYER_COMBORESET)
			{
				if (gametime % 8 < 4)
				{
					usered = false;
				}
			}
			int nComboHit = Player::p[i].nComboHit;
			char buffer[M_STRITOAMAX];
			sprintf(buffer, "%d%c", nComboHit, '0'+(usered?21:20));
			if (usered)
			{
				for (int j=0; j<strlen(buffer)-1; j++)
				{
					buffer[j] += 10;
				}
			}
			SpriteItemManager::FontPrintf(info.spellpointdigitfont, spellpointx[i]+38*displayscale, M_GAMESQUARE_TOP+16*displayscale, HGETEXT_RIGHT, buffer);
			int nSpellPoint = Player::p[i].nSpellPoint;
			sprintf(buffer, "%06d", nSpellPoint);
			SpriteItemManager::FontPrintf(info.spellpointdigitfont, spellpointx[i]+38*displayscale, M_GAMESQUARE_TOP+16*displayscale, HGETEXT_LEFT, buffer);

			if (Player::p[i].winflag)
			{
				SpriteItemManager::RenderSpriteEx(panel.winindi, winindix[i][0], M_GAMESQUARE_TOP+winindih, ARC(panel.winindiheadangle));
				if (i == Player::IsMatchEnd())
				{
					SpriteItemManager::RenderSpriteEx(panel.winindi, winindix[i][1], M_GAMESQUARE_TOP+winindih, ARC(panel.winindiheadangle));
				}
			}

			_spd = SpriteItemManager::CastSprite(panel.slotindex);
			float fslot = Player::p[i].fChargeMax / PLAYER_CHARGEMAX;
			SpriteItemManager::SetSpriteTextureRect(panel.slot, _spd->tex_x, _spd->tex_y, _spd->tex_w*fslot, _spd->tex_h);
			SpriteItemManager::SetSpriteHotSpot(panel.slot, 0, _spd->tex_h);
			panel.slot->SetColor(0xff808080);
			SpriteItemManager::RenderSprite(panel.slot, M_GAMESQUARE_LEFT_(i)+16, M_GAMESQUARE_BOTTOM);
			fslot = Player::p[i].fCharge / PLAYER_CHARGEMAX;
			SpriteItemManager::SetSpriteTextureRect(panel.slot, _spd->tex_x, _spd->tex_y, _spd->tex_w*fslot, _spd->tex_h);
			SpriteItemManager::SetSpriteHotSpot(panel.slot, 0, _spd->tex_h);
			panel.slot->SetColor(0xffffffff);
			BYTE nCharge;
			Player::p[i].GetNCharge(&nCharge);
			if (nCharge > 0)
			{
				panel.slot->SetColor(0xffffff80);
			}
			SpriteItemManager::RenderSprite(panel.slot, M_GAMESQUARE_LEFT_(i)+16, M_GAMESQUARE_BOTTOM);
			SpriteItemManager::RenderSprite(panel.slotback, M_GAMESQUARE_LEFT_(i), M_GAMESQUARE_BOTTOM);
			float tempx;
			for (int j=0; j<PLAYER_DEFAULTINITLIFE/2; j++)
			{
				tempx = panel.lifeindi[FDISP_LIFEINDI_FULL]->GetWidth() * (j-(PLAYER_DEFAULTINITLIFE/2)/2) + M_GAMESQUARE_CENTER_X_(i);
				if (Player::p[i].nLife > j * 2 + 1)
				{
					SpriteItemManager::RenderSprite(panel.lifeindi[FDISP_LIFEINDI_FULL], tempx, M_GAMESQUARE_TOP);
				}
				else if (Player::p[i].nLife > j * 2)
				{
					SpriteItemManager::RenderSprite(panel.lifeindi[FDISP_LIFEINDI_HALF], tempx, M_GAMESQUARE_TOP);
				}
				else
				{
					SpriteItemManager::RenderSprite(panel.lifeindi[FDISP_LIFEINDI_EMPTY], tempx, M_GAMESQUARE_TOP);
				}
			}
			if (info.spellpointdigitfont)
			{
				char tbuff[M_STRITOAMAX];
				sprintf(tbuff, "%02d", Player::p[i].cardlevel);
				SpriteItemManager::FontPrintf(info.spellpointdigitfont, M_GAMESQUARE_LEFT_(i)+2*displayscale, M_GAMESQUARE_BOTTOM-11*displayscale, HGETEXT_LEFT, tbuff);
				sprintf(tbuff, "%02d", Player::p[i].bosslevel);
				SpriteItemManager::FontPrintf(info.spellpointdigitfont, M_GAMESQUARE_RIGHT_(i)-2*displayscale, M_GAMESQUARE_BOTTOM-11*displayscale, HGETEXT_RIGHT, tbuff);
			}
		}
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			SpriteItemManager::RenderSprite(panel.leftedge[i], M_GAMESQUARE_LEFT_(i)-M_GAMESQUARE_EDGE/2, M_GAMESQUARE_CENTER_Y);
			SpriteItemManager::RenderSprite(panel.rightedge[i], M_GAMESQUARE_RIGHT_(i)+M_GAMESQUARE_EDGE/2, M_GAMESQUARE_CENTER_Y);
			SpriteItemManager::RenderSprite(panel.topedge[i], M_GAMESQUARE_CENTER_X_(i), M_GAMESQUARE_TOP-M_GAMESQUARE_EDGE/2);
			SpriteItemManager::RenderSprite(panel.bottomedge[i], M_GAMESQUARE_CENTER_X_(i), M_GAMESQUARE_BOTTOM+M_GAMESQUARE_EDGE/2);
			if (Player::p[i].flag & PLAYER_COSTLIFE)
			{
				DWORD col = 0xffffffff;
				if (gametime % 2)
				{
					col = 0xffff0000;
				}
				hge->Gfx_RenderLine(M_GAMESQUARE_LEFT_(i), M_GAMESQUARE_TOP, M_GAMESQUARE_RIGHT_(i), M_GAMESQUARE_TOP, col);
				hge->Gfx_RenderLine(M_GAMESQUARE_RIGHT_(i), M_GAMESQUARE_TOP, M_GAMESQUARE_RIGHT_(i), M_GAMESQUARE_BOTTOM, col);
				hge->Gfx_RenderLine(M_GAMESQUARE_RIGHT_(i), M_GAMESQUARE_BOTTOM, M_GAMESQUARE_LEFT_(i), M_GAMESQUARE_BOTTOM, col);
				hge->Gfx_RenderLine(M_GAMESQUARE_LEFT_(i), M_GAMESQUARE_BOTTOM, M_GAMESQUARE_LEFT_(i), M_GAMESQUARE_TOP, col);
			}
		}
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
		char tbuff[M_STRMAX];
#ifdef __DEBUG
		sprintf(tbuff, 
			"%f %f",
			hge->Timer_GetWorstFPS(35)/M_DEFAULT_RENDERSKIP,
			hge->Timer_GetFPS()/M_DEFAULT_RENDERSKIP);
		SpriteItemManager::FontPrintf(info.asciifont, 
			400,
			465,
			0,
			tbuff
			);
		sprintf(tbuff, "%d %d", gametime, hge->System_GetState(HGE_FRAMECOUNTER));
		SpriteItemManager::FontPrintf(info.asciifont, 8, 465, 0, tbuff);
		sprintf(tbuff, "%f",	hge->Timer_GetTime());
		SpriteItemManager::FontPrintf(info.asciifont, 540, 1, 0, tbuff);
#endif
		if (((Process::mp.IsInGame() && Player::CheckAble()) || Process::mp.state == STATE_OVER) && info.asciifont)
		{
			int usingtime = gametime;
			if ((Process::mp.state == STATE_CLEAR || Process::mp.state == STATE_OVER) && Process::mp.alltime)
			{
				usingtime = Process::mp.alltime;
			}
			char strfpsbuffer[M_STRMAX];
			if (Process::mp.replaymode)
			{
				sprintf(strfpsbuffer, "%.2ffps(%.2f)", hge->Timer_GetFPS(35), Process::mp.replayFPS);
			}
			else
			{
				sprintf(strfpsbuffer, "%.2ffps", hge->Timer_GetFPS(35));
			}
			info.asciifont->Render(M_CLIENT_CENTER_X, M_CLIENT_BOTTOM-14, HGETEXT_CENTER, strfpsbuffer);
			sprintf(strfpsbuffer, "%02d:%02d", usingtime/3600, (usingtime/60)%60);
			SpriteItemManager::FontPrintf(info.asciifont, M_CLIENT_CENTER_X, M_CLIENT_TOP, HGETEXT_CENTER, strfpsbuffer);
		}
	}
}

void FrontDisplay::RenderSpellName(BYTE playerindex)
{
	if (spellnamestate[1-playerindex])
	{
		float aimx = M_GAMESQUARE_LEFT_(playerindex) + 120;
		float x;
		if (spellnamestate[1-playerindex] < 45)
		{
			x = INTER(M_GAMESQUARE_LEFT_(playerindex)-160, aimx, spellnamestate[1-playerindex]/45.0f);
		}
		else
		{
			x = aimx;
		}
		BYTE alpha = 0xff;
		BYTE spellclass = spellnameclass[1-playerindex];
		if (spellclass < 3 && spellnamestate[1-playerindex] > 148)
		{
			alpha = INTER(0xff, 0, (spellnamestate[1-playerindex]-148)/32.0f);
		}
		float y = M_GAMESQUARE_TOP + 60;
		gameinfodisplay.spellline->SetColor((alpha<<24)|0xffffff);
		SpriteItemManager::RenderSprite(gameinfodisplay.spellline, x, y);
		DWORD ucol = (alpha<<24)|0xFF0000;
		DWORD dcol = (alpha<<24)|0xFFFFFF;
		gameinfodisplay.fsSpell[1-playerindex][spellclass-1].SetColor(ucol, ucol, dcol, dcol);
		gameinfodisplay.fsSpell[1-playerindex][spellclass-1].Render(x-100, y, FONTSYS_DEFAULT_SHADOW);
	}
}

void FrontDisplay::RenderEnemyX()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		if (Enemy::bossindex[i] != 0xff)
		{
			float bossx = Enemy::en[i][Enemy::bossindex[i]].x;
			float px = Player::p[i].x;
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
/*
		if (BossInfo::flag)
		{
			info.enemyx->Render(Enemy::en[ENEMY_MAINBOSSINDEX].x, 472);
		}*/
	
}

bool FrontDisplay::Init()
{
	Release();

	info.normalfont = hge->Font_Load(BResource::bres.resdata.widefontname, 32);

	int idx = 0;

	//For SI
	SpriteItemManager::nullIndex = SpriteItemManager::GetIndexByName(SI_NULL);
	SpriteItemManager::yesIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM_YES);
	SpriteItemManager::noIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM_NO);
	SpriteItemManager::cancelIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM_CANCEL);
	SpriteItemManager::confirmIndex = SpriteItemManager::GetIndexByName(SI_CONFIRM);

	//panel
	panel.leftedge[0] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LEFT_0);
	panel.rightedge[0] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_RIGHT_0);
	panel.topedge[0] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_TOP_0);
	panel.bottomedge[0] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_BOTTOM_0);
	panel.leftedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LEFT_1);
	panel.rightedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_RIGHT_1);
	panel.topedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_TOP_1);
	panel.bottomedge[1] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_BOTTOM_1);

	panel.spellpoint = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_SPELLPOINT);
//	panel.spellpoint->SetHotSpot(0, 0);
	SpriteItemManager::SetSpriteHotSpot(panel.spellpoint, 0, 0);
	panel.combobarindex = SpriteItemManager::GetIndexByName(SI_FRONTPANEL_COMBOBAR);
	panel.combobar = SpriteItemManager::CreateSprite(panel.combobarindex);
	panel.winindi = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_WININDI);
	panel.slotindex = SpriteItemManager::GetIndexByName(SI_FRONTPANEL_SLOT);
	panel.slot = SpriteItemManager::CreateSprite(panel.slotindex);
	panel.slotback = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_SLOTBACK);
//	panel.slotback->SetHotSpot(0, panel.slotback->GetHeight());
	SpriteItemManager::SetSpriteHotSpot(panel.slotback, 0, panel.slotback->GetHeight());
	panel.lifeindi[FDISP_LIFEINDI_EMPTY] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LIFEINDI_EMPTY);
	panel.lifeindi[FDISP_LIFEINDI_HALF] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LIFEINDI_HALF);
	panel.lifeindi[FDISP_LIFEINDI_FULL] = SpriteItemManager::CreateSpriteByName(SI_FRONTPANEL_LIFEINDI_FULL);
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
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		for (int i=0; i<3; i++)
		{
			gameinfodisplay.fsSpell[j][i].SignUp("");
		}
	}
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
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		SpriteItemManager::FreeSprite(&panel.leftedge[i]);
		SpriteItemManager::FreeSprite(&panel.rightedge[i]);
		SpriteItemManager::FreeSprite(&panel.topedge[i]);
		SpriteItemManager::FreeSprite(&panel.bottomedge[i]);
	}
	SpriteItemManager::FreeSprite(&panel.spellpoint);
	SpriteItemManager::FreeSprite(&panel.combobar);
	SpriteItemManager::FreeSprite(&panel.winindi);
	SpriteItemManager::FreeSprite(&panel.slot);
	SpriteItemManager::FreeSprite(&panel.slotback);
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