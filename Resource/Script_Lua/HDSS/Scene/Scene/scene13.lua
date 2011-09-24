function Scene_s13(playerindex, timer)
	local cenx = helper_GetCenterX(playerindex);
	
	if timer == POSTAT then
		
		for i=0, 18 do
			hdssBGOFF(playerindex, i);
		end
		
	elseif timer == QUITAT then
		
		for i=0, 18 do
			hdssBGFLAG(playerindex, i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		local col = global.ARGB(0xff, 0xffffff);
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 0, SI_Scene_13_1
			},
			{
				cenx-3200, 1920, -1440, 6400, 6400, -13500, 0, 0
			},
			{
				-0.008
			}
		)
		hdssBGCOLOR(playerindex, 0, col, col, 0, 0);
				
		local coltop = global.ARGB(0xff, 0xe0e0c0);
		hdssBGVALUE(playerindex, 18, SI_White, cenx, CenterY-20, CenterW, CenterH-40);
		hdssBGCOLOR(playerindex, 18, coltop, coltop, 0, 0, BLEND_ALPHAADD);
	
	elseif math.mod(timer, 16) == 0 then
		local turn = timer / 16;
		local loopturn = math.mod(turn, 4);
		local trueloopturn = math.mod(turn, 8);
		for i=0, 1 do
			local bgindex = (7-trueloopturn)*2 + 2 + i;
			local scale = 0.75;
			local posoffset = -i * 40;
			local paral = RANDT(-60, 60);
			local edgeoffset = 128;
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, bgindex, SI_Scene_13_2, global.ARGB(0xff, 0xA0A0A0)
				},
				{
					cenx - RANDT(72, 216) + (i*2-1) * edgeoffset, -160+posoffset, -480+posoffset, 256*scale, 256*scale, 0, 0, 0
				},
				{
					5.12, 5.12, 9000, true
				},
				{
					paral
				}
			)
			hdssBGFLAG(playerindex, bgindex, BG_LIGHTUPNORMAL, 128);
		end
	end
	return true;
end