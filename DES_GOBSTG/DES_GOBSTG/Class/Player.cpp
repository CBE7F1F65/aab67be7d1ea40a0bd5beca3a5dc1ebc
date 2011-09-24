#include "../header/Player.h"

#include "../header/Process.h"
#include "../header/BGLayer.h"
#include "../header/SE.h"

#include "../header/PlayerBullet.h"
#include "../header/Item.h"
#include "../header/Enemy.h"
#include "../header/Bullet.h"
#include "../header/Chat.h"
#include "../header/BossInfo.h"
#include "../header/EffectIDDefine.h"
#include "../header/SpriteItemManager.h"
#include "../header/FrontDisplayName.h"
#include "../header/FrontDisplay.h"
#include "../header/EventZone.h"
#include "../header/BResource.h"
#include "../header/Scripter.h"
#include "../header/GameInput.h"

#include "../header/GameAI.h"

#define _GAMERANK_MIN	8
#define _GAMERANK_MAX	22
#define _GAMERANK_ADDINTERVAL	9000
#define _GAMERANK_STAGEOVERADD	-8

#define _PL_SHOOTCHARGEINFI_1	8
#define _PL_SHOOTCHARGEINFI_2	47
#define _PL_SHOOTCHARGEINFI_3	63
#define _PL_SHOOTCHARGEINFI_4	127

#define _PLAYER_DEFAULETCARDLEVEL_(X)	(X?9:8)
#define _PLAYER_DEFAULETBOSSLEVEL_(X)	(X?9:8)
#define _CARDLEVEL_ADDINTERVAL	3600
#define _BOSSLEVEL_ADDINTERVAL	3600
#define _CARDLEVEL_MAX	16
#define _BOSSLEVEL_MAX	16

#define _PLAYER_LIFECOSTMAX	2880
#define _PLAYER_COMBOHITMAX	999

#define _PLAYER_SHOOTNOTPUSHOVER	9

#define _PL_SPELLBONUS_BOSS_1	100000
#define _PL_SPELLBONUS_BOSS_2	300000
#define _PL_SPELLBONUS_BOSS_3	500000

Player Player::p[M_PL_MATCHMAXPLAYER];
float Player::lostStack = 0;
bool Player::able = false;

BYTE Player::rank = _GAMERANK_MIN;
int Player::lilycount = 0;

DWORD Player::alltime = 0;

BYTE Player::raisespellstopplayerindex = 0;

BYTE Player::round = 0;

#define _PL_MERGETOPOS_X_(X)	(M_GAMESQUARE_CENTER_X_(X))
#define _PL_MERGETOPOS_Y		(M_GAMESQUARE_BOTTOM - 64)

#define _PL_SHOOTINGCHARGE_1	0x01
#define _PL_SHOOTINGCHARGE_2	0x02
#define _PL_SHOOTINGCHARGE_3	0x04
#define _PL_SHOOTINGCHARGE_4	0x08

#define _PL_CHARGEZONE_R_2	188.0f
#define _PL_CHARGEZONE_R_3	252.0f
#define _PL_CHARGEZONE_R_4	444.5f

#define _PL_CHARGEZONE_MAXTIME_2	49
#define _PL_CHARGEZONE_MAXTIME_3	65
#define _PL_CHARGEZONE_MAXTIME_4	129

Player::Player()
{
	effGraze.exist = false;
	effChange.exist = false;
	effInfi.exist = false;
	effCollapse.exist = false;
	effMerge.exist = false;
	effBorder.exist = false;
	effBorderOn.exist = false;
	effBorderOff.exist = false;
	sprite			= NULL;
	spdrain			= NULL;
	nowID			= 0;
	ID_sub_1		= 0;
	ID_sub_2		= 0;
}

Player::~Player()
{
	SpriteItemManager::FreeSprite(&sprite);
	SpriteItemManager::FreeSprite(&spdrain);
}

void Player::ClearSet(BYTE _round)
{
	x			=	PL_MERGEPOS_X_(playerindex);
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
	bCharge		=	false;
	bDrain		=	false;
	bInfi		=	true;
	hscale		=	1.0f;
	vscale		=	1.0f;
	alpha		=	0xff;
	diffuse		=	0xffffff;

	mergetimer			=	0;
	shottimer			=	0;
	collapsetimer		=	0;
	shoottimer			=	0;
	draintimer			=	0;
	chargetimer			=	0;
	slowtimer			=	0;
	fasttimer			=	0;
	playerchangetimer	=	0;
	costlifetimer		=	0;
	shootchargetimer	=	0;

	shootingchargeflag	=	0;
	nowshootingcharge	=	0;

	fExPoint = 0;
	nGhostPoint = 0;
	nBulletPoint = 0;
	nSpellPoint	= 0;

	nLifeCost	=	0;
	fCharge = 0;
	if (_round == 0)
	{
		fChargeMax = PLAYER_CHARGEONE;
		winflag = 0;
	}

	cardlevel = _PLAYER_DEFAULETCARDLEVEL_(_round);
	bosslevel = _PLAYER_DEFAULETBOSSLEVEL_(_round);
	nowcardlevel = cardlevel;
	nowbosslevel = bosslevel;
	infitimer = 0;
	rechargedelaytimer = 0;
	infireasonflag = 0;

	shootpushtimer = 0;
	shootnotpushtimer = 0;

	spellstoptimer = 0;

	speedfactor		=	1.0f;

	// add
//	initlife	=	PLAYER_DEFAULTINITLIFE;

	exist = true;

	nComboHit = 0;
	nComboHitOri = 0;
	nComboGage = 0;

	nBounceAngle = 0;

	drainx = x;
	drainy = y;
	drainheadangle = 0;
	draintimer = 0;
	drainhscale = 1;
	drainvscale = 0;
	draincopyspriteangle = 0;

	if (effGraze.exist)
	{
		effGraze.Stop(true);
		effGraze.MoveTo(x, y, 0, true);
	}
	if (effChange.exist)
	{
		effChange.Stop(true);
		effChange.MoveTo(x, y, 0, true);
	}
	if (effInfi.exist)
	{
		effInfi.Stop(true);
		effInfi.MoveTo(x, y, 0, true);
	}
	if (effCollapse.exist)
	{
		effCollapse.Stop(true);
		effCollapse.MoveTo(x, y, 0, true);
	}
	if (effMerge.exist)
	{
		effMerge.Stop(true);
		effMerge.MoveTo(x, y, 0, true);
	}
	if (effBorder.exist)
	{
		effBorder.Stop(true);
		effBorder.MoveTo(x, y, 0, true);
	}
	if (effBorderOn.exist)
	{
		effBorderOn.Stop(true);
		effBorderOn.MoveTo(x, y, 0, true);
	}
	if (effBorderOff.exist)
	{
		effBorderOff.Stop(true);
		effBorderOff.MoveTo(x, y, 0, true);
	}

	changePlayerID(nowID, true);
	setShootingCharge(0);

	esChange.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERCHANGE, SpriteItemManager::GetIndexByName(SI_PLAYER_SHOTITEM), x, y, 0, 3.0f);
	esChange.colorSet(0x7fffffff, BLEND_ALPHAADD);
	esChange.chaseSet(EFFSP_CHASE_PLAYER_(playerindex), 0, 0);

	esShot.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERSHOT, SpriteItemManager::GetIndexByName(SI_PLAYER_SHOTITEM), x, y, 0, 1.2f);
	esShot.colorSet(0xccff0000);
	esShot.chaseSet(EFFSP_CHASE_PLAYER_(playerindex), 0, 0);

	esPoint.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERPOINT, SpriteItemManager::GetIndexByName(SI_PLAYER_POINT), x, y);
	esPoint.chaseSet(EFFSP_CHASE_PLAYER_(playerindex), 0, 0);

	esCollapse.valueSet(EFFSPSET_PLAYERUSE, EFFSP_PLAYERCOLLAPSE, SpriteItemManager::GetIndexByName(SI_PLAYER_SHOTITEM), x, y);
	esCollapse.actionSet(0, 0, 160);
	esCollapse.colorSet(0x80ffffff);
}

void Player::ClearRound(BYTE round/* =0 */)
{
	raisespellstopplayerindex = 0xff;
	if (round)
	{
		rank += _GAMERANK_STAGEOVERADD;
		if (rank < _GAMERANK_MIN)
		{
			rank = _GAMERANK_MIN;
		}
		AddLilyCount(-1000);
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			p[i].valueSet(i, round);
		}
	}
	else
	{
		rank = _GAMERANK_MIN;
		lilycount = 0;
		alltime = 0;
	}
}

//add


void Player::valueSet(BYTE _playerindex, BYTE round)
{
	playerindex = _playerindex;
	nowID		= ID;
	ClearSet(round);
	initFrameIndex();
	UpdatePlayerData();
	SetDrainSpriteInfo(x, y);

	nLife		=	initlife;

	if (round == 0)
	{
		lostStack		=	0;
	}

	setFrame(PLAYER_FRAME_STAND);

	effGraze.valueSet(EFF_PL_GRAZE, playerindex, *this);
	effGraze.Stop();
	effChange.valueSet(EFF_PL_CHANGE, playerindex, *this);
	effChange.Stop();
	effInfi.valueSet(EFF_PL_INFI, playerindex, *this);
	effInfi.Stop();
	effCollapse.valueSet(EFF_PL_COLLAPSE, playerindex, *this);
	effCollapse.Stop();
	effMerge.valueSet(EFF_PL_MERGE, playerindex, *this);
	effMerge.Stop();
	effBorder.valueSet(EFF_PL_BORDER, playerindex, *this);
	effBorder.Stop();
	effBorderOn.valueSet(EFF_PL_BORDERON, playerindex, *this);
	effBorderOn.Stop();
	effBorderOff.valueSet(EFF_PL_BORDEROFF, playerindex, *this);
	effBorderOff.Stop();

	SetAble(true);
}

bool Player::Action()
{
	alltime++;
	AddLostStack();
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		if (gametime % _CARDLEVEL_ADDINTERVAL == 0)
		{
			p[i].AddCardBossLevel(1, 0);
		}
		if (gametime % _BOSSLEVEL_ADDINTERVAL == 0)
		{
			p[i].AddCardBossLevel(0, 1);
		}
		DWORD stopflag = Process::mp.GetStopFlag();
		bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, i, FRAME_STOPFLAG_PLAYER);
		bool binspellstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, i, FRAME_STOPFLAG_PLAYERSPELL);
		GameInput::gameinput[i].updateActiveInput(binspellstop);
		if (p[i].exist)
		{
			if (!binstop && !binspellstop)
			{
				p[i].action();
			}
			else if (binspellstop)
			{
				p[i].actionInSpellStop();
			}
			else
			{
				p[i].actionInStop();
			}
			if (!p[i].exist)
			{
				return false;
			}
		}
	}
	if (gametime % _GAMERANK_ADDINTERVAL == 0)
	{
		rank++;
		if (rank > _GAMERANK_MAX)
		{
			rank = _GAMERANK_MAX;
		}
	}
	AddLilyCount(0, true);
	return true;
}

void Player::action()
{
	
#if defined __IPHONE
#define _M_MOVINGMIN	1
	if (!GameAI::ai[playerindex].able) {
		if (!(flag & PLAYER_SHOT)) {
			float tx = Process::mp.touchdirectmove[playerindex].x;
			if (tx > _M_MOVINGMIN) {
				GameInput::SetKey(playerindex, KSI_RIGHT, true);
			}
			else if (tx < -_M_MOVINGMIN){
				GameInput::SetKey(playerindex, KSI_LEFT, true);
			}
			if (fabsf(tx) <= slowspeed) {
				GameInput::SetKey(playerindex, KSI_SLOW, true);
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
	//	GameAI::ai[playerindex].UpdateBasicInfo(x, y, speed, slowspeed, BResource::bres.playerdata[nowID].collision_r);
	GameAI::ai[playerindex].SetMove();
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
	if(flag & PLAYER_PLAYERCHANGE)
	{
		if(PlayerChange())
		{
			flag &= ~PLAYER_PLAYERCHANGE;
		}
	}
	if(flag & PLAYER_SHOOT)
	{
		if(Shoot())
		{
			flag &= ~PLAYER_SHOOT;
		}
	}
	if(flag & PLAYER_BOMB)
	{
		if(Bomb())
		{
			flag &= ~PLAYER_BOMB;
		}
	}
	if(flag & PLAYER_DRAIN)
	{
		if(Drain())
		{
			flag &= ~PLAYER_DRAIN;
		}
	}
	if (flag & PLAYER_CHARGE)
	{
		if (Charge())
		{
			flag &= ~PLAYER_CHARGE;
		}
	}
	if(flag & PLAYER_GRAZE)
	{
		if(Graze())
		{
			flag &= ~PLAYER_GRAZE;
		}
	}

	nLifeCost++;
	if (nLifeCost > _PLAYER_LIFECOSTMAX)
	{
		nLifeCost = _PLAYER_LIFECOSTMAX;
	}
	if (rechargedelaytimer)
	{
		rechargedelaytimer--;
	}
	if (shootchargetimer)
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERSHOOTCHARGEONE, playerindex);
		PlayerBullet::BuildShoot(playerindex, nowID, shootchargetimer, true);
		shootchargetimer--;
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
	if (nComboGage)
	{
		nComboGage--;
		if (nComboGage == PLAYER_COMBORESET)
		{
			AddComboHit(-1, true);
		}
		else if (!nComboGage)
		{
			AddSpellPoint(-1);
		}
	}

	for (list<EventZone>::iterator it=EventZone::ezone[playerindex].begin(); it!=EventZone::ezone[playerindex].end(); it++)
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
		if (GameInput::GetKey(playerindex, KSI_SLOW))
		{
			bSlow = true;
			flag &= ~PLAYER_FASTCHANGE;
			if (GameInput::GetKey(playerindex, KSI_SLOW, DIKEY_DOWN))
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
			if (GameInput::GetKey(playerindex, KSI_SLOW, DIKEY_UP))
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

		if(GameInput::GetKey(playerindex, KSI_FIRE))
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
		if (shootpushtimer < PLAYER_SHOOTPUSHOVER)
		{
			if (GameInput::GetKey(playerindex, KSI_FIRE))
			{
				shootpushtimer++;
			}
			else
			{
				shootpushtimer = 0;
			}
		}
		else
		{
			if (!GameInput::GetKey(playerindex, KSI_FIRE))
			{
				bCharge = false;
				flag &= ~PLAYER_CHARGE;
				shootpushtimer = 0;
			}
			else
			{
				if (!rechargedelaytimer)
				{
					flag &= ~PLAYER_SHOOT;
					bCharge = true;
					if (shootpushtimer >= PLAYER_SHOOTPUSHOVER && !(flag & PLAYER_CHARGE))
					{
						chargetimer = 0;
						flag |= PLAYER_CHARGE;
						shootpushtimer = 0xff;
					}
				}
			}
		}
		if (GameInput::GetKey(playerindex, KSI_DRAIN))
		{
			bDrain = true;
			if (GameInput::GetKey(playerindex, KSI_DRAIN, DIKEY_DOWN))
			{
				if (!(flag & PLAYER_DRAIN))
				{
					draintimer = 0;
					SetDrainSpriteInfo(x, y, 0, 0);
				}
			}
			flag |= PLAYER_DRAIN;
		}
		else
		{
			bDrain = false;
			flag &= ~PLAYER_DRAIN;
		}

#if defined __IPHONE
		if (!GameAI::ai[playerindex].able) {
			if (Process::mp.touchMoveID[playerindex] != 0xff && !(flag & PLAYER_COSTLIFE)) {
				x += Process::mp.touchdirectmove[playerindex].x * speedfactor;
				y += Process::mp.touchdirectmove[playerindex].y * speedfactor;
			}
		}
		else {
#endif
		if((GameInput::GetKey(playerindex, KSI_UP) ^ GameInput::GetKey(playerindex, KSI_DOWN)) &&
			GameInput::GetKey(playerindex, KSI_LEFT) ^ GameInput::GetKey(playerindex, KSI_RIGHT))
			nowspeed *= M_SQUARE_2;
		if(GameInput::GetKey(playerindex, KSI_UP))
			y -= nowspeed;
		if(GameInput::GetKey(playerindex, KSI_DOWN))
			y += nowspeed;
		if(GameInput::GetKey(playerindex, KSI_LEFT))
		{
			x -= nowspeed;
		}
		if(GameInput::GetKey(playerindex, KSI_RIGHT))
		{
			x += nowspeed;
		}
#if defined __IPHONE
		}
#endif

		if(GameInput::GetKey(playerindex, KSI_LEFT))
		{
			updateFrame(PLAYER_FRAME_LEFTPRE);
		}
		if(GameInput::GetKey(playerindex, KSI_RIGHT))
		{
			if (!GameInput::GetKey(playerindex, KSI_LEFT))
			{
				updateFrame(PLAYER_FRAME_RIGHTPRE);
			}
			else
			{
				updateFrame(PLAYER_FRAME_STAND);
			}
		}
		if (!GameInput::GetKey(playerindex, KSI_LEFT) && !GameInput::GetKey(playerindex, KSI_RIGHT))
		{
			updateFrame(PLAYER_FRAME_STAND);
		}
	}
	if(GameInput::GetKey(playerindex, KSI_QUICK) && !(flag & PLAYER_MERGE))
	{
		callBomb();
	}

	if (!(flag & PLAYER_MERGE) || mergetimer >= 32)
	{
		if(x > PL_MOVABLE_RIGHT_(playerindex))
			x = PL_MOVABLE_RIGHT_(playerindex);
		else if(x < PL_MOVABLE_LEFT_(playerindex))
			x = PL_MOVABLE_LEFT_(playerindex);
		if(y > PL_MOVABLE_BOTTOM)
			y = PL_MOVABLE_BOTTOM;
		else if(y < PL_MOVABLE_TOP)
			y = PL_MOVABLE_TOP;
	}
	//AI
	GameAI::ai[playerindex].UpdateBasicInfo(x, y, speed*speedfactor, slowspeed*speedfactor, r, BResource::bres.playerdata[nowID].aidraintime);
	float aiaimx = _PL_MERGETOPOS_X_(playerindex);
	float aiaimy = _PL_MERGETOPOS_Y;
	bool tobelow = false;
	if (PlayerBullet::activelocked[playerindex] != PBLOCK_LOST)
	{
		aiaimx = Enemy::en[playerindex][PlayerBullet::activelocked[playerindex]].x;
		aiaimy = Enemy::en[playerindex][PlayerBullet::activelocked[playerindex]].y + 120;
		tobelow = true;
	}
	else if (PlayerBullet::locked[playerindex] != PBLOCK_LOST)
	{
		aiaimx = Enemy::en[playerindex][PlayerBullet::locked[playerindex]].x;
		aiaimy = Enemy::en[playerindex][PlayerBullet::locked[playerindex]].y;
	}
	GameAI::ai[playerindex].SetAim(aiaimx, aiaimy, tobelow);
	//
	//
	speedfactor = 1.0f;

	if (bInfi && timer % 8 < 4)
	{
		diffuse = 0xff99ff;
	}
	else
		diffuse = 0xffffff;

	esChange.action();
	esShot.action();
	esPoint.action();
	
	effGraze.MoveTo(x, y);
	effGraze.action();
	effCollapse.action();
	effBorderOn.action();
	effBorderOff.action();

	if(!(flag & PLAYER_GRAZE))
		effGraze.Stop();

	for(int i=0;i<PLAYERGHOSTMAX;i++)
	{
		if (pg[i].exist)
		{
			pg[i].action();
		}
	}
}

void Player::actionInSpellStop()
{
	spellstoptimer++;
	Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERINSPELLSTOP, playerindex);
}

void Player::actionInStop()
{
//	Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERINSTOP, playerindex);
}

bool Player::Merge()
{
	mergetimer++;
	if(mergetimer == 1)
	{
		SetInfi(PLAYERINFI_MERGE, 60);
		if(GameInput::GetKey(playerindex, KSI_SLOW))
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
	else if (mergetimer <= 24)
	{
		float interval = mergetimer / 24.0f;
		x = INTER(PL_MERGEPOS_X_(playerindex), _PL_MERGETOPOS_X_(playerindex), interval);
		y = INTER(PL_MERGEPOS_Y, _PL_MERGETOPOS_Y, interval);
		flag &= ~PLAYER_SHOOT;
		alpha = INTER(0, 0xff, interval);
	}
	else if(mergetimer < 60)
	{
		alpha = 0xff;
	}
	else if(mergetimer == 60)
	{
		mergetimer = 0;
		return true;
	}
	return false;
}

bool Player::Shot()
{
	shottimer++;
	// TODO:
	if(bInfi)
	{
		shottimer = 0;
		return true;
	}
	
	if(shottimer == 1)
	{
//		Item::undrainAll();
		SE::push(SE_PLAYER_SHOT, x);
	}
	else if(shottimer == shotdelay)
	{
		shottimer = 0;
		flag |= PLAYER_COSTLIFE;
		return true;
	}

	esShot.hscale = (shotdelay - shottimer) * 4.0f / shotdelay;
	Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERSHOT, playerindex);
	return false;
}

bool Player::CostLife()
{
	costlifetimer++;
	if (costlifetimer == 1)
	{
		AddLilyCount(-1500);
		if (nLife == 1)
		{
			nLife = 0;
			flag |= PLAYER_COLLAPSE;
			costlifetimer = 0;
			return true;
		}
		int nLifeCostNum = nLifeCost / 720 + 2;
		if (nLife > nLifeCostNum+1)
		{
			nLife -= nLifeCostNum;
		}
		else
		{
			FrontDisplay::fdisp.gameinfodisplay.lastlifecountdown[playerindex] = FDISP_COUNTDOWNTIME;
			SE::push(SE_PLAYER_ALERT, x);
			nLife = 1;
		}
		nLifeCost -= 1440;
		if (nLifeCost < 0)
		{
			nLifeCost = 0;
		}
		SetInfi(PLAYERINFI_COSTLIFE, 120);
		if (nLife == 1)
		{
			AddCharge(0, PLAYER_CHARGEMAX);
		}
		else
		{
			AddCharge(0, 130-nLife * 10);
		}
		nBounceAngle = randt();
	}
	else if (costlifetimer == 50)
	{
		EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_ENEMYDAMAGE|EVENTZONE_TYPE_NOSEND|EVENTZONE_CHECKTYPE_CIRCLE, playerindex, x, y, 10, 0, 0, 10, EVENTZONE_EVENT_NULL, 15.6);
	}
	else if (costlifetimer == 60)
	{
		costlifetimer = 0;
		return true;
	}
	else
	{
		GameInput::SetKey(playerindex, KSI_UP, false);
		GameInput::SetKey(playerindex, KSI_DOWN, false);
		GameInput::SetKey(playerindex, KSI_LEFT, false);
		GameInput::SetKey(playerindex, KSI_RIGHT, false);
//		GameInput::SetKey(playerindex, KSI_FIRE, false);
		GameInput::SetKey(playerindex, KSI_QUICK, false);
		GameInput::SetKey(playerindex, KSI_SLOW, false);
		GameInput::SetKey(playerindex, KSI_DRAIN, false);
		x += cost(nBounceAngle) * ((60-costlifetimer) / 20.0f);
		y += sint(nBounceAngle) * ((60-costlifetimer) / 20.0f);
	}
	return false;
}

bool Player::Collapse()
{
	collapsetimer++;
	if(collapsetimer == 1)
	{
		for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
		{
			EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_ENEMYDAMAGE|EVENTZONE_TYPE_NOSEND|EVENTZONE_CHECKTYPE_CIRCLE, i, p[i].x, p[i].y, 64, EVENTZONE_OVERZONE, 0, 1000, EVENTZONE_EVENT_NULL, 16);
			p[i].SetInfi(PLAYERINFI_COLLAPSE, 64);
		}

		esCollapse.x = x;
		esCollapse.y = y;
		SE::push(SE_PLAYER_DEAD, x);

		effCollapse.MoveTo(x, y , 0, true);
		effCollapse.Fire();
		p[1-playerindex].winflag |= 1<<round;
	}
	else if(collapsetimer == 64)
	{
		x = PL_MERGEPOS_X_(playerindex);
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

		AddCharge(0, 130);

//		SetInfi(PLAYERINFI_COLLAPSE);
		exist = false;

		if(GameInput::GetKey(playerindex, KSI_SLOW))
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

	if (!(flag & PLAYER_SHOT) && !(flag & PLAYER_COSTLIFE))
	{
		PlayerBullet::BuildShoot(playerindex, nowID, shoottimer);
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

bool Player::Drain()
{
	draintimer++;
	bDrain = true;
	Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERDRAIN, playerindex);
	return false;
}

bool Player::Bomb()
{
	BYTE ncharge;
	BYTE nchargemax;
	GetNCharge(&ncharge, &nchargemax);
	if (nchargemax > 1)
	{
		BYTE nChargeLevel = shootCharge(nchargemax, true);
		if (nChargeLevel == nchargemax)
		{
			AddCharge(-PLAYER_CHARGEMAX, -PLAYER_CHARGEMAX);
		}
		else
		{
			AddCharge((nChargeLevel-nchargemax)*PLAYER_CHARGEONE, (nChargeLevel-nchargemax)*PLAYER_CHARGEONE);
		}
	}
	return true;
}

bool Player::SlowChange()
{
	if(GameInput::GetKey(playerindex, KSI_SLOW, DIKEY_DOWN))
		slowtimer = 0;
	bSlow = true;
	slowtimer++;
	if(slowtimer == 1)
	{
		ResetPlayerGhost();
		SE::push(SE_PLAYER_SLOWON, x);
		for(int i=0;i<PLAYERGHOSTMAX;i++)
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
	if(GameInput::GetKey(playerindex, KSI_SLOW, DIKEY_UP))
		fasttimer = 0;
	bSlow = false;
	fasttimer++;
	if(fasttimer == 1)
	{
		ResetPlayerGhost();
		SE::push(SE_PLAYER_SLOWOFF, x);
		for(int i=0;i<PLAYERGHOSTMAX;i++)
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

bool Player::Charge()
{
	chargetimer++;
	if (chargetimer == 1)
	{
		SE::push(SE_PLAYER_CHARGEON, x);
	}
	BYTE nChargeLevel = AddCharge(chargespeed);
	if (!GameInput::GetKey(playerindex, KSI_FIRE))
	{
		shootCharge(nChargeLevel);
		chargetimer = 0;
		fCharge = 0;
		if (nChargeLevel > 0)
		{
			rechargedelaytimer = rechargedelay;
		}
		return true;
	}
	bCharge = true;
	return false;
}

bool Player::PlayerChange()
{
	if(GameInput::GetKey(playerindex, KSI_DRAIN, DIKEY_DOWN))
		playerchangetimer = 0;
	playerchangetimer++;
	if(playerchangetimer == 1)
	{
	}
	else if(playerchangetimer == 16)
	{
		playerchangetimer = 0;
		return true;
	}
	esChange.colorSet(0x3030ff | (((16-playerchangetimer) * 16)<<16));
	return false;
}

void Player::changePlayerID(WORD toID, bool moveghost/* =false */)
{
	nowID = toID;
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
	float addcharge = nComboHitOri / 128.0f + 1.0f;
	if (addcharge > 2.0f)
	{
		addcharge = 2.0f;
	}
	AddComboHit(1, true);
	AddCharge(0, addcharge);

	enemyData * edata = &(BResource::bres.enemydata[type]);
	AddExPoint(edata->expoint, x, y);

	int addghostpoint;
	if (edata->ghostpoint < 0)
	{
		addghostpoint = nComboHitOri + 3;
		if (addghostpoint > 28)
		{
			addghostpoint = 28;
		}
	}
	else
	{
		addghostpoint = edata->ghostpoint;
	}
	AddGhostPoint(addghostpoint, x, y);

	int addbulletpoint;
	float _x = x + randtf(-4.0f, 4.0f);
	float _y = y + randtf(-4.0f, 4.0f);
	if (edata->bulletpoint < 0)
	{
		addbulletpoint = nComboHitOri * 3 + 27;
		if (addbulletpoint > 60)
		{
			addbulletpoint = 60;
		}
	}
	else
	{
		addbulletpoint = edata->bulletpoint;
	}
	AddBulletPoint(addbulletpoint, _x, _y);

	int addspellpoint;
	if (edata->spellpoint == -1)
	{
		if (nComboHitOri == 1)
		{
			addspellpoint = 20;
		}
		else
		{
			addspellpoint = nComboHitOri * 30 - 20;
			if (addspellpoint > 3000)
			{
				addspellpoint = 3000;
			}
		}
	}
	else if (edata->spellpoint == -2)
	{
		if (nComboHitOri == 1)
		{
			addspellpoint = 2000;
		}
		else
		{
			addspellpoint = (nComboHitOri + 4) * 200;
			if (addspellpoint > 11000)
			{
				addspellpoint = 11000;
			}
		}
	}
	else
	{
		addspellpoint = edata->spellpoint;
	}
	AddSpellPoint(addspellpoint);
}

void Player::DoGraze(float x, float y)
{
	if(!(flag & (PLAYER_MERGE | PLAYER_SHOT | PLAYER_COLLAPSE)))
	{
		flag |= PLAYER_GRAZE;
	}
}

void Player::DoPlayerBulletHit(int hitonfactor)
{
	if (hitonfactor < 0)
	{
		AddComboHit(-1, true);
	}
}

void Player::DoSendBullet(float x, float y, int sendbonus)
{
	for (int i=0; i<sendbonus; i++)
	{
		AddComboHit(1, false);
		AddGhostPoint(2, x, y);
		AddBulletPoint(3, x, y);
		int addspellpoint = nComboHitOri * 9;
		if (addspellpoint > 1000)
		{
			addspellpoint = 1000;
		}
		AddSpellPoint(addspellpoint);
	}
}

void Player::DoShot()
{
	if (!bInfi && !(flag & (PLAYER_SHOT | PLAYER_COLLAPSE)))
	{
		flag |= PLAYER_SHOT;
		AddComboHit(-1, true);
		AddSpellPoint(-1);
	}
}

void Player::DoItemGet(WORD itemtype, float _x, float _y)
{
	switch (itemtype)
	{
	case ITEM_GAUGE:
		AddCharge(0, PLAYER_CHARGEMAX);
		break;
	case ITEM_BULLET:
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERSENDITEMBULLET, playerindex);
//		Item::SendBullet(1-playerindex, _x, _y, EFFSPSET_SYSTEM_SENDITEMBULLET);
		break;
	case ITEM_EX:
		AddBulletPoint(1, _x, _y);
		AddExPoint(100, _x, _y);
		break;
	case ITEM_POINT:
		AddSpellPoint(70000+rank*7000);
		break;
	}
}

void Player::GetNCharge(BYTE * ncharge, BYTE * nchargemax)
{
	if (ncharge)
	{
		*ncharge = (BYTE)(fCharge/PLAYER_CHARGEONE);
	}
	if (nchargemax)
	{
		*nchargemax = (BYTE)(fChargeMax/PLAYER_CHARGEONE);
	}
}

void Player::GetSpellClassAndLevel(BYTE * spellclass, BYTE * spelllevel, int  _shootingchargeflag)
{
	BYTE usingshootingchargeflag = shootingchargeflag;
	if (_shootingchargeflag > 0)
	{
		usingshootingchargeflag = _shootingchargeflag;
	}
	if (spellclass)
	{
		if (usingshootingchargeflag & _PL_SHOOTINGCHARGE_4)
		{
			if ((usingshootingchargeflag & _PL_SHOOTINGCHARGE_3) || (usingshootingchargeflag & _PL_SHOOTINGCHARGE_2))
			{
				*spellclass = 4;
			}
			else
			{
				*spellclass = 3;
			}
		}
		else if (usingshootingchargeflag & _PL_SHOOTINGCHARGE_3)
		{
			*spellclass = 2;
		}
		else if (usingshootingchargeflag & _PL_SHOOTINGCHARGE_2)
		{
			*spellclass = 1;
		}
		else
		{
			*spellclass = 0;
		}
	}
	if (spelllevel)
	{
		if (usingshootingchargeflag & _PL_SHOOTINGCHARGE_4)
		{
			*spelllevel = nowbosslevel;
		}
		else if(usingshootingchargeflag)
		{
			*spelllevel = nowcardlevel;
		}
		else
		{
			*spelllevel = 0;
		}
	}
}


void Player::ResetPlayerGhost(bool move /* = false */)
{
	int tid = nowID;
	tid *= PLAYERGHOSTMAX * 2;
	if (bSlow)
	{
		tid += PLAYERGHOSTMAX;
	}
	for (int i=0; i<PLAYERGHOSTMAX; i++)
	{
		pg[i].valueSet(playerindex, tid+i, move);
	}
}

void Player::Render()
{
	if (spdrain && bDrain)
	{
		SpriteItemManager::RenderSpriteEx(spdrain, drainx, drainy, ARC(drainheadangle), drainhscale, drainvscale);
		if (draincopyspriteangle)
		{
			SpriteItemManager::RenderSpriteEx(spdrain, drainx, drainy, ARC(drainheadangle+draincopyspriteangle), drainhscale, drainvscale);
		}
	}
	if (sprite)
	{
		sprite->SetColor(alpha<<24|diffuse);
		SpriteItemManager::RenderSpriteEx(sprite, x, y, 0, hscale, vscale);
	}
}

void Player::RenderEffect()
{
	effGraze.Render();

	for(int i=0;i<PLAYERGHOSTMAX;i++)
	{
		if (pg[i].exist)
		{
			pg[i].Render();
		}
	}
	if(flag & PLAYER_PLAYERCHANGE)
	{
		esChange.Render();
	}
	if(flag & PLAYER_SHOT)
		esShot.Render();
	effBorderOff.Render();
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

void Player::callCollapse()
{
	if (flag & PLAYER_COLLAPSE)
	{
		return;
	}
	flag |= PLAYER_COLLAPSE;
	collapsetimer = 0;
}

bool Player::callBomb()
{
	if (Chat::chatitem.IsChatting() || (flag & PLAYER_COLLAPSE))
	{
		return false;
	}
	return Bomb();
}

void Player::callSlowFastChange(bool toslow)
{
	if (toslow)
	{
		GameInput::SetKey(playerindex, KSI_SLOW);
	}
	else
	{
		GameInput::SetKey(playerindex, KSI_SLOW, false);
	}
}

void Player::callPlayerChange()
{
	flag |= PLAYER_PLAYERCHANGE;
	playerchangetimer = 0;
}

void Player::setShootingCharge(BYTE _shootingchargeflag)
{
	if (!_shootingchargeflag)
	{
		shootingchargeflag = 0;
	}
	else
	{
		shootingchargeflag |= _shootingchargeflag;
		if (shootingchargeflag & _PL_SHOOTINGCHARGE_1)
		{
			shootchargetimer = BResource::bres.playerdata[nowID].shootchargetime;
		}
		if (_shootingchargeflag & ~_PL_SHOOTINGCHARGE_1)
		{
			nowshootingcharge = _shootingchargeflag;
			if (_shootingchargeflag & _PL_SHOOTINGCHARGE_4)
			{
				nowbosslevel = bosslevel;
			}
			else
			{
				nowcardlevel = cardlevel;
			}
			Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERSHOOTCHARGE, playerindex);
		}
	}
}

BYTE Player::shootCharge(BYTE nChargeLevel, bool nodelete)
{
	if (flag & PLAYER_COLLAPSE)
	{
		return 0;
	}
	if (!nChargeLevel)
	{
		return 0;
	}
	if (nChargeLevel > 3 && nChargeLevel < 7 && Enemy::bossindex[1-playerindex] != 0xff)
	{
		if (nChargeLevel == 4)
		{
			return shootCharge(3, nodelete);
		}
		else if (nChargeLevel == 6)
		{
			return shootCharge(7, nodelete);
		}
		return 0;
	}
	setShootingCharge(0);
	int chargezonemaxtime=1;
	float chargezoner=0;
	switch (nChargeLevel)
	{
	case 1:
		SetInfi(PLAYERINFI_SHOOTCHARGE, _PL_SHOOTCHARGEINFI_1);
		setShootingCharge(_PL_SHOOTINGCHARGE_1);
//		AddCardBossLevel(1, 0);
		break;
	case 2:
		SetInfi(PLAYERINFI_SHOOTCHARGE, _PL_SHOOTCHARGEINFI_2);
		if (!nodelete)
		{
			setShootingCharge(_PL_SHOOTINGCHARGE_1);
		}
		setShootingCharge(_PL_SHOOTINGCHARGE_2);
		AddCardBossLevel(1, 0);
		chargezonemaxtime = _PL_CHARGEZONE_MAXTIME_2;
		chargezoner = _PL_CHARGEZONE_R_2;
		break;
	case 3:
		SetInfi(PLAYERINFI_SHOOTCHARGE, _PL_SHOOTCHARGEINFI_3);
		if (!nodelete)
		{
			setShootingCharge(_PL_SHOOTINGCHARGE_1);
		}
		setShootingCharge(_PL_SHOOTINGCHARGE_3);
		AddCardBossLevel(1, 0);
		chargezonemaxtime = _PL_CHARGEZONE_MAXTIME_3;
		chargezoner = _PL_CHARGEZONE_R_3;
		break;
	case 4:
		SetInfi(PLAYERINFI_SHOOTCHARGE, _PL_SHOOTCHARGEINFI_4);
		if (!nodelete)
		{
			setShootingCharge(_PL_SHOOTINGCHARGE_1);
		}
		setShootingCharge(_PL_SHOOTINGCHARGE_4);
		AddCardBossLevel(0, 1);
		chargezonemaxtime = _PL_CHARGEZONE_MAXTIME_4;
		chargezoner = _PL_CHARGEZONE_R_4;
		break;
	case 5:
		setShootingCharge(_PL_SHOOTINGCHARGE_4);
		AddCardBossLevel(0, 1);
		break;
	case 6:
		setShootingCharge(_PL_SHOOTINGCHARGE_3);
		setShootingCharge(_PL_SHOOTINGCHARGE_4);
		AddCardBossLevel(1, 1);
		break;
	case 7:
		setShootingCharge(_PL_SHOOTINGCHARGE_3);
		AddCardBossLevel(1, 0);
		break;
	}
	if (nChargeLevel > 1)
	{
		raisespellstopplayerindex = playerindex;
		spellstoptimer = 0;
		Process::mp.SetStop(FRAME_STOPFLAG_SPELLSET|FRAME_STOPFLAG_PLAYERINDEX_0|FRAME_STOPFLAG_PLAYERINDEX_1, PL_SHOOTINGCHARGE_STOPTIME);
		if (chargezoner)
		{
			EventZone::Build(EVENTZONE_TYPE_BULLETFADEOUT|EVENTZONE_TYPE_ENEMYDAMAGE|EVENTZONE_TYPE_NOSEND|EVENTZONE_CHECKTYPE_CIRCLE, playerindex, x, y, chargezonemaxtime, 0, 0, 10, EVENTZONE_EVENT_NULL, chargezoner/chargezonemaxtime, -2, SpriteItemManager::GetIndexByName(SI_PLAYER_CHARGEZONE), 400);
		}
		if (nChargeLevel < 5)
		{
			AddCharge(-PLAYER_CHARGEONE*(nChargeLevel-1), -PLAYER_CHARGEONE*(nChargeLevel-1));
		}
		AddLilyCount(-500);
		FrontDisplay::fdisp.OnShootCharge(playerindex, nowshootingcharge);
	}
	return nChargeLevel;
}

void Player::SendEx(BYTE playerindex, float x, float y)
{
	int _esindex = EffectSp::Build(EFFSPSET_SYSTEM_SENDEXATTACK, playerindex, EffectSp::senditemexsiid, x, y);
	if (_esindex >= 0)
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERSENDEX, playerindex);
		SE::push(SE_BULLET_SENDEX, x);
	}
}

void Player::AddExPoint(float expoint, float x, float y)
{
	fExPoint += expoint;
	float fexsend = fExSendParaB + fExSendParaA * rank;
	if (fexsend < fExSendMax)
	{
		fexsend = fExSendMax;
	}
	if (fExPoint >= fexsend)
	{
		AddExPoint(-fexsend, x, y);
		SendEx(1-playerindex, x, y);
	}
}

void Player::AddGhostPoint(int ghostpoint, float x, float y)
{
	nGhostPoint += ghostpoint;
	if (nGhostPoint >= 60-rank*1.5f)
	{
		if (nBulletPoint >= 10)
		{
			AddGhostPoint(-(60-rank*2), x, y);
			AddBulletPoint(-10, x, y);
			Enemy::SendGhost(1-playerindex, x, y, EFFSPSET_SYSTEM_SENDGHOST);
		}
	}
}

void Player::AddBulletPoint(int bulletpoint, float x, float y)
{
	nBulletPoint += bulletpoint * 4 / 3;
	if (nBulletPoint >= 120-rank*4)
	{
		AddBulletPoint(-(120-rank*4), x, y);
		BYTE setID = EFFSPSET_SYSTEM_SENDBLUEBULLET;
		if (randt(0, 2) == 0)
		{
			setID = EFFSPSET_SYSTEM_SENDREDBULLET;
		}
		Bullet::SendBullet(1-playerindex, x, y, setID);
	}
}

void Player::AddSpellPoint(int spellpoint)
{
	if (spellpoint < 0)
	{
		nSpellPoint = 0;
		return;
	}
	spellpoint = spellpoint * rank / 10 + spellpoint;
	int spellpointone = spellpoint % 10;
	if (spellpointone)
	{
		spellpoint += 10-spellpointone;
	}
	if (nSpellPoint < _PL_SPELLBONUS_BOSS_1 && nSpellPoint + spellpoint >= _PL_SPELLBONUS_BOSS_1 ||
		nSpellPoint < _PL_SPELLBONUS_BOSS_2 && nSpellPoint + spellpoint >= _PL_SPELLBONUS_BOSS_2)
	{
		shootCharge(5);
	}
	else if (nSpellPoint < _PL_SPELLBONUS_BOSS_3 && nSpellPoint + spellpoint >= _PL_SPELLBONUS_BOSS_3)
	{
		shootCharge(6);
	}
	nSpellPoint += spellpoint;
	if (nSpellPoint > PLAYER_NSPELLPOINTMAX)
	{
		nSpellPoint = PLAYER_NSPELLPOINTMAX;
	}
}

void Player::AddComboHit(int combo, bool ori)
{
	if (combo < 0)
	{
		nComboHit = 0;
		nComboHitOri = 0;
		return;
	}
	nComboHit += combo;
	if (nComboHit > PLAYER_NCOMBOHITMAX)
	{
		nComboHit = PLAYER_NCOMBOHITMAX;
	}
	if (ori)
	{
		nComboHitOri += combo;
		if (nComboHitOri > PLAYER_NCOMBOHITMAX)
		{
			nComboHitOri = PLAYER_NCOMBOHITMAX;
		}
	}

	if (nComboGage < 74)
	{
		nComboGage += 30;
		if (nComboGage < 74)
		{
			nComboGage = 74;
		}
	}
	else if (nComboGage < 94)
	{
		nComboGage += 5;
	}
	else
	{
		nComboGage += 2;
	}
	if (nComboGage > PLAYER_COMBOGAGEMAX)
	{
		nComboGage = PLAYER_COMBOGAGEMAX;
	}
}

BYTE Player::AddCharge(float addcharge, float addchargemax)
{
	BYTE ncharge;
	BYTE nchargemax;
	GetNCharge(&ncharge, &nchargemax);
	float addchargemaxval = addchargemax;
	if (addchargemax > 0)
	{
		addchargemaxval = addchargemax * BResource::bres.playerdata[nowID].addchargerate;
	}
	fChargeMax += addchargemaxval;
	if (fChargeMax > PLAYER_CHARGEMAX)
	{
		fChargeMax = PLAYER_CHARGEMAX;
	}
	if (fChargeMax < 0)
	{
		fChargeMax = 0;
	}
	fCharge += addcharge;
	if (fCharge > fChargeMax)
	{
		fCharge = fChargeMax;
	}
	if (fCharge < 0)
	{
		fCharge = 0;
	}
	BYTE nchargenow;
	BYTE nchargemaxnow;
	GetNCharge(&nchargenow, &nchargemaxnow);
	if (nchargenow > ncharge)
	{
		SE::push(SE_PLAYER_CHARGEUP);
	}
	if (nchargemaxnow > nchargemax)
	{
		FrontDisplay::fdisp.gameinfodisplay.gaugefilledcountdown[playerindex] = FDISP_COUNTDOWNTIME;
	}
	return nchargenow;
}

void Player::AddLilyCount(int addval, bool bytime/* =false */)
{
	if (bytime)
	{
		if (gametime < 5400)
		{
			AddLilyCount(gametime/1800+3);
		}
		else
		{
			AddLilyCount(7);
		}
	}
	lilycount += addval;
	if (lilycount > 10000)
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERSENDLILY, rank);
		AddLilyCount(-10000);
	}
	else if (lilycount < 0)
	{
		lilycount = 0;
	}
}

void Player::AddCardBossLevel(int cardleveladd, int bossleveladd)
{
	cardlevel += cardleveladd;
	bosslevel += bossleveladd;
	if (cardlevel > _CARDLEVEL_MAX)
	{
		cardlevel = _CARDLEVEL_MAX;
	}
	if (bosslevel > _BOSSLEVEL_MAX)
	{
		bosslevel = _BOSSLEVEL_MAX;
	}
}
