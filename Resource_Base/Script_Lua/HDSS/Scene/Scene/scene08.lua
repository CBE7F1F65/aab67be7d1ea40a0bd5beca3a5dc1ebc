function Scene_s08(playerindex, timer)
	if timer == POSTAT then
		
		for i=0, 16 do
			hdssBGOFF(playerindex, i);
		end
		
	elseif timer == QUITAT then
		
		for i=0, 16 do
			hdssBGFLAG(playerindex, i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		
		local cenx = helper_GetCenterX(playerindex);
		hdssBGVALUE(playerindex, 0, SI_Scene_08_1, cenx, CenterY, CenterW+128, CenterH+128);
		local coltop = global.ARGB(0x40, 0xffffff);
		local colbottom = global.ARGB(0xff, 0xc6bfd4);
		hdssBGVALUE(playerindex, 1, SI_White, cenx, CenterY, CenterW, CenterH);
		hdssBGCOLOR(playerindex, 1, coltop, coltop, colbottom, colbottom);
		
		local col = global.ARGB(0x80, 0xffffff);
		for i=0, 1 do
			local length = i*64+192;
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, 3-i, SI_Scene_08_3
				},
				{
					cenx-length/2, CenterY-length/2, 0, length, length
				},
				{
					0.4, 0, (i*2-1)*9000, true, true
				}
			)
			hdssBGCOLOR(playerindex, 3-i, col, col, col, col, BLEND_ALPHAADD);
		end
		
		for i=0, 1 do
			for j=0, 1 do
				local basex = cenx+(i*2-1)*80;
				local basey = CenterY+40+j*30;
				local basez = -80*(1-j);
				hdss.Call(HDSS_BGVALEX,
					{
						playerindex, i*2+j+12, SI_Scene_08_2
					},
					{
						basex-8, basey, basez, 16, CenterH
					}
				)
				hdss.Call(HDSS_BGVALEX,
					{
						playerindex, i*2+j+8, SI_Scene_08_2
					},
					{
						basex-(i*2-1)*8, basey, basez, 16, CenterH, 0, -9000
					}
				)
				hdss.Call(HDSS_BGVALEX,
					{
						playerindex, i*2+j+4, SI_Scene_08_2
					},
					{
						basex-8, basey, basez, 16, 16, -9000
					}
				)
			end
		end
		local colbottom = global.ARGB(0xff, 0xc6bfd4);
		hdssBGVALUE(playerindex, 16, SI_White, cenx, CenterY+CenterH/4, CenterW, CenterH/2);
		hdssBGCOLOR(playerindex, 16, 0, 0, colbottom, colbottom);
		
	end
	return true;
end