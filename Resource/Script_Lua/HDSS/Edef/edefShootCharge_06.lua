function Edef_ShootChargeEnemyEID_06_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 64+level/4);
	end
	local speed = level * 0.1 + 1.8 + RANDTF(-0.5, 0.5);
	local angle = RANDT(1, 36000);
	local type = CC_Bullet_Shuttle;
	if math.mod(timer, 2) == 0 then
		type = CC_Bullet_SmallBall;
	end
	for i=0, 1 do
		hdssB(playerindex, x, y, angle+i*18000, speed, type, 2);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_06_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 48+level/4);
	end
	local speed = level * 0.1 + 1.8 + RANDTF(-0.5, 0.5);
	local angle = RANDT(1, 36000);
	local type = CC_Bullet_Shuttle;
	if math.mod(timer, 2) == 0 then
		type = CC_Bullet_Scale;
	end
	for i=0, 1 do
		hdssB(playerindex, x, y, angle+i*18000, speed, type, 2);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_06_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 6);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_OVERPLAYER(playerindex, cx, cy, 224, 60, 60);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif math.mod(timer, 224) == 60 then
		local pattern = RANDT(0, 1);
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
		if pattern == 0 then
			
			hdssEB(CC_ShootChargeEnemyEID_06_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			local aimx = hdss.Get(HDSS_PX,	playerindex);
			local aimy = hdss.Get(HDSS_PY,	playerindex);
			hdssENSAIM(playerindex, level, aimx, aimy, RANDT(0, 1)*2-1*4500);	
				
		elseif pattern == 1 then
			
			hdssEB(CC_ShootChargeEnemyEID_06_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
			
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_06_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 60+level*3);
	elseif math.mod(timer, 6) == 0 then
		local nowindex = timer / 6;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local angleoffset = -aimangle / (8+level/2) * nowindex;
		local aimx = hdss.Get(HDSS_ENAIMX, playerindex);
		local aimy = hdss.Get(HDSS_ENAIMY, playerindex);
		local angle = hdssAMA(x, y, aimx, aimy);
		local speed = level * 0.2 + 2.1;
		hdssB(playerindex, x, y, aimangle+angleoffset+angle, speed, CC_Bullet_BigBall, 2);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_06_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 96+level*6);
	elseif math.mod(timer, 6) == 0 then
		for i=0, 2 do
			local speed = level * 0.15 + 1.4 + RANDTF(-0.5, 0.5);
			local angle = RANDT(1, 36000);
			for j=0, 1 do
				angle = angle + j * 18000;
				hdss.Call(HDSS_BL,
					{
						playerindex, 2, angle, 8, 0, x, y, angle, 0, speed, 0.5, CC_Bullet_SmallBall, 2
					}
				)
			end
		end
		for i=0, 1 do
			local speed = level * 0.15 + 1.4 + RANDTF(-0.5, 0.5);
			local angle = RANDT(1, 36000);
			for j=0, 1 do
				angle = angle + j * 18000;
				hdss.Call(HDSS_BL,
					{
						playerindex, 3, angle, 8, 0, x, y, angle, 0, speed, 0.5, CC_Bullet_Shuttle, 2
					}
				)
			end
		end
	end
	return true;
end


function Edef_ShootChargeEnemyEID_06_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_06_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_06_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end