#ifndef _REPLAY_H
#define _REPLAY_H

#include "Export.h"

struct _ReplayNameListItem 
{
	char filename[M_PATHMAX];
};

class Replay
{
public:
	Replay();
	~Replay();

	void Fill();
	void partFill(BYTE part);
	bool Load(const char * filename, bool getInput = false);
	void Save(const char * filename=NULL);
	bool Check(const char * filename);
	void CreateSaveFilename(char * filename);

	void WriteInput(WORD nowinput);
	WORD ReadInput();
	float GetReplayFPS();
	void InitReplayIndex(bool replaymode=false, BYTE part=0);

	static void Free(const char * filename);
	static void Release(bool deletefiles=true);
	static int GetEnumReplay();
	static void ReleaseEnumReplay();

public:
	partInfo partinfo[RPYPARTMAX];
	replayInfo rpyinfo;
	replayFrame replayframe[M_SAVEINPUTMAX];
	int replayIndex;
	char filename[M_PATHMAX];

	static list<_ReplayNameListItem> _rpyfilenamelist;

	static Replay rpy;
	static Replay * enumrpy;
	static int nenumrpy;
};

#endif