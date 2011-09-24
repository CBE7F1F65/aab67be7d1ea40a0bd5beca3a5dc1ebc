function Edef_ShootChargeEnemyEID_03_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 60+level*5);
	end
	local nowindex = math.mod(timer, 20);
	local oneturn = 12+math.floor(level/8);
	if nowindex < oneturn then
		local xplus = CenterW / oneturn * 2;
		if x > helper_GetCenterX(playerindex) then
			xplus = -xplus;
		end
		local angle = RANDT(8500, 9500);
		local speed = 2.0 + level * 0.1;
		local type = CC_Bullet_Scale;
		local color = 9;
		if math.mod(nowindex, 2) == 1 then
			speed = speed - 0.5;
			type = CC_Bullet_SmallBall;
			color = 4;
		end
		hdssB(playerindex, x+xplus*math.floor(nowindex/2), y, angle, speed, type, color);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_03_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 60+level*5);
	end
	local nowindex = math.mod(timer, 20);
	local oneturn = 10+math.floor(level/8);
	if nowindex < oneturn then
		local xplus = CenterW / oneturn * 2;
		if x > helper_GetCenterX(playerindex) then
			xplus = -xplus;
		end
		local angle = RANDT(8500, 9500);
		local speed = 2.0 + level * 0.1;
		local type = CC_Bullet_BendedKnife;
		local color = 5;
		if math.mod(nowindex, 2) == 1 then
			speed = speed - 0.5;
			type = CC_Bullet_Scale;
			color = 9;
		end
		hdssB(playerindex, x+xplus*math.floor(nowindex/2), y, angle, speed, type, color);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_03_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 3);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_REPOSITION(playerindex, 60);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif math.mod(timer, 180) == 60 then
		local pattern = RANDT(0, 2);
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
		if pattern == 0 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_03_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 1 then
			hdssEB(CC_ShootChargeEnemyEID_03_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		elseif pattern == 2 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_03_3_C, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		end
	elseif timer > 60 and math.mod(timer, 180) == 30 then
		local cenx = helper_GetCenterX(playerindex);
		local xoffset = CenterW * 2 / 5;
		local randpos = RANDT(0, 1);
		
		if randpos == 0 then
			if x > cenx - 32 then
				aimx = cenx - xoffset;
				aimy = 128;
			else
				aimx = cenx;
				aimy = 96;
			end
		else
			if x < cenx + 32 then
				aimx = cenx + xoffset;
				aimy = 128;
			else
				aimx = cenx;
				aimy = 96;
			end
		end
		
		hdssEA(playerindex, ENAC_CHASEAIM_XYSOAOCO,
			{
				aimx, aimy, 0.0
			},
			{
				9000, 0, 30
			}
		);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_03_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	local timemod = 8;
	if level > 9 then
		timemod = 6;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, (10+level)*timemod);
	elseif math.mod(timer, timemod) == 0 then
		local addangle = RANDT(-2500, 2500);
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = level * 0.15 + 1.3;
		hdssA(playerindex,
			{
				TIMERLESS, 75, ANGLESETADD, 180,
				TIMEREQUAL, 75, ANGLESETADD, addangle
			}
		)
		hdssB(playerindex, x, y, aimangle-9000, speed, CC_Bullet_BendedKnife, 4);
		addangle = RANDT(-2500, 2500);
		hdssA(playerindex,
			{
				TIMERLESS, 75, ANGLESETADD, -180,
				TIMEREQUAL, 75, ANGLESETADD, addangle
			}
		)
		hdssB(playerindex, x, y, aimangle+9000, speed, CC_Bullet_BendedKnife, 4);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_03_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	local timemod = 8;
	if level > 9 then
		timemod = 6;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, (10+level)*timemod);
	elseif math.mod(timer, timemod) == 0 then
		local angle = hdssAMAP(playerindex, x, y);
		local speed = level * 0.2 + 1.6;
		hdssB(playerindex, x, y, angle, speed, CC_Bullet_BendedKnife, 3)
	end
	return true;
end


function Edef_ShootChargeEnemyEID_03_3_C(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 40+level*2);
	elseif math.mod(timer, 8) == 0 then
		local nowturn = math.floor(timer / 8)-1;
		local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = level * 0.16 + 1.3;
		local angleoffset = 475;
		for i=0, nowturn do
			hdssB(playerindex, x, y, angle+(2*i-nowturn)*angleoffset, speed, CC_Bullet_Knife, 6);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_03_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_03_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end