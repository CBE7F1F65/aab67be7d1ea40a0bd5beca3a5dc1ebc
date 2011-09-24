#include "Const.h"

class _DataTable
{
public:
	_DataTable();
	~_DataTable();
public:
	void SetFile(FILE * file);
	bool DataTableDefine();
	bool PackageTableDefine();
	bool TextureTableDefine();
	bool EffectTableDefine();
	bool SETableDefine();
	bool CustomConstFile();
//	bool SpellDefineFile();
	bool MusicDefineFile();
	bool BulletDefineFile();
	bool EnemyDefineFile();
	bool PlayerDefineFile();
	bool SpriteDefineFile();
	bool PlayerShootDefineFile();
	bool PlayerGhostDefineFile();

	bool ReadStringBuffer(int nCol);
	bool CommentBuffer();

public:
	FILE * file;
	char buffer[M_STRMAX];
	char strbuffer[4][M_STRMAX];
	char bufferlong[M_STRMAX*4];
	int tindex;
	int tint[32];
	int ti;
	static _DataTable datatable;
};