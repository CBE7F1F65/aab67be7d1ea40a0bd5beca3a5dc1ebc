function Scene_s02(playerindex, timer)
		
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
		for i=0, 2 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i, SI_Scene_02_1+i
				},
				{
					cenx-3200, 2400, -2000, 6400, 6400, -16500, 0, 0
				},
				{
					-0.008+i*0.001
				}
			)
		end
		local col = global.ARGB(0x80, 0xffffff);
		hdssBGCOLOR(playerindex, 2, col, col, col, col);
		
	end
		
	return true;
end