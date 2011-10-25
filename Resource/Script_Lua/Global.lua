LGlobal_MessageBoxCount	=	{}

_DEBUG_LGlobal_Jump	=	-1;
_DEBUG_MatchAndLog	=	0;

function _DEBUG_NewRandomMatch()
	local randchara = {};
	local randcharaname = {};
	local siid;
	for i=0, 1 do
		randchara[i+1] = 0;
		siid, randcharaname[i+1] = game.GetPlayerContentTable(randchara[i+1]);
		hdssSETCHARA(i, randchara[i+1]);
		hdssSETPINITLIFE(i, 10);
	end
	logstr = "NM :	"..randchara[1].."	"..randcharaname[1].."	"..randchara[2].."	"..randcharaname[2];
	LOG(logstr);
	hdssSETSCENE(0);
	hdssSTARTPREP();
	_DEBUG_LGlobal_Jump = -1;
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


function Math_Sign(x)
	x = math.floor(x);
	return math.mod(x, 2)*2-1;
end

function Math_Inter(a, b, x)
	return (b-a)*x+a;
end

function Math_Roll(x, t)
	local modval = math.mod(x, 2*t);
	return ((modval-math.mod(modval, t)) - Math_Sign(modval/t)) * math.mod(x, t);
end
