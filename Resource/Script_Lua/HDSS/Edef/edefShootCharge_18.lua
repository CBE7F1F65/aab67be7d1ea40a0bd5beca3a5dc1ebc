function Edef_ShootChargeEnemyEID_18_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 1);
		local num = level/4+4;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = level * 0.1 + 3.0;
		hdssA(playerindex,
			{
				BOUNCEEQUAL, 0, AND, YLESS, 400, THEN, BOUNCE, 16, 1
			}
		)
		hdssBC(playerindex, num, aimangle, 0, x, y, speed+0.8, CC_Bullet_HugeBall, 0);
		local types = {CC_Bullet_RedFireBall, CC_Bullet_Ring, CC_Bullet_SmallBall, CC_Bullet_SmallBall}
		for i=0, 16 do
			hdss.Call(
				HDSS_BC,
				{
					playerindex, num, aimangle, 0, x+RANDT(-16, 16), y+RANDT(-16, 16), speed+RANDTF(0, 0.5), types[math.mod(i, 4)+1], 2, i+8
				}
			)
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_18_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 1);
		local num = level/4+4;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = level * 0.1 + 3.0;
		hdssA(playerindex,
			{
				BOUNCEEQUAL, 0, AND, YLESS, 400, THEN, BOUNCE, 16, 1
			}
		)
		hdssBC(playerindex, num, aimangle, 0, x, y, speed+0.8, CC_Bullet_HugeBall, 0);
		local types = {CC_Bullet_RedFireBall, CC_Bullet_MiddleBall, CC_Bullet_Ring, CC_Bullet_SmallStar}
		for i=0, 16 do
			hdss.Call(
				HDSS_BC,
				{
					playerindex, num, aimangle, 0, x+RANDT(-16, 16), y+RANDT(-16, 16), speed+RANDTF(0, 0.5), types[math.mod(i, 4)+1], 2, i+8
				}
			)
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_18_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 18);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_OVERPLAYER(playerindex, cx, cy, 120, 60, 60);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif math.mod(timer, 120) == 60 then
		local pattern = RANDT(0, 3);
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
		if pattern == 0 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_18_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 1 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_18_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 2 then
			for i=0, level/8+2.5 do
				ePlayerSendExChase_18(playerindex, x+RANDT(-40, 40), y+RANDT(-40, 40), 0xff, 0, RANDT(30, 90));
			end
		elseif pattern == 3 then
			hdssA(playerindex,
				{
					BOUNCEEQUAL, 0, AND, YLESS, 400, THEN, BOUNCE, 8, 1
				}
			)
			local speed = level * 0.1 + 2.4;
			hdssBC(playerindex, 48+level, RANDT(1, 36000), 0, x, y, speed, CC_Bullet_Shuttle, 2);
			hdssA(playerindex);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_18_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 32+level/2);
	end
	local type = CC_Bullet_Kunai;
	local rollval = hdss.Get(HDSS_ROLL, timer, 16) - 8;
	local angle = -9000+rollval*(9000/8);
	local speed = rollval * 0.3;
	if speed < 0 then
		speed = -speed;
	end
	speed = speed + 2.5;
	for i=0, 3 do
		if i > 1 then
			type = CC_Bullet_SmallBall;
		end
		hdssA(playerindex,
			{
				TIMERLESS, 30, SPEEDSETADD, -4,
				TIMEREQUAL, 45, ANGLESET, 9000,
				TIMERRANGE, 45, 75+level*2, SPEEDSETADD, i+1
			}
		)
		hdssB(playerindex, x, y, angle + i * 150, speed, type, 2);
	end
	hdssA(playerindex);
	return true;
end

function Edef_ShootChargeEnemyEID_18_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 60);
	end
	local speed = global.DIST(x, y, px, py) / 8;
	if speed < 16 then
		speed = 16;
	end
	for i=0, 1 do
		local angle = hdssRMAP(playerindex, x, y, (i*2-1)*60);
		hdssB(playerindex, x, y, angle, speed, CC_Bullet_MiddleBall, 2, 1);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_18_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_18_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_18_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end