function CEClear_CloseUsed()
end

function CEClear_ExitState(tostate)
	CEClear_CloseUsed();
	hdssSETSTATE(tostate);
	hdssCLEARALL();
end

function ControlExecute_cClear(timer)
	CEClear_ExitState(STATE_OVER);
end