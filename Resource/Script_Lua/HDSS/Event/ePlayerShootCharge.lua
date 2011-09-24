function _ePlayerShootCharge_CheckBoss(playerindex)
	local eni, bosseni = hdss.Get(HDSS_ENI, playerindex);
	if bosseni == 0xff then
		hdssEA_FADEOUT(playerindex, -1);
		return true;
	end
	return false;
end

function _ePlayerShootCharge_3_SetBGS(playerindex, oplayerID)
	local bgsi = hdss.Get(HDSS_BGSI, playerindex, LConst_bgset_spellid);
	if bgsi ~= oplayerID+LConst_SceneSpellOffset then
		hdssBGSETUP(playerindex, LConst_bgset_spellid, oplayerID+LConst_SceneSpellOffset, true);
	end
end

function ePlayerShootCharge_00_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_00_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_00_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_00_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_00_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_00_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end


function ePlayerShootCharge_01_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	if px > x then
		x = x - CenterW/2;
	else
		x = x + CenterW/2;
	end
	local y = 0;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y+16, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_01_1, playerindex, x, y, 9000, 6.0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_01_2(playerindex, level, oplayerID, px, py)
	local leftx = helper_GetCenterX(playerindex) - CenterW/2;
	local y = 0;
	for i=0, 1 do
		local x = leftx + i * CenterW;
		hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y+16, LConst_ShootCharge_EnemyDelay);
		hdssEB(CC_ShootChargeEnemyEID_01_2, playerindex, x, y, 9000, 6.0, LConst_EnemyTypeNull, 10);
		hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
		hdssENSAIM(playerindex, level);
	end
	return true;
end

function ePlayerShootCharge_01_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_01_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_02_1(playerindex, level, oplayerID, px, py)
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, px, py, LConst_ShootCharge_EnemyDelay);
	local opx = hdss.Get(HDSS_PX, 1-playerindex);
	local opy = hdss.Get(HDSS_PY, 1-playerindex);
	hdssEB(CC_ShootChargeEnemyEID_02_1, 1-playerindex, opx, opy, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(1-playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(1-playerindex, level);
	return true;
end

function ePlayerShootCharge_02_2(playerindex, level, oplayerID, px, py)
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, px, py, LConst_ShootCharge_EnemyDelay);
	local opx = hdss.Get(HDSS_PX, 1-playerindex);
	local opy = hdss.Get(HDSS_PY, 1-playerindex);
	hdssEB(CC_ShootChargeEnemyEID_02_2, 1-playerindex, opx, opy, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(1-playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(1-playerindex, level);
	return true;
end

function ePlayerShootCharge_02_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_02_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_03_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	if x > px then
		x = x + CenterW / 2;
	else
		x = x - CenterW / 2;
	end
	local y = 0;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y+16, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_03_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_03_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	if x > px then
		x = x + CenterW / 2;
	else
		x = x - CenterW / 2;
	end
	local y = 0;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y+16, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_03_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_03_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_03_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_04_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 0;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y+16, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_04_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_04_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local leftrightindi = RANDT(0, 1) * 2 - 1;
	x = x + leftrightindi * CenterW / 2;
	local y = 0;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y+16, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_04_2, playerindex, x, y, (leftrightindi+1) * 9000, CenterW/(5*(level/1.4+6)), LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_04_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_04_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_05_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	local aimangle = hdssAMAP(playerindex, x, y);
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_05_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_05_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	local aimangle = hdssAMAP(playerindex, x, y);
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_05_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_05_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_05_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_06_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = CenterY;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_06_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_06_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = CenterY;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_06_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_06_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_06_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_07_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_07_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_07_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_07_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_07_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_07_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_08_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 16;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_08_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = (RANDT(0, 1)*2-1)*3000;
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_08_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 16;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_08_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = (RANDT(0, 1)*2-1)*3000;
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_08_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_08_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_09_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = CenterY;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x-CenterW/2, y, LConst_ShootCharge_EnemyDelay);
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x+CenterW/2, y, LConst_ShootCharge_EnemyDelay);
	local leftrightindi = RANDT(0, 1)*2-1;
	x = x + leftrightindi * CenterW/2;
	local aimangle = RANDT(1, 36000);
	hdssEB(CC_ShootChargeEnemyEID_09_1, playerindex, x, y, leftrightindi*9000+9000, 1.6, LConst_EnemyExType_Mystia, 0);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_09_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = CenterY;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x-CenterW/2, y, LConst_ShootCharge_EnemyDelay);
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x+CenterW/2, y, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssEB(CC_ShootChargeEnemyEID_09_2, playerindex, x-CenterW/2, y, 0, 1.6, LConst_EnemyExType_Mystia, 0);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	hdssEB(CC_ShootChargeEnemyEID_09_2, playerindex, x+CenterW/2, y, 18000, 1.6, LConst_EnemyExType_Mystia, 0);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_09_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_09_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_10_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 48;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_10_1, playerindex, x, y, 9000, 0, LConst_EnemyExType_Marlin, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = (RANDT(0, 1)*2-1)*250;
	hdssENSAIM(playerindex, level, px, py, aimangle);
	return true;
end

function ePlayerShootCharge_10_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 48;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_10_2, playerindex, x, y, 9000, 0, LConst_EnemyExType_Marlin, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = (RANDT(0, 1)*2-1)*250;
	hdssENSAIM(playerindex, level, px, py, aimangle);
	return true;
end

function ePlayerShootCharge_10_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_10_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_11_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = TotalCenterY+CenterH/2;
	local leftrightindi = RANDT(0, 1) * 2 - 1;
	x = x + leftrightindi * CenterW/2;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y-16, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_11_1, playerindex, x, y, leftrightindi*9000+9000, CenterW/((10+level/2)*6), LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_11_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = TotalCenterY+CenterH/2;
	local leftrightindi = RANDT(0, 1) * 2 - 1;
	x = x + leftrightindi * CenterW/2;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y-16, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_11_2, playerindex, x, y, leftrightindi*9000+9000, CenterW/((10+level/2)*6), LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_11_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_11_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_12_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = CenterY;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_12_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_12_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = CenterY;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_12_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_12_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_12_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_13_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_13_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_13_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_13_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_13_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_13_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_14_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_14_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_14_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_14_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_14_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_14_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_15_1(playerindex, level, oplayerID, px, py)
	local basex = helper_GetCenterX(playerindex) * 2 - px;
	local basey = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, basex, basey, LConst_ShootCharge_EnemyDelay);
	local baseangle = hdssAMAP(playerindex, basex, basey);
	for i=0, 3 do
		local angle = baseangle+(i-1.5)*3000;
		local cosval = hdss.Get(HDSS_COSA, angle+18000);
		local sinval = hdss.Get(HDSS_SINA, angle+18000);
		local x = 80 * cosval + basex;
		local y = 80 * sinval + basey;
		local bangle = hdssAMAP(playerindex, x, y);
		hdssEB(CC_ShootChargeEnemyEID_15_1, playerindex, x, y, bangle, 3.5, LConst_EnemyExType_AliceYellow, 240);
		hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
		hdssENSAIM(playerindex, level);
	end
	return true;
end

function ePlayerShootCharge_15_2(playerindex, level, oplayerID, px, py)
	local basex = helper_GetCenterX(playerindex) * 2 - px;
	local basey = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, basex, basey, LConst_ShootCharge_EnemyDelay);
	local baseangle = hdssAMAP(playerindex, basex, basey);
	for i=0, 3 do
		local angle = baseangle+(i-1.5)*3000;
		local cosval = hdss.Get(HDSS_COSA, angle+18000);
		local sinval = hdss.Get(HDSS_SINA, angle+18000);
		local x = 80 * cosval + basex;
		local y = 80 * sinval + basey;
		local bangle = hdssAMAP(playerindex, x, y);
		hdssEB(CC_ShootChargeEnemyEID_15_2, playerindex, x, y, bangle, 3.5, LConst_EnemyExType_AliceYellow, 240);
		hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
		hdssENSAIM(playerindex, level);
	end
	return true;
end

function ePlayerShootCharge_15_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_15_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_16_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	local angle = RANDT(1, 36000);
	hdssEB(CC_ShootChargeEnemyEID_16_1, playerindex, x, y, angle, 0.5, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_16_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	local angle = RANDT(1, 36000);
	hdssEB(CC_ShootChargeEnemyEID_16_2, playerindex, x, y, angle, 0.5, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_16_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_16_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_17_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) + RANDT(-96, 96);
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_17_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_17_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) + RANDT(-96, 96);
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_17_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_17_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_17_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_18_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) + RANDT(-96, 96);
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_18_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_18_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) + RANDT(-96, 96);
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_18_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = RANDT(1, 36000);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_18_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_18_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_19_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_19_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);

	return true;
end

function ePlayerShootCharge_19_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_19_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);

	return true;
end

function ePlayerShootCharge_19_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_19_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);

	return true;
end

function ePlayerShootCharge_20_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	if px > x then
		x = x - CenterW/2;
	else
		x = x + CenterW/2;
	end
	local y = 0;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y+16, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_20_1, playerindex, x, y, 9000, 6.0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_20_2(playerindex, level, oplayerID, px, py)
	local leftx = helper_GetCenterX(playerindex) - CenterW/2;
	local y = 0;
	for i=0, 1 do
		local x = leftx + i * CenterW;
		hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y+16, LConst_ShootCharge_EnemyDelay);
		hdssEB(CC_ShootChargeEnemyEID_20_2, playerindex, x, y, 9000, 6.0, LConst_EnemyTypeNull, 10);
		hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
		hdssENSAIM(playerindex, level);
	end
	return true;
end

function ePlayerShootCharge_20_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_20_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_21_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = CenterY-40;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_21_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_21_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex);
	local y = CenterY-40;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_21_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_21_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_21_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_22_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_22_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_22_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 144;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_22_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_22_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	hdssEB(CC_ShootChargeEnemyEID_22_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

function ePlayerShootCharge_23_1(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 96;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_23_1, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = hdssAMAP(playerindex, x, y);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_23_2(playerindex, level, oplayerID, px, py)
	local x = helper_GetCenterX(playerindex) * 2 - px;
	local y = 96;
	hdssEFFSETUP(playerindex, LConst_effid_shootcharge, x, y, LConst_ShootCharge_EnemyDelay);
	hdssEB(CC_ShootChargeEnemyEID_23_2, playerindex, x, y, 9000, 0, LConst_EnemyTypeNull, 10);
	hdssEA_DELAY(playerindex, LConst_ShootCharge_EnemyDelay);
	local aimangle = hdssAMAP(playerindex, x, y);
	hdssENSAIM(playerindex, level, 0, 0, aimangle);
	return true;
end

function ePlayerShootCharge_23_3(playerindex, level, oplayerID, px, py)
	local x = TotalCenterX;
	local y = 0;
	--
	local toindex = hdss.Get(HDSS_CHARA, playerindex);
	if toindex == CC_PlayerID_Hatate then
		toindex = CC_PlayerID_Aya;
	end
	--
	hdssSD(LConst_Desc_HatateIndex+playerindex, toindex);
	hdssEB(CC_ShootChargeEnemyEID_23_3, playerindex, x, y, 9000, 0, oplayerID, 1400, helper_GetRandomItem());
	hdssENSAIM(playerindex, level);
	return true;
end

--

function ePlayerShootChargeOne_00(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_01(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_02(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_03(playerindex, oplayerID, opx, opy, timer, maxtime)
	if timer == 1 then
		hdssSE(CC_SE_Slash, opx);
		local effindex = hdssEFFSETUP(playerindex, LConst_effid_youmuslash, opx, opy-28, 32);
		hdssSD(LConst_Desc_YoumuSlashEffIndex+playerindex, effindex);
		hdss.Call(HDSS_EZONEBUILD,
			{
				EZONETYPE_PLAYERSPEED+EZONECHECK_CIRCLE, playerindex, opx, opy,
				18, EVENTZONE_OVERZONE, EVENTZONE_OVERZONE, 0.5
			}
		)
	end
	local offset = timer/2;
	local effindex = hdss.Get(HDSS_D, LConst_Desc_YoumuSlashEffIndex+playerindex);
	local aimx = opx+8-offset;
	local aimy = opy-28-offset;
	hdssEFFMOVETO(playerindex, effindex, aimx, aimy, 0, true);
	hdss.Call(HDSS_EZONEBUILD,
		{
			EZONETYPE_BULLETFADEOUT+EZONETYPE_ENEMYDAMAGE+EZONECHECK_SQUARE, playerindex, aimx, aimy,
			2, 38+offset, 15.5+offset, 15
		}
	)
	return true;
end

function ePlayerShootChargeOne_04(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_05(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_06(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_07(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_08(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_09(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_10(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_11(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_12(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_13(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_14(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_15(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_16(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_17(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_18(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_19(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_20(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_21(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_22(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end

function ePlayerShootChargeOne_23(playerindex, oplayerID, opx, opy, timer, maxtime)
	return true;
end