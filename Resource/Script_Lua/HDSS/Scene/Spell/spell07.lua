function Spell_s07(playerindex, timer)
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
					playerindex, LConst_gamebg_spellid_1+i, SI_Spell_07_1, col
				},
				{
					cenx-224, 0, 0, 448, TotalH
				},
				{
					0.003, 0, (i*2-1)*9000
				}
			)
		end
		
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEIN, BGMT_FADE);
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_2, BG_FADEINHALF, BGMT_FADE);
	end
	return true;
end