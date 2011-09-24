function Edef_ShootChargeEnemyEID_01_1(playerindex, level, x, y, timer, px, py)

	local row = (math.floor((level+1)/4) + 2) * 2;
	local timemod = math.floor(CenterH / row / hdss.Get(HDSS_ENSPEED, playerindex));
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, timemod*(row-1)+1);
	end
	if math.mod(timer, timemod) == 1 then
		local num = 8;
		local baseangle;
		if x < helper_GetCenterX(playerindex) then
			baseangle = 4500;
		else
			baseangle = 13500;
		end
		local speed = level * 0.02 + 0.4;
		local type = CC_Bullet_Star;
		if math.mod((timer-1)/timemod, 2) == 1 then
			type = CC_Bullet_SmallBall;
		end
		hdss.Call(
			HDSS_BL,
			{
				playerindex, num, baseangle, 0, 0, x, y, baseangle, 0, speed, 0.3, type, 6
			}
		)
	end
	return true;
end

function Edef_ShootChargeEnemyEID_01_2(playerindex, level, x, y, timer, px, py)
	local row = math.floor((level+1)/4) + 2;
	local timemod = math.floor(CenterH / row / hdss.Get(HDSS_ENSPEED, playerindex));
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, timemod*(row-1)+1);
	end
	if math.mod(timer, timemod) == 1 then
		local num = 8;
		local baseangle;
		local color;
		if x < helper_GetCenterX(playerindex) then
			baseangle = 4500;
			color = 10;
		else
			baseangle = 13500;
			color = 6;
		end
		local speed = level * 0.02 + 0.4;
		hdss.Call(
			HDSS_BL,
			{
				playerindex, num, baseangle, 0, 0, x, y, baseangle, 0, speed, 0.3, CC_Bullet_Star, color
			}
		)
	end
	return true;
end

function Edef_ShootChargeEnemyEID_01_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 1);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_OVERPLAYER(playerindex, cx, cy, 90, 60, 60);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif math.mod(timer, 90) == 60 then
		local pattern = RANDT(0, 4);
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
		if pattern == 0 then
			
			hdssEB(CC_ShootChargeEnemyEID_01_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, RANDT(1, 36000));	
				
		elseif pattern == 1 then
			local angle = RANDT(-3000, 3000);
			hdssEB(CC_ShootChargeEnemyEID_01_3_B, playerindex, x, y, angle, hdss.Get(HDSS_SIGN, angle), LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);	
			
		elseif pattern == 2 then
			
			hdssEB(CC_ShootChargeEnemyEID_01_3_C, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);	
		
		elseif pattern == 3 then
			
			hdssEB(CC_ShootChargeEnemyEID_01_3_D, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);	
			
		else
			hdssEB(CC_ShootChargeEnemyEID_01_3_E, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);	
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_01_3_A(playerindex, level, x, y, timer, px, py)

	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 40);
	elseif math.mod(timer, 2) == 0 then
		local baseangle = (19 * (-38 * level + 418) + 180) * timer + hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local looptime = math.floor(level/6) + 2;
		local speed = level * 0.1 + 1.4;
		local type;
		local color;
		local turn = timer / 2;
		if math.mod(turn, 4) < 2 then
			color = 10;
		else
			color = 6;
		end
		if math.mod(turn, 2) == 0 then
			type = CC_Bullet_SmallBall;
		else
			type = CC_Bullet_Star;
		end
		for i=0, looptime-1 do
			hdssBC(playerindex, 3, baseangle + i * 1000, 0, x, y, speed, type, color);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_01_3_B(playerindex, level, x, y, timer, px, py)

	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		local set;
		if level < 10 then
			set = 10;
		elseif level < 15 then
			set = 13;
		else
			set = 20;
		end
		hdssEA_FADEOUT(playerindex, set * 2);
	elseif math.mod(timer, 2) == 0 then
		local num = 4;
		local baseangle = hdssAMA(x, y, px, py);
		local speed = level * 0.1 + 2.5;
		local beginindex = 0;
		if hdss.Get(HDSS_ENSPEED, playerindex) < 0 then
			beginindex = 3;
		end
		hdssA(
			playerindex,
			{
				TIMEREQUAL, 10, ANGLESETAMAP, 0
			}
		)
		hdss.Call(
			HDSS_BL,
			{
				playerindex, num, baseangle+9000, 6, beginindex, x, y, baseangle, 0, speed, -0.2, CC_Bullet_Star, 6
			}
		)
		hdssA(playerindex);
	end
	return true;
	
end


function Edef_ShootChargeEnemyEID_01_3_C(playerindex, level, x, y, timer, px, py)

	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 30+level);
	end
	
	local angleadd = hdss.Get(HDSS_SIGN, timer) * 100;
	local speed = level * 0.1 + 3.0;
	hdssA(
		playerindex,
		{
			TIMERRANGE, 32, 64, ANGLESETADD, angleadd,
			TIMERLESS, 64, SPEEDSETADD, -4,
		}
	)
	for i=0, 1 do
		local angle = RANDT(1, 36000);
		hdssB(playerindex, x, y, angle, speed, CC_Bullet_Star, 14);
	end
	hdssA(playerindex);
	return true;
end

function Edef_ShootChargeEnemyEID_01_3_D(playerindex, level, x, y, timer, px, py)

	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		local num;
		if level < 12 then
			num = 6;
		elseif level < 14 then
			num = 7;
		elseif level < 16 then
			num = 8;
		else
			num = 9;
		end
		hdssEA_FADEOUT(playerindex, num * 8);
	elseif math.mod(timer, 8) == 6 then
		local cx = helper_GetCenterX(playerindex);
		local x = RANDT(cx-CenterW/2+8, cx+CenterW/2-8);
		local y = CenterH + 16;
		local playerID = 0xff;
		local angleoffset = RANDT(-400, 400);
		ePlayerSendExChase_01(playerindex, x, y, playerID, 0, angleoffset);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_01_3_E(playerindex, level, x, y, timer, px, py)

	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		local num = math.floor(level/5) + 3;
		hdssEA_FADEOUT(playerindex, num * 14);
	elseif math.mod(timer, 14) == 6 then
		local xoffset = hdss.Get(HDSS_SIGN, (timer-6)/14) * 64;
		local x = px + xoffset;
		local y = CenterH + 16;
		local playerID = 0xff;
		ePlayerSendExChase_01(playerindex, x, y, playerID, 0);
	end
	return true;
end