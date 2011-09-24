#include "../Header/Scripter.h"
//#include "../Header/processPrep.h"

bool Scripter::Parse(int varcount)
{
/*
		for(vector<Script>::iterator i=pnow->begin();i!=pnow->end();i++)
		{
			bool rv = false;
			int depth = 0;
			if(!i->value)
				continue;
	
			//Filter Type
			DWORD nowval = i->value;
			switch (nowval & SCRKWMASK_TYPE)
			{
				/ ************************************************************************ /
				/ * Action                                                               * /
				/ ************************************************************************ /
			case SCRKW_ACTION:
				switch (nowval)
				{
				case SCR_SD:
					if(rv = Copy(&i, 2))
					{
						if (d[1].bfloat)
						{
							CINT(d[1].value) = (int)(CFLOAT(d[1].value));
						}
						SetValue(CAST(d[0]), d[1].value, false);
					}
					break;
				case SCR_SDF:
					if(rv = Copy(&i, 2))
					{
						if (!d[1].bfloat)
						{
							CFLOAT(d[1].value) = (float)(CINT(d[1].value));
						}
						SetValue(CAST(d[0]), d[1].value, true);
					}
					break;
				case SCR_ST:
					if(rv = Copy(&i, 3))
					{
						int _tdi = CAST(d[0]);
						tar[_tdi].x = CAST(d[1]);
						tar[_tdi].y = CAST(d[2]);
					}
					break;
				case SCR_CALL:
					if(rv = Copy(&i, 2))
					{
						vector<Script> * psaved = pnow;
						int * idescsaved;
						TData * descsaved;
						if (varcount)
						{
							idescsaved = (int *)malloc(sizeof(int) * varcount);
							descsaved = (TData *)malloc(sizeof(TData) * varcount);
							memcpy(idescsaved, &idesc[SCR_VARBEGIN], sizeof(int) * varcount);
							memcpy(descsaved, &d[SCR_VARBEGIN], sizeof(TData) * varcount);
						}
						Execute(SCR_FUNCTION, UCAST(d[0]), UCAST(d[1]));
						if (varcount)
						{
							memcpy(&idesc[SCR_VARBEGIN], idescsaved, sizeof(int) * varcount);
							memcpy(&d[SCR_VARBEGIN], descsaved, sizeof(TData) * varcount);
							free(idescsaved);
							free(descsaved);
						}
						pnow = psaved;
					}
					break;
				case SCR_CALLEX:
					if (rv = Copy(&i, 3))
					{
						vector<Script> * psaved = pnow;
						int * idescsaved;
						TData * descsaved;
						if (varcount)
						{
							idescsaved = (int *)malloc(sizeof(int) * varcount);
							descsaved = (TData *)malloc(sizeof(TData) * varcount);
							memcpy(idescsaved, &idesc[SCR_VARBEGIN], sizeof(int) * varcount);
							memcpy(descsaved, &d[SCR_VARBEGIN], sizeof(TData) * varcount);
						}
						int _tdi = UCAST(d[2]);
						if (_tdi)
						{
							rv = Copy(&i, _tdi, 2);
						}
						Execute(SCR_FUNCTION, UCAST(d[0]), UCAST(d[1]));
						if (varcount)
						{
							memcpy(&idesc[SCR_VARBEGIN], idescsaved, sizeof(int) * varcount);
							memcpy(&d[SCR_VARBEGIN], descsaved, sizeof(TData) * varcount);
							free(idescsaved);
							free(descsaved);
						}
						pnow = psaved;
					}
					break;
				case SCR_EXECUTE:
					if(rv = Copy(&i, 3))
					{
						vector<Script> * psaved = pnow;
						int * idescsaved;
						TData * descsaved;
						if (varcount)
						{
							idescsaved = (int *)malloc(sizeof(int) * varcount);
							descsaved = (TData *)malloc(sizeof(TData) * varcount);
							memcpy(idescsaved, &idesc[SCR_VARBEGIN], sizeof(int) * varcount);
							memcpy(descsaved, &d[SCR_VARBEGIN], sizeof(TData) * varcount);
						}
						Execute(UCAST(d[0]) + SCRIPT_CTOFFSET, UCAST(d[1]), UCAST(d[2]));
						if (varcount)
						{
							memcpy(&idesc[SCR_VARBEGIN], idescsaved, sizeof(int) * varcount);
							memcpy(&d[SCR_VARBEGIN], descsaved, sizeof(TData) * varcount);
							free(idescsaved);
							free(descsaved);
						}
						pnow = psaved;
					}
					break;
	
				case SCR_RETURN:
					if(rv = Copy(&i, 1))
					{
						mp.retvalue = CAST(d[0]);
						return true;
					}
					break;
	
				case SCR_SETSTATE:
					if(rv = Copy(&i, 1))
					{
						mp.state = CAST(d[0]);
					}
					break;
				case SCR_SETTIME:
					if(rv = Copy(&i, 1))
					{
						time = CAST(d[0]);
					}
					break;
				case SCR_SETDIFFI:
					if(rv = Copy(&i, 1))
					{
						mp.nowdifflv = CAST(d[0]);
						if(mp.nowdifflv < M_DIFFI_EXTRA_START)
							mp.defaultdifflv = mp.nowdifflv;
					}
					break;
				case SCR_SETCHARA:
					if(rv = Copy(&i, 3))
					{
						mp.mainchara = CAST(d[0]);
						mp.subchara_1 = CAST(d[1]);
						mp.subchara_2 = CAST(d[2]);
						Player::p[0].ID = mp.mainchara;
						Player::p[0].ID_sub_1 = mp.subchara_1;
						Player::p[0].ID_sub_2 = mp.subchara_2;
					}
					break;
				case SCR_SETSCENE:
					if(rv = Copy(&i, 1))
					{
						mp.scene = CAST(d[0]);
					}
					break;
				case SCR_SETMODE:
					if(rv = Copy(&i, 1))
					{
						int _tdi = CAST(d[0]);
						mp.spellmode = (bool)(_tdi & M_RPYMODE_SPELL);
						mp.practicemode = (bool)(_tdi & M_RPYMODE_PRACTICE);
					}
					break;
				case SCR_STARTPREP:
					if (rv = true)
					{
						mp.startPrep(false);
					}
					break;
	
				case SCR_SETKEY:
					if (rv = Copy(&i, 2))
					{
						hge->Input_SetDIKey(CAST(d[0]), CAST(d[1]));
					}
					break;
				case SCR_DISABLEALLKEY:
					if (rv = true)
					{
						hge->Input_SetDIKey(KS_FIRE_MP, false);
						hge->Input_SetDIKey(KS_QUICK_MP, false);
						hge->Input_SetDIKey(KS_CHARGE_MP, false);
						hge->Input_SetDIKey(KS_SLOW_MP, false);
						hge->Input_SetDIKey(KS_UP_MP, false);
						hge->Input_SetDIKey(KS_DOWN_MP, false);
						hge->Input_SetDIKey(KS_LEFT_MP, false);
						hge->Input_SetDIKey(KS_RIGHT_MP, false);
					}
					break;
	
				case SCR_SETPUSHEVENT:
					if (rv = Copy(&i, 7))
					{
						PushKey::SetPushEvent(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]));
					}
					break;
				case SCR_UPDATEPUSHEVENT:
					if (rv = Copy(&i, 1))
					{
						PushKey::UpdatePushEvent(CAST(d[0]));
					}
					break;
	
				case SCR_STOPACTION:
					if (rv = Copy(&i, 2))
					{
						mp.stopflag = CAST(d[0]);
						mp.stoptimer = CAST(d[1]);
					}
					break;
				case SCR_SETFRAMESKIP:
					if (rv = Copy(&i, 1))
					{
						mp.frameskip = CAST(d[0]);
					}
					break;
	
				case SCR_MUSICCHANGE:
					if(rv = Copy(&i, 2))
					{
						mp.musicChange(CAST(d[0]), (bool)(CAST(d[1])));
					}
					break;
				case SCR_MUSICSLIDE:
					if (rv = Copy(&i, 4))
					{
						mp.musicSlide(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]));
					}
					break;
	
				case SCR_SE:
					if(rv = Copy(&i, 2))
					{
						SE::push(CAST(d[0]), CAST(d[1]));
					}
					break;
				case SCR_SEOFF:
					if (rv = Copy(&i, 1))
					{
						SE::stop(CAST(d[0]));
					}
					break;
	
				case SCR_HSVTORGB:
					if (rv = Copy(&i, 5))
					{
						hgeColorHSV _hsv(CAST(d[0]) / 255.0f, CAST(d[1]) / 255.0f, CAST(d[2]) / 255.0f, CAST(d[3]) / 255.0f);
						int _tdi = CAST(d[4]);
						CINT(d[_tdi].value) = _hsv.GetHWColor();
					}
					break;
				case SCR_PRINT:
					if (rv = Copy(&i, 9))
					{
						fdisp.BuildPostPrint(NULL, CAST(d[0]), CAST(d[1]), GetStringSp(2), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]), CAST(d[8]));
					}
					break;
				case SCR_FRONTSPRITE:
					if (rv = Copy(&i, 7))
					{
						int _tdi = CAST(d[0]);
						SpriteItemManager::BuildFrontSprite(_tdi, CAST(d[1]));
						SpriteItemManager::SetFrontSpriteValue(_tdi, CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]));
					}
					break;
				case SCR_FREEFRONTSPRITE:
					if (rv = Copy(&i, 1))
					{
						SpriteItemManager::FreeFrontSprite(CAST(d[0]));
					}
	
				case SCR_SETSHAKE:
					if (rv = Copy(&i, 2))
					{
						mp.SetShake(CAST(d[0]), CAST(d[1]));
					}
					break;
				}
				break;
				/ ************************************************************************ /
				/ * Basic                                                                * /
				/ ************************************************************************ /
			case SCRKW_BASIC:
				switch (nowval & SCRKWMASK_CLASS)
				{
					/ ************************************************************************ /
					/ * AttackObject                                                         * /
					/ ************************************************************************ /
				case SCRKW_CLASS_ATTACKOBJECT:
					switch (nowval)
					{
					case SCR_BUBUILD:
						if(rv = Copy(&i, 10))
						{
							Bullet::Build(CAST(d[0]), CAST(d[1]), (bool)(CAST(d[2])), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]), CAST(d[8]), CAST(d[9]));
						}
						break;
					case SCR_BUACTIONSET:
						if(rv = Copy(&i, 1))
						{
							int _tdi = CAST(d[0]);
							if(!_tdi)
							{
								Bullet::_bu.actionList[0] = SECTIONEND;
							}
							else if(rv = Copy(&i, _tdi))
							{
								for(int j=0;j<_tdi;j++)
								{
									Bullet::_bu.actionList[j] = CAST(d[j]);
								}
								Bullet::_bu.actionList[_tdi] = SECTIONEND;
							}
						}
						break;
					case SCR_BUBUILDCIRCLE:
						if (rv = Copy(&i, 10))
						{
							Bullet::BuildCircle(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]), CAST(d[8]), CAST(d[9]));
						}
						break;
					case SCR_BUBUILDLINE:
						if (rv = Copy(&i, 14))
						{
							Bullet::BuildLine(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]), CAST(d[8]), CAST(d[9]), CAST(d[10]), CAST(d[11]), CAST(d[12]), CAST(d[13]));
						}
						break;
					case SCR_BUDECANCEL:
						if (rv = Copy(&i, 1))
						{
							int _tdi = CAST(d[0]);
							if (_tdi >= 0 && _tdi < BULLETMAX)
							{
								if (bu.toIndex(_tdi) != VECLST_INDEXERROR)
								{
									(*bu).cancelable = false;
								}
							}
							break;
	
						}
						break;
					case SCR_IZEZONE:
						if (rv = Copy(&i, 6))
						{
							Bullet::IzeBuild(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]));
						}
						break;
	
					case SCR_BEBUILD:
						if(rv = Copy(&i, 10))
						{
							Beam::Build(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), (CAST(d[7])), CAST(d[8]), CAST(d[9]));
						}
						break;
					case SCR_BEVECTOR:
						if (rv = Copy(&i, 5))
						{
							int _tdi = CAST(d[0]);
							if (be.toIndex(_tdi) != VECLST_INDEXERROR)
							{
								if (be.isInRange() && be.isValid())
								{
									if ((*be).able)
									{
										(*be).SetVector(CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]));
									}
								}
							}
						}
						break;
					case SCR_BEHOLD:
						if (rv = Copy(&i, 4))
						{
							int _tdi = CAST(d[0]);
							if (be.toIndex(_tdi) != VECLST_INDEXERROR)
							{
								if (be.isInRange() && be.isValid())
								{
									if ((*be).able)
									{
										(*be).SetHold(CAST(d[1]), CAST(d[2]));
										(*be).angle = CAST(d[3]);
									}
								}
							}
						}
						break;
					case SCR_BEPIN:
						if (rv = Copy(&i, 4))
						{
							int _tdi = CAST(d[0]);
							if (be.toIndex(_tdi) != VECLST_INDEXERROR)
							{
								if (be.isInRange() && be.isValid())
								{
									if ((*be).able)
									{
										(*be).SetHold(CAST(d[1]), CAST(d[2]), CAST(d[3]));
									}
								
								}
							}
						}
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Ghost                                                                * /
					/ ************************************************************************ /
				case SCRKW_CLASS_GHOST:
					switch (nowval)
					{
					case SCR_GHBUILD:
						if(rv = Copy(&i, 10))
						{
							Ghost::Build(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]), CAST(d[8]), CAST(d[9]));
						}
						break;
					case SCR_GHSAIM:
						if(rv = Copy(&i, 2))
						{
							gh[Ghost::index].aim.x = CAST(d[0]);
							gh[Ghost::index].aim.y = CAST(d[1]);
						}
						break;
					case SCR_GHSET:
						if(rv = Copy(&i, 3))
						{
							gh[Ghost::index].angle = CAST(d[0]);
							gh[Ghost::index].speed = CAST(d[1]);
							gh[Ghost::index].ac = CAST(d[2]);
						}
						break;
					case SCR_GHCHASE:
						if (rv = Copy(&i, 3))
						{
							gh[Ghost::index].chaseAim(CAST(d[0]), CAST(d[1]), CAST(d[2]));
						}
						break;
					case SCR_GHSETLIFE:
						if (rv = Copy(&i, 2))
						{
							gh[Ghost::index].life = CAST(d[0]);
							gh[Ghost::index].maxlife = CAST(d[1]);
							if (gh[Ghost::index].life > gh[Ghost::index].maxlife)
							{
								gh[Ghost::index].maxlife = gh[Ghost::index].life;
							}
						}
						break;
					case SCR_GHCHANGE:
						if (rv = Copy(&i, 1))
						{
							gh[Ghost::index].gID = CAST(d[0]);
							gh[Ghost::index].timer = 0;
						}
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Enemy                                                                * /
					/ ************************************************************************ /
				case SCRKW_CLASS_ENEMY:
					switch (nowval)
					{
					case SCR_ENBUILD:
						if(rv = Copy(&i, 11))
						{
							Enemy::Build(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]), CAST(d[8]), CAST(d[9]), UCAST(d[10]));
						}
						break;
					case SCR_ENACTIONSET:
						if(rv = Copy(&i, 1))
						{
							int _tdi = CAST(d[0]);
							if(_tdi)
							{
								if(rv = Copy(&i, _tdi))
								{
									en[Enemy::index].ac = CAST(d[0]);
									for(int j=0; j<_tdi-1; j++)
									{
										en[Enemy::index].para[j] = CAST(d[j+1]);
									}
								}
							}
							else
							{
								en[Enemy::index].ac = 0;
							}
						}
						break;
					case SCR_ENSAIM:
						if(rv = Copy(&i, 2))
						{
							en[Enemy::index].aim.x = CAST(d[0]);
							en[Enemy::index].aim.y = CAST(d[1]);
						}
						break;
					case SCR_ENCHASE:
						if (rv = Copy(&i, 3))
						{
							en[Enemy::index].chaseAim(CAST(d[0]), CAST(d[1]), CAST(d[2]));
						}
						break;
					case SCR_ENSETLIFE:
						if (rv = Copy(&i, 2))
						{
							en[Enemy::index].life = CAST(d[0]);
							en[Enemy::index].maxlife = CAST(d[1]);
							if (en[Enemy::index].life < en[Enemy::index].maxlife)
							{
								en[Enemy::index].maxlife = en[Enemy::index].life;
							}
						}
						break;
					case SCR_ENCHANGE:
						if (rv = Copy(&i, 1))
						{
							en[Enemy::index].eID = CAST(d[0]);
							en[Enemy::index].timer = 0;
						}
						break;
	
					case SCR_DAMAGEZONE:
						if (rv = Copy(&i, 4))
						{
							Enemy::DamageZoneBuild(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]));
						}
						break;
					case SCR_BOSSSTORE:
						if (rv = true)
						{
							Enemy::bossflag[Enemy::index] = BOSS_STORE;
						}
						break;
					case SCR_BOSSATTACK:
						if (rv = true)
						{
							Enemy::bossflag[Enemy::index] = BOSS_ATTACK;
						}
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Math                                                                 * /
					/ ************************************************************************ /
				case SCRKW_CLASS_MATH:
					switch (nowval)
					{
					case SCR_RAMA:
						if(rv = Copy(&i, 7))
						{
							int _tdi = CAST(d[6]);
							BObject _tbobj(CAST(d[1]), CAST(d[2]));
							if(CAST(d[0]))
							{
								CINT(d[_tdi].value) = _tbobj.rMainAngle(CAST(d[3]), CAST(d[4]), CAST(d[5]));
							}
							else
							{
								CINT(d[_tdi].value) = _tbobj.aMainAngle(CAST(d[3]), CAST(d[4]), CAST(d[5]));
							}
							d[_tdi].bfloat = false;
						}
						break;
					case SCR_DIST:
						if (rv = Copy(&i, 5))
						{
							int _tdi = CAST(d[4]);
							float _txo = CAST(d[0]);
							float _tyo = CAST(d[1]);
							float _txa = CAST(d[2]);
							float _tya = CAST(d[3]);
							CFLOAT(d[_tdi].value) = DIST(_txo, _tyo, _txa, _tya);
							d[_tdi].bfloat = true;
						}
						break;
					case SCR_CHASEAIM:
						if (rv = Copy(&i, 3))
						{
							int _tdi[2];
							_tdi[0] = CAST(d[0]);
							BObject _obj;
							_obj.x = tar[_tdi[0]].x;
							_obj.y = tar[_tdi[0]].y;
							_tdi[1] = CAST(d[1]);
							_obj.chaseAim(tar[_tdi[1]].x, tar[_tdi[1]].y, CAST(d[2]));
							_obj.x += cost(_obj.angle) * _obj.speed;
							_obj.y += sint(_obj.angle) * _obj.speed;
							tar[_tdi[0]].x = _obj.x;
							tar[_tdi[0]].y = _obj.y;
						}
						break;
					case SCR_INTER:
						if (rv = Copy(&i, 4))
						{
							int _tdi = CAST(d[3]);
							CFLOAT(d[_tdi].value) = INTER(CAST(d[0]), CAST(d[1]), CAST(d[2]));
							d[_tdi].bfloat = true;
						}
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Other                                                                * /
					/ ************************************************************************ /
				case SCRKW_CLASS_OTHER:
					switch (nowval)
					{
					case SCR_ITEMBUILD:
						if (rv = Copy(&i, 6))
						{
							Item::Build(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]));
						}
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Special                                                              * /
					/ ************************************************************************ /
				case SCRKW_CLASS_SPECIAL:
					switch (nowval)
					{
					case SCR_BOSSUP:
						if(rv = true)
						{
							bossinfo.bossUp();
						}
						break;
					case SCR_SPELLUP:
						if(rv = Copy(&i, 3))
						{
							if(mp.spellmode)
							{
								int _tdi = CAST(d[0]);
								tar[_tdi].x = CAST(d[1]);
								tar[_tdi].y = CAST(d[2]);
							}
						}
						break;
	
					case SCR_ACONTROL:
						if (rv = Copy(&i, 2))
						{
							int _tindex = CAST(d[0]);
							int _tdi = CAST(d[1]);
							if (rv = Copy(&i, _tdi))
							{
								if (_tindex >= 0 && _tindex < BULLETMAX)
								{
									if (bu.toIndex(_tindex) != VECLST_INDEXERROR)
									{
										if (bu.isInRange() && bu.isValid())
										{
											if ((*bu).able)
											{
												if(!_tdi)
												{
													(*bu).actionList[0] = SECTIONEND;
												}
												else
												{
													for(int j=0;j<_tdi;j++)
													{
														(*bu).actionList[j] = CAST(d[j]);
													}
													(*bu).actionList[_tdi] = SECTIONEND;
												}
											}
										}
									}
								}
							}
						}
						break;
					case SCR_BCONTROL:
						if(rv = Copy(&i, 2))
						{
							BObject * _tpbobj = NULL;
							int _ttype = CAST(d[0]);
							int _tdi = CAST(d[1]);
							int _tindex = CAST(d[_tdi]);
	
							if (_tindex >= 0)
							{
								switch(_ttype)
								{
								case BTYPE_BULLET:
									if (_tindex < BULLETMAX)
									{
										if (bu.toIndex(_tindex) != VECLST_INDEXERROR)
										{
											if (bu.isInRange() && bu.isValid())
											{
												if ((*bu).able)
												{
													_tpbobj = &(*bu);
												}
											}
										}
									}
									break;
								case BTYPE_BEAM:
									if (_tindex < BEAMMAX)
									{
										if (be.toIndex(_tindex) != VECLST_INDEXERROR)
										{
											if (be.isInRange() && be.isValid())
											{
												if ((*be).able)
												{
													_tpbobj = &(*be);
												}
											}
										}
									}
									break;
								case BTYPE_ENEMY:
									if (_tindex < ENEMYMAX)
									{
										if(en[_tindex].able)
										{
											Enemy::index = _tindex;
											_tpbobj = &en[Enemy::index];
										}
									}
									break;
								case BTYPE_GHOST:
									if (_tindex < GHOSTMAX)
									{
										if(gh[_tindex].able)
										{
											Ghost::index = _tindex;
											_tpbobj = &gh[Ghost::index];
										}
									}
									break;
								}
							}
	
							if (rv = Copy(&i, 5))
							{
								if(_tpbobj)
								{
									_tpbobj->x = CAST(d[0]);
									_tpbobj->y = CAST(d[1]);
									_tpbobj->angle = CAST(d[2]);
									_tpbobj->headangle = CAST(d[3]);
									_tpbobj->speed = CAST(d[4]);
								}
								else
								{
									CINT(d[_tdi].value) = BINDEX_NULL;
									d[_tdi].bfloat = false;
								}
							}
						}
						break;
	
					case SCR_COLLISION_CIRCLE:
						if (rv = Copy(&i, 6))
						{
							int _tdi = CAST(d[5]);
							BObject _tbobj(CAST(d[0]), CAST(d[1]));
							CINT(d[_tdi].value) = _tbobj.checkCollisionCircle(CAST(d[2]), CAST(d[3]), CAST(d[4]));
							d[_tdi].bfloat = false;
						}
						break;
					case SCR_COLLISION_SQUARE:
						if (rv = Copy(&i, 6))
						{
							int _tdi = CAST(d[5]);
							BObject _tbobj(CAST(d[0]), CAST(d[1]));
							CINT(d[_tdi].value) = _tbobj.checkCollisionSquare(CAST(d[2]), CAST(d[3]), CAST(d[4]));
							d[_tdi].bfloat = false;
						}
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Effect                                                               * /
					/ ************************************************************************ /
				case SCRKW_CLASS_EFFECT:
					switch (nowval)
					{
					case SCR_EFFSETUP:
						if (rv = Copy(&i, 5))
						{
							int _tdi = CAST(d[0]);
							effsys[_tdi].valueSet(CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]));
						}
						break;
					case SCR_EFFSETUPEX:
						if(rv = Copy(&i, 10))
						{
							int _tdi = CAST(d[0]);
							effsys[_tdi].valueSet(CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]), CAST(d[8]), CAST(d[9]));
						}
						break;
					case SCR_EFFSETUPCHASE:
						if (rv = Copy(&i, 8))
						{
							int _tdi = CAST(d[0]);
							effsys[_tdi].valueSet(CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]));
						}
						break;
					case SCR_EFFSTOP:
						if (rv = Copy(&i, 1))
						{
							int _tdi = CAST(d[0]);
							if (effsys[_tdi].exist && effsys[_tdi].eff)
							{
								effsys[_tdi].Stop();
							}
						}
						break;
					case SCR_EFFOFF:
						if(rv = Copy(&i, 1))
						{
							int _tdi = CAST(d[0]);
							effsys[_tdi].exist = false;
						}
						break;
					case SCR_EFFSET:
						if(rv = Copy(&i, 4))
						{
							int _tdi = CAST(d[0]);
							effsys[_tdi].angle = CAST(d[1]);
							effsys[_tdi].speed = CAST(d[2]);
							effsys[_tdi].zSpeed = CAST(d[3]);
						}
						break;
					case SCR_EFFMOVETO:
						if(rv = Copy(&i, 4))
						{
							int _tdi = CAST(d[0]);
							effsys[_tdi].x = CAST(d[1]);
							effsys[_tdi].y = CAST(d[2]);
							effsys[_tdi].z = CAST(d[3]);
						}
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Player                                                               * /
					/ ************************************************************************ /
				case SCRKW_CLASS_PLAYER:
					switch (nowval)
					{
					case SCR_SETPPOS:
						if (rv = Copy(&i, 2))
						{
							float _tdfx = CAST(d[0]);
							float _tdfy = CAST(d[1]);
							_tdfx = _tdfx < PL_MOVABLE_LEFT ? PL_MOVABLE_LEFT : _tdfx;
							_tdfx = _tdfx > PL_MOVABLE_RIGHT ? PL_MOVABLE_RIGHT : _tdfx;
							_tdfy = _tdfy < PL_MOVABLE_TOP ? PL_MOVABLE_TOP : _tdfy;
							_tdfy = _tdfy > PL_MOVABLE_BOTTOM ? PL_MOVABLE_BOTTOM : _tdfy;
							Player::p[0].x = _tdfx;
							Player::p[0].y = _tdfy;
						}
						break;
					case SCR_SETPLIFE:
						if (rv = Copy(&i, 1))
						{
							int _tdi = CAST(d[0]);
							if (_tdi < 0)
							{
								break;
							}
							Player::p[0].nLife = _tdi > PL_NPLAYERMAX ? PL_NPLAYERMAX : _tdi;
						}
						break;
					case SCR_SETPINITLIFE:
						if (rv = Copy(&i, 2))
						{
							int _tdi = CAST(d[0]);
							Player::p[_tdi].SetInitLife(CAST(d[1]));
						}
						break;
					case SCR_SETPPOWER:
						if(rv = Copy(&i, 1))
						{
							int _tdi = CAST(d[0]);
							if (_tdi < 0)
							{
								break;
							}
							Player::p[0].nPower = _tdi;
						}
						break;
					case SCR_SETPFAITH:
						if (rv = Copy(&i, 1))
						{
							int _tdi = CAST(d[0]);
							if (_tdi < 0)
							{
								break;
							}
							Player::p[0].nFaith = _tdi;
						}
						break;
					case SCR_SETPPOINT:
						if (rv = Copy(&i, 1))
						{
							int _tdi = CAST(d[0]);
							if (_tdi < 0)
							{
								break;
							}
							Player::p[0].nPoint = _tdi;
						}
						break;
					case SCR_SETPBBORDER:
						if (rv = Copy(&i, 1))
						{
							if ((bool)(CAST(d[0])) ^ Player::p[0].bBorder)
							{
								Player::p[0].callBomb(true);
							}
						}
						break;
					case SCR_SETPBSLOW:
						if (rv = Copy(&i, 1))
						{
							Player::p[0].callSlowFastChange((bool)(CAST(d[0])));
						}
						break;
					case SCR_SETPBINFI:
						if(rv = true)
						{
							Player::p[0].bInfi = true;
						}
						break;
					case SCR_SETPSPEED:
						if (rv = Copy(&i, 1))
						{
							Player::p[0].speed = CAST(d[0]);
						}
						break;
					case SCR_SETPSLOWSPEED:
						if (rv = Copy(&i, 1))
						{
							Player::p[0].slowspeed = CAST(d[0]);
						}
						break;
					case SCR_SETPSPEEDFACTOR:
						if (rv = Copy(&i, 1))
						{
							Player::p[0].speedfactor = CAST(d[0]);
						}
						break;
	
					case SCR_COLLAPSE:
						if (rv = true)
						{
							Player::p[0].callCollapse();
						}
						break;
	
					case SCR_SHOOTPB:
						if (rv = Copy(&i, 1))
						{
							PlayerBullet::Build(CAST(d[0]));
						}
						break;
					case SCR_BONUSFLAG:
						if (rv = Copy(&i, 1))
						{
							Player::p[0].bonusflag = CAST(d[0]);
						}
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Layer                                                                * /
					/ ************************************************************************ /
				case SCRKW_CLASS_LAYER:
					switch (nowval)
					{
					case SCR_BGVALUE:
						if(rv = Copy(&i, 7))
						{
							int _tdi = CAST(d[0]);
							BGLayer::ubg[_tdi].valueSet(mp.tex, CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), UCAST(d[6]));
						}
						break;
					case SCR_BGVALEX:
						if (rv = Copy(&i, 16))
						{
							int _tdi = CAST(d[0]);
							BGLayer::ubg[_tdi].valueSet(mp.tex, CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]), CAST(d[8]), CAST(d[9]), CAST(d[10]), CAST(d[11]), CAST(d[12]), (bool)(CAST(d[13])), (bool)(CAST(d[14])), UCAST(d[15]));
						}
						break;
					case SCR_BGTEXRECT:
						if(rv = Copy(&i, 5))
						{
							int _tdi = CAST(d[0]);
							BGLayer::ubg[_tdi].texRectSet(CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]));
						}
						break;
					case SCR_BGRECT:
						if(rv = Copy(&i, 9))
						{
							int _tdi = CAST(d[0]);
							ubg[_tdi]->rectSet(CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]), CAST(d[8]));
						}
						break;
					case SCR_BGZ:
						if(rv = Copy(&i, 5))
						{
							int _tdi = CAST(d[0]);
							ubg[_tdi]->zSet(CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]));
						}
						break;
					case SCR_BGSCALE:
						if(rv = Copy(&i, 3))
						{
							int _tdi = CAST(d[0]);
							ubg[_tdi]->scaleSet(CAST(d[1]), CAST(d[2]));
						}
						break;
					case SCR_BGCOLOR:
						if(rv = Copy(&i, 5))
						{
							int _tdi = CAST(d[0]);
							ubg[_tdi]->colorSet(UCAST(d[1]), UCAST(d[2]), UCAST(d[3]), UCAST(d[4]));
						}
						break;
					case SCR_BGMOVE:
						if(rv = Copy(&i, 3))
						{
							int _tdi = CAST(d[0]);
							ubg[_tdi]->moveSet((bool)(CAST(d[1])), (bool)(CAST(d[2])));
						}
						break;
					case SCR_BGFLAG:
						if(rv = Copy(&i, 3))
						{
							int _tdi = CAST(d[0]);
							ubg[_tdi]->SetFlag(CAST(d[1]), CAST(d[2]));
						}
						break;
					case SCR_BGPARAL:
						if(rv = Copy(&i, 2))
						{
							int _tdi = CAST(d[0]);
							ubg[_tdi]->parallelogram(CAST(d[1]));
						}
						break;
					case SCR_BG4V:
						if (rv = Copy(&i, 13))
						{
							int _tdi = CAST(d[0]);
							ubg[_tdi]->vertexSet(CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]), CAST(d[7]), CAST(d[8]), CAST(d[9]), CAST(d[10]), CAST(d[11]), CAST(d[12]));
						}
						break;
					case SCR_BGOFF:
						if(rv = Copy(&i, 1))
						{
							int _tdi = CAST(d[0]);
							if (_tdi == -1)
							{
								BGLayer::KillOtherLayer();
							}
							else
							{
								ubg[_tdi]->exist = false;
							}
						}
						break;
					case SCR_BGBLEND:
						if (rv = Copy(&i, 2))
						{
							int _tdi = CAST(d[0]);
							ubg[_tdi]->SetBlend(CAST(d[1]));
						}
						break;
					case SCR_BGSETUP:
						if(rv = Copy(&i, 4))
						{
							int _tdi = CAST(d[0]);
							if(CAST(d[2]) || BGLayer::set[_tdi].sID == BGLAYERSET_NONE)
							{
								int _tsID = CAST(d[1]);
								if(BGLayer::set[_tdi].sID != BGLAYERSET_NONE && BGLayer::set[_tdi].sID != CAST(d[1]))
								{
									vector<Script> * psaved = pnow;
									int * idescsaved;
									TData * descsaved;
									if (varcount)
									{
										idescsaved = (int *)malloc(sizeof(int) * varcount);
										descsaved = (TData *)malloc(sizeof(TData) * varcount);
										memcpy(idescsaved, &idesc[SCR_VARBEGIN], sizeof(int) * varcount);
										memcpy(descsaved, &d[SCR_VARBEGIN], sizeof(TData) * varcount);
									}
									Execute(SCR_SCENE, BGLayer::set[_tdi].sID, SCRIPT_CON_POST);
									if (varcount)
									{
										memcpy(&idesc[SCR_VARBEGIN], idescsaved, sizeof(int) * varcount);
										memcpy(&d[SCR_VARBEGIN], descsaved, sizeof(TData) * varcount);
										free(idescsaved);
										free(descsaved);
									}
									pnow = psaved;
								}
								BGLayer::set[_tdi].sID = _tsID;
								BGLayer::set[_tdi].quittime = CAST(d[3]);
								BGLayer::set[_tdi].timer = 0;
							}
						}
						break;
					}
					break;
					/ ************************************************************************ /
					/ * Select                                                               * /
					/ ************************************************************************ /
				case SCRKW_CLASS_SELECT:
					switch (nowval)
					{
					case SCR_SELBUILD:
						if(rv = Copy(&i, 16))
						{
							/ *
							Selector::Build(CAST(d[0]), CAST(d[1]), CAST(d[2]), CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]),
								CAST(d[7]), CAST(d[8]),
								CAST(d[9]), CAST(d[10]),
								CAST(d[11]), CAST(d[12]),
								CAST(d[13]), CAST(d[14]),
								(CAST(d[15])));
								* /
						}
						break;
					case SCR_SELCLEAR:
	//					Selector::Clear();
						rv = true;
						break;
					case SCR_SELCONFIRM:
						if(rv = Copy(&i, 4))
						{
							/ *
							int _tdi = CAST(d[3]);
							CINT(d[_tdi].value) = Selector::confirm(CAST(d[0]), CAST(d[1]), CAST(d[2]));
							d[_tdi].bfloat = false;
							* /
						}
						break;
					case SCR_SELSETUP:
						if(rv = Copy(&i, 7))
						{
							/ *
							Selector::Setup(CAST(d[0]), CAST(d[1]), (bool)CAST(d[2]));
							Selector::SetPageNum(CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]));
							* /
						}
						break;
					case SCR_SELFLAG:
						if (rv = Copy(&i, 2))
						{
							/ *
							Selector * _sel = Selector::GetPointer(CAST(d[0]));
	                        if (_sel)
	                        {
								_sel->flag = CAST(d[1]);
	                        }
							* /
						}
						break;
					case SCR_SELSET:
						if (rv = Copy(&i, 1))
						{
							/ *
							* /
						}
						break;
	
					case SCR_ISELBUILD:
						if(rv = Copy(&i, 6))
						{
							InfoSelect::Build(CAST(d[0]), GetStringSp(1), CAST(d[2]), CAST(d[3]), CAST(d[4]), (CAST(d[5])));
						}
						break;
					case SCR_ISELCLEAR:
						InfoSelect::Clear();
						rv = true;
						break;
					case SCR_ISELSET:
						if(rv = Copy(&i, 7))
						{
							InfoSelect::Setup(CAST(d[0]), CAST(d[1]), (bool)CAST(d[2]));
							InfoSelect::SetPageNum(CAST(d[3]), CAST(d[4]), CAST(d[5]), CAST(d[6]));
						}
						break;
					case SCR_ISELFLAG:
						if (rv = Copy(&i, 2))
						{
							InfoSelect * _tifs = InfoSelect::GetPointer(CAST(d[0]));
							if (_tifs)
							{
								_tifs->flag = CAST(d[1]);
							}
						}
						break;
					case SCR_ISELCOLOR:
						if (rv = Copy(&i, 2))
						{
							InfoSelect * _tifs = InfoSelect::GetPointer(CAST(d[0]));
							if (_tifs)
							{
								_tifs->coltype = CAST(d[1]);
							}
						}
					}
					break;
				}
				break;
				/ ************************************************************************ /
				/ * Control                                                              * /
				/ ************************************************************************ /
			case SCRKW_CONTROL:
				switch (nowval)
				{
				case SCR_IF:
	nest:
					if(rv = Copy(&i, 1))
					{
						if(!CAST(d[0]))
						{
							while(true)
							{
								++i;
								if(i->type & SCR_TOKEN_COMMAND && i->value == SCR_THEN)
									depth++;
								if(i->type & SCR_TOKEN_COMMAND && i->value == SCR_END)
								{
									depth--;
									if(!depth)
										break;
								}
							}
							++i;
							if(i!=pnow->end())
							{
								if(i->type & SCR_TOKEN_COMMAND && i->value == SCR_ELSE)
									continue;
								else if(i->type & SCR_TOKEN_COMMAND && i->value == SCR_ELSEIF)
									goto nest;
								else
									--i;
							}
							else
								--i;
						}
					}
					break;
				case SCR_ELSE:
				case SCR_ELSEIF:
					if(true)
					{
						while(true)
						{
							++i;
							if(i->type & SCR_TOKEN_COMMAND && i->value == SCR_THEN)
								depth++;
							if(i->type & SCR_TOKEN_COMMAND && i->value == SCR_END)
							{
								depth--;
								if(!depth)
									break;
							}
						}
					}
					rv = true;
					break;
				case SCR_END:
				case SCR_THEN:
					continue;
	
				case SCR_LOOP:
					if(rv = Copy(&i, 1))
					{
						vector<Script> _while;
						while(true)
						{
							++i;
							if(i->type & SCR_TOKEN_COMMAND && i->value == SCR_THEN)
								depth++;
							else if(i->type & SCR_TOKEN_COMMAND && i->value == SCR_END)
							{
								depth--;
								if(!depth)
									break;
							}
							_while.push_back(*i);
						}
						vector<Script> * psaved = pnow;
						pnow = &_while;
	
						while(CINT(d[CINT(d[0].value)].value)--)
						{
							int _idesc;
							_idesc = idesc[0];
							if(!Parse(varcount))
								break;
							idesc[0] = _idesc;
						}
						pnow = psaved;
					}
					break;
				case SCR_SKIP:
					return true;
					break;
	
				case SCR_CHATON:
					if(rv = Copy(&i, 1))
					{
						int _tdi = CAST(d[0]);
						if(_tdi < 0 || _tdi > PLAYERTYPEMAX || Player::p[0].HavePlayer(_tdi))
						{
							if(!chat.chati)
							{
								if(rv = Copy(&i, 3))
								{
									if(chat.chatOn(CAST(d[0]), CAST(d[1]), CAST(d[2])))
										chat.chati++;
									goto chatout;
								}
							}
							else
							{
								if(chat.chati == 0xff)
								{
									chat.chati = 0;
									goto chatout;
								}
								for(int j=0;j<chat.chati;j++)
								{
									++i;
									++i;
									++i;
								}
								++i;
								if(i->type & SCR_TOKEN_COMMAND && i->value == SCR_CHATOFF)
								{
									if(chat.chatOff())
										chat.chati = 0xff;
									break;
								}
								else
								{
									--i;
									if(rv = Copy(&i, 3))
									{
										if(chat.chat(CAST(d[0]), CAST(d[1]), GetStringSp(2)))
											chat.chati++;
										goto chatout;
									}
								}
							}
						}
						else
						{
	chatout:
							while(true)
							{
								++i;
								if(i->type & SCR_TOKEN_COMMAND && i->value == SCR_CHATOFF)
								{
									rv = true;
									break;
								}
							}
						}
					}
					break;
				case SCR_CHATOFF:
					continue;
				}
				break;
				/ ************************************************************************ /
				/ * Data                                                                 * /
				/ ************************************************************************ /
			case SCRKW_DATA:
				switch (nowval)
				{
				case SCR_DATAGET:
					if (rv = Copy(&i, 4))
					{
						int _tdi = CAST(d[3]);
						CINT(d[_tdi].value) = data.iRead(DATA_BINFILE, UCAST(d[0]), UCAST(d[1]), CAST(d[2]));
						d[_tdi].bfloat = false;
					}
					break;
				case SCR_DATAGETf:
					if (rv = Copy(&i, 4))
					{
						int _tdi = CAST(d[4]);
						CFLOAT(d[_tdi].value) = data.fRead(DATA_BINFILE, UCAST(d[0]), UCAST(d[1]), CAST(d[2]));
						d[_tdi].bfloat = true;
					}
					break;
				case SCR_DATASET:
					if (rv = Copy(&i, 3))
					{
						data.iWrite(DATA_BINFILE, UCAST(d[0]), UCAST(d[1]), CAST(d[2]));
					}
					break;
				case SCR_DATASETf:
					if (rv = Copy(&i, 3))
					{
						data.fWrite(DATA_BINFILE, UCAST(d[0]), UCAST(d[1]), CAST(d[2]));
					}
					break;
				case SCR_SETFLAG:
					if (rv = Copy(&i, 2))
					{
						data.iWrite(DATA_BINFILE, DATAS_FLAG, UCAST(d[0]), CAST(d[1]));
					}
					break;
	
				case SCR_TRYSTAGE:
					if (rv = true)
					{
						DataConnector::Try();
					}
					break;
	
				case SCR_DEBUG_BREAKPOINT:
	#ifdef __DEBUG
					if(rv = true)
					{
						LogOut();
					}
	#endif
					break;
				}
				break;
			}
	
			if(!rv)
			{
	#ifdef __DEBUG
				HGELOG("%s\nError in parsing %d.", HGELOG_ERRSTR, i->value);
				LogOut();
	#endif
				return false;
			}
		}*/
	
	return true;
}
