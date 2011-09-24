function CETitle_Init()
	game.FreeTexture();
	hdssMUSICCHANGE(LConst_musicid_title);
end

function CETitle_SetBG()
	hdssBGVALUE(0, UBGID_BGMASK, SI_White, TotalCenterX, TotalCenterY, TotalW, TotalH, global.ARGB(0xFF, 0));
	hdssBGVALUE(0, LConst_uibg_backgroundid, SI_TitleScene, TotalCenterX, TotalCenterY, TotalW, TotalH);
	hdssBGFLAG(0, UBGID_BGMASK, BG_FADEOUT);
end

function CETitle_SetupSelect(selsysid)
	local tableSelectOffset =
	{
			0, 0,
			-4, -4,
			-8, 0,
			8, 8
	}
	
	local x = 480;
	local ystart = 240;
	local yoffset = 30;
	local infox = 320;
	local infoy = 440;
	
	local _siusetable =
	{
		{SI_Title_Start},
--		{SI_Title_Replay},
--		{SI_Title_Quit}
	}
	for j, it in pairs(_siusetable) do
		local i = j-1;
		local y = ystart + i * yoffset;
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsysid, i, it[1], x, y
			},
			tableSelectOffset
		)
	end
	
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsysid, 1, 0, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		}
	)
end

function CETitle_ExitState(tostate)
	hdssSETSTATE(tostate)
end

function CETitle_DispatchSelect(selsysid)
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsysid);
	if complete then
		CETitle_ExitState(STATE_MATCH_SELECT);
	end
end

function ControlExecute_cTitle(timer)

	local selsysid = LConst_selsys_titleid;
	
	if timer == 1 then
		CETitle_Init();
		--
		if _DEBUG_MatchAndLog > 0 then
			_DEBUG_NewRandomMatch();
			return true;
		end
		--
		CETitle_SetBG();
		CETitle_SetupSelect(LConst_selsys_titleid);
	end
	
	CETitle_DispatchSelect(LConst_selsys_titleid);
	
	if _DEBUG then
		if hge.Input_GetDIKey(DIK_NUMPAD4, DIKEY_DOWN) then
			_DEBUG_LGlobal_Jump = MatchMode_P2C;
		end
		if hge.Input_GetDIKey(DIK_NUMPAD5, DIKEY_DOWN) then
			_DEBUG_LGlobal_Jump = MatchMode_C2P;
		end
		if hge.Input_GetDIKey(DIK_NUMPAD6, DIKEY_DOWN) then
			_DEBUG_LGlobal_Jump = MatchMode_P2P;
		end
--		if hge.Input_GetDIKey(DIK_NUMPAD7, DIKEY_DOWN) then
--			_DEBUG_LGlobal_Jump = MatchMode_N2N;
--		end
		if _DEBUG_LGlobal_Jump ~= -1 then
			game.SetMatchMode(_DEBUG_LGlobal_Jump);
			for i=0, 1 do
				local nowID, lastID, lastID_Sub_1, lastID_Sub_2, lastMatchID, lastMatchID_Sub_1, lastMatchID_Sub_2 = hdss.Get(HDSS_CHARA, i);
				hdssSETCHARA(i, lastMatchID, lastMatchID_Sub_1, lastMatchID_Sub_2);
				hdssSETPINITLIFE(i, 10);
			end
			hdssSETSCENE(hdss.Get(HDSS_CHARA, RANDT(0, 1)));
			hdssSTARTPREP();
			_DEBUG_LGlobal_Jump = -1;
			CETitle_ExitState(STATE_START);
		end
	end
	
	return true;

end