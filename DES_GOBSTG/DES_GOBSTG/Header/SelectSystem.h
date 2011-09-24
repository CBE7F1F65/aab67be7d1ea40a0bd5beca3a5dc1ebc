#ifndef _SELECTSYSTEM_H
#define _SELECTSYSTEM_H

#include "Selector.h"
#include "PushKey.h"

#define SELSYSTEMMAX		4
#define SELSYS_DEFAULTMAXTIME	8

class SelectSystem
{
public:
	SelectSystem();
	~SelectSystem();

	static void Init();
	static void ClearAll();
	static void RenderAll();
	static void Action();

	Selector * BuildSelector(BYTE ID, int siID, float cenx, float ceny,
		float hscale = 1, float vscale = 0,
		BYTE flag = SEL_NULL);
	void Clear();
	void Setup(BYTE pushid, int nselect, int select, BYTE playerindex=0, int keyminus=PUSHKEY_KEYNULL, int keyplus=PUSHKEY_KEYNULL, int keyok=PUSHKEY_KEYNULL, int keycancel=PUSHKEY_KEYNULL, int maxtime=SELSYS_DEFAULTMAXTIME);
	bool SetPageNumber(BYTE nPageNum, float fadebegin, float offset, int initshift=0, int shiftangle=9000);
	void SetSelectFrame(int siID, float x, float y);
	void SetAction(BYTE typeflag, float xadj, float yadj);
	int SetSelect(int select=-1);

	bool Confirm(BYTE pushid, int keyminus=PUSHKEY_KEYNULL, int keyplus=PUSHKEY_KEYNULL, int keyok=PUSHKEY_KEYNULL, int keycancel=PUSHKEY_KEYNULL, float cenx=M_CLIENT_CENTER_X, float ceny=M_CLIENT_CENTER_Y, bool settrue=false);

	void shift(int nshift);
	void action();
	void Render();

	Selector * GetPointer(int index);

	void matchSelect();

public:
	seladj	adj[SEL_STATEMAX];

	hgeSprite * spselectframe;
	float selectframex;
	float selectframey;

	int nselect;
	int select;

	int sellock;
	bool complete;
	bool plus;

	int nPageNum;
	float fadebegin;
	float offset;
	int shiftangle;
	int firstID;
	int lastID;

	bool confirminit;

	int keyplus;
	int keyminus;
	int keyok;
	int keycancel;
	BYTE pushid;

	BYTE playerindex;

	list<Selector>sel;

	static SelectSystem selsys[SELSYSTEMMAX];
};

#endif