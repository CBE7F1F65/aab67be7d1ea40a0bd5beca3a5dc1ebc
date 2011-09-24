function Edef_ShootChargeEnemyEID_04_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, (140/(32-level)) * 10);
	elseif math.mod(timer, 10) == 0 then
		local bx = CenterW / 2 / (140/(32-level)+1) * (timer/10) + x - CenterW/2;
		local baseangle = 
		{
			hdssAMAP(playerindex, bx, y),
			hdssAMAP(playerindex, x*2-bx, y)
		};
		local speed = 2.2 + level * 0.1;
		local type = CC_Bullet_Scale;
		if math.mod(timer, 20) == 0 then
			type = CC_Bullet_SmallBall;
		end
		for i=0, 1 do
			hdss.Call(HDSS_BL,
				{
					playerindex, 8, baseangle[i+1], 0, 0, (x-bx)*2*i+bx, y, baseangle[i+1], 0, speed, 0.6, type, 2
				}
			)
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_04_2(playerindex, level, x, y, timer, px, py)
	if math.mod(timer, 5) == 0 then
		local baseangle = hdssAMAP(playerindex, x, y);
		local speed = 2.2 + level * 0.1;
		hdss.Call(HDSS_BL,
			{
				playerindex, 5, baseangle, 0, 0, x, y, baseangle, 0, speed, 0.6, CC_Bullet_Butterfly, 1
			}
		)
	end
	return true;
end

function Edef_ShootChargeEnemyEID_04_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 4);
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
			hdssEB(CC_ShootChargeEnemyEID_04_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		elseif pattern == 1 then
			local angle = hdssAMAP(playerindex, x, y);
			hdssSE(SE_BOSS_POWER_1, x);
			for i=0, 2 do
				local speed = 4.2 + level * 0.1;
				local color = 3;
				if i == 1 then
					color = 1;
				end
				hdss.Call(HDSS_BC,
					{
						playerindex, level+16, angle, i*12, x, y, speed, CC_Bullet_Butterfly, color, i*8+16
					}
				)
			end
		elseif pattern == 2 then
			hdssEB(CC_ShootChargeEnemyEID_04_3_C, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_04_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, (16+level)* 2);
	end
	local speed = 3.7 + level * 0.1 + RANDTF(-0.5, 0.5);
	local num = math.mod(timer, 2) + 2;
	local type = CC_Bullet_SmallBall;
	if num == 2 then
		type = CC_Bullet_Ring;
	end
	for i=0, num-1 do
		local angle = RANDT(1, 36000);
		if RANDT(0, 3) ~= 0 then
			angle = RANDT(4500, 13500);
		end
		hdssB(playerindex, x, y, angle, speed, type, 2);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_04_3_B(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_04_3_C(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 40);
	elseif math.mod(timer, 8) == 0 then
		hdssSE(CC_SE_Bullet_2, x);
		ePlayerSendExChase_04(playerindex, x, y, playerID, 0);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_04_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_04_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end