function _ePlayerSendEx_Restirict(aimx, aimy, cenx, edge)
	if edge == nil then
		edge = 0;
	end
	if aimx < cenx - TotalW/4 + edge then
		aimx = cenx - TotalW/4 + edge;
	elseif aimx > cenx + TotalW/4 - edge then
		aimx = cenx + TotalW/4 - edge;
	end
	if aimy < edge then
		aimy = edge;
	elseif aimy > TotalH-edge then
		aimy = TotalH-edge;
	end
	return aimx, aimy;
end

function ePlayerSendEx_00(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(16, 144);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_01(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = CenterH + 16;
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_02(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local chasetimer = RANDT(1, 16);
	game.PlayerSendEx(oplayerindex, esindex, x, y, chasetimer);
	return true;
end

function ePlayerSendEx_03(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = opx + RANDTF(-128, 128);
	local aimy = opy + RANDTF(-128, 128);
	local chasetimer = RANDT(120, 180);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx, 32);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_04(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(16, 144);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_05(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(48, 192);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_06(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-120, 120);
	local aimy = RANDTF(208, 464);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_07(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = opx + RANDTF(-32, 32);
	local aimy = 32;
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_08(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(144, 344);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_09(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + (RANDT(0, 1)*2-1)*CenterW/2;
	local aimy = RANDTF(144, 336);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_10(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(48, 176);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_11(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(216, 344);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_12(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-80, 80);
	local aimy = RANDTF(16, 144);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_13(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(16, 144);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_14(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(16, 144);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_15(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(144, 344);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_16(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-120, 120);
	local aimy = RANDTF(144, 272);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_17(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(48, 192);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_18(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(144, 272);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_19(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	return ePlayerSendEx_00(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y);
end

function ePlayerSendEx_20(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	return ePlayerSendEx_01(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y);
end

function ePlayerSendEx_21(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(144, 272);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_22(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = opx + (RANDT(0, 1)*2-1) * RANDTF(80, 120);
	local aimy = RANDTF(16, 144);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end

function ePlayerSendEx_23(esindex, oplayerindex, playerID, opx, opy, px, py, oplayerID, x, y)
	local cenx = helper_GetCenterX(oplayerindex);
	local aimx = cenx + RANDTF(-136, 136);
	local aimy = RANDTF(144, 272);
	local chasetimer = RANDT(45, 60);
	aimx, aimy = _ePlayerSendEx_Restirict(aimx, aimy, cenx);
	game.PlayerSendEx(oplayerindex, esindex, aimx, aimy, chasetimer);
	return true;
end