#include "../Header/Scripter.h"
#include "../Header/Main.h"
#include "../Header/Export_Lua_HDSS.h"

bool Scripter::Copy(vector<Script>::iterator * p, BYTE num, BYTE dstart)
{
	if (num == 0)
	{
		return true;
	}
	int descnum = num+dstart;
	if(descnum > SCR_MAXDESC)
		return false;
	for(int i=dstart; ; i++)
	{
		vector<Script>::iterator ts = ++(*p);
		if(i == descnum && ((*p) == pnow->end() || !((*p)->type & SCR_TOKEN_OPERATOR)))
		{
			--(*p);
			break;
		}
		if(ts->type & SCR_TOKEN_OPERATOR)
		{
			switch(ts->value)
			{
			case SCR_ADD_INT:
				i--;
				tdi = CAST(d[i]);
				idesc[i] = tdi + CINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_SUB_INT:
				i--;
				tdi = CAST(d[i]);
				idesc[i] = tdi - CINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_MUL_INT:
				i--;
				tdi = CAST(d[i]);
				idesc[i] = tdi * CINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_DIV_INT:
				i--;
				tdi = CAST(d[i]);
				idesc[i] = tdi / CINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_ADD_FLOAT:
				i--;
				tdf = CAST(d[i]);
				fdesc[i] = tdf + CFLOAT(ValueF(&(++(*p)), i));
				d[i].value = &fdesc[i];
				d[i].bfloat = true;
				break;
			case SCR_SUB_FLOAT:
				i--;
				tdf = CAST(d[i]);
				fdesc[i] = tdf - CFLOAT(ValueF(&(++(*p)), i));
				d[i].value = &fdesc[i];
				d[i].bfloat = true;
				break;
			case SCR_MUL_FLOAT:
				i--;
				tdf = CAST(d[i]);
				fdesc[i] = tdf * CFLOAT(ValueF(&(++(*p)), i));
				d[i].value = &fdesc[i];
				d[i].bfloat = true;
				break;
			case SCR_DIV_FLOAT:
				i--;
				tdf = CAST(d[i]);
				fdesc[i] = tdf / CFLOAT(ValueF(&(++(*p)), i));
				d[i].value = &fdesc[i];
				d[i].bfloat = true;
				break;
			case SCR_ADD_UINT:
				i--;
				tdu = UCAST(d[i]);
				idesc[i] = tdu + CUINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_SUB_UINT:
				i--;
				tdu = UCAST(d[i]);
				idesc[i] = tdu - CUINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_MUL_UINT:
				i--;
				tdu = UCAST(d[i]);
				idesc[i] = tdu * CUINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_DIV_UINT:
				i--;
				tdu = UCAST(d[i]);
				idesc[i] = tdu / CUINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_MOD:
				i--;
				tdi = CINT(d[i].value);
				idesc[i] = tdi % CINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_MOD_UINT:
				i--;
				tdu = UCAST(d[i]);
				idesc[i] = tdu % CUINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;

			case SCR_INVERSE:
				i--;
				idesc[i] = ~ idesc[i];
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_NOT:
				i--;
				idesc[i] = ! idesc[i];
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;

			case SCR_GREAT_INT:
				i--;
				tdi = CAST(d[i]);
				idesc[i] = tdi > CINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_LESS_INT:
				i--;
				tdi = CAST(d[i]);
				idesc[i] = tdi < CINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_GREAT_FLOAT:
				i--;
				tdf = CAST(d[i]);
				idesc[i] = tdf > CFLOAT(ValueF(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_LESS_FLOAT:
				i--;
				tdf = CAST(d[i]);
				idesc[i] = tdf < CFLOAT(ValueF(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_GREAT_UINT:
				i--;
				tdu = UCAST(d[i]);
				idesc[i] = tdu > CUINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			case SCR_LESS_UINT:
				i--;
				tdu = UCAST(d[i]);
				idesc[i] = tdu < CUINT(ValueI(&(++(*p)), i));
				d[i].value = &idesc[i];
				d[i].bfloat = false;
				break;
			}
		}
		else
		{
			d[i].value = Value(&(*p), i, 0);
		}
		if(*p == pnow->end())
			return false;
	}
	return true;
}

#ifndef __NOTUSELUA
bool Scripter::Execute_Lua(DWORD typeflag, DWORD name, DWORD con)
{
	return Export_Lua_HDSS::Execute(typeflag, name, con);
}
#endif

bool Scripter::Execute(vector<File> * ptype, DWORD name, DWORD con)
{
	nowName = name;
	nowCon = con;
	bool bFound = false;
	bool rv = false;
	for(vector<File>::iterator i=ptype->begin();i!=ptype->end();i++)
	{
		if(i->name == name)
		{
			for(vector<Block>::iterator j=i->file.begin();j!=i->file.end();j++)
			{
				if(j->con > SCR_TIMECONTROL)
				{
					bFound = true;
					DWORD _timefunc0 = j->con & ~SCR_TIMECONTROL;
					DWORD _timefunc = _timefunc0 & ~SCR_TIMECONTROL_TEST0;
					DWORD _con = con;
					while (_timefunc)
					{
						++j;
						if (bFound)
						{
							switch (_timefunc & SCRKT_TEST_OPERATOR)
							{
							case SCR_TIMEFUNC_MOD:
								_con = _con % j->con;
								break;
							case SCR_TIMEFUNC_PLUS:
								_con += j->con;
								break;
							case SCR_TIMEFUNC_LESS:
								if (_con >= j->con)
								{
									bFound = false;
								}
								break;
							case SCR_TIMEFUNC_LESSEQUAL:
								if (_con > j->con)
								{
									bFound = false;
								}
								break;
							case SCR_TIMEFUNC_EQUAL:
								if (_con != j->con)
								{
									bFound = false;
								}
								break;
							case SCR_TIMEFUNC_GREATEQUAL:
								if (_con < j->con)
								{
									bFound = false;
								}
								break;
							case SCR_TIMEFUNC_GREAT:
								if (_con <= j->con)
								{
									bFound = false;
								}
								break;
							default:
								bFound = false;
								break;
							}
						}
						_timefunc = _timefunc >> SCRKT_SIZE_OPERATOR;
					}

					if ((_timefunc0 & SCR_TIMECONTROL_TEST0) && _con != 0)
					{
						bFound = false;
					}

					if (bFound)
					{
						pnow = &(j->block);
					}
				}
				else if(j->con == con)
				{
					pnow = &(j->block);
					bFound = true;
				}
				if(bFound)
				{
					if(!(rv = Parse(j->varcount)))
					{
#ifdef __DEBUG_LOG
						HGELOG("%s\nError in parsing script. At Block %d of File %d.", HGELOG_ERRSTR, j->con, i->name);
#endif
						break;
					}
					bFound = false;
				}
			}
			break;
		}
	}

	return rv;
}

void Scripter::LogOut()
{
#ifdef __DEBUG_LOGOUT
	HGELOG("\n*****DEBUG LOGOUT START*****\n");
	HGELOG("*****DEBUG*****\nFuction Descs:");
	for(int i=0; i<SCR_VARBEGIN; i++)
	{
		if(d[i].bfloat)
			HGELOG("Desc[%d] = %f", i, CFLOAT(d[i].value));
		else
			HGELOG("Desc[%d] = %d", i, CINT(d[i].value));
	}
	HGELOG("*****DEBUG*****\nVariable Descs:");
	for(int i=SCR_VARBEGIN; i<SCR_FREEBEGIN ;i++)
	{
		if(d[i].bfloat)
			HGELOG("Var[%d] = %f", i-SCR_VARBEGIN, CFLOAT(d[i].value));
		else
			HGELOG("Var[%d] = %d", i-SCR_VARBEGIN, CINT(d[i].value));
	}
	HGELOG("*****DEBUG*****\nFree Descs:");
	for(int i=SCR_FREEBEGIN; i<SCR_RESERVEBEGIN; i++)
	{
		if(d[i].bfloat)
			HGELOG("_%d = %f", i-SCR_FREEBEGIN, CFLOAT(d[i].value));
		else
			HGELOG("_%d = %d", i-SCR_FREEBEGIN, CINT(d[i].value));
	}
	HGELOG("\n*****DEBUG LOGOUT OVER*****\n");
#endif
}
