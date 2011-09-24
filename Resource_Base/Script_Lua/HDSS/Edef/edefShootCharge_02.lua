function Edef_ShootChargeEnemyEID_02_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		
		hdssEA_FADEOUT(playerindex, 41);
		local stopflag = STOPFLAG_ALLSET;
		if playerindex == 0 then
			stopflag = stopflag + STOPFLAG_PLAYERINDEX_1;
		else
			stopflag = stopflag + STOPFLAG_PLAYERINDEX_0;
		end
		local oplayerID = hdss.Get(HDSS_CHARA, 1-playerindex);
		if oplayerID == CC_PlayerID_Sakuya then
			stopflag = stopflag - STOPFLAG_PLAYER;
		end
		hdssSTOPACTION(stopflag, 41);
		local aimx = hdss.Get(HDSS_PX, 1-playerindex);
		local aimy = hdss.Get(HDSS_PY, 1-playerindex);
		local aimangle = hdssAMAP(1-playerindex, helper_GetCenterX(1-playerindex), CenterY, 18000);
		hdssENSAIM(playerindex, level, aimx, aimy, aimangle);
		
	elseif math.mod(timer, 4) == 0 then
		
		local aimx = hdss.Get(HDSS_ENAIMX, playerindex);
		local aimy = hdss.Get(HDSS_ENAIMY, playerindex);
		local r = 60;
		local nowindex = timer / 4;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local angle = (nowindex-4.5) * 1200 + aimangle;
		local bx = r * hdss.Get(HDSS_COSA, angle) + aimx;
		local by = r * hdss.Get(HDSS_SINA, angle) + aimy;
		hdssA(1-playerindex,
			{
				TIMERLESS, 30+level, SPEEDSETADD, 5
			}
		)
		hdssB(1-playerindex, bx, by, angle+18000, 0, CC_Bullet_SmallBall, 4, -1);
		hdssB(1-playerindex, bx, by, angle+18000, 0.5, CC_Bullet_Knife, 1, -1);
		hdssA(1-playerindex);
		hdssSE(CC_SE_Bullet_2, bx);
		
	end
	return true;
end

function Edef_ShootChargeEnemyEID_02_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		
		hdssEA_FADEOUT(playerindex, 41);
		local stopflag = STOPFLAG_ALLSET;
		if playerindex == 0 then
			stopflag = stopflag + STOPFLAG_PLAYERINDEX_1;
		else
			stopflag = stopflag + STOPFLAG_PLAYERINDEX_0;
		end
		local oplayerID = hdss.Get(HDSS_CHARA, 1-playerindex);
		if oplayerID == CC_PlayerID_Sakuya then
			stopflag = stopflag - STOPFLAG_PLAYER;
		end
		hdssSTOPACTION(stopflag, 41);
		local aimx = hdss.Get(HDSS_PX, 1-playerindex);
		local aimy = hdss.Get(HDSS_PY, 1-playerindex);
		local aimangle = hdssAMAP(1-playerindex, helper_GetCenterX(1-playerindex), CenterY, 18000);
		hdssENSAIM(playerindex, level, aimx, aimy, aimangle);
		
	elseif math.mod(timer, 4) == 0 then
		
		local aimx = hdss.Get(HDSS_ENAIMX, playerindex);
		local aimy = hdss.Get(HDSS_ENAIMY, playerindex);
		local r = 60;
		local nowindex = timer / 4 - 4.5;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local angle = nowindex * 1200 + aimangle;
		local bx = r * hdss.Get(HDSS_COSA, angle) + aimx;
		local by = r * hdss.Get(HDSS_SINA, angle) + aimy;
		hdssA(1-playerindex,
			{
				TIMERLESS, 30+level, SPEEDSETADD, 5
			}
		)
		for i=0, 3 do
			hdssB(1-playerindex, bx, by, angle+nowindex*737+i*9000, 0.5, CC_Bullet_Knife, 1, -1);
		end
		hdssA(1-playerindex);
		hdssSE(CC_SE_Bullet_2, bx);
		
	end
	return true;
end

function Edef_ShootChargeEnemyEID_02_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 2);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_OVERPLAYER(playerindex, cx, cy, 120, 60, 60);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif math.mod(timer, 120) == 60 then
		local pattern = RANDT(0, 4);
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
		if pattern == 0 then
			
			hdssEB(CC_ShootChargeEnemyEID_02_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);	
				
		elseif pattern == 1 then
			
			hdssEB(CC_ShootChargeEnemyEID_02_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, hdssAMAP(playerindex, x, y));	
			
		elseif pattern == 2 or pattern == 4 then
			
			local aimx = (pattern-3) * CenterW * 2 / 5 + helper_GetCenterX(playerindex);
			hdssEA(playerindex, ENAC_CHASEAIM_XYSOAOCO,
				{
					aimx, 128, 0.0
				},
				{
					9000, 0, 15
				}
			);	
		
		elseif pattern == 3 then
			
			local angle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_02_3_D, playerindex, x, y, angle, 2.2, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);	
				
		end
	end
	
	local savedpattern = hdss.Get(HDSS_D, LConst_Desc_BossPattern+playerindex);
	if savedpattern == 2 or savedpattern == 4 then
		if math.mod(timer, 120) == 75 then
			local aimx = helper_GetCenterX(playerindex)*2 - x;
			hdssEA(playerindex, ENAC_CHASEAIM_XYSOAOCO,
				{
					aimx, 96, 1.0
				},
				{
					-9000, 0, 45
				}
			);
		elseif math.mod(timer, 120) > 75 then
			if math.mod(timer, 4) == 0 then
				local turn = math.floor(level / 4) + 2;
				local nowindex = (math.mod(timer, 120)-75) / 4;
				local speed = level * 0.1 + 1.4;
				local leftrightindi = savedpattern - 3;
				for i=0, turn-1 do
					hdssB(playerindex, x, y, 9000+nowindex*200*leftrightindi-i*(6000/turn)*leftrightindi, speed, CC_Bullet_Knife, 3);
				end
			end
		elseif math.mod(timer, 120) == 1 then
			local cx = helper_GetCenterBossX(playerindex);
			local cy = CenterBossY;
			hdssEA_OVERPLAYER(playerindex, cx, cy, 120, 60, 60);
		end
	end
	
	return true;
end

function Edef_ShootChargeEnemyEID_02_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 40+level*2);
	elseif math.mod(timer, 4) == 0 then
		local speed = level * 0.1 + 1.2;
		local xoffset = RANDTF(-24, 24);
		local yoffset = RANDTF(-24, 24);
		hdssA(playerindex,
			{
				COLOREQUAL, 2, AND, YLESS, 400, THEN, BOUNCE, 0, 1,
				COLOREQUAL, 2, AND, BOUNCEEQUAL, 1, THEN, COLORSET, 3
			}
		)
		hdssBC(playerindex, 7, RANDT(1, 36000), 0, x+xoffset, y+yoffset, speed, CC_Bullet_Knife, 2);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_02_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 64);
	elseif math.mod(timer, 4) == 0 then
		local speed = level * 0.2 + 1.2;
		local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local nowindex = timer / 4;
		local angleoffset = 600;
		for i=0, 1 do
			hdssB(playerindex, x, y, angle+(i*2-1)*(16-nowindex)*angleoffset, speed, CC_Bullet_Knife, 6);
		end
	end
	return true;
end


function Edef_ShootChargeEnemyEID_02_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_02_3_D(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 100+level*4);
		local angle = hdss.Get(HDSS_ENANGLE, playerindex);
		local speed = hdss.Get(HDSS_ENSPEED, playerindex);
		hdssB(playerindex, x, y, angle, speed, CC_Bullet_Knife, 4);
	end
	if math.mod(timer, 2) == 0 then
		hdssA(playerindex,
			{
				TIMERRANGE, 30, 60, SPEEDSETADD, level/3
			}
		)
		hdssB(playerindex, x, y, RANDT(1, 36000), 0.5, CC_Bullet_SmallBall, 6);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_02_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end