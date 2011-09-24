function Edef_SendExChase_00(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_01(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_02(playerindex, rank, x, y, timer, px, py)
	
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 50);
	elseif math.mod(timer, 10) == 0 then
		local angle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = 1.8 + rank * 0.05;
		local xposcon = XGREAT;
		if helper_GetCenterX(playerindex) < TotalCenterX then
			xposcon = XLESS;
		end
		hdssB(playerindex, x, y, angle, speed, CC_BulletEx_SakuyaFake, 3);
		hdssA(1-playerindex, 
			{
				xposcon, TotalCenterX, REMAIN
			}
		);
		hdssB(1-playerindex, x, y, angle, speed, CC_BulletEx_Sakuya, 3);
		hdssA(1-playerindex);
	end
	
	return true;
end

function Edef_SendExChase_03(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_04(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_05(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_06(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_07(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_08(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_09(playerindex, rank, x, y, timer, px, py)
	if timer == 1 then
		local addangle = RANDT(25, 35) * (RANDT(0, 1)*2-1);
		hdssEA(playerindex, ENAC_TURNANGLE_OOOOATOE,
			{
			},
			{
				addangle, 0, 0, 0xffff
			}
		)
	elseif math.mod(timer, 10) == 0 then
		local angle = hdss.Get(HDSS_ENANGLE, playerindex) + 9000;
		hdssA(playerindex,
			{
				TIMERRANGE, 40, 90, SPEEDSETADD, 5
			}
		)
		hdss.Call(
			HDSS_BC,
			{
				playerindex, 2, angle, 3, x, y, 0, CC_Bullet_Scale, 6, 8, 24
			}
		)
		hdssA(playerindex);
	end
	return true;
end

function Edef_SendExChase_10(playerindex, rank, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 56);
	elseif math.mod(timer, 4) == 0 then
		hdssA(playerindex,
			{
				TIMERLESS, 60, SPEEDSETADD, 3,
				TIMERLESS, 60, ANGLESETADD, RANDT(-80, 80)
			}
		)
		hdssB(playerindex, x, y+16, 9000, 1.0, CC_Bullet_Quaver, 1);
		hdssA(playerindex);
	end
	return true;
end

function Edef_SendExChase_11(playerindex, rank, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 52);
	elseif timer > 16 then
		if math.mod(timer, 4) == 0 then
			local angle = hdssAMAP(playerindex, x, y);
			hdssB(playerindex, x, y, angle, 0.75, CC_Bullet_Quaver, 2);
		end
	end
	return true;
end

function Edef_SendExChase_12(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_13(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_14(playerindex, rank, x, y, timer, px, py)
	if hdssCOLLISION_CIRCLE(x, y, px, py, 96, true) then
		hdssEA_FADEOUT(playerindex, -1);
		hdssA(playerindex,
			{
				TIMEREQUAL, 96, FADEOUT
			}
		)
		hdssB(playerindex, x, y, 9000, 0, CC_BulletEx_Reisen, 0, 32);
		hdssA(playerindex);
	end
	return true;
end

function Edef_SendExChase_15(playerindex, rank, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 32);
	elseif timer == 16 then
		local angle = hdssAMAP(playerindex, x, y);
		for i=0, 2 do
			hdssA(playerindex,
				{
					TIMERLESS, 60, SPEEDSETADD, -4-i,
					TIMEREQUAL, 60, ANGLESETADD, 18000,
					TIMEREQUAL, 60, SPEEDSET, 250
				}
			)
			hdssBC(playerindex, 12, angle, 0, x, y, 2.5+i*0.6, CC_Bullet_Scale, i+12);
		end
		hdssA(playerindex);
	end
	return true;
end

function Edef_SendExChase_16(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_17(playerindex, rank, x, y, timer, px, py)
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, 42);
	elseif math.mod(timer, 3) == 0 then
		local nowindex = timer / 3;
		local leftrightindi = math.mod(hdss.Get(HDSS_ENI, playerindex), 2) * 2 - 1;
		local aimangle = hdss.Get(HDSS_ENAIMANGLE, playerindex);
		local speed = (nowindex+3)*0.25;
		hdssBC(playerindex, 8, aimangle+leftrightindi*nowindex*600, 0, x, y, speed, CC_Bullet_Coin, math.mod(nowindex, 3));
	end
	return true;
end

function Edef_SendExChase_18(playerindex, rank, x, y, timer, px, py)
	local delaytimer = hdss.Get(HDSS_ENAIMANGLE, playerindex);
	if timer == 1 then
		hdssEA_FADEOUT(playerindex, delaytimer+36);
	elseif timer > delaytimer and timer <= delaytimer + 24 then
		local speed = RANDT(1.4, 2.0);
		hdssB(playerindex, x, y, RANDT(1, 36000), speed, CC_Bullet_Kunai, 1);
	end
	return true;
end

function Edef_SendExChase_19(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_20(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_21(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_22(playerindex, rank, x, y, timer, px, py)
	return true;
end

function Edef_SendExChase_23(playerindex, rank, x, y, timer, px, py)
	return true;
end