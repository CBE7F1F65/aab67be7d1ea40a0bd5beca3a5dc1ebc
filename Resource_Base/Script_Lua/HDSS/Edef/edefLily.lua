function Edef_Lily(playerindex, rank, x, y, timer, px, py)
	local actiontime = (40-rank) * 5;
	if timer == 1 then
		hdssEA(playerindex, ENAC_CHASEAIM_XYSOAOCO,
			{
				x, CenterY+40, 1.0
			},
			{
				-9000, 0, actiontime
			}
		)
	elseif timer > actiontime then
		local timermode = 11-math.floor((rank+1) / 3);
		if math.mod(timer, timermode) == 1 then
			local oneset =  math.mod(timer-actiontime, 12);
			local angle = (timer-actiontime) * 231 - 9000 - oneset * 28 + hdss.Get(HDSS_SEED) + (22-rank) * 2310;
			local speed = rank * 0.06 + 1.6 - oneset * 0.05;
			local angleadd = 43+rank;
			for i=0, 2 do
				hdssA(playerindex,
					{
						TIMERRANGE, 32, 64, ANGLESETADD, angleadd
					}
				)
				hdssB(playerindex, x, y, angle, speed, CC_Bullet_Ring, 2);
				hdssB(playerindex, x, y, angle+1000, speed+0.3, CC_Bullet_SmallBall, 2);
				hdssA(playerindex,
					{
						TIMERRANGE, 32, 64, ANGLESETADD, -angleadd
					}
				)
				hdssB(playerindex, x, y, 18000-angle, speed, CC_Bullet_Ring, 5);
				hdssB(playerindex, x, y, 18000-angle-1000, speed+0.3, CC_Bullet_SmallBall, 5);
				angle = angle + 3000;
				speed = speed + 0.5
			end
			hdssA(playerindex);
		end
	end
	return true;
end