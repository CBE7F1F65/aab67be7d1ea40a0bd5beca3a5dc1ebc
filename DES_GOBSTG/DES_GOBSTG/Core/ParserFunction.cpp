#include "../Header/Scripter.h"
//#include "../Header/processPrep.h"

void * Scripter::Value(vector<Script>::iterator * p, int i, BYTE force)
{
	/*
		if((*p)->type & SCR_TOKEN_VALUE)
			{
				if(force & SCR_FORCE_INT)
				{
					d[i].bfloat = false;
					if((*p)->type & SCR_TOKEN_FLOAT)
					{
						idesc[i] = (int)CFLOAT(&((*p)->value));
					}
					else
					{
						idesc[i] = (int)CINT(&((*p)->value));
					}
				}
				else if(force & SCR_FORCE_FLOAT)
				{
					d[i].bfloat = true;
					if((*p)->type & SCR_TOKEN_FLOAT)
					{
						fdesc[i] = (float)CFLOAT(&((*p)->value));
					}
					else
					{
						fdesc[i] = (float)CINT(&((*p)->value));
					}
				}
				else
				{
					if((*p)->type & SCR_TOKEN_FLOAT)
					{
						d[i].bfloat = true;
						fdesc[i] = CFLOAT(&((*p)->value));
					}
					else
					{
						d[i].bfloat = false;
						idesc[i] = CINT(&((*p)->value));
					}
				}
			}
			else if((*p)->type & SCR_TOKEN_HANDLE)
			{
				d[i].bfloat = false;
				idesc[i] = (*p)->value;
			}
			else if((*p)->type & SCR_TOKEN_VARIABLE)
			{
				int _tdi = (*p)->value;
				d[i].bfloat = d[_tdi].bfloat;
				if(d[i].bfloat)
					fdesc[i] = CFLOAT(d[_tdi].value);
				else
					idesc[i] = CINT(d[_tdi].value);
			}
			else
			{
				int _tdi;
				float _tdf;
		
				DWORD nowval = (*p)->value;
				switch(nowval & SCRKWMASK_CLASS)
				{
					/ ************************************************************************ /
					/ * AttackObject                                                         * /
					/ ************************************************************************ /
				case SCRKW_CLASS_ATTACKOBJECT:
					switch (nowval)
					{
					case SCR_BUI:
						idesc[i] = Bullet::index;
						d[i].bfloat = false;
						break;
					case SCR_BUANGLE:
						idesc[i] = bu[Bullet::index].angle;
						d[i].bfloat = false;
						break;
					case SCR_BUSPEED:
						fdesc[i] = bu[Bullet::index].speed;
						d[i].bfloat = true;
						break;
					case SCR_BUX:
						fdesc[i] = bu[Bullet::index].x;
						d[i].bfloat = true;
						break;
					case SCR_BUY:
						fdesc[i] = bu[Bullet::index].y;
						d[i].bfloat = true;
						break;
					case SCR_BUTIMER:
						idesc[i] = bu[Bullet::index].timer;
						d[i].bfloat = false;
						break;
					case SCR_BUCANCELABLE:
						idesc[i] = bu[Bullet::index].cancelable;
						d[i].bfloat = false;
						break;
					case SCR_BUHAVEGRAY:
						idesc[i] = (int)bu[Bullet::index].HaveGray();
						d[i].bfloat = false;
						break;
		
					case SCR_BEI:
						idesc[i] = Beam::index;
						d[i].bfloat = false;
						break;
					case SCR_BEANGLE:
						idesc[i] = be[Beam::index].angle;
						d[i].bfloat = false;
						break;
					case SCR_BESPEED:
						fdesc[i] = be[Beam::index].speed;
						d[i].bfloat = true;
						break;
					case SCR_BEX:
						fdesc[i] = be[Beam::index].x;
						d[i].bfloat = true;
						break;
					case SCR_BEY:
						fdesc[i] = be[Beam::index].y;
						d[i].bfloat = true;
						break;
					case SCR_BETIMER:
						idesc[i] = be[Beam::index].timer;
						d[i].bfloat = false;
						break;
					case SCR_BEHOLDTAR:
						idesc[i] = be[Beam::index].holdtar;
						d[i].bfloat = false;
						break;
					case SCR_BEPINTAR:
						idesc[i] = be[Beam::index].pintar;
						d[i].bfloat = false;
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Ghost                                                                * /
					/ ************************************************************************ /
				case SCRKW_CLASS_GHOST:
					switch (nowval)
					{
					case SCR_GHX:
						fdesc[i] = gh[Ghost::index].x;
						d[i].bfloat = true;
						break;
					case SCR_GHY:
						fdesc[i] = gh[Ghost::index].y;
						d[i].bfloat = true;
						break;
					case SCR_GHTIMER:
						idesc[i] = gh[Ghost::index].timer;
						d[i].bfloat = false;
						break;
					case SCR_GHI:
						idesc[i] = Ghost::index;
						d[i].bfloat = false;
						break;
					case SCR_GHANGLE:
						idesc[i] = gh[Ghost::index].angle;
						d[i].bfloat = false;
						break;
					case SCR_GHSPEED:
						fdesc[i] = gh[Ghost::index].speed;
						d[i].bfloat = true;
						break;
					case SCR_GHAMAP:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = gh[Ghost::index].aMainAngle(Player::p[0], _tdi);
						d[i].bfloat = false;
						break;
					case SCR_GHRMAP:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = gh[Ghost::index].rMainAngle(Player::p[0], _tdi);
						d[i].bfloat = false;
						break;
					case SCR_GHAIMX:
						fdesc[i] = gh[Ghost::index].aim.x;
						d[i].bfloat = true;
						break;
					case SCR_GHAIMY:
						fdesc[i] = gh[Ghost::index].aim.y;
						d[i].bfloat = true;
						break;
					case SCR_GHLIFE:
						fdesc[i] = gh[Ghost::index].life;
						d[i].bfloat = true;
						break;
					case SCR_GHAC:
						idesc[i] = gh[Ghost::index].ac;
						d[i].bfloat = false;
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Enemy                                                                * /
					/ ************************************************************************ /
				case SCRKW_CLASS_ENEMY:
					switch (nowval)
					{
					case SCR_ENX:
						fdesc[i] = en[Enemy::index].x;
						d[i].bfloat = true;
						break;
					case SCR_ENY:
						fdesc[i] = en[Enemy::index].y;
						d[i].bfloat = true;
						break;
					case SCR_ENTIMER:
						idesc[i] = en[Enemy::index].timer;
						d[i].bfloat = false;
						break;
					case SCR_ENI:
						idesc[i] = Enemy::index;
						d[i].bfloat = false;
						break;
					case SCR_ENANGLE:
						idesc[i] = en[Enemy::index].angle;
						d[i].bfloat = false;
						break;
					case SCR_ENSPEED:
						fdesc[i] = en[Enemy::index].speed;
						d[i].bfloat = true;
						break;
					case SCR_ENAMAP:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = en[Enemy::index].aMainAngle(Player::p[0], _tdi);
						d[i].bfloat = false;
						break;
					case SCR_ENRMAP:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = en[Enemy::index].rMainAngle(Player::p[0], _tdi);
						d[i].bfloat = false;
						break;
					case SCR_ENAIMX:
						fdesc[i] = en[Enemy::index].aim.x;
						d[i].bfloat = true;
						break;
					case SCR_ENAIMY:
						fdesc[i] = en[Enemy::index].aim.y;
						d[i].bfloat = true;
						break;
					case SCR_ENLIFE:
						fdesc[i] = en[Enemy::index].life;
						d[i].bfloat = true;
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Math                                                                 * /
					/ ************************************************************************ /
				case SCRKW_CLASS_MATH:
					switch (nowval)
					{
					case SCR_RAND:
						idesc[i] = randt();
						d[i].bfloat = false;
						break;
					case SCR_RANDR:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = randt() % (_tdi * 2 + 1) - _tdi;
						d[i].bfloat = false;
						break;
					case SCR_SEED:
						idesc[i] = mp.seed;
						d[i].bfloat = false;
						break;
					case SCR_SINA:
						++(*p);
						fdesc[i] = sint(CINT(Value(&(*p), i, 0)));
						d[i].bfloat = true;
						break;
					case SCR_COSA:
						++(*p);
						fdesc[i] = cost(CINT(Value(&(*p), i, 0)));
						d[i].bfloat = true;
						break;
					case SCR_TANA:
						++(*p);
						fdesc[i] = tant(CINT(Value(&(*p), i, 0)));
						d[i].bfloat = true;
						break;
					case SCR_ASIN2:
						++(*p);
						_tdf = CFLOAT((Value(&(*p), i, 0)));
						++(*p);
						idesc[i] = asin2t(_tdf, CFLOAT(Value(&(*p), i, 0)));
						d[i].bfloat = false;
						break;
					case SCR_ACOS2:
						++(*p);
						_tdf = CFLOAT((Value(&(*p), i, 0)));
						++(*p);
						idesc[i] = acos2t(_tdf, CFLOAT(Value(&(*p), i, 0)));
						d[i].bfloat = false;
						break;
					case SCR_ATAN2:
						++(*p);
						_tdf = CFLOAT((Value(&(*p), i, 0)));
						++(*p);
						idesc[i] = atan2t(_tdf, CFLOAT(Value(&(*p), i, 0)));
						d[i].bfloat = false;
						break;
					case SCR_SQRT:
						++(*p);
						fdesc[i] = sqrtf(CFLOAT((Value(&(*p), i, 0))));
						d[i].bfloat = true;
						break;
					case SCR_SIGN:
						++(*p);
						idesc[i] = SIGN(CINT(Value(&(*p), i, 0)));
						d[i].bfloat = false;
						break;
					case SCR_ROLL:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						++(*p);
						idesc[i] = ROLL(_tdi, CINT(Value(&(*p), i, 0)));
						d[i].bfloat = false;
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Other                                                                * /
					/ ************************************************************************ /
				case SCRKW_CLASS_OTHER:
					switch (nowval)
					{
					case SCR_D:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						if(d[_tdi].bfloat)
							fdesc[i] = CAST(d[_tdi]);
						else
							idesc[i] = CAST(d[_tdi]);
						d[i].bfloat = d[_tdi].bfloat;
						break;
					case SCR_DU:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = UCAST(d[_tdi]);
						d[i].bfloat = false;
						break;
					case SCR_TX:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						fdesc[i] = tar[_tdi].x;
						d[i].bfloat = true;
						break;
					case SCR_TY:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						fdesc[i] = tar[_tdi].y;
						d[i].bfloat = true;
						break;
					case SCR_TIME:
						idesc[i] = time;
						d[i].bfloat = false;
						break;
					case SCR_NOWNAME:
						idesc[i] = nowName;
						d[i].bfloat = false;
						break;
					case SCR_NOWCON:
						idesc[i] = nowCon;
						d[i].bfloat = false;
						break;
		
					case SCR_DIFFI:
						idesc[i] = mp.nowdifflv;
						d[i].bfloat = false;
						break;
					case SCR_SNOSTAGE:
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = data.getStage(_tdi);
						d[i].bfloat = false;
						break;
					case SCR_SNODIFFI:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = data.getDiffi(_tdi);
						d[i].bfloat = false;
						break;
					case SCR_SNOBATTLE:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = data.getBattle(_tdi);
						d[i].bfloat = false;
						break;
					case SCR_SNOUSER:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = data.getSpellUser(_tdi);
						d[i].bfloat = false;
						break;
					case SCR_CHARA:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						if (_tdi == 0)
						{
							idesc[i] = Player::p[0].ID;
						}
						else if (_tdi == 1)
						{
							idesc[i] = Player::p[0].ID_sub_1;
						}
						else if (_tdi == 2)
						{
							idesc[i] = Player::p[0].ID_sub_2;
						}
						else
						{
							idesc[i] = Player::p[0].nowID;
						}
						d[i].bfloat = false;
						break;
					case SCR_GETSCENE:
						idesc[i] = mp.scene;
						d[i].bfloat = false;
						break;
					case SCR_MODE:
						if (mp.practicemode)
						{
							if (mp.spellmode)
							{
								idesc[i] = M_MODE_SPELL;
							}
							else
							{
								idesc[i] = M_MODE_STAGE;
							}
						}
						else
						{
							idesc[i] = M_MODE_NORMAL;
						}
						d[i].bfloat = false;
						break;
					case SCR_REPLAYMODE:
						idesc[i] = mp.replaymode;
						d[i].bfloat = false;
						break;
					case SCR_FRAMESKIP:
						idesc[i] = mp.frameskip;
						d[i].bfloat = false;
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Special                                                              * /
					/ ************************************************************************ /
				case SCRKW_CLASS_SPECIAL:
					switch (nowval)
					{
					case SCR_CHATI:
						idesc[i] = chat.chati;
						d[i].bfloat = false;
						break;
		
					case SCR_BOSSFAILED:
						idesc[i] = BossInfo::failed;
						d[i].bfloat = false;
						break;
					case SCR_BOSSFLAG:
						idesc[i] = BossInfo::flag;
						d[i].bfloat = false;
						break;
		
					case SCR_CHECKKEY:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						++(*p);
						idesc[i] = hge->Input_GetDIKey(_tdi, CINT(Value(&(*p), i, 0)));
						d[i].bfloat = false;
						break;
		
					case SCR_GETFLAG:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = data.iRead(DATA_BINFILE, DATAS_FLAG, _tdi, 0);
						d[i].bfloat = false;
						break;
		
					case SCR_PLAYERNAME:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						CUINT(&idesc[i]) = (DWORD)data.getPlayerName(_tdi);
						d[i].bfloat = true;/ *Specialized for Handle* /
						break;
					case SCR_ENEMYNAME:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						CUINT(&idesc[i]) = (DWORD)data.getEnemyName(_tdi);
						d[i].bfloat = true;/ *Specialized for Handle* /
						break;
					case SCR_SPELLNAME:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						CUINT(&idesc[i]) = (DWORD)data.getSpellName(_tdi);
						d[i].bfloat = true;/ *Specialized for Handle* /
						break;
					case SCR_SPELLUSERNAME:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						CUINT(&idesc[i]) = (DWORD)data.getSpellUserName(_tdi);
						d[i].bfloat = true;/ *Specialized for Handle* /
						break;
					case SCR_SPELLUSERENAME:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						CUINT(&idesc[i]) = (DWORD)data.getSpellUserEName(_tdi);
						d[i].bfloat = true;/ *Specialized for Handle* /
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Effect                                                               * /
					/ ************************************************************************ /
				case SCRKW_CLASS_EFFECT:
					switch (nowval)
					{
					}
					break;
					/ ************************************************************************ /
					/ * Player                                                               * /
					/ ************************************************************************ /
				case SCRKW_CLASS_PLAYER:
					switch (nowval)
					{
					case SCR_PX:
						fdesc[i] = Player::p[0].x;
						d[i].bfloat = true;
						break;
					case SCR_PY:
						fdesc[i] = Player::p[0].y;
						d[i].bfloat = true;
						break;
					case SCR_PLIFE:
						idesc[i] = Player::p[0].nLife;
						d[i].bfloat = false;
						break;
					case SCR_PBOMB:
						idesc[i] = (float)Player::p[0].nPower / Player::p[0].bombperpower;
						d[i].bfloat = false;
						break;
					case SCR_PPOWER:
						idesc[i] = Player::p[0].nPower;
						d[i].bfloat = false;
						break;
					case SCR_PFAITH:
						idesc[i] = Player::p[0].nFaith;
						d[i].bfloat =false;
						break;
					case SCR_PPOINT:
						idesc[i] = Player::p[0].nPoint;
						d[i].bfloat = false;
						break;
					case SCR_PBBORDER:
						idesc[i] = (int)(Player::p[0].bBorder);
						d[i].bfloat = false;
						break;
					case SCR_PBSLOW:
						idesc[i] = (int)(Player::p[0].bSlow);
						d[i].bfloat = false;
						break;
					case SCR_PBINFI:
						idesc[i] = (int)(Player::p[0].bInfi);
						d[i].bfloat = false;
						break;
					case SCR_PSPEED:
						fdesc[i] = Player::p[0].speed;
						d[i].bfloat = true;
						break;
					case SCR_PSLOWSPEED:
						fdesc[i] = Player::p[0].slowspeed;
						d[i].bfloat = true;
						break;
					case SCR_PGX:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						fdesc[i] = Player::p[0].pg[_tdi].x;
						d[i].bfloat = true;
						break;
					case SCR_PGY:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						fdesc[i] = Player::p[0].pg[_tdi].y;
						d[i].bfloat = true;
						break;
					case SCR_HAVEPLAYER:
						++(*p);
						_tdi = CINT(Value(&(*p), i, 0));
						idesc[i] = Player::p[0].HavePlayer(_tdi);
						d[i].bfloat = false;
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Layer                                                                * /
					/ ************************************************************************ /
				case SCRKW_CLASS_LAYER:
					switch (nowval)
					{
					case SCR_BGSINDEX:
						idesc[i] = BGLayer::setindex;
						d[i].bfloat = false;
						break;
					case SCR_BGSTIMER:
						idesc[i] = BGLayer::set[BGLayer::setindex].timer;
						d[i].bfloat = false;
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Select                                                               * /
					/ ************************************************************************ /
				case SCRKW_CLASS_SELECT:
					switch (nowval)
					{
					case SCR_SELCOMPLETE:
						idesc[i] = false;//SelectSystem::complete;
						d[i].bfloat = false;
						break;
					case SCR_SEL:
						idesc[i] = 0;//SelectSystem::select;
						d[i].bfloat = false;
						break;
					case SCR_SELFIRSTID:
						idesc[i] = 0;//SelectSystem::firstID;
						d[i].bfloat = false;
						break;
					case SCR_ISELCOMPLETE:
						idesc[i] = InfoSelect::complete;
						d[i].bfloat = false;
						break;
					case SCR_ISEL:
						idesc[i] = InfoSelect::select;
						d[i].bfloat = false;
						break;
					case SCR_ISELFIRSTID:
						idesc[i] = InfoSelect::firstID;
						d[i].bfloat = false;
						break;
					}
					break;
				}
			}
		
			if(d[i].bfloat)
				return &fdesc[i];*/
		
	return &idesc[i];
}