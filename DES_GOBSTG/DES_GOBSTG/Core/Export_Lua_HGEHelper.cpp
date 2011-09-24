#ifndef __NOTUSELUA

#include "../Header/Export_Lua_HGEHelp.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/Export.h"
#include "../Header/BResource.h"
#include "../Header/SpriteItemManager.h"

list<hgeFont *> Export_Lua_HGEHelp::fontList;
list<hgeSprite *> Export_Lua_HGEHelp::spriteList;
list<hgeEffectSystem *> Export_Lua_HGEHelp::esList;

bool Export_Lua_HGEHelp::_LuaRegistFunction(LuaObject * obj)
{
	// hgeFont
	LuaObject _fontobj = obj->CreateTable("hgeFont");

	_fontobj.Register("NewFont", LuaFn_hgeFont_NewFont);
	_fontobj.Register("DeleteFont", LuaFn_hgeFont_DeleteFont);

	_fontobj.Register("Render", LuaFn_hgeFont_Render);
	_fontobj.Register("RenderEx", LuaFn_hgeFont_Render);
	_fontobj.Register("printf", LuaFn_hgeFont_Render);
	_fontobj.Register("printfb", LuaFn_hgeFont_printfb);

	_fontobj.Register("SetColor", LuaFn_hgeFont_SetColor);
	_fontobj.Register("SetZ", LuaFn_hgeFont_SetZ);
	_fontobj.Register("SetBlendMode", LuaFn_hgeFont_SetBlendMode);
	_fontobj.Register("SetScale", LuaFn_hgeFont_SetScale);
	_fontobj.Register("SetProportion", LuaFn_hgeFont_SetProportion);
	_fontobj.Register("SetRotation", LuaFn_hgeFont_SetRotation);
	_fontobj.Register("SetTracking", LuaFn_hgeFont_SetTracking);
	_fontobj.Register("SetSpacing", LuaFn_hgeFont_SetSpacing);

	_fontobj.Register("GetColor", LuaFn_hgeFont_GetColor);
	_fontobj.Register("GetZ", LuaFn_hgeFont_GetZ);
	_fontobj.Register("GetBlendMode", LuaFn_hgeFont_GetBlendMode);
	_fontobj.Register("GetScale", LuaFn_hgeFont_GetScale);
	_fontobj.Register("GetProportion", LuaFn_hgeFont_GetProportion);
	_fontobj.Register("GetRotation", LuaFn_hgeFont_GetRotation);
	_fontobj.Register("GetTracking", LuaFn_hgeFont_GetTracking);
	_fontobj.Register("GetSpacing", LuaFn_hgeFont_GetSpacing);

	_fontobj.Register("ChangeSprite", LuaFn_hgeFont_ChangeSprite);
	_fontobj.Register("GetSprite", LuaFn_hgeFont_GetSprite);
	_fontobj.Register("GetPreWidth", LuaFn_hgeFont_GetPreWidth);
	_fontobj.Register("GetPostWidth", LuaFn_hgeFont_GetPostWidth);
	_fontobj.Register("GetHeight", LuaFn_hgeFont_GetHeight);
	_fontobj.Register("GetStringWidth", LuaFn_hgeFont_GetStringWidth);

	// hgeSprite
	LuaObject _spriteobj = obj->CreateTable("hgeSprite");

	_spriteobj.Register("NewSprite", LuaFn_hgeSprite_NewSprite);
	_spriteobj.Register("DeleteSprite", LuaFn_hgeSprite_DeleteSprite);

	_spriteobj.Register("Render", LuaFn_hgeSprite_Render);
	_spriteobj.Register("RenderEx", LuaFn_hgeSprite_Render);
	_spriteobj.Register("RenderStretch", LuaFn_hgeSprite_RenderStretch);
	_spriteobj.Register("Render4V", LuaFn_hgeSprite_Render4V);

	_spriteobj.Register("SetTexture", LuaFn_hgeSprite_SetTexture);
	_spriteobj.Register("SetTextureRect", LuaFn_hgeSprite_SetTextureRect);
	_spriteobj.Register("SetColor", LuaFn_hgeSprite_SetColor);
	_spriteobj.Register("SetZ", LuaFn_hgeSprite_SetZ);
	_spriteobj.Register("SetBlendMode", LuaFn_hgeSprite_SetBlendMode);
	_spriteobj.Register("SetHotSpot", LuaFn_hgeSprite_SetHotSpot);
	_spriteobj.Register("SetFlip", LuaFn_hgeSprite_SetFlip);

	_spriteobj.Register("GetTexture", LuaFn_hgeSprite_GetTexture);
	_spriteobj.Register("GetTextureRect", LuaFn_hgeSprite_GetTextureRect);
	_spriteobj.Register("GetColor", LuaFn_hgeSprite_GetColor);
	_spriteobj.Register("GetZ", LuaFn_hgeSprite_GetZ);
	_spriteobj.Register("GetBlendMode", LuaFn_hgeSprite_GetBlendMode);
	_spriteobj.Register("GetHotSpot", LuaFn_hgeSprite_GetHotSpot);
	_spriteobj.Register("GetFlip", LuaFn_hgeSprite_GetFlip);

	_spriteobj.Register("GetWidth", LuaFn_hgeSprite_GetWidth);
	_spriteobj.Register("GetHeight", LuaFn_hgeSprite_GetHeight);
	_spriteobj.Register("GetBoundingBox", LuaFn_hgeSprite_GetBoundingBox);

	// hgeEffectSystem
	LuaObject _esobj = obj->CreateTable("hgeES");

	_esobj.Register("NewES", LuaFn_hgeES_NewES);
	_esobj.Register("DeleteES", LuaFn_hgeES_DeleteES);

	_esobj.Register("Load", LuaFn_hgeES_Load);
	_esobj.Register("Save", LuaFn_hgeES_Save);

	_esobj.Register("Render", LuaFn_hgeES_Render);
	_esobj.Register("MoveTo", LuaFn_hgeES_MoveTo);
	_esobj.Register("Fire", LuaFn_hgeES_Fire);
	_esobj.Register("Stop", LuaFn_hgeES_Stop);

	_esobj.Register("Update", LuaFn_hgeES_Update);

	return true;
}

bool Export_Lua_HGEHelp::_LuaRegistConst(LuaObject * obj)
{
	// hgeFont
	obj->SetInteger("HGETEXT_LEFT", HGETEXT_LEFT);
	obj->SetInteger("HGETEXT_RIGHT", HGETEXT_RIGHT);
	obj->SetInteger("HGETEXT_CENTER", HGETEXT_CENTER);
	obj->SetInteger("HGETEXT_HORZMASK", HGETEXT_HORZMASK);

	obj->SetInteger("HGETEXT_TOP", HGETEXT_TOP);
	obj->SetInteger("HGETEXT_BOTTOM", HGETEXT_BOTTOM);
	obj->SetInteger("HGETEXT_MIDDLE", HGETEXT_MIDDLE);
	obj->SetInteger("HGETEXT_VERTMASK", HGETEXT_VERTMASK);

	return true;
}

hgeFont * Export_Lua_HGEHelp::_Helper_New_hgeFont()
{
	hgeFont * _font = NULL;
	_font = new hgeFont();
	if (_font)
	{
		fontList.push_back(_font);
	}
	return _font;
}

hgeFont * Export_Lua_HGEHelp::_Helper_New_hgeFont(const char * filename, bool bMipmap/* =false */)
{
	hgeFont * _font = NULL;
	_font = new hgeFont(filename, bMipmap);
	if (_font)
	{
		fontList.push_back(_font);
	}
	return _font;
}

hgeFont * Export_Lua_HGEHelp::_LuaHelper_hgeFont_Get(LuaStack * args)
{
	LuaObject _obj = (*args)[1];
	return (hgeFont *)_LuaHelper_GetDWORD(&_obj);
}

void Export_Lua_HGEHelp::_LuaHelper_hgeFont_DeleteFont(hgeFont * _font)
{
	if (_font)
	{
		delete _font;
		for (list<hgeFont *>::iterator it=fontList.begin(); it!=fontList.end();)
		{
			if ((*it) == _font)
			{
				it = fontList.erase(it);
			}
			else
			{
				++it;
			}
		}
		_font = NULL;
	}
}

void Export_Lua_HGEHelp::_LuaHelper_hgeFont_DeleteAllFont()
{
	hgeFont * _font;
	for (list<hgeFont *>::iterator it=fontList.begin(); it!=fontList.end(); it++)
	{
		_font = *it;
		if (_font)
		{
			delete _font;
			_font = NULL;
		}
	}
	fontList.clear();
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_NewFont(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret = 0;
	char * filename = 0;
	bool bMipmap = false;

	hgeFont * _font = NULL;
	int argscount = args.Count();
	if (argscount > 0)
	{
		filename = (char *)(args[1].GetString());
		if (argscount > 1)
		{
			bMipmap = args[2].GetBoolean();
		}
		_font = _Helper_New_hgeFont(filename, bMipmap);
	}
	else
	{
		_font = _Helper_New_hgeFont();
	}
	dret = (DWORD)_font;

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_DeleteFont(LuaState * ls)
{
	LuaStack args(ls);

	if (args.Count() > 0)
	{
		hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
		_LuaHelper_hgeFont_DeleteFont(_font);
	}
	else
	{
		_LuaHelper_hgeFont_DeleteAllFont();
	}

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_Render(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	int argscount = args.Count();

	float scale = 1.0f;
	float properation = 1.0f;
	float rotation = 0;
	float tracking = 0;
	float spacing = 1.0f;
	if (argscount > 5)
	{
		LuaObject _obj = args[6];
		scale = _obj.GetByIndex(1).GetFloat();
		properation = _obj.GetByIndex(2).GetFloat();
		rotation = _obj.GetByIndex(3).GetFloat();
		tracking = _obj.GetByIndex(4).GetFloat();
		spacing = _obj.GetByIndex(5).GetFloat();
	}

	_font->RenderEx(args[2].GetFloat(), args[3].GetFloat(), args[4].GetInteger(), args[5].GetString(), scale, properation, rotation, tracking, spacing);

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_printfb(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);

	SpriteItemManager::FontPrintfb(_font, args[2].GetFloat(), args[3].GetFloat(), args[4].GetFloat(), args[5].GetFloat(), args[6].GetInteger(), args[7].GetString());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_SetColor(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	LuaObject _obj;
	int argscount = args.Count();

	if (argscount > 3)
	{
		DWORD col[4];
		for (int i=0; i<4; i++)
		{
			_obj = args[i+2];
			col[i] = _LuaHelper_GetColor(&_obj);
		}
		_font->SetColor(col[0], col[1], col[2], col[3]);
	}
	else
	{
		DWORD col;
		int i = -1;
		_obj = args[2];
		col = _LuaHelper_GetColor(&_obj);
		if (argscount > 2)
		{
			i = args[3];
		}
		_font->SetColor(col, i);
	}

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_SetZ(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);

	hge3DPoint * ptfar = NULL;
	if (args.Count() > 2)
	{
		ptfar = Export::GetFarPoint(args[3].GetInteger());
	}

	_font->SetZ(args[2].GetFloat(), ptfar);

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_SetBlendMode(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);

	_font->SetBlendMode(args[2].GetInteger());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_SetScale(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);

	_font->SetScale(args[2].GetFloat());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_SetProportion(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);

	_font->SetProportion(args[2].GetFloat());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_SetRotation(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);

	_font->SetRotation(args[2].GetFloat());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_SetTracking(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);

	_font->SetTracking(args[2].GetFloat());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_SetSpacing(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);

	_font->SetSpacing(args[2].GetFloat());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetColor(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	DWORD dret;
	int i=0;

	if (args.Count() > 0)
	{
		i = args[i].GetInteger();
	}
	dret = _font->GetColor(i);

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetZ(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	float fret;

	fret = _font->GetZ();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetBlendMode(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	int iret;

	iret = _font->GetBlendMode();

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetScale(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	float fret;

	fret = _font->GetScale();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetProportion(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	float fret;

	fret = _font->GetProportion();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetRotation(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	float fret;

	fret = _font->GetRotation();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetTracking(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	float fret;

	fret = _font->GetTracking();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetSpacing(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	float fret;

	fret = _font->GetSpacing();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_ChangeSprite(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	LuaObject _obj;
	float pre_a=-1;
	float pre_c=-1;

	int argscount = args.Count();
	if (argscount > 5)
	{
		_obj = args[3];
		HTEXTURE _htexture = (HTEXTURE)(_LuaHelper_GetDWORD(&_obj));
		if (argscount > 7)
		{
			pre_a = args[8].GetFloat();
			if (argscount > 8)
			{
				pre_c = args[9].GetFloat();
			}
		}
		_font->ChangeSprite(args[2].GetInteger(), _htexture, args[4].GetFloat(), args[5].GetFloat(), args[6].GetFloat(), args[7].GetFloat(), pre_a, pre_c);
	}
	else
	{
		_obj = args[3];
		hgeSprite * _hgesprite = (hgeSprite *)(_LuaHelper_GetDWORD(&_obj));
		if (argscount > 3)
		{
			pre_a = args[4].GetFloat();
			if (argscount > 4)
			{
				pre_c = args[5].GetFloat();
			}
		}
		_font->ChangeSprite(args[2].GetInteger(), _hgesprite, pre_a, pre_c);
	}

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetSprite(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	DWORD dret;

	dret = (DWORD)(_font->GetSprite(args[2].GetInteger()));

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetPreWidth(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	float fret;

	fret = _font->GetPreWidth(args[2].GetInteger());

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetPostWidth(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	float fret;

	fret = _font->GetPostWidth(args[2].GetInteger());

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetHeight(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	float fret;

	fret = _font->GetHeight();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeFont_GetStringWidth(LuaState * ls)
{
	LuaStack args(ls);
	hgeFont * _font = _LuaHelper_hgeFont_Get(&args);
	float fret;
	bool bMultiline=true;

	if (args.Count() > 2)
	{
		bMultiline = args[3].GetBoolean();
	}
	fret = _font->GetStringWidth(args[2].GetString(), bMultiline);

	ls->PushNumber(fret);
	return 1;
}

hgeEffectSystem * Export_Lua_HGEHelp::_Helper_New_hgeES()
{
	hgeEffectSystem * _es = NULL;
	_es = new hgeEffectSystem();
	if (_es)
	{
		esList.push_back(_es);
	}
	return _es;
}

hgeEffectSystem * Export_Lua_HGEHelp::_Helper_New_hgeES(const char * filename, HTEXTURE tex /* = 0 */)
{
	hgeEffectSystem * _es = NULL;
	_es = new hgeEffectSystem(filename, tex, BResource::bres.tex);
	if (_es)
	{
		esList.push_back(_es);
	}
	return _es;
}

hgeEffectSystem * Export_Lua_HGEHelp::_Helper_New_hgeES(const hgeEffectSystem & eff)
{
	hgeEffectSystem * _es = NULL;
	_es = new hgeEffectSystem(eff);
	if (_es)
	{
		esList.push_back(_es);
	}
	return _es;
}

hgeEffectSystem * Export_Lua_HGEHelp::_LuaHelper_hgeES_Get(LuaStack * args)
{
	LuaObject _obj = (*args)[1];
	return (hgeEffectSystem *)_LuaHelper_GetDWORD(&_obj);
}

void Export_Lua_HGEHelp::_LuaHelper_hgeES_DeleteES(hgeEffectSystem * _es)
{
	if (_es)
	{
		delete _es;
		for (list<hgeEffectSystem *>::iterator it=esList.begin(); it!=esList.end();)
		{
			if ((*it) == _es)
			{
				it = esList.erase(it);
			}
			else
			{
				++it;
			}
		}
		_es = NULL;
	}
}

void Export_Lua_HGEHelp::_LuaHelper_hgeES_DeleteAllES()
{
	hgeEffectSystem * _es;
	for (list<hgeEffectSystem *>::iterator it=esList.begin(); it!=esList.end(); it++)
	{
		_es = *it;
		if (_es)
		{
			delete _es;
			_es = NULL;
		}
	}
	esList.clear();
}

int Export_Lua_HGEHelp::LuaFn_hgeES_NewES(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret = 0;
	hgeEffectSystem * _es = NULL;

	int argscount = args.Count();
	if (argscount > 0)
	{
		LuaObject _obj;
		if (!args[1].IsNumber())
		{
			HTEXTURE _htexture = 0;
			if (argscount > 1)
			{
				_obj = args[2];
				_htexture = (HTEXTURE)(_LuaHelper_GetDWORD(&_obj));
			}
			const char * filename = args[1].GetString();
			_es = _Helper_New_hgeES(filename, _htexture);
		}
		else
		{
			_obj = args[1];
			hgeEffectSystem * __es = (hgeEffectSystem *)(_LuaHelper_GetDWORD(&_obj));
			_es = _Helper_New_hgeES(*__es);
		}
	}
	else
	{
		_es = _Helper_New_hgeES();
	}
	dret = (DWORD)_es;

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeES_DeleteES(LuaState * ls)
{
	LuaStack args(ls);

	if (args.Count() > 0)
	{
		hgeEffectSystem * _es = _LuaHelper_hgeES_Get(&args);
		_LuaHelper_hgeES_DeleteES(_es);
	}
	else
	{
		_LuaHelper_hgeES_DeleteAllES();
	}

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeES_Load(LuaState * ls)
{
	LuaStack args(ls);
	hgeEffectSystem * _es = _LuaHelper_hgeES_Get(&args);
	int iret;
	HTEXTURE tex=0;
	HTEXTURE * texset=0;

	int argscount = args.Count();
	if (argscount > 2)
	{
		LuaObject _obj;
		_obj = args[3];
		tex = (HTEXTURE)(_LuaHelper_GetDWORD(&_obj));
		if (argscount > 3)
		{
			_obj = args[4];
			texset = (HTEXTURE *)(_LuaHelper_GetDWORD(&_obj));
		}
	}
	iret = _es->Load(args[2].GetString(), tex, texset);

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeES_Save(LuaState * ls)
{
	LuaStack args(ls);
	hgeEffectSystem * _es = _LuaHelper_hgeES_Get(&args);
	bool bret;
	int _texnum=-1;

	if (args.Count() > 2)
	{
		_texnum = args[3].GetInteger();
	}
	bret = _es->Save(args[2].GetString(), _texnum);

	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeES_Render(LuaState * ls)
{
	LuaStack args(ls);
	hgeEffectSystem * _es = _LuaHelper_hgeES_Get(&args);

	hge3DPoint * ptfar = NULL;
	DWORD colormask = 0xffffffff;
	int argscount = args.Count();
	if (argscount > 1)
	{
		ptfar = Export::GetFarPoint(args[2].GetInteger());
		if (argscount > 2)
		{
			LuaObject _obj = args[3];
			colormask = _LuaHelper_GetDWORD(&_obj);
		}
	}

	SpriteItemManager::EffectSystemRender(_es, ptfar, colormask);

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeES_MoveTo(LuaState * ls)
{
	LuaStack args(ls);
	hgeEffectSystem * _es = _LuaHelper_hgeES_Get(&args);
	float z = 0;
	bool bForce = false;

	int argscount = args.Count();
	if (argscount > 3)
	{
		z = args[4].GetFloat();
		if (argscount > 4)
		{
			bForce = args[5].GetBoolean();
		}
	}
	_es->MoveTo(args[2].GetFloat(), args[3].GetFloat(), z, bForce);

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeES_Fire(LuaState * ls)
{
	LuaStack args(ls);
	hgeEffectSystem * _es = _LuaHelper_hgeES_Get(&args);

	_es->Fire();

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeES_Stop(LuaState * ls)
{
	LuaStack args(ls);
	hgeEffectSystem * _es = _LuaHelper_hgeES_Get(&args);
	bool bKill = false;

	if (args.Count() > 1)
	{
		bKill = args[2].GetBoolean();
	}
	_es->Stop(bKill);

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeES_Update(LuaState * ls)
{
	LuaStack args(ls);
	hgeEffectSystem * _es = _LuaHelper_hgeES_Get(&args);

	_es->Update();

	return 0;
}

hgeSprite * Export_Lua_HGEHelp::_Helper_New_hgeSprite()
{
	hgeSprite * _sprite = NULL;
	_sprite = new hgeSprite();
	if (_sprite)
	{
		spriteList.push_back(_sprite);
	}
	return _sprite;
}

hgeSprite * Export_Lua_HGEHelp::_Helper_New_hgeSprite(HTEXTURE tex, float x, float y, float w, float h)
{
	hgeSprite * _sprite = NULL;
	_sprite = new hgeSprite(tex, x, y ,w, h);
	if (_sprite)
	{
		spriteList.push_back(_sprite);
	}
	return _sprite;
}

hgeSprite * Export_Lua_HGEHelp::_Helper_New_hgeSprite(const hgeSprite & spr)
{
	hgeSprite * _sprite = NULL;
	_sprite = new hgeSprite(spr);
	if (_sprite)
	{
		spriteList.push_back(_sprite);
	}
	return _sprite;
}


hgeSprite * Export_Lua_HGEHelp::_LuaHelper_hgeSprite_Get(LuaStack * args)
{
	LuaObject _obj = (*args)[1];
	return (hgeSprite *)_LuaHelper_GetDWORD(&_obj);
}

void Export_Lua_HGEHelp::_LuaHelper_hgeSprite_DeleteSprite(hgeSprite * _sprite)
{
	if (_sprite)
	{
		delete _sprite;
		for (list<hgeSprite *>::iterator it=spriteList.begin(); it!=spriteList.end();)
		{
			if ((*it) == _sprite)
			{
				it = spriteList.erase(it);
			}
			else
			{
				++it;
			}
		}
		_sprite = NULL;
	}
}

void Export_Lua_HGEHelp::_LuaHelper_hgeSprite_DeleteAllSprite()
{
	hgeSprite * _sprite;
	for (list<hgeSprite *>::iterator it=spriteList.begin(); it!=spriteList.end(); it++)
	{
		_sprite = *it;
		if (_sprite)
		{
			delete _sprite;
			_sprite = NULL;
		}
	}
	spriteList.clear();
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_NewSprite(LuaState * ls)
{
	LuaStack args(ls);
	DWORD dret = 0;
	hgeSprite * _sprite = NULL;

	int argscount = args.Count();
	if (argscount > 0)
	{
		LuaObject _obj;
		if (argscount > 1)
		{
			_obj = args[1];
			HTEXTURE _htexture = (HTEXTURE)(_LuaHelper_GetDWORD(&_obj));
			float x = args[2].GetFloat();
			float y = args[3].GetFloat();
			float w = args[4].GetFloat();
			float h = args[5].GetFloat();
			_sprite = _Helper_New_hgeSprite(_htexture, x, y, w, h);
		}
		else
		{
			_obj = args[1];
			hgeSprite * __sprite = (hgeSprite *)(_LuaHelper_GetDWORD(&_obj));
			_sprite = _Helper_New_hgeSprite(*__sprite);
		}
	}
	else
	{
		_sprite = _Helper_New_hgeSprite();
	}
	dret = (DWORD)_sprite;

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_DeleteSprite(LuaState * ls)
{
	LuaStack args(ls);

	if (args.Count() > 0)
	{
		hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
		_LuaHelper_hgeSprite_DeleteSprite(_sprite);
	}
	else
	{
		_LuaHelper_hgeSprite_DeleteAllSprite();
	}

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_Render(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	if (!_sprite)
	{
		return 0;
	}

	int argscount = args.Count();

	if (argscount > 2)
	{
		float rot = 0.0f;
		float hscale=1.0f;
		float vscale=0.0f;
		if (argscount > 3)
		{
			if (!args[4].IsNil())
			{
				rot = args[4].GetFloat();
			}
			if (argscount > 4)
			{
				if (!args[5].IsNil())
				{
					hscale = args[5].GetFloat();
				}
				if (argscount > 5)
				{
					if (!args[6].IsNil())
					{
						vscale = args[6].GetFloat();
					}
				}
			}
		}
		SpriteItemManager::RenderSpriteEx(_sprite, args[2].GetFloat(), args[3].GetFloat(), rot, hscale, vscale);
	}
	else
	{
		SpriteItemManager::RenderSprite(_sprite, args[2].GetFloat(), args[3].GetFloat());
	}

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_RenderStretch(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);

	_sprite->RenderStretch(args[2].GetFloat(), args[3].GetFloat(), args[4].GetFloat(), args[5].GetFloat());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_Render4V(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);

	_sprite->Render4V(args[2].GetFloat(), args[3].GetFloat(), args[4].GetFloat(), args[5].GetFloat(), args[6].GetFloat(), args[7].GetFloat(), args[8].GetFloat(), args[9].GetFloat());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_SetTexture(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);

	LuaObject _obj = args[2];
	HTEXTURE _htexture = (HTEXTURE)(_LuaHelper_GetDWORD(&_obj));
	_sprite->SetTexture(_htexture);

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_SetTextureRect(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	bool adjSize = true;

	if (args.Count() > 5)
	{
		adjSize = args[6].GetBoolean();
	}
	_sprite->SetTextureRect(args[2].GetFloat(), args[3].GetFloat(), args[4].GetFloat(), args[5].GetFloat(), adjSize);

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_SetColor(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);

	int argscount = args.Count();
	LuaObject _obj;
	if (argscount > 3)
	{
		DWORD col[4];
		for (int i=0; i<4; i++)
		{
			_obj = args[i+2];
			col[i] = _LuaHelper_GetColor(&_obj);
		}
		_sprite->SetColor(col[0], col[1], col[2], col[3]);
	}
	else
	{
		int i=-1;
		if (argscount > 2)
		{
			i = args[3].GetInteger();
		}
		DWORD col;
		_obj = args[2];
		col = _LuaHelper_GetColor(&_obj);
		_sprite->SetColor(col, i);
	}

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_SetZ(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);

	int argscount = args.Count();
	if (argscount > 3)
	{
		hge3DPoint * ptfar = NULL;
		if (argscount > 5)
		{
			ptfar = Export::GetFarPoint(args[6].GetInteger());
		}
		_sprite->SetZ(args[2].GetFloat(), args[3].GetFloat(), args[4].GetFloat(), args[5].GetFloat(), ptfar);
	}
	else
	{
		int i=-1;
		hge3DPoint * _ptfar = NULL;
		if (argscount > 2)
		{
			i = args[3].GetInteger();
			if (argscount > 3)
			{
				_ptfar = Export::GetFarPoint(args[4].GetInteger());
			}
		}
		_sprite->SetZ(args[2].GetFloat(), i, _ptfar);
	}

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_SetBlendMode(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);

	_sprite->SetBlendMode(args[2].GetInteger());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_SetHotSpot(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);

	_sprite->SetHotSpot(args[2].GetFloat(), args[3].GetFloat());

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_SetFlip(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	bool bHotSpot = false;

	if (args.Count() > 3)
	{
		bHotSpot = args[4].GetBoolean();
	}
	_sprite->SetFlip(args[2].GetBoolean(), args[3].GetBoolean(), bHotSpot);

	return 0;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_GetTexture(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	int iret;
	DWORD dret;

	HTEXTURE _tex = _sprite->GetTexture();
	iret = _tex.texindex;
	dret = hge->Texture_GetTexture(_tex);

	ls->PushInteger(iret);
	_LuaHelper_PushDWORD(ls, dret);
	return 2;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_GetTextureRect(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	float x;
	float y;
	float w;
	float h;

	_sprite->GetTextureRect(&x, &y, &w, &h);

	ls->PushNumber(x);
	ls->PushNumber(y);
	ls->PushNumber(w);
	ls->PushNumber(h);
	return 4;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_GetColor(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	DWORD dret;
	int i=0;

	if (args.Count() > 1)
	{
		i = args[2].GetInteger();
	}
	dret = _sprite->GetColor(i);

	_LuaHelper_PushDWORD(ls, dret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_GetZ(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	float fret;
	int i=0;

	if (args.Count() > 1)
	{
		i = args[2].GetInteger();
	}
	fret = _sprite->GetZ(i);

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_GetBlendMode(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	int iret;

	iret = _sprite->GetBlendMode();

	ls->PushInteger(iret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_GetHotSpot(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	float x;
	float y;

	_sprite->GetHotSpot(&x, &y);

	ls->PushNumber(x);
	ls->PushNumber(y);
	return 2;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_GetFlip(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	bool bX;
	bool bY;

	_sprite->GetFlip(&bX, &bY);

	ls->PushBoolean(bX);
	ls->PushBoolean(bY);
	return 2;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_GetWidth(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	float fret;

	fret = _sprite->GetWidth();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_GetHeight(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	float fret;

	fret = _sprite->GetHeight();

	ls->PushNumber(fret);
	return 1;
}

int Export_Lua_HGEHelp::LuaFn_hgeSprite_GetBoundingBox(LuaState * ls)
{
	LuaStack args(ls);
	hgeSprite * _sprite = _LuaHelper_hgeSprite_Get(&args);
	hgeRect rect;

	if (args.Count() > 3)
	{
		_sprite->GetBoundingBoxEx(args[2].GetFloat(), args[3].GetFloat(), args[4].GetFloat(), args[5].GetFloat(), args[6].GetFloat(), &rect);
	}
	else
	{
		_sprite->GetBoundingBox(args[2].GetFloat(), args[3].GetFloat(), &rect);
	}

	ls->PushNumber(rect.x1);
	ls->PushNumber(rect.y1);
	ls->PushNumber(rect.x2-rect.x1);
	ls->PushNumber(rect.y2-rect.y1);
	return 4;
}

#endif