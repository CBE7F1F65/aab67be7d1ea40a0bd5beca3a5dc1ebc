#include "../header/Enemy.h"
#include "../header/Player.h"
#include "../header/SE.h"
#include "../header/Item.h"
#include "../header/Scripter.h"
#include "../header/Chat.h"
#include "../header/BossInfo.h"
#include "../header/Process.h"
#include "../header/BResource.h"
#include "../header/FrontDisplay.h"
#include "../header/EffectIDDefine.h"
#include "../header/EventZone.h"
#include "../header/SpriteItemManager.h"
#include "../header/GameAI.h"

#define _DAMAGEZONEMAX	0x10

VectorList<Enemy> Enemy::en[M_PL_MATCHMAXPLAYER];
list<EnemyActivationZone> Enemy::enaz[M_PL_MATCHMAXPLAYER];

BYTE Enemy::bossindex[M_PL_MATCHMAXPLAYER];
BYTE Enemy::nEnemyNow[M_PL_MATCHMAXPLAYER][ENEMY_NMAXSETMAX];

#define _SCOREDISPLAYMAX		(ENEMYMAX*2)
VectorList<ScoreDisplay> Enemy::scoredisplay[M_PL_MATCHMAXPLAYER];

#define _ENEMYDELETE_LEFT_(X)	(M_GAMESQUARE_LEFT_(X)-M_GAMESQUARE_EDGE)
#define _ENEMYDELETE_RIGHT_(X)	(M_GAMESQUARE_RIGHT_(X)+M_GAMESQUARE_EDGE)
#define _ENEMYDELETE_TOP		(M_GAMESQUARE_TOP-M_GAMESQUARE_EDGE)
#define _ENEMYDELETE_BOTTOM		(M_GAMESQUARE_BOTTOM+M_GAMESQUARE_EDGE)

Enemy::Enemy()
{
	exist	= false;
	able	= false;
	ID		= 0;
	sprite = NULL;
}

Enemy::~Enemy()
{
	SpriteItemManager::FreeSprite(&sprite);
}

void Enemy::Init()
{
	Release();
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		en[i].init(ENEMYMAX);
		scoredisplay[i].init(_SCOREDISPLAYMAX);
		bossindex[i] = 0xff;
	}
}

void Enemy::Release()
{
	for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
	{
		en[i].clear();
		enaz[i].clear();
		scoredisplay[i].clear();
	}
}

int Enemy::Build(WORD eID, BYTE playerindex, float x, float y, int angle, float speed, BYTE type, float life, int infitimer)
{
	BYTE nmaxset = BResource::bres.enemydata[type].nmaxset;
	BYTE nmax = BResource::bres.enemydata[type].nmax;
	if (nmax && nEnemyNow[playerindex][nmaxset] > nmax)
	{
		return -1;
	}
	Enemy _en;
	Enemy * _pen = NULL;
	if (en[playerindex].getSize() < ENEMYMAX)
	{
		_pen = en[playerindex].push_back(_en);
	}
	else
	{
		DWORD i = 0;
		DWORD size = en[playerindex].getSize();
		for (en[playerindex].toEnd(); i<size; en[playerindex].toNext(), i++)
		{
			if (!en[playerindex].isValid())
			{
				_pen = en[playerindex].push(_en);
				break;
			}
		}
	}
	if (_pen)
	{
		if (life > 0.5f)
		{
			life -= 0.5f;
		}
		_pen->valueSet(playerindex, eID, x, y, angle, speed, type, life, infitimer);
		return en[playerindex].getIndex();
	}
	return -1;
}

void Enemy::Clear()
{
	exist = false;
	able = false;
	timer = 0;
}

void Enemy::ClearAll()
{
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		for (int i=0; i<en[j].getCapacity(); i++)
		{
			en[j][i].Clear();
		}
		bossindex[j] = 0xff;
		en[j].clear_item();
		enaz[j].clear();
		scoredisplay[j].clear_item();
		for (int i=0; i<ENEMY_NMAXSETMAX; i++)
		{
			nEnemyNow[j][i] = 0;
		}
	}
}

void Enemy::BossFadeout(BYTE playerindex)
{
	if (bossindex[playerindex] != 0xff)
	{
		bossindex[playerindex] = 0xff;
		FrontDisplay::fdisp.SetState(FDISP_SPELLNAME_0+(1-playerindex), FDISPSTATE_OFF);
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_BOSSFADEOUT, playerindex);
	}
}

void Enemy::Action()
{
	PlayerBullet::ClearLock();
	for (int j=0; j<M_PL_MATCHMAXPLAYER; j++)
	{
		for (int k=0; k<ENEMY_NMAXSETMAX; k++)
		{
			nEnemyNow[j][k] = 0;
		}
//		bossindex[j] = 0xff;
		DWORD i = 0;
		DWORD size = en[j].getSize();
		DWORD stopflag = Process::mp.GetStopFlag();
		bool binstop = FRAME_STOPFLAGCHECK_PLAYERINDEX_(stopflag, j, FRAME_STOPFLAG_ENEMY);
		for (en[j].toBegin(); i<size; en[j].toNext(), i++)
		{
			if (en[j].isValid())
			{
				Enemy * pen = &(*(en[j]));
				if (pen->exist)
				{
					BYTE nmaxset = BResource::bres.enemydata[(*en[j]).type].nmaxset;
					nEnemyNow[j][nmaxset]++;
					DWORD _index = en[j].getIndex();
					if (!binstop)
					{
						pen->action();
					}
					else
					{
						pen->actionInStop();
					}
					en[j].toIndex(_index);
					if (pen->able)
					{
						PlayerBullet::CheckAndSetLock((BObject *)pen, j, en[j].getIndex(), pen->checkActive() && pen->maxlife < 100 && (pen->flag & ENEMYFLAG_PBSHOTABLE));
						if (pen->type < PLAYERTYPEMAX)
						{
							bossindex[j] = en[j].getIndex();
						}
					}
					else
					{
						if (pen->type < PLAYERTYPEMAX)
						{
							BossFadeout(j);
						}
					}
					float tw;
					float th;
					pen->GetCollisionRect(&tw, &th);
					GameAI::ai[j].CheckEnemyCollision(pen, tw, th);
				}
				else
				{
					en[j].pop();
				}
			}
		}
		//enaz.clear
		enaz[j].clear();
		//

		i = 0;
		size = scoredisplay[j].size;
		for (scoredisplay[j].toBegin(); i<size; scoredisplay[j].toNext(), i++)
		{
			if (scoredisplay[j].isValid())
			{
				if(!binstop)
				{
					ScoreDisplay * _item = &(*(scoredisplay[j]));
					_item->timer++;
					if(_item->timer >= 48)
					{
						scoredisplay[j].pop();
					}
					if (_item->timer == 40 || _item->timer == 44)
					{
						if (strcmp(_item->cScore, "b"))
						{
							for(int i=0; i<(int)strlen(_item->cScore); i++)
							{
								_item->cScore[i] += 10;
							}
						}
					}
				}
			}
		}
	}
}

void Enemy::BuildENAZ(BYTE playerindex, BYTE flag, float x, float y, float rPrep, float rParal, int angle)
{
	EnemyActivationZone _enaz;
	enaz[playerindex].push_back(_enaz);
	EnemyActivationZone * _penaz = &(*(enaz[playerindex].rbegin()));
	_penaz->flag = flag;
	_penaz->x = x;
	_penaz->y = y;
	_penaz->rPrep = rPrep;
	_penaz->rParal = rParal;
	_penaz->angle = angle;
}

void Enemy::SendGhost(BYTE playerindex, float x, float y, BYTE setID, BYTE * sendtime, float * acceladd)
{
	int siidindex = EFFSPSEND_COLOR_RED;
	if (playerindex)
	{
		siidindex = EFFSPSEND_COLOR_BLUE;
	}
	float _hscale = randtf(1.2f, 1.4f);
	int esindex = EffectSp::Build(setID, playerindex, EffectSp::senditemsiid[siidindex][0], x, y, 0, _hscale);
	if (esindex >= 0)
	{
		EffectSp * _peffsp = &(EffectSp::effsp[playerindex][esindex]);
		_peffsp->colorSet(0x80ffffff, BLEND_ALPHAADD);
		float aimx;
		float aimy;
		aimx = randtf(M_GAMESQUARE_LEFT_(playerindex) + 8, M_GAMESQUARE_RIGHT_(playerindex) - 8);
		aimy = randtf(M_GAMESQUARE_TOP, M_GAMESQUARE_TOP + 128);
		_peffsp->chaseSet(EFFSP_CHASE_FREE, aimx, aimy, randt(45, 60));
		_peffsp->animationSet(EFFSPSEND_ANIMATIONMAX);
		if (sendtime)
		{
			_peffsp->AppendData(*sendtime, *acceladd);
		}
		else
		{
			_peffsp->AppendData(0, 0);
		}
	}
}

void Enemy::RenderAll(BYTE _playerindex)
{
	DWORD i = 0;
	DWORD size = en[_playerindex].getSize();
	for (en[_playerindex].toBegin(); i<size; en[_playerindex].toNext(), i++)
	{
		if (en[_playerindex].isValid())
		{
			if ((*en[_playerindex]).exist)
			{
				(*en[_playerindex]).Render();
				(*en[_playerindex]).RenderEffect();
			}
		}
	}
}

void Enemy::RenderScore(BYTE _playerindex)
{
	DWORD i = 0;
	DWORD size = scoredisplay[_playerindex].size;
	for (scoredisplay[_playerindex].toBegin(); i<size; scoredisplay[_playerindex].toNext(), i++)
	{
		if (scoredisplay[_playerindex].isValid())
		{
			ScoreDisplay * _item = &(*(scoredisplay[_playerindex]));
			if(_item->yellow)
				FrontDisplay::fdisp.info.itemfont->SetColor(0xffffff00);
			else
				FrontDisplay::fdisp.info.itemfont->SetColor(0xffffffff);
			FrontDisplay::fdisp.info.itemfont->RenderEx(_item->x, _item->y-10-_item->timer/4, HGETEXT_CENTER, _item->cScore, FrontDisplay::fdisp.info.itemfont->GetScale());
		}
	}
}

void Enemy::Render()
{
	if (sprite)
	{
		sprite->SetColor(alpha<<24|diffuse);
		SpriteItemManager::RenderSpriteEx(sprite, x, y, ARC(headangle), hscale, vscale);
	}
}

void Enemy::RenderEffect()
{
	eff.Render();
	if(fadeout && timer)
	{
		effCollapse.Render();
	}
	effShot.Render();
}

void Enemy::setTar(BYTE _tarID)
{
	tarID = _tarID;
}

void Enemy::setTake(DWORD _take)
{
	take = _take;
}

void Enemy::setLevelAim(int _level, float aimx, float aimy, int _aimangle)
{
	level = _level;
	aim.x = aimx;
	aim.y = aimy;
	aimangle = _aimangle;
}

void Enemy::valueSet(BYTE _playerindex, WORD _eID, float _x, float _y, int _angle, float _speed, BYTE _type, float _life, int _infitimer)
{
	playerindex	=	_playerindex;
	ID		=	_eID;
	x		=	_x;
	lastx	=	x;
	y		=	_y;
	speed	=	_speed;
	life	=	_life;
	angle	=	_angle;
	take	=	0;
	infitimer = _infitimer;

	timer	=	0;
	damagetimer = 0;
	maxlife	=	life;
	damagerate	=	1;
	exist	=	true;
	fadeout	=	false;
	able	=	true;
	damage	=	false;
	hscale	=	1.0f;
	vscale	=	1.0f;
	alpha	=	0xff;
	diffuse	=	0xffffff;
	ac		=	ENAC_NONE;
	acceladd	=	0;
	sendtime	=	0;
	sendsetID	=	0;
	tarID	=	0xff;
	activetimer = 0;
	activemaxtime = 0;

	actionflag = ENEMYACTION_NONE;
	storetimer = 0;

	xplus = speed * cost(angle);
	yplus = speed * sint(angle);
	lastspeed = speed;
	lastangle = angle;

	setLevelAim();
	ChangeType(_type);
}

void Enemy::ChangeType(BYTE _type)
{
	type = _type;
	enemyData * _enemydata = &(BResource::bres.enemydata[type]);
	faceindex = _enemydata->faceIndex;
	if (!_enemydata->rightPreFrame && !_enemydata->leftPreFrame && !_enemydata->rightFrame && !_enemydata->leftFrame)
	{
		bturnhead = true;
		headangle = angle;
	}
	else
	{
		bturnhead = false;
		headangle	=	0;
	}

	flag = _enemydata->flag;

	accel		=	0;

	for (int i=0; i<ENEMY_PARAMAX; i++)
	{
		fpara[i] = 0;
		ipara[i] = 0;
	}

	if (sprite)
	{
		SpriteItemManager::ChangeSprite(_enemydata->siid, sprite);
	}
	else
	{
		sprite = SpriteItemManager::CreateSprite(_enemydata->siid);
	}

	initFrameIndex();
	setFrame(ENEMY_FRAME_STAND);

	// TODO:
	eff.valueSet(_enemydata->effid, playerindex, *this);
	effShot.valueSet(_enemydata->shotEffid, playerindex, *this);
	effShot.Stop();
	effCollapse.valueSet(_enemydata->collapseEffid, playerindex, *this);
	effCollapse.Stop();
}

void Enemy::matchAction()
{
	switch(ac)
	{
	case ENAC_NONE:
		break;
	case ENAC_DIRECTSET_XYSOAOOO:
		//x，y，angle，speed
		//直接设置（需要连续设置）
		x = para_x;
		y = para_y;
		angle = para_angle;
		speed = para_speed;
		ac = ENAC_NONE;
		break;
	case ENAC_CHASEPLAYER_OOSFATOO:
		//作用时间，摩擦力，退出角度，退出速度
		//靠近主角
		if(timer < para_time)
		{
			angle = aMainAngle(Player::p[playerindex].x, Player::p[playerindex].y);
			speed *= para_friction;
		}
		else
		{
			angle = para_angle;
			speed = para_speed;
		}
		break;
	case ENAC_CHASEAIM_XYSOAOCO:
		//目标x，目标y，追击时间，退出角度，退出速度
		//向原方向前进、停止、撤离
		if (para_counter)
		{
			para_counter = chaseAim(para_x, para_y, para_counter);
		}
		else
		{
			angle = para_angle;
			speed = para_speed;
		}
		break;
	case ENAC_TURNANGLE_OOOOATOE:
		//起始时间，增加角度，终止时间
		//弧线行走
		if (timer >= para_time && timer < para_endtime)
		{
			angle += para_angle;
		}
		break;

	case ENAC_FADEOUT_OOOOOTOO:
		//消失时间
		//直接消失
		if (timer > para_time)
		{
			Fadeout();
		}
		break;

	case ENAC_REPOSITION_OOOOOOCO:
		//作用时间[计数器]
		//BOSS出场复位
		if(para_counter)
		{
			para_counter = chaseAim(M_GAMESQUARE_BOSSX_(playerindex), M_GAMESQUARE_BOSSY, para_counter);
		}
		else
		{
			ac = ENAC_NONE;
			speed = 0;
		}
		break;
	case ENAC_OVERPLAYER_XYOOOTCE:
		//作用时间[计数器]，目标x，目标y，更替周期，追击使用时间
		//在主角上方随机
		if(timer % para_time == 0)
		{
			para_counter = para_endtime;
			if(Player::p[playerindex].x > x)
				para_x = Player::p[playerindex].x + randtf(0, 60);
			else
				para_x = Player::p[playerindex].x - randtf(0, 60);
			float leftedge = M_GAMESQUARE_LEFT_(playerindex) + M_GAMESQUARE_EDGE;
			float rightedge = M_GAMESQUARE_RIGHT_(playerindex) - M_GAMESQUARE_EDGE;
			if(para_x < leftedge)
			{
				if(x <= leftedge + M_GAMESQUARE_EDGE/2)
					para_x = leftedge + M_GAMESQUARE_EDGE/2 + randtf(0, 50);
				else
					para_x = leftedge;
			}
			else if(para_x > rightedge)
			{
				if(x >= rightedge - M_GAMESQUARE_EDGE/2)
					para_x = rightedge - M_GAMESQUARE_EDGE/2 - randtf(0, 50);
				else
					para_x = rightedge;
			}
			para_y = randtf(-40, 40) + M_GAMESQUARE_BOSSY;
		}
		else if(para_counter)
		{
			para_counter = chaseAim(para_x, para_y, para_counter);
		}
		else
		{
			speed = 0;
		}
		break;
	}
}

void Enemy::setAction(WORD _ac, float _para_x, float _para_y, float _para_speed, float _para_friction, int _para_angle, int _para_time, int _para_counter, int _para_endtime)
{
	ac = _ac;
	para_x = _para_x;
	para_y = _para_y;
	para_speed = _para_speed;
	para_friction = _para_friction;
	para_angle = _para_angle;
	para_time = _para_time;
	para_counter = _para_counter;
	para_endtime = _para_endtime;
	if (ac == ENAC_FADEOUT_OOOOOTOO && para_time < 0)
	{
		Fadeout();
	}
}

void Enemy::updateFrame(BYTE frameenum, int usetimer /* = -1*/)
{
	if (usetimer == -1)
	{
		usetimer = timer;
	}
	if (frameenum != nowstate && (frameenum == ENEMY_FRAME_STAND || frameenum+1 != nowstate))
	{
		setFrame(frameenum);
		return;
	}
	if ((usetimer % ENEMY_ANIMATIONSPEED))
	{
		return;
	}
	enemyData * pdata = &(BResource::bres.enemydata[type]);
	frameoffset++;
	BYTE tbyte;
	switch (nowstate)
	{
	case ENEMY_FRAME_STAND:
		if (frameoffset >= pdata->standFrame)
		{
			setFrame(ENEMY_FRAME_STAND);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_STAND) + frameoffset);
		}
		if (flag & ENEMYFLAG_STANDSHAKE)
		{
			float thsx;
			float thsy;
			sprite->GetHotSpot(&thsx, &thsy);
			SpriteItemManager::SetSpriteHotSpot(sprite, thsx, sint(timer*512)*4.8f+thsy-2.4f);
		}
		break;
	case ENEMY_FRAME_RIGHTPRE:
		if (!pdata->rightPreFrame)
		{
			tbyte = pdata->leftPreFrame;
		}
		else
		{
			tbyte = pdata->rightPreFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_RIGHT);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_RIGHTPRE) + frameoffset);
		}
		break;
	case ENEMY_FRAME_RIGHT:
		if (!pdata->rightFrame)
		{
			tbyte = pdata->leftFrame;
		}
		else
		{
			tbyte = pdata->rightFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_RIGHT);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_RIGHT) + frameoffset);
		}
		break;
	case ENEMY_FRAME_LEFTPRE:
		if (!pdata->leftPreFrame)
		{
			tbyte = pdata->rightPreFrame;
		}
		else
		{
			tbyte = pdata->leftPreFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_LEFT);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_LEFTPRE) + frameoffset);
		}
		break;
	case ENEMY_FRAME_LEFT:
		if (!pdata->leftFrame)
		{
			tbyte = pdata->rightFrame;
		}
		else
		{
			tbyte = pdata->leftFrame;
		}
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_LEFT);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_LEFT) + frameoffset);
		}
		break;
	case ENEMY_FRAME_ATTACKPRE:
		tbyte = pdata->attackPreFrame;
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_ATTACK);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_ATTACKPRE) + frameoffset);
		}
		break;
	case ENEMY_FRAME_ATTACK:
		tbyte = pdata->attackFrame;
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_ATTACK);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_ATTACK) + frameoffset);
		}
		break;
	case ENEMY_FRAME_STOREPRE:
		tbyte = pdata->storePreFrame;
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_STORE);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_STOREPRE) + frameoffset);
		}
		break;
	case ENEMY_FRAME_STORE:
		tbyte = pdata->storeFrame;
		if (frameoffset >= tbyte)
		{
			setFrame(ENEMY_FRAME_STORE);
		}
		else
		{
			setIndexFrame(getFrameIndex(ENEMY_FRAME_STORE) + frameoffset);
		}
		break;
	}
}

void Enemy::updateFrameAsMove()
{
	if (bturnhead)
	{
		updateFrame(ENEMY_FRAME_STAND);
	}
	else
	{
		if(lastx - x > ENEMY_BOSSMOVELIMIT)
		{
			updateFrame(ENEMY_FRAME_LEFTPRE);
		}
		else if(x - lastx > ENEMY_BOSSMOVELIMIT)
		{
			updateFrame(ENEMY_FRAME_RIGHTPRE);
		}
		else
		{
			updateFrame(ENEMY_FRAME_STAND);
		}
	}
}

void Enemy::updateAction()
{
	enemyData * pdata = &(BResource::bres.enemydata[type]);
	if(!actionflag)
	{
		updateFrameAsMove();
	}
	if(actionflag & ENEMYACTION_ATTACK)
	{
		if (!pdata->attackFrame)
		{
			updateFrameAsMove();
		}
		else
		{
			updateFrame(ENEMY_FRAME_ATTACKPRE);
		}
		actionflag &= ~ENEMYACTION_ATTACK;
	}
	if(actionflag & ENEMYACTION_STORE)
	{
		if (!pdata->storeFrame)
		{
			updateFrameAsMove();
		}
		else
		{
			updateFrame(ENEMY_FRAME_STOREPRE);
		}
		storetimer++;

		if(storetimer == 1)
		{
		}
		else if(storetimer == 120)
		{
			storetimer = 0;
			actionflag &= ~ENEMYACTION_STORE;
		}
	}
}

void Enemy::initFrameIndex()
{
	enemyData * pdata = &(BResource::bres.enemydata[type]);
	int tfi = 0;
	frameindex[ENEMY_FRAME_STAND] = tfi;

	bool bhr = pdata->rightPreFrame || pdata->rightFrame;
	bool bhl = pdata->leftPreFrame || pdata->leftFrame;

	tfi += pdata->standFrame;
	frameindex[ENEMY_FRAME_RIGHTPRE] = tfi;
	if (bhr)
	{
		tfi += pdata->rightPreFrame;
	}
	else
	{
		tfi += pdata->leftPreFrame;
	}
	frameindex[ENEMY_FRAME_RIGHT] = tfi;
	if (bhr)
	{
		tfi += pdata->rightFrame;
	}
	else
	{
		tfi += pdata->leftFrame;
	}
	if (!bhr || !bhl)
	{
		tfi -= pdata->leftPreFrame + pdata->rightPreFrame + pdata->leftFrame + pdata->rightFrame;
	}
	frameindex[ENEMY_FRAME_LEFTPRE] = tfi;
	if (bhr)
	{
		tfi += pdata->rightPreFrame;
	}
	else
	{
		tfi += pdata->leftPreFrame;
	}
	frameindex[ENEMY_FRAME_LEFT] = tfi;

	if (bhr)
	{
		tfi += pdata->rightFrame;
	}
	else
	{
		tfi += pdata->leftFrame;
	}
	frameindex[ENEMY_FRAME_ATTACKPRE] = tfi;
	tfi += pdata->attackPreFrame;
	frameindex[ENEMY_FRAME_ATTACK] = tfi;
	tfi += pdata->attackFrame;
	frameindex[ENEMY_FRAME_STOREPRE] = tfi;
	tfi += pdata->storePreFrame;
	frameindex[ENEMY_FRAME_STORE] = tfi;
	tfi += pdata->storeFrame;
}

BYTE Enemy::getFrameIndex(BYTE frameenum)
{
	flipx = false;
	enemyData * pdata = &(BResource::bres.enemydata[type]);
	if ((frameenum == ENEMY_FRAME_RIGHTPRE || frameenum == ENEMY_FRAME_RIGHT) && (!pdata->rightPreFrame) ||
		(frameenum == ENEMY_FRAME_LEFTPRE || frameenum == ENEMY_FRAME_LEFT) && (!pdata->leftPreFrame))
	{
		flipx = true;
	}
	return frameindex[frameenum];
}

void Enemy::setFrame(BYTE frameenum)
{
	frameoffset = 0;
	setIndexFrame(getFrameIndex(frameenum));
	nowstate = frameenum;
}

void Enemy::setIndexFrame(BYTE index)
{
	enemyData * pdata = &(BResource::bres.enemydata[type]);
	SpriteItemManager::ChangeSprite(pdata->siid+index, sprite);
//	sprite->SetFlip(flipx, false);
	SpriteItemManager::SetSpriteFlip(sprite, flipx);
}

void Enemy::GetCollisionRect(float * w, float * h)
{
	*w = BResource::bres.enemydata[type].collision_w;
	*h = BResource::bres.enemydata[type].collision_h;
}

bool Enemy::CostLife(float power)
{
	if (infitimer)
	{
		return false;
	}
	life -= power * damagerate;
	damage = true;
	if (life < 0)
	{
		return true;
	}
	return false;
}

bool Enemy::isInRect(float aimx, float aimy, float r, float w, float h, int nextstep/* =0 */)
{
	WORD infinmaxset = BResource::bres.playerdata[Player::p[playerindex].nowID].infinmaxset;
	if (infinmaxset)
	{
		BYTE nmaxset = BResource::bres.enemydata[type].nmaxset;
		for (int i=0; i<4; i++)
		{
			infinmaxset>>(i*4);
			if (!infinmaxset)
			{
				break;
			}
			if ((infinmaxset&0x000f) == nmaxset)
			{
				return false;
			}
		}
	}

	float _x = x;
	float _y = y;
	float _r = r;
	if (nextstep)
	{
		_x += xplus * nextstep;
		_y += yplus * nextstep;
		_r += accel;
		if (ac != ENAC_NONE && ac != ENAC_FADEOUT_OOOOOTOO)
		{
			_r += speed;
		}
		if (sendsetID)
		{
			h += 4;
		}
	}
	return CheckCollisionSquare(_x, _y, aimx, aimy, w, h, _r);
}

void Enemy::actionInStop()
{
	if (!fadeout)
	{
		DoShot();
		DoActivate();
	}
}

void Enemy::DoShot()
{
	float tw;
	float th;
	GetCollisionRect(&tw, &th);
	if (!tw && !th)
	{
		return;
	}

	for (list<EventZone>::iterator it=EventZone::ezone[playerindex].begin(); it!=EventZone::ezone[playerindex].end(); it++)
	{
		if (it->timer < 0)
		{
			continue;
		}
		if ((it->type & EVENTZONE_TYPE_ENEMYDAMAGE))
		{
			if (it->type & EVENTZONE_TYPE_ENEMYBLAST)
			{
				if (!(flag & ENEMYFLAG_BLASTSHOTABLE))
				{
					continue;
				}
			}
			else
			{
				if (!(flag & ENEMYFLAG_EZONESHOTABLE))
				{
					continue;
				}
			}
			if (it->isInRect(x, y, 0, tw, th))
			{
				if ( CostLife(it->power * BResource::bres.enemydata[type].blastdamagerate) )
				{
					if (it->type & EVENTZONE_TYPE_NOSEND)
					{
						sendsetID = 0;
					}
					if (sendsetID)
					{
						ForceActive();
					}
				}

			}
		}
	}

	if (life >= 0 && (flag & ENEMYFLAG_PBSHOTABLE))
	{
		PlayerBullet::CheckShoot(playerindex, this, x, y ,tw, th);
		/*
		if (life < 0)
		{
			Player::p[playerindex].DoPlayerBulletHit(-1);
		}
		*/

	}

	if(!damage && life < maxlife / 5 && timer%8<4)
	{
		SE::push(SE_ENEMY_DAMAGE_1, x);
	}

	if(damage && !damagetimer)
	{
		damagetimer++;
	}
	else if(damagetimer > 0)
	{
		if(damagetimer < 8)
			damagetimer++;
		else
			damagetimer = 0;
		if(damagetimer > 0 && damagetimer % 8 < 4)
		{
			alpha = 0x7f;
			diffuse = 0xb40000;
			effShot.Fire();

			if(life < maxlife / 5)
			{
				SE::push(SE_ENEMY_DAMAGE_2, x);
			}
			else
			{
				SE::push(SE_ENEMY_DAMAGE_1, x);
			}
		}
		else
		{
			alpha = 0xff;
			diffuse = 0xffffff;
			effShot.Stop();
		}
	}
	if(life < 0)
	{
		DWORD _index = en[playerindex].getIndex();
		Scripter::scr.Execute(SCR_EDEF, ID|(playerindex<<16), SCRIPT_CON_POST);
		en[playerindex].toIndex(_index);

		if (life < 0)
		{
			Fadeout();
		}
	}

}

void Enemy::ForceActive()
{
	if (!checkActive())
	{
		Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_PLAYERDRAINCHECK, playerindex);
	}
}

bool Enemy::DoActivate()
{
	if (!enaz[playerindex].size())
	{
		return false;
	}
	if (!checkActive() && Player::p[playerindex].bDrain)
	{
		float rori = (BResource::bres.enemydata[type].collision_w + BResource::bres.enemydata[type].collision_h) / 4;
		if (CheckENAZ(playerindex, x, y, rori))
		{
			ForceActive();
			return true;
		}
	}
	return false;
}

bool Enemy::CheckENAZ(BYTE playerindex, float x, float y, float rori)
{
	bool haveor = false;
	bool orcheck = false;
	if (!enaz[playerindex].size())
	{
		return false;
	}
	for (list<EnemyActivationZone>::iterator it=enaz[playerindex].begin(); it!=enaz[playerindex].end(); it++)
	{
		bool checkret = true;
		switch ((it->flag) & ENAZTYPEMASK)
		{
		case ENAZTYPE_CIRCLE:
			checkret = BObject::CheckCollisionBigCircle(x, y, it->x, it->y, it->rPrep+rori);
			break;
		case ENAZTYPE_ELLIPSE:
			checkret = BObject::CheckCollisionEllipse(x, y, it->x, it->y, it->rPrep, it->rParal, it->angle, rori);
			break;
		case ENAZTYPE_RECT:
			checkret = BObject::CheckCollisionRect(x, y, it->x, it->y, it->rPrep, it->rParal, it->angle, rori);
			break;
		case ENAZTYPE_RIGHTANGLED:
			checkret = BObject::CheckCollisionRightAngled(x, y, it->x, it->y, it->rPrep, it->rParal, it->angle, rori);
			break;
		}
		switch ((it->flag) & ENAZOPMASK)
		{
		case ENAZOP_AND:
			if (!checkret || haveor && !orcheck)
			{
				return false;
			}
			haveor = false;
			break;
		case ENAZOP_OR:
			if (!orcheck && checkret)
			{
				orcheck = true;
			}
			haveor = true;
			break;
		case ENAZOP_NOTAND:
			if (checkret || haveor && !orcheck)
			{
				return false;
			}
			haveor = false;
			break;
		case ENAZOP_NOTOR:
			if (!orcheck && !checkret)
			{
				orcheck = true;
			}
			haveor = true;
			break;
		}
	}
	return true;
}

bool Enemy::checkActive()
{
	if (!sendsetID || activetimer)
	{
		return true;
	}
	return false;
}

void Enemy::AddSendInfo(BYTE _sendsetID, BYTE _sendtime, float _accel, float _acceladd)
{
	sendsetID = _sendsetID;
	sendtime = _sendtime;
	accel = _accel;
	acceladd = _acceladd;
}

void Enemy::Fadeout()
{
	if (!fadeout)
	{
		if (type < PLAYERTYPEMAX)
		{
			SE::push(SE_BOSS_DEAD, x);
		}
		else if (life <= 0)
		{
			SE::push(SE_ENEMY_DEAD, x);
		}
	}
	fadeout = true;
	timer = 0;
}

void Enemy::action()
{
	if (ac == ENAC_DELAY_OOOOOTOO)
	{
		para_time--;
		if (para_time <= 0)
		{
			setAction(ENAC_NONE);
		}
		return;
	}
	timer++;

	if (timer < 60 || activetimer)
	{
		if (accel)
		{
			speed += accel;
		}
	}

	if(infitimer)
	{
		infitimer--;
	}

	effShot.MoveTo(x, y);
	effShot.action();
	eff.MoveTo(x, y);
	eff.action();

	float tw;
	float th;
	GetCollisionRect(&tw, &th);

	if(!fadeout)
	{
		if((Chat::chatitem.IsChatting() || (BossInfo::flag >= BOSSINFO_COLLAPSE)))
		{
			life = 0;
			Fadeout();
		}

		if(ID)
		{
			DWORD _index = en[playerindex].getIndex();
			Scripter::scr.Execute(SCR_EDEF, ID|(playerindex<<16), timer);
			en[playerindex].toIndex(_index);
		}

		if (!Player::p[playerindex].bInfi && !(flag & ENEMYFLAG_NOPLAYERCOLLISION))
		{
			if ((tw || th))
			{
				if (isInRect(Player::p[playerindex].x, Player::p[playerindex].y, Player::p[playerindex].r, tw, th))
				{
					Player::p[playerindex].DoShot();
				}
			}
		}

		matchAction();
//		updateMove();
		x += xplus;
		y += yplus;
		updateAction();

		if (speed != lastspeed || angle != lastangle)
		{
			xplus = speed * cost(angle);
			yplus = speed * sint(angle);
			lastspeed = speed;
			lastangle = angle;
		}

		lastx = x;

		if(tarID != 0xff)
		{
			Target::SetValue(tarID, x, y);
		}

		/*
		if(BossInfo::flag)
		{
			int txdiff = fabsf(Player::p[playerindex].x - x);
			if(txdiff < ENEMY_BOSSX_FADERANGE)
				FrontDisplay::fdisp.info.enemyx->SetColor(((0x40 + txdiff*2) << 24) | 0xffffff);
			else
				FrontDisplay::fdisp.info.enemyx->SetColor(0x80ffffff);
		}
		*/

		DoActivate();

		if (activetimer)
		{
			activetimer++;
			if (activetimer >= activemaxtime)
			{
				Scripter::scr.Execute(SCR_EVENT, SCR_EVENT_ACTIVEGHOSTOVER, playerindex);
				exist = false;
				timer = 0;
			}
			else if ((int)activetimer * 5 >= (int)activemaxtime * 4)
			{
				if (activetimer % 8 < 4)
				{
					alpha = 0x7f;
					diffuse = 0xb40000;
				}
				else
				{
					alpha = 0xff;
					diffuse = 0xffffff;
				}
				eff.SetColorMask((alpha<<24)|diffuse);
			}
		}

		if (bturnhead)
		{
			headangle = angle;
		}

		DoShot();
//		if(x > M_DELETECLIENT_RIGHT_(playerindex) || x < M_DELETECLIENT_LEFT_(playerindex) || y > M_DELETECLIENT_BOTTOM || y < M_DELETECLIENT_TOP)
		if(x > _ENEMYDELETE_RIGHT_(playerindex) || x < _ENEMYDELETE_LEFT_(playerindex) || y > _ENEMYDELETE_BOTTOM || y < _ENEMYDELETE_TOP)
			exist = false;
	}
	else
	{
		if(timer == 1)
		{
			effShot.Stop();
			// TODO:
			effCollapse.MoveTo(x, y, 0, true);
			effCollapse.Fire();
			if (life <= 0)
			{
				giveItem(playerindex);
			}

			if (life < 0)
			{
				Player::p[playerindex].DoEnemyCollapse(x, y, type);
			}
			if (BResource::bres.enemydata[type].spellpoint)
			{
				int tscore = Player::p[playerindex].nSpellPoint;
				ScoreDisplay _item;
				if (tscore < PLAYER_NSPELLPOINTMAX)
				{
					hge->Math_itoa(tscore, _item.cScore);
				}
				else
				{
					strcpy(_item.cScore, "b");
				}
				_item.timer = 0;
				_item.x = x;
				_item.y = y;
				if(tscore >= 300000)
				{
					_item.yellow = true;
				}
				else
				{
					_item.yellow = false;
				}
				scoredisplay[playerindex].push_back(_item);
			}

			BYTE blastmaxtime;
			float blastr;
			float blastpower;
			GetBlastInfo(&blastmaxtime, &blastr, &blastpower);
			if (blastmaxtime && blastr > 0)
			{
				EventZone::Build(EVENTZONE_TYPE_SENDBULLET|EVENTZONE_CHECKTYPE_CIRCLE, playerindex, x, y, blastmaxtime, blastr);
//				EventZone::Build(EVENTZONE_TYPE_ENEMYDAMAGE, playerindex, x, y, blastmaxtime, 0, blastpower, EVENTZONE_EVENT_NULL, blastr/blastmaxtime);
			}

			if (sendsetID)
			{
				sendtime++;
				if (sendtime < 3)
				{
					SendGhost(playerindex, x, y, sendsetID, &sendtime, &acceladd);
				}
			}

		}
		
		else if (timer == 8)
		{
			BYTE blastmaxtime;
			float blastr;
			float blastpower;
			GetBlastInfo(&blastmaxtime, &blastr, &blastpower);
			if (blastmaxtime && blastr > 0)
			{
				EventZone::Build(EVENTZONE_TYPE_ENEMYDAMAGE|EVENTZONE_TYPE_ENEMYBLAST|EVENTZONE_CHECKTYPE_CIRCLE, playerindex, x, y, blastmaxtime, 0, 0, blastpower, EVENTZONE_EVENT_NULL, blastr/blastmaxtime);
			}
		}
		
		else if(timer == 32)
		{
			eff.Stop();
			effCollapse.Stop();
			exist = false;
		}
		effCollapse.action();

		vscale	=	(32 - timer) * 0.03225f;
		alpha	=	(BYTE)((32 - timer) * 8);
	}

	damage = false;
	able = exist && !fadeout && (tw || th);
}

void Enemy::GetBlastInfo(BYTE * maxtime/* =NULL */, float * r/* =NULL */, float * power/* =NULL */)
{
	if (maxtime)
	{
		*maxtime = BResource::bres.enemydata[type].blastmaxtime;
	}
	if (r)
	{
		*r = BResource::bres.enemydata[type].blastr;
	}
	if (power)
	{
		*power = BResource::bres.enemydata[type].blastpower;
	}
}

void Enemy::SetActiveInfo(BYTE _activemaxtime, WORD _eID, BYTE _type, int _angle, float _accelspeed, float _damagerate)
{
	if (!exist || fadeout)
	{
		return;
	}
	activemaxtime = _activemaxtime;
	ID = _eID;
	ChangeType(_type);
	angle = _angle;
	speed = 0;
	accel = _accelspeed;
	damagerate = _damagerate;
	setAction();
	updateAction();
	activetimer = 1;
}

void Enemy::giveItem(BYTE playerindex)
{
	if (!take)
	{
		return;
	}
//	bool first = true;
	float aimx;
	float aimy;

	float tempx = x;
	float tempy = y;

	y -= randtf(0, 30);
	if(x > PL_MOVABLE_RIGHT_(playerindex))
		x = PL_MOVABLE_RIGHT_(playerindex);
	else if(x < PL_MOVABLE_LEFT_(playerindex))
		x = PL_MOVABLE_LEFT_(playerindex);

	for(int i=0;i<ITEMTYPEMAX;i++)
	{
		for(int j=0;j<(int)((take>>(i*4))&0xf);j++)
		{
			/*
			if(!first)
			{
				aimx = (float)((x + randt()%80 - 40));
				if(aimx > 417)
					aimx = 417;
				else if(aimx < 23)
					aimx = 23;
				aimy = (float)(randt()%80 - 240 + y);
				Item::Build(playerindex, i, x, y, false, 18000 + rMainAngle(aimx, aimy), -sqrt(2 * 0.1f * DIST(x, y, aimx, aimy)));
			}
			else
			{
			*/
			Item::Build(playerindex, i, x, y);
			//}
//			first = false;
		}
	}
	x = tempx;
	y = tempy;
}
