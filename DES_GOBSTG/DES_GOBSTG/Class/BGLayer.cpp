#include "../Header/BGLayer.h"
#include "../Header/Main.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/Scripter.h"
#include "../Header/Export.h"
#include "../Header/ProcessDefine.h"
#include "../Header/Process.h"
#include "../Header/BResource.h"
#include "../Header/GameInput.h"
#include "../Header/Player.h"

BGLayer BGLayer::bglayer;

BGLayer::BGLayer()
{
}

BGLayer::~BGLayer()
{
	Release();
}

void BGLayer::Release()
{
	areaid = 0;
	texbegin = 0;
	largemapxtile = 0;
	largemapytile = 0;
	bossytile = 0;

	mapcenx = 0;
	mapxoffset = 0;
	mapceny = 0;
	lastmapcenx = 0;
	lastmapceny = 0;

	xspeed = 0;
	yspeed = 0;

	adatabegin = NULL;

	bSetup = false;

	if (tilemapping)
	{
		free(tilemapping);
		tilemapping = NULL;
	}

	for (int i=0; i<BGTILEMAX; i++)
	{
		bgtiles[i].Release();
	}
}

void BGLayer::Init()
{
	Release();
}

void BGLayer::action()
{
	if (bSetup)
	{
		/*
		if (GameInput::GetKey(KSI_UP))
		{
			mapceny+=3;
		}
		if (GameInput::GetKey(KSI_DOWN))
		{
			mapceny-=3;
		}
		if (GameInput::GetKey(KSI_LEFT))
		{
			mapcenx-=3;
		}
		if (GameInput::GetKey(KSI_RIGHT))
		{
			mapcenx+=3;
		}
		*/
		lastmapcenx = mapcenx;
		lastmapceny = mapceny;

		mapcenx += xspeed;
		mapceny += yspeed;

		UpdateTileSprite();

		tilesxoffset = -(bglayer.mapcenx - ((int)(bglayer.mapcenx))/BGTILE_WIDTH*BGTILE_WIDTH);
		tilesyoffset = bglayer.mapceny - ((int)bglayer.mapceny)/BGTILE_HEIGHT*BGTILE_HEIGHT;

		for (int i=0; i<BGTILEMAX; i++)
		{
			bgtiles[i].action();
		}
	}
}

void BGLayer::Action(bool active)
{
	DWORD stopflag = Process::mp.GetStopFlag();
	bool binstop = FRAME_STOPFLAGCHECK_(stopflag,FRAME_STOPFLAG_LAYER);
	if (!binstop)
	{
		if (active)
		{
			Scripter::scr.Execute(SCR_SCENE, bglayer.areaid, gametime);
			bglayer.action();
		}
	}
}

void BGLayer::RenderAll()
{
	for (int i=0; i<BGTILEMAX; i++)
	{
		bglayer.bgtiles[i].Render();
	}
}


void BGLayer::BGLayerSetup(float begincenx)
{
	Release();
	for (int i=0; i<BGTILEMAX; i++)
	{
		bgtiles[i].init();
	}

	mapcenx = begincenx;
	mapceny = M_GAMESQUARE_HEIGHT/2;

	adatabegin = &(BResource::bres.stageareadata[Process::mp.stage * DATASTRUCT_AREAPERSTAGEMAX]);

	stageareaData * padata = adatabegin;
	texbegin = adatabegin->texbegin;
	for (int i=0; i<DATASTRUCT_AREAPERSTAGEMAX; i++)
	{
		if (padata->begintilex+padata->tilex > largemapxtile)
		{
			largemapxtile = padata->begintilex+padata->tilex;
		}
		largemapytile += padata->tiley;
		if (padata->tiley)
		{
			bossytile = padata->tiley;
		}
		++padata;
	}
	padata = adatabegin;

	int mallocsize = sizeof(BGTileMapping) * largemapxtile*largemapytile;
	tilemapping = (BGTileMapping *)malloc(mallocsize);
	ZeroMemory(tilemapping, mallocsize);

	int nowtilelinebegin = 0;
	for (int i=0; i<DATASTRUCT_AREAPERSTAGEMAX; i++)
	{
		if (padata->tilex == 0 || padata->tiley == 0)
		{
			break;
		}

		if (padata->begintile >= 0)
		{
			//
			int nowtilenum = padata->begintile;
			int nowtexoffset = padata->texbegin-adatabegin->texbegin;
			//

			int savednexttilenum = -1;
			int savednexttexoffset = -1;

			for (int j=0; j<padata->tiley; j++)
			{

				int nowtilenumbase = nowtilenum;
				int nowtexoffsetbase = nowtexoffset;

				int lasttilenum = -1;
				int lasttexoffset = -1;

				for (int k=0; k<=padata->tilex; k++)
				{
					if (k == padata->tilex)
					{
						if (lasttilenum < 0 || lasttexoffset < 0)
						{
							break;
						}
						if (!((nowtilenum%BGTILE_SUBTILE_TOTALTILECOUNT)/BGTILE_SUBTILE_XTILECOUNT))
						{
							savednexttilenum = nowtilenum;
							savednexttexoffset = nowtexoffset;

							nowtilenum = lasttilenum;
							nowtexoffset = lasttexoffset;
						}
						break;
					}

					lasttilenum = nowtilenum;
					lasttexoffset = nowtexoffset;

					BGTileMapping * nowtilemapping = &(tilemapping[(j+nowtilelinebegin)*largemapxtile+padata->begintilex+k]);
					nowtilemapping->texoffset = nowtexoffset;
					nowtilemapping->textilex = ((nowtilenum/BGTILE_SUBTILE_TOTALTILECOUNT)/BGTILE_SUBTILE_XCOUNT*BGTILE_SUBTILE_XTILECOUNT + nowtilenum%BGTILE_SUBTILE_XTILECOUNT);
					nowtilemapping->textiley = ((nowtilenum/BGTILE_SUBTILE_TOTALTILECOUNT)%BGTILE_SUBTILE_YCOUNT*BGTILE_SUBTILE_YTILECOUNT + (BGTILE_SUBTILE_YTILECOUNT-(nowtilenum/BGTILE_SUBTILE_XTILECOUNT)%BGTILE_SUBTILE_YTILECOUNT-1));

					nowtilenum++;
					if (!(nowtilenum % BGTILE_SUBTILE_XTILECOUNT))
					{
						nowtilenum += BGTILE_SUBTILE_TOTALTILECOUNT-BGTILE_SUBTILE_XTILECOUNT;
						if (nowtilenum >= BGTILE_TOTALTILECOUNT)
						{
							nowtilenum -= BGTILE_TOTALTILECOUNT;
							nowtexoffset++;
						}
					}
				}

				nowtilenum = nowtilenumbase + BGTILE_SUBTILE_XTILECOUNT;
				nowtexoffset = nowtexoffsetbase;
				if (!((nowtilenum%BGTILE_SUBTILE_TOTALTILECOUNT)/BGTILE_SUBTILE_XTILECOUNT))
				{
					nowtilenum = savednexttilenum;
					nowtexoffset = savednexttexoffset;
				}
				if (nowtilenum >= BGTILE_TOTALTILECOUNT)
				{
					nowtilenum -= BGTILE_TOTALTILECOUNT;
					nowtexoffset++;
				}
			}
			//
		}
		else
		{
			// For Debug
			for (int j=0; j<padata->tiley; j++)
			{
				for (int k=0; k<=padata->tilex; k++)
				{
					BGTileMapping * nowtilemapping = &(tilemapping[(padata->tiley-j-1)*padata->tilex+k]);
					nowtilemapping->texoffset = 0;
					nowtilemapping->textilex = k;
					nowtilemapping->textiley = j;
				}
			}
		}
		nowtilelinebegin += padata->tiley;
		++padata;
	}
	padata = adatabegin;

	UpdateTileSprite();

	for (int j=0; j<BGTILE_YCOUNTMAX; j++)
	{
		for (int i=0; i<BGTILE_XCOUNTMAX; i++)
		{
			bgtiles[j*BGTILE_XCOUNTMAX+i].x = M_GAMESQUARE_LEFT - BGTILE_WIDTH/2 + BGTILE_WIDTH * i;
			bgtiles[j*BGTILE_XCOUNTMAX+i].y = M_GAMESQUARE_TOP-(BGTILE_HEIGHT)/2 + BGTILE_HEIGHT * (BGTILE_YCOUNTMAX-j-1);
		}
	}

	bSetup = true;
}

void BGLayer::SetMapSpeedInfo(float _xspeed, float _yspeed, float _mapxoffset)
{
	xspeed = _xspeed;
	yspeed = _yspeed;
	if (!((Player::p.flag & PLAYER_MERGE) || (Player::p.flag & PLAYER_COLLAPSE)))
	{
		mapxoffset = _mapxoffset;
	}
}

void BGLayer::UpdateTileSprite()
{
	int nowbegintilex = ((int)(mapcenx))/BGTILE_WIDTH-BGTILE_XCOUNTMAX/2+1;
	int nowbegintiley = ((int)mapceny)/BGTILE_HEIGHT-BGTILE_YCOUNTMAX/2+1;
	for (int j=0; j<BGTILE_YCOUNTMAX; j++)
	{
		for (int i=0; i<BGTILE_XCOUNTMAX; i++)
		{
			bgtiles[j*BGTILE_XCOUNTMAX+i].SetSpriteByXY(nowbegintilex+i, nowbegintiley+j);
		}
	}
}
/*
bool BGLayer::CheckBlank(int * tilenum, int * texoffset)
{
	if (!tilenum || !texoffset)
	{
		return true;
	}
	int checktile = (*tilenum)-(*tilenum)%BGTILE_SUBTILE_XTILECOUNT;
	for (int i=0; i<DATASTRUCT_BLANKMAPTILEMAX; i++)
	{
		if (BResource::bres.blankmaptiledata[i].stage == Process::mp.stage)
		{
			if (checktile == BResource::bres.blankmaptiledata[i].texnumber && (*texoffset) == BResource::bres.blankmaptiledata[i].texoffset)
			{
				*tilenum += BGTILE_SUBTILE_XTILECOUNT;
				if (*tilenum >= BGTILE_TOTALTILECOUNT)
				{
					*tilenum -= BGTILE_TOTALTILECOUNT;
					(*texoffset)++;
				}
				return CheckBlank(tilenum, texoffset);
			}
		}
		else if(BResource::bres.blankmaptiledata[i].stage > Process::mp.stage)
		{
			break;
		}
	}

	return false;
}
*/

BGTile::BGTile()
{

}

BGTile::~BGTile()
{

}

void BGTile::init()
{
	sprite = SpriteItemManager::CreateNullSprite();
	largetilex = -1;
	largetiley = -1;
}

void BGTile::Release()
{
	if (sprite)
	{
		SpriteItemManager::FreeSprite(&sprite);
	}
}

void BGTile::Render()
{
	if (sprite)
	{
		sprite->Render(x+BGLayer::bglayer.tilesxoffset, y+BGLayer::bglayer.tilesyoffset);
	}
}

void BGTile::action()
{
}

void BGTile::SetSpriteByXY(int _largetilex, int _largetiley)
{
	if (largetilex!=_largetilex || largetiley!=_largetiley)
	{
		largetilex = _largetilex;
		largetiley = _largetiley;

		while (largetiley >= BGLayer::bglayer.largemapytile)
		{
			largetiley -= BGLayer::bglayer.bossytile;
		}

		if (largetilex < 0 || largetiley < 0 || largetilex >= BGLayer::bglayer.largemapxtile)
		{
			SpriteItemManager::ChangeSprite(SpriteItemManager::nullIndex, sprite);
			return;
		}

		BGTileMapping * nowmapping = &(BGLayer::bglayer.tilemapping[largetiley*BGLayer::bglayer.largemapxtile + largetilex]);
		int texindex = BGLayer::bglayer.texbegin+nowmapping->texoffset;
		if (nowmapping->texoffset > 1 || nowmapping->texoffset < 0)
		{
			texindex = 0;
		}
		HTEXTURE tex(texindex, NULL);
		SpriteItemManager::SetSpriteData(sprite, tex, nowmapping->textilex*BGTILE_WIDTH, nowmapping->textiley*BGTILE_HEIGHT, BGTILE_WIDTH, BGTILE_HEIGHT);
	}
}