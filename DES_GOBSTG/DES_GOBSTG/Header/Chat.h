#ifndef _CHAT_H
#define _CHAT_H

#include "MainDependency.h"
#include "Const.h"
#include "BGLayer.h"
#include "Fontsys.h"

#define CHATTERMAX	3

#define CHATTER_LEFT		0
#define CHATTER_RIGHT		1
#define CHATTER_TEXTBOX		2

#define CHATSPRITE_LEFT			0x01
#define CHATSPRITE_LEFTFLIP		0x02
#define CHATSPRITE_RIGHT		0x10
#define CHATSPRITE_RIGHTFLIP	0x20

class Chat
{
public:
	Chat();
	~Chat();

	void Init();
	void Release();
	void Clear();
	void Render();

	bool IsChatting();
	bool chatOn(BYTE leftID, BYTE rightID, BYTE chatsprite);
	bool chatOff();

	bool chat(BYTE ID, BYTE chatsprite, const char * text);

public:

	char text[M_STRMAX];
	union{
		struct{
			hgeSprite * leftsprite;
			hgeSprite * rightsprite;
			hgeSprite * textbox;
		};
		hgeSprite * chatter[CHATTERMAX];
	};
	float x[CHATTERMAX];
	float y[CHATTERMAX];

	DWORD col;

	BYTE pushtimer;

	bool chatinit;
	bool chatting;
	BYTE timer;
	BYTE chati;
	Fontsys fschat;

	static Chat chatitem;
};

#endif