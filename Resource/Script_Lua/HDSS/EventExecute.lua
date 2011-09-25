function _EventExecute_EffspChase(playerindex)
end

function _EventExecute_PlayerInStop(playerindex)
	local playerID = hdss.Get(HDSS_CHARA, playerindex);
	return ePlayerInStop(playerindex, playerID);
end

function _EventExecute_BossFadeout(playerindex)
	hdssBGSETUP(playerindex, LConst_bgset_spellid, BGLAYERSET_NONE);
end

function EventExecute(name, con)

	if name == EVENT_EFFSPCHASE then
		return _EventExecute_EffspChase(con);
	elseif name == EVENT_BOSSFADEOUT then
		return _EventExecute_BossFadeout(con);
	elseif name == EVENT_PLAYERINSTOP then
		return _EventExecute_PlayerInStop(con);
	end
	return true;

end