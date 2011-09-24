#ifndef _INFOQUAD_H
#define _INFOQUAD_H

#include "MainDependency.h"

#define	IQB_BOSSLIFE	0x01
#define	IQB_OTHER		0x04

#define	IQF_POWER		0x41
#define	IQF_OTHER		0x44

class InfoQuad
{
public:
	InfoQuad();
	~InfoQuad();

	static void Init();

	void valueSet(
		BYTE type, float x, float y,
		float x0, float y0, DWORD col0,
		float x1, float y1, DWORD col1,
		float x2, float y2, DWORD col2,
		float x3, float y3, DWORD col3
		);

public:
	hgeQuad	quad;
	float	x;
	float	y;
	BYTE	type;
};

#endif