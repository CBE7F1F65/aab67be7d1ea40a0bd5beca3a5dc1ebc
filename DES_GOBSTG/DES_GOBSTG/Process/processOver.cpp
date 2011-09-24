#include "../Header/Process.h"
#include "../Header/Scripter.h"
#include "../Header/FrontDisplay.h"
#include "../Header/GameInput.h"
#include "../Header/Replay.h"

int Process::processOver()
{
	//static char savefilename[M_STRMAX];
	gametime++;
	if (gametime == 1)
	{
		if (!replaymode)
		{
			Replay::rpy.Fill();
			Replay::rpy.Save();
//			FrontDisplay::fdisp.SetState(FDISP_PANEL, 0);
		}
		else
		{
			replayend = true;
		}
	}
	Scripter::scr.Execute(SCR_CONTROL, STATE_OVER, gametime);
	if (state != STATE_OVER)
	{
		if (state != STATE_START)
		{
			FrontDisplay::fdisp.SetState(FDISP_PANEL, FDISPSTATE_OFF);
			for (int i=0; i<M_PL_ONESETPLAYER; i++)
			{
				FrontDisplay::fdisp.SetState(FDISP_SPELLNAME_0+i, FDISPSTATE_OFF);
			}
			FrontDisplay::fdisp.SetState(FDISP_MUSICNAME, FDISPSTATE_OFF);
			GameInput::SwapInput(false);
		}
		return PTURN;
	}
	return PGO;
	/*
	
		if(gametime == 1)
		{
			endscene = scene;
	
			BGLayer::KillOtherLayer();
	
			Player::p[0].exist = false;
			BGLayer::ubg[UBGID_BGMASK].exist = false;
			Fdisp.SetState(FDISP_PANEL, 0);
			musicChange(0, true);
	
			strcpy(savefilename, "");
	
			PushKey::SetPushEvent(PUSHKEY_ID_UIUSE_0, KS_LEFT, KS_RIGHT);
			scr.SetIntValue(SCR_RESERVEBEGIN, 0);
			scr.SetIntValue(SCR_RESERVEBEGIN+1, 0);
			scr.SetIntValue(SCR_RESERVEBEGIN+2, 0);
	
			rpy.Fill();
	
			nowdifflv = data.getDiffi(rpy.rpyinfo.startscene);
	
			scr.SetIntValue(SCR_RESERVEBEGIN+3, DataConnector::Insert());
		}
		retvalue = PGO;
		retvalue = scr.Execute(SCR_CONTROL, STATE_OVER, gametime);
		//pushtimer depth sec nowchar insert
		int tdepth = scr.GetIntValue(SCR_RESERVEBEGIN);
		int tsec = scr.GetIntValue(SCR_RESERVEBEGIN+1);
		int tnowchar = scr.GetIntValue(SCR_RESERVEBEGIN+2);
		int tinsert = scr.GetIntValue(SCR_RESERVEBEGIN+3);
		int tselsys = scr.GetIntValue(SCR_RESERVEBEGIN+4);
	
		if(tdepth == 0)
		{
			char scorebuffer[M_STRITOAMAX];
			_i64toa(rpy.rpyinfo.score, scorebuffer, 10);
			char alivenessbuffer[M_STRITOAMAX];
			_i64toa(rpy.rpyinfo.faith, alivenessbuffer, 10);
			char lostbuffer[M_STRITOAMAX];
			sprintf(lostbuffer, "%.2f", rpy.rpyinfo.lost);
			strcat(lostbuffer, "%");
	
			for(list<Selector>::iterator it=selsys[tselsys].sel.begin();it!=selsys[tselsys].sel.end();it++)
			{
				if(it->ID < 0x10)
				{
					if(rpy.rpyinfo.cont)
					{
						if(it->ID == 2)
						{
							SpriteItemManager::SetSprite(SpriteItemManager::GetIndexByName(SI_RESULT_CANNOTSAVE), it->sprite, tex);
							selsys[tselsys].Setup(tselsys, 1, 1, KS_UP, KS_DOWN, KS_FIRE, KS_QUICK);
						}
						else
						{
							if(it->ID == 0)
								it->flag |= SEL_NONACTIVE;
							SpriteItemManager::SetSprite(-1, it->sprite, tex);
						}
					}
				}
				else if((it->ID & 0xf0) == 0x20)
				{
					if(it->ID < strlen(scorebuffer) + 0x20)
					{
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(scorebuffer[it->ID-0x20]-'0'), it->sprite, tex);
					}
					else
					{
						SpriteItemManager::SetSprite(-1, it->sprite, tex);
					}
				}
				else if((it->ID & 0xf0) == 0x30)
				{
					if(it->ID < strlen(alivenessbuffer) + 0x30)
					{
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(alivenessbuffer[it->ID-0x30]-'0'), it->sprite, tex);
					}
					else
					{
						SpriteItemManager::SetSprite(-1, it->sprite, tex);
					}
				}
				else if((it->ID & 0xf0) == 0x40)
				{
					if(it->ID & 1)
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(rpy.rpyinfo.miss%10), it->sprite, tex);
					else
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(rpy.rpyinfo.miss/10), it->sprite, tex);
				}
				else if((it->ID & 0xf0) == 0x50)
				{
					if(it->ID & 1)
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(rpy.rpyinfo.cont%10), it->sprite, tex);
					else
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(rpy.rpyinfo.cont/10), it->sprite, tex);
				}
				else if((it->ID & 0xf0) == 0x60)
				{
					if(it->ID < strlen(lostbuffer) + 0x60)
					{
						if(lostbuffer[it->ID-0x60] == '.')
							lostbuffer[it->ID-0x60] = '0' + SIDIGITUI_POINTPLUS;
						else if(lostbuffer[it->ID-0x60] == '%')
							lostbuffer[it->ID-0x60] = '0' + SIDIGITUI_MODPLUS;
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(lostbuffer[it->ID-0x60]-'0'), it->sprite, tex);
					}
					else
					{
						SpriteItemManager::SetSprite(-1, it->sprite, tex);
					}
				}
				else if((it->ID & 0xf0) == 0x70)
				{
					if(it->ID & 1)
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(rpy.rpyinfo.border%10), it->sprite, tex);
					else
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(rpy.rpyinfo.border/10), it->sprite, tex);
				}
				else if((it->ID & 0xf0) == 0x80)
				{
					if(it->ID & 1)
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(rpy.rpyinfo.get%10), it->sprite, tex);
					else
						SpriteItemManager::SetSprite(SpriteItemManager::digituiIndex+(rpy.rpyinfo.get/10), it->sprite, tex);
				}
			}
			tdepth = 1;
		}
		else if(tdepth == 2)
		{
			InfoSelect::Clear();
			InfoSelect _ifs[13];
	
			strcpy(_ifs[0].info, res.resdata.uistr.score);
			strcat(_ifs[0].info, "|010");
			_ifs[0].linkl(NULL, rpy.rpyinfo.score);
	
			strcpy(_ifs[1].info, res.resdata.uistr.usingchara);
	
			for (int i=0; i<M_PL_ONESETPLAYER;i ++)
			{
				strcpy(_ifs[2+i].info, "|006");
				strcat(_ifs[2+i].info, data.getPlayerName(rpy.rpyinfo.usingchara[i]));
			}
	
			strcpy(_ifs[5].info, res.resdata.uistr.date);
			_ifs[5].linki("|21014", rpy.rpyinfo.year);
			strcat(_ifs[5].info, "/");
			_ifs[5].linki("|21517", rpy.rpyinfo.month);
			strcat(_ifs[5].info, "/");
			_ifs[5].linki("|21820", rpy.rpyinfo.day);
			strcat(_ifs[5].info, " ");
			_ifs[5].linki("|22123", rpy.rpyinfo.hour);
			strcat(_ifs[5].info, ":");
			_ifs[5].linki("|22426", rpy.rpyinfo.minute);
	
			strcpy(_ifs[6].info, res.resdata.uistr.faith);
			_ifs[6].linki("|012", rpy.rpyinfo.faith);
	
			strcpy(_ifs[7].info, res.resdata.uistr.lost);
			_ifs[7].linkf("|012", 0, rpy.rpyinfo.lost);
			strcat(_ifs[7].info, "%");		
	
			strcpy(_ifs[8].info, res.resdata.uistr.misstime);
			_ifs[8].linki("|022", rpy.rpyinfo.miss);
	
			strcpy(_ifs[9].info, res.resdata.uistr.bordertime);
			_ifs[9].linki("|022", rpy.rpyinfo.border);
	
			strcpy(_ifs[10].info, res.resdata.uistr.gettime);
			_ifs[10].linki("|022", rpy.rpyinfo.get);
	
			strcpy(_ifs[11].info, res.resdata.uistr.modeflag);
			strcat(_ifs[11].info, "|010");
			if(rpy.rpyinfo.modeflag & M_RPYMODE_SPELL)
			{
				strcat(_ifs[11].info, res.resdata.uistr.mode_spell);
			}
			else if(rpy.rpyinfo.modeflag & M_RPYMODE_PRACTICE)
			{
				strcat(_ifs[11].info, res.resdata.uistr.mode_practice);
			}
			else
			{
				strcat(_ifs[11].info, res.resdata.uistr.mode_none);
			}
	
			for(int i=0;i<11;i++)
			{
				infoselect.push_back(_ifs[i]);
				infoselect.rbegin()->valueSet(i+10, _ifs[i].info, 50, 90+i*25, INFO_GREEN, SEL_NONACTIVE);
			}
	
			if(!strcmp(savefilename, ""))
			{
				do{
					strcat(savefilename, M_REPLAY_SAVEFILEPRE);
					char buffer[M_STRITOAMAX];
					for(int i=0;i<RPYFILENAME_CONTENTMAX;i++)
					{
						buffer[0] = randt()%26 + 'A';
						buffer[1] = 0;
						strcat(savefilename, buffer);
					}
					strcat(savefilename, ".");
					strcat(savefilename, res.resdata.replayextensionname7);
				}while(_access(hge->Resource_MakePath(savefilename), 00) != -1);
			}
	
			infoselect.push_back(_ifs[12]);
			infoselect.rbegin()->valueSet(2, res.resdata.uistr.confirm, 320, 410, INFO_GREEN);
	
			InfoSelect::Setup(3, 0);
	
			for(int i=0;i<RPYINFO_USERNAMEMAX-1;i++)
			{
				if(!username[i])
				{
					for(int j=i;j<RPYINFO_USERNAMEMAX-1;j++)
						username[j] = ' ';
					break;
				}
			}
			username[RPYINFO_USERNAMEMAX-1] = 0;
	
			tdepth = 3;
		}
		else if(tdepth == 3)
		{
			if(infoselect.size() > 12)
			{
				infoselect.pop_back();
				infoselect.pop_back();
			}
	
			if(hge->Input_GetDIKey(KS_UP, DIKEY_DOWN) || hge->Input_GetDIKey(KS_DOWN, DIKEY_DOWN))
			{
				tnowchar = 0;
			}
	
			tsec = InfoSelect::select;
			if(tsec == 2)
				goto skip1;
	
			PushKey::UpdatePushEvent(PUSHKEY_ID_UIUSE_0);
	
			if(hge->Input_GetDIKey(KS_LEFT, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_SELECT);
				if(tnowchar)
					tnowchar--;
			}
			else if(hge->Input_GetDIKey(KS_RIGHT, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_SELECT);
				if(tnowchar < RPYFILENAME_CONTENTMAX-1)
					tnowchar++;
			}
			if(hge->Input_GetDIKey(KS_ENTER, DIKEY_DOWN) || hge->Input_GetDIJoy(JS_FIRE, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_OK);
				tsec++;
				InfoSelect::select++;
				tnowchar = 0;
				InfoSelect::avoid = true;
				goto skip3;
			}
			if(hge->Input_GetDIKey(DIK_BACKSPACE, DIKEY_DOWN))
			{
				if(tnowchar)
				{
					SE::push(SE_SYSTEM_CANCEL);
					tnowchar--;
					if(!tsec)
						username[tnowchar] = ' ';
					else
						savefilename[tnowchar+11] = ' ';
				}
			}
			if(hge->Input_GetDIKey(DIK_DELETE, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_CANCEL);
				if(!tsec)
					username[tnowchar] = ' ';
				else
					savefilename[tnowchar+11] = ' ';
			}
	
			char nowchar = getInputNowChar(!tsec);
			if(nowchar > 0)
			{
				SE::push(SE_SYSTEM_OK);
				if(!tsec)
					username[tnowchar] = nowchar;
				else
					savefilename[tnowchar+4] = nowchar;
				if(tnowchar < RPYFILENAME_CONTENTMAX-1)
					tnowchar++;
			}
			for(int i=RPYFILENAME_CONTENTMAX-1;i>=0;i--)
			{
				if(username[i] == ' ')
					username[i] = 0;
				else
					break;
			}
	skip1:
			InfoSelect _ifs[2];
	
			strcpy(_ifs[0].info, res.resdata.uistr.username);
			strcat(_ifs[0].info, "|006");
			strcat(_ifs[0].info, username);
			infoselect.push_back(_ifs[0]);
			infoselect.rbegin()->valueSet(0, _ifs[0].info, 345, 90, INFO_RED);
	
			strcpy(_ifs[1].info, res.resdata.uistr.filename);
			strcat(_ifs[1].info, "|010");
			strcat(_ifs[1].info, savefilename);
			infoselect.push_back(_ifs[1]);
			infoselect.rbegin()->valueSet(1, _ifs[1].info, 215, 380, INFO_RED);
	
			if(tsec == 2)
			{
				if(hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN))
				{
					SE::push(SE_SYSTEM_OK);
	
					SetCurrentDirectory(hge->Resource_MakePath(res.resdata.replayfoldername));
					char * buffer;
					char enumfile[M_STRMAX];
					strcpy(enumfile, res.resdata.replayfoldername);
					strcat(enumfile, "*.");
					strcat(enumfile, res.resdata.replayextensionname7);
					buffer = hge->Resource_EnumFiles(enumfile);
					while(buffer != NULL)
					{
						if(!strcmp(buffer, savefilename))
						{
							tdepth = 4;
							break;
						}
						if(!hge->Resource_EnumFiles())
							break;
					}
					SetCurrentDirectory(hge->Resource_MakePath(""));
	
					if(tdepth != 4)
						tdepth = 6;
					else
						InfoSelect::avoid = true;
	
				}
				else if(hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN))
				{
					SE::push(SE_SYSTEM_CANCEL);
					tdepth = 7;
				}
			}
			else
			{
				InfoSelect::avoid = true;
			}
		}
		else if(tdepth == 4 || tdepth == 5)
		{
			InfoSelect::avoid = true;
			hge->Input_SetDIKey(KS_UP, false);
			hge->Input_SetDIKey(KS_DOWN, false);
		}
		else if(tdepth == 6)
		{
	//		rpy.Fill();
			strcpy(rpy.rpyinfo.username, username);
			rpy.Save(savefilename);
	
			tdepth = 7;
		}
		else if(tdepth == 7)
		{
			InfoSelect::Clear();
			if(tinsert < 0)
			{
				gametime = 0;
				if(practicemode)
					state = STATE_MATCH_SELECT;
				else
					state = STATE_TITLE;
				return PTURN;
			}
	
			InfoSelect _ifs[11];
			for(int i=0;i<10;i++)
			{
				DWORD sec;
				sec = data.sLinkType(DATAS_TOP);
				sec = data.sLinkDiff(sec, nowdifflv);
				sec = data.sLinkNum(sec, i+1);
	
				strcpy(_ifs[i].info, "");
				_ifs[i].linki("|10002", i+1);
				strcat(_ifs[i].info, ".|004");
				strcat(_ifs[i].info, data.sRead(DATA_BINFILE, sec, data.nLinkType(DATAN_USERNAME), RESCONFIGDEFAULT_USERNAME));
				_ifs[i].linkl("|11325", data.lRead(DATA_BINFILE, sec, data.nLinkType(DATAN_SCORE), 0));
				BYTE tlaststage = data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_LASTSTAGE), 0);
				strcat(_ifs[i].info, "(");
				switch(tlaststage)
				{
				case 1:
					strcat(_ifs[i].info, M_LASTSTAGESTR_1);
					break;
				case 2:
					strcat(_ifs[i].info, M_LASTSTAGESTR_2);
					break;
				case 3:
					strcat(_ifs[i].info, M_LASTSTAGESTR_3);
					break;
				case 4:
					strcat(_ifs[i].info, M_LASTSTAGESTR_4);
					break;
				case 5:
					strcat(_ifs[i].info, M_LASTSTAGESTR_5);
					break;
				case 6:
					strcat(_ifs[i].info, M_LASTSTAGESTR_6);
					break;
				default:
					strcat(_ifs[i].info, M_LASTSTAGESTR_C);
					break;
				}
				strcat(_ifs[i].info, ")");
				_ifs[i].linki("|13036", data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_FAITH), 0));
				_ifs[i].linki("|23840", data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_TIME_MONTH), 0));
				strcat(_ifs[i].info, "/");
				_ifs[i].linki("|24143", data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_TIME_DAY), 0));
				_ifs[i].linkf("|24550", 2, data.fRead(DATA_BINFILE, sec, data.nLinkType(DATAN_LOST), 0));
				strcat(_ifs[i].info, "%");
	
				infoselect.push_back(_ifs[i]);
				infoselect.rbegin()->valueSet(i == tinsert-1 ? 0 : i+2, _ifs[i].info, 30, 120+24*i, INFO_GREEN, i == tinsert-1 ? SEL_NULL : SEL_NONACTIVE);
			}
	
			if(!tinsert)
				InfoSelect::Setup(0, 0);
			else
			{
				infoselect.push_back(_ifs[10]);
				infoselect.rbegin()->valueSet(1, res.resdata.uistr.confirm, 300, 380, INFO_GREEN);
				InfoSelect::Setup(2, 0);
			}
	
			tdepth = 8;
		}
		else if(tdepth == 8)
		{
			if(!tinsert)
			{
				tsec = 1;
				goto skip2;
			}
	
			for(list<InfoSelect>::iterator it=infoselect.begin();it!=infoselect.end();it++)
			{
				if(it->ID == 0)
				{
					InfoSelect _ifs;
					strcpy(_ifs.info, it->fsinfo.text);
					for(int j=0;j<RPYINFO_USERNAMEMAX-1;j++)
					{
						if(username[j])
							_ifs.info[j+4] = username[j];
						else
						{
							for(int k=j;k<RPYINFO_USERNAMEMAX-1;k++)
								_ifs.info[k+4] = ' ';
							break;
						}
					}
					_ifs.info[11] = ' ';
					infoselect.push_back(_ifs);
					infoselect.rbegin()->valueSet(it->ID, _ifs.info, it->x, it->y, it->coltype, it->flag);
					it = infoselect.erase(it);
					break;
				}
			}
	
			if(hge->Input_GetDIKey(KS_UP, DIKEY_DOWN) || hge->Input_GetDIKey(KS_DOWN, DIKEY_DOWN))
			{
				tnowchar = 0;
			}
			tsec = InfoSelect::select;
	
			PushKey::UpdatePushEvent(PUSHKEY_ID_UIUSE_0);
	
			if(tsec == 1)
			{
				if(hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN))
				{
					SE::push(SE_SYSTEM_CANCEL);
					tsec = 0;
					InfoSelect::select = 0;
					goto skip3;
				}
				goto skip2;
			}
	
			if(hge->Input_GetDIKey(KS_LEFT, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_SELECT);
				if(tnowchar)
					tnowchar--;
			}
			else if(hge->Input_GetDIKey(KS_RIGHT, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_SELECT);
				if(tnowchar <= RPYINFO_USERNAMEMAX-1)
					tnowchar++;
			}
			if(hge->Input_GetDIKey(KS_ENTER, DIKEY_DOWN) || hge->Input_GetDIJoy(JS_FIRE, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_OK);
				tsec++;
				InfoSelect::select++;
				InfoSelect::avoid = true;
				goto skip3;
			}
			if(hge->Input_GetDIKey(DIK_BACKSPACE, DIKEY_DOWN))
			{
				if(tnowchar)
				{
					SE::push(SE_SYSTEM_CANCEL);
					tnowchar--;
					username[tnowchar] = ' ';
				}
			}
			if(hge->Input_GetDIKey(DIK_DELETE, DIKEY_DOWN))
			{
				SE::push(SE_SYSTEM_CANCEL);
				username[tnowchar] = ' ';
			}
	
			char nowchar = getInputNowChar(!tsec);
			if(nowchar > 0)
			{
				SE::push(SE_SYSTEM_OK);
				username[tnowchar] = nowchar;
				if(tnowchar <= RPYINFO_USERNAMEMAX-1)
					tnowchar++;
			}
			for(int it=RPYINFO_USERNAMEMAX-2;it>=0;it--)
			{
				if(username[it] == ' ')
					username[it] = 0;
				else
					break;
			}
	skip2:
			if((tsec == 1 || !tinsert) && hge->Input_GetDIKey(KS_FIRE, DIKEY_DOWN) ||
				tsec == 0 && hge->Input_GetDIJoy(JS_FIRE, DIKEY_DOWN))
			{
				DWORD sec;
				sec = data.sLinkType(DATAS_TOP);
				sec = data.sLinkDiff(sec, nowdifflv);
				sec = data.sLinkNum(sec, tinsert);
	
				data.sWrite(DATA_BINFILE, sec, data.nLinkType(DATAN_USERNAME), username);
	
				SE::push(SE_SYSTEM_OK);
				gametime = 0;
				state = STATE_TITLE;
				return PTURN;
			}
			if(!tsec)
				InfoSelect::avoid = true;
		}
	skip3:
		scr.SetIntValue(SCR_RESERVEBEGIN, tdepth);
		scr.SetIntValue(SCR_RESERVEBEGIN+1, tsec);
		scr.SetIntValue(SCR_RESERVEBEGIN+2, tnowchar);
		return retvalue;*/
	
}