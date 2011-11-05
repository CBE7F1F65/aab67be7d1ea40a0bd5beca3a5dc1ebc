function CEContinue_CloseUsed()
end

function CEContinue_ExitState(tostate, time)
	CEContinue_CloseUsed();
	hdss.SetState(tostate, time);
end

function ControlExecute_cContinue(timer)
	hdss.SetPlayerInitData(3, 1);
	CEContinue_ExitState(STATE_START, -1);
end