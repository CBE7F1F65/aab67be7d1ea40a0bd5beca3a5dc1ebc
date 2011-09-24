#include "../Header/Process.h"
#include "../Header/BGLayer.h"
#include "../Header/SE.h"
#include "../Header/SelectSystem.h"
#include "../Header/Scripter.h"
#include "../Header/FrontDisplay.h"
#include "../Header/BResource.h"
#include "../Header/Data.h"
#include "../Header/BossInfo.h"
#include "../Header/Enemy.h"
#include "../Header/ConstResource.h"

int Process::processMatchSelect()
{
	gametime++;
	if (gametime == 1)
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_ENTERSTATE, STATE_MATCH_SELECT);
	}
	retvalue = PGO;
	Scripter::scr.Execute(SCR_CONTROL, STATE_MATCH_SELECT, gametime);
	return retvalue;
	/*
	static int snolist[FONTSYSMAX];

	gametime++;
	if(gametime == 1)
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_ENTERSTATE, STATE_MATCH_SELECT);
		fdisp.SetState(FDISP_PANEL, 0);
		if(nowdifflv >= M_DIFFI_EXTRA_START)
			nowdifflv = defaultdifflv;

		Scripter::scr.SetIntValue(SCR_RESERVEBEGIN, -1);
		Scripter::scr.SetIntValue(SCR_RESERVEBEGIN+1, 0);
		Scripter::scr.SetIntValue(SCR_RESERVEBEGIN+2, 0);
	}
	retvalue = PGO;
	Scripter::scr.Execute(SCR_CONTROL, STATE_MATCH_SELECT, gametime);

	int tsec = Scripter::scr.GetIntValue(SCR_RESERVEBEGIN);
	int tsnolistindex = Scripter::scr.GetIntValue(SCR_RESERVEBEGIN+1);
	int tselsys = Scripter::scr.GetIntValue(SCR_RESERVEBEGIN+3);
	int tspmode = Scripter::scr.GetIntValue(SCR_RESERVEBEGIN+16);

	if (tsec == 0)
	{
		tsnolistindex = 0;
		int tsel = selsys[tselsys].select;
		int i = 0;
		for (vector<spellData>::iterator it = res.spelldata.begin(); it!= res.spelldata.end(); it++)
		{
			if ((it->spellflag) & BISF_NOTSPELL)
			{
				continue;
			}
			if (tspmode && it->userID == tsel + ENEMY_BOSSTYPEBEGIN || !tspmode && it->battleID == tsel)
			{
				InfoSelect _ifs;

				int sno = it->sno;
				int tnget = 0;
				int tnmeet = 0;
				LONGLONG tmaxbonus = 0;

				snolist[tsnolistindex] = sno;
				tsnolistindex++;

				tnget = data.nGet(sno, true);
				tnmeet = data.nMeet(sno, true);
				tmaxbonus = data.nHighScore(sno, 0, true, false);

				strcpy(_ifs.info, M_STAGESTR_PRE);
				_ifs.linki("|20206", data.getSpellNumber(sno));
				strcat(_ifs.info, "|008");
				if(data.raGetIndi(sno))
				{
					strcat(_ifs.info, data.getSpellName(sno));
					strcat(_ifs.info, "(");
					switch (data.getDiffi(sno))
					{
					case M_DIFFI_EASY:
						strcat(_ifs.info, M_DIFFISTR_EASY_S);
						break;
					case M_DIFFI_NORMAL:
						strcat(_ifs.info, M_DIFFISTR_NORMAL_S);
						break;
					case M_DIFFI_HARD:
						strcat(_ifs.info, M_DIFFISTR_HARD_S);
						break;
					case M_DIFFI_DESTINY:
						strcat(_ifs.info, M_DIFFISTR_DESTINY_S);
						break;
					case M_DIFFI_EXTRA_1:
					case M_DIFFI_EXTRA_2:
					case M_DIFFI_EXTRA_3:
					case M_DIFFI_EXTRA_4:
					case M_DIFFI_EXTRA_5:
					case M_DIFFI_EXTRA_6:
						strcat(_ifs.info, M_DIFFISTR_EXTRA_S);
						break;
						break;
					}
					strcat(_ifs.info, ")");
					if(tnget)
						_ifs.coltype = INFO_GREEN;
					else
						_ifs.coltype = INFO_YELLOW;
					_ifs.flag = SEL_NULL;
				}
				else
				{
					strcat(_ifs.info, DATA_DEFAULTSTR_WIDE);
					_ifs.coltype = INFO_GRAY;
					_ifs.flag = SEL_NONACTIVE;
				}

				strcat(_ifs.info, "\n");
				_ifs.linki("|10610", tnget);
				strcat(_ifs.info, "/");
				_ifs.linki("|11115", tnmeet);
				strcat(_ifs.info, "(Get/Meet)|035MaxBonus:");
				_ifs.linkl("|14252", tmaxbonus);

				infoselect.push_back(_ifs);
				infoselect.rbegin()->valueSet(i, _ifs.info, 80, i*40+160, _ifs.coltype, _ifs.flag);

				i++;
			}
		}
		InfoSelect::Setup(i, 0);
		InfoSelect::SetPageNum(5, 100, 40);

		tsec = 1;
	}
	else if (tsec == 1)
	{
		scene = snolist[InfoSelect::select];
	}

	Scripter::scr.SetIntValue(SCR_RESERVEBEGIN, tsec);
	Scripter::scr.SetIntValue(SCR_RESERVEBEGIN+1, tsnolistindex);

	return retvalue;
	*/
}
