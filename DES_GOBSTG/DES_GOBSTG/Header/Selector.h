#ifndef _SELECTOR_H
#define _SELECTOR_H

#include "MainDependency.h"
#include "Const.h"
#include "Fontsys.h"

#define SEL_NULL		0x00
#define SEL_NONACTIVE	0x10
#define SEL_GRAY		0x20
#define SEL_STAY		0x40
#define SEL_NOSHIFT		0x80

#define SEL_STATEMAX	0x04

#define	SEL_NONE		0x00
#define	SEL_OVER		0x01
#define	SEL_ENTER		0x02
#define	SEL_LEAVE		0x04

#define SEL_INFOMASK	0x0f
#define SEL_STATEMASK	0xf0

#define SELINFO_NONE	0
#define SELINFO_OVER	1
#define SELINFO_ENTER	2
#define SELINFO_LEAVE	3

#define SELOP_EQUAL		1
#define SELOP_SET		2
#define SELOP_UNSET		4

#define SELFADE_UP		1
#define SELFADE_DOWN	2
#define SELFADE_LEFT	4
#define SELFADE_RIGHT	8


struct seladj
{
	float xadj;
	float yadj;
};

class Selector
{
public:
	Selector();
	~Selector();

	void valueSet(BYTE ID, int siID, float cenx, float ceny,
		float hscale = 1, float vscale = 0,
		BYTE flag = SEL_NULL);
	void infoSet(char * info, DWORD ucol = 0xffffffff, DWORD dcol = 0xffffffff, float shadow = FONTSYS_DEFAULT_SHADOW, float xoffset=0, float yoffset=0, float hscale=1.0f, float vscale=0.0f, BYTE alignflag=HGETEXT_CENTER|HGETEXT_MIDDLE, bool sync=false);
	void actionSet(BYTE setflag, float xadj, float yadj);
	void actionSet(BYTE setflag, seladj * adj=NULL);
	void setAdj(int i, float xadj, float yadj);
	void SetMaxtime(int maxtime);
	void Complete();

	bool checkSub();
	void PreAction(int nselect, int select, int * fvID, Selector ** fvselector);
	bool PostAction(int * select, int sellock, int nPageNum, float fadebegin, float offset, int shiftangle, float * selectframex, float * selectframey);
	bool checkFVState();
	void ChangeState(BYTE state, BYTE op);

	void Render();
	void RenderInfo();

public:
	seladj	adj[SEL_STATEMAX];

	Fontsys fsinfo;
	DWORD infoucol;
	DWORD infodcol;
	float infoshadow;
	float infoxoffset;
	float infoyoffset;
	float infohscale;
	float infovscale;
	float infoalignflag;
	bool infosync;

	float	x;
	float	y;
	float	hscale;
	float	vscale;
	bool	sub;

	hgeSprite * sprite;

	BYTE	ID;
	BYTE	flag;
	BYTE	timer;
	BYTE	maxtime;
	BYTE	alpha;
};

#endif