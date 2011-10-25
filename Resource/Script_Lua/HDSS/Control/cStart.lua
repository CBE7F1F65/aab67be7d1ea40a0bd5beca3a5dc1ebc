function ControlExecute_cStart(timer)
	if timer == 1 then
		
		local scene = hdss.Get(HDSS_GETSCENE);
		local col = global.ARGB(0xff, 0);
		local baseangle = hdss.Get(HDSS_ATAN2, TotalH, TotalW);
		local enemyrandrom = RANDT();
		hdssSD(LConst_Desc_LilyItem, helper_GetRandomItem());
		
		for i=0, 1 do
			
			hdssSD(LConst_Desc_EnemyTimeCounter+i, 0);
			hdssSD(LConst_Desc_EnemyRandom+i, enemyrandrom);
			helper_GetNextEnemyRandom(i);
			
			hdssBGSETUP();
						
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
			local enemytimecounter = hdss.Get(HDSS_D, LConst_Desc_EnemyTimeCounter+i);
			local nowlinenum = hdss.Get(HDSS_D, LConst_Desc_EnemyNowLineNum+i);
			local bdrain = false;
			local bhaveenemy = hdss.Get(HDSS_ENNUM, i, 1) > 0 or hdss.Get(HDSS_ENNUM, i, 2) > 0;
			if nowlinenum <= 0 and bdrain and bhaveenemy then
				enemytimecounter = LConst_EnemyMergeInterval - 1;
			else
				enemytimecounter = enemytimecounter + 1;
			end
			if enemytimecounter >= LConst_EnemyMergeInterval then
				local nowline = hdss.Get(HDSS_D, LConst_Desc_EnemyNowLine+i);
				local nowpattern = math.floor(nowline / 2);
				local nowdirection = math.mod(nowline, 2);
				if nowlinenum > 0 then
					local type, x, y, startangle, addangle, addtimebegin, addtimeend, life = helper_GetEnemyBasicData(nowpattern, nowlinenum, nowdirection, i);
					hdssEB(type, i, x, y, startangle, 2.0, type, life);
					if addangle then
						hdssEA(i, ENAC_TURNANGLE_OOOOATOE,
							{
							},
							{
								addangle, addtimebegin, 0, addtimeend
							}
						)
					end
				end
				nowlinenum = nowlinenum - 1;
				if nowlinenum <= 0 then
					if bdrain and bhaveenemy then
						hdssSD(LConst_Desc_EnemyNowLineNum+i, 0);
					else
						helper_GetNextEnemyRandom(i);
					end
				else
					hdssSD(LConst_Desc_EnemyNowLineNum+i, nowlinenum);
				end
				enemytimecounter = 0;
			end
			hdssSD(LConst_Desc_EnemyTimeCounter+i, enemytimecounter);
		end
	end
		
	if hdss.Get(HDSS_CHECKKEY, 0, KSI_PAUSE, DIKEY_DOWN) and hdss.Get(HDSS_STATE) ~= STATE_CLEAR then
		hdssSE(SE_SYSTEM_PAUSE);
		hdssSETSTATE(STATE_PAUSE, -1);
	end
		
	if _DEBUG then
		if hge.Input_GetDIKey(DIK_NUMPAD0, DIKEY_DOWN) then
			local binfi = hdss.Get(HDSS_PBINFI, 0);
			if binfi then
				hdssSETPBINFI(0, 0, 0);
			else
				hdssSETPBINFI(0, 0);
			end
		end
		if hge.Input_GetDIKey(DIK_NUMPAD1, DIKEY_DOWN) then
			local binfi = hdss.Get(HDSS_PBINFI, 1);
			if binfi then
				hdssSETPBINFI(1, 0, 0);
			else
				hdssSETPBINFI(1, 0);
			end
		end
	end
		
	return true;

end