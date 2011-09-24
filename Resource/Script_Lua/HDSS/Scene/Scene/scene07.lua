function Scene_s07(playerindex, timer)
		
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
					playerindex, i, SI_Scene_07_1
				},
				{
					cenx-3200, 2400, -2000, 6400, 6400, -16500, 0, 0
				},
				{
					-0.004+i*0.001, 0, 9000+i*1000
				}
			)
		end
		local col = global.ARGB(0x80, 0xffffff);
		hdssBGCOLOR(playerindex, 1, col, col, col, col);
		
		local coltop = global.ARGB(0x80, 0xbb7bbd);
		hdssBGVALUE(playerindex, 2, SI_White, cenx, CenterY-20, CenterW, CenterH-40);
		hdssBGCOLOR(playerindex, 2, coltop, coltop, 0, 0, BLEND_ALPHAADD);
		
	end
	return true;
end