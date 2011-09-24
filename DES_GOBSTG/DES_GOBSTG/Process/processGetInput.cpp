#include "../Header/Process.h"
#include "../Header/GameInput.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/Player.h"

void Process::SyncInput()
{
	GameInput::SyncControlInput();
}

void Process::SetInputSwap()
{
	if (matchmode == M_MATCHMODE_C2P)
	{
		GameInput::SwapInput(true);
	}
	else
	{
		GameInput::SwapInput(false);
	}
}

int Process::getInput()
{
	GameInput::UpdateInput(state==STATE_START);
	
#if defined __IPHONE
	
#define M_FRONTBUTTON_AREA	24
	SpriteItemManager::FrontTouchButtonHide();
	
	if (state != STATE_START) {
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++) {
			FrontTouchButton * ftb;
			float xbase = i?(SCREEN_HEIGHT - 24):(24); 
			float xdownbase = i?(SCREEN_HEIGHT/2+80):(80);
			
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_UP);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = xbase;
				ftb->y = SCREEN_WIDTH / 2 - 64;
				ftb->xrange = M_FRONTBUTTON_AREA;
				ftb->yrange = M_FRONTBUTTON_AREA;
			}
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_DOWN);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = xbase;
				ftb->y = SCREEN_WIDTH / 2;
				ftb->xrange = M_FRONTBUTTON_AREA;
				ftb->yrange = M_FRONTBUTTON_AREA;
			}
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_OK);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = xbase;
				ftb->y = SCREEN_WIDTH / 2 + 64;
				ftb->xrange = M_FRONTBUTTON_AREA;
				ftb->yrange = M_FRONTBUTTON_AREA;
			}
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_CANCEL);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = xbase;
				ftb->y = SCREEN_WIDTH / 2 + 128;
				ftb->xrange = M_FRONTBUTTON_AREA;
				ftb->yrange = M_FRONTBUTTON_AREA;
			}
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_LEFT);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = xdownbase;
				ftb->y = SCREEN_WIDTH / 2 + 128;
				ftb->xrange = M_FRONTBUTTON_AREA;
				ftb->yrange = M_FRONTBUTTON_AREA;
			}
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_RIGHT);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = xdownbase + 64;
				ftb->y = SCREEN_WIDTH / 2 + 128;
				ftb->xrange = M_FRONTBUTTON_AREA;
				ftb->yrange = M_FRONTBUTTON_AREA;
			}
		}
	}
	else {
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++) {
			FrontTouchButton * ftb;
			float xbase = i?(SCREEN_HEIGHT-24):(24); 
			
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_PAUSE);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = xbase;
				ftb->y = 32;
				ftb->xrange = M_FRONTBUTTON_AREA;
				ftb->yrange = M_FRONTBUTTON_AREA;
			}
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_SHOOT);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = xbase;
				ftb->y = SCREEN_WIDTH / 2 - 48;
				ftb->xrange = M_FRONTBUTTON_AREA*1.2f;
				ftb->yrange = M_FRONTBUTTON_AREA*1.5f;
			}
			
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_CHARGE);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = -M_FRONTBUTTON_AREA*2;
				ftb->y = SCREEN_WIDTH / 2 - 16;
				ftb->xrange = 0;
				ftb->yrange = 0;
			}
			
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_DRAIN);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = -M_FRONTBUTTON_AREA*2;
				ftb->y = SCREEN_WIDTH / 2 + 8;
				ftb->xrange = 0;
				ftb->yrange = 0;
			}
			
			
			ftb = SpriteItemManager::GetFrontTouchButton(i, FTBUTTON_QUICK);
			if (!ftb->flag) {
				ftb->flag = FRONTTOUCH_NORMAL;
				ftb->x = xbase;
				ftb->y = SCREEN_WIDTH / 2 + 24;
				ftb->xrange = M_FRONTBUTTON_AREA*1.2f;
				ftb->yrange = M_FRONTBUTTON_AREA*1.5f;
			}
		}
	}
	
#endif
	
#if defined __IPHONE
	
	
#define M_PADSQUARE_LEFT_0	(0)
#define M_PADSQUARE_RIGHT_0	(SCREEN_HEIGHT/2)
#define M_PADSQUARE_LEFT_1	(M_PADSQUARE_RIGHT_0)
#define M_PADSQUARE_RIGHT_1	(SCREEN_HEIGHT)
#define M_PADSQUARE_LEFT_(playerindex)	((playerindex)?(M_PADSQUARE_LEFT_1):(M_PADSQUARE_LEFT_0))
#define M_PADSQUARE_RIGHT_(playerindex)	((playerindex)?(M_PADSQUARE_RIGHT_1):(M_PADSQUARE_RIGHT_0))
#define M_PADSQUARE_NOCONTROL_LEFT_0	(0)
#define M_PADSQUARE_NOCONTROL_RIGHT_0	(SCREEN_HEIGHT/2)
#define M_PADSQUARE_NOCONTROL_LEFT_1	(M_PADSQUARE_RIGHT_0)
#define M_PADSQUARE_NOCONTROL_RIGHT_1	(SCREEN_HEIGHT)
#define M_PADSQUARE_NOCONTROL_LEFT_(playerindex)	((playerindex)?(M_PADSQUARE_NOCONTROL_LEFT_1):(M_PADSQUARE_NOCONTROL_LEFT_0))
#define M_PADSQUARE_NOCONTROL_RIGHT_(playerindex)	((playerindex)?(M_PADSQUARE_NOCONTROL_RIGHT_1):(M_PADSQUARE_NOCONTROL_RIGHT_0))
	
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++) {
		bool tapChanged = false;
		for (int j=0; j<FTBUTTON_MAX; j++) {
			
			
			if (SpriteItemManager::ftbutton[i][j].flag) {
				float ftbx = SpriteItemManager::ftbutton[i][j].x;
				float ftby = SpriteItemManager::ftbutton[i][j].y;
				float ftbxrange = SpriteItemManager::ftbutton[i][j].xrange;
				float ftbyrange = SpriteItemManager::ftbutton[i][j].yrange;
				for (int k=0; k<TOUCHPOINT_MAX; k++) {
					
					bool tocontinue = false;
					for (int l=0; l<M_PL_MATCHMAXPLAYER; l++) {
						if (k == touchMoveID[l]) {
							tocontinue = true;
							break;
						}
					}
					if (tocontinue) {
						continue;
					}
					
					if (touchinfo[k].touched/* && !touchinfo[k].toupdate*/) {
						if (fabsf(ftbx - touchinfo[k].x) < ftbxrange && fabsf(ftby - touchinfo[k].y) < ftbyrange) {
							switch (j) {
								case FTBUTTON_LEFT:
									GameInput::SetKey(i, KSI_LEFT, true);
									break;
								case FTBUTTON_RIGHT:
									GameInput::SetKey(i, KSI_RIGHT, true);
									break;
								case FTBUTTON_UP:
									GameInput::SetKey(i, KSI_UP, true);
									break;
								case FTBUTTON_DOWN:
									GameInput::SetKey(i, KSI_DOWN, true);
									break;
								case FTBUTTON_OK:
									if (!touchinfo[k].toupdate) {
										GameInput::SetKey(i, KSI_FIRE, true);
									}
									break;
								case FTBUTTON_CANCEL:
									if (!touchinfo[k].toupdate) {
										GameInput::SetKey(i, KSI_QUICK, true);
									}
									break;
								case FTBUTTON_PAUSE:
									if (!touchinfo[k].toupdate) {
										for (int l=0; l<M_PL_MATCHMAXPLAYER; l++) {
											GameInput::SetKey(l, KSI_PAUSE, true);
										}
									}
									break;
								case FTBUTTON_SHOOT:
//									GameInput::SetKey(i, KSI_FIRE, true);
									if (!touchinfo[k].toupdate) {
										shootTriger[i] = !shootTriger[i];
									}
									break;
								case FTBUTTON_CHARGE:
									GameInput::SetKey(i, KSI_FIRE, true);
									break;
								case FTBUTTON_DRAIN:
//									GameInput::SetKey(i, KSI_DRAIN, true);
									if (!touchinfo[k].toupdate) {
										drainTriger[i] = !drainTriger[i];
									}
									break;
								case FTBUTTON_QUICK:
									GameInput::SetKey(i, KSI_QUICK, true);
									break;
							}
							touchinfo[k].toupdate = true;
						}
						
						else if (j == FTBUTTON_CHARGE && touchMoveID[i] != 0xff && touchMoveID[i] != k &&
								 (matchmode == M_MATCHMODE_P2C || matchmode == M_MATCHMODE_C2P || touchinfo[k].initx >= M_PADSQUARE_NOCONTROL_LEFT_(i) && touchinfo[k].initx <= M_PADSQUARE_NOCONTROL_RIGHT_(i))){
							tapTimer[i]++;
							tapChanged = true;
							GameInput::SetKey(i, KSI_FIRE, true);
						}

					}
				}
			}
		}
		if (!tapChanged) {
			if (tapTimer[i] && tapTimer[i] < PLAYER_SHOOTPUSHOVER) {
				drainTriger[i] = !drainTriger[i];
			}
			tapTimer[i] = 0;
		}
		if (state == STATE_START) {
			if (shootTriger[i] && (gametime % 2)) {
				GameInput::SetKey(i, KSI_FIRE, true);
			}
			if (drainTriger[i]) {
				GameInput::SetKey(i, KSI_DRAIN, true);
			}
		}
	}
	
	
	
	ZeroMemory(touchdirectmove, sizeof(TouchDirectMove)*M_PL_MATCHMAXPLAYER);
	for (int i=0; i<TOUCHPOINT_MAX; i++) {
		if (touchinfo[i].touched) {
			if (!touchinfo[i].toupdate) {
				if (state == STATE_START) {
					
					for (int j=0; j<M_PL_MATCHMAXPLAYER; j++) {
						int k = j;
						if (GameInput::swapinput) {
							k = 1-j;
						}
												
						if (touchMoveID[k] == 0xff) {
							
							bool used = false;
							for (int l=0; l<M_PL_MATCHMAXPLAYER; l++) {
								if (i == touchMoveID[l]) {
									used = true;
									break;
								}
							}
							if (!used) {
								if (touchinfo[i].x>=M_PADSQUARE_LEFT_(j) && touchinfo[i].x<=M_PADSQUARE_RIGHT_(j) || matchmode == M_MATCHMODE_P2C || matchmode == M_MATCHMODE_C2P){
									if (!(matchmode == M_MATCHMODE_P2C && k != 0 || matchmode == M_MATCHMODE_C2P && k != 1)) {
										touchMoveID[k] = i;
									}
								}
							}
							
						}
						if (i == touchMoveID[k]) {
							float scaleval = M_CLIENT_HEIGHT / (SCREEN_WIDTH*screenscale)*touchmovescale;
							touchdirectmove[k].x = (touchinfo[i].x-touchinfo[i].lastx) * scaleval;
							touchdirectmove[k].y = (touchinfo[i].y-touchinfo[i].lasty) * scaleval;
							break;
						}
					}
					touchinfo[i].toupdate = true;
				}
			}
		}
	}
#endif
	
	if (replaymode && !replayend && (state == STATE_START || state == STATE_CLEAR))
	{
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			GameInput::SetKey(i, KSI_UP, false);
			GameInput::SetKey(i, KSI_DOWN, false);
			GameInput::SetKey(i, KSI_LEFT, false);
			GameInput::SetKey(i, KSI_RIGHT, false);
			GameInput::SetKey(i, KSI_FIRE, false);
			GameInput::SetKey(i, KSI_QUICK, false);
			GameInput::SetKey(i, KSI_DRAIN, false);
			GameInput::SetKey(i, KSI_SLOW, false);
		}
	}

	if (state != STATE_START && state != STATE_PLAYER_SELECT)
	{
		GameInput::SyncForActiveInput();
	}

	return PGO;
}