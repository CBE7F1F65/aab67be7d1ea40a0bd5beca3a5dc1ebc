function Spell_s18(playerindex, timer)
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, LConst_gamebg_spellid_1);
		
	elseif timer == QUITAT then
		
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEOUT, BGMT_FADE/2);
		
	elseif timer == 1 then
		local cenx = helper_GetCenterX(playerindex);
		local col = global.ARGB(0, 0xffffff);
		hdssBGVALUE(playerindex, LConst_gamebg_spellid_1, SI_Spell_18_1, cenx, CenterY, TotalH, TotalH, col);
		
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEIN, BGMT_FADE);
	end
		
	return true;
end