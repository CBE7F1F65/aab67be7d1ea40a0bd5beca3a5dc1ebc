#ifndef _FRONTDISPLAY_H
#define _FRONTDISPLAY_H

#include "MainDependency.h"
#include "Const.h"
#include "Effectsys.h"
#include "InfoQuad.h"
#include "Enemy.h"
#include "Fontsys.h"

#define FDISP_ASCII_BEGIN		0x20
#define FDISP_ASCII_END			0x81
#define FDISP_ASCIISMALL_END	0x7E
#define FDISP_ASCII_MAX			(FDISP_ASCII_END-FDISP_ASCII_BEGIN+1)

#define FDISP_LIFEINDIMAX	3

#define FDISP_COUNTDOWNTIME	180

struct fdPostPrint
{
	char str[M_STRMAX];
	hgeFont * font;
	float x;
	float y;
	int align;
	float scale;
	float properation;
	float rotation;
	float tracking;
	float spacing;
};

struct ftPanelSet 
{
	hgeSprite * leftedge[M_PL_MATCHMAXPLAYER];
	hgeSprite * rightedge[M_PL_MATCHMAXPLAYER];
	hgeSprite * topedge[M_PL_MATCHMAXPLAYER];
	hgeSprite * bottomedge[M_PL_MATCHMAXPLAYER];
	hgeSprite * spellpoint;
	hgeSprite * combobar;
	hgeSprite * winindi;
	hgeSprite * slot;
	hgeSprite * slotback;
	hgeSprite * lifeindi[FDISP_LIFEINDIMAX];
	int winindiheadangle;
	int slotindex;
	int combobarindex;
};

struct ftInfoSet
{
	hgeFont * asciifont;
	hgeFont * itemfont;
	hgeFont * spellpointdigitfont;
	hgeFont * headdigitfont;
	HD3DFONT normalfont;

	hgeSprite * cutin;
	hgeSprite * plchat_1;
	hgeSprite * plchat_2;
	hgeSprite * plchat_3;
	hgeSprite * enchat_1;
	hgeSprite * enchat_2;
	hgeSprite * enchat_3;

	hgeSprite * timecircle;
	hgeSprite * enemyx;

	hgeSprite * lifebar;

	hgeSprite * textbox;
	hgeSprite * demo;
	hgeSprite * loading;
};

struct ftNumSet 
{
	union{
		struct  
		{
			hgeSprite * num_0;
			hgeSprite * num_1;
			hgeSprite * num_2;
			hgeSprite * num_3;
			hgeSprite * num_4;
			hgeSprite * num_5;
			hgeSprite * num_6;
			hgeSprite * num_7;
			hgeSprite * num_8;
			hgeSprite * num_9;
		};
		hgeSprite * num[10];
	};

	hgeSprite * num_add;
	hgeSprite * num_sub;
	hgeSprite * num_mul;
	hgeSprite * num_div;
	hgeSprite * num_mod;
	hgeSprite * num_dot;
};

struct ftItemNumSet 
{
	union {
		struct {
			hgeSprite * num_0;
			hgeSprite * num_1;
			hgeSprite * num_2;
			hgeSprite * num_3;
			hgeSprite * num_4;
			hgeSprite * num_5;
			hgeSprite * num_6;
			hgeSprite * num_7;
			hgeSprite * num_8;
			hgeSprite * num_9;
			hgeSprite * fadeI_0;
			hgeSprite * fadeI_1;
			hgeSprite * fadeI_2;
			hgeSprite * fadeI_3;
			hgeSprite * fadeI_4;
			hgeSprite * fadeI_5;
			hgeSprite * fadeI_6;
			hgeSprite * fadeI_7;
			hgeSprite * fadeI_8;
			hgeSprite * fadeI_9;
			hgeSprite * fadeII_0;
			hgeSprite * fadeII_1;
			hgeSprite * fadeII_2;
			hgeSprite * fadeII_3;
			hgeSprite * fadeII_4;
			hgeSprite * fadeII_5;
			hgeSprite * fadeII_6;
			hgeSprite * fadeII_7;
			hgeSprite * fadeII_8;
			hgeSprite * fadeII_9;
			hgeSprite * bonus;
		};
		hgeSprite * itemnum[31];
	};
};

struct ftSpellPointNumSet
{
	union {
		struct {
			hgeSprite * num_0;
			hgeSprite * num_1;
			hgeSprite * num_2;
			hgeSprite * num_3;
			hgeSprite * num_4;
			hgeSprite * num_5;
			hgeSprite * num_6;
			hgeSprite * num_7;
			hgeSprite * num_8;
			hgeSprite * num_9;
			hgeSprite * rednum_0;
			hgeSprite * rednum_1;
			hgeSprite * rednum_2;
			hgeSprite * rednum_3;
			hgeSprite * rednum_4;
			hgeSprite * rednum_5;
			hgeSprite * rednum_6;
			hgeSprite * rednum_7;
			hgeSprite * rednum_8;
			hgeSprite * rednum_9;
			hgeSprite * hit;
			hgeSprite * rethit;
		};
		hgeSprite * spellpointnum[22];
	};
};

struct ftGameInfoDisplaySet
{
	union {
		struct {
			hgeSprite * num_0;
			hgeSprite * num_1;
			hgeSprite * num_2;
			hgeSprite * num_3;
			hgeSprite * num_4;
			hgeSprite * num_5;
			hgeSprite * num_6;
			hgeSprite * num_7;
			hgeSprite * num_8;
			hgeSprite * num_9;
			hgeSprite * slash;
			hgeSprite * colon;
			hgeSprite * space;
			hgeSprite * charge;
			hgeSprite * chargemax;
			hgeSprite * gaugefilled;
			hgeSprite * gaugelevel;
			hgeSprite * caution;
			hgeSprite * lastlife;
			hgeSprite * lily;
			hgeSprite * spellline;
		};
		hgeSprite * gameinfodisplay[21];
	};
	BYTE gaugefilledcountdown[M_PL_MATCHMAXPLAYER];
	BYTE lastlifecountdown[M_PL_MATCHMAXPLAYER];
	BYTE lilycountdown;
	Fontsys fsSpell[M_PL_MATCHMAXPLAYER][3];
	Fontsys fsMusic;
};

struct ftAscIISet 
{
	union {
		struct{
			hgeSprite * space;
			hgeSprite * x21;
			hgeSprite * x22;
			hgeSprite * x23;
			hgeSprite * x24;
			hgeSprite * x25;
			hgeSprite * x26;
			hgeSprite * x27;
			hgeSprite * x28;
			hgeSprite * x29;
			hgeSprite * x2A;
			hgeSprite * x2B;
			hgeSprite * x2C;
			hgeSprite * x2D;
			hgeSprite * x2E;
			hgeSprite * x2F;
			hgeSprite * num_0;
			hgeSprite * num_1;
			hgeSprite * num_2;
			hgeSprite * num_3;
			hgeSprite * num_4;
			hgeSprite * num_5;
			hgeSprite * num_6;
			hgeSprite * num_7;
			hgeSprite * num_8;
			hgeSprite * num_9;
			hgeSprite * x3A;
			hgeSprite * x3B;
			hgeSprite * x3C;
			hgeSprite * x3D;
			hgeSprite * x3E;
			hgeSprite * x3F;
			hgeSprite * x40;
			hgeSprite * ch_A;
			hgeSprite * ch_B;
			hgeSprite * ch_C;
			hgeSprite * ch_D;
			hgeSprite * ch_E;
			hgeSprite * ch_F;
			hgeSprite * ch_G;
			hgeSprite * ch_H;
			hgeSprite * ch_I;
			hgeSprite * ch_J;
			hgeSprite * ch_K;
			hgeSprite * ch_L;
			hgeSprite * ch_M;
			hgeSprite * ch_N;
			hgeSprite * ch_O;
			hgeSprite * ch_P;
			hgeSprite * ch_Q;
			hgeSprite * ch_R;
			hgeSprite * ch_S;
			hgeSprite * ch_T;
			hgeSprite * ch_U;
			hgeSprite * ch_V;
			hgeSprite * ch_W;
			hgeSprite * ch_X;
			hgeSprite * ch_Y;
			hgeSprite * ch_Z;
			hgeSprite * x5B;
			hgeSprite * x5C;
			hgeSprite * x5D;
			hgeSprite * x5E;
			hgeSprite * x5F;
			hgeSprite * x60;
			hgeSprite * ch_a;
			hgeSprite * ch_b;
			hgeSprite * ch_c;
			hgeSprite * ch_d;
			hgeSprite * ch_e;
			hgeSprite * ch_f;
			hgeSprite * ch_g;
			hgeSprite * ch_h;
			hgeSprite * ch_i;
			hgeSprite * ch_j;
			hgeSprite * ch_k;
			hgeSprite * ch_l;
			hgeSprite * ch_m;
			hgeSprite * ch_n;
			hgeSprite * ch_o;
			hgeSprite * ch_p;
			hgeSprite * ch_q;
			hgeSprite * ch_r;
			hgeSprite * ch_s;
			hgeSprite * ch_t;
			hgeSprite * ch_u;
			hgeSprite * ch_v;
			hgeSprite * ch_w;
			hgeSprite * ch_x;
			hgeSprite * ch_y;
			hgeSprite * ch_z;
			hgeSprite * x7B;
			hgeSprite * x7C;
			hgeSprite * x7D;
			hgeSprite * x7E;
			hgeSprite * backspace;
			hgeSprite * end;
			hgeSprite * block;
		};
		hgeSprite * ascii[FDISP_ASCII_MAX];
	};
};


#define FDISP_PANEL			0
#define FDISP_SPELLNAME_0	1
#define FDISP_SPELLNAME_1	2
#define FDISP_MUSICNAME		3

#define FDISPSTATE_ON	1
#define FDISPSTATE_OFF	0

class FrontDisplay
{
public:
	FrontDisplay();
	~FrontDisplay();

	bool Init();
	void Release();

	void action();

	void RenderPanel();
	void RenderHeadInfo(BYTE playerindex);
	void RenderSpellName(BYTE playerindex);

	void RenderEnemyX();

	void SetState(BYTE type, BYTE state=FDISPSTATE_ON);
	void SetValue(LONGLONG llval, int ival, float fval, bool bval);

	void SignUpSpell();
	void OnShootCharge(BYTE playerindex, BYTE nowshootingcharge);
	void OnChangeMusic(int musicID);

	void BuildPostPrint(hgeFont * font, float x, float y, const char * str, int align=HGETEXT_CENTER|HGETEXT_MIDDLE, float scale=1.0f, float properation=1.0f, float rotation=0, float tracking=0, float spacing=1.0f);
	void RenderPostPrint();

	ftPanelSet panel;
	ftInfoSet info;
	ftNumSet bignum;
	ftItemNumSet itemnum;
	ftSpellPointNumSet spellpointnum;
	ftGameInfoDisplaySet gameinfodisplay;
	ftAscIISet ascii;

	list<fdPostPrint> postprintlist;

	LONGLONG llval;
	int ival;
	float fval;
	bool bval;

	BYTE panelstate;
	BYTE spellnamestate[M_PL_MATCHMAXPLAYER];
	BYTE spellnameclass[M_PL_MATCHMAXPLAYER];
	BYTE musicstate;

	static FrontDisplay fdisp;
};

#endif