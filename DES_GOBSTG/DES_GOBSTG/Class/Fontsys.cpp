#include "../Header/Fontsys.h"
#include "../Header/Main.h"
#include "../Header/Scripter.h"
#include "../Header/Data.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/Player.h"
#include "../Header/BResource.h"

HD3DFONT Fontsys::d3dfont = NULL;
hgeFont * Fontsys::font = NULL;

Fontsys::Fontsys()
{
}

Fontsys::~Fontsys()
{
}

void Fontsys::Release()
{
	if (font)
	{
		delete font;
		font = NULL;
	}
}

void Fontsys::Init(HD3DFONT _d3dfont)
{
	d3dfont = _d3dfont;
	Release();
//	changeID = -1;
}

void Fontsys::DoHeatUpBuffer( const char* str, list<int> * charcodelist )
{
	int nowindex = 0;
	int len = strlen(str);
	if (len)
	{
		while (nowindex < len)
		{
			int i=*(unsigned char*)(&(str[nowindex]));
			nowindex++;
			if (i > 0x7f && nowindex < len)
			{
				i = i << 8;
				i = i | (*(unsigned char*)(&(str[nowindex])));
				nowindex++;
			}
			else
			{
				continue;
			}
			bool tocontinue = false;
			list<int>::iterator it=charcodelist->begin();
			for (; it!=charcodelist->end(); it++)
			{
				if (*it == i)
				{
					tocontinue = true;
					break;
				}
				else if (*it > i)
				{
					break;
				}
			}
			if (tocontinue)
			{
				continue;
			}
			int _charcode = i;
			charcodelist->insert(it, 1, _charcode);
//			charcodelist->push_back(_charcode);
		}
	}
}

void Fontsys::HeatUp(bool rebuildfont)
{
	if (rebuildfont)
	{
#ifdef __WIN32
		if (!d3dfont)
		{
			return;
		}

		list<int> charcodelist;

		for (int i=0; i<PLAYERTYPEMAX; i++)
		{
			DoHeatUpBuffer(BResource::bres.playerdata[i].name, &charcodelist);
			for (int j=0; j<3; j++)
			{
				DoHeatUpBuffer(BResource::bres.playerdata[i].spellname[j], &charcodelist);
			}
		}
		for (int i=0; i<ENEMYTYPEMAX; i++)
		{
			DoHeatUpBuffer(BResource::bres.enemydata[i].name, &charcodelist);
			DoHeatUpBuffer(BResource::bres.enemydata[i].ename, &charcodelist);
		}
		for (int i=0; i<MUSICMAX; i++)
		{
			DoHeatUpBuffer(BResource::bres.musdata[i].musicname, &charcodelist);
		}
		Export_Lua::HeatUp(&charcodelist);

		int * charcodes = (int *)malloc(charcodelist.size() * sizeof(int));
		int i = 0;
		for (list<int>::iterator it=charcodelist.begin(); it!=charcodelist.end(); it++, i++)
		{
			charcodes[i] = *it;
		}
		if (hgeFont::CreateFontFileByInfo(charcodes, i, BResource::bres.resdata.fontfilename, d3dfont, 2))
		{
		}
		free(charcodes);
#endif // __WIN32
	}

	if (font)
	{
		delete font;
	}
	font = new hgeFont(BResource::bres.resdata.fontfilename);

	/*
	for (int i=0; i<scr.strdescIndex; i+=(i+1))
	{
		SignUp(FONTSYS_CHATUSE, strdesc[i]);
	}
	*/
/*
	for (int i=0; i<PLAYERTYPEMAX; i++)
	{
		SignUp(i%FONTSYSMAX, Data::data.getPlayerName(i), 1.25f);
	}
	for (int i=0; i<ENEMYTYPEMAX; i++)
	{
		SignUp(i%FONTSYSMAX, Data::data.getEnemyName(i), 1.25f);
	}*/

}

void Fontsys::FocusChanged()
{
/*
	Release();
	SignUp(FONTSYS_CHATUSE, NULL, fontscale[FONTSYS_CHATUSE]);
	SignUp(FONTSYS_SPELLNAMEUSE, NULL, fontscale[FONTSYS_SPELLNAMEUSE]);
	if (changeID >= 0)
	{
		for (int i=0; i<=changeID; i++)
		{
			SignUp(i, NULL, fontscale[i]);
		}
	}*/

}

int Fontsys::strTranslate(char * dtext, const char * stext)
{
	int ret = 1;
	int j=0;
	strcpy(dtext, "");
	for(int i=0;i<(int)strlen(stext);i++)
	{
		if (stext[i] == '\n')
		{
			ret++;
		}
		if (stext[i]<0)
		{
			char twchar[3];
			twchar[0] = stext[i];
			i++;
			j+=2;
			twchar[1] = stext[i];
			twchar[2] = 0;
			strcat(dtext, twchar);
			continue;
		}
		if(stext[i] == FONTSYS_TRANSCHAR)
		{
			i++;
			if(stext[i] != FONTSYS_TRANSCHAR)
			{
				int strcodecon = stext[i] - '0';
				if(!strcodecon)
				{
					int strcodeval = (stext[i+1] - '0') * 10 +	(stext[i+2] - '0');
					while(j < strcodeval)
					{
						strcat(dtext, " ");
						j++;
					}
					i += 2;
					continue;
				}
				else
				{
					int strcodeval1 = (stext[i+1] - '0') * 10 +	(stext[i+2] - '0');
					int strcodeval2 = (stext[i+3] - '0') * 10 +	(stext[i+4] - '0');
					while(j < strcodeval1)
					{
						strcat(dtext, " ");
						j++;
					}
					i += 4;
					char buffer[32];
					int k = 0;
					while(!(stext[i+1] == FONTSYS_TRANSCHAR && stext[i+2] == FONTSYS_CONTROLCHAR))
					{
						i++;
						buffer[k] = stext[i];
						k++;
					}
					buffer[k] = 0;
					for(int l=k;l<strcodeval2-strcodeval1;l++)
					{
						if(strcodecon == 2)
							strcat(dtext, "0");
						else
							strcat(dtext, " ");
						j++;
					}
					strcat(dtext, buffer);
					i += 2;
					j += k;
					continue;
				}
			}
		}
		char tbuff[2];
		tbuff[0] = stext[i];
		tbuff[1] = 0;
		strcat(dtext, tbuff);
		j++;
	}
	return ret;
}

void Fontsys::SignUp(const char * _text, float scale)
{
	if (_text != NULL)
	{
		strTranslate(text, _text);
	}
	fontscale = scale;
	
}

void Fontsys::SetColor(DWORD col0, DWORD col1, DWORD col2, DWORD col3)
{
	font->SetColor(col0, col1, col2, col3);
}

void Fontsys::SetColor(DWORD col, int i)
{
	font->SetColor(col, i);
}

void Fontsys::Render(float x, float y, float shadow, BYTE alignflag)
{
	if (!font)
	{
		return;
	}
	if (shadow)
	{
		DWORD _col[4];
		for (int i=0; i<4; i++)
		{
			_col[i] = font->GetColor(i);
		}
		font->SetColor(_col[0]&0xff000000, _col[1]&0xff000000, _col[2]&0xff000000, _col[3]&0xff000000);
		Render(x+shadow, y+shadow, 0, alignflag);
		font->SetColor(_col[0], _col[1], _col[2], _col[3]);
	}
	font->SetScale(fontscale);
	font->Render(x, y, alignflag, text);
}