/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: timer
*/


#include "hge_impl.h"

#ifdef __PSP
#include <psprtc.h>
#endif // __PSP

#ifdef __IPHONE
#include <mach/mach_time.h>
#endif

LONGLONG CALL HGE_Impl::Timer_GetCurrentSystemTime()
{
#ifdef __WIN32
	LARGE_INTEGER Counter;
	QueryPerformanceCounter(&Counter);
	return Counter.QuadPart;
#else

#ifdef __PSP
	u64 ticks;
	sceRtcGetCurrentTick(&ticks);
	return ticks;
#endif // __PSP
	
#ifdef __IPHONE
	return mach_absolute_time();
#endif;

#endif // __WIN32
}

LONGLONG CALL HGE_Impl::Timer_GetPerformanceFrequency()
{
#ifdef __WIN32
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	return Frequency.QuadPart;
#else

#ifdef __PSP
	return sceRtcGetTickResolution();
#endif // __PSP
	
#ifdef __IPHONE
	mach_timebase_info_data_t info;
	mach_timebase_info(&info);
	return info.denom*1000000000/info.numer;
#endif;

#endif // __WIN32
}

void CALL HGE_Impl::Timer_GetSystemTime(WORD *wYear, WORD *wMonth, WORD *wDayOfWeek, WORD *wDay, WORD *wHour, WORD *wMinute, WORD *wSecond, WORD *wMilliseconds)
{
#if defined __WIN32
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	if (wYear)
	{
		*wYear = systime.wYear;
	}
	if (wMonth)
	{
		*wMonth = systime.wMonth;
	}
	if (wDayOfWeek)
	{
		*wDayOfWeek = systime.wDayOfWeek;
	}
	if (wDay)
	{
		*wDay = systime.wDay;
	}
	if (wHour)
	{
		*wHour = systime.wHour;
	}
	if (wMinute)
	{
		*wMinute = systime.wMinute;
	}
	if (wSecond)
	{
		*wSecond = systime.wSecond;
	}
	if (wMilliseconds)
	{
		*wMilliseconds = systime.wMilliseconds;
	}
#elif defined __PSP
	pspTime psptime;
	u64 filetime;
	sceRtcGetWin32FileTime(&psptime, &filetime);
	if (wYear)
	{
		*wYear = psptime.year;
	}
	if (wMonth)
	{
		*wMonth = psptime.month;
	}
	if (wDayOfWeek)
	{
		*wDayOfWeek = 0;
	}
	if (wDay)
	{
		*wDay = psptime.day;
	}
	if (wHour)
	{
		*wHour = psptime.hour;
	}
	if (wMinute)
	{
		*wMinute = psptime.minutes;
	}
	if (wSecond)
	{
		*wSecond = psptime.seconds;
	}
	if (wMilliseconds)
	{
		*wMilliseconds = psptime.microseconds;
	}
#elif defined __IPHONE
	
	if (wYear)
	{
		*wYear = 0;
	}
	if (wMonth)
	{
		*wMonth = 0;
	}
	if (wDayOfWeek)
	{
		*wDayOfWeek = 0;
	}
	if (wDay)
	{
		*wDay = 0;
	}
	if (wHour)
	{
		*wHour = 0;
	}
	if (wMinute)
	{
		*wMinute = 0;
	}
	if (wSecond)
	{
		*wSecond = 0;
	}
	if (wMilliseconds)
	{
		*wMilliseconds = 0;
	}
	
#else
	if (wYear)
	{
		*wYear = 0;
	}
	if (wMonth)
	{
		*wMonth = 0;
	}
	if (wDayOfWeek)
	{
		*wDayOfWeek = 0;
	}
	if (wDay)
	{
		*wDay = 0;
	}
	if (wHour)
	{
		*wHour = 0;
	}
	if (wMinute)
	{
		*wMinute = 0;
	}
	if (wSecond)
	{
		*wSecond = 0;
	}
	if (wMilliseconds)
	{
		*wMilliseconds = 0;
	}
	

#endif
}

LONGLONG CALL HGE_Impl::Timer_GetFileTime()
{
#if defined __WIN32
	FILETIME filetime;
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	SystemTimeToFileTime(&systime, &filetime);
	return (((ULONGLONG)filetime.dwHighDateTime)<<32)|(filetime.dwLowDateTime);
#elif defined __PSP
	pspTime psptime;
	u64 filetime;
	sceRtcGetWin32FileTime(&psptime, &filetime);
	return filetime;
#elif defined __IPHONE
	return 0;
#else
	return 0;

#endif
}

float CALL HGE_Impl::Timer_GetTime()
{
	return fTime;
}

float CALL HGE_Impl::Timer_GetDelta()
{
	return fDeltaTime;
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
float CALL HGE_Impl::Timer_GetFPS(int mod)
{
	if(mod < 1)
		return fFPS;
	else
	{
		static float nowFPS = 0;
		static float fLastTime = 0;
		static DWORD nLastFrameCounter = 0;
		int modbase = nFrameSkip < 2 ? nFrameCounter : (nFrameCounter / nFrameSkip);
		if((modbase) % mod == 1)
		{
			if (nFrameCounter > nLastFrameCounter && fTime > fLastTime)
			{
				nowFPS = 1 / ((fTime - fLastTime) / (nFrameCounter - nLastFrameCounter));
			}
			fLastTime = fTime;
			nLastFrameCounter = nFrameCounter;
		}
		return nowFPS;
	}
}

/************************************************************************/
/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
float CALL HGE_Impl::Timer_GetWorstFPS(int mod)
{
	if(mod <= 1)
		return fFPS;
	static float worstFPS = HGEFPS_MAX;
	static float worstFPSMod = worstFPS;
	if(worstFPS > fFPS)
		worstFPS = fFPS;
	int modbase = nFrameSkip < 2 ? nFrameCounter : (nFrameCounter / nFrameSkip);
	if((modbase) % mod == 1)
	{
		worstFPSMod = worstFPS;
		worstFPS = HGEFPS_MAX;
	}
	return worstFPSMod;
}
