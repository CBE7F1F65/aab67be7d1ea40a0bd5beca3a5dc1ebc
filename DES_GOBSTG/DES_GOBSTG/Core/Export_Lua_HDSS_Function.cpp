#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "../Header/Export_Lua_HDSS.h"
#include "../Header/Export_Lua_Const.h"
#include "../Header/Scripter.h"
#include "../Header/processPrep.h"

#define _HDSSFUNC_REGISTER(func)	int Export_Lua_HDSS::LuaFn_HDSS_##func(LuaState * ls)

_HDSSFUNC_REGISTER(SetDesc)
{
	_ENTERFUNC_LUA(2);

	int index = node.iNextGet();
	int ival = node.iNextGet();
	Scripter::scr.SetIntValue(index, ival);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(SetDescFloat)
{
	_ENTERFUNC_LUA(2);

	int index = node.iNextGet();
	float fval = node.fNextGet();
	Scripter::scr.SetFloatValue(index, fval);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(GetDesc)
{
	_ENTERFUNC_LUA(1);

	int index = node.iNextGet();
	if (Scripter::scr.d[index].bfloat)
	{
		node.PFloat(CAST(Scripter::scr.d[index]));
	}
	else
	{
		node.PInt(CAST(Scripter::scr.d[index]));
	}

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(SetChara)
{
	_ENTERFUNC_LUA(1);

	int index = node.iNextGet();
	Player::p.SetChara(index);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(GetChara)
{
	_ENTERFUNC_LUA(0);

	int index = Player::p.ID;
	node.PInt(index);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(ClearAll)
{
	_ENTERFUNC_LUA(0);

	Process::mp.ClearAll();

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(SetStage)
{
	_ENTERFUNC_LUA(1);

	int index = node.iNextGet();
	Process::mp.SetScene(index);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(GetStage)
{
	_ENTERFUNC_LUA(0);

	int index = Process::mp.stage;
	node.PInt(index);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(CallStartPrep)
{
	_ENTERFUNC_LUA(0);

	bool callinit = true;
	node.jNextGet();
	if (node.bhavenext)
	{
		callinit = node.bGet();
	}
	Process::mp.startPrep(callinit);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(SetupBG)
{
	_ENTERFUNC_LUA(1);

	float begincenx = node.fNextGet();
	BGLayer::bglayer.BGLayerSetup(begincenx);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(BuildSelect)
{
	_ENTERFUNC_LUA(1);

	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode subnode0(node.ls, node._obj, node.root);
		if (subnode0.argscount >= 5)
		{
			int index = subnode0.iNextGet();
			int id = subnode0.iNextGet();
			int siid = subnode0.iNextGet();
			float cenx = subnode0.fNextGet();
			float ceny = subnode0.fNextGet();
			float hscale = 1.0f;
			float vscale = 0.0f;
			BYTE flag = SEL_NULL;
			Selector * selector = SelectSystem::selsys[index].BuildSelector(id, siid, cenx, ceny, hscale, vscale, flag);

			node.jNextGet();
			if (node.bhavenext && node.ObjIsTable())
			{
				_LObjNode subnode1(node.ls, node._obj, node.root);

				seladj adj[SEL_STATEMAX];
				ZeroMemory(adj, sizeof(seladj)*SEL_STATEMAX);
				bool havestate[SEL_STATEMAX];

				subnode1.jNextGet();
				if (subnode1.bhavenext)
				{
					havestate[0] = true;
					adj[0].xadj = subnode1.fGet() + cenx;
					subnode1.jNextGet();
					if (subnode1.bhavenext)
					{
						adj[0].yadj = subnode1.fGet() + ceny;
						subnode1.jNextGet();
						if (subnode1.bhavenext)
						{
							havestate[1] = true;
							adj[1].xadj = subnode1.fGet() + cenx;
							subnode1.jNextGet();
							if (subnode1.bhavenext)
							{
								adj[1].yadj = subnode1.fGet() + ceny;
								subnode1.jNextGet();
								if (subnode1.bhavenext)
								{
									havestate[2] = true;
									adj[2].xadj = subnode1.fGet() + cenx;
									subnode1.jNextGet();
									if (subnode1.bhavenext)
									{
										adj[2].yadj = subnode1.fGet() + ceny;
										subnode1.jNextGet();
										if (subnode1.bhavenext)
										{
											havestate[3] = true;
											adj[3].xadj = subnode1.fGet() + cenx;
											subnode1.jNextGet();
											if (subnode1.bhavenext)
											{
												adj[3].yadj = subnode1.fGet() + ceny;
												subnode1.jNextGet();
											}
										}
									}
								}
							}
						}
					}
				}

				if (havestate[0])
				{
					selector->actionSet(SELINFO_NONE, adj);
					if (havestate[1])
					{
						selector->actionSet(SELINFO_OVER, adj);
						if (havestate[2])
						{
							selector->actionSet(SELINFO_ENTER, adj);
							if (havestate[3])
							{
								selector->actionSet(SELINFO_LEAVE, adj);
							}
						}
					}
				}

				node.jNextGet();
				if (node.ObjIsTable())
				{
					_LObjNode subnode2(node.ls, node._obj, node.root);

					char * info = NULL;
					DWORD ucol = 0xFFFFFFFF;
					DWORD dcol = 0xFFFFFFFF;
					float shadow = FONTSYS_DEFAULT_SHADOW;
					float xoffset = 0;
					float yoffset = 0;
					hscale = 1.0f;
					vscale = 0.0f;
					BYTE _alignflag = HGETEXT_CENTER|HGETEXT_MIDDLE;
					bool _sync = false;

					subnode2.jNextGet();
					if (subnode2.bhavenext)
					{
						info = (char *)subnode2.sGet();
						subnode2.jNextGet();
						if (subnode2.bhavenext)
						{
							ucol = subnode2.cGet();
							subnode2.jNextGet();
							if (subnode2.bhavenext)
							{
								dcol = subnode2.cGet();
								subnode2.jNextGet();
								if (subnode2.bhavenext)
								{
									shadow = subnode2.fGet();
									subnode2.jNextGet();
									if (subnode2.bhavenext)
									{
										xoffset = subnode2.fGet();
										subnode2.jNextGet();
										if (subnode2.bhavenext)
										{
											yoffset = subnode2.fGet();
											subnode2.jNextGet();
											if (subnode2.bhavenext)
											{
												hscale = subnode2.fGet();
												subnode2.jNextGet();
												if (subnode2.bhavenext)
												{
													vscale = subnode2.fGet();
													subnode2.jNextGet();
													if (subnode2.bhavenext)
													{
														_alignflag = subnode2.iGet();
														subnode2.jNextGet();
														if (subnode2.bhavenext)
														{
															_sync = subnode2.bGet();
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
					selector->infoSet(info, ucol, dcol, shadow, xoffset, yoffset, hscale, vscale, _alignflag, _sync);
				}
			}
		}
	}

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(BuildSelectConfirm)
{
	_ENTERFUNC_LUA(1);

	int selsys = node.iNextGet();
	int keyminus = PUSHKEY_KEYNULL;
	int keyplus = PUSHKEY_KEYNULL;
	int keyok = PUSHKEY_KEYNULL;
	int keycancel = PUSHKEY_KEYNULL;
	float cenx = M_CLIENT_CENTER_X;
	float ceny = M_CLIENT_CENTER_Y;
	bool settrue = true;

	node.jNextGet();
	if (node.bhavenext)
	{
		keyminus = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			keyplus = node.iGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				keyok = node.iGet();
				node.jNextGet();
				if (node.bhavenext)
				{
					keycancel = node.iGet();
					node.jNextGet();
					if (node.bhavenext)
					{
						cenx = node.fGet();
						node.jNextGet();
						if (node.bhavenext)
						{
							ceny = node.fGet();
							node.jNextGet();
							if (node.bhavenext)
							{
								settrue = node.bGet();
							}
						}
					}
				}
			}
		}
	}
	bool bret = SelectSystem::selsys[selsys].Confirm(selsys, keyminus, keyplus, keyok, keycancel, cenx, ceny, settrue);
	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(SetupSelect)
{
	_ENTERFUNC_LUA(1);

	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode subnode0(node.ls, node._obj, node.root);

		if (subnode0.argscount >= 3)
		{
			int selsys = subnode0.iNextGet();
			int nselect = subnode0.iNextGet();
			int select = subnode0.iNextGet();

			BYTE keyplus = PUSHKEY_KEYNULL;
			BYTE keyminus = PUSHKEY_KEYNULL;
			BYTE keyok = PUSHKEY_KEYNULL;
			BYTE keycancel = PUSHKEY_KEYNULL;
			int maxtime = SELSYS_DEFAULTMAXTIME;

			subnode0.jNextGet();
			if (subnode0.bhavenext)
			{
				keyplus = subnode0.iGet();
				subnode0.jNextGet();
				if (subnode0.bhavenext)
				{
					keyminus = subnode0.iGet();
					subnode0.jNextGet();
					if (subnode0.bhavenext)
					{
						keyok = subnode0.iGet();
						subnode0.jNextGet();
						if (subnode0.bhavenext)
						{
							keycancel = subnode0.iGet();
							subnode0.jNextGet();
							if (subnode0.bhavenext)
							{
								maxtime = subnode0.iGet();
							}
						}
					}
				}
			}
			SelectSystem::selsys[selsys].Setup(selsys, nselect, select, keyplus, keyminus, keyok, keycancel, maxtime);

			node.jNextGet();
			if (node.bhavenext && node.ObjIsTable())
			{
				_LObjNode subnode1(node.ls, node._obj, node.root);

				if (subnode1.argscount >= 3)
				{
					int nPageNumber = subnode1.iNextGet();
					float fadebegin = subnode1.fNextGet();
					float offset = subnode1.fNextGet();

					int initshift = 0;
					int shiftangle = 9000;
					subnode1.jNextGet();
					if (subnode1.bhavenext)
					{
						initshift = subnode1.iGet();
						subnode1.jNextGet();
						if (subnode1.bhavenext)
						{
							shiftangle = subnode1.iGet();
						}
					}
					SelectSystem::selsys[selsys].SetPageNumber(nPageNumber, fadebegin, offset, initshift, shiftangle);
				}

				node.jNextGet();
				if (node.bhavenext && node.ObjIsTable())
				{
					_LObjNode subnode2(node.ls, node._obj, node.root);

					if (subnode2.argscount >= 3)
					{
						int selectframeSIID = subnode2.iNextGet();
						float x = subnode2.fNextGet();
						float y = subnode2.fNextGet();
						SelectSystem::selsys[selsys].SetSelectFrame(selectframeSIID, x, y);
					}
				}
			}
		}
	}

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(ReleaseSelect)
{
	_ENTERFUNC_LUA(1);

	int index = node.iNextGet();
	SelectSystem::selsys[index].Clear();

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(CheckSelect)
{
	_ENTERFUNC_LUA(1);

	int selsys = node.iNextGet();
	bool bclearaftercomplete = true;
	node.jNextGet();
	if (node.bhavenext)
	{
		bclearaftercomplete = node.bGet();
	}

	if (selsys >= 0 && selsys < SELSYSTEMMAX)
	{
		node.PBoolean(SelectSystem::selsys[selsys].complete);
		node.PInt(SelectSystem::selsys[selsys].select);
		if (SelectSystem::selsys[selsys].complete && bclearaftercomplete)
		{
			SelectSystem::selsys[selsys].Clear();
		}
	}
	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(CheckInput)
{
	_ENTERFUNC_LUA(1);

	int ksi = node.iNextGet();
	int type = DIKEY_PRESSED;
	node.jNextGet();
	if (node.bhavenext)
	{
		type = node.iGet();
	}
	bool bret = GameInput::GetKey(ksi, type);
	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(ChangeMusic)
{
	_ENTERFUNC_LUA(0);

	int ID = -1;
	bool bForce = false;

	node.jNextGet();
	if (node.bhavenext)
	{
		ID = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			bForce = node.bGet();
		}
	}
	Process::mp.musicChange(ID, bForce);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(ToggleMusicSlide)
{
	_ENTERFUNC_LUA(1);

	float slidetime = node.fNextGet();
	int tovol = 0;
	int pan = -101;
	float pitch = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		tovol = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			pan = node.iGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				pitch = node.fGet();
			}
		}
	}
	Process::mp.musicSlide(slidetime, tovol, pan, pitch);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(PlaySE)
{
	_ENTERFUNC_LUA(1);

	int _type = node.iNextGet();

	float _x = M_CLIENT_CENTER_X;

	node.jNextGet();
	if (node.bhavenext)
	{
		_x = node.fGet();
	}
	SE::push(_type, _x);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(SetPlayerInitData)
{
	_ENTERFUNC_LUA(1);

	BYTE initlife = node.iNextGet();
	Player::p.SetInitLife(initlife);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(TogglePlayerInfi)
{
	_ENTERFUNC_LUA(1);

	BYTE reasonflag = node.iNextGet();
	int infitimer = PLAYER_INFIMAX;
	node.jNextGet();
	if (node.bhavenext)
	{
		infitimer = node.iGet();
	}
	Player::p.SetInfi(reasonflag, infitimer);

	_LEAVEFUNC_LUA;
}
_HDSSFUNC_REGISTER(CheckPlayerInfi)
{
	_ENTERFUNC_LUA(0);

	node.PBoolean(Player::p.bInfi);
	node.PInt(Player::p.infireasonflag);
	node.PInt(Player::p.infitimer);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(BuildEnemy)
{
	_ENTERFUNC_LUA(1);

	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode subnode0(node.ls, node._obj, node.root);

		if (subnode0.argscount >= 7)
		{
			WORD eID = subnode0.iNextGet();
			float x = subnode0.fNextGet();
			float y = subnode0.fNextGet();
			int angle = subnode0.iNextGet();
			float speed = subnode0.fNextGet();
			BYTE type = subnode0.iNextGet();
			float life = subnode0.fNextGet();

			int infitimer = 0;
			subnode0.jNextGet();
			if (subnode0.bhavenext)
			{
				infitimer = subnode0.iGet();
			}

			int enindex = Enemy::Build(eID, x, y, angle, speed, type, life, infitimer);

			if (enindex >= 0)
			{
				node.jNextGet();
				if (node.bhavenext)
				{
					Enemy * pen = &(Enemy::en[enindex]);
					BYTE _tarID = node.iNextGet();
					pen->setTar(_tarID);

					node.jNextGet();
					if (node.bhavenext)
					{
						int _take = node.iNextGet();
						pen->setTake(_take);
					}
				}
				node.PInt(enindex);
			}
		}
	}
	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(GetAllEnemiesInfo)
{
	_ENTERFUNC_LUA(1);

	int enset = node.iNextGet();
	int iret = 0;
	if (enset < 0 || enset >= ENEMY_NMAXSETMAX)
	{
		for (int i=0; i<ENEMY_NMAXSETMAX; i++)
		{
			iret += Enemy::nEnemyNow[i];
		}
	}
	else
	{
		iret = Enemy::nEnemyNow[enset];
	}
	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(SetState)
{
	_ENTERFUNC_LUA(1);

	int state = node.iNextGet();
	int time = 0;
	node.jNextGet();
	if (node.bhavenext)
	{
		time = node.iGet();
	}
	Process::mp.SetState(state, time);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(GetState)
{
	_ENTERFUNC_LUA(0);

	node.PInt(Process::mp.state);

	_LEAVEFUNC_LUA;
}

_HDSSFUNC_REGISTER(GetReplayMode)
{
	_ENTERFUNC_LUA(0);

	node.PBoolean(Process::mp.replaymode);
	node.PBoolean(Process::mp.replayend);

	_LEAVEFUNC_LUA;
}

#undef _HDSSFUNC_REGISTER

#endif
#endif