function CESceneSelect_Init()
	hdssMUSICCHANGE(LConst_musicid_title);
end

function CESceneSelect_SetBG()
	hdssBGVALUE(0, LConst_uibg_backgroundid, SI_SelectScene, TotalCenterX, TotalCenterY, TotalW, TotalH);
	hdssBGVALUE(0, LConst_uibg_topcontentid, SI_TopContent_Scene, TotalCenterX, 64);
end

function CESceneSelect_SetSelect(selsyssceneid, pushkeyid)
	local scenecount = game.GetSceneContentTable();
	
	local ystart = 120;
	local yoffset = 24;

	local tableSelectOffset =
	{
		0, 0,
		-4, -4,
		-8, 0,
		8, 8
	}

	local scale = 1.5;

	hdss.Call(
		HDSS_SELBUILD,
		{
			selsyssceneid, 0, SI_SceneName_Default, TotalCenterX, ystart, scale
		},
		tableSelectOffset
	)
	hdss.Call(
		HDSS_SELBUILD,
		{
			selsyssceneid, 1, SI_SceneName_Random, TotalCenterX, ystart + yoffset, scale
		},
		tableSelectOffset
	)


	for i=0, scenecount-1 do
		
		local j = i+1;
		local ucol = global.HSVA(j/(scenecount+2), 1, 1, 1);
		local dcol = global.HSVA((j+1)/(scenecount+2), 1, 1, 1);
		local scenename = game.GetSceneContentTable(i);
		
		hdss.Call(
			HDSS_SELBUILD,
			{
				selsyssceneid, i+2, SI_SceneName_01+i, TotalCenterX, ystart + (i+2) * yoffset, scale
			},
			tableSelectOffset
		)
	end
	hdss.Call(
		HDSS_SELSETUP,
		{
			selsyssceneid, scenecount+2, 0, 0, KSI_UP, KSI_DOWN, KSI_FIRE
		},
		{
			12, ystart, yoffset
		},
		{
			SI_Select_Frame, TotalCenterX, ystart
		}
	)
	hdssSETPUSHEVENT(pushkeyid, 0, KSI_DRAIN, PUSHKEY_KEYNULL, PUSHKEY_KEYNULL, PUSHKEY_KEYNULL, 2, 0);
end

function CESceneSelect_CloseUsed()
	hdssBGOFF(0, LConst_uibg_player1id, LConst_uibg_player2id);
	for i=0, 11 do
		hdssFREEFRONTSPRITE(i);
	end
	hdssSELCLEAR(LConst_selsys_sceneid);
end

function CESceneSelect_ExitState(tostate)
	CESceneSelect_CloseUsed();
	hdssSETSTATE(tostate);
	if tostate == STATE_START then
		game.FreeTexture();
		hdssSTARTPREP();
	end
end

function CESceneSelect_DispatchSelect(selsyssceneid, pushkeyid)
	local complete, select = hdss.Get(HDSS_SELCOMPLETE, selsyssceneid);
	if complete then
		local scene = select;
		if select == 0 then
			scene = hdss.Get(HDSS_CHARA, RANDT(0, 1));
		elseif select == 1 then
			scene = RANDT(0, game.GetSceneContentTable()-1);
		else
			scene = scene - 2;
		end
		hdssSETSCENE(scene);
		CESceneSelect_ExitState(STATE_START);
	end
	
	hdssUPDATEPUSHEVENT(pushkeyid);

	if hdss.Get(HDSS_CHECKKEY, 0, KSI_QUICK, DIKEY_DOWN) then
		hdssSE(SE_SYSTEM_CANCEL);
		CESceneSelect_ExitState(STATE_PLAYER_SELECT);
	elseif hdss.Get(HDSS_CHECKKEY, 0, KSI_DRAIN, DIKEY_DOWN) then
		hdssSELSET(selsyssceneid);
	end
end

function ControlExecute_cSceneSelect(timer)

	if timer == 1 then
		CESceneSelect_Init();
		CESceneSelect_SetBG();
		CESceneSelect_SetSelect(LConst_selsys_sceneid, PUSHID_UIUSE_0);
	end
	
	CESceneSelect_DispatchSelect(LConst_selsys_sceneid, PUSHID_UIUSE_0);
		
	return true;

end