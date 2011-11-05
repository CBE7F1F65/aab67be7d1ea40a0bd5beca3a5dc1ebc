function ControlExecute_cStart(timer)
	if timer == 1 then
		
		local scene = hdss.GetStage();
		local col = global.ARGB(0xff, 0);
		local baseangle = Math_ArcToAngle(math.atan2(TotalH, TotalW));
		local enemyrandrom = RANDT();
		hdss.SetDesc(LConst_Desc_LilyItem, helper_GetRandomItem());
		
		for i=0, 1 do
			
			hdss.SetDesc(LConst_Desc_EnemyTimeCounter+i, 0);
			hdss.SetDesc(LConst_Desc_EnemyRandom+i, enemyrandrom);
			helper_GetNextEnemyRandom(i);
						
		end
		
		--
		
	elseif timer == 32 then
	end
				
	if timer <= 8 then
		local scale = Math_Inter(1.5, 1, timer/8);
	elseif timer == 32 then
	elseif timer > 48 and timer <= 56 then
		local scale = Math_Inter(1.5, 1, (timer-48)/8);
	elseif timer == 80 then
	elseif timer == 96 then
		
	elseif timer > 96 then

		for i=0, 1 do
			local enemytimecounter = hdss.GetDesc(LConst_Desc_EnemyTimeCounter+i);
			local nowlinenum = hdss.GetDesc(LConst_Desc_EnemyNowLineNum+i);
			local bdrain = false;
			local bhaveenemy = hdss.GetAllEnemiesInfo(1) > 0 or hdss.GetAllEnemiesInfo(2) > 0;
			if nowlinenum <= 0 and bdrain and bhaveenemy then
				enemytimecounter = LConst_EnemyMergeInterval - 1;
			else
				enemytimecounter = enemytimecounter + 1;
			end
			if enemytimecounter >= LConst_EnemyMergeInterval then
				local nowline = hdss.GetDesc(LConst_Desc_EnemyNowLine+i);
				local nowpattern = math.floor(nowline / 2);
				local nowdirection = math.mod(nowline, 2);
				if nowlinenum > 0 then
					local type, x, y, startangle, addangle, addtimebegin, addtimeend, life = helper_GetEnemyBasicData(nowpattern, nowlinenum, nowdirection, i);
					hdss.BuildEnemy(
						{
							type, x, y, startangle, 2.0, type, life
						}
					);
				end
				nowlinenum = nowlinenum - 1;
				if nowlinenum <= 0 then
					if bdrain and bhaveenemy then
						hdss.SetDesc(LConst_Desc_EnemyNowLineNum+i, 0);
					else
						helper_GetNextEnemyRandom(i);
					end
				else
					hdss.SetDesc(LConst_Desc_EnemyNowLineNum+i, nowlinenum);
				end
				enemytimecounter = 0;
			end
			hdss.SetDesc(LConst_Desc_EnemyTimeCounter+i, enemytimecounter);
		end
	end
		
	if hdss.CheckInput(KSI_PAUSE, DIKEY_DOWN) and hdss.GetState() ~= STATE_CLEAR then
		hdss.PlaySE(SE_SYSTEM_PAUSE);
		hdss.SetState(STATE_PAUSE, -1);
	end
		
	if _DEBUG then
		if hge.Input_GetDIKey(DIK_NUMPAD0, DIKEY_DOWN) then
			local binfi = hdss.Get(HDSS_PBINFI);
			if binfi then
				hdss.TogglePlayerInfi(0, 0);
			else
				hdss.TogglePlayerInfi(0);
			end
		end
		if hge.Input_GetDIKey(DIK_NUMPAD1, DIKEY_DOWN) then
			local binfi = hdss.CheckPlayerInfi();
			if binfi then
				hdss.TogglePlayerInfi(0, 0);
			else
				hdss.TogglePlayerInfi(0);
			end
		end
		if hge.Input_GetDIKey(DIK_NUMPAD7, DIKEY_DOWN) then
			hdss.SetPlayerTemper(-10000);
		end
		if hge.Input_GetDIKey(DIK_NUMPAD8, DIKEY_DOWN) then
			hdss.SetPlayerTemper(10000);
		end
	end
		
	return true;

end