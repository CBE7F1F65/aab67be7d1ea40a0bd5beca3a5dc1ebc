function CEMatchSelect_Init()
	hdssMUSICCHANGE(LConst_musicid_title);
end

function CEMatchSelect_SetBG()
end

function CEMatchSelect_CloseUsed(selsysmatchid, selsyslatencyid, bbottom)
	--Close
end

function CEMatchSelect_ExitState(tostate)
	hdssSETSTATE(tostate);
end

function ControlExecute_cMatchSelect(timer)


	CEMatchSelect_ExitState(STATE_PLAYER_SELECT, false);		
	return true;

end