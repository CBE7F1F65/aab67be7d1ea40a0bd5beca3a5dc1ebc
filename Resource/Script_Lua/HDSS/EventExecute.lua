function _EventExecute_PlayerShot(playerindex)
	local playerID, nLife, shottimer, shotdelay, nchargemax = game.GetPlayerShotInfo(playerindex);
	return LTable_ePlayerShotFunction[playerID+1](playerindex, playerID, nLife, shottimer, shotdelay, nchargemax);
end

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
	elseif name == EVENT_PLAYERSHOT then
		return _EventExecute_PlayerShot(con);
	elseif name == EVENT_BOSSFADEOUT then
		return _EventExecute_BossFadeout(con);
	elseif name == EVENT_PLAYERINSTOP then
		return _EventExecute_PlayerInStop(con);
	end
	return true;

end