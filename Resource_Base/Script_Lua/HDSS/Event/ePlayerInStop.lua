function ePlayerInSpellStop(playerindex, bSpell, spellPlayerID, oplayerID, stoptimer, stopmaxtime, spellClass, spellLevel)

	local x = helper_GetCenterBossX(playerindex);
	
	if stoptimer == stopmaxtime - 2 then
		for i=0, 1 do
			hdssBGOFF(i, LConst_gamefg_spellflashid);
		end
	end
		
	if bSpell then
		if stoptimer == 1 then
			hdssSEOFF();
			hdssSE(SE_PLAYER_SPELLCUTIN);
		end
		
		if stoptimer < stopmaxtime-2 then
			local vscale = 2.0;
			local alpha = 0xff;
			if stoptimer < stopmaxtime/4 then
				local intervalue = stoptimer / (stopmaxtime/4);
				vscale = hdssINTER(8.0, 2.0, intervalue);
				alpha = hdssINTER(0, 0xff, intervalue);
			end
			
			local siid = SI_PlayerSpellCutIn_01_LL + spellPlayerID*4;
			if playerindex == 1 then
				siid = siid + 2;
			end
			local col = global.ARGB(alpha, 0xffffff);
			
			x = x - 16;
			hdssFRONTSPRITE(LConst_game_FrontSprite_SpellCutInLeftID, siid, x, 160, 0, 2, vscale, col);
			siid = siid + 1;
			x = x + 144;
			hdssFRONTSPRITE(LConst_game_FrontSprite_SpellCutInRightID, siid, x, 160, 0, 2, vscale, col);
		else
			hdssFREEFRONTSPRITE(LConst_game_FrontSprite_SpellCutInLeftID);
			hdssFREEFRONTSPRITE(LConst_game_FrontSprite_SpellCutInRightID);
		end
	else
		if stoptimer < stopmaxtime-2 then
			local hscale = 1.0
			if stoptimer < stopmaxtime/4 then
				local intervalue = stoptimer / (stopmaxtime/4);
				hscale = hdssINTER(1.2, 1.0, intervalue);
			end
			local col = global.ARGB(0xff, 0xffffff);
			hdssFRONTSPRITE(LConst_game_FrontSprite_WarningID, SI_GameInfo_Warning, x, 240, 0, hscale, 0, col, BLEND_ALPHAADD);
			x = x + 48;
			hdssFRONTSPRITE(LConst_game_FrontSprite_SpellClassID, SI_GameInfo_ClassFairy+spellClass-1, x, 288);
			local digit0 = math.floor(spellLevel/10);
			local digit1 = spellLevel - digit0 * 10;
			x = x+ 56;
			hdssFRONTSPRITE(LConst_game_FrontSprite_LevelDigit_0ID, SI_SpellPointDigitCharacter_Red_0+digit0, x, 288);
			x = x + 6;
			hdssFRONTSPRITE(LConst_game_FrontSprite_LevelDigit_1ID, SI_SpellPointDigitCharacter_Red_0+digit1, x, 288);
		else
			hdssFREEFRONTSPRITE(LConst_game_FrontSprite_WarningID);
			hdssFADEOUTFRONTSPRITE(LConst_game_FrontSprite_SpellClassID, 32);
			hdssFADEOUTFRONTSPRITE(LConst_game_FrontSprite_LevelDigit_0ID, 32);
			hdssFADEOUTFRONTSPRITE(LConst_game_FrontSprite_LevelDigit_1ID, 32);
		end
	end
end

function ePlayerInStop(playerindex, playerID)
end