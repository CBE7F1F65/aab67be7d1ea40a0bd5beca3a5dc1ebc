#include "../Header/processPrep.h"

void Process::_Render(BYTE renderflag/* =M_RENDER_NULL */)
{
	BYTE playerindex = Export::GetPlayerIndexByRenderFlag(renderflag);
	Export::clientSet3DMode();
	Export::clientSetMatrix(worldx[playerindex], worldy[playerindex], worldz[playerindex], renderflag);
	BGLayer::RenderBG(playerindex);
	Export::clientSet2DMode();
	Export::clientSetMatrix(worldx[playerindex], worldy[playerindex], worldz[playerindex], renderflag);
	if(renderflag != M_RENDER_NULL)
	{
		EventZone::RenderAll(playerindex);
		Enemy::RenderAll(playerindex);
		PlayerBullet::RenderAll(playerindex);
		Player::RenderAll(playerindex);
		Effectsys::RenderAll(playerindex);
		Beam::RenderAll(playerindex);
		Bullet::RenderAll(playerindex);
		Item::RenderAll(playerindex);
		Enemy::RenderScore(playerindex);
		FrontDisplay::fdisp.RenderSpellName(playerindex);
		FrontDisplay::fdisp.RenderHeadInfo(playerindex);
		//
		/*
		for (int i=M_GAMESQUARE_LEFT_(playerindex); i<M_GAMESQUARE_RIGHT_(playerindex); i++)
		{
			for (int j=M_GAMESQUARE_TOP; j<M_GAMESQUARE_BOTTOM; j++)
			{
				if (Player::p[playerindex].bDrain)
				{
					if (Enemy::CheckENAZ(playerindex, i, j, 1))
					{
						hge->Gfx_RenderLine(i, j, i+1, j);
					}
				}
			}
		}
		*/
		//
		//
		/*
		if (Bullet::bu[playerindex].getSize())
		{
			DWORD i = 0;
			DWORD size = Bullet::bu[playerindex].getSize();
			for (Bullet::bu[playerindex].toBegin(); i<size; Bullet::bu[playerindex].toNext(), i++)
			{
				if (Bullet::bu[playerindex].isValid())
				{
					if ((*(Bullet::bu[playerindex])).type == 44)
					{
						for (int i=M_GAMESQUARE_LEFT_(playerindex); i<M_GAMESQUARE_RIGHT_(playerindex); i++)
						{
							for (int j=M_GAMESQUARE_TOP; j<M_GAMESQUARE_BOTTOM; j++)
							{
								if ((*(Bullet::bu[playerindex])).isInRect(i, j, 1))
								{
									hge->Gfx_RenderLine(i, j, i+1, j, 0xffffff00);
								}
							}
						}
					}
				}
			}
		}
		*/
		/*
		if (Beam::be[playerindex].getSize())
		{
			DWORD i = 0;
			DWORD size = Beam::be[playerindex].getSize();
			for (Beam::be[playerindex].toBegin(); i<size; Beam::be[playerindex].toNext(), i++)
			{
				if (Beam::be[playerindex].isValid())
				{
					for (int i=M_GAMESQUARE_LEFT_(playerindex); i<M_GAMESQUARE_RIGHT_(playerindex); i++)
					{
						for (int j=M_GAMESQUARE_TOP; j<M_GAMESQUARE_BOTTOM; j++)
						{
							if ((*(Beam::be[playerindex])).isInRect(i, j, 1))
							{
								hge->Gfx_RenderLine(i, j, i+1, j, 0xffffff00);
							}
						}
					}
				}
			}
		}
		*/
		//
	}
	BGLayer::RenderFG(playerindex);
}

void Process::_RenderTar()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		if (rendertar[i])
		{
			if (sprendertar[i])
			{
				delete sprendertar[i];
			}
			sprendertar[i] = new hgeSprite(hge->Target_GetTexture(rendertar[i]), M_GAMESQUARE_LEFT_(i), M_GAMESQUARE_TOP, M_GAMESQUARE_WIDTH, M_GAMESQUARE_HEIGHT);
			SpriteItemManager::RenderSprite(sprendertar[i], M_GAMESQUARE_CENTER_X_(i), M_GAMESQUARE_CENTER_Y);
		}
	}
}

int Process::render()
{
#ifndef __WIN32
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0x00000000);
#endif

	bool isingame = IsInGame();
	if (isingame)
	{
#if defined __WIN32
		hge->Gfx_BeginScene(rendertar[0]);
		hge->Gfx_Clear(0x00000000);
#elif defined __PSP
		hge->Gfx_SetClipping(M_SIDE_EDGE, 0, SCREEN_WIDTH/2-M_SIDE_EDGE, SCREEN_HEIGHT);
#elif defined __IPHONE
		hge->Gfx_SetClipping(SCREEN_WIDTH*(1-screenscale), SCREEN_HEIGHT/2, SCREEN_WIDTH*screenscale, (SCREEN_HEIGHT/2-M_SIDE_EDGE)*screenscale);
#endif // __WIN32
		_Render(M_RENDER_LEFT);
#ifdef __WIN32
		hge->Gfx_EndScene();
#endif // __WIN32
#if defined __WIN32
		hge->Gfx_BeginScene(rendertar[1]);
		hge->Gfx_Clear(0x00000000);
#elif defined __PSP
		hge->Gfx_SetClipping(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2-M_SIDE_EDGE, SCREEN_HEIGHT);
#elif defined __IPHONE
		hge->Gfx_SetClipping(SCREEN_WIDTH*(1-screenscale), SCREEN_HEIGHT/2-(SCREEN_HEIGHT/2-M_SIDE_EDGE)*screenscale, SCREEN_WIDTH*screenscale, (SCREEN_HEIGHT/2-M_SIDE_EDGE)*screenscale);
#endif // __WIN32
		_Render(M_RENDER_RIGHT);
#ifdef __WIN32
		hge->Gfx_EndScene();
#endif // __WIN32
	}

#ifdef __WIN32
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0x00000000);
#else
	hge->Gfx_SetClipping(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
#endif // __WIN32
	Export::clientSetMatrix();
	if (state == STATE_INIT)
	{
		int ret = renderInit();
		hge->Gfx_EndScene();
		return ret;
	}
	//BGLayer

	if (!isingame)
	{
		_Render();
	}
	else
	{
		_RenderTar();
	}
	SpriteItemManager::RenderFrontSprite();
	FrontDisplay::fdisp.RenderPostPrint();

	FrontDisplay::fdisp.RenderPanel();

	if(isingame)
	{
		Chat::chatitem.Render();
		EffectSp::RenderAll();
		FrontDisplay::fdisp.RenderEnemyX();
	}
	BGLayer::RenderFGPause();
	SelectSystem::RenderAll();
	
#if defined __IPHONE
	Export::clientSetMatrix(0, 0, 0, M_RENDER_SUPER);
	SpriteItemManager::RenderFrontTouchButton();
#endif
	
	hge->Gfx_EndScene();
	return PGO;
}

int Process::renderInit()
{
	if (texInit.tex)
	{
		hgeQuad quad;
		quad.blend = BLEND_DEFAULT;
		quad.tex = texInit;
		quad.v[0].col = quad.v[1].col = quad.v[2].col = quad.v[3].col = 0xffffffff;
		quad.v[0].tx = 0;	quad.v[0].ty = 0;
		quad.v[1].tx = 1;	quad.v[1].ty = 0;
		quad.v[2].tx = 1;	quad.v[2].ty = 1;
		quad.v[3].tx = 0;	quad.v[3].ty = 1;
		quad.v[0].x = M_CLIENT_LEFT;	quad.v[0].y = M_CLIENT_TOP;	quad.v[0].z = 0;
		quad.v[1].x = M_CLIENT_RIGHT;	quad.v[1].y = M_CLIENT_TOP;	quad.v[1].z = 0;
		quad.v[2].x = M_CLIENT_RIGHT;	quad.v[2].y = M_CLIENT_BOTTOM;	quad.v[2].z = 0;
		quad.v[3].x = M_CLIENT_LEFT;	quad.v[3].y = M_CLIENT_BOTTOM;	quad.v[3].z = 0;
		SpriteItemManager::RenderQuad(&quad);
	}
	return PGO;
}