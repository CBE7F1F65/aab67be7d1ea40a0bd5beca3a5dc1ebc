function Scene_s00(timer)
	local mapcenx, mapceny, xspeed, yspeed, mapxoffset = hdss.GetMapSpeedInfo();
	if timer == 0 then
		hdss.SetupBG(760);
		hdss.SetMapSpeedInfo(xspeed, 7.6);
	elseif timer < 120 then
		hdss.SetMapSpeedInfo(xspeed, yspeed-0.05);
	elseif timer == 800 then
		hdss.SetMapSpeedInfo(-1.0, yspeed);
	elseif timer == 1200 then
		hdss.SetMapSpeedInfo(0, 0);
	end
	return true;
end