function CEOver_Init()	
end

function CEOver_SetBG()
end

function CEOver_SetSelect(selsysoverid, select)
	
	local replaymode, replayend = hdss.Get(HDSS_REPLAYMODE);
	
	local ystart = TotalCenterY;
	if not replaymode then
		ystart = ystart - 36;
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
	for i=0, 4 do
		if replaymode and (i == 1 or i == 3) then
			continue;
		end
		
		local flag = SEL_NULL;
		local y = ystart + yoffset * nselect;
		if i == 4 then
			flag = SEL_NONACTIVE;
			y = ystart - yoffset * 1.5;
		end
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsysoverid, nselect, SI_Pause_ResetGame+i, TotalCenterX, y, 1, 0, flag
			},
			tableSelectOffset
		)
		nselect = nselect + 1;
	end
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsysoverid, nselect-1, 1, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		}
	)
end

function CEOver_CloseUsed()
	hdssSELCLEAR(LConst_selsys_overid);
end

function CEOver_ExitState(tostate)
	CEOver_CloseUsed();
	hdssSETSTATE(tostate);
	if tostate == STATE_START then
		hdssSTARTPREP();
	end
end

function CEOver_DispatchSelect(selsysoverid, tostate)
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysoverid);
	if complete then
		return select;
	end
	return -1;
end

function ControlExecute_cOver(timer)

	local dselcomplete = RESERVEBEGIN;
	local dselselect = RESERVEBEGIN + 1;
	
	if timer == 1 then
		CEOver_Init();
		hdssSD(dselcomplete, 0);
		CEOver_SetBG();
	else
		local _selcomplete = hdss.Get(HDSS_D, dselcomplete);
		if _selcomplete == 0 then
			CEOver_SetSelect(LConst_selsys_overid, _selselect);
			_selcomplete = 1;
		elseif _selcomplete == 1 then
			local ret = CEOver_DispatchSelect(LConst_selsys_overid, timer-0xff00);
			local replaymode, replayend = hdss.Get(HDSS_REPLAYMODE);
			if ret >= 0 then
				if ret == 0 then
					CEOver_ExitState(STATE_START);
				elseif ret == 1 then
					if replaymode then
						CEOver_ExitState(STATE_REPLAY);
					else
						CEOver_ExitState(STATE_PLAYER_SELECT);
					end
				elseif ret == 2 then
					CEOver_ExitState(STATE_TITLE);
				else
					hdssSAVEREPLAY();
					CEOver_ExitState(STATE_TITLE);
				end
			end
		end
		hdssSD(dselcomplete, _selcomplete);
	end
		
	return true;

end