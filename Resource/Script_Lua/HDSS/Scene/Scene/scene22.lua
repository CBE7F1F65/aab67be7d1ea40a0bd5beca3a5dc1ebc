function Scene_s22(playerindex, timer)
		
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
		local colb = global.ARGB(0xff, 0xffffff);
		local colt = global.ARGB(0x80, 0xffffff);
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 2, SI_Scene_22_1
			},
			{
				cenx-1200, 1920, -1440, 2400, 4800, -16500, 0, 0
			},
			{
				-0.002
			}
		)
		hdssBGCOLOR(playerindex, 2, colb, colb, colt, colt);
		
		for i=0,1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i, SI_Scene_22_2
				},
				{
					cenx-1200+(i*2-1)*600, 1920, -1440, 2400, 4800, -16500, 0, 0
				},
				{
					-0.002
				},
				{
					0, i==0
				}
			)
			hdssBGCOLOR(playerindex, i, colb, colb, colt, colt);
		end
		
	end
end