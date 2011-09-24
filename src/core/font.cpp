/************************************************************************/
/* This file is originally Yuki Izayoi's codes                          */
/* h5nc (h5nc@yahoo.com.cn) copied these codes under her permission     */
/* Some changes are made by h5nc                                        */
/************************************************************************/

/* 
Font implemention 
Yuki Izayoi 2007.2.16
*/

//edit by Thor/h5nc 2007.2.19

#include "hge_impl.h"

HD3DFONT CALL HGE_Impl::Font_Load(const char * fontStyle,int height)
{
#if defined __WIN32
	/*
	LOGFONT lf;
	memset(&lf,0,sizeof(lf));
	lf.lfHeight         = height;    // in logical units
	lf.lfWidth          = 0;	    // in logical units
	lf.lfWeight         = 1000;   // boldness, range 0(light) - 1000(bold)
	lf.lfItalic         = false;
	lf.lfUnderline      = false;
	lf.lfStrikeOut      = false;
	lf.lfCharSet        = DEFAULT_CHARSET;
	strcpy(lf.lfFaceName, fontStyle); // font style
	*/
	D3DXFONT_DESC dfdesc;
	memset(&dfdesc, 0, sizeof(D3DXFONT_DESC));
	dfdesc.Height		= height;
	dfdesc.Width		= 0;
	dfdesc.Weight		= 1000;
	dfdesc.CharSet		= DEFAULT_CHARSET;
	strcpy(dfdesc.FaceName, fontStyle);

	ID3DXFont * font;
	if (FAILED(D3DXCreateFontIndirect(pD3DDevice,&dfdesc,&font)))
	{
		_PostError("Font_Load: Font create failed ");
		return 0;
	}

	CFontList * newFont = new CFontList();
	newFont->font = (HD3DFONT)font;
	newFont->next = fontList;
	fontList = newFont;

	return (HD3DFONT)font;
#else
	return NULL;
#endif

}
void CALL HGE_Impl::Font_Free(HD3DFONT font)
{
#if defined __WIN32
	ID3DXFont * pFont = (ID3DXFont * )font;
	CFontList * listIterator = fontList;
	CFontList * listPrevIterator = NULL;

	while (listIterator != NULL)
	{
		if (listIterator->font == font)
		{
			CFontList * nextFont = listIterator->next;
			if (listPrevIterator != 0)
			{
				listPrevIterator ->next = nextFont;
			}
			else
			{
				fontList = nextFont;
			}
			delete listIterator;
			break;
		}
		listPrevIterator = listIterator;
		listIterator = listIterator->next;
	}
	if (pFont != NULL)
	{
		pFont->Release();
	}
#endif
}

int CALL HGE_Impl::Gfx_RenderTextToTarget(HTEXTURE * tex, HTARGET tar, HD3DFONT font, const char * text, float x, float y, float w, float h, DWORD color /* = 0xffffffff */)
{
#if defined __WIN32
	Gfx_BeginScene(tar);
	Gfx_Clear(0x00000000);
	int height = Gfx_RenderText(font, text, x, y, w, h, color);
	Gfx_EndScene();

	if (tex)
	{
		*tex = Target_GetTexture(tar);
	}
	return height;
#else
	return 0;
#endif
}

int CALL HGE_Impl::Gfx_RenderText(HD3DFONT font, const char * text, float x, float y, float w, float h, DWORD color)
{
#if defined __WIN32
	/*
	if(shadow)
		Gfx_RenderText(font, text, x+1, y+1, w, h, 0xff000000, false);
		*/
	if (font == NULL)
	{
		return 0;
	}
	RECT rect;
	rect.left = (LONG)x;
	rect.top = (LONG)y;
	rect.right = (LONG)(x + w);
	rect.bottom = (LONG)(y + h);

	ID3DXFont * pFont = (ID3DXFont * )font;
	if (pFont)
	{
		return pFont->DrawText(NULL, text, -1, &rect, DT_NOCLIP, color);
	}
#endif
	return 0;
}
/*
//add by Thor/h5nc
//begin
void CALL HGE_Impl::Font_Print(HD3DFONT font, float x, float y, unsigned short align, DWORD color, unsigned short shadow, char *format, ...)
{
	RECT rect;
	rect.right = (LONG)nScreenWidth;
	rect.bottom = (LONG)nScreenHeight;

	char * pArg = (char *) &format + sizeof(format);
	char buffer[512];
	vsprintf(buffer, format, pArg);

	char *linebuffer;
	int fontWidth;

	linebuffer = strtok(buffer, "\n");

	ID3DXFont * pFont = (ID3DXFont *)font;
	float oldx = x;

	LOGFONT lf;
	pFont->GetLogFont(&lf);
	fontWidth = lf.lfHeight + 1;
	switch(align)
	{
	case DT_CENTER:
		x -= fontWidth * strlen(linebuffer) * 0.25f + shadow;
		break;
	case DT_RIGHT:
		x -= fontWidth * strlen(linebuffer) * 0.5f + shadow;
		break;
	}

	for(int i=0;i<shadow;i++)
	{
		rect.left = (LONG)x + i+1;
		rect.top = (LONG)y + i+1;
		pFont->DrawText(linebuffer, -1, &rect, DT_WORDBREAK, 0xFF000000);
	}
	rect.left = (LONG)x;
	rect.top = (LONG)y;
	pFont->DrawText(linebuffer, -1, &rect, DT_WORDBREAK, color);

	while(1)
	{
		linebuffer = strtok(NULL, "\n");
		if(linebuffer != NULL)
		{
			x = oldx;
			y += fontWidth + shadow+1;
			if(align)
			{
				switch(align)
				{
				case DT_CENTER:
					x -= fontWidth * strlen(linebuffer) * 0.25f + shadow;
					break;
				case DT_RIGHT:
					x -= fontWidth * strlen(linebuffer) * 0.5f + shadow-1;
					break;
				}
			}
			for(int i=0;i<shadow;i++)
			{
				rect.left = (LONG)x + i+1;
				rect.top = (LONG)y + i+1;
				pFont->DrawText(linebuffer, -1, &rect, DT_WORDBREAK, 0xFF000000);
			}
			rect.left = (LONG)x;
			rect.top = (LONG)y;
			pFont->DrawText(linebuffer, -1, &rect, DT_WORDBREAK, color);
		}
		else
			break;
	}	
}

void CALL HGE_Impl::Font_Print(HD3DFONT font, float x, float y, float w, float h, unsigned short align, DWORD color, unsigned short shadow, char *format, ...)
{
	RECT rect;
	rect.right = (LONG)(w + x);
	rect.bottom = (LONG)(h + y);

	char * pArg = (char *) &format + sizeof(format);
	char buffer[512];
	vsprintf(buffer, format, pArg);

	char *linebuffer;
	int nline = 1;
	int fontWidth;
	for(BYTE i=0; i<strlen(buffer); i++)
	{
		if(buffer[i] == '\n')
			nline++;
	}
	linebuffer = strtok(buffer, "\n");

	ID3DXFont * pFont = (ID3DXFont *)font;
	float oldx = x;

	LOGFONT lf;
	pFont->GetLogFont(&lf);
	fontWidth = lf.lfHeight+1;
	if(align & DT_CENTER)
		x += w * 0.5f - fontWidth * strlen(linebuffer) * 0.25f - shadow;
	else if(align & DT_RIGHT)
		x += w - fontWidth * strlen(linebuffer) * 0.5f - shadow;
	if(align & DT_VCENTER)
		y += (h - (fontWidth + shadow+1) * nline) * 0.5f + 2;
	else if(align & DT_BOTTOM)
		y += h - (fontWidth + shadow+1) * nline;

	for(int i=0;i<shadow;i++)
	{
		rect.left = (LONG)x + i+1;
		rect.top = (LONG)y + i+1;
		pFont->DrawText(linebuffer, -1, &rect, DT_WORDBREAK, 0xFF000000);
	}
	rect.left = (LONG)x;
	rect.top = (LONG)y;
	pFont->DrawText(linebuffer, -1, &rect, DT_WORDBREAK, color);
	
	while(1)
	{
		linebuffer = strtok(NULL, "\n");
		if(linebuffer != NULL)
		{
			x = oldx;
			y += fontWidth + shadow+1;
			if(align)
			{
				if(align & DT_CENTER)
					x += w * 0.5f - fontWidth * strlen(linebuffer) * 0.25f - shadow;
				else if(align & DT_RIGHT)
					x += w - fontWidth * strlen(linebuffer) * 0.5f - shadow;
			}
			for(int i=0;i<shadow;i++)
			{
				rect.left = (LONG)x + i+1;
				rect.top = (LONG)y + i+1;
				pFont->DrawText(linebuffer, -1, &rect, DT_WORDBREAK, 0xFF000000);
			}
			rect.left = (LONG)x;
			rect.top = (LONG)y;
			pFont->DrawText(linebuffer, -1, &rect, DT_WORDBREAK, color);
		}
		else
			break;
	}
}
//end
*/
void HGE_Impl::_FontDone()
{
	while (fontList != NULL)
	{
		CFontList * temp = fontList;
		fontList = temp->next;
		delete temp;
	}
}