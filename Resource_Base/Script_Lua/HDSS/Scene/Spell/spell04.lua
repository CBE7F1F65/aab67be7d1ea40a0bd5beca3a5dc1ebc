function Spell_s04(playerindex, timer)
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, LConst_gamebg_spellid_1, LConst_gamebg_spellid_2);
		
	elseif timer == QUITAT then
		
		for i=0, 1 do
			hdssBGFLAG(playerindex, i+LConst_gamebg_spellid_1, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		local cenx = helper_GetCenterX(playerindex);
		local col = global.ARGB(0, 0xffffff);
		hdssBGVALUE(playerindex, LConst_gamebg_spellid_1, SI_Spell_04_1, cenx, CenterY, 448, TotalH, col);
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, LConst_gamebg_spellid_2, SI_Spell_04_2, col
			},
			{
				cenx-224, 0, 0, 448, TotalH
			},
			{
				0.003, 0, -13500
			}
		)
--		hdssBGCOLOR(playerindex, LConst_gamebg_spellid_2, col, col, col, col, BLEND_ALPHAADD);
		
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEIN, BGMT_FADE);
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_2, BG_FADEINHALF, BGMT_FADE);
	end
	return true;
end