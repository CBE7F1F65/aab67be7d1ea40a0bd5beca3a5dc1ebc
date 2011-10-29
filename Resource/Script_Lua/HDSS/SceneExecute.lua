LTable_SceneIDFunction	=
{
	Scene_s00,
}

function SceneExecute(area, timer)
	
	local mapcenx, mapceny, xspeed, yspeed, mapxoffset = hdss.GetMapSpeedInfo();

	local mapxoffsetmove = 0.5;
	local mapxoffsetmax = 16;
	local tomapxoffset = mapxoffset;
	
	if hdss.CheckInput(KSI_LEFT) then
		tomapxoffset = mapxoffset-mapxoffsetmove;
		if tomapxoffset < -mapxoffsetmax then
			tomapxoffset = -mapxoffsetmax;
		end
	end
	if hdss.CheckInput(KSI_RIGHT) then
		tomapxoffset = mapxoffset+mapxoffsetmove;
		if tomapxoffset > mapxoffsetmax then
			tomapxoffset = mapxoffsetmax;
		end
	end
	
	if tomapxoffset ~= mapxoffset then
		hdss.SetMapSpeedInfo(xspeed, yspeed, tomapxoffset);
	end
	
	return LTable_SceneIDFunction[area+1](timer);

end