function _Scene_s21_BuildOne(playerindex, cenx, x, y, z, siid, bgindex)
	local scale = (cenx-x)*2 / 192;
	local col = global.ARGB(0xff, 0x101010);
	for i=0, 1 do
		if i == 1 then
			col = global.ARGB(0xff, 0xffffff);
		end
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, bgindex+(1-i), siid+i, col
			},
			{
				x, y, z, 192*scale, 16*scale, -i*9000-3000, 0, 0
			},
			{
				8, 2, 9000, true
			}
		)
	end
end

function Scene_s21(playerindex, timer)
	local cenx = helper_GetCenterX(playerindex);
	
	if timer == POSTAT then
		
		for i=0, 46 do
			hdssBGOFF(playerindex, i);
		end
		
	elseif timer == QUITAT then
		
		for i=0, 46 do
			hdssBGFLAG(playerindex, i, BG_FADEOUT, BGMT_FADE/2);
		end
		
	elseif timer == 1 then
		local col = global.ARGB(0xff, 0xffffff);
		hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, 0, SI_Scene_21_1
				},
				{
					cenx-3200, 2400, -2000, 6400, 6400, -16500, 0, 0
				},
				{
					-0.008
				}
		)
		
		local sidecolor = global.ARGB(0xff, 0x101010);
		for i=0, 1 do
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i+43, SI_Scene_21_4_01+i, col
				},
				{
					cenx+(i*2-1)*624-48, -1200, -1300, 96, 3072, 1404, 0, 0
				},
				{
					0.005
				}
			)
			hdss.Call(
				HDSS_BGVALEX,
				{
					playerindex, i+1, SI_Scene_21_4_03+i, sidecolor
				},
				{
					cenx+(i*2-1)*576, -1200, -1300, 96, 3072, 1404, -9000, 0
				},
				{
					0.005
				}
			)
		end
		
		hdss.Call(
			HDSS_BGVALEX,
			{
				playerindex, 45, SI_Scene_21_2
			},
			{
				cenx-224, 0, 0, 448, TotalH
			},
			{
				0.003, 0, 4500
			}
		)

		local coltop = global.ARGB(0xff, 0xb08090);
		hdssBGVALUE(playerindex, 46, SI_White, cenx, CenterY-20, CenterW, CenterH-40, col);
		hdssBGCOLOR(playerindex, 46, coltop, coltop, 0, 0);
		
		for i=0, 19 do
			_Scene_s21_BuildOne(playerindex, cenx, cenx-576, (19-i)*128-1200, (19-i)*32-1300, SI_Scene_21_3_01+math.mod((i+13)*2, 16), i*2+3);
		end
	
	elseif math.mod(timer, 16) == 0 then
		local nowindex = math.mod(timer / 16, 20) * 2;
		_Scene_s21_BuildOne(playerindex, cenx, cenx-576, -1200, -1300, SI_Scene_21_3_01+math.mod(nowindex, 16), nowindex+3);
	end
	return true;
end