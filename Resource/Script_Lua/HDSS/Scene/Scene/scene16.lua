function Scene_s16(playerindex, timer)
	local cenx = helper_GetCenterX(playerindex);
	if timer == POSTAT then
		
		for i=0, 3 do
			hdssBGOFF(playerindex, i);
		end
		
	elseif timer == QUITAT then
		
		for i=0, 3 do
			hdssBGFLAG(playerindex, i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 0, SI_Scene_16_1
			},
			{
				cenx-3200, 2400, -2000, 6400, 6400, -16500, 0, 0
			},
			{
				-0.001
			}
		)
		local coltop = global.ARGB(0xff, 0xbf0313);
		hdssBGVALUE(playerindex, 1, SI_White, cenx, CenterY+200, CenterW, CenterH+400);
		hdssBGCOLOR(playerindex, 1, coltop, coltop, 0, 0);
	end

	local cosval = hdss.Get(HDSS_COSA, timer*45);
	hdssBGVALUE(playerindex, 2, SI_Scene_16_2, cenx-cosval*40, CenterY-160, 400, 400);
	hdssBGVALUE(playerindex, 3, SI_Scene_16_2, cenx+cosval*40, CenterY-120, 400, 400);	
	
	
end