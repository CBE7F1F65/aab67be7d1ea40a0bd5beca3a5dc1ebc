function Scene_s14(playerindex, timer)
	if timer == POSTAT then
		
		for i=0, 4 do
			hdssBGOFF(playerindex, i);
		end
		
	elseif timer == QUITAT then
		
		for i=0, 4 do
			hdssBGFLAG(playerindex, i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		local cenx = helper_GetCenterX(playerindex);
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 2, SI_Scene_14_3
			},
			{
				cenx-3200, 1920, -1440, 6400, 6400, -9000, 0, 0
			},
			{
				-0.008
			}
		)
		local col = global.ARGB(0xff, 0xffffff);
		local coltop = global.ARGB(0x40, 0xffffff);
		hdssBGCOLOR(playerindex, 2, col, col, coltop, coltop);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i, SI_Scene_14_1+i
				},
				{
					cenx+(i*2-1)*3200, -4480, -4480, 6400, 6400, -9000, 0, 9000
				},
				{
					-0.004
				}
			)
			hdssBGCOLOR(playerindex, i, col, col, coltop, coltop);
		end
		
	elseif math.mod(timer, 128) == 0 then
		
		local cenx = helper_GetCenterX(playerindex);
		local turn = timer / 128;
		local leftrightindi = math.mod(turn, 2);
		local bgindex = leftrightindi + 3;
		local scale = 1.75;
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, bgindex, SI_Scene_14_4+RANDT(0, 1), global.ARGB(0xff, 0xA0A0A0)
			},
			{
				cenx+(leftrightindi*2-1)*160, 0, -160, 128*scale, 128*scale, -9000, 0, 9000
			},
			{
				0, 1.2, 0, true
			}
		)
		hdssBGFLAG(playerindex, bgindex, BG_LIGHTUPNORMAL, 128);
		hdssBGBLEND(playerindex, bgindex, BLEND_ALPHAADD);
	end
	return true;
		
end