function Scene_s15(playerindex, timer)
	if timer == POSTAT then
		
		for i=0, 2 do
			hdssBGOFF(playerindex, i);
		end
		
	elseif timer == QUITAT then
		
		for i=0, 2 do
			hdssBGFLAG(playerindex, i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		local cenx = helper_GetCenterX(playerindex);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i, SI_Scene_15_1+i
				},
				{
					cenx-3200, 2400, -2000, 6400, 6400, -16500, 0, 0
				},
				{
					-0.005
				}
			)
		end
		local col = global.ARGB(0x80, 0xffffff);
		hdssBGCOLOR(playerindex, 1, col, col, col, col);
		
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 2, SI_Scene_15_3
			},
			{
				cenx-3200, 2400, -2000, 6400, 6400, -16500, 0, 0
			},
			{
				-0.008
			}
		)
		hdssBGCOLOR(playerindex, 2, col, col, col, col, BLEND_ALPHAADD);
		hdssBGVALUE(playerindex, 3, SI_Scene_15_4, cenx, CenterBossY, 192, 192);
		hdssBGCOLOR(playerindex, 3, col, col, col, col, BLEND_ALPHAADD);
		
	end
		
	return true;
end