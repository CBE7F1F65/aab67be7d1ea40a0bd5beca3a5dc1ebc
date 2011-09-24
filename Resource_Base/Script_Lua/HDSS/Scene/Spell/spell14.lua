function Spell_s14(playerindex, timer)
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, LConst_gamebg_spellid_1, LConst_gamebg_spellid_2);
		
	elseif timer == QUITAT then
		
		for i=0, 1 do
			hdssBGFLAG(playerindex, LConst_gamebg_spellid_1+i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		local cenx = helper_GetCenterX(playerindex);
		local col = global.ARGB(0, 0xffffff);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, LConst_gamebg_spellid_1+i, SI_Spell_14_1+i, col
				},
				{
					cenx-TotalH*0.5/(i+1), TotalCenterY-TotalH*0.5/(i+1), 0, TotalH/(i+1), TotalH/(i+1)
				},
				{
					0.9, 0, (i*2-1)*9000, true, true
				}
			)
			
		end
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_1, BG_FADEIN, BGMT_FADE);
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_2, BG_FADEINHALF, BGMT_FADE);
	end
	
	return true;
end