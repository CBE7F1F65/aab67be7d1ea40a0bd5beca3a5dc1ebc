function CESceneSelect_Init()
	hdss.ChangeMusic(LConst_musicid_title);
end

function CESceneSelect_CloseUsed()
end

function CESceneSelect_ExitState(tostate)
	CESceneSelect_CloseUsed();
	hdss.SetState(tostate);
	if tostate == STATE_START then
		game.FreeTexture();
		hdss.CallStartPrep();
	end
end

function ControlExecute_cSceneSelect(timer)

	if timer == 1 then
		CESceneSelect_Init();
	end
	_DEBUG_NewRandomMatch();
	CESceneSelect_ExitState(STATE_START);
		
	return true;

end