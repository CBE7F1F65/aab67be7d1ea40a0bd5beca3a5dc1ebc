function CEReplay_Init()
	hdssMUSICCHANGE(LConst_musicid_title);
end

function CEReplay_SetBG()
	--Mask
	hdssBGVALUE(0, UBGID_BGMASK, SI_White, TotalCenterX, TotalCenterY, TotalW, TotalH, global.ARGB(0xFF, 0));
	--BG
	hdssBGVALUE(0, LConst_uibg_backgroundid, SI_ReplayScene, TotalCenterX, TotalCenterY, TotalW, TotalH);
	--Fade
	hdssBGFLAG(0, UBGID_BGMASK, BG_FADEOUT);
end

function CEReplay_CloseUsed()
end

function CEReplay_ExitState(tostate)
	CEReplay_CloseUsed();
	hdssSETSTATE(tostate);
end

function CEReplay_SetSelect(selsysreplayid, dnselect, pushkeyid)
	local rpyindex = 0;
	local rpyname = "";
	
	local x = 96;
	local ystart = 96;
	local yoffset = 32;

	local tableSelectOffset =
	{
		0, 0,
		-4, -1,
		-4, 0,
		4, 4
	}
	
	local dcol = global.ARGB(0xff, 0xff8000);
	
	while true do
		rpyname, rpyinfotable = game.GetEnumReplayInfo(rpyindex);
		if rpyname == "" then
			break;
		end
		
		local year = math.mod(rpyinfotable.year, 100);
		local month = rpyinfotable.month;
		local day = rpyinfotable.day;
		local username = rpyinfotable.username;
		local usingchara = rpyinfotable.usingchara;
		local strname = string.format("%02d    %02d/%02d/%02d    %s\n  %s %s vs %s %s", rpyindex+1, year, month, day, rpyname, username[1], usingchara[1][1], username[2], usingchara[2][1]);
		local y = ystart + rpyindex * yoffset;
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsysreplayid, rpyindex, -1, x, y
			},
			tableSelectOffset,
			{
				strname, LConst_selsys_ucol, dcol, LConst_selsys_shadow, 0, 0, 0.75, 0, LConst_selsys_align_left
			}
		)
		rpyindex = rpyindex + 1;
	end
	
	hdssSD(dnselect, rpyindex);
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsysreplayid, rpyindex, 0, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		},
		{
			12, ystart, yoffset, 0
		}
	)
	hdssSETPUSHEVENT(pushkeyid, 0, KSI_LEFT, KSI_RIGHT, PUSHKEY_KEYNULL, PUSHKEY_KEYNULL);
	
end

function CEReplay_DispatchSelect(selsysreplayid, nselect, pushkeyid)
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysreplayid);
	if complete then
		game.SetEnumReplayByIndex(select);
		hdssSTARTPREP();
		CEReplay_ExitState(STATE_START);
	end
	
	if hdss.Get(HDSS_CHECKKEY, 0, KSI_QUICK, DIKEY_DOWN) then
		hdssSE(SE_SYSTEM_CANCEL);
		CEReplay_ExitState(STATE_TITLE);
	end
	
	hdssUPDATEPUSHEVENT(pushkeyid);
	
	if hdss.Get(HDSS_CHECKKEY, 0, KSI_RIGHT, DIKEY_DOWN) then
		select = select + 10;
		if select >= nselect then
			select = nselect - 1;
		end
		hdssSELSET(selsysreplayid, select);
		hdssSE(SE_SYSTEM_SELECT);
	elseif hdss.Get(HDSS_CHECKKEY, 0, KSI_LEFT, DIKEY_DOWN) then
		select = select - 10;
		if select < 0 then
			select = 0;
		end
		hdssSELSET(selsysreplayid, select);
		hdssSE(SE_SYSTEM_SELECT);
	end
end

function ControlExecute_cReplay(timer)
	
	local dnselect = RESERVEBEGIN;
	if timer == 1 then
		CEReplay_Init();
		hdssSD(dnselect, 0);
		CEReplay_SetBG();
		CEReplay_SetSelect(LConst_selsys_replayid, dnselect, PUSHID_UIUSE_0);
	end
	local _nselect = hdss.Get(HDSS_D, dnselect);
	CEReplay_DispatchSelect(LConst_selsys_replayid, _nselect, PUSHID_UIUSE_0);
end