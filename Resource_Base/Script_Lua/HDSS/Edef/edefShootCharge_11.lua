function Edef_ShootChargeEnemyEID_11_1(playerindex, level, x, y, timer, px, py)
	if math.mod(timer, 6) == 0 then
		hdssA(playerindex,
			{
				TIMERRANGE, 360, 420+level*4, SPEEDSETADD, 3
			}
		)
		local nowindex = timer / 6;
		local type = CC_Bullet_SmallBall;
		if math.mod(nowindex, 2) == 1 then
			type = CC_Bullet_Scale;
		end
		hdssB(playerindex, x, y, -9000, 0.4, type, 2)
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_11_2(playerindex, level, x, y, timer, px, py)
	if math.mod(timer, 6) == 0 then
		hdssA(playerindex,
			{
				TIMERRANGE, 360, 420+level*4, SPEEDSETADD, 3
			}
		)
		local nowindex = timer / 6;
		local color = 2;
		if math.mod(nowindex, 2) == 1 then
			color = 13;
		end
		hdssB(playerindex, x, y, -9000, 0.4, CC_Bullet_Scale, color)
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_11_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 11);
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
			local baseangle = hdssAMAP(playerindex, x, y);
			local speed = 3.0;
			local basespeed = level * 0.1 + 0.7;
			for i=0, 1 do
				hdssA(playerindex,
					{
						TIMERLESS, 50, SPEEDSETADD, -6,
						TIMEREQUAL, 50, ANGLESETADD, -(i*2-1)*10000,
						TIMEREQUAL, 50, SPEEDSET, basespeed*100;
					}
				)
				for j=0, 1 do
					local angle = baseangle + (i*2-1)*(6000 + j*1500);
					hdss.Call(HDSS_BL,
						{
							playerindex, 4+level/4, angle, 0, 0, x, y, angle, 0, speed, 0.4, CC_Bullet_LegatoQuaver, 2
						}
					)
				end
			end
			hdssA(playerindex);
		elseif pattern == 1 then
			local angle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_11_3_B, playerindex, x, y, angle, 3, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		elseif pattern == 2 then
			hdssEB(CC_ShootChargeEnemyEID_11_3_C, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_11_3_A(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_11_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 45);
	elseif math.mod(timer, 15) == 0 then
		local speed = level * 0.1 + 1.0;
		hdssBC(playerindex, 8+level/2, RANDT(1, 36000), 0, x, y, speed, CC_Bullet_LegatoQuaver, 2);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_11_3_C(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 40+level*4);
	end
	local num = 2;
	local type = CC_Bullet_Shuttle;
	local speed = level*0.05+0.6+RANDTF(-0.2, 0.2);
	if math.mod(timer, 2) == 0 then
		num = 4;
		type = CC_Bullet_SmallBall;
	end
	local bx = x + RANDTF(-48, 48);
	local by = y + RANDTF(-48, 48);
	hdssBC(playerindex, num, RANDT(1, 36000), 0, bx, by, speed, type, 2);
	return true;
end

function Edef_ShootChargeEnemyEID_11_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_11_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end