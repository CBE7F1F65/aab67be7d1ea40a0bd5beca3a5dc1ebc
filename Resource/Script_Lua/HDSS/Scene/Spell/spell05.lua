function Spell_s05(playerindex, timer)
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, LConst_gamebg_spellid_1, LConst_gamebg_spellid_2, LConst_gamebg_spellid_3);
		
	elseif timer == QUITAT then
		
		for i=0, 2 do
			hdssBGFLAG(playerindex, i+LConst_gamebg_spellid_1, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		local cenx = helper_GetCenterX(playerindex);
		local col = global.ARGB(0, 0xffffff);
		hdssBGVALUE(playerindex, LConst_gamebg_spellid_2, SI_Spell_05_1, cenx, CenterY, 448, TotalH, col);
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, LConst_gamebg_spellid_1, SI_Spell_05_2, col
			},
			{
				cenx-224, 0, 0, 448, TotalH
			},
			{
				0.009, 0, -9000
			}
		)
		
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEIN, BGMT_FADE);
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_2, BG_FADEIN, BGMT_FADE);
		
	elseif timer > 60 and timer < 80 then
		hdssBGVALUE(playerindex, LConst_gamebg_spellid_3, SI_Spell_05_3, helper_GetCenterBossX(playerindex), CenterBossY, 384, (timer-60)*384/20);
	end
	return true;
end