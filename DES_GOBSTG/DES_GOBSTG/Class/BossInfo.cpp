#include "../header/BossInfo.h"
#include "../header/Enemy.h"
#include "../header/Player.h"
#include "../header/SE.h"
#include "../header/EffectSp.h"
#include "../header/Data.h"
#include "../header/Process.h"
#include "../header/BGLayer.h"
#include "../header/Fontsys.h"
#include "../header/Item.h"
#include "../header/BResource.h"
#include "../header/DataConnector.h"
#include "../header/Scripter.h"
#include "../header/FrontDisplay.h"
#include "../header/Bullet.h"
#include "../header/BResource.h"

BossInfo BossInfo::bossinfo;
int BossInfo::sno;
int BossInfo::turntoscene;
bool BossInfo::failed;
bool BossInfo::allover;
BYTE BossInfo::flag;
BYTE BossInfo::spellflag;
Fontsys BossInfo::fsspellname;

bool BossInfo::Init()
{
	Release();

	allover = false;

	return true;
}

void BossInfo::Clear()
{
	turntoscene = S0;
	spellflag = BISF_NONE;
	flag = 0;
}

//bossinfo
bool BossInfo::Fill(int _sno)
{
/*
	spellData * item = &(BResource::bres.spelldata[_sno]);
	sno = _sno;
	spellflag = item->spellflag;
	strcpy(spellname, item->spellname);
	strcpy(enemyname, Data::data.getEnemyName(item->userID));
	strcpy(enemyename, Data::data.getEnemyEName(item->userID));
	limit = item->timelimit;
	remain = item->remain;
	turntoscene = item->turntoscene;*/

	return true;
}

bool BossInfo::isSpell()
{
	return flag && !(spellflag & BISF_NOTSPELL);
}

void BossInfo::bossUp()
{
/*
//	Fill(mp.scene);

	failed	= false;

	flag = BOSSINFO_UP | BOSSINFO_ENABLE;
	timer = 0;
	itemstack = 0;

	if(!(spellflag & BISF_NOTSPELL))
	{
//		BGLayer::ubg[UBGID_BGMASK].SetFlag(BG_WHITEFLASH, BGMT_FLASH);
//		Enemy::actionflag[ENEMY_MAINBOSSINDEX] = BOSS_SPELLUP;
		fsspellname.SignUp(spellname, FrontDisplay::fdisp.info.smallfont);
//		get = DataConnector::nGet();
//		meet = DataConnector::nMeet() - 1;
//		if(meet < 0)
//			meet = 0;
	}*/

}

void BossInfo::Release()
{
	flag = 0;
	spellflag = BISF_NONE;
	failed = false;
}

void BossInfo::quit()
{
/*
		if (flag & BOSSINFO_COLLAPSE)
		{
		}
		else if (flag & BOSSINFO_TIMEOVER)
		{
			failed = true;
		}
		/ *
		if(!(spellflag & BISF_NOTSPELL) && mp.spellmode)
		{
			BGLayer::ubg[UBGID_BGMASK].SetFlag(BG_WHITEOUT, BGMT_OUT);
		}
		* /
		if(remain)
		{
			Enemy::en[ENEMY_MAINBOSSINDEX].alpha = 0xff;
		}
	
		scr.Execute(SCR_STAGE, sno, SCRIPT_CON_POST);
		fsspellname.SignOff();
	
		spellflag = BISF_NONE;
		flag = 0;
		exist = false;
	
		allover = false;
		mp.frameskip = M_DEFAULT_FRAMESKIP;*/
	
}

bool BossInfo::action()
{
/*
		exist = true;
	
		if(flag < BOSSINFO_COLLAPSE)
		{
			if (Enemy::en[ENEMY_MAINBOSSINDEX].able)
			{
				if(timer == limit * 60)
				{
					flag |= BOSSINFO_TIMEOVER;
					timer = 0;
				}
			}
			else
			{
				flag |= BOSSINFO_COLLAPSE;
				if(!(spellflag & BISF_NOTSPELL) && !failed)
				{
					if(spellflag & BISF_WAIT)
						timer = limit * 30;
					itemstack = (limit * 60 - timer) / 15;
				}
				timer = 0;
			}
		}
		timer++;
		FrontDisplay::fdisp.BossAction();
	
		if(flag & BOSSINFO_UP)
		{
			if(timer == 160)
				flag &= ~BOSSINFO_UP;
		}
		else if(flag & BOSSINFO_COLLAPSE)
		{
			if(timer == 1)
			{
				for (int i=0; i<M_PL_MATCHMAXPLAYER; i++)
				{
					Player::p[i].SetInfi(PLAYERINFI_OVER, 160);
				}
				scr.Execute(SCR_STAGE, sno, SCRIPT_CON_QUIT);
	
				if(remain)
				{
					Enemy::en[ENEMY_MAINBOSSINDEX].alpha = 0x7f;
					Enemy::en[ENEMY_MAINBOSSINDEX].defrate = 1.0f;
					Enemy::en[ENEMY_MAINBOSSINDEX].ac = 0;
					Enemy::en[ENEMY_MAINBOSSINDEX].speed = 0;
				}
			}
			else if(timer == 160)
			{
				quit();
				return true;
			}
			if(Enemy::en[ENEMY_MAINBOSSINDEX].timer == 16 && Enemy::en[ENEMY_MAINBOSSINDEX].life < 0 / *&& !mp.spellmode* / && remain)
			{
				Enemy::en[ENEMY_MAINBOSSINDEX].exist = true;
				Enemy::en[ENEMY_MAINBOSSINDEX].fadeout = false;
				Enemy::en[ENEMY_MAINBOSSINDEX].life = 0;
				Enemy::en[ENEMY_MAINBOSSINDEX].timer = 0;
				Enemy::en[ENEMY_MAINBOSSINDEX].alpha = 0xff;
			}
		}
		else if(flag & BOSSINFO_TIMEOVER)
		{
			if(timer == 1)
			{
				scr.Execute(SCR_STAGE, sno, SCRIPT_CON_QUIT);
				SE::push(SE_BOSS_TIMEUP);
				if(remain)
				{
					Enemy::en[ENEMY_MAINBOSSINDEX].defrate = 1.0f;
					Enemy::en[ENEMY_MAINBOSSINDEX].alpha = 0x7f;
				}
				if(!(spellflag & BISF_WAIT))
					failed = true;
				/ *
				if(!failed && !(spellflag & BISF_NOTSPELL) && (spellflag & BISF_WAIT))
				{
					Player::p[0].getspell[Player::p[0].ncGet] = mp.scene;
					Player::p[0].ncGet++;
				}
				* /
				if(spellflag & BISF_NOTSPELL)
				{
					timer = 100;
				}
				// TODO:
	//			Bullet::IzeBuild(0, BULLETIZE_FADEOUT, Enemy::en[ENEMY_MAINBOSSINDEX].x, Enemy::en[ENEMY_MAINBOSSINDEX].y);
				if((spellflag & BISF_WAIT) || !remain)
				{
					Enemy::en[ENEMY_MAINBOSSINDEX].life = -1;
				}
	
				if(turntoscene - SCLEAR > S1/ * && !mp.spellmode* /)
				{
					allover = true;
				}
			}
			if(timer == 160)
			{
				quit();
				return true;
			}
			if(Enemy::en[ENEMY_MAINBOSSINDEX].timer == 16 && Enemy::en[ENEMY_MAINBOSSINDEX].life < 0/ * && !mp.spellmode* / && remain)
			{
				Enemy::en[ENEMY_MAINBOSSINDEX].exist = true;
				Enemy::en[ENEMY_MAINBOSSINDEX].fadeout = false;
				Enemy::en[ENEMY_MAINBOSSINDEX].life = 0;
				Enemy::en[ENEMY_MAINBOSSINDEX].timer = 0;
				Enemy::en[ENEMY_MAINBOSSINDEX].alpha = 0xff;
			}
		}
		if(!(spellflag & BISF_NOTSPELL) && flag < BOSSINFO_COLLAPSE)
		{
			if(!failed && !(spellflag & BISF_WAIT))
			{
			}
			else if(failed)
			{
			}
			else if(timer == limit * 60 - 1)
			{
				Enemy::en[ENEMY_MAINBOSSINDEX].life = -1;
			}
		}
		if(flag < BOSSINFO_COLLAPSE)
		{
			if(timer >= (limit-10) * 60 && timer % 60 == 0)
				SE::push(SE_BOSS_TIMEOUT);
			if(timer >= (limit-3) * 60 && timer % 60 == 10)
				SE::push(SE_BOSS_TIMEOUT);
		}
		else if(!(spellflag & BISF_NOTSPELL) && !failed)
		{
			if(timer < 90)
			{
				int tthrow = itemstack / (90-timer);
				float tr;
				float tangle;
				if(timer <= 30)
				{
					tr = timer + 40;
					tangle = timer * 1800;
				}
				else if(timer <= 60)
				{
					tr = timer + 20;
					tangle = -timer * 1800 + 12000;
				}
				else
				{
					tr = timer;
					tangle = timer * 1800 - 12000;
				}
				float tx = Enemy::en[ENEMY_MAINBOSSINDEX].x + tr * cost(tangle);
				float ty = Enemy::en[ENEMY_MAINBOSSINDEX].y + tr * sint(tangle);
	
				FrontDisplay::fdisp.BossMoveItemEffect(tx, ty);
	//			effItem.MoveTo(tx, ty);
	
				for(int i=0;i<tthrow;i++)
				{
					// TODO:
					Item::Build(0, ITEM_SMALLFAITH, tx+randt()%10-5, ty+randt()%10-5, true);
				}
				itemstack -= tthrow;
			}
		}*/
	
	return false;
}
