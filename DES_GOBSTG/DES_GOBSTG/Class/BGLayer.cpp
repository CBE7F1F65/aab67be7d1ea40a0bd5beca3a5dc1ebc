#include "../header/BGLayer.h"
#include "../header/Main.h"
#include "../header/SpriteItemManager.h"
#include "../header/Scripter.h"
#include "../header/Export.h"
#include "../header/ProcessDefine.h"
#include "../header/Process.h"
#include "../Header/BResource.h"

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
		for (int i=0; i<BGTILEMAX; i++)
		{
			bglayer.bgtiles[i].action();
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


void BGLayer::BGLayerSetup()
{
	Release();
	for (int i=0; i<BGTILEMAX; i++)
	{
		bgtiles[i].init();
	}
}

BGTile::BGTile()
{

}

BGTile::~BGTile()
{

}

void BGTile::init()
{
	sprite = SpriteItemManager::CreateNullSprite();
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
		sprite->Render(x, y);
	}
}

void BGTile::action()
{
	x += BGLayer::bglayer.xspeed;
	y += BGLayer::bglayer.yspeed;

	if (x >= M_MAINVIEW_WIDTH + BGTILE_WIDTH/2)
	{
		x -= M_MAINVIEW_WIDTH;
	}
	else if (x < -BGTILE_WIDTH/2)
	{
		x += M_MAINVIEW_WIDTH;
	}
	if (y >= M_MAINVIEW_HEIGHT+BGTILE_HEIGHT/2)
	{
		y -= M_MAINVIEW_HEIGHT;
	}
	else if (y < -BGTILE_HEIGHT/2)
	{
		y += M_MAINVIEW_HEIGHT;
	}
}