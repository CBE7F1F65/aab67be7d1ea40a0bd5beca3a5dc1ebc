#include "../header/Chat.h"
#include "../header/BGLayer.h"
#include "../header/Player.h"
#include "../header/Bullet.h"
#include "../header/Fontsys.h"
#include "../header/Main.h"
#include "../header/Process.h"
#include "../header/SpriteItemManager.h"
#include "../header/FrontDisplay.h"
#include "../header/FrontDisplayName.h"
#include "../header/Enemy.h"
#include "../header/EventZone.h"
#include "../header/GameInput.h"

Chat Chat::chatitem;

#define _CHAT_LINECHARACTER	34

Chat::Chat()
{
	Clear();
	for (int i=0; i<CHATTERMAX; i++)
	{
		chatter[i] = NULL;
	}
}

Chat::~Chat()
{
}

bool Chat::IsChatting()
{
	return chatting;
}

void Chat::Clear()
{
	col = 0x00000000;
	pushtimer = 0xff;
	chatting = false;
	chatinit = false;
	timer = 0;
	chati = 0;
}

void Chat::Init()
{
	Release();
	leftsprite = SpriteItemManager::CreateNullSprite();
	rightsprite = SpriteItemManager::CreateNullSprite();
	textbox = SpriteItemManager::CreateSpriteByName(SI_FRONT_TEXT);
}

void Chat::Release()
{
	Clear();
	for (int i=0; i<CHATTERMAX; i++)
	{
		if (chatter[i])
		{
			SpriteItemManager::FreeSprite(&chatter[i]);
		}
	}
}

void Chat::Render()
{
	if (!IsChatting())
	{
		return;
	}
	for(int i = 0; i < CHATTERMAX-1; i++)
	{
		if (chatter[i])
		{
			SpriteItemManager::RenderSpriteEx(chatter[i], x[i], y[i], 0, 0.8f);
		}
	}
	if (textbox)
	{
		SpriteItemManager::RenderSpriteEx(textbox, x[CHATTER_TEXTBOX], y[CHATTER_TEXTBOX], ARC(9000), 80.0f/(textbox->GetWidth()), 352.0f/(textbox->GetHeight()));
	}
	fschat.SetColor(0xffffffff, 0xffffffff, col, col);
	fschat.Render(M_CLIENT_CENTER_X-160, M_CLIENT_CENTER_Y+148, FONTSYS_DEFAULT_SHADOW);
}

bool Chat::chat(BYTE ID, BYTE chatsprite, const char * _text)
{
	timer++;
	if(!chatting)
	{
		timer = 0;
		return true;
	}

	if(GameInput::GetKey(0, KSI_FIRE))
	{
		if(pushtimer < M_PUSH_FIRST)
			pushtimer++;
		else if(pushtimer == M_PUSH_FIRST)
			pushtimer = M_PUSH_FIRST - M_PUSH_SKIP;
	}
	else
	{
		pushtimer = 0;
	}

	if(GameInput::GetKey(0, KSI_FIRE, DIKEY_DOWN) || pushtimer == M_PUSH_FIRST || timer == M_NOPUSH_SKIP)
	{
		chatinit = false;
		timer = 0;
		chati++;
		return true;
	}

	if(chatinit)
	{
		return false;
	}

	if (timer == 1)
	{
		if(chatsprite & CHATSPRITE_LEFT)
		{
			leftsprite->SetColor(0xffffffff);
			rightsprite->SetColor(0x80ffffff);
			textbox->SetColor(0xff3333ff);
			SpriteItemManager::ptFace(ID, leftsprite);
//			leftsprite->SetFlip(chatsprite & CHATSPRITE_LEFTFLIP, false);
			SpriteItemManager::SetSpriteFlip(leftsprite, chatsprite & CHATSPRITE_LEFTFLIP);
		}
		else
		{
			leftsprite->SetColor(0x80ffffff);
			rightsprite->SetColor(0xffffffff);
			textbox->SetColor(0xffff3333);
			SpriteItemManager::ptFace(ID, rightsprite);
//			rightsprite->SetFlip(chatsprite & CHATSPRITE_RIGHTFLIP, false);
			SpriteItemManager::SetSpriteFlip(rightsprite, chatsprite & CHATSPRITE_RIGHTFLIP);
		}
		int line = 0;
		int tlength = strlen(_text);
		for(WORD i=0;i<tlength+1;i++)
		{
			if(i!=0 && !(i%_CHAT_LINECHARACTER) && i < tlength-1)
			{
				text[i+line] = '\n';
				line++;
			}
			text[i+line] = _text[i];
		}
		fschat.SignUp(text, 0.625f);
		if(chatsprite & CHATSPRITE_LEFT)
		{
			col = 0xff6699ff;
		}
		else
		{
			col = 0xffff6666;
		}
	}
	else if (timer == 16)
	{
		chatinit = true;
	}
	else
	{
		float timerscale = timer/16.0f;
		if (chatsprite & CHATSPRITE_LEFT)
		{
			x[CHATTER_LEFT] = INTER(x[CHATTER_LEFT], M_GAMESQUARE_CENTER_X_(0)+40, timerscale);
			x[CHATTER_RIGHT] = INTER(x[CHATTER_RIGHT], M_GAMESQUARE_CENTER_X_(1), timerscale);
		}
		else
		{
			x[CHATTER_LEFT] = INTER(x[CHATTER_LEFT], M_GAMESQUARE_CENTER_X_(0), timerscale);
			x[CHATTER_RIGHT] = INTER(x[CHATTER_RIGHT], M_GAMESQUARE_CENTER_X_(1)-40, timerscale);
		}
	}
	return false;
}

bool Chat::chatOn(BYTE leftID, BYTE rightID, BYTE chatsprite)
{
	timer++;

	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		Player::p[i].SetInfi(PLAYERINFI_CHAT);
	}
	chatinit = false;
	
	if(timer == 1)
	{
		pushtimer = 0xff;

		strcpy(text, "");
		fschat.SignUp(text, 0.625f);
		
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_CHECKTYPE_CIRCLE, i, Player::p[i].x, Player::p[i].y);
//			Bullet::IzeBuild(i, BULLETIZE_FAITH, Player::p[i].x, Player::p[i].y);
		}

		chatting = true;
		if (leftID != 0xff)
		{
			SpriteItemManager::ptFace(leftID, leftsprite);
//			leftsprite->SetFlip(chatsprite & CHATSPRITE_LEFTFLIP, false);
			SpriteItemManager::SetSpriteFlip(leftsprite, chatsprite & CHATSPRITE_LEFTFLIP);
		}
		else
		{
			SpriteItemManager::ptFace(-1, leftsprite);
		}
		if (rightID != 0xff)
		{
			SpriteItemManager::ptFace(rightID, rightsprite);
//			rightsprite->SetFlip(chatsprite & CHATSPRITE_RIGHTFLIP, false);
			SpriteItemManager::SetSpriteFlip(rightsprite, chatsprite & CHATSPRITE_RIGHTFLIP);
		}
		else
		{
			SpriteItemManager::ptFace(-1, rightsprite);
		}
		if (chatsprite & CHATSPRITE_LEFT)
		{
			textbox->SetColor(0xff3333ff);
		}
		else
		{
			textbox->SetColor(0xffff3333);
		}
		chati = 0;
	}
	if(timer <= 36)
	{
		float timerscale = timer / 36.0f;
		x[CHATTER_LEFT] = INTER(M_CLIENT_LEFT-192, M_GAMESQUARE_CENTER_X_(0), timerscale);
		y[CHATTER_LEFT] = INTER(M_CLIENT_BOTTOM, M_CLIENT_CENTER_Y+108, timerscale);
		x[CHATTER_RIGHT] = INTER(M_CLIENT_RIGHT+192, M_GAMESQUARE_CENTER_X_(1), timerscale);
		y[CHATTER_RIGHT] = INTER(M_CLIENT_BOTTOM, M_CLIENT_CENTER_Y+108, timerscale);

		if(chatsprite & CHATSPRITE_LEFT)
		{
			rightsprite->SetColor(0x80ffffff);
		}
		else
		{
			leftsprite->SetColor(0x80ffffff);
		}
		x[CHATTER_TEXTBOX] = M_CLIENT_CENTER_X;
		y[CHATTER_TEXTBOX] = M_CLIENT_BOTTOM+72-timer*4;
	}
	else
	{
		/*
		if (leftID != 0xff)
		{
			x[CHATTER_LEFTNAME] = M_GAMESQUARE_CENTER_X_(0);
			y[CHATTER_LEFTNAME] = M_CLIENT_CENTER_Y+108;
		}
		if (rightID != 0xff)
		{
			x[CHATTER_RIGHTNAME] = M_GAMESQUARE_CENTER_X_(1);
			y[CHATTER_RIGHTNAME] = M_CLIENT_CENTER_Y+108;
		}
		match(CHATTER_LEFTNAME, leftsprite);
		match(CHATTER_RIGHTNAME, rightsprite);
		*/
		timer = 0;
		chati = 1;
		return true;
	}
	return false;
}

bool Chat::chatOff()
{
	timer++;

	if(timer <= 32)
	{
		x[CHATTER_LEFT] -= timer * 15;
		x[CHATTER_RIGHT] += timer * 15;
		y[CHATTER_TEXTBOX] += timer * 4;
	}
	else
	{
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			Player::p[i].SetInfi(PLAYERINFI_CHAT, PLAYER_INFIUNSET);
		}
		timer = 0;
		chatting = false;
		chati = 0;
		return true;
	}
	return false;
}