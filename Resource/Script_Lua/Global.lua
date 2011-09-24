LGlobal_MessageBoxCount	=	{}

_DEBUG_LGlobal_Jump	=	-1;
_DEBUG_MatchAndLog	=	0;

_DEBUG_ReplayCount = 0;

function _DEBUG_GetSaveReplayName()
	local filename = string.format("DES_TH_09X_XXXXXX_%04d_xxxx.rpy", _DEBUG_ReplayCount);
	_DEBUG_ReplayCount = _DEBUG_ReplayCount + 1;
	return filename;
end

function _DEBUG_NewRandomMatch()
	game.SetMatchMode(MatchMode_P2C);
	local randchara = {};
	local randcharaname = {};
	local siid;
	for i=0, 1 do
		randchara[i+1] = RANDT(0, 23);
		siid, randcharaname[i+1] = game.GetPlayerContentTable(randchara[i+1]);
		hdssSETCHARA(i, randchara[i+1], 0xff, 0xff);
		hdssSETPINITLIFE(i, 10);
	end
	logstr = "NM :	"..randchara[1].."	"..randcharaname[1].."	"..randchara[2].."	"..randcharaname[2];
	LOG(logstr);
	hdssSETSCENE(23);
	hdssSTARTPREP();
	CETitle_ExitState(STATE_START);
end

function LGlobal_CallMessageBoxOnce(content, title, indi)
	if indi == nil then
		indi = 1;
	end
	if LGlobal_MessageBoxCount[indi] == nil or hge.Input_GetDIKey(DIK_DELETE, DIKEY_DOWN) then
		LGlobal_MessageBoxCount[indi] = 0;
	end
	if LGlobal_MessageBoxCount[indi] > 0 then
		return 0;
	end
	LGlobal_MessageBoxCount[indi] = LGlobal_MessageBoxCount[indi] + 1;
	return LGlobal_CallMessageBox(content, title);
end

function LGlobal_CallMessageBox(content, title)
	content = tostring(content);
	title = tostring(title);
	return global.MessageBox(content, title);
end

MB	=	LGlobal_CallMessageBoxOnce;
MBA	=	LGlobal_CallMessageBox;
LOG	=	hge.System_Log;

RANDT	=	game.Random_Int;
RANDTF	=	game.Random_Float;

LTable_ePlayerDrainFunction = 
{
	ePlayerDrain_00,
	ePlayerDrain_01,
	ePlayerDrain_02,
	ePlayerDrain_03,
	ePlayerDrain_04,
	ePlayerDrain_05,
	ePlayerDrain_06,
	ePlayerDrain_07,
	ePlayerDrain_08,
	ePlayerDrain_09,
	ePlayerDrain_10,
	ePlayerDrain_11,
	ePlayerDrain_12,
	ePlayerDrain_13,
	ePlayerDrain_14,
	ePlayerDrain_15,
	ePlayerDrain_16,
	ePlayerDrain_17,
	ePlayerDrain_18,
	ePlayerDrain_19,
	ePlayerDrain_20,
	ePlayerDrain_21,
	ePlayerDrain_22,
	ePlayerDrain_23,
}

LTable_ePlayerShotFunction = 
{
	ePlayerShot_00,
	ePlayerShot_01,
	ePlayerShot_02,
	ePlayerShot_03,
	ePlayerShot_04,
	ePlayerShot_05,
	ePlayerShot_06,
	ePlayerShot_07,
	ePlayerShot_08,
	ePlayerShot_09,
	ePlayerShot_10,
	ePlayerShot_11,
	ePlayerShot_12,
	ePlayerShot_13,
	ePlayerShot_14,
	ePlayerShot_15,
	ePlayerShot_16,
	ePlayerShot_17,
	ePlayerShot_18,
	ePlayerShot_19,
	ePlayerShot_20,
	ePlayerShot_21,
	ePlayerShot_22,
	ePlayerShot_23,
}

LTable_ePlayerSendExFunction = 
{
	ePlayerSendEx_00,
	ePlayerSendEx_01,
	ePlayerSendEx_02,
	ePlayerSendEx_03,
	ePlayerSendEx_04,
	ePlayerSendEx_05,
	ePlayerSendEx_06,
	ePlayerSendEx_07,
	ePlayerSendEx_08,
	ePlayerSendEx_09,
	ePlayerSendEx_10,
	ePlayerSendEx_11,
	ePlayerSendEx_12,
	ePlayerSendEx_13,
	ePlayerSendEx_14,
	ePlayerSendEx_15,
	ePlayerSendEx_16,
	ePlayerSendEx_17,
	ePlayerSendEx_18,
	ePlayerSendEx_19,
	ePlayerSendEx_20,
	ePlayerSendEx_21,
	ePlayerSendEx_22,
	ePlayerSendEx_23,
}

LTable_eActiveGhostOverFunction = 
{
	eActiveGhostOver_00,
	eActiveGhostOver_01,
	eActiveGhostOver_02,
	eActiveGhostOver_03,
	eActiveGhostOver_04,
	eActiveGhostOver_05,
	eActiveGhostOver_06,
	eActiveGhostOver_07,
	eActiveGhostOver_08,
	eActiveGhostOver_09,
	eActiveGhostOver_10,
	eActiveGhostOver_11,
	eActiveGhostOver_12,
	eActiveGhostOver_13,
	eActiveGhostOver_14,
	eActiveGhostOver_15,
	eActiveGhostOver_16,
	eActiveGhostOver_17,
	eActiveGhostOver_18,
	eActiveGhostOver_19,
	eActiveGhostOver_20,
	eActiveGhostOver_21,
	eActiveGhostOver_22,
	eActiveGhostOver_23,
}

LTable_ePlayerSendExChaseFunction	=
{
	ePlayerSendExChase_00,
	ePlayerSendExChase_01,
	ePlayerSendExChase_02,
	ePlayerSendExChase_03,
	ePlayerSendExChase_04,
	ePlayerSendExChase_05,
	ePlayerSendExChase_06,
	ePlayerSendExChase_07,
	ePlayerSendExChase_08,
	ePlayerSendExChase_09,
	ePlayerSendExChase_10,
	ePlayerSendExChase_11,
	ePlayerSendExChase_12,
	ePlayerSendExChase_13,
	ePlayerSendExChase_14,
	ePlayerSendExChase_15,
	ePlayerSendExChase_16,
	ePlayerSendExChase_17,
	ePlayerSendExChase_18,
	ePlayerSendExChase_19,
	ePlayerSendExChase_20,
	ePlayerSendExChase_21,
	ePlayerSendExChase_22,
	ePlayerSendExChase_23,
}

LTable_ePlayerShootChargeFunction	=
{
	{	ePlayerShootCharge_00_1			,
		ePlayerShootCharge_00_2			,
		ePlayerShootCharge_00_3			},
	{	ePlayerShootCharge_01_1			,
		ePlayerShootCharge_01_2			,
		ePlayerShootCharge_01_3			},
	{	ePlayerShootCharge_02_1			,
		ePlayerShootCharge_02_2			,
		ePlayerShootCharge_02_3			},
	{	ePlayerShootCharge_03_1			,
		ePlayerShootCharge_03_2			,
		ePlayerShootCharge_03_3			},
	{	ePlayerShootCharge_04_1			,
		ePlayerShootCharge_04_2			,
		ePlayerShootCharge_04_3			},
	{	ePlayerShootCharge_05_1			,
		ePlayerShootCharge_05_2			,
		ePlayerShootCharge_05_3			},
	{	ePlayerShootCharge_06_1			,
		ePlayerShootCharge_06_2			,
		ePlayerShootCharge_06_3			},
	{	ePlayerShootCharge_07_1			,
		ePlayerShootCharge_07_2			,
		ePlayerShootCharge_07_3			},
	{	ePlayerShootCharge_08_1			,
		ePlayerShootCharge_08_2			,
		ePlayerShootCharge_08_3			},
	{	ePlayerShootCharge_09_1			,
		ePlayerShootCharge_09_2			,
		ePlayerShootCharge_09_3			},
	{	ePlayerShootCharge_10_1			,
		ePlayerShootCharge_10_2			,
		ePlayerShootCharge_10_3			},
	{	ePlayerShootCharge_11_1			,
		ePlayerShootCharge_11_2			,
		ePlayerShootCharge_11_3			},
	{	ePlayerShootCharge_12_1			,
		ePlayerShootCharge_12_2			,
		ePlayerShootCharge_12_3			},
	{	ePlayerShootCharge_13_1			,
		ePlayerShootCharge_13_2			,
		ePlayerShootCharge_13_3			},
	{	ePlayerShootCharge_14_1			,
		ePlayerShootCharge_14_2			,
		ePlayerShootCharge_14_3			},
	{	ePlayerShootCharge_15_1			,
		ePlayerShootCharge_15_2			,
		ePlayerShootCharge_15_3			},
	{	ePlayerShootCharge_16_1			,
		ePlayerShootCharge_16_2			,
		ePlayerShootCharge_16_3			},
	{	ePlayerShootCharge_17_1			,
		ePlayerShootCharge_17_2			,
		ePlayerShootCharge_17_3			},
	{	ePlayerShootCharge_18_1			,
		ePlayerShootCharge_18_2			,
		ePlayerShootCharge_18_3			},
	{	ePlayerShootCharge_19_1			,
		ePlayerShootCharge_19_2			,
		ePlayerShootCharge_19_3			},
	{	ePlayerShootCharge_20_1			,
		ePlayerShootCharge_20_2			,
		ePlayerShootCharge_20_3			},
	{	ePlayerShootCharge_21_1			,
		ePlayerShootCharge_21_2			,
		ePlayerShootCharge_21_3			},
	{	ePlayerShootCharge_22_1			,
		ePlayerShootCharge_22_2			,
		ePlayerShootCharge_22_3			},
	{	ePlayerShootCharge_23_1			,
		ePlayerShootCharge_23_2			,
		ePlayerShootCharge_23_3			},
}

LTable_ePlayerShootChargeOneFunction	=	
{
	ePlayerShootChargeOne_00,
	ePlayerShootChargeOne_01,
	ePlayerShootChargeOne_02,
	ePlayerShootChargeOne_03,
	ePlayerShootChargeOne_04,
	ePlayerShootChargeOne_05,
	ePlayerShootChargeOne_06,
	ePlayerShootChargeOne_07,
	ePlayerShootChargeOne_08,
	ePlayerShootChargeOne_09,
	ePlayerShootChargeOne_10,
	ePlayerShootChargeOne_11,
	ePlayerShootChargeOne_12,
	ePlayerShootChargeOne_13,
	ePlayerShootChargeOne_14,
	ePlayerShootChargeOne_15,
	ePlayerShootChargeOne_16,
	ePlayerShootChargeOne_17,
	ePlayerShootChargeOne_18,
	ePlayerShootChargeOne_19,
	ePlayerShootChargeOne_20,
	ePlayerShootChargeOne_21,
	ePlayerShootChargeOne_22,
	ePlayerShootChargeOne_23,
}