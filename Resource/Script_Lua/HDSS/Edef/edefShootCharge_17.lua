function Edef_ShootChargeEnemyEID_17_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 18);
	elseif math.mod(timer, 6) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local nowindex = timer / 6;
		local type = CC_Bullet_Coin;
		if math.mod(nowindex, 2) == 0 then
			type = CC_Bullet_SmallBall;
		end
		local speed = (3-nowindex) * 0.5 + level * 0.08 + 1.0;
		hdssBC(playerindex, 40+level, aimangle, 0, x, y, speed, type, 0);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_17_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 18);
	elseif math.mod(timer, 6) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local nowindex = timer / 6;
		local speed = (3-nowindex) * 0.5 + level * 0.08 + 1.0;
		hdssBC(playerindex, 40+level, aimangle, 0, x, y, speed, CC_Bullet_Coin, nowindex-1);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_17_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 17);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_OVERPLAYER(playerindex, cx, cy, 150, 60, 60);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif math.mod(timer, 150) == 60 then
		local pattern = RANDT(0, 3);
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
		if pattern == 0 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_17_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 1 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_17_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 2 then
			
			local angle = RANDT(1, 36000);
			local speed = 0.06*level+0.8;
			hdssBC(playerindex, 64+level, angle, 6, x, y, speed, CC_Bullet_BigShuttle, 1);
			hdssBC(playerindex, 64+level, angle, 0, x, y, speed, CC_Bullet_Coin, 5);
			
		elseif pattern == 3 then
			hdssEB(CC_ShootChargeEnemyEID_17_3_D, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, RANDT(1, 36000));
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_17_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 96);
	elseif math.mod(timer, 8) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = level * 0.1 + 3.6;
		for i=0, 2 do
			hdssB(playerindex, x, y, aimangle+(i-1)*3000, speed, CC_Bullet_BigShuttle, 6);
		end
	end
	
	if timer >= 15 and timer < 90 and math.mod(timer, 15) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = level * 0.1 + 3.0;
		for i=0, 7 do
			hdssB(playerindex, x, y, aimangle+(i-3.5)*800, speed, CC_Bullet_Coin, 2);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_17_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 48+level*3);
	end
	local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
	local type = CC_Bullet_SmallBall;
	local color = 0;
	local nowindex = math.mod(timer, 4);
	if nowindex == 2 then
		type = CC_Bullet_BigShuttle;
	elseif nowindex == 3 then
		type = CC_Bullet_Coin;
		color = 1;
	end
	local speed = level *0.08 + 2.0 + RANDTF(-1, 1);
	hdssB(playerindex, x, y, aimangle+RANDT(-1200, 1200), speed, type, color);
	return true;
end


function Edef_ShootChargeEnemyEID_17_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_17_3_D(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 18);
	elseif math.mod(timer, 6) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local nowindex = timer / 6;
		local type = CC_Bullet_Coin;
		local color = 4;
		if math.mod(nowindex, 2) == 1 then
			type = CC_Bullet_SmallBall;
			color = 15;
		end
		local speed = (3-nowindex) * 0.5 + level * 0.08 + 1.0;
		hdssBC(playerindex, 40+level, aimangle, 0, x, y, speed, type, color);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_17_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end