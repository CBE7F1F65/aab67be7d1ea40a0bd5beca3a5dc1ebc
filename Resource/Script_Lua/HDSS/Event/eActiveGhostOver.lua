function _eActiveGhostOver_Send3(playerindex)
	local x, y, angle, rank = helper_GetActiveGhostOverInfo(playerindex);
	local speed = 1 + rank * 0.1;
	for i=-1, 1 do
		hdssB(playerindex, x, y, angle + i * 900, speed, 2, 2);
	end
end

function _eActiveGhostOver_Send1(playerindex)
	local x, y, angle, rank = helper_GetActiveGhostOverInfo(playerindex);
	local speed = 1 + rank * 0.1;
	hdssB(playerindex, x, y, angle, speed, 2, 2);
end

function eActiveGhostOver_00(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_01(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_02(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_03(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_04(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_05(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_06(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_07(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_08(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_09(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_10(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_11(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_12(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_13(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_14(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_15(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_16(playerindex)
	_eActiveGhostOver_Send1(playerindex);
	return true;
end

function eActiveGhostOver_17(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_18(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_19(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_20(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_21(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_22(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end

function eActiveGhostOver_23(playerindex)
	_eActiveGhostOver_Send3(playerindex);
	return true;
end
