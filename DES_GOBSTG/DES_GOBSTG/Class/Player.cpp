#include "../Header/Player.h"

#include "../Header/Process.h"
#include "../Header/BGLayer.h"
#include "../Header/SE.h"

#include "../Header/PlayerBullet.h"
#include "../Header/PlayerLaser.h"
#include "../Header/Item.h"
#include "../Header/Enemy.h"
#include "../Header/Bullet.h"
#include "../Header/Chat.h"
#include "../Header/BossInfo.h"
#include "../Header/EffectIDDefine.h"
#include "../Header/SpriteItemManager.h"
#include "../Header/FrontDisplayName.h"
#include "../Header/FrontDisplay.h"
#include "../Header/EventZone.h"
#include "../Header/BResource.h"
#include "../Header/Scripter.h"
#include "../Header/GameInput.h"
#include "../Header/Replay.h"
#include "../Header/DataConnector.h"

#include "../Header/GameAI.h"

#define _GAMERANK_MIN	0
#define _GAMERANK_MAX	5

Player Player::p;
BYTE Player::rank = _GAMERANK_MIN;
DWORD Player::alltime = 0;
BYTE Player::round = 0;


#define _PLAYER_SHOOTNOTPUSHOVER	9

#define _PL_MERGETOPOS_X	(M_GAMESQUARE_CENTER_X/2)
#define _PL_MERGETOPOS_Y		(PL_MOVABLE_BOTTOM - 32)

#define _PL_COMBOMINUS_NOR	((-PLAYER_COMBOGAGEMAX)/32)
#define _PL_COMBOMINUS_SEC	((-PLAYER_COMBOGAGEMAX)/64)

#define _PL_COMBORESET	(-PLAYER_COMBOGAGEMAX)
#define _PL_COMBOKEEP	200

/*
#define _PL_SCOREMUL_1_HIT	500
#define _PL_SCOREMUL_2_HIT	1000
#define _PL_SCOREMUL_3_HIT	3000
#define _PL_SCOREMUL_4_HIT	5000
#define _PL_SCOREMUL_5_HIT	7000
#define _PL_SCOREMUL_6_HIT	10000
*/

#define _PL_DEFAULTBOMBMAX	3
#define _PL_BOMBTIME		120
#define _PL_PASSIVEBOMBTIME	48

#define _SCOREMULMAX	10.0f

#define _PLWEAPON_NULL	0
#define _PLWEAPON_LASER	1
#define _PLWEAPON_SHOOT	2

Player::Player()
{
	effGraze.exist = false;
	effCollapse.exist = false;
	sprite			= NULL;
	ID			= 0;
}

Player::~Player()
{
	SpriteItemManager::FreeSprite(&sprite);
}

void Player::ClearSet(BYTE _round)
{
	x			=	PL_MERGEPOS_X;
	y			=	PL_MERGEPOS_Y;
	round	=	_round;

	for(int i=0;i<PL_SAVELASTMAX;i++)
	{
		lastx[i] = x;
		lasty[i] = y;
		lastmx[i] = x;
		lastmy[i] = y;
	}
	timer		=	0;
	angle		=	0;
	flag		=	PLAYER_MERGE;
	bSlow		=	false;
	bLaser		=	false;
	bInfi		=	true;
	hscale		=	1.0f;
	vscale		=	1.0f;
	alpha		=	0xff;
	diffuse		=	0xffffff;

	mergetimer			=	0;
	collapsetimer		=	0;
	shoottimer			=	0;
	bombtimer			=	0;
	slowtimer			=	0;
	fasttimer			=	0;
	costlifetimer		=	0;
	hypertimer			=	0;
	freezetimer			=	0;

	infitimer = 0;
	infireasonflag = 0;

	nBombMax = _PL_DEFAULTBOMBMAX;
	nBomb = nBombMax;
	bPassiveBomb = false;

	PlayerLaser::StopFire();

	shootpushtimer = 0;
	shootnotpushtimer = 0;
	lasertimer = 0;
	lastWeapon = _PLWEAPON_NULL;
	lastStableWeapon = _PLWEAPON_NULL;

	speedfactor		=	1.0f;

	nHitScore = 0;
	nLastHitScore = 0;

	// add
//	initlife	=	PLAYER_DEFAULTINITLIFE;

	exist = true;

	nComboHit = 0;
	nLastComboHit = 0;
	nComboHitMax = 0;
	nComboGage = 0;

	nScore = 0;
	nHiScore = DataConnector::nHiScore();
	AddScoreMul(-1);
	fLastScoreMul = 0;

	hitdisplaykeeptimer = 0;

	nTemper = 0;
	temperSelf = TEMPERSTATE_NULL;
	SetEnemyTemper(TEMPERSTATE_NULL);
	bhyper = false;
	bfreeze = false;

	if (effGraze.exist)
	{
		effGraze.Stop(true);
		effGraze.MoveTo(x, y, 0, true);
	}
	if (effCollapse.exist)
	{
		effCollapse.Stop(true);
		effCollapse.MoveTo(x, y, 0, true);
	}

	changePlayerID(ID, true);

	esShot.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERSHOT, SpriteItemManager::GetIndexByName(SI_PLAYER_SHOTITEM), x, y, 0, 1.2f);
	esShot.colorSet(0xccff0000);
	esShot.chaseSet(EFFSP_CHASE_PLAYER, 0, 0);

	esPoint.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERPOINT, SpriteItemManager::GetIndexByName(SI_PLAYER_POINT), x, y);
	esPoint.chaseSet(EFFSP_CHASE_PLAYER, 0, 0);

	esCollapse.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERCOLLAPSE, SpriteItemManager::GetIndexByName(SI_PLAYER_SHOTITEM), x, y);
	esCollapse.actionSet(0, 0, 160);
	esCollapse.colorSet(0x80ffffff);
}


void Player::valueSet(BYTE round)
{
	ID		= ID;
	ClearSet(round);
	initFrameIndex();
	UpdatePlayerData();

	nLife		=	initlife;

	if (round == 0)
	{
		Replay::lostStack	=	0;
		rank = _GAMERANK_MIN;
	}

	setFrame(PLAYER_FRAME_STAND);

	effGraze.valueSet(EFF_PL_GRAZE, *this);
	effGraze.Stop();
	effCollapse.valueSet(EFF_PL_COLLAPSE, *this);
	effCollapse.Stop();
	SetAble(true);
}

bool Player::Action()
{
	alltime++;
	Replay::AddLostStack();
	DWORD stopflag = Process::mp.GetStopFlag();
	bool binstop = FRAME_STOPFLAGCHECK_(stopflag, FRAME_STOPFLAG_PLAYER);
	bool binspellstop = FRAME_STOPFLAGCHECK_(stopflag, FRAME_STOPFLAG_PLAYERSPELL);
	GameInput::gameinput.updateActiveInput(binspellstop);
	if (p.exist)
	{
		if (!binstop && !binspellstop)
		{
			p.action();
		}
		else if (binspellstop)
		{
		}
		else
		{
			p.actionInStop();
		}

		if (!p.exist)
		{
			return false;
		}
	}
	return true;
}

void Player::action()
{
	
#if defined __IPHONE
#define _M_MOVINGMIN	1
	if (!GameAI::ai.able) {
		if (!(flag & PLAYER_SHOT)) {
			float tx = Process::mp.touchdirectmove.x;
			if (tx > _M_MOVINGMIN) {
				GameInput::SetKey(KSI_RIGHT, true);
			}
			else if (tx < -_M_MOVINGMIN){
				GameInput::SetKey(KSI_LEFT, true);
			}
			if (fabsf(tx) <= slowspeed) {
				GameInput::SetKey(KSI_SLOW, true);
			}
		}
	}
#endif
	
	float nowspeed = 0;
	timer++;

	alpha = 0xff;
	if(timer == 1)
		flag |= PLAYER_MERGE;

	//savelast
	if(lastmx[0] != x || lastmy[0] != y)
	{
		for(int i=PL_SAVELASTMAX-1;i>0;i--)
		{
			lastmx[i] = lastmx[i-1];
			lastmy[i] = lastmy[i-1];
		}
		lastmx[0] = x;
		lastmy[0] = y;
	}
	for(int i=PL_SAVELASTMAX-1;i>0;i--)
	{
		lastx[i] = lastx[i-1];
		lasty[i] = lasty[i-1];
	}
	lastx[0] = x;
	lasty[0] = y;

	//AI
	//	GameAI::ai.UpdateBasicInfo(x, y, speed, slowspeed, BResource::bres.playerdata[nowID].collision_r);
	GameAI::ai.SetMove();
	//
	
	if(flag & PLAYER_MERGE)
	{
		if(Merge())
		{
			flag &= ~PLAYER_MERGE;
		}
	}
	if(flag & PLAYER_SHOT)
	{
		if(Shot())
		{
			flag &= ~PLAYER_SHOT;
		}
	}
	if (flag & PLAYER_COSTLIFE)
	{
		if (CostLife())
		{
			flag &= ~PLAYER_COSTLIFE;
		}
	}
	if(flag & PLAYER_COLLAPSE)
	{
		if(Collapse())
		{
			flag &= ~PLAYER_COLLAPSE;
			if (!nLife)
			{
				exist = false;
			}
			return;
		}
	}
	if(flag & PLAYER_SLOWCHANGE)
	{
		if(SlowChange())
		{
			flag &= ~PLAYER_SLOWCHANGE;
		}
	}
	if(flag & PLAYER_FASTCHANGE)
	{
		if(FastChange())
		{
			flag &= ~PLAYER_FASTCHANGE;
		}
	}
	if(flag & PLAYER_SHOOT)
	{
		if(Shoot())
		{
			flag &= ~PLAYER_SHOOT;
		}
	}
	if (flag & PLAYER_LASER)
	{
		if (Laser())
		{
			flag &= ~PLAYER_LASER;
			PlayerLaser::StopFire();
		}
	}
	if (flag & PLAYER_HYPER)
	{
		if (Hyper())
		{
			flag &= ~PLAYER_HYPER;
		}
	}
	if (flag & PLAYER_FREEZE)
	{
		if (Freeze())
		{
			flag &= ~PLAYER_FREEZE;
		}
	}
	if(flag & PLAYER_BOMB)
	{
		if(Bomb())
		{
			flag &= ~PLAYER_BOMB;
		}
	}
	if(flag & PLAYER_GRAZE)
	{
		if(Graze())
		{
			flag &= ~PLAYER_GRAZE;
		}
	}

	if (infitimer > 0)
	{
		infitimer--;
		bInfi = true;
	}
	else if (infitimer == PLAYER_INFIMAX)
	{
		bInfi = true;
	}
	else
	{
		bInfi = false;
	}
	/*
	if (nComboGage > 0)
	{
		nComboGage -= _PL_COMBOMINUS_NOR;
		if (nComboGage <= _PL_COMBORESET)
		{
			AddComboGage(-1);
		}
	}
	*/

	bool weaponchanged = false;
	if (flag & PLAYER_LASER && !(lastWeapon == _PLWEAPON_LASER))
	{
		lastWeapon = _PLWEAPON_LASER;
		weaponchanged = true;
	}
	else if (flag & PLAYER_SHOOT && !(lastWeapon == _PLWEAPON_SHOOT))
	{
		lastWeapon = _PLWEAPON_SHOOT;
		weaponchanged = true;
	}
	if (temperSelf == TEMPERSTATE_NULL && temperEnemy == TEMPERSTATE_NULL)
	{
		if (flag & PLAYER_LASER)
		{
			lastStableWeapon = _PLWEAPON_LASER;
		}
		else if (flag & PLAYER_SHOOT)
		{
			lastStableWeapon = _PLWEAPON_SHOOT;
		}
	}
	if (temperEnemy != temperSelf && !bhyper && !bfreeze)
	{
		if (temperSelf == TEMPERSTATE_COLD && ((flag & PLAYER_LASER) || (flag & PLAYER_BOMB) || (flag & PLAYER_COLLAPSE)))
		{
			SetEnemyTemper(TEMPERSTATE_COLD);
			lastStableWeapon = _PLWEAPON_LASER;
		}
		else if (temperSelf == TEMPERSTATE_HOT && ((flag & PLAYER_SHOOT) || (flag & PLAYER_BOMB) || (flag & PLAYER_COLLAPSE)))
		{
			SetEnemyTemper(TEMPERSTATE_HOT);
			lastStableWeapon = _PLWEAPON_SHOOT;
		}
		else
		{
			bool stableweaponchanged = false;
			if (flag & PLAYER_LASER && !(lastStableWeapon == _PLWEAPON_LASER))
			{
				stableweaponchanged = true;
			}
			else if (flag & PLAYER_SHOOT && !(lastStableWeapon == _PLWEAPON_SHOOT))
			{
				stableweaponchanged = true;
			}
			if (stableweaponchanged || (flag & PLAYER_BOMB) || (flag & PLAYER_COLLAPSE))
			{
				AddComboGage(_PL_COMBOMINUS_NOR);
				if (!nComboGage)
				{
					SetEnemyTemper(TEMPERSTATE_NULL);
				}
			}
		}
	}

	if (hitdisplaykeeptimer)
	{
		hitdisplaykeeptimer--;
		if (hitdisplaykeeptimer == 0)
		{
			nLastComboHit = nComboHit;
			fLastScoreMul = fScoreMul;
			nLastHitScore = nHitScore;
		}
	}

	for (list<EventZone>::iterator it=EventZone::ezone.begin(); it!=EventZone::ezone.end(); it++)
	{
		if (it->timer < 0)
		{
			continue;
		}
		if ((it->type) & EVENTZONE_TYPEMASK_PLAYER)
		{
			if (it->isInRect(x, y, r))
			{
				if (it->type & EVENTZONE_TYPE_PLAYERDAMAGE)
				{
					DoShot();
				}
				if (it->type & EVENTZONE_TYPE_PLAYEREVENT)
				{
				}
				if (it->type & EVENTZONE_TYPE_PLAYERSPEED)
				{
					speedfactor = it->power;
				}
			}
		}
	}

	//input
	if(!(flag & PLAYER_SHOT || flag & PLAYER_COLLAPSE))
	{
		if (GameInput::GetKey(KSI_SLOW))
		{
			bSlow = true;
			flag &= ~PLAYER_FASTCHANGE;
			if (GameInput::GetKey(KSI_SLOW, DIKEY_DOWN))
			{
				if (!(flag & PLAYER_SLOWCHANGE))
				{
					slowtimer = 0;
					flag |= PLAYER_SLOWCHANGE;
				}
			}
		}
		else
		{
			bSlow = false;
			flag &= ~PLAYER_SLOWCHANGE;
			if (GameInput::GetKey(KSI_SLOW, DIKEY_UP))
			{
				if (!(flag & PLAYER_FASTCHANGE))
				{
					fasttimer = 0;
					flag |= PLAYER_FASTCHANGE;
				}
			}
		}
		if(bSlow)
		{
			nowspeed = slowspeed;
		}
		else
		{
			nowspeed = speed;
		}
		nowspeed *= speedfactor;

		if(GameInput::GetKey(KSI_FIRE))
		{
			if (!Chat::chatitem.IsChatting())
			{
				flag |= PLAYER_SHOOT;
			}
			shootnotpushtimer = 0;
		}
		else
		{
			if (shootnotpushtimer < 0xff)
			{
				shootnotpushtimer++;
			}
		}
		/*
		if (shootpushtimer < PLAYER_SHOOTPUSHOVER)
		{
			if (GameInput::GetKey(KSI_FIRE))
			{
				shootpushtimer++;
			}
			else
			{
				shootpushtimer = 0;
				bLaser = false;
			}
		}
		else
		{
			if (!GameInput::GetKey(KSI_FIRE))
			{
				shootpushtimer = 0;
				bLaser = false;
			}
			else
			{
				flag &= ~PLAYER_SHOOT;
				bLaser = true;
				if (!(flag & PLAYER_LASER))
				{
					lasertimer = 0;
					flag |= PLAYER_LASER;
					shootpushtimer = 0xff;
				}
			}
		}
		*/
		if (GameInput::GetKey(KSI_SLOW))
		{
			flag &= ~PLAYER_SHOOT;
			bLaser = true;
			if (!(flag & PLAYER_LASER))
			{
				lasertimer = 0;
				flag |= PLAYER_LASER;
			}
		}

#if defined __IPHONE
		if (!GameAI::ai.able) {
			if (Process::mp.touchMoveID != 0xff && !(flag & PLAYER_COLLAPSE)) {
				x += Process::mp.touchdirectmove.x * speedfactor;
				y += Process::mp.touchdirectmove.y * speedfactor;
			}
		}
		else {
#endif
		if((GameInput::GetKey(KSI_UP) ^ GameInput::GetKey(KSI_DOWN)) &&
			GameInput::GetKey(KSI_LEFT) ^ GameInput::GetKey(KSI_RIGHT))
			nowspeed *= M_SQUARE_2;
		if(GameInput::GetKey(KSI_UP))
			y -= nowspeed;
		if(GameInput::GetKey(KSI_DOWN))
			y += nowspeed;
		if(GameInput::GetKey(KSI_LEFT))
		{
			x -= nowspeed;
		}
		if(GameInput::GetKey(KSI_RIGHT))
		{
			x += nowspeed;
		}
#if defined __IPHONE
		}
#endif

		if(GameInput::GetKey(KSI_LEFT))
		{
			updateFrame(PLAYER_FRAME_LEFTPRE);
		}
		if(GameInput::GetKey(KSI_RIGHT))
		{
			if (!GameInput::GetKey(KSI_LEFT))
			{
				updateFrame(PLAYER_FRAME_RIGHTPRE);
			}
			else
			{
				updateFrame(PLAYER_FRAME_STAND);
			}
		}
		if (!GameInput::GetKey(KSI_LEFT) && !GameInput::GetKey(KSI_RIGHT))
		{
			updateFrame(PLAYER_FRAME_STAND);
		}
	}
	if(GameInput::GetKey(KSI_QUICK) && !(flag & PLAYER_MERGE))
	{
		callBomb();
	}

	if (!(flag & PLAYER_MERGE) || mergetimer >= 32)
	{
		if(x > PL_MOVABLE_RIGHT)
			x = PL_MOVABLE_RIGHT;
		else if(x < PL_MOVABLE_LEFT)
			x = PL_MOVABLE_LEFT;
		if(y > PL_MOVABLE_BOTTOM)
			y = PL_MOVABLE_BOTTOM;
		else if(y < PL_MOVABLE_TOP)
			y = PL_MOVABLE_TOP;
	}
	//AI
	GameAI::ai.UpdateBasicInfo(x, y, speed*speedfactor, slowspeed*speedfactor, r, BResource::bres.playerdata[ID].aidraintime);
	float aiaimx = _PL_MERGETOPOS_X;
	float aiaimy = _PL_MERGETOPOS_Y;
	bool tobelow = false;
	if (PlayerBullet::locked != PBLOCK_LOST)
	{
		aiaimx = Enemy::en[PlayerBullet::locked].x;
		aiaimy = Enemy::en[PlayerBullet::locked].y;
	}
	GameAI::ai.SetAim(aiaimx, aiaimy, tobelow);
	//
	//
	speedfactor = 1.0f;

	if (bInfi && timer % 8 < 4)
	{
		diffuse = 0xff99ff;
	}
	else
		diffuse = 0xffffff;

	esShot.action();
	esPoint.action();
	
	effGraze.MoveTo(x, y);
	effGraze.action();
	effCollapse.action();

	if(!(flag & PLAYER_GRAZE))
		effGraze.Stop();

	for(int i=0;i<DATASTRUCT_PLAYERSUBMAX;i++)
	{
		if (pg[i].exist)
		{
			pg[i].action();
		}
	}
}

void Player::actionInStop()
{
//	Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERINSTOP);
}

bool Player::Merge()
{
	mergetimer++;
	if(mergetimer == 1)
	{
		SetInfi(PLAYERINFI_MERGE, 60);
		if(GameInput::GetKey(KSI_SLOW))
		{
			flag |= PLAYER_SLOWCHANGE;
			slowtimer = 0;
			flag &= ~PLAYER_FASTCHANGE;
		}
		else
		{
			flag |= PLAYER_FASTCHANGE;
			fasttimer = 0;
			flag &= ~PLAYER_SLOWCHANGE;
		}
	}
	else if (mergetimer < 24)
	{
		float interval = mergetimer / 24.0f;
		x = INTER(PL_MERGEPOS_X, _PL_MERGETOPOS_X, interval);
		y = INTER(PL_MERGEPOS_Y, _PL_MERGETOPOS_Y, interval);
		flag &= ~PLAYER_SHOOT;
		alpha = INTER(0, 0xff, interval);
	}
	else if(mergetimer == 24)
	{
		alpha = 0xff;
		mergetimer = 0;
		return true;
	}
	return false;
}

bool Player::Shot()
{
	if(bInfi)
	{
		return true;
	}
	
//	Item::undrainAll();
	SE::push(SE_PLAYER_SHOT, x);
	if (flag & PLAYER_HYPER)
	{
		bhyper = false;
		hypertimer = 0;
		flag &= ~PLAYER_HYPER;
	}
	if (nBomb)
	{
		callBomb(true);
	}
	else
	{
		flag |= PLAYER_COLLAPSE;
	}
	return true;
}

bool Player::CostLife()
{
	costlifetimer++;
	if (costlifetimer == 1)
	{
		SetInfi(PLAYERINFI_COSTLIFE, 120);
	}
	else if (costlifetimer == 50)
	{
		EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_ENEMYDAMAGE|EVENTZONE_TYPE_NOSCORE|EVENTZONE_CHECKTYPE_CIRCLE, x, y, 10, 0, 0, 10, EVENTZONE_EVENT_NULL, 15.6);
	}
	else if (costlifetimer == 60)
	{
		costlifetimer = 0;
		return true;
	}
	return false;
}

bool Player::Collapse()
{
	collapsetimer++;
	if(collapsetimer == 1)
	{
		p.SetInfi(PLAYERINFI_COLLAPSE, 64);

		esCollapse.x = x;
		esCollapse.y = y;
		SE::push(SE_PLAYER_DEAD, x);

		effCollapse.MoveTo(x, y , 0, true);
		effCollapse.Fire();

		AddComboHit(-1);
		AddComboGage(_PL_COMBORESET);
		AddHitScore(-1);
		if (nLife == 1)
		{
			nLife = 0;
			// Todo:
//			flag |= PLAYER_COLLAPSE;
			collapsetimer = 0;
			EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_NOSCORE|EVENTZONE_CHECKTYPE_CIRCLE, p.x, p.y);
			return true;
		}
		EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_ENEMYDAMAGE|EVENTZONE_TYPE_NOSCORE|EVENTZONE_CHECKTYPE_CIRCLE, p.x, p.y, 64, EVENTZONE_OVERZONE, 0, 1000, EVENTZONE_EVENT_NULL, 16);
		nLife--;
		if (nBombMax < PLAYER_BOMBMAX)
		{
			nBombMax++;
		}
		nBomb = nBombMax;
	}
	else if(collapsetimer == 64)
	{
		x = PL_MERGEPOS_X;
		y = PL_MERGEPOS_Y;
		for(int i=0;i<PL_SAVELASTMAX;i++)
		{
			lastx[i] = x;
			lasty[i] = y;
			lastmx[i] = x;
			lastmy[i] = y;
		}

		timer = 0;
		collapsetimer = 0;
		vscale = 1.0f;
		flag |= PLAYER_MERGE;

//		SetInfi(PLAYERINFI_COLLAPSE);
//		exist = false;

		if(GameInput::GetKey(KSI_SLOW))
		{
			flag |= PLAYER_SLOWCHANGE;
			slowtimer = 0;
			flag &= ~PLAYER_FASTCHANGE;
		}
		else
		{
			flag |= PLAYER_FASTCHANGE;
			fasttimer = 0;
			flag &= ~PLAYER_SLOWCHANGE;
		}

		effCollapse.Stop();

		return true;
	}
	
	esCollapse.hscale = collapsetimer / 1.5f;
	esCollapse.alpha = (BYTE)((WORD)(0xff * collapsetimer) / 0x3f);
	esCollapse.colorSet(0xff0000);

	alpha = (0xff - collapsetimer * 4);
	vscale = (float)(collapsetimer)/40.0f + 1.0f;
	return false;
}

bool Player::Shoot()
{
	if(Chat::chatitem.IsChatting())
	{
		shoottimer = 0;
		return true;
	}

	if (!(flag & PLAYER_SHOT) && !(flag & PLAYER_COLLAPSE))
	{
		PlayerBullet::BuildShoot(ID, shoottimer, bhyper);
		AddScore(nComboHit);
	}
	shoottimer++;
	//
	if(shootnotpushtimer > _PLAYER_SHOOTNOTPUSHOVER)
	{
		shoottimer = 0;
		return true;
	}
	return false;
}

bool Player::Laser()
{
	if (Chat::chatitem.IsChatting())
	{
		lasertimer = 0;
		return true;
	}

	if (!(flag & PLAYER_SHOT) && !(flag & PLAYER_COLLAPSE))
	{
		lasertimer++;
		AddScore(nComboHit);
		if (lasertimer == 1)
		{
			PlayerLaser::Shoot();
		}
	}

	if (!GameInput::GetKey(KSI_SLOW))
	{
		lasertimer = 0;
		PlayerLaser::StopFire();
		return true;
	}

	return false;
}


bool Player::Hyper()
{
	hypertimer++;
	bhyper = true;
	if (hypertimer == 1)
	{
		rank++;
		if (rank > _GAMERANK_MAX)
		{
			rank = _GAMERANK_MAX;
		}
		SetInfi(PLAYERINFI_HYPER, PLAYER_HYPERINFITIMEMAX);
	}
	else if (hypertimer == PLAYER_HYPERTIMEMAX)
	{
		bhyper = false;
		hypertimer = 0;
		if (flag & PLAYER_LASER)
		{
			lasertimer = 0;
		}
		SetInfi(PLAYERINFI_HYPER, PLAYER_HYPERINFITIMEMAX);
		EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_CHECKTYPE_CIRCLE, x, y, 16);
		return true;
	}
	return false;
}

bool Player::Freeze()
{
	freezetimer++;
	bfreeze = true;
	if (freezetimer == 1)
	{
		rank++;
		if (rank > _GAMERANK_MAX)
		{
			rank = _GAMERANK_MAX;
		}
		SetInfi(PLAYERINFI_FREEZE, PLAYER_FREEZETIMEMAX);
		float rspeed = 8.0f;
		if (rank == _GAMERANK_MAX)
		{
			rspeed = 1.0f;
		}
		EventZone::Build(EVENTZONE_TYPE_BULLETFREEZE|EVENTZONE_CHECKTYPE_CIRCLE, x, y, PLAYER_FREEZETIMEMAX, 0, 0, 0, EVENTZONE_TYPE_BULLETFREEZE, rspeed);
	}
	else if (freezetimer == PLAYER_FREEZETIMEMAX)
	{
		bfreeze = false;
		freezetimer = 0;
		return true;
	}
	return false;
}

bool Player::Bomb()
{
	if (!(flag & PLAYER_BOMB))
	{
		flag |= PLAYER_BOMB;
	}

	bombtimer++;
	BYTE bombmaxtime = bPassiveBomb?_PL_PASSIVEBOMBTIME:_PL_BOMBTIME;
	if (bombtimer == 1)
	{
		if (!nBomb || bInfi)
		{
			bombtimer = 0;
			return true;
		}
		nBomb--;
		EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_ENEMYDAMAGE|EVENTZONE_TYPE_NOSCORE|EVENTZONE_CHECKTYPE_CIRCLE, p.x, p.y, bombmaxtime, EVENTZONE_OVERZONE, 0, 1000, EVENTZONE_EVENT_NULL, 16);
		SetInfi(PLAYERINFI_BOMB, bombmaxtime);
	}
	else if (bombtimer == bombmaxtime)
	{
		bombtimer = 0;
		return true;
	}

	return false;
}

bool Player::SlowChange()
{
	if(GameInput::GetKey(KSI_SLOW, DIKEY_DOWN))
		slowtimer = 0;
	bSlow = true;
	slowtimer++;
	if(slowtimer == 1)
	{
		ResetPlayerGhost();
		SE::push(SE_PLAYER_SLOWON, x);
		for(int i=0;i<DATASTRUCT_PLAYERSUBMAX;i++)
		{
			pg[i].timer = 0;
		}
	}
	else if(slowtimer == 16)
	{
		esPoint.colorSet(0xffffffff);
		slowtimer = 0;
		return true;
	}

	esPoint.actionSet(0, 0, (24 - slowtimer) * 25);
	esPoint.colorSet(((slowtimer*16)<<24)+0xffffff);
	return false;
}

bool Player::FastChange()
{
	if(GameInput::GetKey(KSI_SLOW, DIKEY_UP))
		fasttimer = 0;
	bSlow = false;
	fasttimer++;
	if(fasttimer == 1)
	{
		ResetPlayerGhost();
		SE::push(SE_PLAYER_SLOWOFF, x);
		for(int i=0;i<DATASTRUCT_PLAYERSUBMAX;i++)
		{
			pg[i].timer = 0;
		}
	}
	else if(fasttimer == 16)
	{
		esPoint.colorSet(0x00ffffff);
		fasttimer = 0;
		return true;
	}
	esPoint.colorSet(((0xff-fasttimer*16)<<24)+0xffffff);
	return false;
}

void Player::changePlayerID(WORD toID, bool moveghost/* =false */)
{
	ID = toID;
	ResetPlayerGhost(moveghost);
	UpdatePlayerData();
}

bool Player::Graze()
{
	effGraze.Fire();
	SE::push(SE_PLAYER_GRAZE, x);
	return true;
}

void Player::DoEnemyCollapse(float x, float y, BYTE type)
{
	enemyData * edata = &(BResource::bres.enemydata[type]);

	LONGLONG addscore = edata->score;
	AddHitScore(addscore);
	AddScore(addscore);
	AddComboHit(1);
}

void Player::DoGraze(float x, float y)
{
	if(!(flag & (PLAYER_MERGE | PLAYER_SHOT | PLAYER_COLLAPSE)))
	{
		flag |= PLAYER_GRAZE;
	}
}

void Player::DoPlayerBulletKill(BYTE type)
{
	enemyData * edata = &(BResource::bres.enemydata[type]);
	int addcombogage = edata->combogage;//*_PL_COMBOGAGE_BULLETKILLMUL;
	AddComboGage(addcombogage);
	int addtemper = edata->killtemperpoint;
	AddTemper(-addtemper);
}

void Player::DoPlayerLaserHit(BYTE type, bool hitprotect)
{
	int addtemper = BResource::bres.enemydata[type].laserhittemperpoint;
	if (hitprotect)
	{
		addtemper = BResource::bres.enemydata[type].protecthittemperpoint;
	}
	AddTemper(addtemper);
	KeepComboGage();
}

void Player::DoPlayerLaserKill(BYTE type)
{
	enemyData * edata = &(BResource::bres.enemydata[type]);
	int addcombogage = edata->combogage;
	AddComboGage(addcombogage);
	int addtemper = edata->killtemperpoint;
	AddTemper(addtemper);
}

void Player::DoShot()
{
	if (!bInfi && !(flag & (PLAYER_SHOT | PLAYER_COLLAPSE)))
	{
		flag |= PLAYER_SHOT;
		AddComboGage(_PL_COMBORESET);
	}
}

void Player::DoBulletDead(float x, float y, bool frozen)
{
	if (frozen)
	{
		AddComboHit(1);
	}
	float addmul = 0;
	switch (rank)
	{
	case 0:
		addmul = 0.05f;
		break;
	case 1:
		addmul = 0.006f;
		break;
	case 2:
		addmul = 0.007f;
		break;
	case 3:
		addmul = 0.008f;
		break;
	case 4:
	case 5:
		addmul = 0.01f;
		break;
	}
	AddScoreMul(addmul);
}

void Player::DoItemGet(WORD itemtype, float _x, float _y)
{
	switch (itemtype)
	{
	case ITEM_GAUGE:
		break;
	case ITEM_BULLET:
		break;
	case ITEM_EX:
		break;
	case ITEM_POINT:
		break;
	}
}

void Player::ResetPlayerGhost(bool move /* = false */)
{
	int tid = ID;
	tid *= DATASTRUCT_PLAYERSUBMAX * 2;
	if (bSlow)
	{
		tid += DATASTRUCT_PLAYERSUBMAX;
	}
	for (int i=0; i<DATASTRUCT_PLAYERSUBMAX; i++)
	{
		pg[i].valueSet(tid+i, move);
	}
}

void Player::Render()
{
	if (sprite)
	{
		DWORD usediffuse = diffuse;
		/*
		if (usediffuse == 0xffffff)
		{
			BYTE r=0;
			BYTE g=0xff;
			BYTE b=0;
			int keytemper = 0xff*nTemper/PLAYER_TEMPERMAX;
			if (nTemper > PLAYER_TEMPERHOTEDGE || nTemper < PLAYER_TEMPERCOLDEDGE)
			{
				g = 0x80;
			}
			if (keytemper < 0)
			{
				b = -keytemper;
			}
			else
			{
				r = keytemper;
			}
			usediffuse = ARGB(0, r, g, b);
		}
		*/
		sprite->SetColor(alpha<<24|usediffuse);
		SpriteItemManager::RenderSpriteEx(sprite, x, y, 0, hscale, vscale);
	}
}

void Player::RenderEffect()
{
	effGraze.Render();

	for(int i=0;i<DATASTRUCT_PLAYERSUBMAX;i++)
	{
		if (pg[i].exist)
		{
			pg[i].Render();
		}
	}
	if(flag & PLAYER_SHOT)
		esShot.Render();
	if(bSlow || flag & PLAYER_FASTCHANGE)
	{
		esPoint.Render();
		esPoint.headangle = -esPoint.headangle;
		esPoint.Render();
		esPoint.headangle = -esPoint.headangle;
	}
	if(flag & PLAYER_COLLAPSE)
		esCollapse.Render();

	effCollapse.Render();
}

void Player::callHyper()
{
	if (flag & PLAYER_HYPER || flag & PLAYER_FREEZE)
	{
		return;
	}
	flag |= PLAYER_HYPER;
	hypertimer = 0;
}

void Player::callFreeze()
{
	if (flag & PLAYER_HYPER || flag & PLAYER_FREEZE)
	{
		return;
	}
	flag |= PLAYER_FREEZE;
	freezetimer = 0;
}

void Player::callCollapse()
{
	if (flag & PLAYER_COLLAPSE)
	{
		return;
	}
	flag |= PLAYER_COLLAPSE;
	collapsetimer = 0;
}

bool Player::callBomb(bool bpassive)
{
	if (Chat::chatitem.IsChatting() || (flag & PLAYER_COLLAPSE))
	{
		return false;
	}
	bPassiveBomb = bpassive;
	return Bomb();
}

void Player::callSlowFastChange(bool toslow)
{
	if (toslow)
	{
		GameInput::SetKey(KSI_SLOW);
	}
	else
	{
		GameInput::SetKey(KSI_SLOW, false);
	}
}

void Player::SetEnemyTemper(BYTE temperstate)
{
	if (temperEnemy == TEMPERSTATE_HOT && temperstate == TEMPERSTATE_COLD)
	{
		if (nTemper == -PLAYER_TEMPERMAX)
		{
			callFreeze();
		}
	}
	else if (temperEnemy == TEMPERSTATE_COLD && temperstate == TEMPERSTATE_HOT)
	{
		if (nTemper == PLAYER_TEMPERMAX)
		{
			callHyper();
		}
	}
	temperEnemy = temperstate;
	if (temperEnemy == TEMPERSTATE_NULL)
	{
		AddComboGage(_PL_COMBORESET);
		AddComboHit(-1);
		AddHitScore(-1);
	}
}

float Player::GetHyperCostLife(float hyperpower)
{
	float rate = 1;
	switch (rank)
	{
	case 1:
		rate = 0.85f;
		break;
	case 2:
		rate = 0.6f;
		break;
	case 3:
		rate = 0.5f;
		break;
	case 4:
		rate = 0.4f;
		break;
	case 5:
		rate = 0.3f;
		break;
	}
	return hyperpower*rate;
}

void Player::AddScore(LONGLONG addscore)
{
	nScore += addscore;
	if (nScore > nHiScore)
	{
		nHiScore = nScore;
	}
}

void Player::AddScoreMul(float scoremul)
{
	if (scoremul < 0)
	{
		fScoreMul = 1.0f;
		return;
	}
	fScoreMul += scoremul;
	if (fScoreMul >= _SCOREMULMAX)
	{
		fScoreMul = _SCOREMULMAX;
	}
	if (!hitdisplaykeeptimer)
	{
		fLastScoreMul = fScoreMul;
	}
}

void Player::AddHitScore(LONGLONG addscore)
{
	if (addscore < 0)
	{
		nHitScore = 0;
		return;
	}
	if (flag & PLAYER_COLLAPSE || flag & PLAYER_COLLAPSE || flag & PLAYER_SHOT || flag & PLAYER_BOMB)
	{
		return;
	}
	nHitScore += addscore * ((bhyper||bfreeze)?1:fScoreMul);
	if (!hitdisplaykeeptimer)
	{
		nLastHitScore = nHitScore;
	}
}

void Player::AddComboGage(int gage)
{
	if (flag & PLAYER_COLLAPSE || flag & PLAYER_COLLAPSE || flag & PLAYER_SHOT || flag & PLAYER_BOMB)
	{
		gage = _PL_COMBORESET;
	}

	if (gage <= _PL_COMBORESET)
	{
		nComboGage = 0;
		AddComboHit(-1);
	}
	else
	{
		nComboGage += gage;
		if (nComboGage > PLAYER_COMBOGAGEMAX)
		{
			nComboGage = PLAYER_COMBOGAGEMAX;
		}
		else if (nComboGage < 0)
		{
			nComboGage = 0;
		}
	}
}

void Player::KeepComboGage()
{
	if (flag & PLAYER_COLLAPSE || flag & PLAYER_COSTLIFE || flag & PLAYER_SHOT || flag & PLAYER_BOMB)
	{
		AddComboHit(_PL_COMBORESET);
		return;
	}

	if (nComboGage < _PL_COMBOKEEP)
	{
		nComboGage = _PL_COMBOKEEP;
	}
}

void Player::AddComboHit(int combo)
{
	if (flag & PLAYER_COLLAPSE || flag & PLAYER_COSTLIFE || flag & PLAYER_SHOT || flag & PLAYER_BOMB)
	{
		combo = -1;
	}

	if (combo < 0)
	{
		nComboHit = 0;
		AddScoreMul(-1);
		AddHitScore(-1);
		if (!hitdisplaykeeptimer)
		{
			hitdisplaykeeptimer = PLAYER_HITDISPLAYTIMEMAX;
		}
		return;
	}


	nComboHit += combo;
	/*
	if (nComboHit < _PL_SCOREMUL_1_HIT)
	{
		fScoreMul = 1;
	}
	else if (nComboHit < _PL_SCOREMUL_2_HIT)
	{
		fScoreMul = 2;
	}
	else if (nComboHit < _PL_SCOREMUL_3_HIT)
	{
		fScoreMul = 3;
	}
	else if (nComboHit < _PL_SCOREMUL_4_HIT)
	{
		fScoreMul = 4;
	}
	else if (nComboHit < _PL_SCOREMUL_5_HIT)
	{
		fScoreMul = 5;
	}
	else if (nComboHit < _PL_SCOREMUL_6_HIT)
	{
		fScoreMul = 6;
	}
	else
	{
		fScoreMul = 7;
	}
	*/

	if (!hitdisplaykeeptimer)
	{
		nLastComboHit = nComboHit;
	}
	AddScore(nHitScore);
	if (nComboHit > nComboHitMax)
	{
		nComboHitMax = nComboHit;
	}
}

void Player::AddTemper(int temper)
{
	nTemper += temper;
	if (nTemper > PLAYER_TEMPERMAX)
	{
		nTemper = PLAYER_TEMPERMAX;
	}
	else if (nTemper < -PLAYER_TEMPERMAX)
	{
		nTemper = -PLAYER_TEMPERMAX;
	}

	if (nTemper >= PLAYER_TEMPERHOTEDGE)
	{
		temperSelf = TEMPERSTATE_HOT;
	}
	else if (nTemper <= PLAYER_TEMPERCOLDEDGE)
	{
		temperSelf = TEMPERSTATE_COLD;
	}
	else
	{
		temperSelf = TEMPERSTATE_NULL;
	}
}
