function Edef_ShootChargeEnemyEID_12_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 0);
	end
	local baseangle = RANDT(1, 36000);
	local speed = level * 0.08 + 1.8;
	for i=0, 3 do
		local type = CC_Bullet_Shuttle;
		if math.mod(i, 2) == 0 then
			type = CC_Bullet_SmallBall;
		end
		hdssA(playerindex,
			{
				TIMERLESS, 60, SPEEDSETADD, -5,
				TIMERRANGE, 60, 120, SPEEDSETADD, 5,
				TIMERRANGE, 60, 120, ANGLESETADD, (math.floor(i/2)*2-1)*120
			}
		)
		hdssBC(playerindex, 16, baseangle+i*562.5, 0, x, y, speed, type, 2);
	end
	hdssA(playerindex);

	return true;
end

function Edef_ShootChargeEnemyEID_12_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 0);
	end
	local baseangle = RANDT(1, 36000);
	local speed = level * 0.08 + 1.8;
	for i=0, 3 do
		local color = 2;
		if math.mod(i, 2) == 0 then
			color = 15;
		end
		hdssA(playerindex,
			{
				TIMERLESS, 60, SPEEDSETADD, -5,
				TIMERRANGE, 60, 120, SPEEDSETADD, 5,
				TIMERRANGE, 60, 120, ANGLESETADD, (math.floor(i/2)*2-1)*120
			}
		)
		hdssBC(playerindex, 16, baseangle+i*562.5, 0, x, y, speed, CC_Bullet_Shuttle, color);
	end
	hdssA(playerindex);
	return true;
end

function Edef_ShootChargeEnemyEID_12_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 12);
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
			local baseangle = RANDT(1, 36000);
			local speed = 2.5;
			for i=0, 1 do
				hdssA(playerindex,
					{
						TIMERLESS, 60, SPEEDSETADD, -4,
						TIMERRANGE, 90, 120+level*4, SPEEDSETADD, 4,
						TIMERRANGE, 90, 150, ANGLESETADD, (i*2-1)*120
					}
				)
				hdssBC(playerindex, 24, baseangle+i*750, 0, x, y, speed, CC_Bullet_BigBall, 1);
			end
			hdssA(playerindex);
		elseif pattern == 1 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_12_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 2 then
			hdssEB(CC_ShootChargeEnemyEID_12_3_C, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_12_3_A(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_12_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 84);
	elseif math.mod(timer, 14) == 0 then
		local nowindex = timer / 14;
		local type = CC_Bullet_Shuttle;
		if nowindex >= 2 and nowindex < 4 then
			type = CC_Bullet_SmallBall;
		end
		local leftrightindi = math.mod(nowindex, 2)*2-1;
		local baseangle = hdssAMAP(playerindex, x, y);
		local speed = level * 0.08 + 2.0;
		for i=0, 12 do
			hdssB(playerindex, x, y, baseangle+leftrightindi*(i+4)*270, speed, type, 2);
		end
	end
	return true;
end


function Edef_ShootChargeEnemyEID_12_3_C(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 24+level*2);
	elseif math.mod(timer, 8) == 0 then
		ePlayerSendExChase_12(playerindex, x, y, 0xff, 0);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_12_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_12_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end