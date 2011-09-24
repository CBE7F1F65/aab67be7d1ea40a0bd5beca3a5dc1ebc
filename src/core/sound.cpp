/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: audio routines
*/

/************************************************************************/
/* This file is modified by h5nc (h5nc@yahoo.com.cn)                    */
/* Changes of using higher version of BASS will not be marked in detail */
/* Anything of Music is removed                                         */
/************************************************************************/

#include "hge_impl.h"

#if defined __WIN32
#define BASSDEF(f) (WINAPI *f)	// define the functions as pointers
#endif
#if defined __WIN32 || defined __IPHONE
#include "BASS/bass.h"
#endif

#if defined __WIN32
#define LOADBASSFUNCTION(f) *((void**)&f)=(void*)GetProcAddress(hBass,#f)
#elif defined __IPHONE
#define LOADBASSFUNCTION(f) (#f)
#endif


HEFFECT CALL HGE_Impl::Effect_Load(const char *filename, DWORD size)
{
	DWORD _size, length, samples;
	HSAMPLE hs = NULL;
	HSTREAM hstrm;
#if defined __WIN32 || defined __IPHONE
	BASS_CHANNELINFO info;
#endif
	void *buffer, *data;

	if(hBass)
	{
		if(bSilent) return 1;

		if(size) { data=(void *)filename; _size=size; }
		else
		{
			data=Resource_Load(filename, &_size);
			if(!data) return NULL;
		}
#if defined __WIN32 || defined __IPHONE
		hs=BASS_SampleLoad(TRUE, data, 0, _size, 4, BASS_SAMPLE_OVER_VOL);
		if(!hs) {
			hstrm=BASS_StreamCreateFile(TRUE, data, 0, _size, BASS_STREAM_DECODE);
			if(hstrm) {
				length=(DWORD)BASS_ChannelGetLength(hstrm, BASS_POS_BYTE);
				BASS_ChannelGetInfo(hstrm, &info);
				samples=length;
				if(info.chans < 2) samples>>=1;
				if((info.flags & BASS_SAMPLE_8BITS) == 0) samples>>=1;
				buffer=(void*)BASS_SampleCreate(samples, info.freq, 2, 4, info.flags | BASS_SAMPLE_OVER_VOL);
				if(!buffer)
				{
					BASS_StreamFree(hstrm);
					_PostError("Can't create sound effect: Not enough memory");
				}
				else
				{
					BASS_ChannelGetData(hstrm, buffer, length);
//					hs=BASS_SampleCreateDone();
					BASS_StreamFree(hstrm);
//					if(!hs)	_PostError("Can't create sound effect");
				}
			}
		}
#endif
		if(!size) Resource_Free(data);
		return hs;
	}
	else return 0;
}

HCHANNEL CALL HGE_Impl::Effect_Play(HEFFECT eff)
{
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		HCHANNEL chn;
		chn=BASS_SampleGetChannel(eff, FALSE);
		BASS_ChannelPlay(chn, FALSE);
		return chn;
#endif
	}
	return NULL;
}

HCHANNEL CALL HGE_Impl::Effect_PlayEx(HEFFECT eff, int volume, int pan, float pitch, bool loop)
{
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		BASS_SAMPLE info;
		HCHANNEL chn;
		BASS_SampleGetInfo(eff, &info);

		chn=BASS_SampleGetChannel(eff, FALSE);
//		BASS_ChannelSetAttributes(chn, (int)(pitch*info.freq), volume, pan);
		BASS_ChannelSetAttribute(chn, BASS_ATTRIB_FREQ, pitch*info.freq);
		BASS_ChannelSetAttribute(chn, BASS_ATTRIB_VOL, (float)volume / 100.0f);
		BASS_ChannelSetAttribute(chn, BASS_ATTRIB_PAN, (float)pan / 100.0f);

		info.flags &= ~BASS_SAMPLE_LOOP;
		if(loop) info.flags |= BASS_SAMPLE_LOOP;
		BASS_ChannelFlags(chn, info.flags, 0xffffffff);
		BASS_ChannelPlay(chn, FALSE);
		return chn;
#endif
	}
	return NULL;
}


void CALL HGE_Impl::Effect_Free(HEFFECT eff)
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_SampleFree(eff);
#endif
}

/*
HMUSIC CALL HGE_Impl::Music_Load(const char *filename, DWORD size)
{
	void *data;
	DWORD _size;
	HMUSIC hm;

	if(hBass)
	{
		if(size)
		{
			data=(void *)filename;
			_size=size;
		}
		else
		{
			data=Resource_Load(filename, &_size);
			if(!data) return 0;
		}

		hm=BASS_MusicLoad(TRUE, data, 0, 0, BASS_MUSIC_PRESCAN | BASS_MUSIC_POSRESETEX | BASS_MUSIC_RAMP, 0);
		if(!hm)	_PostError("Can't load music");
		if(!size) Resource_Free(data);
		return hm;
	}
	else return 0;
}

HCHANNEL CALL HGE_Impl::Music_Play(HMUSIC mus, bool loop, int volume, int order, int row)
{
	if(hBass)
	{
		DWORD pos = BASS_MusicGetOrderPosition(mus);
		if(order == -1) order = LOWORD(pos);
		if(row == -1) row = HIWORD(pos);
		BASS_ChannelSetPosition(mus, MAKEMUSICPOS(order, row));

		BASS_CHANNELINFO info;
		BASS_ChannelGetInfo(mus, &info);
		BASS_ChannelSetAttributes(mus, info.freq, volume, 0);

		info.flags &= ~BASS_SAMPLE_LOOP;
		if(loop) info.flags |= BASS_SAMPLE_LOOP;
		BASS_ChannelSetFlags(mus, info.flags);

		BASS_ChannelPlay(mus, FALSE);

		return mus;
	}
	else return 0;
}

void CALL HGE_Impl::Music_Free(HMUSIC mus)
{
	if(hBass) BASS_MusicFree(mus);
}

void CALL HGE_Impl::Music_SetAmplification(HMUSIC music, int ampl)
{
	if(hBass) BASS_MusicSetAttribute(music, BASS_MUSIC_ATTRIB_AMPLIFY, ampl);
}

int CALL HGE_Impl::Music_GetAmplification(HMUSIC music)
{
	if(hBass) return BASS_MusicGetAttribute(music, BASS_MUSIC_ATTRIB_AMPLIFY);
	else return -1;
}

int CALL HGE_Impl::Music_GetLength(HMUSIC music)
{
	if(hBass)
	{
		return BASS_MusicGetOrders(music);
	}
	else return -1;
}

void CALL HGE_Impl::Music_SetPos(HMUSIC music, int order, int row)
{
	if(hBass)
	{
		BASS_ChannelSetPosition(music, MAKEMUSICPOS(order, row));
	}
}

bool CALL HGE_Impl::Music_GetPos(HMUSIC music, int *order, int *row)
{
	if(hBass)
	{
		DWORD pos;
		pos = BASS_MusicGetOrderPosition(music);
		if(pos == -1) return false;
		*order = LOWORD(pos);
		*row = HIWORD(pos);
		return true;
	}
	else return false;
}

void CALL HGE_Impl::Music_SetInstrVolume(HMUSIC music, int instr, int volume)
{
	if(hBass)
	{
		BASS_MusicSetAttribute(music, BASS_MUSIC_ATTRIB_VOL_INST + instr, volume);		
	}
}

int CALL HGE_Impl::Music_GetInstrVolume(HMUSIC music, int instr)
{
	if(hBass)
	{
		return BASS_MusicGetAttribute(music, BASS_MUSIC_ATTRIB_VOL_INST + instr);		
	}
	else return -1;
}

void CALL HGE_Impl::Music_SetChannelVolume(HMUSIC music, int channel, int volume)
{
	if(hBass)
	{
		BASS_MusicSetAttribute(music, BASS_MUSIC_ATTRIB_VOL_CHAN + channel, volume);		
	}
}

int CALL HGE_Impl::Music_GetChannelVolume(HMUSIC music, int channel)
{
	if(hBass)
	{
		return BASS_MusicGetAttribute(music, BASS_MUSIC_ATTRIB_VOL_CHAN + channel);		
	}
	else return -1;
}
*/
HSTREAM CALL HGE_Impl::Stream_Load(const char *filename, DWORD size, bool bLoad)
{
	void *data=NULL;
	DWORD _size;
	HSTREAM hs;
	CStreamList *stmItem;

	if(hBass)
	{
		if(bSilent) return 1;

		if (bLoad)
		{
			if(size) { data=(void *)filename; _size=size; }
			else
			{
				data=Resource_Load(filename, &_size);
				if(!data) return 0;
			}
#if defined __WIN32 || defined __IPHONE
			hs=BASS_StreamCreateFile(TRUE, data, 0, _size, BASS_STREAM_PRESCAN);
#endif
		}
#if defined __WIN32 || defined __IPHONE
		else
		{
			hs=BASS_StreamCreateFile(FALSE, Resource_MakePath(filename), 0, 0, BASS_STREAM_PRESCAN);
		}
#endif
		if(!hs)
		{
			_PostError("Can't load stream");
			if(!size && data) Resource_Free(data);
			return 0;
		}
		if(!size && bLoad)
		{
			stmItem=new CStreamList;
			stmItem->hstream=hs;
			stmItem->data=data;
			stmItem->next=streams;
			streams=stmItem;
		}
		return hs;
	}
	else return 0;
}

void CALL HGE_Impl::Stream_Free(HSTREAM stream)
{
	CStreamList *stmItem=streams, *stmPrev=0;

	if(hBass)
	{
		while(stmItem)
		{
			if(stmItem->hstream==stream)
			{
				if(stmPrev) stmPrev->next=stmItem->next;
				else streams=stmItem->next;
				Resource_Free(stmItem->data);
				delete stmItem;
				break;
			}
			stmPrev=stmItem;
			stmItem=stmItem->next;
		}
#if defined __WIN32 || defined __IPHONE
		BASS_StreamFree(stream);
#endif
	}
}

HCHANNEL CALL HGE_Impl::Stream_Play(HSTREAM stream, bool loop, int volume)
{
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		BASS_CHANNELINFO info;
		BASS_ChannelGetInfo(stream, &info);
//		BASS_ChannelSetAttributes(stream, info.freq, volume, 0);
		BASS_ChannelSetAttribute(stream, BASS_ATTRIB_FREQ, float(info.freq));
		BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, (float)volume / 100.0f);

		info.flags &= ~BASS_SAMPLE_LOOP;
		if(loop) info.flags |= BASS_SAMPLE_LOOP;
		BASS_ChannelFlags(stream, info.flags, 0xffffffff);
		BASS_ChannelPlay(stream, TRUE);
		return stream;
#endif
	}
	return NULL;
}

void CALL HGE_Impl::Channel_SetPanning(HCHANNEL chn, int pan)
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_ChannelSetAttribute(chn, BASS_ATTRIB_PAN, (float)pan / 100.0f);
#endif
}

void CALL HGE_Impl::Channel_SetVolume(HCHANNEL chn, int volume)
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_ChannelSetAttribute(chn, BASS_ATTRIB_VOL, (float)volume / 100.0f);
#endif
}

void CALL HGE_Impl::Channel_SetPitch(HCHANNEL chn, float pitch)
{
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		BASS_CHANNELINFO info;
		BASS_ChannelGetInfo(chn, &info);
		BASS_ChannelSetAttribute(chn, BASS_ATTRIB_FREQ, pitch*info.freq);
#endif
	}
}

void CALL HGE_Impl::Channel_Pause(HCHANNEL chn)
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_ChannelPause(chn);
#endif
}

void CALL HGE_Impl::Channel_Resume(HCHANNEL chn)
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_ChannelPlay(chn, FALSE);
#endif
}

void CALL HGE_Impl::Channel_Stop(HCHANNEL chn)
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_ChannelStop(chn);
#endif
}

void CALL HGE_Impl::Channel_PauseAll()
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_Pause();
#endif
}

void CALL HGE_Impl::Channel_ResumeAll()
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_Start();
#endif
}

void CALL HGE_Impl::Channel_StopAll()
{
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		BASS_Stop();
		BASS_Start();
#endif
	}
}

bool CALL HGE_Impl::Channel_IsPlaying(HCHANNEL chn)
{
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		if(BASS_ChannelIsActive(chn)==BASS_ACTIVE_PLAYING) return true;
		return false;
#endif
	}
	return false;
}

QWORD CALL HGE_Impl::Channel_GetLength(HCHANNEL chn) {
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		return BASS_ChannelGetLength(chn, BASS_POS_BYTE);
#endif
	}
	return -1;
}

QWORD CALL HGE_Impl::Channel_GetPos(HCHANNEL chn) {
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		return BASS_ChannelGetPosition(chn, BASS_POS_BYTE);
#endif
	}
	return -1;
}

void CALL HGE_Impl::Channel_SetPos(HCHANNEL chn, QWORD pos) {
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		BASS_ChannelSetPosition(chn, pos, BASS_POS_BYTE);
#endif
	}
}


/************************************************************************/
/* This function is added by h5nc (h5nc@yahoo.com.cn)                   */
/************************************************************************/
void CALL HGE_Impl::Channel_SetStartPos(HCHANNEL chn, hgeChannelSyncInfo * pcsi)
{
	if (pcsi != NULL && hBass)
	{
#if defined __WIN32 || defined __IPHONE
		BASS_ChannelSetPosition(chn, pcsi->startPos, BASS_POS_BYTE);
#endif
	}
}

/************************************************************************/
/* This function is modified by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
void CALL HGE_Impl::Channel_SlideTo(HCHANNEL channel, float _time, int volume, int pan, float pitch)
{
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		BASS_CHANNELINFO info;
		BASS_ChannelGetInfo(channel, &info);

		DWORD time = _time * 1000;

//		BASS_ChannelSlideAttributes(channel, freq, volume, pan, DWORD(time*1000));
		if (pitch != -1)
		{
			BASS_ChannelSlideAttribute(channel, BASS_ATTRIB_FREQ, pitch * info.freq, time);
		}
		if (volume != -1)
		{
			BASS_ChannelSlideAttribute(channel, BASS_ATTRIB_VOL, (float)volume / 100.0f, time);
		}
		if (pan != -101)
		{
			BASS_ChannelSlideAttribute(channel, BASS_ATTRIB_PAN, (float)pan / 100.0f, time);
		}
#endif
	}
}

bool CALL HGE_Impl::Channel_IsSliding(HCHANNEL channel)
{
	if(hBass)
	{
#if defined __WIN32 || defined __IPHONE
		if(BASS_ChannelIsSliding(channel, BASS_ATTRIB_VOL)) return true;
		return false;
#endif
	}
	return false;
}


//////// Implementation ////////


bool HGE_Impl::_SoundInit()
{
	if(!bUseSound || hBass) return true;
#if defined __WIN32 || defined __IPHONE
#if defined __WIN32
	hBass=LoadLibrary(szBassDllFile);
#elif defined __IPHONE
	hBass=1;
#endif
#endif
	if (!hBass)
	{
		_PostError("Can't load BASS.DLL");
		return false;
	}

	LOADBASSFUNCTION(BASS_GetVersion);

	if (HIWORD(BASS_GetVersion()) != BASSVERSION)
	{
		_PostError("Incorrect BASS.DLL version");
		return false;
	}

	/************************************************************************/
	/* Some functions are deleted or added by h5nc (h5nc@yahoo.com.cn)      */
	/************************************************************************/
//	LOADBASSFUNCTION(BASS_GetDeviceDescription);
	LOADBASSFUNCTION(BASS_Init);
	LOADBASSFUNCTION(BASS_Free);
	LOADBASSFUNCTION(BASS_Start);
	LOADBASSFUNCTION(BASS_Pause);
	LOADBASSFUNCTION(BASS_Stop);
	LOADBASSFUNCTION(BASS_SetConfig);
	//LOADBASSFUNCTION(BASS_ErrorGetCode);

	LOADBASSFUNCTION(BASS_SampleLoad);
	LOADBASSFUNCTION(BASS_SampleCreate);
//	LOADBASSFUNCTION(BASS_SampleCreateDone);
	LOADBASSFUNCTION(BASS_SampleGetInfo);
	LOADBASSFUNCTION(BASS_SampleGetChannel);
	LOADBASSFUNCTION(BASS_SampleFree);
	/*
	LOADBASSFUNCTION(BASS_MusicLoad);
	LOADBASSFUNCTION(BASS_MusicFree);
	LOADBASSFUNCTION(BASS_MusicGetOrders);
	LOADBASSFUNCTION(BASS_MusicGetOrderPosition);
	LOADBASSFUNCTION(BASS_MusicSetAttribute);
	LOADBASSFUNCTION(BASS_MusicGetAttribute);
*/
	LOADBASSFUNCTION(BASS_StreamCreateFile);
	LOADBASSFUNCTION(BASS_StreamFree);
	
	LOADBASSFUNCTION(BASS_ChannelGetInfo);
	LOADBASSFUNCTION(BASS_ChannelGetAttribute);
	LOADBASSFUNCTION(BASS_ChannelSetAttribute);
	LOADBASSFUNCTION(BASS_ChannelSlideAttribute);
	LOADBASSFUNCTION(BASS_ChannelIsSliding);
	LOADBASSFUNCTION(BASS_ChannelFlags);
	LOADBASSFUNCTION(BASS_ChannelGetData);
	LOADBASSFUNCTION(BASS_ChannelPlay);
	LOADBASSFUNCTION(BASS_ChannelPause);
	LOADBASSFUNCTION(BASS_ChannelStop);
	LOADBASSFUNCTION(BASS_ChannelIsActive);
	LOADBASSFUNCTION(BASS_ChannelGetLength);
	LOADBASSFUNCTION(BASS_ChannelGetPosition);
	LOADBASSFUNCTION(BASS_ChannelSetPosition);
	LOADBASSFUNCTION(BASS_ChannelSeconds2Bytes);
	LOADBASSFUNCTION(BASS_ChannelBytes2Seconds);
	LOADBASSFUNCTION(BASS_ChannelSetSync);
	LOADBASSFUNCTION(BASS_ChannelUpdate);
	LOADBASSFUNCTION(BASS_ChannelRemoveSync);

	bSilent=false;
	if (!BASS_Init(-1,nSampleRate,0,
#if defined __WIN32
				   hwnd,
#elif defined __IPHONE
				   NULL,
#endif
				   NULL))
	{
		System_Log("BASS Init failed, using no sound");
		BASS_Init(0,nSampleRate,0,
#if defined __WIN32
				  hwnd,
#elif defined __IPHONE
				  NULL,
#endif

				  NULL);
		bSilent=true;
	}
	else
	{
//		System_Log("Sound Device: %s",BASS_GetDeviceDescription(1));
		System_Log("Sample rate: %ld\n", nSampleRate);
	}

	//BASS_SetConfig(BASS_CONFIG_BUFFER, 5000);
	//BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 50);

	_SetFXVolume(nFXVolume);
	_SetSampleVolume(nSampleVolume);
	_SetStreamVolume(nStreamVolume);

	return true;
}

void HGE_Impl::_SoundDone()
{
	CStreamList *stmItem=streams, *stmNext;
	
	if(hBass)
	{

		/************************************************************************/
		/* This condition is added by h5nc (h5nc@yahoo.com.cn)                  */
		/************************************************************************/
#if defined __WIN32 || defined __IPHONE
		if (HIWORD(BASS_GetVersion()) == BASSVERSION)
		{
			BASS_Stop();
			BASS_Free();
		}

		//int err = BASS_ErrorGetCode(); 
#if defined __WIN32
		FreeLibrary(hBass);
#endif
#endif
		hBass=0;

		while(stmItem)
		{
			stmNext=stmItem->next;
			Resource_Free(stmItem->data);
			delete stmItem;
			stmItem=stmNext;
		}
		streams=0;
	}
}

void HGE_Impl::_SetSampleVolume(int vol)
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, vol);
#endif
}

void HGE_Impl::_SetStreamVolume(int vol)
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, vol);
#endif // __WIN32
}

void HGE_Impl::_SetFXVolume(int vol)
{
#if defined __WIN32 || defined __IPHONE
	if(hBass) BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, vol);
#endif // __WIN32
}

/************************************************************************/
/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
#if defined __WIN32 || defined __IPHONE
void CALLBACK _BASS_Sync_Func(HSYNC handle, DWORD channel, DWORD data, void * _pcsi)
{
	hgeChannelSyncInfo * pcsi = (hgeChannelSyncInfo *)_pcsi;
	BASS_ChannelSetPosition(channel, pcsi->startPos+pcsi->introLength, BASS_POS_BYTE);
	BASS_ChannelUpdate(channel, 0);
//	BASS_ChannelSetSync(channel, BASS_SYNC_POS, pcsi->endPos, _BASS_Sync_Func, pcsi);
}
#endif // __WIN32

void HGE_Impl::Channel_SetLoop(HCHANNEL channel, hgeChannelSyncInfo * pcsi)
{
	if (pcsi != NULL && hBass)
	{
		if (pcsi->sync)
		{
			Channel_RemoveLoop(channel, pcsi);
		}
#if defined __WIN32 || defined __IPHONE
		pcsi->sync = BASS_ChannelSetSync(channel, BASS_SYNC_POS|BASS_SYNC_MIXTIME, pcsi->startPos+pcsi->allLength, _BASS_Sync_Func, pcsi);
		BASS_ChannelUpdate(channel, 0);
#endif // __WIN32
	}
}

void HGE_Impl::Channel_RemoveLoop(HCHANNEL channel, hgeChannelSyncInfo * pcsi)
{
	if (pcsi != NULL && hBass)
	{
#if defined __WIN32 || defined __IPHONE
		BASS_ChannelRemoveSync(channel, pcsi->sync);
#endif // __WIN32
	}
}





