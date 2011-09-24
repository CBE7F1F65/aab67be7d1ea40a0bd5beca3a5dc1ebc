function Spell_s16(playerindex, timer)
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, LConst_gamebg_spellid_1, LConst_gamebg_spellid_2);
		
	elseif timer == QUITAT then
		
		for i=0, 1 do
			hdssBGFLAG(playerindex, i+LConst_gamebg_spellid_1, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		local cenx = helper_GetCenterX(playerindex);
		local col = global.ARGB(0, 0xffffff);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, LConst_gamebg_spellid_1+i, SI_Spell_16_1, col
				},
				{
					cenx-224, 0, 0, 448, TotalH
				},
				{
					i*0.003, 0, i*18000+9000
				}
			)
			hdssBGFLAG(playerindex, LConst_gamebg_spellid_1+i, BG_FADEIN, BGMT_FADE);
		end
	end
	return true;
end