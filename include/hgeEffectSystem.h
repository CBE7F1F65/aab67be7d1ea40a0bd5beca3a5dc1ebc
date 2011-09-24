#ifndef HGEEFFECTSYSTEM_H
#define HGEEFFECTSYSTEM_H

#include "hge.h"
#include "hgesprite.h"
#include "hgeColor.h"

#define MAX_EFFECTS 500

#define HGEEFFECT_AGE_STOP		-2
#define HGEEFFECT_AGE_FOREVER	-1
#define HGEEFFECT_AGE_START		0
#define HGEEFFECT_AGE_ONCE		0x400

#define HGEEFFECT_AFFECTORIDMASK	0x00ff
#define HGEEFFECT_EMITTERIDMASK		0xff00

#define HGEEFFECT_EMITTERMAX	UCHAR_MAX
#define HGEEFFECT_AFFECTORMAX	UCHAR_MAX

enum{
	HGEEFFECT_AFFECTORTYPE_NONE,
	HGEEFFECT_AFFECTORTYPE_SPIN,
	HGEEFFECT_AFFECTORTYPE_SPEEDRADIAL,
	HGEEFFECT_AFFECTORTYPE_SPEEDTANGENTIAL,
	HGEEFFECT_AFFECTORTYPE_SPEED_X,
	HGEEFFECT_AFFECTORTYPE_SPEED_Y,
	HGEEFFECT_AFFECTORTYPE_SPEED_Z,
	HGEEFFECT_AFFECTORTYPE_SCALE,
	HGEEFFECT_AFFECTORTYPE_SCALE_X,
	HGEEFFECT_AFFECTORTYPE_SCALE_Y,
	HGEEFFECT_AFFECTORTYPE_ZSTRETCH,
	HGEEFFECT_AFFECTORTYPE_COLOR,

	HGEEFFECT_AFFECTORTYPE_END
};

struct hgeEffectObject{
	int		nAge;
	int		nLifeTime;
	float	x, y, z;
	float	zStretch;
	float	zStretchBuffer;
	float	fSpeedX;
	float	fSpeedXBuffer;
	float	fSpeedY;
	float	fSpeedYBuffer;
	float	fSpeedZ;
	float	fSpeedZBuffer;
	float	fSpeedRaditial;
	float	fSpeedRaditialBuffer;
	float	fSpeedTangential;
	float	fSpeedTangentialBuffer;
	float	fHeadDirection;
	float	fHeadDirectionBuffer;
	float	fScaleX;
	float	fScaleXBuffer;
	float	fScaleY;
	float	fScaleYBuffer;
	DWORD	color;
	DWORD	colorBuffer;
};

struct hgeEffectBasicInfo{
	int		nLifeTime;
	int		nRepeatDelay;
	HTEXTURE tex;
};

enum{
	HGEEFFECT_EI_NSTARTTIME,
	HGEEFFECT_EI_NENDTIME,
	HGEEFFECT_EI_NLIFETIMEMIN,
	HGEEFFECT_EI_NLIFETIMEMAX,
	HGEEFFECT_EI_FEMITNUM,
	HGEEFFECT_EI_FROTATIONX,
	HGEEFFECT_EI_FROTATIONY,
	HGEEFFECT_EI_FRADIUS,
	HGEEFFECT_EI_FRADIUSINNER,
	HGEEFFECT_EI_FTHETASTART,
	HGEEFFECT_EI_FTHETASTEP,
	HGEEFFECT_EI_FTRACERESISTANCE,
	HGEEFFECT_EI_FTEXTUREX,
	HGEEFFECT_EI_FTEXTUREY,
	HGEEFFECT_EI_FTEXTUREW,
	HGEEFFECT_EI_FTEXTUREH,
	HGEEFFECT_EI_FHOTX,
	HGEEFFECT_EI_FHOTY,
	HGEEFFECT_EI_BLEND,
	HGEEFFECT_EI_BTRACE,
	HGEEFFECT_EI_BADJUSTDIRECTION,
	
	HGEEFFECT_EI_END,
};

struct hgeEffectEmitterInfo{
	int		nStartTime;
	int		nEndTime;
	int		nLfieTimeMin;
	int		nLifeTimeMax;
	float	fEmitNum;
	float	fRotationX;
	float	fRotationY;
	float	fRadius;
	float	fRadiusInner;
	float	fThetaStart;
	float	fThetaStep;
	float	fTraceResistance;
	float	fTextureX;
	float	fTextureY;
	float	fTextureW;
	float	fTextureH;
	float	fHotX;
	float	fHotY;
	char	blend;
	char	bTrace;
	char	bAdjustDirection;
};

enum{
	HGEEFFECT_AI_NAFFECTORSTARTTIME,
	HGEEFFECT_AI_NAFFECTORENDTIME,
	HGEEFFECT_AI_NRANDOMPICKINTERVAL,
	HGEEFFECT_AI_FSTARTVALUEMIN,
	HGEEFFECT_AI_FSTARTVALUEMAX,
	HGEEFFECT_AI_FENDVALUEMIN,
	HGEEFFECT_AI_FENDVALUEMAX,
	HGEEFFECT_AI_FINCREMENTVALUEMIN,
	HGEEFFECT_AI_FINCREMENTVALUEMAX,
	HGEEFFECT_AI_FINCREMENTSCALE,
	HGEEFFECT_AI_FACCELERATION,
	HGEEFFECT_AI_BUSESTARTVALUE,
	HGEEFFECT_AI_BUSEENDVALUE,
	HGEEFFECT_AI_TYPE,
	
	HGEEFFECT_AI_END,
};

struct hgeEffectAffectorInfo{
	int		nAffectorStartTime;
	int		nAffectorEndTime;
	int		nRandomPickInterval;
	float	fStartValueMin;
	float	fStartValueMax;
	float	fEndValueMin;
	float	fEndValueMax;
	float	fIncrementValueMin;
	float	fIncrementValueMax;
	float	fIncrementScale;
	float	fAcceleration;
	char	bUseStartValue;
	char	bUseEndValue;
	char	type;
};

struct hgeEffectAffector{
	hgeEffectAffectorInfo	eai;
	int						nAge;
	BYTE					ID;
};

struct CAffectorList{
	hgeEffectAffector		affector;
	CAffectorList *			next;
};

struct hgeEffectEmitter{
	hgeEffectObject			* obj;
	CAffectorList *			eaiList;
	hgeEffectEmitterInfo	eei;
	int						nEffectObjectsAlive;
	int						nAge;
	int						nObj;
	float					fEmissionResidue;
	hgeSprite *				sprite;
	BYTE					ID;
};

struct CEmitterList{
	hgeEffectEmitter		emitter;
	CEmitterList *			next;
};

class hgeEffectSystem
{
public:
	hgeEffectSystem();
	hgeEffectSystem(const char * filename, HTEXTURE tex = 0, HTEXTURE * texset = 0);
	hgeEffectSystem(const hgeEffectSystem & eff);
	~hgeEffectSystem();

	int Load(const char * filename, HTEXTURE tex = 0, HTEXTURE * texset = 0);
	bool Save(const char * filename, int _texnum = -1);

	void FreeList();
	void Render(hge3DPoint *ptfar=NULL, DWORD colormask=0xffffffff);
	void MoveTo(float x, float y, float z = 0, bool bForce = false);
	void Fire();
	void Stop(bool bKill = false);

	void Update();

	void Affect(hgeEffectObject * obj, hgeEffectAffector * affector);
	void UpdateValue(float * value, float * bufferValue, hgeEffectAffectorInfo * eai, int nAge);
	void UpdateColorValue(DWORD * value, DWORD * bufferValue, hgeEffectAffectorInfo * eai, int nAge);

	bool SetBasicInfo(hgeEffectBasicInfo * ebi);
	bool AddEmitter(hgeEffectEmitter * emitter);
	bool AddEmitter(BYTE emitterID, hgeEffectEmitterInfo * emitterInfo);
	bool DeleteEmitter(BYTE emitterID);
	bool AddAffector(BYTE emitterID, hgeEffectAffector * affector);
	bool AddAffector(BYTE affectorID, BYTE emitterID, hgeEffectAffectorInfo * affectorInfo);
	bool DeleteAffector(BYTE emitterID, BYTE affectorID);

	void * GetEmitterInfoValuePointer(BYTE emitterID, BYTE type);
	void * GetAffectorInfoValuePointer(BYTE emitterID, BYTE affectorID, BYTE type);

	int GetEmitterAge(BYTE emitterID);
	int GetAffectorAge(BYTE emitterID, BYTE affectorID);
	int GetEffectObjectAlive(BYTE emitterID = 0, int * nobj=NULL);

public:
	void InitEffectSystem();
	void InitEffectSystem(const char * filename, HTEXTURE tex = 0, HTEXTURE * texset = 0);
	void InitEffectSystem(const hgeEffectSystem & eff);

public:
	static void Release();

public:
	hgeEffectBasicInfo	ebi;
	CEmitterList *		eiList;
	int		nAge;
	int		nDelayCounter;
	float	x, y, z;
	float	lastx, lasty, lastz;
	int		texnum;

	static HGE	*	hge;
};

#endif
