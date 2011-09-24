
#include "../Header/DataPrinter.h"
#include "../Header/Data.h"
#include "../Header/BResource.h"
#include "../Header/ConstResource.h"

replayFrame DataPrinter::rpyframe[M_SAVEINPUTMAX];
partInfo DataPrinter::partinfo[RPYPARTMAX];
replayInfo DataPrinter::rpyinfo;
#ifdef __WIN32
string DataPrinter::str;
#endif // __WIN32

DataPrinter::DataPrinter()
{
}

DataPrinter::~DataPrinter()
{
}

void DataPrinter::getHeader()
{
/*
	SYSTEMTIME systime;
	GetLocalTime(&systime);

	char buffer[M_STRMAX];

	str = DPS_SECTION_HEADER;
	str += DPS_COMMENT;
	str += GAME_TITLE;
	str += DPS_SPACE;
	str += GAME_VERSION_STR;
	str += DPS_SPACE;
	str += DPS_HEAD_TITLE;
	str += DPS_RETURN;

	str += DPS_COMMENT;
	str += DPS_RETURN;

	str += DPS_COMMENT;
	str += DPS_HEAD_EXPLAIN_1;
	str += DPS_RETURN;

	str += DPS_COMMENT;
	str += DPS_HEAD_EXPLAIN_2;
	str += DPS_RETURN;

	str += DPS_COMMENT;
	str += DPS_HEAD_EXPLAIN_3;
	str += DPS_RETURN;

	str += DPS_COMMENT;
	str += DPS_TABLE_1;
	str += DPS_HEAD_TIMESTAMPSIGN;
	str += DPS_LEFTANGLEBRACKET;

	sprintf(buffer, "%04d%s%02d%s%02d%s%02d%s%02d%s%02d",
		systime.wYear, DPS_SLASH,
		systime.wMonth, DPS_SLASH,
		systime.wDay, DPS_SPACE,
		systime.wHour, DPS_COLON,
		systime.wMinute, DPS_COLON,
		systime.wSecond);
	str += buffer;

	str += DPS_RIGHTANGLEBRACKET;
	str += DPS_RETURN;

	str += DPS_RETURN;

	str += DPS_RETURN;*/

}

#ifdef __WIN32
bool DataPrinter::WriteString(string * str, HANDLE hFile)
{
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	DWORD byteswritten = 0;
	DWORD bytestowrite = strlen(str->data());
	WriteFile(hFile, str->data(), bytestowrite, &byteswritten, NULL);
	if (bytestowrite == byteswritten)
	{
		return true;
	}
	return false;
}
#endif // __WIN32

bool DataPrinter::PrintScore()
{	
/*
		char filename[M_PATHMAX];
		strcpy(filename, DPS_SCOREFILENAME);
		strcat(filename, ".");
		strcat(filename, DPS_EXTENSION);
		HANDLE hFile = CreateFile(hge->Resource_MakePath(filename), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			HGELOG("Failed in creating Score Data File %s!", filename);
			return false;
		}
	
		char buffer[M_STRMAX];
	
		//Header
		getHeader();
	
		WriteString(&str, hFile);
	
		//Top10
		str = DPS_SECTION_TOP10;
		str += DPS_COMMENT;
		str += DPS_TITLE_TOP;
		str += DPS_RETURN;
	
		WriteString(&str, hFile);
	
		DWORD sec = 0;
		DWORD name = 0;
	
		sec = data.sLinkType(DATAS_TOP);
	
		for (int i=0; i<M_NSTAGEDIFFI-1; i++)
		{
			str = DPS_RETURN;
			str += DPS_COMMENT;
			str += DPS_COMMENTDOUBLELINE;
			str += DPS_RETURN;
			str += res.resdata.uistr.difflv;
			str += DPS_SPACE;
			switch (i)
			{
			case M_DIFFI_EASY:
				str += M_DIFFISTR_EASY;
				break;
			case M_DIFFI_NORMAL:
				str += M_DIFFISTR_NORMAL;
				break;
			case M_DIFFI_HARD:
				str += M_DIFFISTR_HARD;
				break;
			case M_DIFFI_DESTINY:
				str += M_DIFFISTR_DESTINY;
				break;
			case M_DIFFI_EXTRA_1:
				str += M_DIFFISTR_EXTRA_1;
				break;
			case M_DIFFI_EXTRA_2:
				str += M_DIFFISTR_EXTRA_2;
				break;
			case M_DIFFI_EXTRA_3:
				str += M_DIFFISTR_EXTRA_3;
				break;
			case M_DIFFI_EXTRA_4:
				str += M_DIFFISTR_EXTRA_4;
				break;
			case M_DIFFI_EXTRA_5:
				str += M_DIFFISTR_EXTRA_5;
				break;
			case M_DIFFI_EXTRA_6:
				str += M_DIFFISTR_EXTRA_6;
				break;
			}
	
			str += DPS_RETURN;
	
			WriteString(&str, hFile);
			
			sec = data.sLinkDiff(sec, i);
	
			for (int j=0; j<DATA_NTOP10FILESAVE; j++)
			{
				sec = data.sLinkNum(sec, j+1);
	
	
				LONGLONG _score = data.lRead(DATA_BINFILE, sec, data.nLinkType(DATAN_SCORE), 0);
				if (!_score)
				{
					continue;
				}
				str = DPS_COMMENT;
				str += DPS_COMMENTLINE;
				str += DPS_RETURN;
				WriteString(&str, hFile);
	
				str = DPS_TABLE_1;
				str += DPS_TAG_TOPNUM;
				str += itoa(j+1, buffer, 10);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.usingchara;
				name = data.nLinkType(DATAN_CHARA);
				int chara[M_PL_ONESETPLAYER];
				for (int k=0; k<M_PL_ONESETPLAYER; k++)
				{
					chara[k] = data.iRead(DATA_BINFILE, sec, data.nLinkNum(name, k+1), 0);
					str += DPS_RETURN;
					str += DPS_TABLE_3;
					str += data.getPlayerName(chara[k]);
				}
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.score;
				str += DPS_TABLE_1;
				str += _i64toa(_score, buffer, 10);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.username;
				str += DPS_TABLE_1;
				str += data.sRead(DATA_BINFILE, sec, data.nLinkType(DATAN_USERNAME), RESCONFIGDEFAULT_USERNAME);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.laststage;
				str += DPS_TABLE_1;
				switch(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_LASTSTAGE), 0))
				{
				case 1:
					str += M_LASTSTAGESTR_1;
					break;
				case 2:
					str += M_LASTSTAGESTR_2;
					break;
				case 3:
					str += M_LASTSTAGESTR_3;
					break;
				case 4:
					str += M_LASTSTAGESTR_4;
					break;
				case 5:
					str += M_LASTSTAGESTR_5;
					break;
				case 6:
					str += M_LASTSTAGESTR_6;
					break;
				case 0xff:
					str += M_LASTSTAGESTR_C;
					break;
				default:
					str += M_LASTSTAGESTR_EX;
					break;
				}
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.date;
				str += DPS_TABLE_1;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_TIME_YEAR), 0), buffer, 10);
				str += DPS_SLASH;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_TIME_MONTH), 0), buffer, 10);
				str += DPS_SLASH;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_TIME_DAY), 0), buffer, 10);
				str += DPS_SPACE;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_TIME_HOUR), 0), buffer, 10);
				str += DPS_COLON;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_TIME_MINUTE), 0), buffer, 10);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.lost;
				str += DPS_TABLE_1;
				sprintf(buffer, "%f", data.fRead(DATA_BINFILE, sec, data.nLinkType(DATAN_LOST), 0));
				str += buffer;
				str += DPS_PERCENT;
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.alltime;
				str += DPS_TABLE_1;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_ALLTIME), 0), buffer, 10);
				str += DPS_RETURN;
	/ *
				str += DPS_TABLE_2;
				str += res.resdata.uistr.maxplayer;
				str += DPS_TABLE_1;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_MAXPLAYER), 0), buffer, 10);
				str += DPS_RETURN;
	* /
				str += DPS_TABLE_2;
				str += res.resdata.uistr.point;
				str += DPS_TABLE_1;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_POINT), 0), buffer, 10);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.faith;
				str += DPS_TABLE_1;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_FAITH), 0), buffer, 10);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.misstime;
				str += DPS_TABLE_1;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_MISS), 0), buffer, 10);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.bordertime;
				str += DPS_TABLE_1;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_BOMB), 0), buffer, 10);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.gettime;
				str += DPS_TABLE_1;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_SPELLGET), 0), buffer, 10);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.pausetime;
				str += DPS_TABLE_1;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_PAUSE), 0), buffer, 10);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.continuetime;
				str += DPS_TABLE_1;
				str += itoa(data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_CONTINUE), 0), buffer, 10);
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.borderrate;
				str += DPS_TABLE_1;
				sprintf(buffer, "%f", data.fRead(DATA_BINFILE, sec, data.nLinkType(DATAN_BORDERRATE), 0) * 100);
				str += buffer;
				str += DPS_PERCENT;
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += res.resdata.uistr.fastrate;
				str += DPS_TABLE_1;
				sprintf(buffer, "%f", data.fRead(DATA_BINFILE, sec, data.nLinkType(DATAN_FASTRATE), 0) * 100);
				str += buffer;
				str += DPS_PERCENT;
				str += DPS_RETURN;
	
				str += DPS_TABLE_2;
				str += DPS_TOP_TAGSTR_SPELLLIST;
				str += DPS_RETURN;
				str += DPS_TABLE_2;
				str += DPS_TOP_TAGSTR_SPELLLIST_EX;
				str += DPS_RETURN;
	
				WriteString(&str, hFile);
				
	
				name = data.nLinkType(DATAN_GETSPELL);
				for (int l=0; l<M_GETSPELLMAX; l++)
				{
					name = data.nLinkNum(name, l+1);
					int _sno = data.iRead(DATA_BINFILE, sec, name, 0);
					if (!_sno)
					{
						continue;
					}
	
					str = DPS_TABLE_2;
					str += DPS_TAG_SPELLPRIFIX;
					str += itoa(data.getSpellNumber(_sno), buffer, 10);
					str += DPS_SPACE;
					str += data.getSpellName(_sno);
					while (strlen(str.data()) < DPS_SPELLNAME_NFORMAT)
					{
						str += DPS_SPACE;
					}
					str += DPS_LEFTBRACKET;
					str += itoa(data.nGet(_sno), buffer, 10);
					str += DPS_SLASH;
					str += itoa(data.nMeet(_sno), buffer, 10);
					str += DPS_RIGHTBRACKET;
					str += DPS_RETURN;
	
					WriteString(&str, hFile);
					
				}
			}
		}
	
		str = DPS_RETURN;
	
		//Spell
		str += DPS_SECTION_SPELL;
		str += DPS_COMMENT;
		str += DPS_COMMENTDOUBLELINE;
		str += DPS_RETURN;
		str += DPS_TITLE_SPELL;
		str += DPS_RETURN;
		str += DPS_TITLE_SPELL_EX;
		str += DPS_RETURN;
	
		WriteString(&str, hFile);
	
		for (vector<spellData>::iterator it = res.spelldata.begin(); it!= res.spelldata.end(); it++)
		{
			if (data.raGetIndi(it->sno))
			{
				str = DPS_TAG_SPELLPRIFIX;
				str += itoa(data.getSpellNumber(it->sno), buffer, 10);
				str += DPS_SPACE;
				str += data.getSpellName(it->sno);
				while (strlen(str.data()) < DPS_SPELLNAME_NFORMAT)
				{
					str += DPS_SPACE;
				}
				str += itoa(data.nGet(it->sno), buffer, 10);
				str += DPS_SLASH;
				str += DPS_TABLE_1;
				str += itoa(data.nMeet(it->sno), buffer, 10);
				str += DPS_SLASH;
				str += DPS_TABLE_1;
				str += itoa(data.nGet(it->sno, true), buffer, 10);
				str += DPS_SLASH;
				str += DPS_TABLE_1;
				str += itoa(data.nMeet(it->sno, true), buffer, 10);
				str += DPS_TABLE_1;
				str += DPS_LEFTBRACKET;
				switch (data.getDiffi(it->sno))
				{
				case M_DIFFI_EASY:
					str += M_DIFFISTR_EASY;
					break;
				case M_DIFFI_NORMAL:
					str += M_DIFFISTR_NORMAL;
					break;
				case M_DIFFI_HARD:
					str += M_DIFFISTR_HARD;
					break;
				case M_DIFFI_DESTINY:
					str += M_DIFFISTR_DESTINY;
					break;
				case M_DIFFI_EXTRA_1:
					str += M_DIFFISTR_EXTRA_1;
					break;
				case M_DIFFI_EXTRA_2:
					str += M_DIFFISTR_EXTRA_2;
					break;
				case M_DIFFI_EXTRA_3:
					str += M_DIFFISTR_EXTRA_3;
					break;
				case M_DIFFI_EXTRA_4:
					str += M_DIFFISTR_EXTRA_4;
					break;
				case M_DIFFI_EXTRA_5:
					str += M_DIFFISTR_EXTRA_5;
					break;
				case M_DIFFI_EXTRA_6:
					str += M_DIFFISTR_EXTRA_6;
					break;
				}
				str += DPS_SPACE;
				str += _i64toa(data.nHighScore(it->sno, 0, true), buffer, 10);
				str += DPS_RIGHTBRACKET;
				str += DPS_RETURN;
	
				WriteString(&str, hFile);
			}
		}
	
		str = DPS_RETURN;
		//total
		str += DPS_SECTION_TOTAL;
		str += DPS_COMMENT;
		str += DPS_COMMENTDOUBLELINE;
		str += DPS_RETURN;
		str += DPS_TITLE_TOTAL;
		str += DPS_RETURN;
	
		str += DPS_TOTAL_RUNTIME;
		str += DPS_TABLE_1;
		LONGLONG tldiffruntime = data.getTotalRunTime();
		int trunhour = tldiffruntime / 3600;
		int trunminute = (tldiffruntime / 60) % 60;
		int trunsecond = tldiffruntime % 60;
		str += itoa(trunhour, buffer, 10);
		str += DPS_COLON;
		str += itoa(trunminute, buffer, 10);
		str += DPS_COLON;
		str += itoa(trunsecond, buffer, 10);
		str += DPS_RETURN;
	
		str += DPS_TOTAL_GAMETIME;
		str += DPS_TABLE_1;
		LONGLONG tltotalplaytime = data.lRead(DATA_BINFILE, data.sLinkType(DATAS_TOTAL), data.nLinkType(DATAN_TOTALPLAYTIME), 0) / 10000000;
		int tplayhour = tltotalplaytime / 3600;
		int tplayminute = (tltotalplaytime / 60) % 60;
		int tplaysecond = tltotalplaytime % 60;
		str += itoa(tplayhour, buffer, 10);
		str += DPS_COLON;
		str += itoa(tplayminute, buffer, 10);
		str += DPS_COLON;
		str += itoa(tplaysecond, buffer, 10);
		str += DPS_RETURN;
	
		str += DPS_TOTAL_PLAYTIME;
		str += DPS_TABLE_2;
		str += M_DIFFISTR_EASY;
		str += DPS_TABLE_1;
		str += M_DIFFISTR_NORMAL;
		str += DPS_TABLE_1;
		str += M_DIFFISTR_HARD;
		str += DPS_TABLE_1;
		str += M_DIFFISTR_EXTRA_1;
		str += DPS_TABLE_1;
		str += M_DIFFISTR_EXTRA_2;
		str += DPS_TABLE_1;
		str += M_DIFFISTR_EXTRA_3;
		str += DPS_TABLE_1;
		str += M_DIFFISTR_EXTRA_4;
		str += DPS_TABLE_1;
		str += M_DIFFISTR_EXTRA_5;
		str += DPS_TABLE_1;
		str += M_DIFFISTR_EXTRA_6;
		str += DPS_TABLE_1;
		str += DPS_TOTAL_PLAYTIME_ALL;
		str += DPS_RETURN;
	
		int tplaytime[PLAYERTYPEMAX+1][M_NSTAGEDIFFI+1];
		int tcleartime[M_NSTAGEDIFFI+1];
		int tpracticetime[M_NSTAGEDIFFI+1];
		for(int i=0;i<M_NSTAGEDIFFI+1;i++)
		{
			for (int j=0; j<PLAYERTYPEMAX+1; j++)
			{
				tplaytime[j][i] = 0;
			}
			tcleartime[i] = 0;
			tpracticetime[i] = 0;
		}
		int tplayerIDmax = 0;
		for (int i=0; i<PLAYERTYPEMAX; i++)
		{
			if (!strlen(data.getPlayerName(i)))
			{
				tplayerIDmax = i;
				break;
			}
			for(int j=0;j<M_NSTAGEDIFFI;j++)
			{
				DWORD sec;
				DWORD name;
				sec = data.sLinkType(DATAS_TOTAL);
				sec = data.sLinkDiff(sec, j);
				name = data.nLinkType(DATAN_PLAYTIME);
				name = data.nLinkNum(name, i+1);
	
				tplaytime[i][j] = data.iRead(DATA_BINFILE, sec, name, 0);
				tplaytime[i][M_NSTAGEDIFFI] += tplaytime[i][j];
			}
		}
		for (int i=0; i<M_NSTAGEDIFFI; i++)
		{
			for (int j=0; j<tplayerIDmax; j++)
			{
				tplaytime[tplayerIDmax][i] += tplaytime[j][i];
			}
			tplaytime[tplayerIDmax][M_NSTAGEDIFFI] += tplaytime[tplayerIDmax][i];
		}
		for(int i=0;i<M_NSTAGEDIFFI;i++)
		{
			tcleartime[i] += data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_CLEARTIME), 0);
			tpracticetime[i] += data.iRead(DATA_BINFILE, sec, data.nLinkType(DATAN_PRACTICETIME), 0);
			tcleartime[M_NSTAGEDIFFI] += tcleartime[i];
			tpracticetime[M_NSTAGEDIFFI] += tpracticetime[i];
		}
	
		for (int i=0; i<tplayerIDmax; i++)
		{
			str += data.getPlayerName(i);
			str += DPS_TABLE_1;
			for (int j=0; j<M_NSTAGEDIFFI+1; j++)
			{
				str += DPS_TABLE_1;
				str += itoa(tplaytime[i][j], buffer, 10);
			}
			str += DPS_RETURN;
		}
		str += DPS_TOTAL_PLAYTIME_ALLCHARA;
		str += DPS_TABLE_1;
		for (int i=0; i<M_NSTAGEDIFFI+1; i++)
		{
			str += DPS_TABLE_1;
			str += itoa(tplaytime[tplayerIDmax][i], buffer, 10);
		}
		str += DPS_RETURN;
		
		str += DPS_TOTAL_CLEARTIME;
		for (int i=0; i<M_NSTAGEDIFFI+1; i++)
		{
			str += DPS_TABLE_1;
			str += itoa(tcleartime[i], buffer, 10);
		}
		str += DPS_RETURN;
	
		str += DPS_TOTAL_PRACTICETIME;
		for (int i=0; i<M_NSTAGEDIFFI+1; i++)
		{
			str += DPS_TABLE_1;
			str += itoa(tpracticetime[i], buffer, 10);
		}
	
		WriteString(&str, hFile);
	
		CloseHandle(hFile);
		*/
	
	return true;
}

bool DataPrinter::PrintReplayData(const char * foldername, const char * filename)
{
/*
		hge->Resource_SetPath(foldername);
		if (!filename || !Export::rpyLoad(filename, &rpyinfo, partinfo, rpyframe))
		{
			hge->Resource_SetPath("../");
			return false;
		}
	
		char ofilename[M_PATHMAX];
		strcpy(ofilename, filename);
		while (ofilename[strlen(ofilename)-1] != '.')
		{
			ofilename[strlen(ofilename)-1] = 0;
		}
		strcat(ofilename, DPS_EXTENSION);
		HANDLE hFile = CreateFile(hge->Resource_MakePath(ofilename), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			HGELOG("Failed in creating Replay Data File %s!", ofilename);
			return false;
		}
	
		DWORD bytestowrite = 0;
		DWORD byteswritten = 0;
	
		char buffer[M_STRMAX];
	
		//Header
		getHeader();
	
		WriteString(&str, hFile);
		
	
		//replayinfo
		str = DPS_SECTION_REPLAYINFO;
		str += DPS_COMMENT;
		str += DPS_COMMENTDOUBLELINE;
		str += DPS_RETURN;
		str += DPS_TITLE_REPLAYINFO;
		str += DPS_RETURN;
		str += DPS_RETURN;
	
		str += res.resdata.uistr.filename;
		str += DPS_TABLE_1;
		str += filename;
		str += DPS_RETURN;
	
		str += res.resdata.uistr.username;
		str += DPS_TABLE_1;
		str += rpyinfo.username;
		str += DPS_RETURN;
	
		str += res.resdata.uistr.usingchara;
		str += DPS_RETURN;
		for (int i=0; i<M_PL_ONESETPLAYER; i++)
		{
			str += DPS_TABLE_2;
			str += data.getPlayerName(rpyinfo.usingchara[i]);
			str += DPS_RETURN;
		}
	
		str += res.resdata.uistr.laststage;
		str += DPS_TABLE_1;
		if (rpyinfo.modeflag & M_RPYMODE_SPELL)
		{
			str += DPS_TAG_SPELLPRIFIX;
			str += itoa(rpyinfo.startscene, buffer, 10);
			str += DPS_SPACE;
			str += data.getSpellName(rpyinfo.startscene);
		}
		else
		{
			switch (rpyinfo.laststage)
			{
			case 1:
				str += M_LASTSTAGESTR_1;
				break;
			case 2:
				str += M_LASTSTAGESTR_2;
				break;
			case 3:
				str += M_LASTSTAGESTR_3;
				break;
			case 4:
				str += M_LASTSTAGESTR_4;
				break;
			case 5:
				str += M_LASTSTAGESTR_5;
				break;
			case 6:
				str += M_LASTSTAGESTR_6;
				break;
			case 0xff:
				str += M_LASTSTAGESTR_C;
				break;
			default:
				str += M_LASTSTAGESTR_EX;
				break;
			}
		}
		str += DPS_RETURN;
	
		str += res.resdata.uistr.score;
		str += DPS_TABLE_1;
		str += _i64toa(rpyinfo.score, buffer, 10);
		str += DPS_RETURN;
	
		str += res.resdata.uistr.point;
		str += DPS_TABLE_1;
		str += itoa(rpyinfo.point, buffer, 10);
		str += DPS_RETURN;
	
		str += res.resdata.uistr.faith;
		str += DPS_TABLE_1;
		str += itoa(rpyinfo.faith, buffer, 10);
		str += DPS_RETURN;
	
		str += res.resdata.uistr.alltime;
		str += DPS_TABLE_1;
		str += itoa(rpyinfo.alltime, buffer, 10);
		str += DPS_RETURN;
	
		str += res.resdata.uistr.date;
		str += DPS_TABLE_1;
		str += itoa(rpyinfo.year, buffer, 10);
		str += DPS_SLASH;
		str += itoa(rpyinfo.month, buffer, 10);
		str += DPS_SLASH;
		str += itoa(rpyinfo.day, buffer, 10);
		str += DPS_SPACE;
		str += itoa(rpyinfo.hour, buffer, 10);
		str += DPS_COLON;
		str += itoa(rpyinfo.minute, buffer, 10);
		str += DPS_RETURN;
	
		str += res.resdata.uistr.lost;
		str += DPS_TABLE_1;
		sprintf(buffer, "%f", rpyinfo.lost);
		str += buffer;
		str += DPS_PERCENT;
		str += DPS_RETURN;
	
		str += res.resdata.uistr.borderrate;
		str += DPS_TABLE_1;
		sprintf(buffer, "%f", rpyinfo.borderrate * 100);
		str += buffer;
		str += DPS_PERCENT;
		str += DPS_RETURN;
	
		str += res.resdata.uistr.fastrate;
		str += DPS_TABLE_1;
		sprintf(buffer, "%f", rpyinfo.fastrate * 100);
		str += buffer;
		str += DPS_PERCENT;
		str += DPS_RETURN;
	
		str += res.resdata.uistr.modeflag;
		str += DPS_TABLE_1;
		if (rpyinfo.modeflag & M_RPYMODE_SPELL)
		{
			str += res.resdata.uistr.mode_spell;
		}
		else if (rpyinfo.modeflag & M_RPYMODE_PRACTICE)
		{
			str += res.resdata.uistr.mode_practice;
		}
		else
		{
			str += res.resdata.uistr.mode_none;
		}
		str += DPS_RETURN;
	/ *
		str += res.resdata.uistr.maxplayer;
		str += DPS_TABLE_1;
		str += itoa(rpyinfo.maxplayer, buffer, 10);
		str += DPS_RETURN;
	* /
		str += res.resdata.uistr.misstime;
		str += DPS_TABLE_1;
		str += itoa(rpyinfo.miss, buffer, 10);
		str += DPS_RETURN;
	
		str += res.resdata.uistr.bordertime;
		str += DPS_TABLE_1;
		str += itoa(rpyinfo.border, buffer, 10);
		str += DPS_RETURN;
	
		str += res.resdata.uistr.gettime;
		str += DPS_TABLE_1;
		str += itoa(rpyinfo.get, buffer, 10);
		str += DPS_RETURN;
	
		str += res.resdata.uistr.continuetime;
		str += DPS_TABLE_1;
		str += itoa(rpyinfo.cont, buffer, 10);
		str += DPS_RETURN;
	
		str += res.resdata.uistr.pausetime;
		str += DPS_TABLE_1;
		str += itoa(rpyinfo.pause, buffer, 10);
		str += DPS_RETURN;
		str += DPS_RETURN;
	
		str += DPS_RPYINFO_TAGSTR_SPELLLIST;
		str += DPS_RETURN;
		for (int i=0; i<M_GETSPELLMAX; i++)
		{
			if (rpyinfo.getspell[i])
			{
				str += DPS_TABLE_1;
				str += data.getSpellName(rpyinfo.getspell[i]);
				str += DPS_RETURN;
			}
		}
		str += DPS_RETURN;
	
		WriteString(&str, hFile);
		
	
		if (!rpyinfo.modeflag)
		{
			//partinfo
			str = DPS_SECTION_PARTNFO;
			str += DPS_COMMENT;
			str += DPS_COMMENTDOUBLELINE;
			str += DPS_RETURN;
			str += DPS_TITLE_PARTINFO;
			str += DPS_RETURN;
			for (int i=0; i<RPYPARTMAX; i++)
			{
				int index = 0;
				if (partinfo[i].offset)
				{
					for (int j=i+1; j<RPYPARTMAX; j++)
					{
						if (partinfo[j].offset)
						{
							index = j;
							break;
						}
					}
					str += DPS_COMMENTLINE;
					str += DPS_RETURN;
					str += DPS_TAG_PART;
					str += DPS_TABLE_1;
					switch (i+1)
					{
					case 1:
						str += M_LASTSTAGESTR_1;
						break;
					case 2:
						str += M_LASTSTAGESTR_2;
						break;
					case 3:
						str += M_LASTSTAGESTR_3;
						break;
					case 4:
						str += M_LASTSTAGESTR_4;
						break;
					case 5:
						str += M_LASTSTAGESTR_5;
						break;
					case 6:
						str += M_LASTSTAGESTR_6;
						break;
					default:
						str += M_LASTSTAGESTR_EX;
						break;
					}
					str += DPS_RETURN;
	
					str += DPS_TABLE_1;
					str += res.resdata.uistr.score;
					str += DPS_TABLE_1;
					str += _i64toa(partinfo[index].nowscore, buffer, 10);
					str += DPS_RETURN;
	
					str += DPS_TABLE_1;
					str += res.resdata.uistr.point;
					str += DPS_TABLE_1;
					str += itoa(partinfo[index].nowpoint, buffer, 10);
					str += DPS_RETURN;
	
					str += DPS_TABLE_1;
					str += res.resdata.uistr.faith;
					str += DPS_TABLE_1;
					str += itoa(partinfo[index].nowfaith, buffer, 10);
					str += DPS_RETURN;
	
					str += DPS_TABLE_1;
					str += res.resdata.uistr.graze;
					str += DPS_TABLE_1;
					str += itoa(partinfo[index].nowgraze, buffer, 10);
					str += DPS_RETURN;
				}
			}
			str += DPS_RETURN;
	
			WriteString(&str, hFile);
			
		}
	
		//fps
		str = DPS_SECTION_REPLAYFRAME;
		str += DPS_COMMENT;
		str += DPS_COMMENTDOUBLELINE;
		str += DPS_RETURN;
		str += DPS_TITLE_REPLAYFRAME;
		str += DPS_RETURN;
	
		int index=0;
		double sum = 0;
		double sumsub = 0;
		while (rpyframe[index].input != 0xffff)
		{
			float tfps = Export::rpyGetReplayFPS(rpyframe[index]);
			sumsub += tfps;
			sum += tfps;
			index++;
			if (index % DPS_REPLAYFRAME_AVERAGE_INTERVAL == 0)
			{
				if (index == DPS_REPLAYFRAME_AVERAGE_INTERVAL)
				{
					str += DPS_REPLAYFRAME_TAGSTR_TOTAL_AVERAGE;
					str += DPS_COLON;
					str += DPS_RETURN;
				}
				str += itoa(index / DPS_REPLAYFRAME_AVERAGE_INTERVAL, buffer, 10);
				str += DPS_TABLE_1;
				sumsub /= DPS_REPLAYFRAME_AVERAGE_INTERVAL;
				sprintf(buffer, "%f", (float)sumsub);
				str += buffer;
				str += DPS_RETURN;
				sumsub = 0;
			}
		}
		if (index)
		{
			sum /= index;
		}
		str += DPS_REPLAYFRAME_TAGSTR_AVERAGE;
		str += DPS_TABLE_1;
		sprintf(buffer, "%f", (float)sum);
		str += buffer;
	
		WriteString(&str, hFile);
		
	
		CloseHandle(hFile);
	
		hge->Resource_SetPath("../");
		*/
	
	return true;
}
