function Edef_ShootChargeEnemyEID_23_1(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 80);
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		ePlayerSendExChase_23(playerindex, x, y, 0xff, 0, aimangle);
	elseif timer == 74 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local cosval = hdss.Get(HDSS_COSA, aimangle+9000);
		local sinval = hdss.Get(HDSS_SINA, aimangle+9000);
		hdssA(playerindex,
			{
				TIMERRANGE, 45, 90+level*2, SPEEDSETADD, 4
			}
		)
		for i=0, 7 do
			local bx = x + (i-3.5)*cosval*16;
			local by = y + (i-3.5)*sinval*16;
			local type = CC_Bullet_SmallStar;
			if math.mod(i, 2) == 1 then
				type = CC_Bullet_SmallBall;
			end
			hdss.Call(
				HDSS_BL,
				{
					playerindex, 25, aimangle, 12, 12, bx, by, aimangle, (i-3.5)*750, 1.0, -0.015, type, 2
				}
			)
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_23_2(playerindex, level, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 80);
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		ePlayerSendExChase_23(playerindex, x, y, 0xff, 0, aimangle);
	elseif timer == 74 then
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local cosval = hdss.Get(HDSS_COSA, aimangle+9000);
		local sinval = hdss.Get(HDSS_SINA, aimangle+9000);
		hdssA(playerindex,
			{
				TIMERRANGE, 45, 90+level*2, SPEEDSETADD, 4
			}
		)
		for i=0, 7 do
			local bx = x + (i-3.5)*cosval*16;
			local by = y + (i-3.5)*sinval*16;
			local color = 2;
			if math.mod(i, 2) == 1 then
				color = 6;
			end
			hdss.Call(
				HDSS_BL,
				{
					playerindex, 25, aimangle, 12, 12, bx, by, aimangle, (i-3.5)*750, 1.0, -0.015, CC_Bullet_SmallStar, color
				}
			)
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_ShootChargeEnemyEID_23_3(playerindex, level, x, y, timer, px, py, overbgs)
	if overbgs == nil or overbgs == false then
		_ePlayerShootCharge_3_SetBGS(playerindex, 23);
	end
	local toindex = hdss.Get(HDSS_D, LConst_Desc_HatateIndex+playerindex);
	return LTable_EnemyEIDFunction[toindex*8+CC_ShootChargeEnemyEID_00_3-CC_EnemyEID_Lily+1][2](playerindex, level, x, y, timer, px, py, true);
end

function Edef_ShootChargeEnemyEID_23_3_A(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_23_3_B(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_23_3_C(playerindex, level, x, y, timer, px, py)
	return true;
end

function Edef_ShootChargeEnemyEID_23_3_D(playerindex, level, x, y, timer, px, py)
	return true;
end


function Edef_ShootChargeEnemyEID_23_3_E(playerindex, level, x, y, timer, px, py)
	return true;
end