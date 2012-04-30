/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hgeFont helper class implementation
*/


#include "../../include/hgefont.h"
#include <stdlib.h>
#include <stdio.h>

const char FNTHEADERTAG[]="[HGEFONT]";
const char FNTBITMAPNUMTAG[]="BitmapNum";
const char FNTBITMAPTAG[]="Bitmap";
const char FNTSIZETAG[]="Size";
const char FNTCHARTAG[]="Char";
const char FNTWCHARTAG[]="WChar";

#define _FNTCOMMAND_BITMAPNUM	0x00
#define _FNTCOMMAND_BITMAP		0x01
#define _FNTCOMMAND_SIZE		0x02
#define _FNTCOMMAND_CHAR		0x10
#define _FNTCOMMAND_WCHAR		0x20


HGE *hgeFont::hge=0;


/************************************************************************/
/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
void hgeFont::_FontInit(int _size)
{
	hge=hgeCreate(HGE_VERSION);

	fHeight=0.0f;
	fScale=1.0f;
	fProportion=1.0f;
	fRot=0.0f;
	fTracking=0.0f;
	fSpacing=1.0f;
	hTexture=NULL;
	texnum = 0;

	fZ=0;
	nBlend=BLEND_DEFAULT;
	for (int i=0; i<4; i++)
	{
		col[i] = 0xFFFFFFFF;
	}

	letters = NULL;
	pre = NULL;
	post = NULL;
	wCh = NULL;
	bWide = false;
	size = 0;

	_FontResize(_size);

/*
	ZeroMemory( &letters, sizeof(letters) );
	ZeroMemory( &pre, sizeof(letters) );
	ZeroMemory( &post, sizeof(letters) );*/

}

void hgeFont::_FontResize(int _size/* =256 */)
{
	if (size || letters || pre || post || wCh)
	{
		_FontFree();
	}
	size = _size;
	if (size > 0)
	{
		letters = (hgeSprite**)malloc(sizeof(hgeSprite *) * size);
		pre = (float *)malloc(sizeof(float) * size);
		post = (float *)malloc(sizeof(float) * size);
		wCh = (int *)malloc(sizeof(int) * size);

		ZeroMemory( letters, sizeof(hgeSprite *) * size );
		ZeroMemory( pre, sizeof(float) * size );
		ZeroMemory( post, sizeof(float) * size );
		ZeroMemory( wCh, sizeof(int) * size );
	}
	if (size > 256)
	{
		bWide = true;
	}
}

void hgeFont::_FontFree()
{
	if (letters)
	{
		for(int i=0; i<size; i++)
		{
			if(letters[i]) delete letters[i];
		}
		free(letters);
		letters = NULL;
	}
	if (pre)
	{
		free(pre);
		pre = NULL;
	}
	if (post)
	{
		free(post);
		post = NULL;
	}
	if (wCh)
	{
		free(wCh);
		wCh = NULL;
	}
	for (int i=0; i<texnum; i++)
	{
		if(hTexture[i].tex)
		{
			hge->Texture_Free(hTexture[i]);
		}
	}
	if (hTexture)
	{
		free(hTexture);
		hTexture = NULL;
	}
	texnum = 0;
	size = 0;
}

void hgeFont::_FontTexResize(int _texnum/* =0 */)
{
	if (texnum)
	{
		for (int i=0; i<texnum; i++)
		{
			if (hTexture)
			{
				if (hTexture[i].tex)
				{
					hge->Texture_Free(hTexture[i]);
				}
			}
		}
	}
	if (hTexture)
	{
		free(hTexture);
		hTexture = NULL;
	}
	texnum = _texnum;
	if (texnum > 0)
	{
		hTexture = (HTEXTURE *)malloc(sizeof(HTEXTURE) * texnum);
	}
}

/************************************************************************/
/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
void hgeFont::NewFont(const char *szFont, bool bMipmap/* =false */)
{
	void	*data;
	DWORD	datasize;
	char	*desc, *pdesc;
	char	linebuf[256];
	char	buf[_MAX_PATH], *pbuf;
	char	chr;
	int		i, x, y, w, h, a, c;
	int		_wCh = 0;
	int		_nTex = 0;
	int		_texnum = 0;
	int		_size = 0;
	int		nowtexnum = 0;

	// Setup variables
	
	// Load font description

	data=hge->Resource_Load(szFont, &datasize);
	if(!data) return;

	desc = new char[datasize+1];
	memcpy(desc,data,datasize);
	desc[datasize]=0;
	hge->Resource_Free(data);

	pdesc=_get_line(desc,linebuf);
	if(strcmp(linebuf, FNTHEADERTAG))
	{
		hge->System_Log("Font %s has incorrect format.", szFont);
		delete[] desc;	
		return;
	}

	// Parse font description

	while(pdesc = _get_line(pdesc,linebuf))
	{
		_wCh = -1;
		_nTex = 0;
		BYTE command;
		if (!strncmp(linebuf, FNTBITMAPNUMTAG, sizeof(FNTBITMAPNUMTAG)-1 ))
		{
			command = _FNTCOMMAND_BITMAPNUM;
		}
		else if (!strncmp(linebuf, FNTBITMAPTAG, sizeof(FNTBITMAPTAG)-1 ))
		{
			command = _FNTCOMMAND_BITMAP;
		}
		else if (!strncmp(linebuf, FNTSIZETAG, sizeof(FNTSIZETAG)-1 ))
		{
			command = _FNTCOMMAND_SIZE;
		}
		else if (!strncmp(linebuf, FNTCHARTAG, sizeof(FNTCHARTAG)-1 ))
		{
			command = _FNTCOMMAND_CHAR;
		}
		else if (!strncmp(linebuf, FNTWCHARTAG, sizeof(FNTWCHARTAG)-1 ))
		{
			command = _FNTCOMMAND_WCHAR;
		}

		if (command == _FNTCOMMAND_BITMAPNUM)
		{
			if (!sscanf(linebuf, "BitmapNum = %d", &_texnum))
			{
				continue;
			}
			_FontTexResize(_texnum);
		}
		else if(command == _FNTCOMMAND_BITMAP)
		{
			strcpy(buf,szFont);
			pbuf=strrchr(buf,'\\');
			if(!pbuf) pbuf=strrchr(buf,'/');
			if(!pbuf) pbuf=buf;
			else pbuf++;
			if(!sscanf(linebuf, "Bitmap = %s", pbuf)) continue;

			if (!texnum || !hTexture)
			{
				_FontTexResize(1);
			}

			if (nowtexnum < texnum && hTexture)
			{
				hTexture[nowtexnum]=hge->Texture_Load(buf, 0, bMipmap);
				if(!hTexture[nowtexnum].tex)
				{
					delete[] desc;	
					return;
				}
				nowtexnum++;
			}
		}

		else if (command == _FNTCOMMAND_SIZE)
		{
			if (!sscanf(linebuf, "Size = %d", &_size))
			{
				continue;
			}
			_FontResize(_size);
		}

		else if(command == _FNTCOMMAND_CHAR || command == _FNTCOMMAND_WCHAR)
		{
			if (!size)
			{
				_FontResize();
			}
			pbuf=strchr(linebuf,'=');
			if(!pbuf) continue;
			pbuf++;
			while(*pbuf==' ') pbuf++;
			if(*pbuf=='\"')
			{
				pbuf++;
				i=(unsigned char)*pbuf++;
				pbuf++; // skip "
			}
			else
			{
				i=0;
				while((*pbuf>='0' && *pbuf<='9') || (*pbuf>='A' && *pbuf<='F') || (*pbuf>='a' && *pbuf<='f'))
				{
					chr=*pbuf;
					if(chr >= 'a') chr-='a'-':';
					if(chr >= 'A') chr-='A'-':';
					chr-='0';
					if(chr>0xF) chr=0xF;
					i=(i << 4) | chr;
					pbuf++;
				}
				if(i<0 || i>=size) continue;
			}
			if (command == _FNTCOMMAND_CHAR)
			{
				sscanf(pbuf, " , %d , %d , %d , %d , %d , %d", &x, &y, &w, &h, &a, &c);
			}
			else if (command == _FNTCOMMAND_WCHAR)
			{
				sscanf(pbuf, " , %d , %d , %d , %d , %d , %d, %x, %d", &x, &y, &w, &h, &a, &c, &_wCh, &_nTex);
			}

			if (hTexture && _nTex < texnum)
			{
				ChangeSprite(i, hTexture[_nTex], (float)x, (float)y, (float)w, (float)h, (float)a, (float)c, _wCh);
			}
			/*
			letters[i] = new hgeSprite(hTexture, (float)x, (float)y, (float)w, (float)h);
			letters[i] -> SetHotSpot(0, 0);
			pre[i]=(float)a;
			post[i]=(float)c;
			if(h>fHeight) fHeight=(float)h;
			*/
		}
	}

	delete[] desc;	
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
hgeFont::hgeFont(int _size)
{
	_FontInit(_size);
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
hgeFont::hgeFont(const char *szFont, bool bMipmap)
{
	_FontInit(0);
	NewFont(szFont, bMipmap);
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
hgeFont::hgeFont(const hgeFont &fnt)
{
	hge=hgeCreate(HGE_VERSION);

	hTexture=fnt.hTexture;
	fHeight=fnt.fHeight;
	fScale=fnt.fScale;
	fRot=fnt.fRot;
	fTracking=fnt.fTracking;
	fSpacing=fnt.fSpacing;
	for (int i=0; i<4; i++)
	{
		col[i] = fnt.col[i];
	}
	fZ=fnt.fZ;
	nBlend=fnt.nBlend;

	for(int i=0; i<256; i++)
	{
		if(fnt.letters[i]) letters[i]=new hgeSprite(*fnt.letters[i]);
		else letters[i]=0;
		pre[i]=fnt.pre[i];
		post[i]=fnt.post[i];
	}
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
hgeFont& hgeFont::operator= (const hgeFont &fnt)
{
	if(this!=&fnt)
	{
		hTexture=fnt.hTexture;
		fHeight=fnt.fHeight;
		fScale=fnt.fScale;
		fRot=fnt.fRot;
		fTracking=fnt.fTracking;
		fSpacing=fnt.fSpacing;
		for (int i=0; i<4; i++)
		{
			col[i] = fnt.col[i];
		}
		fZ=fnt.fZ;
		nBlend=fnt.nBlend;

		for(int i=0; i<256; i++)
		{
			if(letters[i]) delete letters[i];
			if(fnt.letters[i]) letters[i]=new hgeSprite(*fnt.letters[i]);
			else letters[i]=0;
			pre[i]=fnt.pre[i];
			post[i]=fnt.post[i];
		}
	}

	return *this;
}

hgeFont::~hgeFont()
{
	_FontFree();
	hge->Release();
}

/************************************************************************/
/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
// begin
void hgeFont::ChangeSprite(int chr, hgeSprite * sprite, float pre_a, float post_c)
{
	if (!sprite || chr < 0 || chr >= size)
	{
		return;
	}
	float tex_x = 0;
	float tex_y = 0;
	float tex_w = 0;
	float tex_h = 0;
	sprite->GetTextureRect(&tex_x, &tex_y, &tex_w, &tex_h);
	ChangeSprite(chr, sprite->GetTexture(), tex_x, tex_y, tex_w, tex_h, pre_a, post_c);
}

void hgeFont::ChangeSprite(int chr, HTEXTURE tex, float tex_x, float tex_y, float tex_w, float tex_h, float pre_a, float post_c, int _wCh)
{
	if (chr < 0 || chr >= size)
	{
		return;
	}
	if (!letters[chr])
	{
		letters[chr] = new hgeSprite(tex, tex_x, tex_y, tex_w, tex_h);
	}
	else
	{
		letters[chr]->SetTexture(tex);
		letters[chr]->SetTextureRect(tex_x, tex_y, tex_w, tex_h);
	}
	letters[chr]->SetHotSpot(0, 0);
	pre[chr]=pre_a;
	post[chr]=post_c;
	wCh[chr]=_wCh;
	if (wCh[chr] >= 0)
	{
		bWide = true;
	}
	if(tex_h>fHeight) fHeight=tex_h;
}
// end

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
void hgeFont::RenderEx(float x, float y, int align, const char *string, float scale/* =1.0f */, float properation/* =1.0f */, float rotation/* =0 */, float tracking/* =0 */, float spacing/* =1.0f */)
{
	float _scale = fScale;
	float _properation = fProportion;
	float _rotation = fRot;
	float _tracking = fTracking;
	float _spacing = fSpacing;

	SetScale(scale);
	SetProportion(properation);
	SetRotation(rotation);
	SetTracking(tracking);
	SetSpacing(spacing);

	Render(x, y, align, string);

	SetScale(_scale);
	SetProportion(_properation);
	SetRotation(_rotation);
	SetTracking(_tracking);
	SetSpacing(_spacing);
}
/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
void hgeFont::Render(float x, float y, int align, const char *string)
{
	int i;
	float	fx=x;

	align &= HGETEXT_HORZMASK;
	if(align==HGETEXT_RIGHT) fx-=GetStringWidth(string, false);
	if(align==HGETEXT_CENTER) fx-=int(GetStringWidth(string, false)/2.0f);

	while(*string)
	{
		if(*string=='\n')
		{
			y+=int(fHeight*fScale*fSpacing);
			fx=x;
			if(align == HGETEXT_RIGHT)  fx -= GetStringWidth(string+1, false);
			if(align == HGETEXT_CENTER) fx -= int(GetStringWidth(string+1, false)/2.0f);
		}
		else
		{
			i=(unsigned char)*string;
			if (bWide)
			{
				if (i > 0x7f)
				{
					i = i << 8;
					string++;
					i = i | ((unsigned char)*string);
					i = ChangeWideChar(i);
				}
			}
			if (i >= 0 && i < size)
			{
				if(!letters[i]) i='?';
				if(letters[i])
				{
					fx += pre[i]*fScale*fProportion;
					letters[i]->SetColor(col[0], col[1], col[2], col[3]);
					letters[i]->RenderEx(fx, y, fRot, fScale*fProportion, fScale);
					fx += (letters[i]->GetWidth()+post[i]+fTracking)*fScale*fProportion;
				}
			}
		}
		string++;
	}
}

int hgeFont::ChangeWideChar(int wchr)
{
	for (int i=0; i<size; i++)
	{
		if (wCh[i] == wchr)
		{
			return i;
		}
	}
	return -1;
}

void hgeFont::printf(float x, float y, int align, const char *buffer)
{
	if (!letters)
	{
		return;
	}
/*
	char	*pArg=(char *) &format+sizeof(format);

	_vsnprintf(buffer, sizeof(buffer)-1, format, pArg);
	buffer[sizeof(buffer)-1]=0;
	//vsprintf(buffer, format, pArg);*/


	Render(x,y,align,buffer);
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
void hgeFont::printfb(float x, float y, float w, float h, int align, const char *buffer)
{
	char	chr, *pbuf, *prevword, *linestart;
	int		i,lines=0;
	float	tx, ty, hh, ww;

	if (!letters)
	{
		return;
	}
/*
	char	*pArg=(char *) &format+sizeof(format);

	_vsnprintf(buffer, sizeof(buffer)-1, format, pArg);
	buffer[sizeof(buffer)-1]=0;
	//vsprintf(buffer, format, pArg);*/


	linestart=(char *)buffer;
	pbuf=(char *)buffer;
	prevword=0;

	for(;;)
	{
		i=0;
		while(pbuf[i] && pbuf[i]!=' ' && pbuf[i]!='\n') i++;

		chr=pbuf[i];
		pbuf[i]=0;
		ww=GetStringWidth(linestart);
		pbuf[i]=chr;

		if(ww > w)
		{
			if(!chr)
			{
				lines++;
				break;
			}
			if(pbuf==linestart)
			{
				pbuf[i]='\n';
				linestart=&pbuf[i+1];
			}
			else
			{
				*prevword='\n';
				linestart=prevword+1;
				lines++;
			}
		}

		if(pbuf[i]=='\n')
		{
			prevword=&pbuf[i];
			linestart=&pbuf[i+1];
			pbuf=&pbuf[i+1];
			lines++;
			continue;
		}

		if(!pbuf[i]) {lines++;break;}

		prevword=&pbuf[i];
		pbuf=&pbuf[i+1];
	}
	
	tx=x;
	ty=y;
	hh=fHeight*fSpacing*fScale*lines;

	switch(align & HGETEXT_HORZMASK)
	{
		case HGETEXT_LEFT: break;
		case HGETEXT_RIGHT: tx+=w; break;
		case HGETEXT_CENTER: tx+=int(w/2); break;
	}

	switch(align & HGETEXT_VERTMASK)
	{
		case HGETEXT_TOP: break;
		case HGETEXT_BOTTOM: ty+=h-hh; break;
		case HGETEXT_MIDDLE: ty+=int((h-hh)/2); break;
	}

	Render(tx,ty,align,buffer);
}

float hgeFont::GetStringWidth(const char *string, bool bMultiline) const
{
	if (!letters)
	{
		return 0;
	}
	int i;
	float linew, w = 0;

	while(*string)
	{
		linew = 0;

		while(*string && *string!='\n')
		{
			i=(unsigned char)*string;
			if(!letters[i]) i='?';
				if(letters[i])
					linew += letters[i]->GetWidth() + pre[i] + post[i] + fTracking;

			string++;
		}

		if(!bMultiline) return linew*fScale*fProportion;

		if(linew > w) w = linew;

		while (*string == '\n' || *string == '\r') string++;
  }

	return w*fScale*fProportion;
}


/************************************************************************/
/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
DWORD hgeFont::GetColor(int i)
{
	return col[i];
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
/*
void hgeFont::SetColor(DWORD col)
{
	dwCol=col;
	for(int i=0;i<256;i++) if(letters[i]) letters[i]->SetColor(col);
}
*/
void hgeFont::SetColor(DWORD _col, int i /*=-1*/)
{
	if (i < 0)
	{
		SetColor(_col, _col, _col, _col);
	}
	else
	{
		col[i] = _col;
	}
}

void hgeFont::SetColor(DWORD col0, DWORD col1, DWORD col2, DWORD col3)
{
	col[0] = col0;
	col[1] = col1;
	col[2] = col2;
	col[3] = col3;
	/*
	for(int i=0;i<256;i++) 
		if(letters[i]) 
		{
			letters[i]->SetColor(col0, 0);
			letters[i]->SetColor(col1, 1);
			letters[i]->SetColor(col2, 2);
			letters[i]->SetColor(col3, 3);
		}
	*/
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
void hgeFont::SetZ(float z, hge3DPoint *ptfar)
{
	fZ=z;
	for(int i=0;i<256;i++) if(letters[i]) letters[i]->SetZ(z, z, z, z, ptfar);
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
void hgeFont::SetBlendMode(int blend)
{
	nBlend=blend;
	for(int i=0;i<256;i++) if(letters[i]) letters[i]->SetBlendMode(blend);
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
char *hgeFont::_get_line(char *file, char *line)
{
	int i=0;

	if(!file[i]) return 0;

	while(file[i] && file[i]!='\n' && file[i]!='\r')
	{
		line[i]=file[i];
		i++;
	}
	line[i]=0;

	while(file[i] && (file[i]=='\n' || file[i]=='\r')) i++;

	if(file[i]) return file+i;
	else return 0;
}

#ifdef __WIN32
bool hgeFont::CreateFontFileByInfo( int * charcode, int num, const char * fontfilename, HD3DFONT d3dfont, int fontscale /*=1*/ )
{
	if (num < 1 || !charcode || !fontfilename)
	{
		return false;
	}

	if (fontscale < 1)
	{
		fontscale = 1;
	}

	int fontw = 16*fontscale;
	int fonth = 16*fontscale;

	int texw = 256;
	int texh = 256;

	int nrow = texw/fontw;
	int ncol = texh/fonth;

	if (!nrow || !ncol)
	{
		return false;
	}

	int fonttexnum = (num-1) / (nrow*ncol) + 1 + 1;
	FILE * fontfile = fopen(hge->Resource_MakePath(fontfilename), "w");
	if (!fontfile)
	{
		return false;
	}

	HTARGET tar = hge->Target_Create(texw, texh, false);
	if (!hge->Gfx_BeginScene(tar))
	{
		hge->Target_Free(tar);
		return false;
	}
	hge->Gfx_Clear(0x00000000);

	char savefilenamebase[_MAX_PATH];
	char buffer[256];
	char textbuffer[16];
	strcpy(buffer, "[HGEFONT]\n\n");
	fwrite(buffer, strlen(buffer), 1, fontfile);
	sprintf(buffer, "BitmapNum=%d\n", fonttexnum);
	fwrite(buffer, strlen(buffer), 1, fontfile);

	strcpy(savefilenamebase, hge->Resource_MakePath(fontfilename));
	int filenamelen = strlen(savefilenamebase);
	while (filenamelen > 1)
	{
		filenamelen--;
		if (savefilenamebase[filenamelen] != M_FOLDER_SLASH && savefilenamebase[filenamelen] != M_FOLDER_SLASH_WRONG)
		{
			savefilenamebase[filenamelen] = 0;
		}
		else
		{
			break;
		}
	}

	for (int i=0; i<fonttexnum; i++)
	{
		sprintf(buffer, "Bitmap=font_%02d.png\n", i);
		fwrite(buffer, strlen(buffer), 1, fontfile);
	}
	sprintf(buffer, "Size=%d\n\n", num + 0x100);
	fwrite(buffer, strlen(buffer), 1, fontfile);

	int i=0x10;
	for (; i<0x80; i++)
	{
		int x = i % (nrow*2) * (fontw/2);
		int y = i / (nrow*2) * fonth;
		sprintf(buffer, "Char=\"%c\", %d, %d, %d, %d, 0, 0\n", i, x, y, fontw/2, fonth);
		fwrite(buffer, strlen(buffer), 1, fontfile);
		sprintf(textbuffer, "%c", i);
		hge->Gfx_RenderText(d3dfont, textbuffer, x, y, fontw/2, fonth);
	}

	int nowtexnum = 0;

	i = 0x100;
	for (int j=0; j<num; j++, i++)
	{
		int texnum = (i-0x100) / (nrow*ncol)+1;
		int x = (i) % nrow * fontw;
		int y = ((i) / nrow) % nrow * fonth;
		if (nowtexnum != texnum)
		{
			hge->Gfx_EndScene();
			HTEXTURE tex = hge->Target_GetTexture(tar);
			sprintf(buffer, "%sfont_%02d.png", savefilenamebase, nowtexnum);
			hge->Texture_Save(tex, buffer, D3DXIFF_PNG);

			if (!hge->Gfx_BeginScene(tar))
			{
				hge->Target_Free(tar);
				return false;
			}
			hge->Gfx_Clear(0x00000000);
			nowtexnum = texnum;
		}
		sprintf(buffer, "WChar=%x, %d, %d, %d, %d, 0, 0, %x, %d\n", i, x, y, fontw, fonth, charcode[j], texnum);
		fwrite(buffer, strlen(buffer), 1, fontfile);

		textbuffer[0] = (charcode[j] & 0xff00) >> 8;
		textbuffer[1] = charcode[j] & 0xff;
		textbuffer[2] = 0;
		hge->Gfx_RenderText(d3dfont, textbuffer, x, y, fontw/2, fonth);
	}

	hge->Gfx_EndScene();
	HTEXTURE tex = hge->Target_GetTexture(tar);
	sprintf(buffer, "%sfont_%02d.png", savefilenamebase, nowtexnum);
	hge->Texture_Save(tex, buffer, D3DXIFF_PNG);

	hge->Target_Free(tar);

	fclose(fontfile);

	return true;
}
#endif