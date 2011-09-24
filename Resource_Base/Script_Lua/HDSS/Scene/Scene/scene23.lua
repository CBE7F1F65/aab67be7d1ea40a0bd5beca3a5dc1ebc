function Scene_s23(playerindex, timer)
	if timer == POSTAT then
		
		for i=0, 1 do
			hdssBGOFF(playerindex, i);
		end
		
	elseif timer == QUITAT then
		
		for i=0, 1 do
			hdssBGFLAG(playerindex, i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		local cenx = helper_GetCenterX(playerindex);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i, SI_Scene_23_1+1-i
				},
				{
					cenx-320, 0, 0, 640, 640, 0, 0, 0
				},
				{
					0.001+i*0.006
				}
			)
		end
		local col = global.ARGB(0xE0, 0xffffff);
		hdssBGCOLOR(playerindex, 1, col, col, col, col);
		
	end
	return true;
end