function _Edef_ShootChargeEnemyEID_07_CallPerfectFreeze(x, y, level, playerindex)
	
	game.SetPerfectFreezeParam(1-playerindex,
		{
			TIMEREQUAL, 2, AND, INDEXMODEQUAL, 2, 0, THEN, TYPESET, CC_Bullet_SmallBall, 
			TIMEREQUAL, 2, AND, INDEXMODEQUAL, 2, 0, THEN, COLORSET, 15, 
			TIMEREQUAL, 2, ANGLESETRAND, 1, 36000, 
			TIMERRANGE, 60, level*4+80, SPEEDSETADD, 3
		}
	)
	game.SetPerfectFreezeParam(playerindex,
		{
			TIMEREQUAL, 2, ANGLESETRAND, 1, 36000, 
			TIMERRANGE, 60, level*4+80, SPEEDSETADD, 3
		}
	)
	for i=0, 1 do
		hdss.Call(HDSS_EZONEBUILD,
			{
				EZONETYPE_BULLETPERFECTFREEZE+EZONECHECK_CIRCLE, i, helper_GetCenterX(i), CenterY, 
				4, EVENTZONE_OVERZONE
			}
		)
	end
end

function Edef_ShootChargeEnemyEID_07_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 76);
		local num = 32+level*2;
		local angle = RANDT(1, 36000);
		hdssBC(playerindex, num, angle, 0, x, y, 2.0, CC_Bullet_Arris, 6);
		hdssBC(playerindex, num, angle+18000/num, 0, x, y, 2.0, CC_Bullet_SmallBall, 6);
	elseif timer == 60 then
		_Edef_ShootChargeEnemyEID_07_CallPerfectFreeze(x, y, level, playerindex);
	elseif timer > 60 and math.mod(timer, 4) == 0 then	
		hdssSE(CC_SE_Bullet_2);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_07_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 76);
		local num = 32+level*2;
		local angle = RANDT(1, 36000);
		hdssBC(playerindex, num, angle, 0, x, y, 2.0, CC_Bullet_Arris, 6);
		hdssBC(playerindex, num, angle+18000/num, 0, x, y, 1.2, CC_Bullet_Arris, 6);
	elseif timer == 60 then
		_Edef_ShootChargeEnemyEID_07_CallPerfectFreeze(x, y, level, playerindex);
	elseif timer > 60 and math.mod(timer, 4) == 0 then	
		hdssSE(CC_SE_Bullet_2);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_07_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 7);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_OVERPLAYER(playerindex, cx, cy, 90, 60, 60);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif math.mod(timer, 90) == 60 then
		local pattern = RANDT(0, 2);
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
		if pattern == 0 then
			
			local leftrightindi = RANDT(0, 1)*2-1;
			local cenx = helper_GetCenterX(playerindex);
			hdssEB(CC_ShootChargeEnemyEID_07_3_A, playerindex, cenx+leftrightindi*CenterW/2, 0, leftrightindi*9000+9000, CenterW/(24+level), LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
			for i=0, 2 do
				local speed = level * 0.1 + 2.0 + i * 0.2;
				hdssBC(playerindex, 16, 9000, 16*i, x, y, speed, CC_Bullet_SmallBall, 15);
			end
				
		elseif pattern == 1 then
			
			local num = 32 + level;
			local baseangle = RANDT(1, 36000);
			local speed = level * 0.1 + 0.6;
			for i=0, 1 do
				hdssA(playerindex,
					{
						TIMERLESS, 90, SPEEDSETADD, -1,
						TIMERRANGE, 90, 120, SPEEDSETADD, 5,
						TIMERRANGE, 90, 120, ANGLESETADD, (i*2-1) * 150
					}
				)
				hdssBC(playerindex, num, baseangle+i*18000/(num), 0, x, y, speed, CC_Bullet_Arris, 8);
			end
			hdssA(playerindex);
			
		elseif pattern == 2 then
			
			hdssEB(CC_ShootChargeEnemyEID_07_3_C, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);	
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_07_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if math.mod(timer, 4) == 2 then
		local playerID = 0xff;
		ePlayerSendExChase_07(playerindex, x, y, playerID, 0);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_07_3_B(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_07_3_C(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 30+level);
	end
	local bx = RANDTF(-48, 48) + x;
	local by = RANDTF(-48, 48) + y;
	local angle = RANDT(-450, 450) + 9000;
	local speed = level * 0.05 + 2.4;
	hdssB(playerindex, bx, by, angle, speed, CC_Bullet_Arris, 6);
	return true;
end

function Edef_ShootChargeEnemyEID_07_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_07_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end