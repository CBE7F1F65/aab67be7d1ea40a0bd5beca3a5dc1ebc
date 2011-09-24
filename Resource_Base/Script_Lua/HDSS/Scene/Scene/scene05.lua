function Scene_s05(playerindex, timer)
	if timer == POSTAT then
		
		for i=0, 5 do
			hdssBGOFF(playerindex, i);
		end
		
	elseif timer == QUITAT then
		
		for i=0, 5 do
			hdssBGFLAG(playerindex, i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		local cenx = helper_GetCenterX(playerindex);
		hdssBGVALUE(playerindex, 0, SI_Scene_05_3, cenx, CenterY, 448, TotalH);
		local col = global.ARGB(0x80, 0xffffff);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i+1, SI_Scene_05_1+i, col
				},
				{
					(i*2-1)*TotalW/4+cenx-128*i, 0, 0, 256, 512
				},
				{
					0.009
				}
			)
		end
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 4, SI_Scene_05_4
			},
			{
				cenx-128, 40, 0, 256, 256
			},
			{
				0.5, 0, (1-playerindex*2)*9000, true, true
			}
		)
				
	end
	return true;
end