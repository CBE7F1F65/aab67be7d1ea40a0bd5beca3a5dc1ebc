#include "../header/BGLayer.h"
#include "../header/Main.h"
#include "../header/SpriteItemManager.h"
#include "../header/Scripter.h"
#include "../header/Export.h"
#include "../header/ProcessDefine.h"
#include "../header/Process.h"
#include "../Header/BResource.h"
#include "../Header/GameInput.h"

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
	timer = 0;
	texbegin = 0;
	largemapxtile = 0;
	largemapytile = 0;

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

void BGLayer::Action(bool active)
{
	DWORD stopflag = Process::mp.GetStopFlag();
	bool binstop = FRAME_STOPFLAGCHECK_(stopflag,FRAME_STOPFLAG_LAYER);
	if (!binstop)
	{
		if (active)
		{
			Scripter::scr.Execute(SCR_SCENE, bglayer.areaid, bglayer.timer);
		}

		if (bglayer.bSetup)
		{
			/*
			if (GameInput::GetKey(KSI_UP))
			{
				bglayer.mapceny+=3;
			}
			if (GameInput::GetKey(KSI_DOWN))
			{
				bglayer.mapceny-=3;
			}
			if (GameInput::GetKey(KSI_LEFT))
			{
				bglayer.mapcenx-=3;
			}
			if (GameInput::GetKey(KSI_RIGHT))
			{
				bglayer.mapcenx+=3;
			}
			*/
			bglayer.UpdateTileSprite();

			bglayer.tilesxoffset = -(bglayer.mapcenx - ((int)bglayer.mapcenx)/BGTILE_WIDTH*BGTILE_WIDTH);
			bglayer.tilesyoffset = bglayer.mapceny - ((int)bglayer.mapceny)/BGTILE_HEIGHT*BGTILE_HEIGHT;

			for (int i=0; i<BGTILEMAX; i++)
			{
				bglayer.bgtiles[i].action();
			}
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
	mapceny = M_MAINVIEW_HEIGHT/2;

	adatabegin = &(BResource::bres.areadata[Process::mp.stage * DATASTRUCT_STAGEAREAMAX]);

	areaData * padata = adatabegin;
	texbegin = adatabegin->texbegin;
	for (int i=0; i<DATASTRUCT_STAGEAREAMAX; i++)
	{
		if (padata->begintilex+padata->tilex > largemapxtile)
		{
			largemapxtile = padata->begintilex+padata->tilex;
		}
		largemapytile += padata->tiley;
		++padata;
	}
	padata = adatabegin;

	int mallocsize = sizeof(BGTileMapping) * largemapxtile*largemapytile;
	tilemapping = (BGTileMapping *)malloc(mallocsize);
	ZeroMemory(tilemapping, mallocsize);

	int nowtilelinebegin = 0;
	for (int i=0; i<DATASTRUCT_STAGEAREAMAX; i++)
	{
		if (padata->tilex == 0 || padata->tiley == 0)
		{
			break;
		}
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
		nowtilelinebegin += padata->tiley;
		++padata;
	}
	padata = adatabegin;

	UpdateTileSprite();

	for (int j=0; j<BGTILE_YCOUNTMAX; j++)
	{
		for (int i=0; i<BGTILE_XCOUNTMAX; i++)
		{
			bgtiles[j*BGTILE_XCOUNTMAX+i].x = (M_CLIENT_WIDTH-M_MAINVIEW_WIDTH - BGTILE_WIDTH)/2 + BGTILE_WIDTH * i;
			bgtiles[j*BGTILE_XCOUNTMAX+i].y = (BGTILE_HEIGHT)/2 + BGTILE_HEIGHT * (BGTILE_YCOUNTMAX-j-1);
		}
	}

	bSetup = true;
}

void BGLayer::UpdateTileSprite()
{
	int nowbegintilex = ((int)mapcenx)/BGTILE_WIDTH-BGTILE_XCOUNTMAX/2+1;
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

		if (largetilex < 0 || largetiley < 0 || largetilex >= BGLayer::bglayer.largemapxtile || largetiley >= BGLayer::bglayer.largemapytile)
		{
			SpriteItemManager::ChangeSprite(SpriteItemManager::nullIndex, sprite);
			return;
		}

		BGTileMapping * nowmapping = &(BGLayer::bglayer.tilemapping[largetiley*BGLayer::bglayer.largemapxtile + largetilex]);
		int texindex = BGLayer::bglayer.texbegin+nowmapping->texoffset;
		HTEXTURE tex(texindex, NULL);
		SpriteItemManager::SetSpriteData(sprite, tex, nowmapping->textilex*BGTILE_WIDTH, nowmapping->textiley*BGTILE_HEIGHT, BGTILE_WIDTH, BGTILE_HEIGHT);
	}
}