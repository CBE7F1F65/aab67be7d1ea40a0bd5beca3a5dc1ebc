function CEMatchSelect_Init()
	hdssMUSICCHANGE(LConst_musicid_title);
end

function CEMatchSelect_SetBG()
end

function CEMatchSelect_CloseUsed(selsysmatchid, selsyslatencyid, bbottom)
	--Close
	if bbottom == nil then
		bbottom = true;
	end
	--Clear
	hdssSELCLEAR(selsysmatchid, selsyslatencyid);
end

function CEMatchSelect_SetSelect_Match(selsysmatchid)
	--Select
	local x = TotalCenterX;
	local ybottomcenter = 440;
	local yoffset = 64;
	local ystart = TotalCenterY - yoffset;
	
	local _siusetable =
	{
--		SI_MatchSelect_N2N,
		SI_MatchSelect_P2P,
		SI_MatchSelect_P2C,
		SI_MatchSelect_C2P
	}
	for j, it in pairs(_siusetable) do
		local i = j-1;
		local y = ystart + i * yoffset;
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsysmatchid, i, it, x, y
			},
			{
				0, 0,
				-4, -4,
				0, ybottomcenter - y,
				8, 8
			}
		)
	end
	
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsysmatchid, 3, 0, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		}
	)
end

function CEMatchSelect_DispatchSelect_Match(selsysmatchid)
	--SelectOver
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysmatchid);
	if complete then
		CEMatchSelect_ExitState(STATE_PLAYER_SELECT, false);
	elseif hdss.Get(HDSS_CHECKKEY, 0, KSI_QUICK, DIKEY_DOWN) then
		hdssSE(SE_SYSTEM_CANCEL);
		CEMatchSelect_ExitState(STATE_TITLE);
	end
	return false;
end

function CEMatchSelect_SetBG_Waiting()
end

function CEMatchSelect_DispatchPasteIP(selsyslatencyid, _ipx, _ipport)
	
end

function CEMatchSelect_SetBG_Accessing()
	hdssSE(SE_SYSTEM_OK);
end

function CEMatchSelect_DisplayIP(ipx, ipport)
	local ipd0, ipd1, ipd2, ipd3 = global.GetARGB(ipx);
	local strip = string.format("%d.%d.%d.%d:%d", ipd0, ipd1, ipd2, ipd3, ipport);
	hdss.Call(
		HDSS_PRINT,
		{
			TotalCenterX, TotalCenterY, strip
		},
		{
			1.5
		}
	)
end

function CEMatchSelect_ExitState(tostate, bbottom)
	hdssSETSTATE(tostate);
	CEMatchSelect_CloseUsed(LConst_selsys_matchid, LConst_selsys_latencyid, bbottom);
end

function ControlExecute_cMatchSelect(timer)

	local dselcomplete = RESERVEBEGIN;
	local dipx = RESERVEBEGIN + 1;
	local dipport = RESERVEBEGIN + 2;
	local dlatency = RESERVEBEGIN + 3;
	
	if timer == 1 then
		CEMatchSelect_Init();
		hdssSD(dselcomplete, 0);
		hdssSDf(dipx, 0);
		hdssSD(dipport, 0);
		hdssSD(dlatency, 0);
		CEMatchSelect_SetBG();
	end
	
	local _selcomplete = hdss.Get(HDSS_D, dselcomplete);
	local _ipx = hdss.Get(HDSS_D, dipx);
	local _ipport = hdss.Get(HDSS_D, dipport);
	local _latency = hdss.Get(HDSS_D, dlatency);
	
	if _selcomplete == 0 then
		CEMatchSelect_CloseUsed(LConst_selsys_matchid, LConst_selsys_latencyid);
		CEMatchSelect_SetSelect_Match(LConst_selsys_matchid);
		_selcomplete = 1;
		
	elseif _selcomplete == 1 then
		if CEMatchSelect_DispatchSelect_Match(LConst_selsys_matchid) then
			_selcomplete = 2;
		end
	
	elseif _selcomplete == 2 then
		CEMatchSelect_SetBG_Waiting();
		_selcomplete = 3;
	
	elseif _selcomplete == 3 then
		_selcomplete = 4;
		
	elseif _selcomplete == 4 then
		CEMatchSelect_SetBG_Accessing();
		_selcomplete = 5;
	
	elseif _selcomplete == 5 then
		_selcomplete = 6;
	
	elseif _selcomplete == 6 then
		_selcomplete = 7;
	
	elseif _selcomplete == 7 then
	end
	
	
	hdssSD(dselcomplete, _selcomplete);
	hdssSDf(dipx, _ipx);
	hdssSD(dipport, _ipport);
	hdssSD(dlatency, _latency);
		
	return true;

end