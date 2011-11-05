function eventPlayerDead(con)
end

function EventExecute(name, con)
	
	if name == EVENT_PLAYERDEAD then
		return eventPlayerDead(con);
	end
	
	return true;

end