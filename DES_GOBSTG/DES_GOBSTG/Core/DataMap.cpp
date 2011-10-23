#include "../Header/Data.h"

dataMapTable dataMap[] = 
{
	{"_DATASTART_",		0xffffffff},

	{"_E",				0x00100000},
	{"_N",				0x00200000},
	{"_H",				0x00300000},
	{"_D",				0x00400000},
	{"_X",				0x00500000},

	{"Header",			0x01000000},
	{"GameVersion",		0x01010000},
	{"Signature",		0x01020000},
	{"FileType",		0x01030000},

	{"Top",				0x02000000},
	{"Score",			0x02010000},
	{"LastStage",		0x02020000},
	{"Username",		0x02030000},
	{"Year",			0x02040000},
	{"Month",			0x02050000},
	{"Day",				0x02060000},
	{"Hour",			0x02070000},
	{"Minute",			0x02080000},
	{"Lost",			0x02090000},
	{"BorderRate",		0x020A0000},
	{"FastRate",		0x020B0000},
	{"AllTime",			0x020C0000},
	{"SpellGet",		0x020D0000},
	{"MaxPlayer",		0x020E0000},
	{"Point",			0x020F0000},
	{"Faith",			0x02100000},
	{"Miss",			0x02110000},
	{"Bomb",			0x02120000},
	{"Continue",		0x02130000},
	{"Pause",			0x02140000},
	{"GetSpell",		0x02150000},
	{"Chara",			0x02160000},

	{"Spell",			0x03000000},
	{"GetGame",			0x03010000},
	{"MeetGame",		0x03020000},
	{"GetPractice",		0x03030000},
	{"MeetPractice",	0x03040000},
	{"TopBonus",		0x03050000},

	{"StagePractice",	0x04000000},
	{"TryTime",			0x04010000},
	{"TopScore",		0x04020000},

	{"Total",			0x05000000},
	{"PlayTime",		0x05010000},
	{"ClearTime",		0x05020000},
	{"PracticeTime",	0x05030000},
	{"FirstRunTime",	0x05040000},
	{"TotalPlayTime",	0x05050000},

	{"Flag",			0x0A000000},

	{"_END_",				0xffffffff}
};