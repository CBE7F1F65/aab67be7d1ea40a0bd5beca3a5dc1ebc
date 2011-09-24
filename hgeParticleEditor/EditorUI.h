#ifndef _EDITORUI_H
#define _EDITORUI_H

#include "../DES_GOBSTG/DES_GOBSTG/header/MainDependency.h"
#include "../include/hgeEffectSystem.h"


#define UIEDITMODE_EB	1
#define UIEDITMODE_EE	2
#define UIEDITMODE_EA	4

#define UIEDITINPUT_MAX	10

class EditorUI{
public:
	EditorUI();
	~EditorUI();

	void Update();
	void Render();
	bool UpdateInput();
	bool UpdateValue();

	void SetupInit();
	void SetupEB(bool updateLsit = false);
	void SetupEE(bool updateList = false);
	void SetupEA();
	bool EditEB();
	bool EditEE();
	bool EditEA();
	void PageUp();
	void PageDown();
	void Refresh();
	void ChangePanel(BYTE info);
	bool Add();
	bool Delete();
	void Operate();
	bool Save();
	bool isListNull();
	bool ChangeBGTex(int texnum = -1);

public:
	DWORD timer;

	float mx;
	float my;

	hgeInputEvent inputevent;
	bool clickdown;
	bool clickup;
	int wheel;

	float zpos;
	int nlives;
	int nobj;

	int oper;
	char * input;
	char * title;
	char * addinfo;

	BYTE pushtimer;

	BYTE editmode;

	int ebnum;
	CEmitterList * emitterItem;
	CAffectorList * affectorItem;
	hgeEffectEmitter * emitter;
	hgeEffectAffector * affector;

	float fval;
	int ival;
	DWORD uval;
};

extern EditorUI ui;
extern HGE * hge;

#endif