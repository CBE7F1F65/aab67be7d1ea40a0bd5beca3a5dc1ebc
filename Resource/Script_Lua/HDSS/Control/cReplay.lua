function CEReplay_Init()
	hdss.ChangeMusic(LConst_musicid_title);
end

function CEReplay_SetBG()
end

function CEReplay_CloseUsed()
end

function CEReplay_ExitState(tostate)
	CEReplay_CloseUsed();
	hdss.SetState(tostate);
end

function ControlExecute_cReplay(timer)
	return true;
end