#ifndef _FONTSYS_H
#define _FONTSYS_H

#include "MainDependency.h"
#include "Const.h"

#define FONTSYS_DEFAULT_SHADOW	0.4f

#define FONTSYS_TRANSCHAR		'|'
#define FONTSYS_CONTROLCHAR		'E'
#define FONTSYS_CONTROLSTR		"|E"

#define FONTSYS_TARGETWIDTH		M_CLIENT_WIDTH
#define FONTSYS_TARGETHEIGHT	(M_CLIENT_HEIGHT/2)

#define FONTSYS_CHATTEXTWIDTH	300
#define FONTSYS_CHATTEXTHEIGHT	80

class Fontsys
{
public:
	Fontsys();
	~Fontsys();

	static void Init(HD3DFONT d3dfont);
	static void HeatUp(bool rebuildfont=false);
	static void DoHeatUpBuffer(const char* str, list<int> * charcodelist);
	static void FocusChanged();
	static void Release();

	void SignUp(const char * text = NULL, float scale=1.0f);
	void SetColor(DWORD col0, DWORD col1, DWORD col2, DWORD col3);
	void SetColor(DWORD col, int i=-1);
	void Render(float x, float y, float shadow = 0, BYTE alignflag = HGETEXT_LEFT|HGETEXT_TOP);

	int strTranslate(char * dtext, const char * stext);

public:
	char text[M_STRMAX];
	float fontscale;

	static HD3DFONT d3dfont;
	static hgeFont * font;
};

#endif