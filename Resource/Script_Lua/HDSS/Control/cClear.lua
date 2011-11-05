function CEClear_CloseUsed()
end

function CEClear_ExitState(tostate)
	CEClear_CloseUsed();
	hdss.SetState(tostate);
	hdss.ClearAll();
end

function ControlExecute_cClear(timer)
	if timer == 120 then
		local nowstage = hdss.GetStage();
		hdss.SetStage(nowstage+1);
		CEClear_ExitState(STATE_START);
	end
end