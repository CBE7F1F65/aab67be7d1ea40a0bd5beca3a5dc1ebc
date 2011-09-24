function Edef_ShootChargeEnemyEID_09_1(playerindex, level, x, y, timer, px, py)
	local nway = 4;
	if level > 10 then
		nway = 6;
	end
	if math.mod(timer, 4) == 0 then
		hdssA(playerindex,
			{
				TIMERRANGE, 40-level, 90, SPEEDSETADD, nway
			}
		)
		local nowindex = timer / 4;
		for i=0, nway-1 do
			local leftrightindi = math.mod(i, 2) * 2 - 1;
			local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex) + (nowindex * 927 + i * (36000 / nway)) * leftrightindi;
			local type = CC_Bullet_Scale;
			if math.mod(nowindex, 2) == 0 then
				type = CC_Bullet_SmallBall;
			end
			hdssB(playerindex, x, y, angle, 0, type, 2, 8, 24);
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_09_2(playerindex, level, x, y, timer, px, py)
	local nway = 4;
	if level > 10 then
		nway = 6;
	end
	if math.mod(timer, 8) == 0 then
		hdssA(playerindex,
			{
				TIMERRANGE, 40-level, 90, SPEEDSETADD, nway
			}
		)
		local nowindex = timer / 8;
		for i=0, nway-1 do
			local leftrightindi = math.mod(i, 2) * 2 - 1;
			local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex) + (nowindex * 927 + i * (36000 / nway)) * leftrightindi;
			hdssB(playerindex, x, y, angle, 0, CC_Bullet_Scale, 2, 8, 24);
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_09_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 9);
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
			local angle = hdssAMAP(playerindex, x, y);
			local aimangle = RANDT(1, 36000);
			hdssEB(CC_ShootChargeEnemyEID_09_3_A, playerindex, x, y, angle, 1.6, LConst_EnemyExType_Mystia, 0);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 1 then
			local angle = hdssAMAP(playerindex, x, y);
			local aimangle = RANDT(1, 36000);
			hdssEB(CC_ShootChargeEnemyEID_09_3_A, playerindex, x, y, angle, 1.6, LConst_EnemyExType_Mystia, 0);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
			
			aimangle = angle;
			hdssEB(CC_ShootChargeEnemyEID_09_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 2 then
			local angle = hdssAMAP(playerindex, x, y);
			for i=0, 6 do
				local aimangle = RANDT(1, 36000);
				hdssEB(CC_ShootChargeEnemyEID_09_3_C, playerindex, x, y, angle+(i-3)*3000, 1.6, LConst_EnemyExType_Mystia, 0);
				hdssENSAIM(playerindex, level, 0, 0, aimangle);
			end
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_09_3_A(playerindex, level, x, y, timer, px, py)
--	if _ePlayerShootCharge_CheckBoss(playerindex) then
--		return true;
--	end
	if math.mod(timer, 8) == 0 then
		local nowindex = timer / 8;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local leftrightindi = math.mod(aimangle, 2) * 2 - 1;
		local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex) + (nowindex * 927) * leftrightindi;
		local type = CC_Bullet_Scale;
		if math.mod(nowindex, 2) == 0 then
			type = CC_Bullet_SmallBall;
		end
		hdssA(playerindex,
			{
				TIMERRANGE, 40-level, 90, SPEEDSETADD, 5
			}
		)
		hdssB(playerindex, x, y, angle, 0, type, 2, 8, 24);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_09_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 32);
	elseif math.mod(timer, 2) == 0 then
		local nowindex = timer / 2;
		local leftrightindi = 1;
		if x < px then
			leftrightindi = -1;
		end
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local angle = aimangle + leftrightindi * (nowindex-6) * 1687.5;
		for i=0, 2 do
			local speed = level * 0.05 + 1.6 + i * 0.6;
			local speedadd = speed * 100 / 32;
			hdssA(playerindex,
				{
					TIMERRANGE, 32, 64, SPEEDSETADD, -speedadd,
					TIMERRANGE, 64, 96, SPEEDSETADD, speedadd
				}
			)
			hdssB(playerindex, x, y, angle, speed, CC_Bullet_MiddleBall, 10);
		end
		hdssA(playerindex);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_09_3_C(playerindex, level, x, y, timer, px, py)
--	if _ePlayerShootCharge_CheckBoss(playerindex) then
--		return true;
--	end
	if math.mod(timer, 6) == 0 then
		local nowindex = timer / 6;
		local angle = hdss.Get(HDSS_ENANGLE, playerindex) + 18000;
		local type = CC_Bullet_Scale;
		if math.mod(nowindex, 2) == 0 then
			type = CC_Bullet_SmallBall;
		end
		hdssA(playerindex,
			{
				TIMERRANGE, 40-level, 90, SPEEDSETADD, 5
			}
		)
		hdssB(playerindex, x, y, angle, 0, type, 2, 8, 24);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_09_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_09_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end