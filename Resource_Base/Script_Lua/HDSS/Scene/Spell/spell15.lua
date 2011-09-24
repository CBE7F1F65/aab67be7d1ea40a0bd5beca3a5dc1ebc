function Spell_s15(playerindex, timer)
	if timer == POSTAT then
		
		hdssBGOFF(playerindex, LConst_gamebg_spellid_1, LConst_gamebg_spellid_2, LConst_gamebg_spellid_3);
		
	elseif timer == QUITAT then
		
		for i=0, 2 do
			hdssBGFLAG(playerindex, i+LConst_gamebg_spellid_1, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		local cenx = helper_GetCenterX(playerindex);
		local col = global.ARGB(0, 0xffffff);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, LConst_gamebg_spellid_1+i, SI_Spell_15_1, col
				},
				{
					cenx+224*(-i), 0, 0, 224, TotalH
				},
				{
					0.005, 0, 9000
				}
			)
			hdssBGFLAG(playerindex, LConst_gamebg_spellid_1+i, BG_FADEIN, BGMT_FADE);
		end
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, LConst_gamebg_spellid_3, SI_Spell_15_1, col
			},
			{
				cenx-112, 0, 0, 224, TotalH
			},
			{
				0.005, 0, -9000
			}
		)
		hdssBGFLAG(playerindex, LConst_gamebg_spellid_3, BG_FADEIN, BGMT_FADE);
		hdssBGBLEND(playerindex, LConst_gamebg_spellid_3, BLEND_ALPHAADD);
	end
	return true;
end