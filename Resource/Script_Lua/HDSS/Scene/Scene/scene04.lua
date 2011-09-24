function Scene_s04(playerindex, timer)
		
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
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 1, SI_Scene_04_1
			},
			{
				cenx-3200, 2400, -2000, 6400, 6400, -16500, 0, 0
			},
			{
				0.001, 0, 0
			}
		)
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i+2, SI_Scene_04_2
				},
				{
					0, i * 180, 0, TotalW, TotalW/2
				},
				{
					0.001 * (i+1), 0, 0
				}
			)
		end
		
		local col = global.ARGB(0xff, 0xb4e5f9);
		hdssBGVALUE(playerindex, 0, SI_White, cenx, CenterY, CenterW, CenterH, col);
		
	end
	return true;
end