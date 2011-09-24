function Spell_s13(playerindex, timer)
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
				playerindex, LConst_gamebg_spellid_1, SI_Spell_13_2, col
			},
			{
				cenx-224, 0, 0, 448, TotalH
			},
			{
				0.004, 0, -9000
			}
		)
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, LConst_gamebg_spellid_2, SI_Spell_13_1, col
			},
			{
				cenx-TotalH*0.375, TotalCenterY-TotalH*0.375, 0, TotalH*0.75, TotalH*0.75
			},
			{
				0.7, 0, 9000, true, true
			}
		)
		hdssBGCOLOR(playerindex, LConst_gamebg_spellid_2, col, col, col, col, BLEND_ALPHAADD);
		
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEIN, BGMT_FADE);
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_2, BG_FADEINHALF, BGMT_FADE);
	end
	return true;
end