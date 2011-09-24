function Spell_s02(playerindex, timer)
		
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, LConst_gamebg_spellid_1);
		
	elseif timer == QUITAT then
		
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEOUT, BGMT_FADE/2);
		
	elseif timer == 1 then
		local cenx = helper_GetCenterX(playerindex);
		local col = global.ARGB(0, 0xffffff);
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, LConst_gamebg_spellid_1, SI_Spell_02_1, col
			},
			{
				cenx-TotalH*0.6, TotalCenterY-TotalH*0.6, 0, TotalH*1.2, TotalH*1.2
			},
			{
				0.9, 0, 9000, true, true
			}
		)
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEIN, BGMT_FADE);
	end
	
	return true;
end