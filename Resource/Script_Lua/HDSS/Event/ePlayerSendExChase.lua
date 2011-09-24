function ePlayerSendExChase_00(playerindex, x, y, playerID, appendfloat)
	
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local angle;
	angle = RANDT(-5500, -2500);
	if RANDT(0, 1) == 1 then
		angle = -18000 - angle;
	end
	local speed = 1.4;
	local type = CC_BulletEx_Reimu;
	local startacctime = 24;
	local stopacctime = cardlevel * 6 + 32;
	local acc = 6;
	local afterstopadd = (stopacctime - startacctime) * acc
	hdssA(playerindex, 
		{
			TIMERLESS, stopacctime, YSETACCADD, startacctime, acc,
			TIMERGREAT, stopacctime, YSETADD, afterstopadd,
			EVERY, BOUNCELR, 0 ,16,
		}
	);
	hdssB(playerindex, x, y, angle, speed, type, 0);
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_01(playerindex, x, y, playerID, appendfloat, angleoffset)
	
	if angleoffset == nil then
		angleoffset = 0;
	end
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local speed = 18;
	hdss.Call(
		HDSS_BEB,
		{
			playerindex, x, y, -9000+angleoffset, speed, CC_Bullet_ShuttleBeam, 5, 720, 0, BEAMFLAG_DELAY
		}
	)
	hdssEFFSETUP(playerindex, LConst_effid_sendex_01, x, y, 64, angleoffset, 0.01);
	return true;
end

function ePlayerSendExChase_02(playerindex, x, y, playerID, appendfloat)
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local angle = hdssAMAP(playerindex, x, y);
	hdssEB(CC_SendExChaseEnemyEID_02, 1-playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssENSAIM(1-playerindex, rank, 0, 0, angle);
	return true;
end

function ePlayerSendExChase_03(playerindex, x, y, playerID, appendfloat)
	hdssA(playerindex,
		{
			TIMEREQUAL, 300, FADEOUT
		}
	)
	hdssB(playerindex, x, y, 9000, 0, CC_BulletEx_Youmu, 0);
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_04(playerindex, x, y, playerID, appendfloat)
	local angle = hdssAMAP(playerindex, x, y);
	local cosval = hdss.Get(HDSS_COSA, angle);
	local sinval = hdss.Get(HDSS_SINA, angle);
	local frontoffset = 8;
	local bx = x;
	local by = y;
	hdssA(playerindex,
		{
			TIMERLESS, 90, SPEEDSETADD, 12,
			BOUNCEEQUAL, 0, BOUNCELR, 16, 1
		}
	)
	for i=0, 4 do
		hdssB(playerindex, bx, by, angle, 0, CC_BulletEx_Aya, 0);
		bx = bx + frontoffset * cosval;
		by = by + frontoffset * sinval;
	end
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_05(playerindex, x, y, playerID, appendfloat)
	local angle = RANDT(1, 36000);
	for i=0, 1 do
		hdssA(playerindex,
			{
				TIMERLESS, 90, ANGLESETADD, (i*2-1)*75,
				TIMERLESS, 90, SPEEDSETADD, 4
			}
		)
		hdss.Call(HDSS_BC,
			{
				playerindex, 8, angle, 0, x, y, 1.6, CC_Bullet_Butterfly, 2+i, i*16+8
			}
		)
	end
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_06(playerindex, x, y, playerID, appendfloat)
	hdssEFFSETUP(playerindex, LConst_effid_sendex_06, x, y, 300);
	hdss.Call(HDSS_EZONEBUILD,
		{
			EZONETYPE_PLAYERSPEED+EZONECHECK_CIRCLE, playerindex, x, y,
			300, 72, 0, 0.4
		}
	)
	return true;
end

function ePlayerSendExChase_07(playerindex, x, y, playerID, appendfloat)
	hdssA(playerindex,
		{
			TIMERLESS, 60, SPEEDSETADD, 5
		}
	)
	hdssB(playerindex, x, y, 9000, 1.0, CC_BulletEx_Cirno, RANDT(0, 1));
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_08(playerindex, x, y, playerID, appendfloat)
	local angle = RANDT(1, 36000);
	hdssA(playerindex,
		{
			TIMERLESS, 60, SPEEDSETADD, 4
		}
	)
	for i=0, 1 do
		local speed = 0.8 + i * 0.1;
		local type = CC_Bullet_LegatoQuaver;
		if i == 1 then
			type = CC_Bullet_Quaver;
		end
		hdssBC(playerindex, 8, angle+i*2250, 0, x, y, speed, type, 0);
	end
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_09(playerindex, x, y, playerID, appendfloat)
	local angle = RANDT(-3000, 3000);
	local cenx = helper_GetCenterX(playerindex);
	if x > cenx then
		angle = angle + 18000;
	end
	hdssEB(CC_SendExChaseEnemyEID_09, playerindex, x, y, angle, 1.6, LConst_EnemyExType_Mystia, 0);
	return true;
end

function ePlayerSendExChase_10(playerindex, x, y, playerID, appendfloat)
	hdssEB(CC_SendExChaseEnemyEID_10, playerindex, x, y, 9000, 0, LConst_EnemyExType_Marlin, 0);
	return true;
end

function ePlayerSendExChase_11(playerindex, x, y, playerID, appendfloat)
	hdssEB(CC_SendExChaseEnemyEID_11, playerindex, x, y, 9000, 0, LConst_EnemyExType_Lunasa, 0);
	return true;
end

function ePlayerSendExChase_12(playerindex, x, y, playerID, appendfloat)
	local leftrightindi = -1;
	if x < helper_GetCenterX(playerindex) then
		leftrightindi = 1;
	end
	local addangle = leftrightindi*80;
	hdssA(playerindex,
		{
			EVERY, ANGLESETADD, addangle,
			EVERY, BOUNCELR, 0, 16
		}
	)
	hdssB(playerindex, x, y, 9000, 3.0, CC_BulletEx_Tei, 0);
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_13(playerindex, x, y, playerID, appendfloat)
	local speed = RANDTF(1.0, 4.0);
	local type = CC_BulletEx_Yuka_Middle;
	if RANDT(0, 1) == 1 then
		type = CC_BulletEx_Yuka_Small;
	end
	hdssB(playerindex, x, y, 9000, speed, type, 0);
	return true;
end

function ePlayerSendExChase_14(playerindex, x, y, playerID, appendfloat, angle, speed)
	if angle == nil then
		angle = RANDT(8990, 9010);
	end
	if speed == nil then
		speed = RANDTF(2.0, 2.4);
	end
	hdssEB(CC_SendExChaseEnemyEID_14, playerindex, x, y, angle, speed, LConst_EnemyExType_Reisen, 0);
	return true;
end

function ePlayerSendExChase_15(playerindex, x, y, playerID, appendfloat)
	hdssEB(CC_SendExChaseEnemyEID_15, playerindex, x, y, 9000, 0, LConst_EnemyExType_AliceRed, 240);
	return true;
end

function ePlayerSendExChase_16(playerindex, x, y, playerID, appendfloat)
	hdssEFFSETUP(playerindex, LConst_effid_sendex_16, x, y, 300);
	hdss.Call(HDSS_EZONEBUILD,
		{
			EZONETYPE_BULLETSTUPA+EZONECHECK_CIRCLE, playerindex, x, y,
			300, 64, 0, 1.2, CC_Bullet_Stupa
		}
	)
	return true;
end

function ePlayerSendExChase_17(playerindex, x, y, playerID, appendfloat)
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	hdssEB(CC_SendExChaseEnemyEID_17, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 0);
	hdssENSAIM(playerindex, rank, 0, 0, RANDT(1, 36000));
	return true;
end

function ePlayerSendExChase_18(playerindex, x, y, playerID, appendfloat, delaytime)
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	hdssEB(CC_SendExChaseEnemyEID_18, playerindex, x, y, 9000, 0, LConst_EnemyExType_Remilia, 0);
	if delaytime == nil then
		delaytime = RANDT(1, 60);
	end
	hdssENSAIM(playerindex, rank, 0, 0, delaytime);
	return true;
end

function ePlayerSendExChase_19(playerindex, x, y, playerID, appendfloat)
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local angle;
	local speed = 1.4;
	local type = CC_BulletEx_ReimuII;
	local startacctime = 24;
	local stopacctime = cardlevel * 6 + 32;
	local acc = 6;
	local afterstopadd = (stopacctime - startacctime) * acc
	hdssA(playerindex, 
		{
			TIMERLESS, stopacctime, YSETACCADD, startacctime, acc,
			TIMERGREAT, stopacctime, YSETADD, afterstopadd,
			EVERY, BOUNCELR, 0 ,16,
		}
	);
	angle = RANDT(-5500, -2500);
	for i=0, 1 do
		if i == 1 then
			angle = -18000 - angle;
		end
		hdssB(playerindex, x, y, angle, speed, type, 0);
	end
	hdssA(playerindex);
end

function ePlayerSendExChase_20(playerindex, x, y, playerID, appendfloat, angleoffset)
	if angleoffset == nil then
		angleoffset = 0;
	end
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local speed = 18;
	for i=0, 2 do
		hdss.Call(
			HDSS_BEB,
			{
				playerindex, x+(i-1)*8, y, -9000+angleoffset, speed, CC_Bullet_ShuttleBeam, 3, 360, 0, BEAMFLAG_DELAY
			}
		)
	end
	hdssEFFSETUP(playerindex, LConst_effid_sendex_01, x, y, 64, angleoffset, 0.01);
	return true;
end

function ePlayerSendExChase_21(playerindex, x, y, playerID, appendfloat)
	local ox = x+(1-playerindex*2)*TotalW/2;
	hdssEFFSETUP(playerindex, LConst_effid_sendex_21_out, x, y, 300);
	hdssEFFSETUP(1-playerindex, LConst_effid_sendex_21_in, ox, y, 300);
	hdss.Call(HDSS_EZONEBUILD,
		{
			EZONETYPE_BULLETWARP+EZONECHECK_CIRCLE, 1-playerindex, ox, y,
			300, 64, 0, 1.0, CC_Bullet_SmallBall
		}
	)
	return true;
end

function ePlayerSendExChase_22(playerindex, x, y, playerID, appendfloat)
	local rank, cardlevel, bosslevel = hdss.Get(HDSS_RANK, 1-playerindex);
	local speed = rank * 0.1 + 1.2;
	local angle = hdssAMAP(playerindex, x, y);
	hdssB(playerindex, x, y, angle, speed, CC_Bullet_BigStar, 5, 9);
	hdssA(playerindex,
		{
			TIMEREQUAL, 9, ANGLESET, angle
		}
	)
	hdssBC(playerindex, 5, 9000, 6, x, y, speed, CC_Bullet_Star, 10);
	hdssA(playerindex);
	return true;
end

function ePlayerSendExChase_23(playerindex, x, y, playerID, appendfloat, angle)
	hdssA(playerindex,
		{
			TIMEREQUAL, 65, COLORSET, 1,
			TIMEREQUAL, 74, COLORSET, 0,
			TIMEREQUAL, 74, FADEOUT
		}
	)
	if angle == nil then
		angle = RANDT(1, 36000);
	end
	hdssB(playerindex, x, y, angle, 0, CC_BulletEx_Hatate, 0, 64);
	hdssBUDECANCEL(playerindex);
	hdssA(playerindex);
end