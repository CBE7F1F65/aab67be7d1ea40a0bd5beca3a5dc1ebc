function Scene_s17(playerindex, timer)
	local cenx = helper_GetCenterX(playerindex);
	
	if timer == POSTAT then
		
		for i=0, 38 do
			hdssBGOFF(playerindex, i);
		end
		
	elseif timer == QUITAT then
		
		for i=0, 38 do
			hdssBGFLAG(playerindex, i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		local col = global.ARGB(0xff, 0xffffff);
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 0, SI_Scene_17_1
			},
			{
				cenx-3200, 1920, -1440, 6400, 6400, -13500, 0, 0
			},
			{
				-0.002
			}
		)
		hdssBGCOLOR(playerindex, 0, col, col, 0, 0);
				
		local coltop = global.ARGB(0xff, 0xa0b0f0);
		hdssBGVALUE(playerindex, 38, SI_White, cenx, CenterY-20, CenterW, CenterH-40);
		hdssBGCOLOR(playerindex, 38, coltop, coltop, 0, 0, BLEND_ALPHAADD);
	
	elseif math.mod(timer, 32) == 0 then
		local turn = timer / 32;
		local loopturn = math.mod(turn, 4);
		local trueloopturn = math.mod(turn, 16);
		
		if math.mod(timer, 320) == 0 then
			local leftrightindi = math.mod(timer, 320*2) / 320;
			local bgindex = 34+math.mod(timer, 320*4)/320;
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, bgindex, SI_Scene_17_4, global.ARGB(0xff, 0xA0A0A0)
				},
				{
					cenx + (leftrightindi*2-1)*960, -1600-RANDT(0, 400), -1440, 1200, 1200, 0, 18000*leftrightindi, 0
				},
				{
					1.28, 1.28, 9000, true
				}
			)
			hdssBGFLAG(playerindex, bgindex, BG_LIGHTUPNORMAL, 512);
		end
		
		for i=0, 1 do
			local bgindex = (15-trueloopturn)*2 + 2 + i;
			local scale = 1;
			local posoffset = -i * 80;
			local paral = RANDT(-60, 60);
			local edgeoffset = 128;
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, bgindex, SI_Scene_17_2+RANDT(0, 1), global.ARGB(0xff, 0xA0A0A0)
				},
				{
					cenx + RANDT(-240, 120) + (i*2-1) * edgeoffset, -160+posoffset, -480+posoffset, 160*scale, 128*scale, 0, 0, 0
				},
				{
					1.28, 1.28, 9000, true
				},
				{
					paral
				}
			)
			hdssBGFLAG(playerindex, bgindex, BG_LIGHTUPNORMAL, 512);
		end
	end
	return true;
end