function hdssSD(index, value)
	return hdss.Call(
		HDSS_SD,
		{
			index, value
		}
	)
end

function hdssSDf(index, value)
	return hdss.Call(
		HDSS_SDf,
		{
			index, value
		}
	)
end

function hdssSETCHARA(index, id)
	return hdss.Call(
		HDSS_SETCHARA,
		{
			index, id
		}
	)
end

function hdssSETSCENE(scene)
	return hdss.Call(
		HDSS_SETSCENE,
		{
			scene
		}
	)
end

function hdssSTARTPREP(callinit)
	return hdss.Call(
		HDSS_STARTPREP,
		{
			callinit
		}
	)
end

function hdssBGSETUP()
	return hdss.Call(
		HDSS_BGSETUP,
		{
		}
	)
end

function hdssSELSET(index, select)
	return hdss.Call(
		HDSS_SELSET,
		{
			index, select
		}
	)
end

function hdssSELCONFIRM(index, keyminus, keyplus, keyok, keycancel, cenx, ceny, settrue)
	return hdss.Call(
		HDSS_SELCONFIRM,
		{
			index, keyminus, keyplus, keyok, keycancel, cenx, ceny, settrue
		}
	)
end

function hdssSELCLEAR(index1, index2, index3, index4)
	if index1 == nil then
		return;
	end
	hdss.Call(
		HDSS_SELCLEAR,
		{
			index1
		}
	)
	if index2 == nil then
		return;
	end
	hdss.Call(
		HDSS_SELCLEAR,
		{
			index2
		}
	)
	if index3 == nil then
		return;
	end
	hdss.Call(
		HDSS_SELCLEAR,
		{
			index3
		}
	)
	if index4 == nil then
		return;
	end
	hdss.Call(
		HDSS_SELCLEAR,
		{
			index4
		}
	)
end

function hdssSETSTATE(tostate, time)
	return hdss.Call(
		HDSS_SETSTATE,
		{
			tostate, time
		}
	)
end

function hdssCLEARALL()
	return hdss.Call(
		HDSS_CLEARALL,
		{
		}
	)
end

function hdssMUSICCHANGE(ID, bForce)
	return hdss.Call(
		HDSS_MUSICCHANGE,
		{
			ID, bForce
		}
	)
end

function hdssMUSICSLIDE(slidetime, tovol, pan, pitch)
	return hdss.Call(
		HDSS_MUSICSLIDE,
		{
			slidetime, tovol, pan, pitch
		}
	)
end

function hdssSETPINITLIFE(playerindex, life)
	return hdss.Call(
		HDSS_SETPINITLIFE,
		{
			playerindex, life
		}
	)
end

function hdssSETPBINFI(playerindex, reasonflag, infitimer)
	return hdss.Call(
		HDSS_SETPBINFI,
		{
			playerindex, reasonflag, infitimer
		}
	)
end

function hdssEA(playerindex, ac, fpara, ipara)
	if fpara == nil then
		fpara = {0, 0, 0, 0};
	end
	if ipara == nil then
		ipara = {0, 0, 0, 0};
	end
	for i=1, 4 do
		if fpara[i] == nil then
			fpara[i] = 0;
		end
		if ipara[i] == nil then
			ipara[i] = 0;
		end
	end
	return hdss.Call(
		HDSS_EA,
		{
			playerindex, ac, fpara[1], fpara[2], fpara[3], fpara[4], ipara[1], ipara[2], ipara[3], ipara[4], 
		}
	)
end

function hdssEB(eID, playerindex, x, y, angle, speed, type, life, take)
	if take == nil or take == 0 then
		return hdss.Call(
			HDSS_EB,
			{
				eID, playerindex, x, y, angle, speed, type, life
			}
		)
	else
		return hdss.Call(
			HDSS_EB,
			{
				eID, playerindex, x, y, angle, speed, type, life
			},
			{
				0xff
			},
			{
				take
			}
		)
	end
end