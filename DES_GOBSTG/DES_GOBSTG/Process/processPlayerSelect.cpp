#include "../Header/Process.h"
#include "../Header/Scripter.h"

#include "../Header/GameInput.h"

int Process::processPlayerSelect()
{
	gametime++;
	if(gametime == 1)
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_ENTERSTATE, STATE_PLAYER_SELECT);
	}
#if defined __IPHONE
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++) {
		GameInput::SetKey(i, KSI_SLOW, true);
	}
#endif
	retvalue = PGO;
	Scripter::scr.Execute(SCR_CONTROL, STATE_PLAYER_SELECT, gametime);
	return retvalue;
}
