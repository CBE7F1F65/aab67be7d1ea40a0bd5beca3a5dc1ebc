#include "../Header/Process.h"
#include "../Header/Scripter.h"
#include "../Header/SelectSystem.h"

int Process::processTitle()
{
	gametime++;
	if(gametime == 1)
	{
		reload();
		for (int i=0; i<SELSYSTEMMAX; i++)
		{
			SelectSystem::selsys[i].select = titleselect;
		}
	}
	retvalue = PGO;
	Scripter::scr.Execute(SCR_CONTROL, STATE_TITLE, gametime);
	int tselsys = Scripter::scr.GetIntValue(SCR_RESERVEBEGIN);
	titleselect = SelectSystem::selsys[tselsys].select;
	return retvalue;
	
}