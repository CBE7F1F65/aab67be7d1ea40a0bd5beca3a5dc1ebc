#include "../Header/Process.h"
#include "../Header/Scripter.h"

int Process::processSpell()
{
	gametime++;
	if(gametime == 1)
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_ENTERSTATE, STATE_SPELL);
	}
	retvalue = PGO;
	Scripter::scr.Execute(SCR_CONTROL, STATE_SPELL, gametime);
	return retvalue;
}