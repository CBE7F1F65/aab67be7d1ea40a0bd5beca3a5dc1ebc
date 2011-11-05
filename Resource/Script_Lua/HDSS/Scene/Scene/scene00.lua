function Scene_s00(timer)
	local mapcenx, mapceny, xspeed, yspeed, mapxoffset = hdss.GetMapSpeedInfo();
	if timer == 1 then
		hdss.SetupBG(760);
		hdss.SetMapSpeedInfo(xspeed, 7.6);
		hdss.BuildEnemy(
			{
				36, 160, 60, 0, 0.0, 36, 9999999
			}
		)
	elseif timer < 120 then
		hdss.SetMapSpeedInfo(xspeed, yspeed-0.05);
	elseif timer == 800 then
		hdss.SetMapSpeedInfo(0, yspeed);
	elseif timer == 1200 then
--		hdss.SetMapSpeedInfo(0, 0);
--		hdss.SetState(STATE_CLEAR, -1);
	end
	return true;
end