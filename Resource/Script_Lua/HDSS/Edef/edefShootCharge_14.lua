function Edef_ShootChargeEnemyEID_14_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 32);
	elseif math.mod(timer, 2) == 0 and math.mod(timer, 16) < (8+(level-2)/2) then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local parttimer = math.mod(timer, 16);
		local type = CC_Bullet_SmallBall;
		local addangle = 12000 - parttimer * 150;
		if timer < 16 then
			type = CC_Bullet_GunBullet;
			addangle = -addangle;
		end
		hdssA(playerindex,
			{
				TIMERLESS, 45, SPEEDSETADD, -6,
				TIMEREQUAL, 75+parttimer*2, ANGLESETADD, addangle,
				TIMERRANGE, 75+parttimer*2, 100+level*2+parttimer*2, SPEEDSETADD, 6
			}
		)
		hdssBC(playerindex, 16, aimangle, 0, x, y, 2.5, type, 2);
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_14_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 64);
	elseif math.mod(timer, 32) == 8 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local leftrightindi = -1;
		if timer > 32 then
			leftrightindi = 1;
		end
		local addangle = 300;
		for i=0, 3 do
			for j=0, level+12 do
				local angle = aimangle + i * 9000 + j * (9000/(level+12)) + (leftrightindi+1)*4500;
				hdssA(playerindex,
					{
						TIMERLESS, 45, SPEEDSETADD, -6,
						TIMEREQUAL, 75+j*4, ANGLESETADD, addangle*j+6000*leftrightindi-9000,
						TIMERRANGE, 75+j*4, 100+level*2+j*4, SPEEDSETADD, 6
					}
				)
				hdssB(playerindex, x, y, angle, 2.5, CC_Bullet_GunBullet, 2);
			end
		end
		hdssA(playerindex);
		
	end
	return true;
end

function Edef_ShootChargeEnemyEID_14_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 14);
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
			hdssEB(CC_ShootChargeEnemyEID_14_3_A, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level);
		elseif pattern == 1 then
			hdssEB(CC_ShootChargeEnemyEID_14_3_B, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
			hdssENSAIM(playerindex, level, 0, 0, RANDT(1, 36000));
		elseif pattern == 2 then
			for i=0, 2 do
				ePlayerSendExChase_14(playerindex, x, y, 0xff, 0, (i-1)*1500+9000, 2.0);
			end
		end
	end
	return true;
end

function Edef_ShootChargeEnemyEID_14_3_A(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 88);
	elseif math.mod(timer, 11) == 0 then
		hdssBC(playerindex, level+32, RANDT(1, 36000), 0, x, y, level*0.08+1.8, CC_Bullet_GunBullet, 2);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_14_3_B(playerindex, level, x, y, timer, px, py)
	if _ePlayerShootCharge_CheckBoss(playerindex) then
		return true;
	end
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 120);
	end
	local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
	local speed = level * 0.1 + 3.5;
	hdssB(playerindex, x, y, timer*500+aimangle, speed, CC_Bullet_GunBullet, 2);
	return true;
end


function Edef_ShootChargeEnemyEID_14_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_14_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_14_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end