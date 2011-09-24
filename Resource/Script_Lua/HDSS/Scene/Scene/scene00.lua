function Scene_s00(playerindex, timer)
	
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
				playerindex, 0, SI_Scene_00_1
			},
			{
				cenx-3200, 1920, -1440, 6400, 6400, -13500, 0, 0
			},
			{
				-0.008
			}
		)
		hdssBGCOLOR(playerindex, 0, col, col, 0, 0);
		
		
		local coltop = global.ARGB(0xff, 0xb4e5f9);
		hdssBGVALUE(playerindex, 1, SI_White, cenx, CenterY-20, CenterW, CenterH-40);
		hdssBGCOLOR(playerindex, 1, coltop, coltop, 0, 0, BLEND_ALPHAADD);
	
	elseif math.mod(timer, 32) == 0 then
		local turn = timer / 32;
		local loopturn = math.mod(turn, 4);
		for i=0, 1 do
			local bgindex = 12-loopturn + 2 + i * 4;
			local scale = 1.25;
			local posoffset = -i * 40;
			local paral = RANDT(-60, 60);
			local edgeoffset = 200;
			if loopturn == 0 then
				edgeoffset = 160;
				paral = (i*2-1) * RANDT(-45, -60);
			end
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, bgindex, SI_Scene_00_4, global.ARGB(0xff, 0xA0A0A0)
				},
				{
					cenx - loopturn * 12 + (i*2-1) * edgeoffset, -640+posoffset, -480+posoffset, 16*scale, 512*scale, 0, 0, 0
				},
				{
					5.12, 5.12, 9000, true
				},
				{
					paral
				}
			)
			hdssBGFLAG(playerindex, bgindex, BG_LIGHTUPNORMAL, 128);
			edgeoffset = edgeoffset + 240
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, bgindex-8, RANDT(0, 1)+SI_Scene_00_2, global.ARGB(0xff, 0xA0A0A0)
				},
				{
					cenx - loopturn * 12 + (i*2-1) * edgeoffset, RANDT(-360, -200)+posoffset, -480+posoffset, 256*scale, 256*scale, 0, 0, i*18000
				},
				{
					5.12, 5.12, 9000, true
				},
				{
					paral
				}
			)
			hdssBGFLAG(playerindex, bgindex-8, BG_LIGHTUPNORMAL, 128);
		end
	end
	
	return true;
end