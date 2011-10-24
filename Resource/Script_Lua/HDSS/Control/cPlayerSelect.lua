function CEPlayerSelect_Init()
	hdssMUSICCHANGE(LConst_musicid_title);
end

function CEPlayerSelect_SetBG()
end

function CEPlayerSelect_CloseUsed(bcloseall)
end

function CEPlayerSelect_ExitState(tostate, bcloseall)
	game.FreeTexture();
	CEPlayerSelect_CloseUsed(bcloseall);
	hdssSETSTATE(tostate);
end

function ControlExecute_cPlayerSelect(timer)
	
	CEPlayerSelect_ExitState(STATE_SCENE_SELECT, false);
	return true;

end