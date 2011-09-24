#ifndef _BEAM_H
#define _BEAM_H

#include "BObject.h"

#define BEAM_INVALIDSCALE	0.5f

#define BEAMFLAG_NONE		0x00
#define BEAMFLAG_HORIZON	0x01
#define BEAMFLAG_STOP		0x02
#define BEAMFLAG_HS			(BEAMFLAG_HORIZON + BEAMFLAG_STOP)
#define BEAMFLAG_NOGRAZE	0x10
#define BEAMFLAG_DELAY		0x20

class Beam : public BObject
{
public:
	Beam();
	~Beam();

	static void Init();
	static int Build(BYTE playerindex, float x, float y, int angle, float speed, BYTE type, BYTE color, float length, float width = 0, BYTE flag = BEAMFLAG_NONE, int fadeintime = 8, int fadeouttime = 0, BYTE tarID = 0xff);
	static void ClearItem();
	static void Action();
	static void RenderAll(BYTE playerindex);

	void valueSet(WORD ID, float x, float y,int angle, float speed, BYTE type, BYTE color, float length, float width = 0, BYTE flag = BEAMFLAG_NONE, int fadeintime = 8, int fadeouttime = 0, BYTE tarID = 0xff);
	bool isInRect(float aimx, float aimy, float r, int nextstep=0);

	void SetVector(const BObject &ori, const BObject &aim);
	void SetVector(float orix, float oriy, float aimx, float aimy);

	void SetHold(BYTE holdtar, float holdoffset);
	void SetHold(BYTE holdtar, BYTE pintar, float holdoffset);

	void action(BYTE playerindex);

	void Render();

public:
	float	xplus;
	float	yplus;
	float	lastspeed;
	float	holdoffset;
	int		lastangle;
	int		fadeintime;
	int		fadeouttime;

	float	texw;
	float	texh;

	bool	fadeout;
	bool	able;

	float	length;
	float	width;
	BYTE	flag;
	BYTE	type;
	BYTE	color;
	BYTE	grazetimer;
	BYTE	holdtar;
	BYTE	pintar;

	BYTE	delaytimer;

	static VectorList<Beam> be[M_PL_MATCHMAXPLAYER];
};

#endif