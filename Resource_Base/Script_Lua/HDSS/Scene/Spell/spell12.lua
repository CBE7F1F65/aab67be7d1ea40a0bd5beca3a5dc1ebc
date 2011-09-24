function Spell_s12(playerindex, timer)
		
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, LConst_gamebg_spellid_1, LConst_gamebg_spellid_2);
		
	elseif timer == QUITAT then
		
		for i=0, 1 do
			hdssBGFLAG(playerindex, i+LConst_gamebg_spellid_1, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		local cenx = helper_GetCenterX(playerindex);
		local col = global.ARGB(0, 0xffffff);
		hdssBGVALUE(playerindex, LConst_gamebg_spellid_2, SI_Spell_12_1, cenx, CenterY, 448, TotalH, col);
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, LConst_gamebg_spellid_1, SI_Spell_12_2, col
			},
			{
				cenx-224, 0, 0, 448, TotalH
			},
			{
				0.003, 0, -9000
			}
		)
		hdssBGCOLOR(playerindex, LConst_gamebg_spellid_2, col, col, col, col, BLEND_ALPHAADD);
		
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEIN, BGMT_FADE);
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_2, BG_FADEINHALF, BGMT_FADE);
	elseif timer > BGMT_FADE then
		local col = hdssHSVTORGB((hdss.Get(HDSS_ROLL, timer, 240))/240, 1, 1, 1);
		hdssBGCOLOR(playerindex, LConst_gamebg_spellid_2, col, col, col, col);
	end
	return true;
end