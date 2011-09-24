function Edef_ShootChargeEnemyEID_08_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 96);
	elseif math.mod(timer, 6) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = level * 0.1 + 1.7;
		local nowindex = timer / 6;
		local type = CC_Bullet_SmallBall;
		if math.mod(nowindex, 2) == 1 then
			type = CC_Bullet_Scale;
		end
		local addangle = aimangle / 10;
		hdssA(playerindex,
			{
				TIMERLESS, 30, ANGLESETADD, addangle,
				TIMERRANGE, 30, 55, ANGLESETADD, -addangle,
				TIMERRANGE, 55, 70, ANGLESETADD, addangle,
				TIMERRANGE, 70, 85, ANGLESETADD, -addangle
			}
		)
		for i=0, 6 do
			local angle = 9000 + (i-3)*1000 - aimangle/2;
			hdssB(playerindex, x, y, angle, speed, type, 2);
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_08_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 96);
	elseif math.mod(timer, 12) == 0 then
		local speed = level * 0.1 + 1.8;
		local type = CC_Bullet_Scale;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		for i=0, 1 do
			if i == 1 then
				aimangle = -aimangle;
			end
			local color = 2;
			if i == 1 then
				color = 6;
			end
			local addangle = aimangle / 10;
			hdssA(playerindex,
				{
					TIMERLESS, 30, ANGLESETADD, addangle,
					TIMERRANGE, 30, 55, ANGLESETADD, -addangle,
					TIMERRANGE, 55, 70, ANGLESETADD, addangle,
					TIMERRANGE, 70, 85, ANGLESETADD, -addangle
				}
			)
			for i=0, 6 do
				local angle = 9000 + (i-3)*1000 - aimangle/2;
				hdssB(playerindex, x, y, angle, speed, type, color);
			end
			hdssA(playerindex);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_08_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 8);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_OVERPLAYER(playerindex, cx, cy, 120, 60, 60);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif math.mod(timer, 120) == 60 then
		local pattern = RANDT(0, 2);
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
		if pattern == 0 then
			local aimangle = (RANDT(0, 1)*2-1)*400;
			hdssEB(CC_ShootChargeEnemyEID_08_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);	
		elseif pattern == 1 then
			local aimangle = (RANDT(0, 1)*2-1)*3000;
			hdssEB(CC_ShootChargeEnemyEID_08_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 2 then
			local speed = 2.8 + level * 0.1;
			hdssBC(playerindex, 56, RANDT(1, 36000), 0, x, y, speed, CC_Bullet_Quaver, 0);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_08_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 80);
	elseif math.mod(timer, 5) == 0 then
		local angle = level * 754;
		local speed = level * 0.1 + 2.5;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		hdssA(playerindex,
			{
				TIMERLESS, 80, ANGLESETADD, aimangle
			}
		)
		hdssBC(playerindex, 16, angle, 0, x, y, speed, CC_Bullet_Scale, 2);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_08_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 64);
	elseif math.mod(timer, 4) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = level * 0.1 + 1.7;
		local nowindex = timer / 4;
		local type = CC_Bullet_SmallBall;
		if math.mod(nowindex, 2) == 1 then
			type = CC_Bullet_Scale;
		end
		local addangle = aimangle / 10;
		hdssA(playerindex,
			{
				TIMERLESS, 30, ANGLESETADD, addangle,
				TIMERRANGE, 30, 55, ANGLESETADD, -addangle,
				TIMERRANGE, 55, 70, ANGLESETADD, addangle,
				TIMERRANGE, 70, 85, ANGLESETADD, -addangle
			}
		)
		for i=0, 2 do
			local angle = 9000 + (i-1)*1200 - aimangle/2;
			hdssB(playerindex, x, y, angle, speed, type, 2);
		end
		hdssA(playerindex);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_08_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_08_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_08_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end