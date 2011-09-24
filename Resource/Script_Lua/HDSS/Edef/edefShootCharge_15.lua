function Edef_ShootChargeEnemyEID_15_1(playerindex, level, x, y, timer, px, py)
	if math.mod(timer, 5) == 0 then
		local nowindex = timer / 5;
		local enangle = hdss.Get(HDSS_ENANGLE, playerindex);
		local leftrightindi = math.mod(timer/6, 2)*2-1;
		local angle = enangle;
		local type = CC_Bullet_MiddleBall;
		if math.mod(nowindex, 2) == 0 then
			hdssA(playerindex,
				{
					TIMERRANGE, 75, 100+level*2, SPEEDSETADD, 4
				}
			)
			type = CC_Bullet_SmallBall;
		else
			hdssA(playerindex,
				{
					TIMERGREAT, 75, SPEEDSETADD, 3,
					TIMEREQUAL, 115+level*2, FADEOUT
				}
			)
			angle = angle+leftrightindi*RANDT(13500, 16000);
		end
		hdssB(playerindex, x, y, angle, 0, type, 14);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_15_2(playerindex, level, x, y, timer, px, py)
	if math.mod(timer, 5) == 0 then
		local nowindex = timer / 5;
		local enangle = hdss.Get(HDSS_ENANGLE, playerindex);
		local leftrightindi = math.mod(timer/6, 2)*2-1;
		local angle;
		local type = CC_Bullet_MiddleBall;
		if math.mod(nowindex, 2) == 0 then
			hdssA(playerindex,
				{
					TIMERRANGE, 75, 100+level*2, SPEEDSETADD, 4
				}
			)
			type = CC_Bullet_Scale;
			angle = 18000 + enangle;
		else
			hdssA(playerindex,
				{
					TIMERGREAT, 75, SPEEDSETADD, 3,
					TIMEREQUAL, 115+level*2, FADEOUT
				}
			)
			angle = enangle+leftrightindi*RANDT(13500, 16000);
		end
		hdssB(playerindex, x, y, angle, 0, type, 14);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_15_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 15);
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
			hdssEB(CC_ShootChargeEnemyEID_15_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, RANDT(1, 36000));
		elseif pattern == 1 then
			hdssEB(CC_ShootChargeEnemyEID_15_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, RANDT(0, 1)*2-1);
		elseif pattern == 2 then
			local angle = RANDT(1, 36000);
			for i=0, 3 do
				hdssEB(CC_ShootChargeEnemyEID_15_3_C, playerindex, x, y, angle+i*9000, 3.5, LConst_EnemyExType_AliceBlue, 240);
				hdssENSAIM(playerindex, level);
			end
		elseif pattern == 3 then
			local angle = RANDT(1, 36000);
			for i=0, 4 do
				hdssEB(CC_ShootChargeEnemyEID_15_3_D, playerindex, x, y, angle+i*7200, 3.5, LConst_EnemyExType_AliceBlue, 240);
				hdssENSAIM(playerindex, level);
			end
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_15_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 60);
	elseif math.mod(timer, 2) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local leftrightindi = math.mod(hdss.Get(HDSS_ENI, playerindex), 2)*2-1;
		local nowindex = timer / 2;
		hdssA(playerindex,
			{
				TIMEREQUAL, 9, ANGLESETADD, 16500,
				TIMERLESS, 60, ANGLESETADD, leftrightindi*150
			}
		)
		local type = CC_Bullet_Ring;
		if math.mod(nowindex, 2) == 0 then
			type = CC_Bullet_SmallBall;
		end
		local speed = level * 0.08 + 2.0;
		hdssBC(playerindex, 4+level/4, aimangle+nowindex*600*leftrightindi, 80, x, y, speed, type, 6);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_15_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 60);
	elseif math.mod(timer, 6) == 0 then
		local leftrightindi = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local nowindex = timer / 6;
		local angle = 9000 + (nowindex-5)*leftrightindi*900;
		local bx = x + hdss.Get(HDSS_COSA, angle) * 80;
		local by = y + hdss.Get(HDSS_SINA, angle) * 80;
		local speed = level * 0.05 + 2.4;
		hdssBC(playerindex, 8+level/2, angle, 0, bx, by, speed, CC_Bullet_Scale, 2);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_15_3_C(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 24);
	elseif math.mod(timer, 2) == 0 then
		local angle = hdss.Get(HDSS_ENANGLE, playerindex);
		local nowindex = 12 - timer / 2;
		local leftrightindi = (math.mod(hdss.Get(HDSS_ENANGLE, playerindex), 2)*2-1);
		hdssA(playerindex,
			{
				TIMERLESS, 45, SPEEDSETADD, -4,
				TIMEREQUAL, 60, ANGLESETADD, 18000-leftrightindi*nowindex*500,
				TIMERRANGE, 60, 100+level*2, SPEEDSETADD, 5
			}
		)
		for i=0, 2 do
			local color = 2;
			if i > 0 then
				color = i*2+10;
			end
			hdssB(playerindex, x, y, angle+leftrightindi*(-nowindex*500+i*3000), 2.0+i*0.1, CC_Bullet_Scale, color);
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_15_3_D(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 24);
	elseif math.mod(timer, 2) == 0 then
		local angle = hdss.Get(HDSS_ENANGLE, playerindex);
		local nowindex = 12 - timer / 2;
		local leftrightindi = (math.mod(hdss.Get(HDSS_ENANGLE, playerindex), 2)*2-1);
		hdssA(playerindex,
			{
				TIMERLESS, 45, SPEEDSETADD, -4,
				TIMEREQUAL, 60, ANGLESETADD, 18000+leftrightindi*nowindex*500,
				TIMERRANGE, 60, 100+level*2, SPEEDSETADD, 5
			}
		)
		for i=0, 2 do
			local color = 2;
			if i > 0 then
				color = i*2+10;
			end
			hdssB(playerindex, x, y, angle+leftrightindi*(-nowindex*500+i*3000), 2.0+i*0.1, CC_Bullet_Scale, color);
		end
		hdssA(playerindex);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_15_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end