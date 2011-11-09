function Scene_CheckPointXOver(val, x, lastx, step, stepdesc)
	local bret = false;
	if step == stepdesc then
		if x >= val and val > lastx then
			bret = true;
			stepdesc = Scene_SaveStepDesc(step+1);
		end
	end
	return bret, step+1, stepdesc;
end

function Scene_CheckPointXBelow(val, x, lastx, step, stepdesc)
	local bret = false;
	if step == stepdesc then
		if x <= val and val < lastx then
			bret = true;
			stepdesc = Scene_SaveStepDesc(step+1);
		end
	end
	return bret, step+1, stepdesc;
end

function Scene_CheckPointYOver(val, y, lasty, step, stepdesc)
	local bret = false;
	if step == stepdesc then
		if y >= val and val > lasty then
			bret = true;
			stepdesc = Scene_SaveStepDesc(step+1);
		end
	end
	return bret, step+1, stepdesc;
end

function Scene_CheckPointYBelow(val, y, lasty, step, stepdesc)
	local bret = false;
	if step == stepdesc then
		if y <= val and val < lasty then
			bret = true;
			stepdesc = Scene_SaveStepDesc(step+1);
		end
	end
	return bret, step+1, stepdesc;
end

function Scene_SaveStepDesc(step)
	hdss.SetDesc(LConst_Desc_StageAreaCheckPoint, step);
	return step;
end

function Scene_s00(timer)
	
	local mapcenx, mapceny, lastcenx, lastceny, xspeed, yspeed, mapxoffset = hdss.GetMapSpeedInfo();
	local stepdesc = hdss.GetDesc(LConst_Desc_StageAreaCheckPoint);

	if timer == 1 then
		hdss.SetupBG(176);
		hdss.SetMapSpeedInfo(xspeed, 0);
		Scene_SaveStepDesc(0);
		hdss.BuildEnemy(
			{
				36, 160, 60, 0, 0.0, 36, 9999999
			}
		)
	elseif timer == 120 then
		hdss.SetMapSpeedInfo(xspeed, 3.6);
	elseif timer >120 and timer < 180 then
		hdss.SetMapSpeedInfo(xspeed, yspeed-0.048);
	end
		
	local bret = false;
	local step = 0;
	
	bret, step, stepdesc = Scene_CheckPointYOver(1664, mapceny, lastceny, step, stepdesc);
	if bret then
		hdss.SetMapSpeedInfo(1.5, 0);
	end
	
	bret, step, stepdesc = Scene_CheckPointXOver(768, mapcenx, lastcenx, step, stepdesc);
	if bret then
		hdss.SetMapSpeedInfo(0, 1.0);
	end
	
	bret, step, stepdesc = Scene_CheckPointYOver(2560, mapceny, lastceny, step, stepdesc);
	if bret then
		hdss.SetMapSpeedInfo(-1.5, 0);
	end
	
	bret, step, stepdesc = Scene_CheckPointXBelow(176, mapcenx, lastcenx, step, stepdesc);
	if bret then
		hdss.SetMapSpeedInfo(0, 1.5);
	end
	
--	if mapceny >= 1664 and lastceny > 1664 and mapcenx == lastcenx then
--		hdss.SetMapSpeedInfo(1.5, 0);

--	elseif mapcenx >= 768 and lastcenx < 768 and mapceny == lastceny then
--		hdss.SetMapSpeedInfo(0, 0.5);
--	elseif mapceny >= 2560 and lastceny < 2560 and mapcenx == lastcenx then
--		hdss.SetMapSpeedInfo(-1.5, 0);
--	elseif mapcenx <= 176 and lastcenx > 176 and mapceny == lastceny and mapceny >= 2560 then
--		hdss.SetMapSpeedInfo(0, 0.5);

--	elseif timer == 850 then
--		hdss.SetMapSpeedInfo(1.5, 0);
--	elseif timer == 1200 then
--		hdss.SetMapSpeedInfo(0, 0);
--		hdss.SetState(STATE_CLEAR, -1);
--	end
	
	return true;
end