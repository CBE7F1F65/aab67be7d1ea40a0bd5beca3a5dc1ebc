function _eSendBulletSpeedRestrict(speed, rank)
	speed = speed + RANDTF(-0.1, 0.1);
	if speed < 0.8 then
		speed = 0.8;
	elseif speed > 3.0 + rank * 0.1 then
		speed = 3.0 + rank * 0.1;
	end
	return speed;
end

function _eSendBulletSpeed(rank, bSmall)
	return 1.3 + rank * 0.11;
end

function _eSendItemBulletSpeed(rank)
	return 1.7 + rank * 0.1;
end

function _eSendBigBulletAngle()
	return RANDT(8250, 9750);
end

function _eSendBulletSpecialSpeed(speed)
	local chara = hdss.Get(HDSS_CHARA, playerindex);
	if chara == CC_PlayerID_Aya then
		speed = speed * 0.93;
	end
	return speed;
end

function eSendRedBullet(playerindex, x, y, sendtime, speed, setID, bSmall)
	local rank = hdss.Get(HDSS_RANK);
	local angle;
	if bSmall then
		angle = RANDT(7500, 10500);
	else
		angle = _eSendBigBulletAngle();
	end
	if speed < 0 then
		speed = _eSendBulletSpeed(rank);
	elseif not bSmall then
		speed = speed + 0.3;
	end
	
	if bSmall then
		speed = _eSendBulletSpecialSpeed(speed)
	end
	
	speed = _eSendBulletSpeedRestrict(speed, rank);
	local type = CC_Bullet_MiddleBall;
	if bSmall then
		type = CC_Bullet_SmallBall;
	end
	local index = hdssB(playerindex, x, y, angle, speed, type, 4);
	if bSmall then
		game.AddSendBulletInfo(setID, sendtime+1, playerindex, index);
	end
	return true;
end

function eSendBlueBullet(playerindex, x, y, sendtime, speed, setID, bSmall)
	local rank = hdss.Get(HDSS_RANK);
	local angle;
	if bSmall then
		angle = hdssAMAP(playerindex, x, y, RANDT(-9000/7, 9000/7));
	else
		angle = _eSendBigBulletAngle();
	end
	if speed < 0 then
		speed = _eSendBulletSpeed(rank, bSmall);
	elseif not bSmall then
		speed = speed + 0.3;
	end
	
	if bSmall then
		speed = _eSendBulletSpecialSpeed(speed)
	end
	
	speed = _eSendBulletSpeedRestrict(speed, rank);
	local type = CC_Bullet_MiddleBall;
	if bSmall then
		type = CC_Bullet_SmallBall;
	end
	local index = hdssB(playerindex, x, y, angle, speed, type, 6);
	if bSmall then
		game.AddSendBulletInfo(setID, sendtime+1, playerindex, index);
	end
	return true;
end

function eSendExBullet(playerindex, x, y, setID)
	local rank = hdss.Get(HDSS_RANK);
	local angle = 9000 + RANDT(-7500, 7500);
	local speed = 1.7 + rank * 0.1;
	speed = speed + 0.3;
	speed = _eSendBulletSpeedRestrict(speed, rank);
	hdssB(playerindex, x, y, angle, speed, CC_Bullet_MiddleBall, 5);
	return true;
end

function eSendItemBullet(playerindex, x, y, setID)
	local rank = hdss.Get(HDSS_RANK);
	local angle = _eSendBigBulletAngle();
	local speed = _eSendItemBulletSpeed(rank);
	speed = _eSendBulletSpeedRestrict(speed, rank);
	local type = CC_Bullet_MiddleBall;
	hdssB(playerindex, x, y, angle, speed, type, 3);
	return true;
end

function eSendGhost(playerindex, x, y, sendtime, acceladd, setID)
	local rank = hdss.Get(HDSS_RANK);
	
	local accel;
	acceladd = acceladd + RANDTF(0, 1/120);
	if sendtime == 0 then
		acceladd =  acceladd + rank / 600;
		accel = 0.025;
	elseif sendtime == 1 then
		accel = 0.03;
	else
		accel = 0.11 / 3;
	end
		
	local angle;
	--
	if RANDT(0, 4) == 0 then
		angle = hdssAMAP(playerindex, x, y, RANDT(-2250, 2250));
	else
		angle = RANDT(8910, 9090);
	end
	--
	local type = LConst_GhostTypeStart + sendtime * 2;
	local index = hdssEB(type, playerindex, x, y, angle, 0, type, 80);
	if index ~= nil then
		game.AddSendGhostInfo(setID, sendtime, playerindex, accel+acceladd, acceladd, index);
	end
	return true;
end

function eSendExAttack(playerindex, x, y, playerID, appendfloat, setID)
	return LTable_ePlayerSendExChaseFunction[playerID+1](playerindex, x, y, playerID, appendfloat);
end