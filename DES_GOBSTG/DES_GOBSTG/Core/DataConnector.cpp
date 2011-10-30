#include "../Header/DataConnector.h"
#include "../Header/Process.h"
#include "../Header/Player.h"
#include "../Header/Data.h"
#include "../Header/Replay.h"

int DataConnector::Insert()
{
	if(Process::mp.replaymode)
		return -1;

	DWORD sec;

	if(Process::mp.practicemode)
	{
		sec = Data::data.sLinkType(DATAS_STAGEPRACTICE);
		sec = Data::data.sLinkDiff(sec, Replay::rpy.rpyinfo.difflv);
		sec = Data::data.sLinkNum(sec, Replay::rpy.rpyinfo.stage);
		if(Replay::rpy.rpyinfo.score > Data::data.lRead(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_TOPSCORE), 0))
		{
			Data::data.lWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_TOPSCORE), Replay::rpy.rpyinfo.score);
		}
		return -1;
	}

	sec = Data::data.sLinkType(DATAS_TOP);
	sec = Data::data.sLinkDiff(sec, Replay::rpy.rpyinfo.difflv);

	for(int i=DATA_NTOP10FILESAVE;i>=0;i--)
	{
		DWORD secbuf = sec;
		secbuf = Data::data.sLinkNum(secbuf, i);
		if(i == 0 || Data::data.lRead(DATA_BINFILE, secbuf, Data::data.nLinkType(DATAN_SCORE), 0) > Replay::rpy.rpyinfo.score)
		{
			if(i == DATA_NTOP10FILESAVE)
				return 0;

			for(int j=DATA_NTOP10FILESAVE-1;j>i;j--)
			{
				Data::data.MoveDown(sec, j);
			}
			//
			sec = Data::data.sLinkNum(sec, i+1);

			Data::data.lWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_SCORE), Replay::rpy.rpyinfo.score);
			Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_LASTSTAGE), Replay::rpy.rpyinfo.stage);
			Data::data.sWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_USERNAME), Replay::rpy.rpyinfo.username);
			Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_TIME_YEAR), Replay::rpy.rpyinfo.year);
			Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_TIME_MONTH), Replay::rpy.rpyinfo.month);
			Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_TIME_DAY), Replay::rpy.rpyinfo.day);
			Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_TIME_HOUR), Replay::rpy.rpyinfo.hour);
			Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_TIME_MINUTE), Replay::rpy.rpyinfo.minute);
			Data::data.fWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_LOST), Replay::rpy.rpyinfo.lost);
			Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_ALLTIME), Replay::rpy.rpyinfo.alltime);

			DWORD name;
			name = Data::data.nLinkType(DATAN_CHARA);
			name = Data::data.nLinkNum(name, 1);
			Data::data.iWrite(DATA_BINFILE, sec, name, Replay::rpy.rpyinfo.usingchara);

			return i+1;
		}
	}
	return 0;
}

/*
//////////////////////////////
//replaymode, p[0].ID, scene, spellmode
void DataConnector::Meet()
{
	if(Process::mp.replaymode)
		return;

	DWORD sec;
	int t;
	sec = Data::data.sLinkType(DATAS_SPELL);
	sec = Data::data.sLinkNum(sec, Process::mp.scene);
	if(Process::mp.spellmode)
	{
		t = Data::data.iRead(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_MEETPRACTICE), 0);
		Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_MEETPRACTICE), t+1);

		WORD indi = Data::data.raGetIndi(Process::mp.scene);
		indi |= 1 << 8;
		Data::data.raSetIndi(Process::mp.scene, indi);
	}
	else
	{
		t = Data::data.iRead(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_MEETGAME), 0);
		Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_MEETGAME), t+1);

		WORD indi = Data::data.raGetIndi(Process::mp.scene);
		indi |= 1;
		Data::data.raSetIndi(Process::mp.scene, indi);
	}
}

///////////////////////////
//replaymode, p[0].ID, scene, spellmode
void DataConnector::Get()
{
	if(Process::mp.replaymode)
		return;

	DWORD sec;
	int t;
	sec = Data::data.sLinkType(DATAS_SPELL);
	sec = Data::data.sLinkNum(sec, Process::mp.scene);
	if(Process::mp.spellmode)
	{
		t = Data::data.iRead(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_GETPRACTICE), 0);
		Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_GETPRACTICE), t+1);
	
		WORD indi = Data::data.raGetIndi(Process::mp.scene);
		indi |= 1 << 12;
		Data::data.raSetIndi(Process::mp.scene, indi);
	}
	else
	{
		t = Data::data.iRead(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_GETGAME), 0);
		Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_GETGAME), t+1);
		
		WORD indi = Data::data.raGetIndi(Process::mp.scene);
		indi |= 1 << 4;
		Data::data.raSetIndi(Process::mp.scene, indi);
	}
}

//luchara, scene, spellmode
int DataConnector::nMeet()
{
	return Data::data.nMeet(Process::mp.scene, Process::mp.spellmode);
}

//luchara, scene, spellmode
int DataConnector::nGet()
{
	return Data::data.nGet(Process::mp.scene, Process::mp.spellmode);
}

*/
//replaymode, practicemode, nowdifflv, luchara
void DataConnector::Clear()
{
	if(Process::mp.replaymode || Process::mp.practicemode)
	{
		return;
	}

	DWORD sec;
	sec = Data::data.sLinkType(DATAS_TOTAL);
	sec = Data::data.sLinkDiff(sec, Process::mp.nowdifflv);

	Data::data.iWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_CLEARTIME), Data::data.iRead(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_CLEARTIME), 0)+1);
}

//playtimeStart
void DataConnector::addPlayTime()
{
	DWORD sec;

	LONGLONG playtimeEnd = hge->Timer_GetFileTime();

	sec = Data::data.sLinkType(DATAS_TOTAL);
	if(playtimeEnd > Process::mp.playtimeStart)
		Data::data.lWrite(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_TOTALPLAYTIME), Data::data.lRead(DATA_BINFILE, sec, Data::data.nLinkType(DATAN_TOTALPLAYTIME), 0) + (playtimeEnd - Process::mp.playtimeStart));

	Process::mp.playtimeStart = 0;
}

//spellmode, luchara, scene, nowdifflv, practicemode
LONGLONG DataConnector::nHiScore()
{
	return Data::data.nHighScore(Process::mp.stage, Process::mp.nowdifflv, Process::mp.practicemode);
}

//nowdifflv, luchara, scene
int DataConnector::nTryStageTime()
{
	return Data::data.nTryStageTime(Process::mp.stage, Process::mp.nowdifflv);
}

//spellmode, replaymode, practicemode, nowdifflv, luchara, scene
void DataConnector::Try(bool first)
{
	if(Process::mp.replaymode)
	{
		return;
	}
	
	DWORD sec;
	DWORD name;
	if(Process::mp.practicemode || !nTryStageTime())
	{
		sec = Data::data.sLinkType(DATAS_STAGEPRACTICE);
		sec = Data::data.sLinkDiff(sec, Process::mp.nowdifflv);
		sec = Data::data.sLinkNum(sec, Process::mp.stage/M_STAGENSCENE);

		name = Data::data.nLinkType(DATAN_TRYTIME);
		if(Process::mp.practicemode)
			Data::data.iWrite(DATA_BINFILE, sec, name, Data::data.iRead(DATA_BINFILE, sec, name, 0)+1);
		else
			Data::data.iWrite(DATA_BINFILE, sec, name, 1);
	}

	sec = Data::data.sLinkType(DATAS_TOTAL);
	sec = Data::data.sLinkDiff(sec, Process::mp.nowdifflv);

	if(Process::mp.practicemode)
	{
		name = Data::data.nLinkType(DATAN_PRACTICETIME);
		Data::data.iWrite(DATA_BINFILE, sec, name, Data::data.iRead(DATA_BINFILE, sec, name, 0)+1);
	}
	else if (first)
	{
		name = Data::data.nLinkType(DATAN_PLAYTIME);
		Data::data.iWrite(DATA_BINFILE, sec, name, Data::data.iRead(DATA_BINFILE, sec, name, 0)+1);
		name = Data::data.nLinkNum(name, Player::p.ID+1);
		Data::data.iWrite(DATA_BINFILE, sec, name, Data::data.iRead(DATA_BINFILE, sec, name, 0)+1);
	}
}
