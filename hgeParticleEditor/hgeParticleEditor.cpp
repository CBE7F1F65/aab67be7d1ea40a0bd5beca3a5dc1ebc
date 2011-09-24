#include "../include/hge.h"
#include "../DES_GOBSTG/DES_GOBSTG/Header/Export.h"
#include "../DES_GOBSTG/DES_GOBSTG/Header/ConstResource.h"
#include "../DES_GOBSTG/DES_GOBSTG/Header/BResource.h"
#include "../DES_GOBSTG/DES_GOBSTG/Header/Data.h"
#include "../include/hgeEffectSystem.h"
#include "EditorRes.h"
#include "EditorUI.h"

HGE * hge = hgeCreate(HGE_VERSION);

bool FrameFunc()
{
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	if(hge->Input_GetKeyState(HGEK_CTRL) && hge->Input_GetKeyState(HGEK_BACKSPACE))
	{
		if(!eres.Load())
			return true;
		ui.timer = 0;
	}
	ui.Update();

	return false;
}

bool RenderFunc()
{
	if (hge->System_GetState(HGE_2DMODE))
	{
		Export::clientSetMatrix();
	}
	else
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);

		D3DXMATRIXA16 matView;
		D3DXVECTOR3 vEyePt( M_ACTIVECLIENT_CENTER_X, M_ACTIVECLIENT_CENTER_Y, M_ACTIVECLIENT_HEIGHT/2);
		D3DXVECTOR3 vLookatPt( M_ACTIVECLIENT_CENTER_X, M_ACTIVECLIENT_CENTER_Y, 0 );
		D3DXVECTOR3 vUpVec( 0.0f, -1.0f, 0.0f );
		D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );


		D3DXMATRIXA16 matProj;
		D3DXMATRIXA16 tmat;
		D3DXMatrixIdentity(&matProj);
		D3DXMatrixTranslation(&tmat, -0.5f, 0.5f, 0.0f);
		D3DXMatrixMultiply(&matProj, &matProj, &tmat);
		D3DXMatrixPerspectiveOffCenterLH( &tmat, -M_ACTIVECLIENT_CENTER_X, M_ACTIVECLIENT_CENTER_X+(M_CLIENT_WIDTH-M_ACTIVECLIENT_WIDTH), -M_CLIENT_CENTER_Y, M_CLIENT_CENTER_Y, M_CLIENT_HEIGHT/2, 0 );
		D3DXMatrixMultiply(&matProj, &matProj, &tmat);

		Export::clientSetMatrixUser(matWorld, matView, matProj);
	}
	
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0x00000000);

	ui.Render();

	hge->Gfx_EndScene();
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);

	if (!Export::clientInitial(false, true))
	{
		hge->System_SetState(HGE_TITLE, "HGE Effect System Editor by h5nc");
	}

	if(hge->System_Initiate())
	{
		Export::clientAfterInitial(RESCONFIGDEFAULT_SCREENSCALE);
		if(eres.Load())
		{
			hge->System_Start();
		}
	}
	eres.Release();

//	hge->System_Shutdown();
	hge->Release();
}