function Edef_ShootChargeEnemyEID_16_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 44+level*8/3);
	end
	local type = CC_Bullet_SmallBall;
	if math.mod(timer, 8) == 0 then
		type = CC_Bullet_Shuttle;
	end
	local leftrightindi = math.mod(hdss.Get(HDSS_ENI, playerindex), 2) * 2 - 1;
	local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex) + timer * leftrightindi * 1125;
	local speed = level * 0.1 + 1.5;
	for i=0, 1 do
		hdssB(playerindex, x, y, angle, speed, type, 2);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_16_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 44+level*8/3);
	end
	local type = CC_Bullet_Stupa;
	local speed = level * 0.1 + 1.3;
	local color = 0;
	if math.mod(timer, 2) == 1 then
		type = CC_Bullet_Shuttle;
		speed = speed + 0.2;
		color = 2;
	end
	local leftrightindi = math.mod(hdss.Get(HDSS_ENI, playerindex), 2) * 2 - 1;
	local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex) + timer * leftrightindi * 1125;
	for i=0, 1 do
		hdssB(playerindex, x, y, angle, speed, type, color);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_16_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 16);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_OVERPLAYER(playerindex, cx, cy, 150, 60, 60);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif math.mod(timer, 150) == 60 then
		local pattern = RANDT(0, 2);
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
		if pattern == 0 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_16_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 1 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_16_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 2 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_16_3_C, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_16_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, (level+1)*5);
	elseif math.mod(timer, 5) == 0 then
		local speed = level * 0.1 + 4.4;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		for i=0, 7 do
			hdssB(playerindex, x, y, aimangle+(i-3.5)*2000, speed, CC_Bullet_Stupa, 0, 24);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_16_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 32);
	elseif math.mod(timer, 8) == 0 then
		local nowindex = timer / 8;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = level * 0.1 + 2.6;
		local type = CC_Bullet_SmallBall;
		if math.mod(nowindex, 2) == 1 then
			type = CC_Bullet_Shuttle;
		end
		hdssBC(playerindex, 40+level, aimangle, 0, x, y, speed, type, 2);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_16_3_C(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 16);
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		for i=0, 1 do
			for j=0, 3 do
				hdss.Call(HDSS_BEB,
					{
						playerindex, x, y, aimangle+(i*2-1)*9000+(j-1)*1000, 0.5, CC_Bullet_ShuttleBeam, i*4+2, 384, 32, BEAMFLAG_HS, 16, 80
					}
				)
			end
		end
	elseif timer == 16 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		hdss.Call(HDSS_BEB,
			{
				playerindex, x, y, aimangle, 0.1, CC_Bullet_ShuttleBeam, 4, 512, 96, BEAMFLAG_HS, 54, 96
			}
		)
	end
	return true;
end

function Edef_ShootChargeEnemyEID_16_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_16_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end