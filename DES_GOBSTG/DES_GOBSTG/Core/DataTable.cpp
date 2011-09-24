#include "../Header/Data.h"
#include "../Header/BResource.h"
#include "../Header/DataTable.h"
#include "../Header/SpriteItemManager.h"

_DataTable _DataTable::datatable;

#define _EOF_DATATABLE	(feof(file))
#define _CHECKEOF_DATATABLE	if (_EOF_DATATABLE)	\
								return false
#define _READSTRINGBUFFERLINE(X)	if (!ReadStringBuffer(X))	\
										return false
#define _BREAKCOMMENTBUFFER	if (!CommentBuffer())	\
								break
#define _INITTINT	ti = -1
#define _LOADTINT	(tint[++ti])
#define _SAVETINT	(&_LOADTINT)

#ifndef __INTEL_COMPILER
#define _DOSWAPTINT	int tbegin = 0;	\
					int tend = ti;	\
					while (tbegin < tend)	\
					{	\
						int tswapint = tint[tbegin];	\
						tint[tbegin] = tint[tend];	\
						tint[tend] = tswapint;	\
						++tbegin;	\
						--tend;	\
					}
#else
#define _DOSWAPTINT
#endif

_DataTable::_DataTable()
{
}

_DataTable::~_DataTable()
{
}

bool _DataTable::ReadStringBuffer(int nCol)
{
	if (!file)
	{
		return false;
	}
	for (int i=0; i<nCol; i++)
	{
		fscanf(file, "%s", buffer);
		_CHECKEOF_DATATABLE;
	}
	return true;
}

bool _DataTable::CommentBuffer()
{
	if (!file)
	{
		return false;
	}
	fscanf(file, "%s", buffer);
	_CHECKEOF_DATATABLE;
	if (buffer[0] == '#')
	{
		fscanf(file, "%[^\r\n]", bufferlong);
		_CHECKEOF_DATATABLE;
		CommentBuffer();
	}
	return true;
}

void _DataTable::SetFile(FILE * _file)
{
	file = _file;
}

bool _DataTable::DataTableDefine()
{
	_READSTRINGBUFFERLINE(2);
	strcpy(BResource::bres.resdata.customconstfilename, BResource::bres.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(BResource::bres.resdata.customconstfilename, buffer);
//	strcpy(BResource::bres.resdata.spelldefinefilename, BResource::bres.resdata.datafoldername);
//	_READSTRINGBUFFERLINE(2);
//	strcat(BResource::bres.resdata.spelldefinefilename, buffer);
	strcpy(BResource::bres.resdata.musicdefinefilename, BResource::bres.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(BResource::bres.resdata.musicdefinefilename, buffer);
	strcpy(BResource::bres.resdata.bulletdefinefilename, BResource::bres.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(BResource::bres.resdata.bulletdefinefilename, buffer);
	strcpy(BResource::bres.resdata.enemydefinefilename, BResource::bres.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(BResource::bres.resdata.enemydefinefilename, buffer);
	strcpy(BResource::bres.resdata.playerdefinefilename, BResource::bres.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(BResource::bres.resdata.playerdefinefilename, buffer);
	strcpy(BResource::bres.resdata.spritedefinefilename, BResource::bres.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(BResource::bres.resdata.spritedefinefilename, buffer);
	strcpy(BResource::bres.resdata.playershootdefinefilename, BResource::bres.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(BResource::bres.resdata.playershootdefinefilename, buffer);
	strcpy(BResource::bres.resdata.playerghostdefinefilename, BResource::bres.resdata.datafoldername);
	_READSTRINGBUFFERLINE(2);
	strcat(BResource::bres.resdata.playerghostdefinefilename, buffer);
	return true;
}

bool _DataTable::PackageTableDefine()
{
	ZeroMemory(BResource::bres.resdata.packagefilename, sizeof(char) * PACKAGEMAX * M_PATHMAX);
	_READSTRINGBUFFERLINE(3);
	while (!feof(file))
	{
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		fscanf(file, "%s", BResource::bres.resdata.packagefilename[tindex]);
	}
	return true;
}

bool _DataTable::TextureTableDefine()
{
	ZeroMemory(BResource::bres.texturedata, RSIZE_TEXTURE);
	_READSTRINGBUFFERLINE(5);
	while (!feof(file))
	{
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		textureData * item = &(BResource::bres.texturedata[tindex]);
		fscanf(file, "%s%d%d",
			item->texfilename,
			&(item->width),
			&(item->height)
			);
	}
	return true;
}

bool _DataTable::EffectTableDefine()
{
	ZeroMemory(BResource::bres.resdata.effectsysfilename, sizeof(char) * EFFECTSYSTYPEMAX * M_PATHMAX);
	_READSTRINGBUFFERLINE(3);
	while (!feof(file))
	{
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		fscanf(file, "%s", BResource::bres.resdata.effectsysfilename[tindex]);
	}
	return true;
}

bool _DataTable::SETableDefine()
{
	ZeroMemory(BResource::bres.resdata.sefilename, sizeof(char) * SEMAX * M_PATHMAX);
	_READSTRINGBUFFERLINE(3);
	while (!feof(file))
	{
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		fscanf(file, "%s", BResource::bres.resdata.sefilename[tindex]);
	}
	return true;
}

bool _DataTable::CustomConstFile()
{
//	BResource::bres.ReleaseCustomConst();
	BResource::bres.MallocCustomConst();
	ZeroMemory(BResource::bres.customconstdata, RSIZE_CUSTOMCONST);
	_READSTRINGBUFFERLINE(4);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;

		customconstData * item = &(BResource::bres.customconstdata[tindex]);
		fscanf(file, "%s%d", 
			item->name, 
			&(item->value));

		_DOSWAPTINT;
		_INITTINT;
	}
	return true;
}
/*
bool _DataTable::SpellDefineFile()
{
//	BResource::bres.spelldata.clear();
	ZeroMemory(BResource::bres.spelldata, RSIZE_SPELL);
	_READSTRINGBUFFERLINE(11);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		spellData * item = &(BResource::bres.spelldata[tindex]);

		fscanf(file, "%d\t%[^\t]%d%d%d%I64d%d%x%d", 
			&(item->spellnumber), 
			item->spellname, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			&(item->bonus), 
			&(item->turntoscene), 
			_SAVETINT, 
			_SAVETINT);

		_DOSWAPTINT;
		_INITTINT;
		item->timelimit = _LOADTINT;
		item->remain = _LOADTINT;
		item->userID = _LOADTINT;
		item->spellflag = _LOADTINT;
		item->battleID = _LOADTINT;
//		BResource::bres.spelldata.push_back(item);
	}
	return true;
}
*/
bool _DataTable::MusicDefineFile()
{
	ZeroMemory(BResource::bres.musdata, RSIZE_MUSIC);
	_READSTRINGBUFFERLINE(7);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		musicData * item = &(BResource::bres.musdata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "\t%[^\t]%s%d%d%d", 
			item->musicname, 
			item->musicfilename, 
			&(item->startpos), 
			&(item->introlength), 
			&(item->alllength));

		_DOSWAPTINT;
		_INITTINT;
	}
	return true;
}

bool _DataTable::BulletDefineFile()
{
	ZeroMemory(BResource::bres.bulletdata, RSIZE_BULLET);
	_READSTRINGBUFFERLINE(17);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		bulletData * item = &(BResource::bres.bulletdata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%s%d%d%d%f%f%d%d%d%d%d%d%d%d%x", 
			strbuffer[0],
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			&(item->collisionMain), 
			&(item->collisionSub), 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			&(item->nTurnAngle), 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT);

		_DOSWAPTINT;
		_INITTINT;
		item->siid = SpriteItemManager::GetIndexByName(strbuffer[0]);
		item->nRoll = _LOADTINT;
		item->nColor = _LOADTINT;
		item->collisiontype = _LOADTINT;
		item->fadecolor = _LOADTINT;
		item->whitecolor = _LOADTINT;
		item->autosendsetID = _LOADTINT;
		item->seID = _LOADTINT;
		item->effID = _LOADTINT;
		item->blendtype = _LOADTINT;
		item->renderdepth = _LOADTINT;
		item->renderflag = _LOADTINT;
	}
	return true;
}

bool _DataTable::EnemyDefineFile()
{
	ZeroMemory(BResource::bres.enemydata, RSIZE_ENEMY);
	_READSTRINGBUFFERLINE(31);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		enemyData * item = &(BResource::bres.enemydata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%d%s%f%f%x%d%d%d%d%d%d%d%d%d%d%d%d%d%d%f%d%d%d%d%f%f%f\t%[^\t]\t%[^\r\n]", 
			_SAVETINT, 
			strbuffer[0],
			&(item->collision_w), 
			&(item->collision_h), 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			&(item->effid), 
			&(item->shotEffid), 
			&(item->collapseEffid), 
			&(item->expoint), 
			&(item->ghostpoint), 
			&(item->bulletpoint), 
			&(item->spellpoint), 
			_SAVETINT, 
			&(item->blastr),
			&(item->blastpower),
			&(item->blastdamagerate), 
			item->name,
			item->ename);

		_DOSWAPTINT;
		_INITTINT;
		item->faceIndex  = _LOADTINT;
		item->siid = SpriteItemManager::GetIndexByName(strbuffer[0]);
		item->flag = _LOADTINT;
		item->standFrame  = _LOADTINT;
		item->rightPreFrame  = _LOADTINT;
		item->rightFrame = _LOADTINT;
		item->leftPreFrame  = _LOADTINT;
		item->leftFrame = _LOADTINT;
		item->attackPreFrame  = _LOADTINT;
		item->attackFrame = _LOADTINT;
		item->storePreFrame  = _LOADTINT;
		item->storeFrame  = _LOADTINT;
		item->nmaxset	=	_LOADTINT;
		item->nmax = _LOADTINT;
		item->blastmaxtime = _LOADTINT;
	}
	return true;
}

bool _DataTable::PlayerDefineFile()
{
	ZeroMemory(BResource::bres.playerdata, RSIZE_PLAYER);
	_READSTRINGBUFFERLINE(31);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		playerData * item = &(BResource::bres.playerdata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%f%f%f%f%f%d%d%d%f%f%f%x%s%s%s\t%[^\t]\t%[^\t]\t%[^\t]%d%s%d%d%d%d%d%d\t%[^\t]\t%[^\t]\t%[^\r\n]", 
			&(item->collision_r), 
			&(item->fastspeed), 
			&(item->slowspeed), 
			&(item->chargespeed), 
			&(item->addchargerate), 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			&(item->exsendparab), 
			&(item->exsendparaa), 
			&(item->exsendmax), 
			_SAVETINT, 
			strbuffer[0], 
			strbuffer[1], 
			strbuffer[2], 
			item->spellname[0], 
			item->spellname[1], 
			item->spellname[2], 
			_SAVETINT, 
			strbuffer[3], 
			&(item->aidraintime), 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			_SAVETINT, 
			item->scenename, 
			item->name,
			item->ename);

		_DOSWAPTINT;
		_INITTINT;
		item->shotdelay = _LOADTINT;
		item->rechargedelay = _LOADTINT;
		item->shootchargetime = _LOADTINT;
		item->infinmaxset = _LOADTINT;
		item->siid = SpriteItemManager::GetIndexByName(strbuffer[0]);
		item->faceSIID = SpriteItemManager::GetIndexByName(strbuffer[1]);
		item->spellcutinSIID = SpriteItemManager::GetIndexByName(strbuffer[2]);
		item->musicID = _LOADTINT;
		item->drainzoneSIID = SpriteItemManager::GetIndexByName(strbuffer[3]);
		item->standFrame = _LOADTINT;
		item->leftPreFrame = _LOADTINT;
		item->leftFrame = _LOADTINT;
		item->rightPreFrame = _LOADTINT;
		item->rightFrame = _LOADTINT;
	}
	return true;
}

bool _DataTable::SpriteDefineFile()
{
	fscanf(file, "%d", &(BResource::bres.spritenumber));
	BResource::bres.InitSpriteData();
//	ZeroMemory(BResource::bres.spritedata, RSIZE_SPRITE);
	_READSTRINGBUFFERLINE(8);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		spriteData * item = &(BResource::bres.spritedata[tindex]);

		fscanf(file, "%s%d%f%f%f%f", 
			item->spritename, 
			&(item->tex),
			&(item->tex_x), 
			&(item->tex_y), 
			&(item->tex_w), 
			&(item->tex_h));

		_DOSWAPTINT;
		_INITTINT;
	}
	return true;
}

bool _DataTable::PlayerShootDefineFile()
{
	ZeroMemory(BResource::bres.playershootdata, RSIZE_PLAYERSHOOT);
	_READSTRINGBUFFERLINE(20);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		playershootData * item = &(BResource::bres.playershootdata[tindex]);

		fscanf(file, "%d%d%s%d%d%x%f%d%d%d%d%f%f%f%f%f%f%d", 
			_SAVETINT, 
			_SAVETINT, 
			strbuffer[0],
			_SAVETINT, 
			&(item->hitonfactor), 
			_SAVETINT, 
			&(item->power), 
			&(item->deletetime),
			_SAVETINT, 
			&(item->angle), 
			&(item->addangle), 
			&(item->speed), 
			&(item->accelspeed),
			&(item->scale),
			&(item->collisionr),
			&(item->xbias), 
			&(item->ybias),  
			_SAVETINT);

		_DOSWAPTINT;
		_INITTINT;
		item->userID = _LOADTINT;
		item->bchargeshoot = (bool)_LOADTINT;
		item->siid = SpriteItemManager::GetIndexByName(strbuffer[0]);
		item->timeMod = _LOADTINT;
		item->flag = _LOADTINT;
		item->arrange = _LOADTINT;
		item->seID = _LOADTINT;
	}
	return true;
}

bool _DataTable::PlayerGhostDefineFile()
{
	ZeroMemory(BResource::bres.playerghostdata, RSIZE_PLAYERGHOST);
	_READSTRINGBUFFERLINE(12);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		playerghostData * item = &(BResource::bres.playerghostdata[tindex]);

		fscanf(file, "%s%f%f%f%x%d%d%f%d%d", 
			strbuffer[0],  
			&(item->xadj), 
			&(item->yadj), 
			&(item->speed), 
			_SAVETINT, 
			_SAVETINT, 
			&(item->shootangle), 
			&(item->mover), 
			&(item->startangle),
			_SAVETINT);

		_DOSWAPTINT;
		_INITTINT;
		item->siid = SpriteItemManager::GetIndexByName(strbuffer[0]);
		item->flag = _LOADTINT;
		item->rolltime = _LOADTINT;
		item->blend = _LOADTINT;
	}
	return true;
}


FILE * Data::checkTableFile(BYTE type)
{
	getFile(type);
	if (!nowfilename)
	{
		return NULL;
	}
	FILE * file = fopen(hge->Resource_MakePath(nowfilename), "rb");
	if (!file)
	{
		return NULL;
	}
	int tgameversion = -1;
	char tsignature[M_STRMAX];
	int tfiletype = -1;

	fscanf(file, "%x%s%x", &tgameversion, tsignature, &tfiletype);
	if (tgameversion != GAME_VERSION || strcmp(tsignature, GAME_SIGNATURE) || tfiletype != type)
	{
		fclose(file);
		return NULL;
	}
	return file;
}

bool Data::GetTableFile(BYTE type)
{
	if (!(type & DATA_TABLEHEADER))
	{
		return false;
	}
	FILE * file = checkTableFile(type);
	if (file == NULL)
	{
		return false;
	}

	_DataTable::datatable.SetFile(file);

	char buffer[M_STRMAX];
	int tindex;
	int tint[32];
	switch (type)
	{
	case DATA_DATATABLEDEFINE:
		_DataTable::datatable.DataTableDefine();
		break;
	case DATA_PACKAGETABLEDEFINE:
		_DataTable::datatable.PackageTableDefine();
		break;
	case DATA_TEXTURETABLEDEFINE:
		_DataTable::datatable.TextureTableDefine();
		break;
	case DATA_EFFECTTABLEDEFINE:
		_DataTable::datatable.EffectTableDefine();
		break;
	case DATA_SETABLEDEFINE:
		_DataTable::datatable.SETableDefine();
		break;

	case DATA_CUSTOMCONSTFILE:
		_DataTable::datatable.CustomConstFile();
		break;
		/*
	case DATA_SPELLDEFINEFILE:
		_DataTable::datatable.SpellDefineFile();
		break;
		*/
	case DATA_MUSICDEFINEFILE:
		_DataTable::datatable.MusicDefineFile();
		break;

	case DATA_BULLETDEFINEFILE:
		_DataTable::datatable.BulletDefineFile();
		break;
	case DATA_ENEMYDEFINEFILE:
		_DataTable::datatable.EnemyDefineFile();
		break;
	case DATA_PLAYERDEFINEFILE:
		_DataTable::datatable.PlayerDefineFile();
		break;
	case DATA_SPRITEDEFINEFILE:
		_DataTable::datatable.SpriteDefineFile();
		break;

	case DATA_PLAYERSHOOTDEFINE:
		_DataTable::datatable.PlayerShootDefineFile();
		break;
	case DATA_PLAYERGHOSTDEFINE:
		_DataTable::datatable.PlayerGhostDefineFile();
		break;
	}
	fclose(file);
	return true;
}
