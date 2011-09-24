function ePlayerShot_00(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)
	return true;
end

function ePlayerShot_01(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)
	return true;
end

function ePlayerShot_02(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_03(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_04(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_05(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_06(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_07(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_08(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_09(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_10(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_11(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_12(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)
	local shottime = hdss.Get(HDSS_D, LConst_Desc_TeiShotTime+playerindex);
	if shottimer == 1 and shottime == 0 and nLife == 1 and nchargemax > 1 then
		hdssSETKEY(playerindex, KSI_QUICK);
		hdssSD(LConst_Desc_TeiShotTime+playerindex, shottime+1);
	end
	return true;
end

function ePlayerShot_13(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_14(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_15(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_16(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_17(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_18(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_19(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_20(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_21(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_22(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end

function ePlayerShot_23(playerindex, playerID, nLife, shottimer, shotdelay, nchargemax)

	return true;
end
