#include "../Header/Process.h"
#include "../Header/Player.h"
#include "../Header/Scripter.h"

#define _PCLEAR_FDISP_TIME			240
#define _PCLEAR_FDIPS_CANCELTIME	60

int Process::processClear()
{
	if (!alltime)
	{
		alltime = gametime;
//		Player::p.exist = false;
	}
	processStart();
	Scripter::scr.Execute(SCR_CONTROL, STATE_CLEAR, gametime-alltime);

	return PGO;
}