#include "../Header/Process.h"
#include "../Header/Player.h"
#include "../Header/Data.h"
#include "../Header/DataConnector.h"
#include "../Header/Replay.h"
#include "../Header/GameInput.h"

void Process::frameStart()
{
	gametime++;
	WORD nowInput = 0;
	if(!replaymode)
	{
		playing = true;
		nowInput = GameInput::GetNowInput();
		Replay::rpy.WriteInput(nowInput);
	}
	else
	{
		nowInput = Replay::rpy.ReadInput();
		replayFPS = Replay::rpy.GetReplayFPS();

		if(nowInput == 0xffff)
		{
			replayend = true;
//			scene = S1;
//			clearPrep();
			GameInput::SetKey(0, KSI_PAUSE);
			GameInput::SetKey(1, KSI_PAUSE);
		}
		else
		{
			GameInput::SetNowInput(nowInput);

		}
	}
	active = true;
}