#include "../Header/Process.h"
#include "../Header/Scripter.h"

int Process::processSceneSelect()
{
	gametime++;
	if(gametime == 1)
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_ENTERSTATE, STATE_SCENE_SELECT);
	}
	retvalue = PGO;
	Scripter::scr.Execute(SCR_CONTROL, STATE_SCENE_SELECT, gametime);
	return retvalue;
}
