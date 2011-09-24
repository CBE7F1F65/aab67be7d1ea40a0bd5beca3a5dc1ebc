function Edef_ShootChargeEnemyEID_22_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 80);
	end
	if math.mod(timer, 12) == 0 then
		local turn = timer/12;
		local num = level * 1.5;
		local angle = level * 1340 + turn * 120;
		local r = 64 - turn * 8;
		local speed = turn * 0.08 + level * 0.1 + 1.2;
		hdssA(playerindex,
			{
				TIMEREQUAL, 9, ANGLESETADD, 18000 + turn * 400
			}
		)
		hdssBC(playerindex, num, angle, r, x, y, speed, CC_Bullet_Shuttle, turn+7);
		hdssBC(playerindex, num, angle+18000/num, r, x, y, speed, CC_Bullet_SmallBall, turn+7);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_22_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 60);
	end
	local timemod = 64;
	if level > 12 then
		timemod = 32;
	end
	if math.mod(timer, timemod) == 1 then
		local turn = math.floor(timer/timemod);
		local length = 80 + turn * 20;
		local num = level * 2;
		if level <= 12 then
			num = num * 1.5;
		end
		local space = length/(num-2);
		local tr = length / 1.618;
		
		hdssA(playerindex,
			{
				TIMERRANGE, 32, 64, SPEEDSETADD, level/5+2
			}
		)
		for i=0, 4 do
			local baseangle = i*7200 + turn * 18000;
			local tx = tr * hdss.Get(HDSS_COSA, baseangle+19800) + x;
			local ty = tr * hdss.Get(HDSS_SINA, baseangle+19800) + y;
			local angle = baseangle + 9000;
			hdss.Call(
				HDSS_BL,
				{
					playerindex, num, baseangle, space, 0, tx, ty, angle, -27000/num + turn * 18000, 0, 0, CC_Bullet_Shuttle, turn*4+2
				}
			)
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_22_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 22);
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
			hdssEB(CC_ShootChargeEnemyEID_22_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		elseif pattern == 1 then
			hdssEB(CC_ShootChargeEnemyEID_22_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		elseif pattern == 2 then
			local cenx = helper_GetCenterX(playerindex);
			if px < cenx then
				x = cenx + TotalW/8;
			else
				x = cenx - TotalW/8;
			end
			x = x + RANDTF(-16, 16);
			hdssEB(CC_ShootChargeEnemyEID_22_3_C, playerindex, x, 0, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		elseif pattern == 3 then
			local baseangle = hdssAMAP(playerindex, x, y);
			for i=0, 2 do
				local angle = (i-1)*2500+baseangle;
				local speed = level * 0.2 + 1.2;
				local num = level*2/3;
				hdssB(playerindex, x, y, angle, speed, CC_Bullet_BigBall, 3, 9);
				hdssA(playerindex,
					{
						TIMEREQUAL, 9, ANGLESET, angle
					}
				)
				hdssBC(playerindex, num, angle, 16, x, y, speed, CC_Bullet_SmallBall, 6);
				hdssA(playerindex);
			end
		else
			hdssEB(CC_ShootChargeEnemyEID_22_3_E, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);	
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_22_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 18);
	else
		local turn = 0;
		if timer > 10 then
			turn = 1;
		end
		local num = level + 10;
		local baseangle = hdss.Get(HDSS_SIGN, level) * timer * 120 + level * 1700 + hdss.Get(HDSS_SEED);
		local baser = timer * 20 + 32;
		hdssA(playerindex,
			{
				TIMEREQUAL, 64, FADEOUT
			}
		)
		hdss.Call(
			HDSS_BC,
			{
				playerindex, num, baseangle, baser, x, y, 0, CC_Bullet_Shuttle, turn * 2 + 2, 16, 16
			}
		)
		if level > 12 then
			hdss.Call(
				HDSS_BC,
				{
					playerindex, num, 18000-baseangle, baser, x, y, 0, CC_Bullet_Shuttle, turn + 5, 16, 16
				}
			)
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_22_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 10);
	elseif math.mod(timer, 4) == 0 then
		local turn = timer / 4;
		local length = 80 + turn * 20;
		local num = level * 2;
		local space = length/(num-2);
		local tr = length / 1.618;
		hdssA(playerindex,
			{
				TIMEREQUAL, 30, SPEEDSETMUL, 10000,
				TIMERRANGE, 32, 64, SPEEDSETADD, level/5+2
			}
		)
		for i=0, 4 do
			local baseangle = i*7200 + turn * 18000;
			local tx = tr * hdss.Get(HDSS_COSA, baseangle+19800) + x;
			local ty = tr * hdss.Get(HDSS_SINA, baseangle+19800) + y;
			local angle = baseangle + 9000;
			hdss.Call(
				HDSS_BL,
				{
					playerindex, num, baseangle, space, 0, tx, ty, angle, -6000/num + i * 600, 0, 0.001, CC_Bullet_Shuttle, turn*4+2
				}
			)
		end
		hdssA(playerindex);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_22_3_C(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		local movespeed = 12-level * 0.5
		hdssEA(
			playerindex, ENAC_DIRECTSET_XYSOAOOO,
			{
				x, y, movespeed
			},
			{
				9000
			}
		)
	end
	local angle = timer * 900 + level * 1300 + hdss.Get(HDSS_SEED);
	local type = CC_Bullet_Shuttle;
	if math.mod(timer, 2) == 0 then
		type = CC_Bullet_SmallBall;
	end
	local addval = level * 0.3 + 1.6;
	hdssA(playerindex,
		{
			TIMERRANGE, 128, 160, SPEEDSETADD, addval
		}
	)
	hdssB(playerindex, x, y, angle, 0.1, type, 1);
	hdssA(playerindex);
	return true;
end

function Edef_ShootChargeEnemyEID_22_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_22_3_E(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	local totalturn = level;
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, totalturn*2+1);
	elseif math.mod(timer, 2) == 0 then
		local turn = timer / 2;
		local angle = 36000/totalturn*turn + level * 1340 + hdss.Get(HDSS_SEED);
		local speed = level * 0.2 + 1.2;
		hdss.Call(
			HDSS_BEB,
			{
				playerindex, x, y, angle, speed, CC_Bullet_ShuttleBeam, 6, 96+turn*4
			}
		)
	end
	return true;
end