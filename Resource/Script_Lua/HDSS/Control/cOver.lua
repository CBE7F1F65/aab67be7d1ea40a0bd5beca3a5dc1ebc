function CEOver_Init()	
end

function CEOver_SetBG()
end

function CEOver_SetSelect(selsysoverid, select)
	
end

function CEOver_CloseUsed()
end

function CEOver_ExitState(tostate)
	CEOver_CloseUsed();
	hdssSETSTATE(tostate);
end
function ControlExecute_cOver(timer)

	CEOver_ExitState(STATE_TITLE);
	return true;

end