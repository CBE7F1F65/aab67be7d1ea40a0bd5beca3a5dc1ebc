function CESceneSelect_Init()
	hdssMUSICCHANGE(LConst_musicid_title);
end

function CESceneSelect_CloseUsed()
end

function CESceneSelect_ExitState(tostate)
	CESceneSelect_CloseUsed();
	hdssSETSTATE(tostate);
	if tostate == STATE_START then
		game.FreeTexture();
		hdssSTARTPREP();
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