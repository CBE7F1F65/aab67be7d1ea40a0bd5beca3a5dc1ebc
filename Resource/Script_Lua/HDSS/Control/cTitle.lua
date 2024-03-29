function CETitle_Init()
	game.FreeTexture();
	hdss.ChangeMusic(LConst_musicid_title);
end

function CETitle_SetBG()
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
		hdss.BuildSelect(
			{
				selsysid, i, it[1], x, y
			},
			tableSelectOffset
		)
	end
	
	hdss.SetupSelect(
		{
			selsysid, 1, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		}
	)
end

function CETitle_ExitState(tostate)
	hdss.SetState(tostate)
end

function CETitle_DispatchSelect(selsysid)
	local complete, select = hdss.CheckSelect(selsysid);
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
			_DEBUG_LGlobal_Jump = 1;
		end
		if _DEBUG_LGlobal_Jump == 1 then
			_DEBUG_NewRandomMatch();
		end
	end
	
	return true;

end