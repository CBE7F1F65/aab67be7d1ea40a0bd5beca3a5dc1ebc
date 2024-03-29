#include "../Header/Data.h"
#include "../Header/BResource.h"
#include "../Header/Export.h"
#include "../Header/ConstResource.h"

Data Data::data;

Data::Data()
{
	strcpy(nowfilename, "");
	password = NULL;

	binmode = false;
	bin.clear();
}

Data::~Data()
{
}

void Data::GetIni()
{
	password = Export::GetPassword();
}

char * Data::translateSection(DWORD sec)
{
	strcpy(transbufs, "");
	for(int i=DATAMAPENUM_DATASTART; i<DATAMAPENUM_END; i++)
	{
		if((sec & ~DATASBINMASK_TYPE) == dataMap[i].binname)
		{
			strcat(transbufs, dataMap[i].textname);
			break;
		}
	}
	for(int i=DATAMAPENUM_DATASTART; i<DATAMAPENUM_END; i++)
	{
		if((sec & ~DATASBINMASK_DIFF) == dataMap[i].binname)
		{
			strcat(transbufs, dataMap[i].textname);
			break;
		}
	}
	for(int i=DATAMAPENUM_DATASTART; i<DATAMAPENUM_END; i++)
	{
		if((sec & ~DATASBINMASK_CHARA) == dataMap[i].binname)
		{
			strcat(transbufs, dataMap[i].textname);
			break;
		}
	}
	if(sec & ~DATASBINMASK_NUM)
	{
		char buffer[M_STRITOAMAX];
		strcat(transbufs, "_");
		strcat(transbufs, hge->Math_itoa((sec & ~DATASBINMASK_NUM), buffer));
	}
	return transbufs;
}

char * Data::translateName(DWORD name)
{
	strcpy(transbufn, "");
	for(int i=DATAMAPENUM_DATASTART; i<DATAMAPENUM_END; i++)
	{
		if((name & ~DATANBINMASK_TYPE) == dataMap[i].binname)
		{
			strcat(transbufn, dataMap[i].textname);
			break;
		}
	}
	if(name & ~DATASBINMASK_NUM)
	{
		char buffer[M_STRITOAMAX];
		strcat(transbufn, "_");
		strcat(transbufn, hge->Math_itoa((name & ~DATASBINMASK_NUM), buffer));
	}
	return transbufn;
}

DWORD Data::sLinkType( DWORD type)
{
	return dataMap[type].binname;
}

DWORD Data::sLinkDiff(DWORD sec, BYTE diff)
{
	switch(diff)
	{
	case M_DIFFI_EASY:
		sec &= DATASBINMASK_DIFF;
		sec |= dataMap[DATATDIFF_E].binname;
		break;
	case M_DIFFI_NORMAL:
		sec &= DATASBINMASK_DIFF;
		sec |= dataMap[DATATDIFF_N].binname;
		break;
	case M_DIFFI_HARD:
		sec &= DATASBINMASK_DIFF;
		sec |= dataMap[DATATDIFF_H].binname;
		break;
	case M_DIFFI_DESTINY:
		sec &= DATASBINMASK_DIFF;
		sec |= dataMap[DATATDIFF_D].binname;
		break;
	case M_DIFFI_EXTRA:
		sec &= DATASBINMASK_DIFF;
		sec |= dataMap[DATATDIFF_X].binname;
		break;
	}
	return sec;
}

DWORD Data::sLinkNum(DWORD sec, DWORD num)
{
	sec &= DATASBINMASK_NUM;
	sec |= (num & ~DATASBINMASK_NUM);
	return sec;
}

DWORD Data::nLinkType(DWORD type)
{
	return dataMap[type].binname;
}

DWORD Data::nLinkNum(DWORD name, DWORD num)
{
	name &= DATASBINMASK_NUM;
	name |= (num & ~DATANBINMASK_NUM);
	return name;
}
/*
WORD Data::raGetIndi(int sno)
{
	return indi[sno];
}
void Data::raSetIndi(int sno, WORD _indi)
{
	indi[sno] = _indi;
}
*/

char * Data::getPlayerName(int type)
{
	if (type < 0 || type >= DATASTRUCT_PLAYERTYPEMAX)
	{
		return NULL;
	}
	return BResource::bres.playerdata[type].name;
}

char * Data::getPlayerEName(int type)
{
	if (type < 0 || type >= DATASTRUCT_PLAYERTYPEMAX)
	{
		return NULL;
	}
	return BResource::bres.playerdata[type].ename;
}

void Data::MoveDown(DWORD sec, BYTE i)
{
	DWORD secS;
	DWORD secD;

	secS = sLinkNum(sec, i);
	secD = sLinkNum(sec, i+1);

	lWrite(DATA_BINFILE, secD, nLinkType(DATAN_SCORE), lRead(DATA_BINFILE, secS, nLinkType(DATAN_SCORE), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_LASTSTAGE), iRead(DATA_BINFILE, secS, nLinkType(DATAN_LASTSTAGE), 0));
	sWrite(DATA_BINFILE, secD, nLinkType(DATAN_USERNAME), sRead(DATA_BINFILE, secS, nLinkType(DATAN_USERNAME), RESCONFIGDEFAULT_USERNAME));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_TIME_YEAR), iRead(DATA_BINFILE, secS, nLinkType(DATAN_TIME_YEAR), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_TIME_MONTH), iRead(DATA_BINFILE, secS, nLinkType(DATAN_TIME_MONTH), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_TIME_DAY), iRead(DATA_BINFILE, secS, nLinkType(DATAN_TIME_DAY), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_TIME_HOUR), iRead(DATA_BINFILE, secS, nLinkType(DATAN_TIME_HOUR), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_TIME_MINUTE), iRead(DATA_BINFILE, secS, nLinkType(DATAN_TIME_MINUTE), 0));
	fWrite(DATA_BINFILE, secD, nLinkType(DATAN_LOST), fRead(DATA_BINFILE, secS, nLinkType(DATAN_LOST), 0));
	fWrite(DATA_BINFILE, secD, nLinkType(DATAN_BORDERRATE), fRead(DATA_BINFILE, secS, nLinkType(DATAN_BORDERRATE), 0));
	fWrite(DATA_BINFILE, secD, nLinkType(DATAN_FASTRATE), fRead(DATA_BINFILE, secS, nLinkType(DATAN_FASTRATE), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_ALLTIME), iRead(DATA_BINFILE, secS, nLinkType(DATAN_ALLTIME), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_SPELLGET), iRead(DATA_BINFILE, secS, nLinkType(DATAN_SPELLGET), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_MAXPLAYER), iRead(DATA_BINFILE, secS, nLinkType(DATAN_MAXPLAYER), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_POINT), iRead(DATA_BINFILE, secS, nLinkType(DATAN_POINT), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_FAITH), iRead(DATA_BINFILE, secS, nLinkType(DATAN_FAITH), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_MISS), iRead(DATA_BINFILE, secS, nLinkType(DATAN_MISS), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_BOMB), iRead(DATA_BINFILE, secS, nLinkType(DATAN_BOMB), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_CONTINUE), iRead(DATA_BINFILE, secS, nLinkType(DATAN_CONTINUE), 0));
	iWrite(DATA_BINFILE, secD, nLinkType(DATAN_PAUSE), iRead(DATA_BINFILE, secS, nLinkType(DATAN_PAUSE), 0));

	DWORD name;
	name = nLinkType(DATAN_CHARA);
	name = nLinkNum(name, 1);
	iWrite(DATA_BINFILE, secD, name, iRead(DATA_BINFILE, secS, name, 0));
	/*
	name = nLinkType(DATAN_GETSPELL);
	for (int j=0; j<M_GETSPELLMAX; j++)
	{
		name = nLinkNum(name, j+1);
		iWrite(DATA_BINFILE, secD, name, iRead(DATA_BINFILE, secS, name, 0));
	}
	*/
}

BYTE * Data::CreateMemHeader(BYTE type)
{
	BYTE * memheader = (BYTE *)malloc(M_BINHEADER_OFFSET);
	ZeroMemory(memheader, M_BINHEADER_OFFSET);

	char buffer[M_STRMAX];
	char tbuff[M_STRITOAMAX];
	strcpy(buffer, "[");
	strcat(buffer, translateSection(sLinkType(DATAS_HEADER)));
	strcat(buffer, "]\r\n");
	strcat(buffer, translateName(nLinkType(DATAN_GAMEVERSION)));
	strcat(buffer, "=");
	strcat(buffer, hge->Math_itoa(GAME_VERSION, tbuff));
	strcat(buffer, "\r\n");
	strcat(buffer, translateName(nLinkType(DATAN_SIGNATURE)));
	strcat(buffer, "=");
	strcat(buffer, GAME_SIGNATURE);
	strcat(buffer, "\r\n");
	strcat(buffer, translateName(nLinkType(DATAN_FILETYPE)));
	strcat(buffer, "=");
	strcat(buffer, hge->Math_itoa(type, tbuff));
	strcat(buffer, "\r\n");

	memcpy(memheader, buffer, strlen(buffer));

	return memheader;
}

bool Data::CheckMemHeader(const BYTE * memdata, DWORD size, BYTE type)
{
	bool ret = true;
	if(!memdata || size < M_BINHEADER_OFFSET)
		return false;

	BYTE * memheader = CreateMemHeader(type);
	if(strncmp((char *)memheader, (char *)memdata, M_BINHEADER_OFFSET))
	{
		ret = false;
	}
	free(memheader);

	return ret;
}

void Data::getFile(BYTE type)
{
	switch(type)
	{
	case DATA_CUSTOMCONSTFILE:
		strcpy(nowfilename, RESDATASTR_TABLE_CUSTOMCONST);
		break;

	case DATA_MUSICDEFINEFILE:
		strcpy(nowfilename, RESDATASTR_TABLE_MUSIC);
		break;

	case DATA_BULLETDEFINEFILE:
		strcpy(nowfilename, RESDATASTR_TABLE_BULLET);
		break;
	case DATA_ENEMYDEFINEFILE:
		strcpy(nowfilename, RESDATASTR_TABLE_ENEMY);
		break;
	case DATA_PLAYERDEFINEFILE:
		strcpy(nowfilename, RESDATASTR_TABLE_PLAYER);
		break;
	case DATA_SPRITEDEFINEFILE:
		strcpy(nowfilename, RESDATASTR_TABLE_SPRITE);
		break;
	case DATA_PLAYERSHOOTDEFINE:
		strcpy(nowfilename, RESDATASTR_TABLE_PLAYERSHOOT);
		break;
	case DATA_PLAYERLASERDEFINE:
		strcpy(nowfilename, RESDATASTR_TABLE_PLAYERLASER);
		break;
	case DATA_PLAYERSUBDEFINE:
		strcpy(nowfilename, RESDATASTR_TABLE_PLAYERSUB);
		break;
	case DATA_STAGEAREADEFINE:
		strcpy(nowfilename, RESDATASTR_TABLE_AREA);
		break;

	case DATA_PACKAGETABLEDEFINE:
		strcpy(nowfilename, RESDATASTR_TABLE_PACKAGE);
		break;
	case DATA_TEXTURETABLEDEFINE:
		strcpy(nowfilename, RESDATASTR_TABLE_TEXTURE);
		break;
	case DATA_EFFECTTABLEDEFINE:
		strcpy(nowfilename, RESDATASTR_TABLE_EFFECTSYS);
		break;
	case DATA_SETABLEDEFINE:
		strcpy(nowfilename, RESDATASTR_TABLE_SE);
		break;

	case DATA_RESOURCEFILE:
		strcpy(nowfilename, RESDATASTR_RESFILENAME);
		break;
	case DATA_BINFILE:
		strcpy(nowfilename, RESDATASTR_BINFILENAME);
		break;

	default:
		strcpy(nowfilename, "");
	}
}

bool Data::Init(BYTE type)
{
	if(binmode && (type & DATA_TABLEHEADER) ||
		(type == DATA_RESOURCEFILE))
	{
		return true;
	}

	getFile(type);
	if(!nowfilename)
		return false;

	hge->Resource_DeleteFile(nowfilename);

	if(type == DATA_BINFILE)
		bin.clear();

	if((type & DATA_MEMORYHEADER) ||
		(type == DATA_RESOURCEFILE) && binmode)
	{
		char * fname;
		char * bname;

		switch(type)
		{
			/*
		case DATA_SCRIPTFILE:
			fname = scriptfilename;
			bname = scrbinname;
			break;
			*/

		case DATA_RESOURCEFILE:
			fname = RESDATASTR_RESFILENAME;
			bname = RESDATASTR_RESFILENAME;
			break;
/*
		case DATA_SPELLACCESSFILE:
			fname = spellaccessfilename;
			bname = rabinname;
			break;
			*/
		}

		BYTE * _content;
		DWORD _size;

		BYTE * _memheader;
		_memheader = CreateMemHeader(type);

		/*
		if(type == DATA_SPELLACCESSFILE)
		{
			_size = M_BINHEADER_OFFSET + sizeof(WORD) * DATARA_INDIMAX;
			_content = (BYTE *)malloc(_size);
			memcpy(_content, _memheader, M_BINHEADER_OFFSET);
			free(_memheader);
			BYTE * it = _content + M_BINHEADER_OFFSET;
			for(int i=0; i<DATARA_INDIMAX; i++)
			{
				*(WORD *)it = indi[i];
				it += DATARA_INDI_SIZE;
			}
		}
		else
		{
		*/
			_size = M_BINHEADER_OFFSET;
			_content = _memheader;
//		}

		hgeMemoryFile memfile;
		memfile.data = _content;
		memfile.filename = bname;
		memfile.size = _size;

		hge->Resource_CreatePack(fname, password, &memfile, NULL);

		free(_content);
	}
	
	if(type == DATA_BINFILE)
	{
		hgeMemoryFile memfile;
		char tfilename[M_PATHMAX];
		strcpy(tfilename, RESDATASTR_BINFILENAME);
		memfile.filename = tfilename;
		memfile.data = NULL;
		memfile.size = 0;

		hge->Resource_CreatePack(nowfilename, password, &memfile, NULL);

		LONGLONG tnowtime = hge->Timer_GetFileTime();
		iWrite(type, sLinkType(DATAS_HEADER), nLinkType(DATAN_GAMEVERSION), GAME_VERSION);
		sWrite(type, sLinkType(DATAS_HEADER), nLinkType(DATAN_SIGNATURE), GAME_SIGNATURE);
		iWrite(type, sLinkType(DATAS_HEADER), nLinkType(DATAN_FILETYPE), type);
		lWrite(DATA_BINFILE, sLinkType(DATAS_TOTAL), nLinkType(DATAN_FIRSTRUNTIME), tnowtime);
	}
#ifdef __DEBUG_LOG
	HGELOG("Succeeded in rebuilding Data File %s.", nowfilename);
#endif
	return true;
}

bool Data::SetFile(const char * _filename, BYTE type)
{
	getFile(type);
	if(!nowfilename)
		return false;
	strcpy(nowfilename, hge->Resource_MakePath(_filename));

	if(type == DATA_BINFILE)
	{
		hge->Resource_AttachPack(nowfilename, password);
		BYTE * content;
		DWORD size;
		content = hge->Resource_Load(RESDATASTR_BINFILENAME, &size);
		hge->Resource_RemovePack(nowfilename);
		if(content)
		{
			MemToList(content, size);
		}
		hge->Resource_Free(content);
	}
	if(!hge->Resource_AccessFile(nowfilename) ||
		!CheckHeader(type))
	{
		if(type == DATA_BINFILE || (type & DATA_MEMORYHEADER))
		{
			if(!Init(type))
			{
				goto failed;
			}
		}
		else
		{
failed:
#ifdef __DEBUG_LOG
				HGELOG("%s\nFailed in Getting Data File %s.", HGELOG_ERRSTR, nowfilename);
#endif
				strcpy(nowfilename, "");
				return false;
		}
	}
/*
	if(type == DATA_SPELLACCESSFILE)
	{
		hge->Resource_AttachPack(nowfilename, password);
		BYTE * content;
		DWORD size;
		content = hge->Resource_Load(rabinname, &size);
		BYTE * it = NULL;
		if(content)
			it = content + M_BINHEADER_OFFSET;
		for(int i=0; i<DATARA_INDIMAX; i++)
		{
			indi[i] = content ? *(WORD *)(it) : 0;
			if(content)
				it += DATARA_INDI_SIZE;
		}
		hge->Resource_Free(content);
	}
*/
	return true;
}

bool Data::GetAllTable()
{
	//package
	if (!GetTableFile(DATA_PACKAGETABLEDEFINE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading PackageDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}
	//texture
	if (!GetTableFile(DATA_TEXTURETABLEDEFINE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading TextureDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}
	//effect
	if (!GetTableFile(DATA_EFFECTTABLEDEFINE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading EffectDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}
	//se
	if (!GetTableFile(DATA_SETABLEDEFINE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading SEDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}

	//music
	if (!GetTableFile(DATA_MUSICDEFINEFILE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading MusicDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}

	//sprite
	if (!GetTableFile(DATA_SPRITEDEFINEFILE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading SpriteDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}

	if (!GetTableFile(DATA_BULLETDEFINEFILE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading BulletDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}

	//boss
	if (!GetTableFile(DATA_ENEMYDEFINEFILE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading EnemyDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}

	//player
	if (!GetTableFile(DATA_PLAYERDEFINEFILE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading PlayerDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}

	//playershoot
	if (!GetTableFile(DATA_PLAYERSHOOTDEFINE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading PlayerShootDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}

	//playerlaser
	if (!GetTableFile(DATA_PLAYERLASERDEFINE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading PlayerLaserDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}

	//playerghost
	if (!GetTableFile(DATA_PLAYERSUBDEFINE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading PlayerSubDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}

	//area
	if (!GetTableFile(DATA_STAGEAREADEFINE))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading AreaDefineFile", HGELOG_ERRSTR);
#endif // __DEBUG
		return false;
	}

	return true;
}

bool Data::CheckHeader(BYTE type)
{
	if(/*type == DATA_SCRIPTFILE ||*/
		type == DATA_RESOURCEFILE && binmode/*
		 ||
				type == DATA_SPELLACCESSFILE*/
		)
	{
		char * fname;
		char * bname;
		switch(type)
		{
			/*
		case DATA_SCRIPTFILE:
			fname = scriptfilename;
			bname = scrbinname;
			break;
			*/
		case DATA_RESOURCEFILE:
			fname = RESDATASTR_RESFILENAME;
			bname = RESDATASTR_RESFILENAME;
			break;
			/*
		case DATA_SPELLACCESSFILE:
			fname = spellaccessfilename;
			bname = rabinname;
			break;
			*/
		}
		BYTE * _content;
		DWORD _size;
		hge->Resource_AttachPack(fname, password);
		_content = hge->Resource_Load(bname, &_size);
		hge->Resource_RemovePack(fname);
		if(!CheckMemHeader(_content, _size, type))
		{
			hge->Resource_Free(_content);
			return false;
		}
		hge->Resource_Free(_content);
	}
	/*
	else
	{
		if(iRead(type, sLinkType(DATAS_HEADER), nLinkType(DATAN_GAMEVERSION), -1) != GAME_VERSION ||
			strcmp(sRead(type, sLinkType(DATAS_HEADER), nLinkType(DATAN_SIGNATURE), ""), GAME_SIGNATURE) ||
			iRead(type, sLinkType(DATAS_HEADER), nLinkType(DATAN_FILETYPE), -1) != type)
			return false;
	}
	*/
	return true;
}

bool Data::SaveBin()
{
	bool ret = true;
	//binfile
	getFile(DATA_BINFILE);
	BYTE * _bin;
	DWORD _size;
	_bin = ListToMem(&_size);

	hgeMemoryFile memfile;
	char tfilename[M_PATHMAX];
	strcpy(tfilename, RESDATASTR_BINFILENAME);
	memfile.filename = tfilename;
	memfile.data = _bin;
	memfile.size = _size;

	if (!hge->Resource_CreatePack(nowfilename, password, &memfile, NULL))
	{
		ret = false;
	}

	bin.clear();
	free(_bin);

	if (!ret)
	{
		return false;
	}

	//spellaccessfile
	/*
	getFile(DATA_SPELLACCESSFILE);
	BYTE * _radata;
	_size = DATARA_INDIMAX * DATARA_INDI_SIZE + DATA_HEADEROFFSET;
	_radata = (BYTE *)malloc(_size);

	BYTE * _raheader;
	_raheader = hge->Resource_Load(rabinname);
	if(_raheader)
	{
		memcpy(_radata, _raheader, DATA_HEADEROFFSET);
	}
	hge->Resource_Free(_raheader);

	BYTE * rait = _radata+DATA_HEADEROFFSET;

	for(int i=0; i<DATARA_INDIMAX; i++)
	{
		*(WORD *)rait = indi[i];
		rait += DATARA_INDI_SIZE;
	}

	memfile.filename = rabinname;
	memfile.data = _radata;
	memfile.size = _size;

	if (!hge->Resource_CreatePack(nowfilename, password, &memfile, NULL))
	{
		ret = false;
	}

	free(_radata);
*/
	return ret;
}

bool Data::MemToList(BYTE * memcontent, DWORD size)
{
	bin.clear();
	for(BYTE * it=memcontent; it<memcontent+size; it+=sizeof(dataBin))
	{
		bool bFound = false;
		dataBin _bin;
		memcpy(&_bin, it, sizeof(dataBin));
		for(vector<dataSection>::iterator i=bin.begin(); i!=bin.end(); i++)
		{
			if(i->section == _bin.section)
			{
				for(vector<dataName>::iterator j=i->data.begin(); j!=i->data.end(); j++)
				{
					if(j->name == _bin.name)
					{
						j->value = _bin.value;
						bFound = true;
						break;
					}
				}
				if(!bFound)
				{
					dataName _dataname;
					_dataname.name = _bin.name;
					_dataname.value = _bin.value;
					i->data.push_back(_dataname);
				}
				bFound = true;
				break;
			}
		}
		if(!bFound)
		{
			dataSection _datasec;
			dataName _dataname;
			_dataname.value = _bin.value;
			_dataname.name = _bin.name;
			_datasec.section = _bin.section;
			_datasec.data.push_back(_dataname);
			bin.push_back(_datasec);
		}
	}
	return true;
}

LONGLONG * Data::AttachValue(DWORD section, DWORD name, LONGLONG def_val)
{
	for(vector<dataSection>::iterator i=bin.begin(); i!=bin.end(); i++)
	{
		if(i->section == section)
		{
			for(vector<dataName>::iterator j=i->data.begin(); j!=i->data.end(); j++)
			{
				if(j->name == name)
					return &(j->value);
			}
			dataName _dataname;
			_dataname.name = name;
			_dataname.value = def_val;
			i->data.push_back(_dataname);
			return &(i->data.back().value);
		}
	}
	dataSection _datasec;
	dataName _dataname;
	_dataname.name = name;
	_dataname.value = def_val;
	_datasec.data.push_back(_dataname);
	_datasec.section = section;
	bin.push_back(_datasec);
	return &(bin.back().data.back().value);
}

BYTE * Data::ListToMem(DWORD * size)
{
	BYTE * memcontent;
	*size = 0;
	for(vector<dataSection>::iterator i=bin.begin(); i!=bin.end(); i++)
	{
		*size += (i->data.size()) * sizeof(dataBin);
	}
	memcontent = (BYTE *)malloc(*size);
	BYTE * it = memcontent;
	for(vector<dataSection>::iterator i=bin.begin(); i!=bin.end(); i++)
	{
		for(vector<dataName>::iterator j=i->data.begin(); j!=i->data.end(); j++)
		{
			dataBin _bin;
			_bin.section = i->section;
			_bin.name = j->name;
			_bin.value = j->value;
			memcpy(it, &_bin, sizeof(dataBin));
			it += sizeof(dataBin);
		}
	}
	return memcontent;
}

bool Data::iWrite(BYTE type, DWORD section, DWORD name, int value)
{
	getFile(type);
	if(nowfilename)
	{
		if(type == DATA_BINFILE)
		{
			*AttachValue(section, name) = value;
			return true;
		}
		else
		{
			hge->Ini_SetInt(translateSection(section), translateName(name), value, nowfilename);
			return true;
/*
			sprintf(buf, "%d", value);
			if(WritePrivateProfileString(translateSection(section), translateName(name), buf, nowfilename))
				return true;*/

		}
	}
	return false;
}
int Data::iRead(BYTE type, DWORD section, DWORD name, int def_val)
{
	getFile(type);
	if(nowfilename)
	{
		if(type == DATA_BINFILE)
		{
			return (int)(*AttachValue(section, name, def_val));
		}
		else
		{
			return hge->Ini_GetInt(translateSection(section), translateName(name), def_val, nowfilename);
/*
			if(GetPrivateProfileString(translateSection(section), translateName(name), "", buf, sizeof(buf), nowfilename))
			{
				return atoi(buf);
			}*/

		}
	}
	return def_val;
}
bool Data::lWrite(BYTE type, DWORD section, DWORD name, LONGLONG value)
{
	getFile(type);
	if(nowfilename)
	{
		if(type == DATA_BINFILE)
		{
			*AttachValue(section, name) = value;
			return true;
		}
		else
		{
			sprintf(buf, "%d", value);
			hge->Ini_SetString(translateSection(section), translateName(name), buf, nowfilename);
			return true;
/*
			_i64toa(value, buf, 10);
			if(WritePrivateProfileString(translateSection(section), translateName(name), buf, nowfilename))
				return true;*/

		}
	}
	return false;
}
LONGLONG Data::lRead(BYTE type, DWORD section, DWORD name, LONGLONG def_val)
{
	getFile(type);
	if(nowfilename)
	{
		if(type == DATA_BINFILE)
		{
			return *AttachValue(section, name, def_val);
		}
		else
		{
			strcpy(buf, hge->Ini_GetString(translateSection(section), translateName(name), "", nowfilename));
			if (!strlen(buf))
			{
				return def_val;
			}
			else
			{
				LONGLONG value;
				sscanf(buf, "%d", &value);
				return value;
			}
/*
			if(GetPrivateProfileString(translateSection(section), translateName(name), "", buf, sizeof(buf), nowfilename))
			{
				return _atoi64(buf);
			}*/

		}
	}
	return def_val;
}
bool Data::fWrite(BYTE type, DWORD section, DWORD name, float value)
{
	getFile(type);
	if(nowfilename)
	{
		if(type == DATA_BINFILE)
		{
			*AttachValue(section, name) = *((DWORD *)(&value));
			return true;
		}
		else
		{
			hge->Ini_SetFloat(translateSection(section), translateName(name), value, nowfilename);
			return true;
/*
			sprintf(buf, "%f", value);
			if(WritePrivateProfileString(translateSection(section), translateName(name), buf, nowfilename))
				return true;*/

		}
	}
	return false;
}
float Data::fRead(BYTE type, DWORD section, DWORD name, float def_val)
{
	getFile(type);
	if(nowfilename)
	{
		if(type == DATA_BINFILE)
		{
			return *((float *)(AttachValue(section, name, *((float *)&def_val))));
		}
		else
		{
			return hge->Ini_GetFloat(translateSection(section), translateName(name), def_val, nowfilename);
/*
			if(GetPrivateProfileString(translateSection(section), translateName(name), "", buf, sizeof(buf), nowfilename))
			{
				return float(atof(buf));
			}*/

		}
	}
	return def_val;
}
bool Data::sWrite(BYTE type, DWORD section, DWORD name, const char * value)
{
	getFile(type);
	if(nowfilename)
	{
		if(type == DATA_BINFILE)
		{
			*AttachValue(section, name) = *((LONGLONG *)value);
			return true;
		}
		else
		{
			hge->Ini_SetString(translateSection(section), translateName(name), value, nowfilename);
			return true;
/*
			if(WritePrivateProfileString(translateSection(section), translateName(name), value, nowfilename))
				return true;*/

		}
	}
	return false;
}
char * Data::sRead(BYTE type, DWORD section, DWORD name, const char * def_val)
{
	getFile(type);
	if(nowfilename)
	{
		if(type == DATA_BINFILE)
		{
			return (char *)(AttachValue(section, name, *((LONGLONG *)def_val)));
		}
		else
		{
			strcpy(buf, hge->Ini_GetString(translateSection(section), translateName(name), def_val, nowfilename));
//			GetPrivateProfileString(translateSection(section), translateName(name), def_val, buf, sizeof(buf), nowfilename);
		}
	}
	else
		strcpy(buf, def_val);
	return buf;
}

//
bool Data::SetEffectSystemResourceName(int effi, const char * filename)
{
	if(effi < 0 || effi >= DATASTRUCT_EFFECTMAX)
		return false;
	strcpy(BResource::bres.resdata.effectsysfilename[effi], filename);
	FILE * file = checkTableFile(DATA_EFFECTTABLEDEFINE);
	if (file == NULL)
	{
		return false;
	}
	char comment[2][M_STRMAX];
	fscanf(file, "%s%s", comment[0], comment[1]);
	fclose(file);
	file = NULL;

	getFile(DATA_EFFECTTABLEDEFINE);
	file = fopen(nowfilename, "wb");
	if (!file)
	{
		return false;
	}
	fprintf(file, "%x\t%s\t%x\r\n", GAME_VERSION, GAME_SIGNATURE, DATA_EFFECTTABLEDEFINE);
	fprintf(file, "%s\t%s\r\n", comment[0], comment[1]);
	for (int i=0; i<DATASTRUCT_EFFECTMAX; i++)
	{
		if (strlen(BResource::bres.resdata.effectsysfilename[i]))
		{
			fprintf(file, "%d\t%s\r\n", i, BResource::bres.resdata.effectsysfilename[i]);
		}
	}
	fclose(file);

	/*
	DWORD sec = sLinkType(RESDATAS_EFFECTSYS);
	DWORD name = nLinkNum(nLinkType(RESDATAN_TYPE), effi+1);
	if(!filename)
	{
		sWrite(DATA_RESOURCEFILE, sec, name, "");
	}
	else
	{
		sWrite(DATA_RESOURCEFILE, sec, name, filename);
	}
	*/
	return true;
}

bool Data::GetEffectSystemResourceName(int effi, char * filename)
{
	if(!filename || effi < 0 || effi >= DATASTRUCT_EFFECTMAX)
		return false;
	if (!strlen(BResource::bres.resdata.effectsysfilename[effi]))
	{
		return false;
	}
	strcpy(filename, BResource::bres.resdata.effectsysfilename[effi]);
	/*
	DWORD sec = sLinkType(RESDATAS_EFFECTSYS);
	DWORD name = nLinkNum(nLinkType(RESDATAN_TYPE), effi+1);
	char buffer[M_STRMAX];
	strcpy(buffer, sRead(DATA_RESOURCEFILE, sec, name, ""));
	if(!strlen(buffer))
		return false;
	strcpy(filename, buffer);
	*/
	return true;
}

int Data::nMeet(int sno, bool bSpell /* = false */)
{
	DWORD sec;
	sec = sLinkType(DATAS_SPELL);
	sec = sLinkNum(sec, sno);
	if(bSpell)
	{
		return iRead(DATA_BINFILE, sec, nLinkType(DATAN_MEETPRACTICE), 0);
	}
	else
	{
		return iRead(DATA_BINFILE, sec, nLinkType(DATAN_MEETGAME), 0);
	}
}

int Data::nGet(int sno, bool bSpell /* = false */)
{
	DWORD sec;
	sec = sLinkType(DATAS_SPELL);
	sec = sLinkNum(sec, sno);
	if(bSpell)
	{
		return iRead(DATA_BINFILE, sec, nLinkType(DATAN_GETPRACTICE), 0);
	}
	else
	{
		return iRead(DATA_BINFILE, sec, nLinkType(DATAN_GETGAME), 0);
	}
}

LONGLONG Data::nHighScore(int sno, BYTE difflv, bool bSpell /* = false */, bool bPractice /* = false */)
{
	DWORD sec;
	if(bSpell)
	{
		sec = sLinkType(DATAS_SPELL);
		sec = sLinkNum(sec, sno);
		return lRead(DATA_BINFILE, sec, nLinkType(DATAN_TOPBONUS), 0);
	}

	if(bPractice)
	{
		sec = sLinkType(DATAS_STAGEPRACTICE);
		sec = sLinkDiff(sec, difflv);
		sec = sLinkNum(sec, sno / M_STAGENSCENE);
		return lRead(DATA_BINFILE, sec, nLinkType(DATAN_TOPSCORE), 0);
	}

	sec = sLinkType(DATAS_TOP);
	sec = sLinkDiff(sec, difflv);
	sec = sLinkNum(sec, 1);

	return lRead(DATA_BINFILE, sec, nLinkType(DATAN_SCORE), 0);
}

int Data::nTryStageTime(int stage, BYTE difflv)
{
	DWORD sec;

	sec = sLinkType(DATAS_STAGEPRACTICE);
	sec = sLinkDiff(sec, difflv);
	sec = sLinkNum(sec, stage);

	return iRead(DATA_BINFILE, sec, nLinkType(DATAN_TRYTIME), 0);
}

LONGLONG Data::getTotalRunTime()
{
	LONGLONG firstruntime = lRead(DATA_BINFILE, sLinkType(DATAS_TOTAL), nLinkType(DATAN_FIRSTRUNTIME), 0);
	LONGLONG tlnowtime;
	tlnowtime = hge->Timer_GetFileTime();
/*
	FILETIME nowfiletime;
	SYSTEMTIME nowsystemtime;
	GetLocalTime(&nowsystemtime);
	SystemTimeToFileTime(&nowsystemtime, &nowfiletime);
	tlnowtime = (((LONGLONG)nowfiletime.dwHighDateTime)<<32) | nowfiletime.dwLowDateTime;
*/

	if (!firstruntime)
	{
		lWrite(DATA_BINFILE, sLinkType(DATAS_TOTAL), nLinkType(DATAN_FIRSTRUNTIME), tlnowtime);
		firstruntime = tlnowtime;
	}

	return (tlnowtime - firstruntime) / 10000000;
}