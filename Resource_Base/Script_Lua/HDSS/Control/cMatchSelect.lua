function CEMatchSelect_Init()
	hdssMUSICCHANGE(LConst_musicid_title);
end

function CEMatchSelect_SetBG()
	--Mask
	hdssBGVALUE(0, UBGID_BGMASK, SI_White, TotalCenterX, TotalCenterY, TotalW, TotalH, global.ARGB(0xFF, 0));
	--BG
	hdssBGVALUE(0, LConst_uibg_backgroundid, SI_SelectScene, TotalCenterX, TotalCenterY, TotalW, TotalH);
	--TopContent
	hdssBGVALUE(0, LConst_uibg_topcontentid, SI_TopContent_MatchMode, TotalCenterX, 96);
	--Fade
	hdssBGFLAG(0, UBGID_BGMASK, BG_FADEOUT);
end

function CEMatchSelect_CloseUsed(selsysmatchid, selsyslatencyid, bbottom)
	--Close
	if bbottom == nil then
		bbottom = true;
	end
	if bbottom then
		hdssBGOFF(0, LConst_uibg_bottomid);
	end
	hdssBGOFF(0, LConst_uibg_infoid);
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
--		if select == 0 then
--			game.SetMatchMode(MatchMode_N2N);
--			return true;
--		else
		if select == 0 then
			hdssBGVALUE(0, LConst_uibg_bottomid, SI_MatchSelect_P2P, TotalCenterX, 440);
			game.SetMatchMode(MatchMode_P2P);
		elseif select == 1 then
			hdssBGVALUE(0, LConst_uibg_bottomid, SI_MatchSelect_P2C, TotalCenterX, 440);
			game.SetMatchMode(MatchMode_P2C);
		elseif select == 2 then
			hdssBGVALUE(0, LConst_uibg_bottomid, SI_MatchSelect_C2P, TotalCenterX, 440);
			if hdss.Get(HDSS_CHECKKEY, 0, KSI_SLOW) or hdss.Get(HDSS_CHECKKEY, 1, KSI_SLOW) then
				game.SetMatchMode(MatchMode_C2C);
			else
				game.SetMatchMode(MatchMode_C2P);
			end
		end
		CEMatchSelect_ExitState(STATE_PLAYER_SELECT, false);
	elseif hdss.Get(HDSS_CHECKKEY, 0, KSI_QUICK, DIKEY_DOWN) then
		hdssSE(SE_SYSTEM_CANCEL);
		CEMatchSelect_ExitState(STATE_TITLE);
	end
	return false;
end

function CEMatchSelect_SetBG_Waiting()
	hdssBGVALUE(0, LConst_uibg_bottomid, SI_MatchSelect_N2N, TotalCenterX, 440);
	hdssBGVALUE(0, LConst_uibg_infoid, SI_MatchMode_Waiting, TotalCenterX, 200, 384, 60);
end

function CEMatchSelect_DispatchPasteIP(selsyslatencyid, _ipx, _ipport)
	
	local ret = 0;
	local retipx = 0;
	local retipport = 0;
	if hge.Input_GetKeyState(HGEK_CTRL) and hge.Input_GetKeyState(HGEK_V) then
		local strclipboard = global.GetClipBoard();
		
		local ipd0, ipd1, ipd2, ipd3, ipport;
		local stristart = 1;
		local striend = 1;
		stristart, striend = string.find(strclipboard, "%d+", stristart);
		if stristart ~= nil then
			ipd0 = string.sub(strclipboard, stristart, striend);
			stristart = striend + 1;
			stristart, striend = string.find(strclipboard, "%d+", stristart);
			if stristart ~= nil then
				ipd1 = string.sub(strclipboard, stristart, striend);
				stristart = striend + 1;
				stristart, striend = string.find(strclipboard, "%d+", stristart);
				if stristart ~= nil then
					ipd2 = string.sub(strclipboard, stristart, striend);
					stristart = striend + 1;
					stristart, striend = string.find(strclipboard, "%d+", stristart);
					if stristart ~= nil then
						ipd3 = string.sub(strclipboard, stristart, striend);
						stristart = striend + 1;
						stristart, striend = string.find(strclipboard, "%d+", stristart);
						if stristart ~= nil then
							ipport = string.sub(strclipboard, stristart, striend);
						end
							
						if ipport == nil then
							ipport = M_DEFAULTIPPORT;
						end
						ipd0 = tonumber(ipd0);
						ipd1 = tonumber(ipd1);
						ipd2 = tonumber(ipd2);
						ipd3 = tonumber(ipd3);
						ipport = tonumber(ipport);
					
						if ipd0 >= 1 and ipd0 <= 0xFF and
							ipd1 >= 0 and ipd1 <= 0xFF and
							ipd2 >= 0 and ipd2 <= 0xFF and
							ipd3 >= 0 and ipd3 <= 0xFF then
							
							if ipport >= 0 and ipport <= 0xFFFF then
								retipx = global.ARGB(ipd0, ipd1, ipd2, ipd3);
								retipport = ipport;
								game.SetLastIP(retipx, retipport);
								ret = 1;
							end
								
						end
					end
				end
			end
		end
		
	elseif hdss.Get(HDSS_CHECKKEY, 0, KSI_ENTER, DIKEY_DOWN) then
		retipx, retipport = game.GetLastIP();
		local ipd0, ipd1, ipd2, ipd3 = global.GetARGB(retipx);
		if ipd0 ~= 0 then
			ret = 1;
		end
	elseif hdss.Get(HDSS_CHECKKEY, 0, KSI_QUICK, DIKEY_DOWN) then
		hdssSE(SE_SYSTEM_CANCEL);
		ret = -1;
	end
	return ret, retipx, retipport;
end

function CEMatchSelect_SetBG_Accessing()
	hdssBGVALUE(0, LConst_uibg_infoid, SI_MatchMode_Accessing, TotalCenterX, 200, 384, 30);
	hdssSE(SE_SYSTEM_OK);
end

function CEMatchSelect_DispatchAccess()
	local latency = game.AccessIP();
	if latency < 0 then
		hdssSE(SE_SYSTEM_CANCEL);
	end
	return latency;
end

function CEMatchSelect_SetSelect_Latency(selsyslatencyid, latency)
	
	hdssBGVALUE(0, LConst_uibg_infoid, SI_MatchMode_Latency, TotalCenterX, 200, 384, 30);
	hdssSELCLEAR(selsyslatencyid);
	
	local x = TotalCenterX;
	local ystart = 320;
	local yoffset = 20;
	for i=0, 8 do
		local ucol = global.HSVA((i-1) * 0.1 + 0.2, 1, 1, 1);
		local dcol = global.HSVA(i * 0.1 + 0.2, 1, 1, 1);
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsyslatencyid, i, -1, x, ystart + i * yoffset
			},
			{
				0, 0,
				-4, -4,
				-8, 0,
				8, 8
			},
			{
				string.format("Latency:%d", i+1), ucol, dcol
			}
		)
	end
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsyslatencyid, 9, latency-1, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		},
		{
			1, ystart, yoffset, latency-1
		}
	)
	hdssSE(SE_SYSTEM_OK);
end

function CEMatchSelect_DispatchSelect_Latency(selsyslatencyid, latency)

	local ret = 0;
	if hdss.Get(HDSS_CHECKKEY, 0, KSI_QUICK, DIKEY_DOWN) then
		hdssSELCLEAR(selsyslatencyid);
		ret = -1;
	hdssSE(SE_SYSTEM_CANCEL);
	end
	
	--SelectOver
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsyslatencyid);
	if complete then
		latency = select + 1;
		game.SetLatency(latency);
		CEMatchSelect_ExitState(STATE_PLAYER_SELECT, false);
		ret = 1;
	end
	return ret;
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
		local ret, retipx, retipport = CEMatchSelect_DispatchPasteIP(LConst_selsys_latencyid);
		if ret == -1 then
			_selcomplete = 0;
		elseif ret == 1 then
			_ipx = retipx;
			_ipport = retipport;
			_selcomplete = 4;
		end
		
	elseif _selcomplete == 4 then
		CEMatchSelect_SetBG_Accessing();
		_selcomplete = 5;
	
	elseif _selcomplete == 5 then
		_latency = CEMatchSelect_DispatchAccess();
		if _latency < 0 then
			_selcomplete = 0;
		elseif _latency > 0 then
			_selcomplete = 6;
		end
	
	elseif _selcomplete == 6 then
		CEMatchSelect_SetSelect_Latency(LConst_selsys_latencyid, _latency);
		_selcomplete = 7;
	
	elseif _selcomplete == 7 then
		local ret = CEMatchSelect_DispatchSelect_Latency(LConst_selsys_latencyid)
		if ret == -1 then
			_selcomplete = 2;
		end
	end
	
	-- IP
	if _selcomplete > 3 then
		CEMatchSelect_DisplayIP(_ipx, _ipport);
	end
	
	hdssSD(dselcomplete, _selcomplete);
	hdssSDf(dipx, _ipx);
	hdssSD(dipport, _ipport);
	hdssSD(dlatency, _latency);
		
	return true;

end