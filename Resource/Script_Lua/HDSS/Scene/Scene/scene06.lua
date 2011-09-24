function Scene_s06(playerindex, timer)
		
	if timer == POSTAT then
		
		for i=0, 3 do
			hdssBGOFF(playerindex, i);
		end
		
	elseif timer == QUITAT then
		
		for i=0, 3 do
			hdssBGFLAG(playerindex, i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		local cenx = helper_GetCenterX(playerindex);
		local backcol = global.ARGB(0xff, 0x644c59);
		hdssBGVALUE(playerindex, 0, SI_White, cenx, CenterY, CenterW, CenterH, backcol);
		local col = global.ARGB(0xff, 0xffffff);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i+1, SI_Scene_06_2-i
				},
				{
					cenx-3200, 1920, -1440, 6400, 6400, -13500, 0, 0
				},
				{
					(-0.004+i*0.001)*(i+1), 0, 8500+1000*i
				}
			)
			hdssBGCOLOR(playerindex, i+1, col, col, 0, 0);
		end
		local coltop = global.ARGB(0xff, 0xb4e5f9);
		hdssBGVALUE(playerindex, 3, SI_White, cenx, CenterY-20, CenterW, CenterH-40);
		hdssBGCOLOR(playerindex, 3, coltop, coltop, 0, 0, BLEND_ALPHAADD);
		
	end
	return true;
end