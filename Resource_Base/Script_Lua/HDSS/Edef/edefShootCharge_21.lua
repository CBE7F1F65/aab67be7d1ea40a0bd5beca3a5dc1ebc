function Edef_ShootChargeEnemyEID_21_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 80);
		local cenx = helper_GetCenterX(playerindex);
		for i=0, level/4+1 do
		local aimx = cenx + RANDTF(-136, 136);
		local aimy = RANDTF(144, 272);
			ePlayerSendExChase_21(playerindex, aimx, aimy, 0xff, 0);
			hdssEFFSETUP(playerindex, LConst_effid_shootcharge, aimx, aimy, LConst_ShootCharge_EnemyDelay);
			hdssEFFSETUP(1-playerindex, LConst_effid_shootcharge, aimx+(1-playerindex*2)*TotalW/2, aimy, LConst_ShootCharge_EnemyDelay);
		end
	elseif timer == 80 then
		local speed = level * 0.1 + 1.6;
		local type = CC_Bullet_SmallBall;
		for i=0, 1 do
			if i == 1 then
				type = CC_Bullet_Kunai;
			end
			hdssBC(playerindex, 48+level, RANDT(1, 36000), 0, x, y, speed, type, 5);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_21_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 80);
		local cenx = helper_GetCenterX(playerindex);
		for i=0, level/4+2 do
		local aimx = cenx + RANDTF(-136, 136);
		local aimy = RANDTF(144, 272);
			ePlayerSendExChase_21(playerindex, aimx, aimy, 0xff, 0);
			hdssEFFSETUP(playerindex, LConst_effid_shootcharge, aimx, aimy, LConst_ShootCharge_EnemyDelay);
			hdssEFFSETUP(1-playerindex, LConst_effid_shootcharge, aimx+(1-playerindex*2)*TotalW/2, aimy, LConst_ShootCharge_EnemyDelay);
		end
	elseif timer == 80 then
		for i=0, 1 do
			local speed = level * 0.1 + 1.6 + i * 0.3;
			hdssBC(playerindex, 48+level, RANDT(1, 36000), 0, x, y, speed, CC_Bullet_Kunai, 5);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_21_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 21);
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
		local cenx = helper_GetCenterX(playerindex);
		if pattern == 0 then
			hdssEB(CC_ShootChargeEnemyEID_21_3_A, playerindex, cenx, CenterY, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, RANDT(1, 36000));
		elseif pattern == 1 then
			hdssEB(CC_ShootChargeEnemyEID_21_3_B, playerindex, cenx, CenterY, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		elseif pattern == 2 then
			hdssEB(CC_ShootChargeEnemyEID_21_3_C, playerindex, cenx, CenterY, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_21_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 90);
	elseif math.mod(timer, 2) == 0 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local leftrightindi = math.mod(hdss.Get(HDSS_ENI, playerindex), 2) * 2 - 1;
		hdssA(playerindex,
			{
				TIMEREQUAL, 9, ANGLESETADD, leftrightindi * (math.mod(timer, 15)+8) * 160 + 18000,
				TIMERRANGE, 90, 120, SPEEDSETADD, 6,
				TIMEREQUAL, 200, FADEOUT 
			}
		)
		hdss.Call(
			HDSS_BC,
			{
				playerindex, 2, aimangle + leftrightindi * timer * 200, 80, x, y, 0, CC_Bullet_Amulet, 4, 8, 16
			}
		)
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_21_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 90);
	elseif math.mod(timer, 4) == 0 then
		local nowindex = timer / 2;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local leftrightindi = math.mod(hdss.Get(HDSS_ENI, playerindex), 2) * 2 - 1;
		if math.mod(nowindex, 2) == 0 then
			hdssA(playerindex,
				{
					TIMEREQUAL, 9, ANGLESETADD, leftrightindi * 17500,
					TIMERRANGE, 90, 120, SPEEDSETADD, 6,
					TIMEREQUAL, 200, FADEOUT 
				}
			)
		else
			hdssA(playerindex,
				{
					TIMERRANGE, 90, 120, SPEEDSETADD, 6,
					TIMEREQUAL, 200, FADEOUT 
				}
			)
		end
		hdss.Call(
			HDSS_BC,
			{
				playerindex, 4, aimangle + leftrightindi * nowindex * 200, 80, x, y, 0, CC_Bullet_Amulet, 3, 8, 16
			}
		)
		hdssA(playerindex);
	end
	return true;
end


function Edef_ShootChargeEnemyEID_21_3_C(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 90);
	elseif math.mod(timer, 8) == 0 then
		local nowindex = timer / 4;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local leftrightindi = math.mod(hdss.Get(HDSS_ENI, playerindex), 2) * 2 - 1;
		hdssA(playerindex,
			{
				TIMEREQUAL, 9, ANGLESETADD, leftrightindi * (math.mod(nowindex, 9)-4) * 30 + 18000,
				TIMERRANGE, 90, 120, SPEEDSETADD, 6,
			}
		)
		hdss.Call(
			HDSS_BC,
			{
				playerindex, 8, aimangle + leftrightindi * nowindex * 200, 80, x, y, 0, CC_Bullet_Amulet, 4, 8, 16
			}
		)
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_21_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_21_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end