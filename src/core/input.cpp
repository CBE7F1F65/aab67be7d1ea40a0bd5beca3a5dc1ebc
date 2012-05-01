/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: input
*/

/************************************************************************/
/* This define is added by h5nc (h5nc@yahoo.com.cn)                     */
/************************************************************************/
#define INITGUID

#include "hge_impl.h"

#ifdef __PSP
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#endif // __PSP

/************************************************************************/
/* These header files are added by h5nc (h5nc@yahoo.com.cn)             */
/************************************************************************/
//#include <objbase.h>

#ifdef __WIN32
GUID HGE_Impl::joyGuid[DIJOY_MAXDEVICE];
#endif

char *KeyNames[] =
{
 "?",
 "Left Mouse Button", "Right Mouse Button", "?", "Middle Mouse Button",
 "?", "?", "?", "Backspace", "Tab", "?", "?", "?", "Enter", "?", "?",
 "Shift", "Ctrl", "Alt", "Pause", "Caps Lock", "?", "?", "?", "?", "?", "?",
 "Escape", "?", "?", "?", "?",
 "Space", "Page Up", "Page Down", "End", "Home",
 "Left Arrow", "Up Arrow", "Right Arrow", "Down Arrow",
 "?", "?", "?", "?", "Insert", "Delete", "?",
 "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
 "?", "?", "?", "?", "?", "?", "?",
 "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
 "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
 "Left Win", "Right Win", "Application", "?", "?",
 "NumPad 0", "NumPad 1", "NumPad 2", "NumPad 3", "NumPad 4",
 "NumPad 5", "NumPad 6", "NumPad 7", "NumPad 8", "NumPad 9",
 "Multiply", "Add", "?", "Subtract", "Decimal", "Divide",
 "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "Num Lock", "Scroll Lock",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "Semicolon", "Equals", "Comma", "Minus", "Period", "Slash", "Grave",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?",
 "Left bracket", "Backslash", "Right bracket", "Apostrophe",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?", "?", "?", "?", "?", "?", "?", "?",
 "?", "?", "?"
};


bool CALL HGE_Impl::Input_GetEvent(hgeInputEvent *event)
{
	CInputEventList *eptr;

	if(queue)
	{
		eptr=queue;
		memcpy(event, &eptr->event, sizeof(hgeInputEvent));
		queue=eptr->next;
		delete eptr;
		return true;
	}
	
	return false;
}

void CALL HGE_Impl::Input_GetMousePos(float *x, float *y)
{
	*x=Xpos; *y=Ypos;
}


void CALL HGE_Impl::Input_SetMousePos(float x, float y)
{
#ifdef __WIN32
	POINT pt;
	pt.x=(long)x; pt.y=(long)y;
	ClientToScreen(hwnd, &pt);

	SetCursorPos(pt.x,pt.y);
#endif
}

int CALL HGE_Impl::Input_GetMouseWheel()
{
	return Zpos;
}

bool CALL HGE_Impl::Input_IsMouseOver()
{
	return bMouseOver;
}

bool CALL HGE_Impl::Input_GetKeyState(int key)
{
	/************************************************************************/
	/* This condition is added by h5nc (h5nc@yahoo.com.cn)                  */
	/************************************************************************/
#ifdef __WIN32
	if(bActive)
		return ((GetKeyState(key) & 0x8000) != 0);
#endif
	return false;
}

bool CALL HGE_Impl::Input_KeyDown(int key)
{
	/************************************************************************/
	/* This condition is added by h5nc (h5nc@yahoo.com.cn)                  */
	/************************************************************************/
	if(bActive)
		return (keyz[key] & 1) != 0;
	return false;
}

bool CALL HGE_Impl::Input_KeyUp(int key)
{
	/************************************************************************/
	/* This condition is added by h5nc (h5nc@yahoo.com.cn)                  */
	/************************************************************************/
	if(bActive)
		return (keyz[key] & 2) != 0;
	return false;
}

char* CALL HGE_Impl::Input_GetKeyName(int key)
{
	return KeyNames[key];
}

int CALL HGE_Impl::Input_GetKey()
{
	return VKey;
}

int CALL HGE_Impl::Input_GetChar()
{
	return Char;
}


//////// Implementation ////////


void HGE_Impl::_InputInit()
{
#ifdef __WIN32
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(hwnd, &pt);
	Xpos = (float)pt.x;
	Ypos = (float)pt.y;
#else
	Xpos = 0;
	Ypos = 0;
#endif

	memset(&keyz, 0, sizeof(keyz));

	memset(touchesState, 0, sizeof(touchesState));
}

/************************************************************************/
/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
// begin
bool CALL HGE_Impl::Input_GetDIKey(int key, BYTE stateType)
{
	if(key >= 0 && key < 256)
	{
		switch(stateType)
		{
		case DIKEY_PRESSED:
			if(keyState[key])
				return true;
			break;
		case DIKEY_DOWN:
			if(keyState[key] && !lastKeyState[key])
				return true;
			break;
		case DIKEY_UP:
			if(!keyState[key] && lastKeyState[key])
				return true;
			break;
		default:
			return false;
		}
	}
	return false;
}

bool CALL HGE_Impl::Input_SetDIKey(int key, bool set)
{
	if(key >=0 && key < 256)
	{
		if(set)
			keyState[key] |= 1<<7;
		else
			keyState[key] = 0;
	}
	return true;
}

bool CALL HGE_Impl::Input_GetDIJoy(int joy, BYTE stateType /* = DIKEY_PRESSED */, int joydevice/* =0 */)
{
#ifdef __WIN32
	if(joy >=0 && joy < 32)
	{
		switch(stateType)
		{
		case DIKEY_PRESSED:
			if(joyState[joydevice].rgbButtons[joy])
				return true;
			break;
		case DIKEY_DOWN:
			if(joyState[joydevice].rgbButtons[joy] && !lastJoyState[joydevice].rgbButtons[joy])
				return true;
			break;
		case DIKEY_UP:
			if(!joyState[joydevice].rgbButtons[joy] && lastJoyState[joydevice].rgbButtons[joy])
				return true;
			break;
		default:
			return false;
		}
	}
	else
	{
		switch(joy)
		{
		case JOY_LEFT:
			switch(stateType)
			{
			case DIKEY_PRESSED:
				if(joyState[joydevice].lX < 0)
					return true;
				break;
			case DIKEY_DOWN:
				if(joyState[joydevice].lX < 0 && !(lastJoyState[joydevice].lX < 0))
					return true;
				break;
			case DIKEY_UP:
				if(!(joyState[joydevice].lX < 0) && lastJoyState[joydevice].lX < 0)
					return true;
				break;
			default:
				return false;
			}
			break;
		case JOY_RIGHT:
			switch(stateType)
			{
			case DIKEY_PRESSED:
				if(joyState[joydevice].lX > 0)
					return true;
				break;
			case DIKEY_DOWN:
				if(joyState[joydevice].lX > 0 && !(lastJoyState[joydevice].lX > 0))
					return true;
				break;
			case DIKEY_UP:
				if(!(joyState[joydevice].lX > 0) && lastJoyState[joydevice].lX > 0)
					return true;
				break;
			default:
				return false;
			}
			break;
		case JOY_UP:
			switch(stateType)
			{
			case DIKEY_PRESSED:
				if(joyState[joydevice].lY < 0)
					return true;
				break;
			case DIKEY_DOWN:
				if(joyState[joydevice].lY < 0 && !(lastJoyState[joydevice].lY < 0))
					return true;
				break;
			case DIKEY_UP:
				if(!(joyState[joydevice].lY < 0) && lastJoyState[joydevice].lY < 0)
					return true;
				break;
			default:
				return false;
			}
			break;
		case JOY_DOWN:
			switch(stateType)
			{
			case DIKEY_PRESSED:
				if(joyState[joydevice].lY > 0)
					return true;
				break;
			case DIKEY_DOWN:
				if(joyState[joydevice].lY > 0 && !(lastJoyState[joydevice].lY > 0))
					return true;
				break;
			case DIKEY_UP:
				if(!(joyState[joydevice].lY > 0) && lastJoyState[joydevice].lY > 0)
					return true;
				break;
			default:
				return false;
			}
			break;
		default:
			return false;
		}
	}
#endif
	return false;
}
// end

void HGE_Impl::_UpdateMouse()
{
#if defined __WIN32
	POINT	pt;
	RECT	rc;

	GetCursorPos(&pt);
	GetClientRect(hwnd, &rc);
	MapWindowPoints(hwnd, NULL, (LPPOINT)&rc, 2);

	if(bCaptured || (PtInRect(&rc, pt) && WindowFromPoint(pt)==hwnd))
		bMouseOver=true;
	else
		bMouseOver=false;
#elif defined __IPHONE
#endif
}

void HGE_Impl::_BuildEvent(int type, int key, int scan, int flags, int x, int y)
{
#ifdef __WIN32
	CInputEventList *last, *eptr=new CInputEventList;
	unsigned char kbstate[256];
	POINT pt;

	eptr->event.type=type;
	eptr->event.chr=0;
	pt.x=x; pt.y=y;

	GetKeyboardState(kbstate);
	if(type==INPUT_KEYDOWN)
	{
		if((flags & HGEINP_REPEAT) == 0) keyz[key] |= 1;
		ToAscii(key, scan, kbstate, (unsigned short *)&eptr->event.chr, 0);
	}
	if(type==INPUT_KEYUP)
	{
		keyz[key] |= 2;
		ToAscii(key, scan, kbstate, (unsigned short *)&eptr->event.chr, 0);
	}
	if(type==INPUT_MOUSEWHEEL)
	{
		eptr->event.key=0; eptr->event.wheel=key;
		ScreenToClient(hwnd,&pt);
	}
	else { eptr->event.key=key; eptr->event.wheel=0; }

	if(type==INPUT_MBUTTONDOWN)
	{
		keyz[key] |= 1;
		SetCapture(hwnd);
		bCaptured=true;
	}
	if(type==INPUT_MBUTTONUP)
	{
		keyz[key] |= 2;
		ReleaseCapture();
		Input_SetMousePos(Xpos, Ypos);
		pt.x=(int)Xpos; pt.y=(int)Ypos;
		bCaptured=false;
	}
	
	if(kbstate[VK_SHIFT] & 0x80) flags|=HGEINP_SHIFT;
	if(kbstate[VK_CONTROL] & 0x80) flags|=HGEINP_CTRL;
	if(kbstate[VK_MENU] & 0x80) flags|=HGEINP_ALT;
	if(kbstate[VK_CAPITAL] & 0x1) flags|=HGEINP_CAPSLOCK;
	if(kbstate[VK_SCROLL] & 0x1) flags|=HGEINP_SCROLLLOCK;
	if(kbstate[VK_NUMLOCK] & 0x1) flags|=HGEINP_NUMLOCK;
	eptr->event.flags=flags;

	if(pt.x==-1) { eptr->event.x=Xpos;eptr->event.y=Ypos; }
	else
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		float windoww = rect.right - rect.left;
		float windowh = rect.bottom - rect.top;

		if(pt.x<0) pt.x=0;
		if(pt.y<0) pt.y=0;
		if(pt.x>=windoww) pt.x=windoww-1;
		if(pt.y>=windowh) pt.y=windowh-1;

		eptr->event.x=(float)pt.x;
		eptr->event.y=(float)pt.y;
	}

	eptr->next=0; 

	if(!queue) queue=eptr;
	else
	{
		last=queue;
		while(last->next) last=last->next;
		last->next=eptr;
	}

	if(eptr->event.type==INPUT_KEYDOWN || eptr->event.type==INPUT_MBUTTONDOWN)
	{
		VKey=eptr->event.key;Char=eptr->event.chr;
	}
	else if(eptr->event.type==INPUT_MOUSEMOVE)
	{
		Xpos=eptr->event.x;Ypos=eptr->event.y;

	}
	else if(eptr->event.type==INPUT_MOUSEWHEEL)
	{
		Zpos+=eptr->event.wheel;
	}
#endif
}

void HGE_Impl::_ClearQueue()
{
	CInputEventList *nexteptr, *eptr=queue;
	
	memset(&keyz, 0, sizeof(keyz));
	
	while(eptr)
	{
		nexteptr=eptr->next;
		delete eptr;
		eptr=nexteptr;
	}

	queue=0; VKey=0; Char=0; Zpos=0;
}

/************************************************************************/
/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
// begin
#ifdef __WIN32
BOOL CALLBACK HGE_Impl::_EnumJoysticksCallback (const DIDEVICEINSTANCE * pdidInstance, VOID* pContext)
{
	int count = *(int*)pContext;
	if (count < DIJOY_MAXDEVICE)
	{
		joyGuid[count] = pdidInstance->guidInstance;
		count++;
		*(int *)pContext = count;
	}
	if (count >= DIJOY_MAXDEVICE)
	{
		*(int *)pContext = 0;
		return DIENUM_STOP;
	}

	return (DIENUM_CONTINUE);
}
#endif

LPDIRECTINPUT8 CALL HGE_Impl::Input_GetDevice()
{
#ifdef __WIN32
	return lpDInput;
#else
	return NULL;
#endif
}

int HGE_Impl::_DIInit()
{

	bool keyable = true;
	bool nojoy = true;
#if defined __WIN32
	lpDIKDevice = NULL;

	if (FAILED (DirectInput8Create (hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**) &lpDInput, NULL)))
	{
		keyable = false;
	}

	if (keyable && FAILED (lpDInput->CreateDevice(GUID_SysKeyboard, &lpDIKDevice, NULL)))
	{
		keyable = false;
	}
	if (keyable && FAILED (lpDIKDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		keyable = false;
	}
	if (keyable && FAILED (lpDIKDevice->SetCooperativeLevel (hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		keyable = false;
	}
	if(keyable && FAILED (lpDIKDevice->Acquire ()))
	{
		keyable = false;
	}

	int enumcount = 0;
	for (int i=0; i<DIJOY_MAXDEVICE; i++)
	{
		haveJoy[i] = true;
		lpDIJDevice[i] = NULL;
	}
	if (FAILED (lpDInput->EnumDevices (DI8DEVCLASS_GAMECTRL, _EnumJoysticksCallback, &enumcount, DIEDFL_ATTACHEDONLY)))
	{
		for (int i=0; i<DIJOY_MAXDEVICE; i++)
		{
			haveJoy[i] = false;
		}
	}
	for (int i=0; i<DIJOY_MAXDEVICE; i++)
	{
		if (haveJoy[i] && FAILED (lpDInput->CreateDevice(joyGuid[i], &lpDIJDevice[i], NULL)))
		{
			haveJoy[i] = false;
		}
		if (haveJoy[i] && FAILED (lpDIJDevice[i]->SetDataFormat(&c_dfDIJoystick)))
		{
			haveJoy[i] = false;
		}
		if (haveJoy[i] && FAILED (lpDIJDevice[i]->SetCooperativeLevel (hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		{
			haveJoy[i] = false;
		}

		if (haveJoy[i])
		{
			DIPROPRANGE joyRange;

			joyRange.lMin = -24;
			joyRange.lMax = 24;

			joyRange.diph.dwSize       = sizeof(DIPROPRANGE); 
			joyRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
			joyRange.diph.dwObj        = DIJOFS_X;
			joyRange.diph.dwHow        = DIPH_BYOFFSET;

			lpDIJDevice[i]->SetProperty(DIPROP_RANGE, &joyRange.diph);

			joyRange.lMin = -24;
			joyRange.lMax = 24;

			joyRange.diph.dwSize       = sizeof(DIPROPRANGE); 
			joyRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
			joyRange.diph.dwObj        = DIJOFS_Y;
			joyRange.diph.dwHow        = DIPH_BYOFFSET;

			lpDIJDevice[i]->SetProperty(DIPROP_RANGE,&joyRange.diph);

			DIPROPDWORD deadZone;

			deadZone.diph.dwSize       = sizeof(deadZone);
			deadZone.diph.dwHeaderSize = sizeof(deadZone.diph);
			deadZone.diph.dwObj        = DIJOFS_X;
			deadZone.diph.dwHow        = DIPH_BYOFFSET;
			deadZone.dwData            = 1000;

			lpDIJDevice[i]->SetProperty(DIPROP_DEADZONE, &deadZone.diph);

			deadZone.diph.dwSize       = sizeof(deadZone);
			deadZone.diph.dwHeaderSize = sizeof(deadZone.diph);
			deadZone.diph.dwObj        = DIJOFS_Y;
			deadZone.diph.dwHow        = DIPH_BYOFFSET;
			deadZone.dwData            = 1000;

			lpDIJDevice[i]->SetProperty(DIPROP_DEADZONE,&deadZone.diph);

			if (FAILED (lpDIJDevice[i]->Acquire()))
			{
				haveJoy[i] = false;
			}
		}
		if (haveJoy[i])
		{
			nojoy = false;
		}

	}

	for (int i=0; i<DIJOY_MAXDEVICE; i++)
	{
		for (int j=i; j<DIJOY_MAXDEVICE; j++)
		{
			if (haveJoy[j] && !haveJoy[i])
			{
				LPDIRECTINPUTDEVICE8 _lpDIJDevice;
				_lpDIJDevice = lpDIJDevice[i];
				lpDIJDevice[i] = lpDIJDevice[j];
				lpDIJDevice[j] = _lpDIJDevice;

				GUID _joyGuid;
				_joyGuid = joyGuid[i];
				joyGuid[i] = joyGuid[j];
				joyGuid[j] = _joyGuid;

				haveJoy[i] = !haveJoy[i];
				haveJoy[j] = !haveJoy[j];

				break;
			}
		}
	}
#elif defined __PSP
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
#elif defined __IPHONE
	
#endif

	return ((!nojoy)?0:ERROR_NOJOYSTICK) | (keyable?0:ERROR_NOKEYBOARD);
}

bool HGE_Impl::Input_HaveJoy(int joydevice)
{
#ifdef __WIN32
	return haveJoy[joydevice];
#else
	return false;
#endif
}

void HGE_Impl::_DIRelease()
{
#ifdef __WIN32
	if(lpDIKDevice != NULL)
	{
		lpDIKDevice->Unacquire();
		lpDIKDevice->Release();
		lpDIKDevice = NULL;
	}
	for (int i=0; i<DIJOY_MAXDEVICE; i++)
	{
		if(lpDIJDevice[i] != NULL)
		{
			lpDIJDevice[i]->Unacquire();
			lpDIJDevice[i]->Release();
			lpDIJDevice[i] = NULL;
		}
	}
#endif
}

int HGE_Impl::_DIUpdate()
{
	bool keyable = true;

	memcpy(lastKeyState, keyState, sizeof(keyState));
#ifdef __WIN32
	if(lpDIKDevice == NULL)
	{
		_DIRelease();
		_DIInit();
		if(lpDIKDevice == NULL)
		{
			keyable = false;
//			return ERROR_NOKEYBOARD;
		}
	}
#endif
	if(keyable)
	{
#ifdef __WIN32
		HRESULT hRet = lpDIKDevice->GetDeviceState(256, keyState);
		if(FAILED(hRet)/* && hRet == DIERR_INPUTLOST*/)
		{
			if(FAILED(lpDIKDevice->Acquire()))
			{
				_DIRelease();
				_DIInit();
				if(FAILED(lpDIKDevice->Acquire()))
					keyable = false;
			}
			if(keyable && FAILED(lpDIKDevice->GetDeviceState(256, keyState)))
				keyable = false;
		}
		if(hwnd != GetActiveWindow())
		{
			ZeroMemory(&keyState, sizeof(keyState));
		}
#else
		/************************************************************************/
		/* TODO                                                                 */
		/************************************************************************/
		ZeroMemory(&keyState, sizeof(keyState));

#if defined __PSP
		SceCtrlData pad;
		sceCtrlPeekBufferPositive(&pad, 1);
		//Analog pad.Lx, Pad.Ly
		for (int i=0; i<32; i++)
		{
			if (pad.Buttons & (1<<i))
			{
				keyState[i] = 1<<7;
			}
		}
#elif defined __IPHONE
#endif // __PSP

#endif // __WIN32
	}

	bool nojoy = true;
#ifdef __WIN32
	for (int i=0; i<DIJOY_MAXDEVICE; i++)
	{
		lastJoyState[i] = joyState[i];
		if(haveJoy[i])
		{
			if(lpDIJDevice[i] == NULL)
			{
				_DIRelease();
				_DIInit();
				if(lpDIJDevice[i] == NULL)
				{
					haveJoy[i] = false;
				}
			}
			if(haveJoy[i] && FAILED(lpDIJDevice[i]->Poll()))
			{
				if(FAILED(lpDIJDevice[i]->Acquire()))
				{
					_DIRelease();
					_DIInit();
					if(FAILED(lpDIJDevice[i]->Acquire()))
					{
						haveJoy[i] = false;
					}
				}
			}
			if(haveJoy[i] && FAILED(lpDIJDevice[i]->GetDeviceState(sizeof(DIJOYSTATE), &joyState[i])))
			{
				haveJoy[i] = false;
			}
		}
		else
		{
			haveJoy[i] = false;
		}

		if (haveJoy[i])
		{
			nojoy = false;
		}
	}
#endif

	return ((!nojoy)?0:ERROR_NOJOYSTICK) | (keyable?0:ERROR_NOKEYBOARD);
}

void HGE_Impl::_TouchRelease()
{
}

void HGE_Impl::_TouchInit()
{
	memset(touchesState, 0, sizeof(touchesState));
}

void HGE_Impl::_TouchUpdate()
{
	for (int i=0; i<TOUCH_TOUCHMAX; i++)
	{
		if (touchesState[i].touching)
		{
			touchesState[i].touchtimer++;
			touchesState[i].notouchtimer = 0;
		}
		else
		{
			touchesState[i].notouchtimer++;
			touchesState[i].touchtimer = 0;
		}
		touchesState[i].lasttouching = touchesState[i].touching;

		touchesState[i].touching = false;
	}
}

bool HGE_Impl::Input_IsTouchDown(int touch)
{
	if (touch < 0 || touch >= TOUCH_TOUCHMAX)
	{
		return false;
	}
	if (touchesState[touch].lasttouching == false && touchesState[touch].touching == true)
	{
		return true;
	}
	return false;
}

bool HGE_Impl::Input_IsTouchOn(int touch)
{
	if (touch < 0 || touch >= TOUCH_TOUCHMAX)
	{
		return false;
	}
	if (touchesState[touch].touching == true)
	{
		return true;
	}
	return false;
}

bool HGE_Impl::Input_IsTouchUp(int touch)
{
	if (touch < 0 || touch >= TOUCH_TOUCHMAX)
	{
		return false;
	}
	if (touchesState[touch].lasttouching == true && touchesState[touch].touching == false)
	{
		return true;
	}
	return false;
}

void HGE_Impl::Input_GetTouchPos(int touch, float *x, float *y)
{
	if (touch < 0 || touch >= TOUCH_TOUCHMAX || !x || !y)
	{
		return;
	}
	*x = touchesState[touch].x;
	*y = touchesState[touch].y;
}

void HGE_Impl::Input_GetLastTouchPos(int touch, float *x, float *y)
{
	if (touch < 0 || touch >= TOUCH_TOUCHMAX || !x || !y)
	{
		return;
	}
	*x = touchesState[touch].lastx;
	*y = touchesState[touch].lasty;
}

void HGE_Impl::Input_GetFirstTouchPos(int touch, float *x, float *y)
{
	if (touch < 0 || touch >= TOUCH_TOUCHMAX || !x || !y)
	{
		return;
	}
	*x = touchesState[touch].firstx;
	*y = touchesState[touch].firsty;
}

int HGE_Impl::Input_GetTouchDuration(int touch)
{
	if (touch < 0 || touch >= TOUCH_TOUCHMAX)
	{
		return 0;
	}
	return touchesState[touch].touchtimer;
}

int HGE_Impl::Input_GetNoTouchDuration(int touch)
{
	if (touch < 0 || touch >= TOUCH_TOUCHMAX)
	{
		return 0;
	}
	return touchesState[touch].notouchtimer;
}

void HGE_Impl::Input_SetTouchPos(int touch, float x, float y)
{
	if (touch < 0 || touch >= TOUCH_TOUCHMAX)
	{
		return;
	}

	touchesState[touch].touching = true;
	if (!touchesState[touch].lasttouching)
	{
		touchesState[touch].firstx = x;
		touchesState[touch].firsty = y;
		touchesState[touch].lastx = x;
		touchesState[touch].lasty = y;
	}
	else
	{
		touchesState[touch].lastx = touchesState[touch].x;
		touchesState[touch].lasty = touchesState[touch].y;
	}
	touchesState[touch].x = x;
	touchesState[touch].y = y;
}


// end