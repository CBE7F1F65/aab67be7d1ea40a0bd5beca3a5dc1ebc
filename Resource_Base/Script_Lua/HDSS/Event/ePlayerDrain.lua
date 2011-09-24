function ePlayerDrain_00(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	if draintimer < 20 then
		hscale = draintimer * 0.125 + 0.5;
	else
		hscale = 3;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	local r = hscale * 32;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	
	return true;
end

function ePlayerDrain_01(playerindex, x, y, draintimer, type)

	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	if draintimer > 100 then
		draintimer = 100;
	elseif draintimer < 30 then
		draintimer = 30;
	end
	local hscale = (draintimer / 100) * 1.75;
	local vscale = 1.75;
	local ceny = y-TotalH/2+16;
	game.SetDrainSpriteInfo(playerindex, x, ceny, 0, hscale, vscale);
	
	local rl = TotalH/2;
	local rs = 146 / 7 * vscale;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_ELLIPSE+ENAZOP_AND, x, ceny, rs, rl);
	
	return true;
end


function ePlayerDrain_02(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale = 1.25;
	local vscale = 1.25;
	if draintimer < 30 then
		hscale = (draintimer / 30) * 1.25;
	else
		draintimer = 30;
	end
	
	
--	local lastx, lasty, lastmx, lastmy, moveangle, moved = game.GetPlayerMoveInfo(playerindex, 1);

	local drainangle = hdss.Get(HDSS_D, LConst_Desc_DrainAngle+playerindex);
	local moveangle = 9000;
	local bkeyup = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_UP);
	local bkeydown = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_DOWN);
	local bkeyleft = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_LEFT);
	local bkeyright = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_RIGHT);
	if bkeyup and not bkeydown then
		if bkeyleft and not bkeyright then
			moveangle = -13500;
		elseif not bkeyleft and bkeyright then
			moveangle = -4500;
		else
			moveangle = -9000;
		end
	elseif not bkeyup and bkeydown then
		if bkeyleft and not bkeyright then
			moveangle = 13500;
		elseif not bkeyleft and bkeyright then
			moveangle = 4500;
		else
			moveangle = 9000;
		end
	else
		if bkeyleft and not bkeyright then
			moveangle = 18000;
		elseif not bkeyleft and bkeyright then
			moveangle = 0;
		else
			moveangle = drainangle-18000;
		end
	end
	
	moveangle = moveangle + 18000;
	moveangle = hdss.Get(HDSS_REGANGLE, moveangle);
	
	local baseangle = drainangle;
	if moveangle ~= drainangle then
		
		local plusval = 1500;
		drainangle = hdss.Get(HDSS_REGANGLE, drainangle);
		local bplus = true;
		if moveangle > drainangle then
			if drainangle + 18000 < moveangle then
				bplus = false;
			end
		else
			if moveangle + 18000 > drainangle then
				bplus = false;
			end
		end
		
		if bplus then
			if moveangle < drainangle then
				moveangle = moveangle + 36000;
			end
			baseangle = drainangle + plusval;
			if baseangle > moveangle then
				baseangle = moveangle;
			end
		else
			if moveangle > drainangle then
				moveangle = moveangle - 36000;
			end	
			baseangle = drainangle - plusval;
			if baseangle < moveangle then
				baseangle = moveangle;
			end
		end
		baseangle = hdss.Get(HDSS_REGANGLE, baseangle);
	end
	hdssSD(LConst_Desc_DrainAngle+playerindex, baseangle);
	
	local roffset = 15;
	local cenx = x + roffset * hdss.Get(HDSS_COSA, baseangle+18000);
	local ceny = y + roffset * hdss.Get(HDSS_SINA, baseangle+18000);
	game.SetDrainSpriteInfo(playerindex, cenx, ceny, baseangle+9000, hscale, vscale);
	
	local r = 160;
	local xadjc = 80;
	local xadjcc = 80;
	local yadjc = 80 * draintimer / 30;
	local yadjcc = -yadjc;
	
	local rl = 80;
	local rs = yadjc;
	
	local cosbaseangle = hdss.Get(HDSS_COSA, baseangle);
	local sinbaseangle = hdss.Get(HDSS_SINA, baseangle);
		
	local newxadjc = cosbaseangle * xadjc - sinbaseangle * yadjc;
	local newyadjc = sinbaseangle * xadjc + cosbaseangle * yadjc;
	local newxadjcc = cosbaseangle * xadjcc - sinbaseangle * yadjcc;
	local newyadjcc = sinbaseangle * xadjcc + cosbaseangle * yadjcc;
			
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, r);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx+newxadjcc, ceny+newyadjcc, rl, rs, baseangle - 9000);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx+newxadjc, ceny+newyadjc, rs, rl, baseangle + 18000);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, r);
	
	return true;
end


function ePlayerDrain_03(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	if draintimer < 184 then
		hscale = draintimer / 184 + 0.125;
	else
		hscale = 1.125;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	local r = hscale * 128;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	return true;
end

function ePlayerDrain_04(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale = 1;
	local vscale = 1;
	if draintimer < 50 then
		hscale = (draintimer / 50);
	else
		draintimer = 50;
	end
		
	local cenx = x;
	local ceny = y + 15;
	game.SetDrainSpriteInfo(playerindex, cenx, ceny, 0, hscale, vscale);
	
	local r = 128;
	local xadjc = 64;
	local xadjcc = 64;
	local yadjc = 64 * draintimer / 50;
	local yadjcc = -yadjc;
	
	local rl = 80;
	local rs = yadjc;
			
	local newxadjc = yadjc;
	local newyadjc = -xadjc;
	local newxadjcc = yadjcc;
	local newyadjcc = -xadjcc;
			
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, r);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx+newxadjcc, ceny+newyadjcc, rl, rs, -18000);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx+newxadjc, ceny+newyadjc, rs, rl, 9000);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, r);
	
	return true;
end

function ePlayerDrain_05(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel/2, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local cenx = x;
	local ceny = y-32;
	game.SetDrainSpriteInfo(playerindex, cenx, ceny);

	local rs = 48;
	local rl = 80;

	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, 128);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx-64, ceny, rs, rl, -15193);
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, cenx+64, ceny, rl, rs, 6193);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, ceny, 128);
	
	return true;
end

function ePlayerDrain_06(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale = 1;
	
	local drainangle = hdss.Get(HDSS_D, LConst_Desc_DrainAngle+playerindex)+9000;
	local moveangle = 0;
	if draintimer == 1 then
		drainangle = 0;
	end
	local bkeyleft = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_LEFT);
	local bkeyright = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_RIGHT);
	if bkeyleft and not bkeyright then
		moveangle = -3000;
	elseif not bkeyleft and bkeyright then
		moveangle = 3000;
	end
		
	moveangle = hdss.Get(HDSS_REGANGLE, moveangle);
	local baseangle = drainangle;
	if moveangle ~= drainangle then
		
		local plusval = 150;
		drainangle = hdss.Get(HDSS_REGANGLE, drainangle);
		local bplus = true;
		if moveangle > drainangle then
			if drainangle + 18000 < moveangle then
				bplus = false;
			end
		else
			if moveangle + 18000 > drainangle then
				bplus = false;
			end
		end
		
		if bplus then
			if moveangle < drainangle then
				moveangle = moveangle + 36000;
			end
			baseangle = drainangle + plusval;
			if baseangle > moveangle then
				baseangle = moveangle;
			end
		else
			if moveangle > drainangle then
				moveangle = moveangle - 36000;
			end	
			baseangle = drainangle - plusval;
			if baseangle < moveangle then
				baseangle = moveangle;
			end
		end
		baseangle = hdss.Get(HDSS_REGANGLE, baseangle);
	end
	hdssSD(LConst_Desc_DrainAngle+playerindex, baseangle-9000);
	
	
	game.SetDrainSpriteInfo(playerindex, x, y, baseangle, hscale);
		
	local r = 128 * hscale;
	local rl = r * 0.95105651629515357211643933337938 / 2;
	local rs = r * 0.69098300562505257589770658281718 / 2;
	local rc = r * 0.47692506126500779613470272746983;
--	local l = r * 1.1755705045849462583374119092781;
	local alphaangle = -6761.3822440803248593179302045761;
--	local alphaanglearc = -1.1800838214508454916725787783211;
	
	local cenangle = baseangle + alphaangle;
		
	local cenpos	=	
	{
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	}

	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	for i=0, 4 do
		cenpos[i+1][1] = hdss.Get(HDSS_COSA, cenangle+i*7200) * rc;
		cenpos[i+1][2] = hdss.Get(HDSS_SINA, cenangle+i*7200) * rc;
		hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, x+cenpos[i+1][1], y+cenpos[i+1][2], rl, rs, 7200*i+1800+baseangle);
	end
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	return true;
end

function ePlayerDrain_07(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 200, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	if draintimer < 3 then
		hscale = draintimer * 0.25 + 0.75;
	else
		hscale = 1.5;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	local r = hscale * 32;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	
	return true;
end

function ePlayerDrain_08(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	local vscale = CenterH;
	if draintimer < 32 then
		hscale = draintimer;
	else
		hscale = 32;
	end
	local ceny = CenterY;
	game.SetDrainSpriteInfo(playerindex, x, ceny, 0, hscale, vscale);
		
	hdssENAZBUILD(playerindex, ENAZTYPE_RECT+ENAZOP_AND, x, ceny, hscale/2, vscale/2);
	
	return true;
end

function ePlayerDrain_09(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	local yoffset;
	if draintimer < 9 then
		hscale = draintimer * 0.125 + 0.625;
		yoffset = -(draintimer * 6 + 30);
	else
		hscale = 1.75;
		yoffset = -84;
	end
	game.SetDrainSpriteInfo(playerindex, x, y+yoffset, 0, hscale);
	
	local r = hscale * 32;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y+yoffset, r);
	
	return true;
end

function ePlayerDrain_10(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local vscale;
	local yoffset;
	if draintimer < 48 then
		vscale = draintimer;
	else
		vscale = 48;
	end
	local hscale = CenterW;
	local cenx = helper_GetCenterX(playerindex);
	game.SetDrainSpriteInfo(playerindex, cenx, y, 0, hscale, vscale);
		
	hdssENAZBUILD(playerindex, ENAZTYPE_RECT+ENAZOP_AND, cenx, y, hscale/2, vscale/2);
	
	return true;
end

function ePlayerDrain_11(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	local yoffset;
	if draintimer < 16 then
		hscale = draintimer;
	else
		hscale = 16;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, CenterH*2, hscale, 9000);
	local cenx = helper_GetCenterX(playerindex);
		
	hdssENAZBUILD(playerindex, ENAZTYPE_RECT+ENAZOP_OR, x, CenterY, hscale/2, CenterH/2);
	hdssENAZBUILD(playerindex, ENAZTYPE_RECT+ENAZOP_OR, cenx, y, CenterW/2, hscale/2);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, cenx, CenterY, CenterH);
	
	return true;
end

function ePlayerDrain_12(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	local vscale;
	if draintimer < 40 then
		hscale = draintimer * 0.029375 + 0.075;
		vscale = draintimer * 0.014 + 0.04;
	else
		hscale = 1.25
		vscale = 0.6;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale, vscale);
	
	local r = vscale*37+hscale*hscale*128*64/vscale/74;
	local yoffset = r - vscale * 74;
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y-yoffset, r);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y+yoffset, r);
	return true;
end

function ePlayerDrain_13(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	if draintimer < 4 then
		hscale = draintimer * 0.0625 + 0.75;
	else
		hscale = 1;
	end
	local angle = draintimer * 300;
	game.SetDrainSpriteInfo(playerindex, x, y, angle, hscale);
	
	local r = hscale * 48;
	local rs = hscale * 24;
	local rl = hscale * 96;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_OR, x, y, r);
	for i=0, 5 do
		local cosval = hdss.Get(HDSS_COSA, angle+i*6000);
		local sinval = hdss.Get(HDSS_SINA, angle+i*6000);
		local xoffset = (r+rs)*cosval;
		local yoffset = (r+rs)*sinval;
		hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_OR, x+xoffset, y+yoffset, rs);
	end
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, rl);
	
	return true;
end

function ePlayerDrain_14(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, 0.011796875, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	if draintimer < 12 then
		hscale = draintimer * 0.05 + 0.15;
	else
		hscale = 0.75;
	end
	
	local drainangle = hdss.Get(HDSS_D, LConst_Desc_DrainAngle+playerindex);
	local moveangle = 9000;
	local bkeyup = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_UP);
	local bkeydown = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_DOWN);
	local bkeyleft = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_LEFT);
	local bkeyright = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_RIGHT);
	if bkeyup and not bkeydown then
		if bkeyleft and not bkeyright then
			moveangle = -13500;
		elseif not bkeyleft and bkeyright then
			moveangle = -4500;
		else
			moveangle = -9000;
		end
	elseif not bkeyup and bkeydown then
		if bkeyleft and not bkeyright then
			moveangle = 13500;
		elseif not bkeyleft and bkeyright then
			moveangle = 4500;
		else
			moveangle = 9000;
		end
	else
		if bkeyleft and not bkeyright then
			moveangle = 18000;
		elseif not bkeyleft and bkeyright then
			moveangle = 0;
		else
			moveangle = drainangle-18000;
		end
	end
	
	moveangle = moveangle + 18000;
	moveangle = hdss.Get(HDSS_REGANGLE, moveangle);
	
	local baseangle = drainangle;
	if moveangle ~= drainangle then
		
		local plusval = 1500;
		drainangle = hdss.Get(HDSS_REGANGLE, drainangle);
		local bplus = true;
		if moveangle > drainangle then
			if drainangle + 18000 < moveangle then
				bplus = false;
			end
		else
			if moveangle + 18000 > drainangle then
				bplus = false;
			end
		end
		
		if bplus then
			if moveangle < drainangle then
				moveangle = moveangle + 36000;
			end
			baseangle = drainangle + plusval;
			if baseangle > moveangle then
				baseangle = moveangle;
			end
		else
			if moveangle > drainangle then
				moveangle = moveangle - 36000;
			end	
			baseangle = drainangle - plusval;
			if baseangle < moveangle then
				baseangle = moveangle;
			end
		end
		baseangle = hdss.Get(HDSS_REGANGLE, baseangle);
	end
	hdssSD(LConst_Desc_DrainAngle+playerindex, baseangle);
	
	game.SetDrainSpriteInfo(playerindex, x, y, baseangle, hscale);
	
	local r = hscale*(37+128*64/74);
	local offset = r - hscale * 74;
	local cosval = hdss.Get(HDSS_COSA, baseangle);
	local sinval = hdss.Get(HDSS_SINA, baseangle);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x+offset*sinval, y+offset*cosval, r);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x-offset*sinval, y-offset*cosval, r);
	return true;
end

function ePlayerDrain_15(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	if draintimer < 90 then
		hscale = draintimer * 0.004 + 0.84;
	else
		hscale = 1.2;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	local r = hscale * 80;
	local yoffset = hscale * 32;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_AND, x, y+yoffset, r, r, 13500);
	return true;
end

function ePlayerDrain_16(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	if draintimer < 5 then
		hscale = draintimer * 0.1 + 0.25;
	else
		hscale = 0.75;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	local r = hscale * 128;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	
	return true;
end

function ePlayerDrain_17(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	if draintimer < 20 then
		hscale = (20-draintimer) * 0.2375;
	else
		hscale = 0;
	end
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	local r = hscale * 128;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	return true;
end

function ePlayerDrain_18(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale = 0.6;
	
	local drainangle = hdss.Get(HDSS_D, LConst_Desc_DrainAngle+playerindex)+9000;
	local moveangle = 0;
	if draintimer == 1 then
		drainangle = 0;
	end
	local bkeyleft = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_LEFT);
	local bkeyright = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_RIGHT);
	if bkeyleft and not bkeyright then
		moveangle = -9000;
	elseif not bkeyleft and bkeyright then
		moveangle = 9000;
	end
		
	moveangle = hdss.Get(HDSS_REGANGLE, moveangle);
	local baseangle = drainangle;
	if moveangle ~= drainangle then
		
		local plusval = 600;
		drainangle = hdss.Get(HDSS_REGANGLE, drainangle);
		local bplus = true;
		if moveangle > drainangle then
			if drainangle + 18000 < moveangle then
				bplus = false;
			end
		else
			if moveangle + 18000 > drainangle then
				bplus = false;
			end
		end
		
		if bplus then
			if moveangle < drainangle then
				moveangle = moveangle + 36000;
			end
			baseangle = drainangle + plusval;
			if baseangle > moveangle then
				baseangle = moveangle;
			end
		else
			if moveangle > drainangle then
				moveangle = moveangle - 36000;
			end	
			baseangle = drainangle - plusval;
			if baseangle < moveangle then
				baseangle = moveangle;
			end
		end
		baseangle = hdss.Get(HDSS_REGANGLE, baseangle);
	end
	hdssSD(LConst_Desc_DrainAngle+playerindex, baseangle-9000);
	
	
	game.SetDrainSpriteInfo(playerindex, x, y, baseangle, hscale);
		
	local r = 128 * hscale;
	local rs = 80 * hscale;
	local offset = 48;
	local xoffset = hdss.Get(HDSS_COSA, baseangle+9000) * offset;
	local yoffset = hdss.Get(HDSS_SINA, baseangle+9000) * offset;

	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_NOTAND, x+xoffset, y+yoffset, rs);
	return true;
end

function ePlayerDrain_19(playerindex, x, y, draintimer, type)
	return ePlayerDrain_00(playerindex, x, y, draintimer, type);
end

function ePlayerDrain_20(playerindex, x, y, draintimer, type)
	return ePlayerDrain_01(playerindex, x, y, draintimer, type);
end

function ePlayerDrain_21(playerindex, x, y, draintimer, type)
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local pgx = hdss.Get(HDSS_PGX, playerindex, 0);
	local pgy = hdss.Get(HDSS_PGY, playerindex, 0);
	local hscale;
	if draintimer < 16 then
		hscale = draintimer * 0.1 + 0.4;
	else
		hscale = 2;
	end
	game.SetDrainSpriteInfo(playerindex, pgx, pgy, 0, hscale);
	
	local r = hscale * 32;
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, pgx, pgy, r);
	
	return true;
end

function ePlayerDrain_22(playerindex, x, y, draintimer, type)

	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	if draintimer > 60 then
		draintimer = 60;
	elseif draintimer < 30 then
		draintimer = 30;
	end
	local hscale = (draintimer / 100) + 0.4;
	game.SetDrainSpriteInfo(playerindex, x, y, 0, hscale);
	
	local r = 128 * hscale;
	local rl = r * 0.95105651629515357211643933337938 / 2;
	local rs = r * 0.69098300562505257589770658281718 / 2;
	local rc = r * 0.47692506126500779613470272746983;
--	local l = r * 1.1755705045849462583374119092781;
	local alphaangle = -6761.3822440803248593179302045761;
--	local alphaanglearc = -1.1800838214508454916725787783211;
	
	local cenangle = alphaangle;
		
	local cenpos	=	
	{
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	}

	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	for i=0, 4 do
		cenpos[i+1][1] = hdss.Get(HDSS_COSA, cenangle+i*7200) * rc;
		cenpos[i+1][2] = hdss.Get(HDSS_SINA, cenangle+i*7200) * rc;
		hdssENAZBUILD(playerindex, ENAZTYPE_RIGHTANGLED+ENAZOP_OR, x+cenpos[i+1][1], y+cenpos[i+1][2], rl, rs, 7200*i+1800);
	end
	
	hdssENAZBUILD(playerindex, ENAZTYPE_CIRCLE+ENAZOP_AND, x, y, r);
	
	return true;
end

function ePlayerDrain_23(playerindex, x, y, draintimer, type)
	
	if type ~= nil then
		game.SetGhostActiveInfo(playerindex, 160, type+1, type+1, -9000, LConst_ActiveGhostDefaultAccel, LConst_ActiveGhostDefaultDamageRate);
		hdssSE(SE_GHOST_ACTIVATE, x, y);
		return true;
	end
	
	local hscale;
	local vscale;
	local yoffset;
	if draintimer < 8 then
		hscale = draintimer * 5 + 40;
		vscale = draintimer * 10 + 80;
	else
		hscale = 80;
		vscale = 160;
	end
	
	local drainangle = hdss.Get(HDSS_D, LConst_Desc_DrainAngle+playerindex);
	local moveangle = 9000;
	local bkeyup = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_UP);
	local bkeydown = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_DOWN);
	local bkeyleft = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_LEFT);
	local bkeyright = hdss.Get(HDSS_CHECKKEY, playerindex, KSI_RIGHT);
	if bkeyup and not bkeydown then
		if bkeyleft and not bkeyright then
			moveangle = -13500;
		elseif not bkeyleft and bkeyright then
			moveangle = -4500;
		else
			moveangle = -9000;
		end
	elseif not bkeyup and bkeydown then
		if bkeyleft and not bkeyright then
			moveangle = 13500;
		elseif not bkeyleft and bkeyright then
			moveangle = 4500;
		else
			moveangle = 9000;
		end
	else
		if bkeyleft and not bkeyright then
			moveangle = 18000;
		elseif not bkeyleft and bkeyright then
			moveangle = 0;
		else
			moveangle = drainangle-18000;
		end
	end
	
	moveangle = moveangle + 18000;
	moveangle = hdss.Get(HDSS_REGANGLE, moveangle);
	
	local baseangle = drainangle;
	if moveangle ~= drainangle then
		
		local plusval = 1500;
		drainangle = hdss.Get(HDSS_REGANGLE, drainangle);
		local bplus = true;
		if moveangle > drainangle then
			if drainangle + 18000 < moveangle then
				bplus = false;
			end
		else
			if moveangle + 18000 > drainangle then
				bplus = false;
			end
		end
		
		if bplus then
			if moveangle < drainangle then
				moveangle = moveangle + 36000;
			end
			baseangle = drainangle + plusval;
			if baseangle > moveangle then
				baseangle = moveangle;
			end
		else
			if moveangle > drainangle then
				moveangle = moveangle - 36000;
			end	
			baseangle = drainangle - plusval;
			if baseangle < moveangle then
				baseangle = moveangle;
			end
		end
		baseangle = hdss.Get(HDSS_REGANGLE, baseangle);
	end
	hdssSD(LConst_Desc_DrainAngle+playerindex, baseangle);
	
	game.SetDrainSpriteInfo(playerindex, x, y-80, baseangle+9000, hscale, vscale);
		
	hdssENAZBUILD(playerindex, ENAZTYPE_RECT+ENAZOP_AND, x, y-80, hscale/2, vscale/2, baseangle);
	
	return true;
end