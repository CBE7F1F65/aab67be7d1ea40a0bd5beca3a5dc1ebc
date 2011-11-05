function edef_LilyFunction(x, y, guid, timer, px, py)
	if math.mod(timer, 8) == 0 then
		local modindex = timer/8;
		for i=0, 15 do
			local angle = 0 + i*600 + (hdss.Roll(modindex, 10)-5)*200;
			local speed = 1.5;
			hdss.BuildBullet(guid, x, y, angle, speed, 0, 1);
		end
	end
end

LTable_EnemyEIDFunction	=	
{
	{36, edef_LilyFunction}
}


function EdefExecute(name, timer)

	local px, py = hdss.GetPlayerInfo();
	local x, y, eID, guid = hdss.GetEnemyInfo();
	for i, it in pairs(LTable_EnemyEIDFunction) do
		if it[1] == eID then
			return it[2](x, y, guid, timer, px, py);
		end
	end
	return true;

end