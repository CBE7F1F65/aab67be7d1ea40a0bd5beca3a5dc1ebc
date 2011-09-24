function Edef_ShootChargeEnemyEID_13_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 40+level*4);
	elseif math.mod(timer, 4) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local nowindex = timer / 4;
		local speed = level * 0.05 + timer * 0.05 + 0.8;
		local type = CC_Bullet_Shuttle;
		if math.mod(nowindex, 2) == 0 then
			type = CC_Bullet_SmallBall;
		end
		for i=0, 1 do
			hdssBC(playerindex, 6, aimangle+(i*2-1)*nowindex*900, 0, x, y, speed, type, 14);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_13_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 40+level*4);
	elseif math.mod(timer, 4) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local nowindex = timer / 4;
		local speed = level * 0.05 + timer * 0.05 + 0.8;
		for i=0, 1 do
			hdssBC(playerindex, 6, aimangle+(i*2-1)*nowindex*900, 0, x, y, speed, CC_Bullet_Scale, 13);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_13_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 13);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_OVERPLAYER(playerindex, cx, cy, 180, 60, 60);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif math.mod(timer, 180) == 60 then
		local pattern = RANDT(0, 2);
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
		if pattern == 0 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_13_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 1 then
			hdssEB(CC_ShootChargeEnemyEID_13_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		elseif pattern == 2 then
			local baseangle = RANDT(1, 36000);
			local speed = 2.5;
			for i=0, 1 do
				hdssA(playerindex,
					{
						TIMERLESS, 60, SPEEDSETADD, -4,
						TIMERRANGE, 60, 90+level, SPEEDSETADD, 4,
						TIMERRANGE, 60, 120, ANGLESETADD, (i*2-1)*120,
						TIMERGREAT, 60, AND, YLESS, CenterY, THEN, BOUNCE, 8, 1
					}
				)
				local color = 2;
				if i == 1 then
					color = 14;
				end
				hdssBC(playerindex, 16+level, baseangle+i*(18000/(16+level)), 0, x, y, speed, CC_Bullet_Ring, color);
			end
			hdssA(playerindex);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_13_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 120);
	elseif math.mod(timer, 5) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local angle = aimangle - 3000;
		local leftrightindi = math.mod(hdss.Get(HDSS_ENI, playerindex), 2) * 2 - 1;
		if timer > 80 then
			angle = angle + (timer-80)*100*leftrightindi;
		end
		local speed = level * 0.1 + 4.4;
		hdssBC(playerindex, 6, angle, 16, x, y, speed, CC_Bullet_BigBall, 6);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_13_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	Edef_ShootChargeEnemyEID_13_1(playerindex, level, x, y, timer, px, py);
	return true;
end


function Edef_ShootChargeEnemyEID_13_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_13_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_13_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end