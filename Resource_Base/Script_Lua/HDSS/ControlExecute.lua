function ControlExecute(name, con)

	if name == STATE_START then
		return ControlExecute_cStart(con);
	elseif name == STATE_PAUSE then
		return ControlExecute_cPause(con);
	elseif name == STATE_CLEAR then
		return ControlExecute_cClear(con);
	elseif name == STATE_TITLE then
		return ControlExecute_cTitle(con);
	elseif name == STATE_MATCH_SELECT then
		return ControlExecute_cMatchSelect(con);
	elseif name == STATE_PLAYER_SELECT then
		return ControlExecute_cPlayerSelect(con);
	elseif name == STATE_SCENE_SELECT then
		return ControlExecute_cSceneSelect(con);
	elseif name == STATE_OVER then
		return ControlExecute_cOver(con);
	elseif name == STATE_REPLAY then
		return ControlExecute_cReplay(con);
	end
	
	return true;

end