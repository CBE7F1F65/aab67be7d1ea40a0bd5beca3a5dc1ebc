#include "../Header/Process.h"
#include "../Header/Scripter.h"
#include "../Header/SE.h"
#include "../Header/BResource.h"
#include "../Header/PushKey.h"

int Process::processMusic()
{
	gametime++;
	/*
	if(gametime == 1)
	{
		scr.SetIntValue(SCR_RESERVEBEGIN, 0);
		scr.SetIntValue(SCR_RESERVEBEGIN+1, 0);

		PushKey::SetPushEvent(PUSHKEY_ID_UIUSE_0, KS_LEFT, KS_RIGHT);

		int i = 0;
		while(true)
		{
			if(!strlen(res.musdata[i].musicfilename))
			{
				scr.SetIntValue(SCR_RESERVEBEGIN+2, i);
				break;
			}
			i++;
		}

		InfoSelect::select = 0;
	}
	scr.Execute(SCR_CONTROL, STATE_MUSIC, gametime);

	if(hge->Input_GetDIKey(KS_QUICK, DIKEY_DOWN))
	{
		SE::push(SE_SYSTEM_CANCEL);
		gametime = 0;
		state = STATE_TITLE;
		return PTURN;
	}
	//sel maxnum
	int tmusicsel = scr.GetIntValue(SCR_RESERVEBEGIN);
	int tiselfirstID = scr.GetIntValue(SCR_RESERVEBEGIN+1);
	int tmaxmusic = scr.GetIntValue(SCR_RESERVEBEGIN+2);

	if(InfoSelect::complete)
	{
//		SE::push(SE_SYSTEM_OK);
		tiselfirstID = InfoSelect::firstID;
		musicChange(tmusicsel + 1, true);
	}
	else if(hge->Input_GetDIKey(KS_PAUSE, DIKEY_DOWN))
	{
		if(hge->Channel_IsPlaying(channel))
		{
			SE::push(SE_SYSTEM_OK);
			musicChange(musicID+1, true);
		}
	}
	else if(hge->Input_GetDIKey(KS_CHARGE, DIKEY_DOWN))
	{
		if(hge->Channel_IsPlaying(channel))
		{
			SE::push(SE_SYSTEM_OK);
			if (musicID == 0)
			{
				musicID = tmaxmusic;
			}
			musicChange(musicID, true);
		}
	}
	else if (hge->Input_GetDIKey(KS_SLOW, DIKEY_DOWN))
	{
		if(hge->Channel_IsPlaying(channel))
		{
			SE::push(SE_SYSTEM_OK);
			if (musicID == tmaxmusic-1)
			{
				musicID = -1;
			}
			musicChange(musicID+2, true);
		}
	}
	if(!infoselect.size())
	{
		InfoSelect * _ifs = new InfoSelect[tmaxmusic];
//		InfoSelect * _ifs = (InfoSelect *)malloc(tmaxmusic * sizeof(InfoSelect));
		for(int i=0;i<tmaxmusic;i++)
		{
			strcpy(_ifs[i].info, "No.");
			_ifs[i].linki("|10305", i + 1);
			strcat(_ifs[i].info, "|008");	
			strcat(_ifs[i].info, res.musdata[i].musicname);

			infoselect.push_back(_ifs[i]);
			infoselect.rbegin()->valueSet(i, _ifs[i].info, 70, i*22+100, INFO_GREEN);
		}
		delete [] _ifs;
//		free(_ifs);

		if (tmusicsel >= tmaxmusic)
		{
			tmusicsel = tmaxmusic - 1;
		}
		InfoSelect::Setup(tmaxmusic, tmusicsel);

		for(int i=0;i<4;i++)
		{
			InfoSelect::Build(i+tmaxmusic, res.musdata[0].explain[i], 70+i*15, 350+i*25, INFO_RED, SEL_NONACTIVE|SEL_STAY);
		}

		InfoSelect::SetPageNum(10, 67, 22, tiselfirstID);

		tmusicsel = -1;
	}

	PushKey::UpdatePushEvent(PUSHKEY_ID_UIUSE_0);

	if(hge->Input_GetDIKey(KS_LEFT, DIKEY_DOWN))
	{
		SE::push(SE_SYSTEM_SELECT);
		tmusicsel -= 10;
		if (tmusicsel < 0)
		{
			tmusicsel = 0;
		}
		InfoSelect::select = tmusicsel;
	}
	else if(hge->Input_GetDIKey(KS_RIGHT, DIKEY_DOWN))
	{
		SE::push(SE_SYSTEM_SELECT);
		tmusicsel += 10;
		if (tmusicsel >= tmaxmusic)
		{
			tmusicsel = tmaxmusic - 1;
		}
		InfoSelect::select = tmusicsel;
	}

	if(InfoSelect::select != tmusicsel)
	{
		tmusicsel = InfoSelect::select;
		for(int i=0;i<4;i++)
		{
			float _tx =  70+i*15;
			float _ty = 350+i*25;
			InfoSelect * _tifs = InfoSelect::GetPointer(i+tmaxmusic);
			_tifs->valueSet(i+tmaxmusic, res.musdata[tmusicsel].explain[i], _tx, _ty, INFO_RED, SEL_NONACTIVE|SEL_STAY);
		}
	}

	scr.SetIntValue(SCR_RESERVEBEGIN, tmusicsel);
	scr.SetIntValue(SCR_RESERVEBEGIN+1, tiselfirstID);

	*/
	return PGO;
}