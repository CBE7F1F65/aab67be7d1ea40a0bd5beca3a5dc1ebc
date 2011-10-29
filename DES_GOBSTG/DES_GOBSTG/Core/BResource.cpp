#include "../Header/BResource.h"
#include "../Header/data.h"
#include "../Header/ConstResource.h"

BResource BResource::bres;

BResource::BResource()
{
	ZeroMemory(&resdata, RSIZE_RESOURCE);
	ZeroMemory(tex, sizeof(HTEXTURE) * DATASTRUCT_TEXMAX);
	ZeroMemory(texinfo, sizeof(hgeTextureInfo) * DATASTRUCT_TEXMAX);
	customconstdata = NULL;
	spritenumber = 0;
	spritedata = NULL;
}

BResource::~BResource()
{
	ReleaseSpriteData();
	ReleaseCustomConst();
}

void BResource::InitSpriteData()
{
	ReleaseSpriteData();
	spritedata = (spriteData *)malloc(RSIZE_SPRITE);
	ZeroMemory(spritedata, RSIZE_SPRITE);
}

void BResource::ReleaseSpriteData()
{
	if (spritedata)
	{
		free(spritedata);
		spritedata = NULL;
	}
}

void BResource::MallocCustomConst()
{
	ReleaseCustomConst();
	customconstdata = (customconstData *)malloc(RSIZE_CUSTOMCONST);
}

void BResource::ReleaseCustomConst()
{
	if (customconstdata)
	{
		free(customconstdata);
		customconstdata = NULL;
	}
}


//Scripter::LoadAll
bool BResource::Fill()
{
	return Data::data.GetAllTable();
}

bool BResource::Pack(void * pStrdesc, void * pCustomConstData)
{
//	if(pStrdesc == NULL || pCustomConstData == NULL)
//		return false;

	DWORD size = M_BINHEADER_OFFSET + 
		RSIZE_RESOURCE + 
		RSIZE_STRINGDESC + 
		RSIZE_CUSTOMCONST + 
		RSIZE_TEXTURE + 
		RSIZE_MUSIC + 
		RSIZE_BULLET + 
		RSIZE_ENEMY + 
		RSIZE_PLAYER + 
//		RSIZE_SPRITE + 
		RSIZE_PLAYERSHOOT + 
		RSIZE_PLAYERSUB + 
		RSIZE_STAGEAREA + 
		RSIZE_SPRITENUMBER +
		RSIZE_SPRITE;
	BYTE * content = (BYTE *)malloc(size);
	if(!content)
		return false;

	DWORD offset;

	BYTE * _header = Data::data.CreateMemHeader(DATA_RESOURCEFILE);
	if(!_header)
		return false;
	memcpy(content, _header, M_BINHEADER_OFFSET);
	offset = M_BINHEADER_OFFSET;
	free(_header);

	memcpy(content+offset, &resdata, RSIZE_RESOURCE);
	offset += RSIZE_RESOURCE;
	if (!pStrdesc)
	{
		ZeroMemory(content+offset, RSIZE_STRINGDESC);
	}
	else
	{
		memcpy(content+offset, pStrdesc, RSIZE_STRINGDESC);
	}
	offset += RSIZE_STRINGDESC;
	if (!pCustomConstData)
	{
		ZeroMemory(content+offset, RSIZE_CUSTOMCONST);
	}
	else
	{
		memcpy(content+offset, pCustomConstData, RSIZE_CUSTOMCONST);
	}
	offset += RSIZE_CUSTOMCONST;
	memcpy(content+offset, texturedata, RSIZE_TEXTURE);
	offset += RSIZE_TEXTURE;
	memcpy(content+offset, musdata, RSIZE_MUSIC);
	offset += RSIZE_MUSIC;
	memcpy(content+offset, bulletdata, RSIZE_BULLET);
	offset += RSIZE_BULLET;
	memcpy(content+offset, enemydata, RSIZE_ENEMY);
	offset += RSIZE_ENEMY;
	memcpy(content+offset, playerdata, RSIZE_PLAYER);
	offset += RSIZE_PLAYER;
//	memcpy(content+offset, spritedata, RSIZE_SPRITE);
	//	offset += RSIZE_SPRITE;
	memcpy(content+offset, playershootdata, RSIZE_PLAYERSHOOT);
	offset += RSIZE_PLAYERSHOOT;
	memcpy(content+offset, playerlaserdata, RSIZE_PLAYERLASER);
	offset += RSIZE_PLAYERLASER;
	memcpy(content+offset, playersubdata, RSIZE_PLAYERSUB);
	offset += RSIZE_PLAYERSUB;
	memcpy(content+offset, stageareadata, RSIZE_STAGEAREA);
	offset += RSIZE_STAGEAREA;

	memcpy(content+offset, &spritenumber, RSIZE_SPRITENUMBER);
	offset += RSIZE_SPRITENUMBER;
	memcpy(content+offset, spritedata, RSIZE_SPRITE);
	offset += RSIZE_SPRITE;
	/*
	for(vector<spellData>::iterator i=spelldata.begin(); i!=spelldata.end(); i++)
	{
		memcpy(content+offset, &(*i), sizeof(spellData));
		offset += sizeof(spellData);
	}
	*/

	hgeMemoryFile memfile;
	memfile.data = content;
	char tfilename[M_PATHMAX];
	strcpy(tfilename, RESDATASTR_RESFILENAME);
	memfile.filename = tfilename;
	memfile.size = size;

	bool ret = false;
	ret = hge->Resource_CreatePack(hge->Resource_MakePath(tfilename), Data::data.password, &memfile, NULL);

	free(content);

	return ret;
}

bool BResource::Gain(void * pStrdesc, void * pCustomConstData)
{
	BYTE * content;
	DWORD size;
	bool ret = false;

	hge->Resource_AttachPack(RESDATASTR_RESFILENAME, Data::data.password);
	content = hge->Resource_Load(RESDATASTR_RESFILENAME, &size);
	hge->Resource_RemovePack(RESDATASTR_RESFILENAME);
	if(content)
	{
//		spelldata.clear();
		if(Data::data.CheckMemHeader(content, size, DATA_RESOURCEFILE))
		{
			DWORD offset = M_BINHEADER_OFFSET;
			memcpy(&resdata, content+offset, RSIZE_RESOURCE);
			offset += RSIZE_RESOURCE;
			if(pStrdesc)
				memcpy(pStrdesc, content+offset, RSIZE_STRINGDESC);
			offset += RSIZE_STRINGDESC;
			if(pCustomConstData)
				memcpy(pCustomConstData, content+offset, RSIZE_CUSTOMCONST);
			offset += RSIZE_CUSTOMCONST;
			memcpy(texturedata, content+offset, RSIZE_TEXTURE);
			offset += RSIZE_TEXTURE;
			memcpy(musdata, content+offset, RSIZE_MUSIC);
			offset += RSIZE_MUSIC;
			memcpy(bulletdata, content+offset, RSIZE_BULLET);
			offset += RSIZE_BULLET;
			memcpy(enemydata, content+offset, RSIZE_ENEMY);
			offset += RSIZE_ENEMY;
			memcpy(playerdata, content+offset, RSIZE_PLAYER);
			offset += RSIZE_PLAYER;
//			memcpy(spritedata, content+offset, RSIZE_SPRITE);
//			offset += RSIZE_SPRITE;
			memcpy(playershootdata, content+offset, RSIZE_PLAYERSHOOT);
			offset += RSIZE_PLAYERSHOOT;
			memcpy(playerlaserdata, content+offset, RSIZE_PLAYERLASER);
			offset += RSIZE_PLAYERLASER;
			memcpy(playersubdata, content+offset, RSIZE_PLAYERSUB);
			offset += RSIZE_PLAYERSUB;
			memcpy(stageareadata, content+offset, RSIZE_STAGEAREA);
			offset += RSIZE_STAGEAREA;

			memcpy(&spritenumber, content+offset, RSIZE_SPRITENUMBER);
			offset += RSIZE_SPRITENUMBER;
			InitSpriteData();
			memcpy(spritedata, content+offset, RSIZE_SPRITE);
			/*
			while(offset < size)
			{
				spellData _rdata;
				memcpy(&_rdata, content+offset, sizeof(spellData));
				offset += sizeof(spellData);
				spelldata.push_back(_rdata);
			}
			*/
			ret = true;
		}
	}
	hge->Resource_Free(content);

	if(!hge->Resource_AccessFile(RESDATASTR_FOLDER_SNAPSHOT))
	{
		hge->Resource_CreateDirectory(RESDATASTR_FOLDER_SNAPSHOT);
	}
	if(!hge->Resource_AccessFile(RESDATASTR_FOLDER_REPLAY))
	{
		hge->Resource_CreateDirectory(RESDATASTR_FOLDER_REPLAY);
	}
	return ret;
}

bool BResource::LoadPackage(int packindex)
{
	if(strlen(resdata.packagefilename[packindex]) && !hge->Resource_AttachPack(resdata.packagefilename[packindex], Data::data.password))
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in Loading Package File %s.", HGELOG_ERRSTR, resdata.packagefilename[packindex]);
#endif
		return false;
	}
	return true;
}

bool BResource::LoadAllPackage()
{
	for(int i=0; i<DATASTRUCT_PACKAGEMAX; i++)
	{
		if (!LoadPackage(i))
		{
			return false;
		}
	}
	return true;
}

void BResource::InitTexinfo()
{
	for (int i=0; i<DATASTRUCT_TEXMAX; i++)
	{
		texinfo[i].tex = NULL;
		texinfo[i].texw = texturedata[i].width;
		texinfo[i].texh = texturedata[i].height;
	}
	for (int i=0; i<DATASTRUCT_TEXMAX; i++)
	{
		tex[i].texindex = i;
		texinfo[i].tex = &tex[i].tex;
	}
	hge->Gfx_SetTextureInfo(DATASTRUCT_TEXMAX, texinfo);
}

bool BResource::LoadTexture( int texindex/*=-1*/ )
{
	if (texindex < 0)
	{
		for (int i=0; i<DATASTRUCT_TEXMAX; i++)
		{
			LoadTexture(i);
		}
		return true;
	}

	char tnbuffer[M_STRMAX];
	if(tex[texindex].tex)
		hge->Texture_Free(tex[texindex]);
	tex[texindex].tex = NULL;

	strcpy(tnbuffer, bres.texturedata[texindex].texfilename);
	if(strlen(tnbuffer))
	{
		tex[texindex] = hge->Texture_Load(tnbuffer);
//		strcpy(tnbuffer, BResource::bres.resdata.texfilename[TEX_WHITE]);
	}

	if(tex[texindex].tex == NULL)
	{
#ifdef __DEBUG_LOG
		HGELOG("%s\nFailed in loading Texture File %s.(To be assigned to Index %d).", HGELOG_ERRSTR, tnbuffer, texindex);
#endif
//		tex[i] = tex[TEX_WHITE];
		tex[texindex] = hge->Texture_Create(0, 0);
		return false;
	}
#ifdef __DEBUG_LOG
	else
	{
		HGELOG("Succeeded in loading Texture File %s.(Assigned to Index %d).", tnbuffer, texindex);
	}
#endif
	tex[texindex].texindex = texindex;
	return true;
}

bool BResource::FreeTexture( int texindex/*=-1*/ )
{
	if (texindex < 0)
	{
		for (int i=0; i<DATASTRUCT_TEXMAX; i++)
		{
			FreeTexture(i);
		}
		return true;
	}

	if (tex[texindex].tex)
	{
		hge->Texture_Free(tex[texindex]);
		tex[texindex] = NULL;
		tex[texindex].texindex = texindex;
		return true;
	}
	return false;
}

/*
int BResource::SplitString(const char * str)
{
	if (str == NULL)
	{
		return 0;
	}
	for (int k=0; k<M_SCRIPTFOLDERMAX; k++)
	{
		strcpy(scriptfolder[k], "");
	}
	int length = strlen(str);
	int i = 0;
	int j = 0;
	int n = 0;
	while (i <= length)
	{
		if (str[i] == '|' || str[i] == 0)
		{
			scriptfolder[n][j] = 0;
			n++;
			j = 0;
		}
		else
		{
			scriptfolder[n][j] = str[i];
			j++;
		}
		i++;
	}
	return n;
}
*/