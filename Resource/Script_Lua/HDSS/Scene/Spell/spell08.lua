function Spell_s08(playerindex, timer)
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, LConst_gamebg_spellid_1, LConst_gamebg_spellid_2);
		
	elseif timer == QUITAT then
		
		for i=0, 1 do
			hdssBGFLAG(playerindex, i+LConst_gamebg_spellid_1, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		local cenx = helper_GetCenterX(playerindex);
		local col = global.ARGB(0, 0xffffff);
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, LConst_gamebg_spellid_1, SI_Spell_08_1, col
			},
			{
				cenx-TotalH*0.6, TotalCenterY-TotalH*0.6, 0, TotalH*1.2, TotalH*1.2
			},
			{
				0.5, 0, 9000, true, true
			}
		)
		hdssBGVALUE(playerindex, LConst_gamebg_spellid_2, SI_Spell_08_2, cenx+32, CenterY+16, 320, 320);
		hdssBGCOLOR(playerindex, LConst_gamebg_spellid_2, col, col, col, col, BLEND_ALPHAADD);
		
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEIN, BGMT_FADE);
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_2, BG_FADEIN, BGMT_FADE);
	end
	return true;
end