#include "../Header/Process.h"
#include "../Header/Replay.h"
#include "../Header/Scripter.h"
#include "../Header/BResource.h"
#include "../Header/SE.h"
#include "../Header/Data.h"
#include "../Header/DataPrinter.h"
#include "../Header/Export.h"
#include "../Header/Player.h"
#include "../Header/PushKey.h"

int Process::processReplay()
{
	gametime++;

	if(gametime == 1)
	{
		ClearAll();
		Replay::GetEnumReplay();
	}

	Scripter::scr.Execute(SCR_CONTROL, STATE_REPLAY, gametime);
	if (state != STATE_REPLAY)
	{
		return PTURN;
	}
/*
	//-> pushtimer page depth index nrpys rpydifflv
	int tdepth = scr.GetIntValue(SCR_RESERVEBEGIN);
	int tindex = scr.GetIntValue(SCR_RESERVEBEGIN+1);
	int trpydifflv = scr.GetIntValue(SCR_RESERVEBEGIN+2);
	int tnrpys = scr.GetIntValue(SCR_RESERVEBEGIN+3);

	if(hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN) && tdepth < 2)
	{
		SE::push(SE_SYSTEM_CANCEL);
		for (int i=0; i<tnrpys; i++)
		{
			Replay::Free(Replay::enumrpy.filename[i]);
		}
		SetCurrentDirectory(hge->Resource_MakePath(""));
		gametime = 0;
		state = STATE_TITLE;
		return PTURN;
	}

	if(!tdepth)
	{
		InfoSelect::Clear();
		InfoSelect _ifs[RPYENUMMAX];
		int i;
		for(i=0; i<tnrpys; i++)
		{
			tindex = i;
			strcpy(_ifs[i].info, Replay::enumrpy[tindex].rpyinfo.username);

			_ifs[i].linki("|20911", Replay::enumrpy[tindex].rpyinfo.year%100);
			strcat(_ifs[i].info, "/");

			_ifs[i].linki("|21214", Replay::enumrpy[tindex].rpyinfo.month);

			strcat(_ifs[i].info, "/");
			_ifs[i].linki("|21517", Replay::enumrpy[tindex].rpyinfo.day);

			strcat(_ifs[i].info, "|021");
			if(Replay::enumrpy[tindex].rpyinfo.modeflag & M_RPYMODE_PRACTICE)
			{
				if(Replay::enumrpy[tindex].rpyinfo.modeflag & M_RPYMODE_SPELL)
				{
					strcat(_ifs[i].info, M_STAGESTR_PRE);
					_ifs[i].linki("|21519", data.getSpellNumber(Replay::enumrpy[tindex].rpyinfo.startscene));
					_ifs[i].coltype = INFO_RED;
				}
				else
				{
					
					switch(Replay::enumrpy[tindex].rpyinfo.difflv)
					{
					case M_DIFFI_EASY:
						strcat(_ifs[i].info, M_DIFFISTR_EASY);
						break;
					case M_DIFFI_NORMAL:
						strcat(_ifs[i].info, M_DIFFISTR_NORMAL);
						break;
					case M_DIFFI_HARD:
						strcat(_ifs[i].info, M_DIFFISTR_HARD);
						break;
					}
					
					strcat(_ifs[i].info, "-");
					switch(data.getStage(Replay::enumrpy[tindex].rpyinfo.startscene))
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
					}
					_ifs[i].coltype = INFO_YELLOW;
				}
			}
			else
			{
				switch(Replay::enumrpy[tindex].rpyinfo.difflv)
				{
				case M_DIFFI_EASY:
					strcat(_ifs[i].info, M_DIFFISTR_EASY);
					break;
				case M_DIFFI_NORMAL:
					strcat(_ifs[i].info, M_DIFFISTR_NORMAL);
					break;
				case M_DIFFI_HARD:
					strcat(_ifs[i].info, M_DIFFISTR_HARD);
					break;
				case M_DIFFI_DESTINY:
					strcat(_ifs[i].info, M_DIFFISTR_DESTINY);
					break;
				default:
					strcat(_ifs[i].info, M_DIFFISTR_EXTRA);
					break;
				}
				_ifs[i].coltype = INFO_GREEN;
			}
			_ifs[i].linkl("|12840", Replay::enumrpy[tindex].rpyinfo.score);

			strcat(_ifs[i].info, "|041");
			strcat(_ifs[i].info, Replay::enumrpy.filename[tindex]);
			_ifs[i].info[strlen(_ifs[i].info) - 4] = 0;

			infoselect.push_back(_ifs[i]);
			infoselect.rbegin()->valueSet(i, _ifs[i].info, 30, 120+i*22, _ifs[i].coltype);
		}

		InfoSelect::Setup(i, InfoSelect::select);
		InfoSelect::SetPageNum(12, 87, 22);
		if(InfoSelect::select >= i)
			InfoSelect::select = i - 1;

		tdepth = 1;
	}
	if(tdepth == 1)
	{
		tindex = InfoSelect::select;
		trpydifflv = Replay::enumrpy[tindex].rpyinfo.difflv;

		PushKey::UpdatePushEvent(PUSHKEY_ID_UIUSE_0);

		if(hge->Input_GetDIKey(KS_LEFT, DIKEY_DOWN))
		{
			SE::push(SE_SYSTEM_SELECT);
			InfoSelect::select -= 10;
			if (InfoSelect::select < 0)
			{
				InfoSelect::select = 0;
			}
		}
		else if(hge->Input_GetDIKey(KS_RIGHT, DIKEY_DOWN))
		{
			SE::push(SE_SYSTEM_SELECT);
			InfoSelect::select += 10;
			if (InfoSelect::select >= tnrpys)
			{
				InfoSelect::select = tnrpys-1;
			}
		}

		if(InfoSelect::complete)
		{
			tdepth = 2;
		}
	}
	if(tdepth == 2)
	{
		InfoSelect::Clear();
		InfoSelect _ifs[24];
		if(!(Replay::enumrpy[tindex].rpyinfo.modeflag & M_RPYMODE_SPELL))
		{
			switch (Replay::enumrpy[tindex].rpyinfo.difflv)
			{
			case M_DIFFI_EASY:
				strcpy(_ifs[23].info, M_DIFFISTR_EASY);
				break;
			case M_DIFFI_NORMAL:
				strcpy(_ifs[23].info, M_DIFFISTR_NORMAL);
				break;
			case M_DIFFI_HARD:
				strcpy(_ifs[23].info, M_DIFFISTR_HARD);
				break;
			case M_DIFFI_DESTINY:
				strcpy(_ifs[23].info, M_DIFFISTR_DESTINY);
				break;
			default:
				strcpy(_ifs[23].info, M_DIFFISTR_EXTRA);
				break;
			}
			_ifs[23].Build(23, _ifs[23].info, 280, 90, INFO_RED, SEL_NONACTIVE);

			for (int i=0; i<7; i++)
			{
				strcpy(_ifs[i].info, M_STAGESTR_STAGEPRE);
			}
			strcat(_ifs[0].info, M_LASTSTAGESTR_1);
			strcat(_ifs[1].info, M_LASTSTAGESTR_2);
			strcat(_ifs[2].info, M_LASTSTAGESTR_3);
			strcat(_ifs[3].info, M_LASTSTAGESTR_4);
			strcat(_ifs[4].info, M_LASTSTAGESTR_5);
			strcat(_ifs[5].info, M_LASTSTAGESTR_6);
			strcat(_ifs[6].info, M_LASTSTAGESTR_EX);
			for(int i=0;i<7;i++)
			{
				_ifs[i].flag = SEL_NONACTIVE | SEL_GRAY;
				_ifs[i].coltype = INFO_GRAY;
			}
			if(Replay::enumrpy[tindex].rpyinfo.difflv < M_DIFFI_EXTRA_START)
			{
				for(int i=0;i<RPYPARTMAX;i++)
				{
					if(Replay::enumrpy[tindex].partinfo[i].offset && Replay::enumrpy[tindex].partinfo[i].offset != Replay::enumrpy[tindex].rpyinfo.offset + 1)
					{
						int j;
						for(j=i+1;j<RPYPARTMAX;j++)
						{
							if(Replay::enumrpy[tindex].partinfo[j].offset)
							{
								_ifs[i].linkl("|21020", Replay::enumrpy[tindex].partinfo[j].nowscore);
								break;
							}
						}
						if(j == RPYPARTMAX)
							_ifs[i].linkl("|21020", Replay::enumrpy[tindex].rpyinfo.score);
						_ifs[i].flag = SEL_NULL;
						_ifs[i].coltype = INFO_GREEN;
					}
				}
			}
			else
			{
				int i = 6;//8+Replay::enumrpy[tindex].rpyinfo.difflv-3;
				_ifs[i].linkl("|21020", Replay::enumrpy[tindex].rpyinfo.score);
				_ifs[i].flag = SEL_NULL;
				_ifs[i].coltype = INFO_GREEN;
			}
			for(int i=0;i<7;i++)
			{
				infoselect.push_back(_ifs[i]);
				infoselect.rbegin()->valueSet(i, _ifs[i].info, 390, 120+22*i, _ifs[i].coltype, _ifs[i].flag);
			}
			InfoSelect::Setup(7, 0);
		}
		else
		{
			strcpy(_ifs[0].info, M_STAGESTR_PRE);
			_ifs[0].linki("|20206", data.getSpellNumber(Replay::enumrpy[tindex].rpyinfo.startscene));

			strcat(_ifs[0].info, "\n");
			strcat(_ifs[0].info, data.getSpellName((int)(Replay::enumrpy[tindex].rpyinfo.startscene)));
			infoselect.push_back(_ifs[0]);
			infoselect.rbegin()->valueSet(0, _ifs[0].info, 160, 80, INFO_RED);

			strcpy(_ifs[1].info, res.resdata.uistr.score);
			_ifs[1].linkl("|10216", Replay::enumrpy[tindex].rpyinfo.score);

			infoselect.push_back(_ifs[1]);
			infoselect.rbegin()->valueSet(1, _ifs[1].info, 320, 75, INFO_RED, SEL_NONACTIVE);

			InfoSelect::Setup(1, 0);
		}

		strcpy(_ifs[10].info, res.resdata.uistr.username);
		strcat(_ifs[10].info, "|008");
		strcat(_ifs[10].info, Replay::enumrpy[tindex].rpyinfo.username);

		strcpy(_ifs[11].info, res.resdata.uistr.usingchara);

		for (int i=0; i<M_PL_ONESETPLAYER;i ++)
		{
			strcpy(_ifs[12+i].info, "|006");
			strcat(_ifs[12+i].info, data.getPlayerName(Replay::enumrpy[tindex].rpyinfo.usingchara[i]));
		}

		strcpy(_ifs[15].info, res.resdata.uistr.date);
		_ifs[15].linki("|21014", Replay::enumrpy[tindex].rpyinfo.year);
		strcat(_ifs[15].info, "/");
		_ifs[15].linki("|21517", Replay::enumrpy[tindex].rpyinfo.month);
		strcat(_ifs[15].info, "/");
		_ifs[15].linki("|21820", Replay::enumrpy[tindex].rpyinfo.day);
		strcat(_ifs[15].info, " ");
		_ifs[15].linki("|22123", Replay::enumrpy[tindex].rpyinfo.hour);
		strcat(_ifs[15].info, ":");
		_ifs[15].linki("|22426", Replay::enumrpy[tindex].rpyinfo.minute);

		strcpy(_ifs[16].info, res.resdata.uistr.faith);
		_ifs[16].linki("|012", Replay::enumrpy[tindex].rpyinfo.faith);

		strcpy(_ifs[17].info, res.resdata.uistr.lost);
		_ifs[17].linkf("|012", 0, Replay::enumrpy[tindex].rpyinfo.lost);
		strcat(_ifs[17].info, "%");		

		strcpy(_ifs[18].info, res.resdata.uistr.misstime);
		_ifs[18].linki("|022", Replay::enumrpy[tindex].rpyinfo.miss);

		strcpy(_ifs[19].info, res.resdata.uistr.bordertime);
		_ifs[19].linki("|022", Replay::enumrpy[tindex].rpyinfo.border);

		strcpy(_ifs[20].info, res.resdata.uistr.gettime);
		_ifs[20].linki("|022", Replay::enumrpy[tindex].rpyinfo.get);

		strcpy(_ifs[21].info, res.resdata.uistr.filename);
		strcat(_ifs[21].info, "|010");
		strcat(_ifs[21].info, Replay::enumrpy.filename[tindex]);

		strcpy(_ifs[22].info, res.resdata.uistr.modeflag);
		strcat(_ifs[22].info, "|010");
		if(Replay::enumrpy[tindex].rpyinfo.modeflag & M_RPYMODE_SPELL)
		{
			strcat(_ifs[22].info, res.resdata.uistr.mode_spell);
		}
		else if(Replay::enumrpy[tindex].rpyinfo.modeflag & M_RPYMODE_PRACTICE)
		{
			strcat(_ifs[22].info, res.resdata.uistr.mode_practice);
		}
		else
		{
			strcat(_ifs[22].info, res.resdata.uistr.mode_none);
		}

		for(int i=10;i<23;i++)
		{
			infoselect.push_back(_ifs[i]);
			infoselect.rbegin()->valueSet(i, _ifs[i].info, 40, 125+(i-10)*25, INFO_GREEN, SEL_NONACTIVE);
		}

		tdepth = 3;
	}
	if(tdepth == 3)
	{
		if(hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN))
		{
			SE::push(SE_SYSTEM_CANCEL);
			tdepth = 0;
			InfoSelect::Clear();
			InfoSelect::select = tindex;
		}
		else if (hge->Input_GetDIKey(DIK_D, DIKEY_DOWN))
		{
			DataPrinter::PrintReplayData(res.resdata.replayfoldername, Replay::enumrpy.filename[tindex]);
		}

		if(InfoSelect::complete)
		{
			replaymode = true;
			if (Replay::enumrpy[tindex].rpyinfo.difflv < M_DIFFI_EXTRA_START)
			{
				scene = Replay::enumrpy[tindex].partinfo[InfoSelect::select].scene;
			}
			else
			{
				scene = Replay::enumrpy[tindex].rpyinfo.startscene;
			}
			strcpy(rpyfilename, Replay::enumrpy.filename[tindex]);
			state = STATE_START;
			startPrep();
			return PTURN;
		}
	}

	scr.SetIntValue(SCR_RESERVEBEGIN, tdepth);
	scr.SetIntValue(SCR_RESERVEBEGIN+1, tindex);
	scr.SetIntValue(SCR_RESERVEBEGIN+2, trpydifflv);
*/

	return PGO;
}