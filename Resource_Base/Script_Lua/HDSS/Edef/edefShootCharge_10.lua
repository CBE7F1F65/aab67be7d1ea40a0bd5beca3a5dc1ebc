function Edef_ShootChargeEnemyEID_10_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 300+level*7.5);
	elseif math.mod(timer, 3) == 0 then
		local aimx = hdss.Get(HDSS_ENAIMX, playerindex);
		local aimy = hdss.Get(HDSS_ENAIMY, playerindex);
		local angle = hdssAMA(x, y, aimx, aimy);
		local addangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		hdssA(playerindex,
			{
				TIMERLESS, 30, ANGLESETADD, addangle,
				TIMERRANGE, 30, 60, ANGLESETADD, -addangle*1.5,
				TIMERRANGE, 60, 90, ANGLESETADD, addangle*1.5,
				TIMERRANGE, 90, 110, ANGLESETADD, -addangle
			}
		)
		local speed = level * 0.1 + 3.0;
		local type = CC_Bullet_SmallBall;
		if math.mod(timer/3, 2) == 0 then
			type = CC_Bullet_Shuttle;
		end
		hdssB(playerindex, x, y, angle, speed, type, 2);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_10_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 350+level*10);
	elseif math.mod(timer, 4) == 0 then
		local aimx = hdss.Get(HDSS_ENAIMX, playerindex);
		local aimy = hdss.Get(HDSS_ENAIMY, playerindex);
		local angle = hdssAMA(x, y, aimx, aimy);
		local addangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		hdssA(playerindex,
			{
				TIMERLESS, 30, ANGLESETADD, addangle,
				TIMERRANGE, 30, 60, ANGLESETADD, -addangle*1.5,
				TIMERRANGE, 60, 90, ANGLESETADD, addangle*1.5,
				TIMERRANGE, 90, 110, ANGLESETADD, -addangle
			}
		)
		local speed = level * 0.1 + 3.0;
		local type = CC_Bullet_Scale;
		hdssB(playerindex, x, y, angle, speed, type, 6);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_10_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 10);
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
			hdssEB(CC_ShootChargeEnemyEID_10_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 1 then
			local aimangle = hdssAMAP(playerindex, x, y);
			hdssEB(CC_ShootChargeEnemyEID_10_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, aimangle);
		elseif pattern == 2 then
		end
	end
	
	local savedpattern = hdss.Get(HDSS_D, LConst_Desc_BossPattern+playerindex);
	if savedpattern == 2 then
		if math.mod(timer, 180) >= 60 and math.mod(timer, 30) == 0 then
			hdssEA_OVERPLAYER(playerindex, x, y, 30, 30, 30);
			if math.mod(timer, 180) >= 90 then
				local baseangle = hdssAMAP(playerindex, x, y);
				local speed = level*0.08 + 1.8;
				for i=0, 2 do
					local angle = baseangle+(i-1)*3000;
					local type = CC_Bullet_Quaver;
					if i == 1 then
						type = CC_Bullet_LegatoQuaver;
					end
					hdss.Call(HDSS_BL, 
						{
							playerindex, 7, angle, 0, 0, x, y, angle, 0, speed, 0.5, type, 1
						}
					);
				end
			end
		elseif math.mod(timer, 180) == 0 then
			hdssEA_OVERPLAYER(playerindex, x, y, 180, 30, 60);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_10_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 32+level*4);
	end
	local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
	local speed = level * 0.05 + 1.8;
	hdssA(playerindex,
		{
			TIMERLESS, 80, SPEEDSETADD, 1
		}
	)
	hdssB(playerindex, x, y, aimangle, speed, CC_Bullet_Quaver, 1);
	hdssA(playerindex);
	return true;
end

function Edef_ShootChargeEnemyEID_10_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 64+level*8);
	end
	local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
	local angle = aimangle + (timer-32) * 835;
	local speed = level * 0.05 + 1.5;
	local type;
	if math.mod(timer, 2) == 0 then
		type = CC_Bullet_Quaver;
	else
		type = CC_Bullet_LegatoQuaver;
	end
	for i=0, 1 do
		if i == 1 then
			type = CC_Bullet_SmallBall;
		end
		hdssB(playerindex, x, y, angle, speed, type, 1);
		angle = 18000 - angle;
	end
	return true;
end


function Edef_ShootChargeEnemyEID_10_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_10_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_10_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end