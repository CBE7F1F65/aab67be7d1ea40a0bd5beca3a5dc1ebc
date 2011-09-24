function Scene_s18(playerindex, timer)
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
		hdssBGVALUE(playerindex, 2, SI_Scene_18_3, cenx, CenterY, CenterW, CenterW);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i, SI_Scene_18_1+1-i
				},
				{
					cenx-3200, 2400, -2000, 6400, 6400, -16500, 0, 0
				},
				{
					(i*2-1)*0.008
				}
			)
		end
		local col = global.ARGB(0xff, 0xffffff);
		hdssBGCOLOR(playerindex, 0, col, col, col, col, BLEND_ALPHAADD);
		hdssBGCOLOR(playerindex, 1, col, col, col, col, BLEND_ALPHAADD);
		hdssBGCOLOR(playerindex, 2, col, col, col, col, BLEND_ALPHAADD);
		
	end
		
	return true;
end