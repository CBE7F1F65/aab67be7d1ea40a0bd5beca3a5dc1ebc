function Edef_ShootChargeEnemyEID_05_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, (level/3+4)*6);
	elseif math.mod(timer, 6) == 0 then
		local nowturn = timer / 6;
		local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex) + nowturn * 200;
		local speed = level * 0.1 + nowturn * 0.5 + 1.8;
		for i=0, 1 do
			local type = CC_Bullet_Butterfly;
			if i == 1 then
				type = CC_Bullet_SmallBall;
			end
			hdssBC(playerindex, 8+(level/4), (i*2-1)*angle, 0, x, y, speed/(i+1), type, 4);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_05_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, (level/3+4)*6);
	elseif math.mod(timer, 6) == 0 then
		local nowturn = timer / 6;
		local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex) + nowturn * 200;
		local speed = level * 0.1 + nowturn * 0.5 + 1.8;
		for i=0, 1 do
			local type = CC_Bullet_Butterfly;
			if i == 0 then
				type = CC_Bullet_RedFireBall;
			end
			hdssBC(playerindex, 8+(level/4), (i*2-1)*angle, 0, x, y, speed/(i+1), type, i+3);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_05_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 5);
	end
	if timer == 1 then
		local cx = helper_GetCenterBossX(playerindex);
		local cy = CenterBossY;
		hdssEA_REPOSITION(playerindex, 60);
		local pattern = 0;
		hdssSD(LConst_Desc_BossPattern+playerindex, pattern);
	elseif timer == 810 then
		hdssEA_FADEOUT(playerindex, -1);
	elseif timer > 60 and math.mod(timer-60, 180) < 60 then
		if math.mod(timer, 15) == 0 then
			local aimangle;
			local nowindex = math.mod(timer-60, 180) / 15;
			if nowindex == 0 then
				aimangle = hdssAMAP(playerindex, x, y);
				hdssENSAIM(playerindex, level, 0, 0, aimangle);
			else
				aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
			end
			local num = level;
			local leftrightindi = math.mod(nowindex, 2)*2-1;
			local angleoffset = leftrightindi * 200;
			for i=0, 3 do
				local speed = level * 0.1 + 2.0 + i * 0.5;
				hdssA(playerindex,
					{
						TIMEREQUAL, 9, ANGLESETADD, leftrightindi*4500-i*150
					}
				)
				hdssBC(playerindex, num, aimangle+angleoffset, 80, x, y, speed, CC_Bullet_Butterfly, 1);
				hdssA(playerindex,
					{
						TIMEREQUAL, 9, ANGLESETADD, leftrightindi*13500+i*150
					}
				)
				hdssBC(playerindex, num, aimangle+angleoffset, 80, x, y, speed, CC_Bullet_Butterfly, 2);
			end
			hdssA(playerindex);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_05_3_A(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_05_3_B(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_05_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_05_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_05_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end