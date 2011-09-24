#include "../Header/SpriteItemManager.h"
#include "../Header/FrontDisplayName.h"
#include "../Header/BResource.h"

int SpriteItemManager::nullIndex = 0;
int SpriteItemManager::yesIndex = 0;
int SpriteItemManager::noIndex = 0;
int SpriteItemManager::cancelIndex = 0;
int SpriteItemManager::confirmIndex = 0;

FrontSprite SpriteItemManager::frontsprite[FRONTSPRITEMAX];

#if defined __IPHONE
FrontTouchButton SpriteItemManager::ftbutton[M_PL_MATCHMAXPLAYER][FTBUTTON_MAX];
#endif

SpriteItemManager::SpriteItemManager()
{
	ZeroMemory(frontsprite, sizeof(FrontSprite) * FRONTSPRITEMAX);
#if defined __IPHONE
	ZeroMemory(ftbutton, sizeof(FrontTouchButton)*M_PL_MATCHMAXPLAYER*FTBUTTON_MAX);
#endif
}

SpriteItemManager::~SpriteItemManager()
{

}

bool SpriteItemManager::LoadTextureWhenNeededCallBack()
{
	return LoadTextureWhenNeeded(*(hge->Texture_GetTextureToLoad()));
}

void SpriteItemManager::Init()
{
	hge->System_SetState(HGE_LOADTEXTUREFUNC, SpriteItemManager::LoadTextureWhenNeededCallBack);
	FreeFrontSprite();
#if defined __IPHONE
	InitFrontTouchButton();
#endif
}

void SpriteItemManager::Release()
{
	FreeFrontSprite();
#if defined __IPHONE
	ReleaseFrontTouchButton();
#endif
}

#if defined __IPHONE
void SpriteItemManager::InitFrontTouchButton()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++) {
		ftbutton[i][FTBUTTON_LEFT].sprite = CreateSpriteByName(SI_IPHONE_LEFT);
		ftbutton[i][FTBUTTON_RIGHT].sprite = CreateSpriteByName(SI_IPHONE_RIGHT);
		ftbutton[i][FTBUTTON_UP].sprite = CreateSpriteByName(SI_IPHONE_UP);
		ftbutton[i][FTBUTTON_DOWN].sprite = CreateSpriteByName(SI_IPHONE_DOWN);
		ftbutton[i][FTBUTTON_OK].sprite = CreateSpriteByName(SI_IPHONE_OK);
		ftbutton[i][FTBUTTON_CANCEL].sprite = CreateSpriteByName(SI_IPHONE_CANCEL);
		ftbutton[i][FTBUTTON_PAUSE].sprite = CreateSpriteByName(SI_IPHONE_PAUSE);
		ftbutton[i][FTBUTTON_SHOOT].sprite = CreateSpriteByName(SI_IPHONE_SHOOT);
		ftbutton[i][FTBUTTON_CHARGE].sprite = CreateSpriteByName(SI_IPHONE_CHARGE);
		ftbutton[i][FTBUTTON_DRAIN].sprite = CreateSpriteByName(SI_IPHONE_DRAIN);
		ftbutton[i][FTBUTTON_QUICK].sprite = CreateSpriteByName(SI_IPHONE_QUICK);
	}
}

void SpriteItemManager::ReleaseFrontTouchButton()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++) {
		for (int j=0; j<FTBUTTON_MAX; j++) {
			FreeSprite(&(ftbutton[i][j].sprite));
		}
	}
}

FrontTouchButton * SpriteItemManager::GetFrontTouchButton(BYTE playerindex, BYTE buttontype)
{
	if (playerindex < M_PL_MATCHMAXPLAYER && buttontype < FTBUTTON_MAX) {
		return &(ftbutton[playerindex][buttontype]);
	}
	return NULL;
}

void SpriteItemManager::FrontTouchButtonHide()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++) {
		for (int j=0; j<FTBUTTON_MAX; j++) {
			ftbutton[i][j].flag = FRONTTOUCH_HIDDEN;
		}
	}
}

void SpriteItemManager::RenderFrontTouchButton()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++) {
		for (int j=0; j<FTBUTTON_MAX; j++) {
			if (ftbutton[i][j].flag) {
				switch (ftbutton[i][j].flag) {
					case FRONTTOUCH_TOUCHED:
						ftbutton[i][j].sprite->SetColor(0xffff0000);
						break;
					default:
						ftbutton[i][j].sprite->SetColor(0xffffffff);
						break;
				}
				RenderSprite(ftbutton[i][j].sprite, ftbutton[i][j].x, ftbutton[i][j].y);
			}
		}
	}
}

#endif

HTEXTURE SpriteItemManager::GetTexture(int index)
{
	if (index < 0 || index >= BResource::bres.spritenumber)
	{
		return NULL;
	}
	return BResource::bres.tex[BResource::bres.spritedata[index].tex];
}

float SpriteItemManager::GetTexX(int index)
{
	if (index < 0 || index >= BResource::bres.spritenumber)
	{
		return 0;
	}
	return BResource::bres.spritedata[index].tex_x;
}

float SpriteItemManager::GetTexY(int index)
{
	if (index < 0 || index >= BResource::bres.spritenumber)
	{
		return 0;
	}
	return BResource::bres.spritedata[index].tex_y;
}

float SpriteItemManager::GetTexW(int index)
{
	if (index < 0 || index >= BResource::bres.spritenumber)
	{
		return 0;
	}
	return BResource::bres.spritedata[index].tex_w;
}

float SpriteItemManager::GetTexH(int index)
{
	if (index < 0 || index >= BResource::bres.spritenumber)
	{
		return 0;
	}
	return BResource::bres.spritedata[index].tex_h;
}

void SpriteItemManager::FrontSpriteAction()
{
	for (int i=0; i<FRONTSPRITEMAX; i++)
	{
		if (frontsprite[i].sprite)
		{
			if (frontsprite[i].fadeoutmaxtime)
			{
				frontsprite[i].fadeouttimer++;
				if (frontsprite[i].fadeouttimer == frontsprite[i].fadeoutmaxtime)
				{
					FreeFrontSprite(i);
				}
			}
		}
	}
}

void SpriteItemManager::RenderFrontSprite()
{
	for (int i=0; i<FRONTSPRITEMAX; i++)
	{
		if (frontsprite[i].sprite)
		{
			if (frontsprite[i].fadeoutmaxtime)
			{
				BYTE _alpha = INTER(0xff, 0, ((float)frontsprite[i].fadeouttimer)/frontsprite[i].fadeoutmaxtime);
				frontsprite[i].col = (_alpha<<24)|0xffffff;
			}
			frontsprite[i].sprite->SetColor(frontsprite[i].col);
			frontsprite[i].sprite->SetBlendMode(frontsprite[i].blend);
			RenderSpriteEx(frontsprite[i].sprite, frontsprite[i].x, frontsprite[i].y, frontsprite[i].rot, frontsprite[i].hscale, frontsprite[i].vscale);
		}
	}
}

int SpriteItemManager::GetIndexByName(const char * spritename)
{
	if (!spritename)
	{
		return -1;
	}
	if (!strlen(spritename))
	{
		return -1;
	}
	for (int i=0; i<BResource::bres.spritenumber; i++)
	{
		if (!strcmp(spritename, BResource::bres.spritedata[i].spritename))
		{
			return i;
			break;
		}
	}
	return -1;
}

spriteData * SpriteItemManager::CastSprite(int index)
{
	if (index >= 0 && index < BResource::bres.spritenumber)
	{
		return &(BResource::bres.spritedata[index]);
	}
	return NULL;
}

bool SpriteItemManager::SetSprite(int index, hgeSprite * sprite)
{
	if (!sprite)
	{
		return false;
	}
	if (index < 0)
	{
		SetSpriteTextureRect(sprite, 0, 0, 0, 0);
		return true;
	}
	spriteData * _sd = CastSprite(index);
	if (!_sd)
	{
		return false;
	}
	HTEXTURE tex(_sd->tex, NULL);
	SetSpriteData(sprite, tex, _sd->tex_x, _sd->tex_y, 
		_sd->tex_w < 0 ? hge->Texture_GetWidth(tex)-_sd->tex_x : _sd->tex_w, 
		_sd->tex_h < 0 ? hge->Texture_GetHeight(tex)-_sd->tex_y : _sd->tex_h);
	return true;
}

bool SpriteItemManager::HaveFrontSprite(int ID)
{
	if (ID < 0 || ID >= FRONTSPRITEMAX)
	{
		return false;
	}
	if (frontsprite[ID].sprite)
	{
		return true;
	}
	return false;
}

void SpriteItemManager::ClearFrontSpriteVale(int ID)
{
	if (ID < 0 || ID >= FRONTSPRITEMAX)
	{
		return;
	}
	hgeSprite * _sprite = frontsprite[ID].sprite;
	ZeroMemory(&frontsprite[ID], sizeof(FrontSprite));
	frontsprite[ID].blend = BLEND_DEFAULT;
	frontsprite[ID].sprite = _sprite;
}

hgeSprite * SpriteItemManager::ChangeFrontSprite(int ID, int index)
{
	if (ID < 0 || ID >= FRONTSPRITEMAX)
	{
		return NULL;
	}
	if (HaveFrontSprite(ID))
	{
		if (ChangeSprite(index, frontsprite[ID].sprite))
		{
			return frontsprite[ID].sprite;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		frontsprite[ID].sprite = CreateSprite(index);
		return frontsprite[ID].sprite;
	}
	return NULL;

}

void SpriteItemManager::FreeFrontSprite(int ID/* =-1 */)
{
	if (ID >= FRONTSPRITEMAX)
	{
		return;
	}
	if (ID < 0)
	{
		for (int i=0; i<FRONTSPRITEMAX; i++)
		{
			FreeFrontSprite(i);
		}
		return;
	}
	FreeSprite(&frontsprite[ID].sprite);
	ClearFrontSpriteVale(ID);
}

hgeSprite * SpriteItemManager::BuildFrontSprite(int ID, int index)
{
	if (index >= 0)
	{
		if (HaveFrontSprite(ID))
		{
			FreeFrontSprite(ID);
		}
		return ChangeFrontSprite(ID, index);
	}
	return NULL;
}

hgeSprite * SpriteItemManager::BuildFrontSpriteByName(int ID, const char * spritename)
{
	return BuildFrontSprite(ID, GetIndexByName(spritename));
}

void SpriteItemManager::SetFrontSpriteValue(int ID, float x, float y, int angle/* =0 */, float hscale/* =1.0f */, float vscale/* =0.0f */, DWORD col/* =0xffffffff */, int blend/* =BLEND_DEFAULT */)
{
	if (ID < 0 || ID >= FRONTSPRITEMAX)
	{
		return;
	}
	frontsprite[ID].x = x;
	frontsprite[ID].y = y;
	frontsprite[ID].rot = ARC(angle);
	frontsprite[ID].hscale = hscale;
	frontsprite[ID].vscale = vscale;
	frontsprite[ID].col = col;
	frontsprite[ID].blend = blend;
}

void SpriteItemManager::SetFrontSpriteFadeoutTime(int ID, int fadeouttime)
{
	if (ID < 0 || ID >= FRONTSPRITEMAX)
	{
		return;
	}
	frontsprite[ID].fadeoutmaxtime = fadeouttime;
}

hgeSprite * SpriteItemManager::CreateNullSprite()
{
	hgeSprite * sprite;
	sprite = CreateSprite(nullIndex);
	return sprite;
}

hgeSprite * SpriteItemManager::CreateSprite(int index)
{
	hgeSprite * sprite;
//	sprite = CreateNullSprite();
	sprite = new hgeSprite();
	if (index < 0)
	{
		return sprite;
	}
	HTEXTURE tex(BResource::bres.spritedata[index].tex, NULL);
	SetSpriteData(sprite, tex, BResource::bres.spritedata[index].tex_x, BResource::bres.spritedata[index].tex_y, BResource::bres.spritedata[index].tex_w, BResource::bres.spritedata[index].tex_h);
	return sprite;
}

bool SpriteItemManager::SetSpriteData(hgeSprite * sprite, HTEXTURE _tex, float texx, float texy, float texw, float texh, bool flipx/* =false */, bool flipy/* =false */)
{
	if (!sprite)
	{
		return false;
	}
	sprite->SetTexture(_tex);
	if (!SetSpriteTextureRect(sprite, texx, texy, texw, texh))
	{
		return false;
	}
	if (!SetSpriteFlip(sprite, flipx, flipy))
	{
		return false;
	}
	return true;
}

bool SpriteItemManager::SetSpriteTextureRect(hgeSprite * sprite, float texx, float texy, float texw, float texh)
{
	if (!sprite)
	{
		return false;
	}
	sprite->SetTextureRect(texx, texy, texw, texh);
	return true;
}

bool SpriteItemManager::SetSpriteHotSpot(hgeSprite * sprite, float hotx, float hoty)
{
	if (!sprite)
	{
		return false;
	}
	sprite->SetHotSpot(hotx, hoty);
	return true;
}

bool SpriteItemManager::SetSpriteFlip(hgeSprite * sprite, bool flipx/* =false */, bool flipy/* =false */)
{
	if (!sprite)
	{
		return false;
	}
	sprite->SetFlip(flipx, flipy);
	return true;
}

bool SpriteItemManager::CreateSprite(int index, hgeSprite ** sprite)
{
	if (!sprite)
	{
		return false;
	}
	*sprite = CreateSprite(index);
	if (*sprite)
	{
		return true;
	}
	return false;
}

bool SpriteItemManager::ChangeSprite(int index, hgeSprite * sprite)
{
	if (!sprite || index < 0)
	{
		return false;
	}
	HTEXTURE tex(BResource::bres.spritedata[index].tex, NULL);
	SetSpriteData(sprite, tex, BResource::bres.spritedata[index].tex_x, BResource::bres.spritedata[index].tex_y, BResource::bres.spritedata[index].tex_w, BResource::bres.spritedata[index].tex_h);
	return true;
}

hgeSprite * SpriteItemManager::CreateSpriteByName(const char * spritename)
{
	int index = GetIndexByName(spritename);
	if (index >= 0)
	{
		return CreateSprite(index);
	}
	return NULL;
}

bool SpriteItemManager::CreateSpriteByName(const char * spritename, hgeSprite ** sprite)
{
	if (!sprite)
	{
		return false;
	}
	*sprite = CreateSpriteByName(spritename);
	if (*sprite)
	{
		return true;
	}
	return false;
}

void SpriteItemManager::FreeSprite(hgeSprite ** sprite)
{
	if (sprite && *sprite)
	{
		free(*sprite);
		*sprite = NULL;
	}
}

bool SpriteItemManager::ptFace(int index, hgeSprite * sprite)
{
	if (!sprite)
	{
		return false;
	}
	if (index < 0)
	{
		SpriteItemManager::SetSpriteTextureRect(sprite, 0, 0, 0, 0);
		return true;
	}
	ChangeSprite(BResource::bres.playerdata[index].faceSIID, sprite);
	return true;
}

bool SpriteItemManager::LoadTextureWhenNeeded(HTEXTURE tex)
{
	if (hge->Texture_GetTexture(tex) == NULL)
	{
		BResource::bres.LoadTexture(tex.texindex);
		return true;
	}
	return false;
}

void SpriteItemManager::RenderSprite( hgeSprite * sprite, float x, float y )
{
	if (!sprite)
	{
		return;
	}
//	LoadTextureWhenNeeded(sprite->quad.tex);
	sprite->Render(x, y);
}

void SpriteItemManager::RenderSpriteEx( hgeSprite * sprite, float x, float y, float rot, float hscale/*=1.0f*/, float vscale/*=0.0f*/ )
{
	if (!sprite)
	{
		return;
	}
//	LoadTextureWhenNeeded(sprite->quad.tex);
	sprite->RenderEx(x, y, rot, hscale, vscale);
}

void SpriteItemManager::FontPrintf( hgeFont * font, float x, float y, int align, const char * str)
{
	if (!font)
	{
		return;
	}
	font->printf(x, y, align, str);
}

void SpriteItemManager::FontPrintfb( hgeFont * font, float x, float y, float w, float h, int align, const char * str)
{
	if (!font)
	{
		return;
	}
	font->printfb(x, y, w, h, align, str);
}

void SpriteItemManager::EffectSystemRender( hgeEffectSystem * eff, hge3DPoint *ptfar, DWORD colormask )
{
	if (!eff)
	{
		return;
	}
//	LoadTextureWhenNeeded(eff->ebi.tex);
	eff->Render(ptfar, colormask);
}

void SpriteItemManager::RenderQuad( hgeQuad * quad )
{
	if (!quad)
	{
		return;
	}
//	LoadTextureWhenNeeded(quad->tex);
	hge->Gfx_RenderQuad(quad);
}