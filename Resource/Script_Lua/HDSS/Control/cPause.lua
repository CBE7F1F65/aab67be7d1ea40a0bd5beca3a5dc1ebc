function CEPause_Init()
end

function CEPause_SetBG()
end

function CEPause_SetSelect(selsyspauseid, select)
	
	local replaymode, replayend = hdss.GetReplayMode();
	
	local ystart = TotalCenterY;
	if not replaymode then
		ystart = ystart - 48;
	end
	local yoffset = 36;

	local tableSelectOffset =
	{
		0, 0,
		-4, -4,
		-8, 0,
		8, 8
	}
	
	local nselect = 0;
	for i=0, 5 do
		if replaymode and (i == 2 or i == 4) then
			continue;
		end
		
		local flag = SEL_NULL;
		local y = ystart + yoffset * nselect;
		
		if i == 5 then
			flag = SEL_NONACTIVE;
			y = ystart - yoffset * 1.5;
		end
		hdss.BuildSelect(
			{
				selsyspauseid, nselect, SI_Pause_Start+i, TotalCenterX, y, 1, 0, flag
			},
			tableSelectOffset
		)
		nselect = nselect + 1;
	end
	hdss.SetupSelect(
		{
			selsyspauseid, nselect-1, select, KSI_UP, KSI_DOWN, KSI_FIRE
		}
	)
end

function CEPause_CloseUsed()
	hdss.ReleaseSelect(LConst_selsys_pauseid);
	hdss.ReleaseSelect(LConst_selsys_pauseconfirmid);
end

function CEPause_ExitState(tostate, bPrep)
	CEPause_CloseUsed();
	local time = 0;
	if bPrep == nil then
		bPrep = false;
	end
	if not bPrep and tostate == STATE_START then
		time = -1;
	end
	hdss.SetState(tostate, time);
	if bPrep then
		hdss.CallStartPrep();
	end

	if tostate ~= STATE_START then
		game.FreeTexture();
		hdss.ClearAll();
	end
end

function CEPause_DispatchSelect(selsyspauseid, tostate)
	local complete, select = hdss.CheckSelect(selsyspauseid);
	if complete then
		if select == 0 then
			CEPause_ExitState(tostate);
		end
		return select;
	end
	
	if hdss.CheckInput(KSI_QUICK, DIKEY_UP) or hdss.CheckInput(KSI_PAUSE, DIKEY_DOWN) then
		hdss.PlaySE(SE_SYSTEM_CANCEL);
		CEPause_ExitState(tostate);
	end
	return 0;
end

function CEPause_SetConfirmSelect(selsyspauseconfirmid)
	
	local ystart = TotalCenterY;
	local yoffset = 36;

	local tableSelectOffset =
	{
		0, 0,
		-4, -4,
		-8, 0,
		8, 8
	}
	
	for i=0, 2 do
		local flag = SEL_NULL;
		local y = ystart + yoffset * i;
		if i == 2 then
			flag = SEL_NONACTIVE;
			y = ystart - yoffset * 1.5;
		end
		hdss.BuildSelect(
			{
				selsyspauseconfirmid, i, SI_Confirm_Yes+i, TotalCenterX, y, 1, 0, flag
			},
			tableSelectOffset
		)
	end
	hdss.SetupSelect(
		{
			selsyspauseconfirmid, 2, 1, KSI_UP, KSI_DOWN, KSI_FIRE
		}
	)
end

function CEPause_DispatchConfirmSelect(selsyspauseconfirmid)
	local complete, select = hdss.CheckSelect(selsyspauseconfirmid);
	if complete then
		if select == 0 then
			return 1;
		else
			return -1;
		end
	end
	
	if hdss.CheckInput(KSI_QUICK, DIKEY_UP) then
		hdss.PlaySE(SE_SYSTEM_CANCEL);
		hdss.ReleaseSelect(selsyspauseconfirmid);
		return -1;
	end
	return 0;
end

function ControlExecute_cPause(timer)

	local dselcomplete = RESERVEBEGIN;
	local dselselect = RESERVEBEGIN + 1;
	
	if timer == 0 then
		CEPause_Init();
		hdss.SetDesc(dselcomplete, 0);
		hdss.SetDesc(dselselect, 0);
		CEPause_SetBG();
	else
		local _selcomplete = hdss.GetDesc(dselcomplete);
		local _selselect = hdss.GetDesc(dselselect);
		if _selcomplete == 0 then
			CEPause_SetSelect(LConst_selsys_pauseid, _selselect);
			_selcomplete = 1;
		elseif _selcomplete == 1 then
			_selselect = CEPause_DispatchSelect(LConst_selsys_pauseid, timer-0xff00);
			if _selselect > 0 then
				_selcomplete = 2;
			end
		elseif _selcomplete == 2 then
			CEPause_SetConfirmSelect(LConst_selsys_pauseconfirmid);
			_selcomplete = 3;
		elseif _selcomplete == 3 then
			local ret = CEPause_DispatchConfirmSelect(LConst_selsys_pauseconfirmid);
			local replaymode, replayend = hdss.GetReplayMode();
			if ret > 0 then
				if _selselect == 1 then
					CEPause_ExitState(STATE_START, true);
				elseif _selselect == 2 then
					if replaymode then
						CEPause_ExitState(STATE_REPLAY);
					else
						CEPause_ExitState(STATE_PLAYER_SELECT);
					end
				elseif _selselect == 3 then
					CEPause_ExitState(STATE_TITLE);
				else
					CEPause_ExitState(STATE_TITLE);
				end
			elseif ret < 0 then
				_selcomplete = 0;
			end
		end
		hdss.SetDesc(dselcomplete, _selcomplete);
		hdss.SetDesc(dselselect, _selselect);
	end
		
	return true;

end