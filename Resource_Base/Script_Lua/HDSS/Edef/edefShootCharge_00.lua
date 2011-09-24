function Edef_ShootChargeEnemyEID_00_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 100);
	end
	if math.mod(timer, 32) == 2 then
		local turn = math.floor(timer / 32);
		if level < 15 and turn > 1 then
			return;
		end
		local num = level * 2 + 32;
		local baseangle = RANDT(1, 36000);
		local addangle = 18000 / num;
		local speed = level * 0.2 + 0.4;
		hdssBC(playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_SmallBall, 1);
		baseangle = baseangle + addangle;
		hdssBC(playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_Shuttle, 1);
		
		baseangle = RANDT(1, 36000);
		hdssA(playerindex,
			{
				TIMERLESS, 90, SPEEDSETADD, -2,
				TIMEREQUAL, 90, SPEEDSET, speed*150,
				TIMEREQUAL, 90, ANGLESETAMAP, 0,
				TIMERLESS, 180, REMAIN,
			}
		)
		hdssBC(playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_SmallBall, 15);
		baseangle = baseangle + addangle;
		hdssBC(playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_Shuttle, 15);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_00_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 100);
	end
	if math.mod(timer, 32) == 2 then
		local turn = math.floor(timer / 32);
		if level < 15 and turn > 1 then
			return;
		end
		local num = level * 2 + 48;
		local baseangle = RANDT(1, 36000);
		local speed = level * 0.08 + 1.4;
		hdssBC(playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_Amulet, 1);
		
		hdssA(playerindex,
			{
				TIMERLESS, 90, SPEEDSETADD, -2,
				TIMEREQUAL, 90, SPEEDSET, speed*150,
				TIMEREQUAL, 90, ANGLESETAMAP, 0,
				TIMERRANGE, 90, 170, SPEEDSETADD, -speed*15/8,
				TIMEREQUAL, 170, SPEEDSET, speed*100,
				TIMEREQUAL, 170, ANGLESETAMAP, 0,
				TIMERLESS, 240, REMAIN,
			}
		)
		hdssBC(playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_Amulet, 15);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_00_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 0);
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
			
			local baseangle = RANDT(1, 36000);
			local num = 40 + level * 4;
			for i=0, 4 do
				local speed = level * 0.1 + i * 0.5 + 0.4;
				hdssBC(playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_Amulet, 1);
			end
				
		elseif pattern == 1 then
			hdssEB(CC_ShootChargeEnemyEID_00_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);	
		elseif pattern == 2 then
			
			local num = 40 + level * 2;
			local baseangle = RANDT(1, 36000);
			local speed = level * 0.08 + 1.2;
			hdssA(playerindex,
				{
					TIMERLESS, 90, SPEEDSETADD, -2,
					TIMEREQUAL, 90, SPEEDSET, speed*100,
					TIMEREQUAL, 90, ANGLESETAMAP, 0,
					TIMERLESS, 180, REMAIN,
				}
			)
			for i=0, 1 do
				hdssBC(playerindex, num, baseangle, 0, x, y, speed + i * 0.4, CC_Bullet_Amulet, 15);
			end
			hdssA(playerindex);
		
		elseif pattern == 3 then
			
			local num = 30 + level;
			local baseangle = RANDT(1, 36000);
			local speed = level * 0.02 + 0.8;
			for i=0, 1 do
				hdssA(playerindex,
					{
						TIMERLESS, 90, ANGLESETADD, (i*2-1) * 100
					}
				)
				hdssBC(playerindex, num, baseangle, 0, x, y, speed, CC_Bullet_SmallBall, i * 14 + 1);
			end
			hdssA(playerindex);
			
		else
			hdssEB(CC_ShootChargeEnemyEID_00_3_E, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);	
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_00_3_A(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_00_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 8+math.floor(level/2));
	else
		local baseangle = hdssAMA(x, y, px, py);
		local speed = 0.5 + timer * 0.1 + level * 0.02;
		hdssB(playerindex, x, y, baseangle, speed, CC_Bullet_Amulet, 1);
		for i=0, 2 do
			local angle = baseangle + (i-1) * 1500;
			speed = 1.0 + timer * 0.1 + level * 0.02;
			hdssB(playerindex, x, y, angle, speed, CC_Bullet_SmallBall, 15);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_00_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_00_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_00_3_E(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 48 + level * 4);
	elseif math.mod(timer, 12) == 0 then
		ePlayerSendExChase_00(playerindex, x, y);
	end
	return true;
end