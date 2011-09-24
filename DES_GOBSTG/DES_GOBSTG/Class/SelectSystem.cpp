#include "../header/SelectSystem.h"
#include "../header/Main.h"
#include "../header/Process.h"
#include "../header/SpriteItemManager.h"
#include "../header/PushKey.h"
#include "../header/SE.h"
#include "../header/PushKey.h"
#include "../header/GameInput.h"

SelectSystem SelectSystem::selsys[SELSYSTEMMAX];

SelectSystem::SelectSystem()
{
	select = 0;
	spselectframe = NULL;
	Clear();
}

SelectSystem::~SelectSystem()
{
	Clear();
}

void SelectSystem::Init()
{
	ClearAll();
}

void SelectSystem::ClearAll()
{
	for (int i=0; i<SELSYSTEMMAX; i++)
	{
		selsys[i].Clear();
	}
}

void SelectSystem::RenderAll()
{
	for (int i=0; i<SELSYSTEMMAX; i++)
	{
		selsys[i].Render();
	}
}

void SelectSystem::Action()
{
	for (int i=0; i<SELSYSTEMMAX; i++)
	{
		selsys[i].action();
	}
}

void SelectSystem::Clear()
{
	for(list<Selector>::iterator it=sel.begin();it!=sel.end();it++)
	{
		SpriteItemManager::FreeSprite(&(it->sprite));
	}
	SpriteItemManager::FreeSprite(&spselectframe);
	sel.clear();
	nselect = 0;
	nPageNum = 0;
	complete = false;
	confirminit = false;
	plus = true;
	keyplus = PUSHKEY_KEYNULL;
	keyminus = PUSHKEY_KEYNULL;
	keyok = PUSHKEY_KEYNULL;
	keycancel = PUSHKEY_KEYNULL;
}

Selector * SelectSystem::BuildSelector(BYTE ID, int siID, float cenx, float ceny, float hscale, float vscale, BYTE flag /* = SEL_NULL */)
{
	Selector _selector;
	sel.push_back(_selector);
	Selector * _pselector = &(*(sel.rbegin()));
	_pselector->valueSet(ID, siID, cenx, ceny, hscale, vscale, flag);
	_pselector->actionSet(SELINFO_NONE, adj);
	_pselector->actionSet(SELINFO_OVER, adj);
	_pselector->actionSet(SELINFO_ENTER, adj);
	_pselector->actionSet(SELINFO_LEAVE, adj);
	return _pselector;
}

void SelectSystem::Setup(BYTE _pushid, int _nselect, int _select, BYTE _playerindex, int _keyminus, int _keyplus, int _keyok, int _keycancel, int maxtime/* =-1 */)
{
	nselect = _nselect;
	select = _select;
	playerindex = _playerindex;
	if (keyplus == PUSHKEY_KEYNULL && _keyplus != PUSHKEY_KEYNULL)
		keyplus = _keyplus;
	if (keyminus == PUSHKEY_KEYNULL && _keyminus != PUSHKEY_KEYNULL)
		keyminus = _keyminus;
	if (keyok == PUSHKEY_KEYNULL && _keyok != PUSHKEY_KEYNULL)
		keyok = _keyok;
	if (keycancel == PUSHKEY_KEYNULL && _keycancel != PUSHKEY_KEYNULL)
		keycancel = _keycancel;
	pushid = _pushid;
	for (list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		it->SetMaxtime(maxtime);
	}
	if (_keyplus != PUSHKEY_KEYNULL || _keyminus != PUSHKEY_KEYNULL)
	{
		PushKey::SetPushEvent(pushid, 0, keyplus, keyminus);
	}
}

bool SelectSystem::SetPageNumber(BYTE _nPageNum, float _fadebegin, float _offset, int initshift/* =0 */, int _shiftangle/* =9000 */)
{
	if (nselect < _nPageNum)
	{
		return false;
	}
	nPageNum = _nPageNum;
	fadebegin = _fadebegin - _offset * 1.5f;
	offset = _offset;
	firstID = 0;
	lastID = nPageNum - 1;
	shiftangle = _shiftangle;
	shift(initshift);
	return true;
}

void SelectSystem::SetAction(BYTE typeflag, float xadj, float yadj)
{
	adj[typeflag].xadj = xadj;
	adj[typeflag].yadj = yadj;

	for (list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		it->actionSet(typeflag, adj);
	}
}

void SelectSystem::SetSelectFrame(int siID, float x, float y)
{
	SpriteItemManager::FreeSprite(&spselectframe);
	spselectframe = SpriteItemManager::CreateSprite(siID);
	selectframex = x;
	selectframey = y;
}

void SelectSystem::shift(int nshift)
{
	if (!nshift)
	{
		return;
	}
	float moveoffset = offset * nshift;
	float xmoveoffset = moveoffset * cost(shiftangle);
	float ymoveoffset = moveoffset * sint(shiftangle);
	for (list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		if ((it->flag & SEL_STAY) || (it->flag & SEL_NOSHIFT))
		{
			continue;
		}
		for (int i=0; i<SEL_STATEMAX; i++)
		{
			it->adj[i].xadj -= xmoveoffset;
			it->adj[i].yadj -= ymoveoffset;
		}
		it->timer = 0;
	}
	firstID += nshift;
	while (firstID >= nselect)
	{
		firstID -= nselect;
	}
	lastID = firstID + (nPageNum-1);
	if (lastID >= nselect)
	{
		lastID = nselect - 1;
		firstID = lastID - (nPageNum-1);
	}
}

void SelectSystem::matchSelect()
{
	for(list<Selector>::iterator it=sel.begin();it!=sel.end();it++)
	{
		if(it->ID == select && (it->flag & SEL_NONACTIVE))
		{
			list<Selector>::iterator jt = it;
			do
			{
				if(plus)
				{
					jt++;
					if(jt == sel.end())
						jt++;
				}
				else
				{
					jt--;
					if(jt == sel.end())
						jt--;
				}
				if(!((jt->flag & SEL_NONACTIVE) || (jt->flag & SEL_GRAY)))
				{
					select = jt->ID;
					break;
				}
			}while(jt!=it);
			break;
		}
	}
}

Selector * SelectSystem::GetPointer(int index)
{
	if (index < 0 || index >= sel.size())
	{
		return NULL;
	}
	int tindex = 0;
	for (list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		if (index == tindex)
		{
			return &(*it);
		}
		tindex++;
	}
	return NULL;
}

void SelectSystem::action()
{
	int fvID = -1;
	Selector * fvselector = NULL;
	for(list<Selector>::iterator it=sel.begin();it!=sel.end();it++)
	{
		it->PreAction(nselect, select, &fvID, &fvselector);
	}

	if(fvselector != NULL)
	{
		PushKey::UpdatePushEvent(pushid, playerindex);
		if (keyplus != PUSHKEY_KEYNULL)
		{
			if(GameInput::GetKey(playerindex, keyplus, DIKEY_DOWN))
			{
				plus = true;
				SE::push(SE_SYSTEM_SELECT);
				select++;
				if(select == nselect)
					select = 0;
			}
		}
		if (keyminus != PUSHKEY_KEYNULL)
		{
			if(GameInput::GetKey(playerindex, keyminus, DIKEY_DOWN))
			{
				plus = false;
				SE::push(SE_SYSTEM_SELECT);
				select--;
				if(select == -1)
					select = nselect - 1;
			}
		}
		matchSelect();
		if (nPageNum)
		{
			if (select < firstID)
			{
				shift(select - firstID);
			}
			else if (select > lastID)
			{
				shift(select - lastID);
			}
		}
		if(keyok != PUSHKEY_KEYNULL && GameInput::GetKey(playerindex, keyok, DIKEY_DOWN))
		{
			bool benter = false;
			for(list<Selector>::iterator it = sel.begin(); it != sel.end(); it++)
			{
				if(it->ID == select)
				{
					if(!((it->flag) & SEL_NONACTIVE))
					{
						sellock = select;
						benter = true;
						break;
					}
				}
			}
			if(benter)
			{
				SE::push(SE_SYSTEM_OK);
				for(list<Selector>::iterator it = sel.begin(); it != sel.end(); it++)
				{
					if(it->ID == select)
						it->ChangeState(SEL_ENTER, SELOP_SET);
					else
						it->ChangeState(SEL_LEAVE, SELOP_SET);
				}
			}
			else
			{
				SE::push(SE_SYSTEM_CANCEL);
			}
		}
	}

	if (keycancel != PUSHKEY_KEYNULL && GameInput::GetKey(playerindex, keycancel, DIKEY_DOWN))
	{
		SE::push(SE_SYSTEM_CANCEL);
		for(list<Selector>::iterator it = sel.begin(); it != sel.end(); it++)
		{
			it->ChangeState(SEL_LEAVE, SELOP_SET);
		}
		select = -1;
		complete = true;
	}
	else
	{
		for (list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
		{
			bool bret = it->PostAction(&select, sellock, nPageNum, fadebegin, offset, shiftangle, &selectframex, &selectframey);
			if (bret && !complete)
			{
				complete = true;
			}
		}
	}

}

int SelectSystem::SetSelect(int _select)
{
	if (_select < 0)
	{
		select += randt(1, nselect-1);
		if (nselect)
		{
			select %= nselect;
		}
		else
		{
			select = 0;
		}
	}
	else
	{
		select = _select;
	}
	return select;
}

void SelectSystem::Render()
{
	for(list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		it->Render();
	}
	if (spselectframe)
	{
		SpriteItemManager::RenderSprite(spselectframe, selectframex, selectframey);
	}
	for(list<Selector>::iterator it=sel.begin(); it!=sel.end(); it++)
	{
		it->RenderInfo();
	}
}

bool SelectSystem::Confirm(BYTE _pushid, int _keyminus, int _keyplus, int _keyok, int _keycancel, float cenx/* =M_CLIENT_CENTER_X */, float ceny/* =M_CLIENT_CENTER_Y */, bool settrue/* =false */)
{
	if(!confirminit)
	{
		Clear();

		Selector * _sel;
		_sel = BuildSelector(0, SpriteItemManager::yesIndex, cenx, ceny);
		_sel->actionSet(SELINFO_NONE, cenx-30, ceny+45);
		_sel->actionSet(SELINFO_OVER, cenx-30, ceny+40);
		_sel->actionSet(SELINFO_ENTER, cenx-30, ceny+45);
		_sel->actionSet(SELINFO_LEAVE, cenx-30, ceny+50);
		_sel = BuildSelector(1, SpriteItemManager::noIndex, cenx, ceny);
		_sel->actionSet(SELINFO_NONE, cenx+30, ceny+45);
		_sel->actionSet(SELINFO_OVER, cenx+30, ceny+40);
		_sel->actionSet(SELINFO_ENTER, cenx+30, ceny+45);
		_sel->actionSet(SELINFO_LEAVE, cenx+30, ceny+50);
		_sel = BuildSelector(2, SpriteItemManager::confirmIndex, cenx, ceny, 1, 0, SEL_NONACTIVE);
		_sel->actionSet(SELINFO_NONE, cenx, ceny);
		_sel->actionSet(SELINFO_OVER, cenx, ceny);
		_sel->actionSet(SELINFO_ENTER, cenx, ceny);
		_sel->actionSet(SELINFO_LEAVE, cenx, ceny);

		Setup(_pushid, 2, settrue?0:1, playerindex, _keyplus, _keyminus, _keyok, _keycancel);
		confirminit = true;
	}
	if(complete)
	{
		confirminit = false;
		if(select == 0)
			return true;
	}
	return false;
}