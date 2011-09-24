#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "../Header/Export_Lua_HDSS.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/Scripter.h"

#include "../Header/Export_Lua_HDSS_CallGet.h"

int Export_Lua_HDSS::LuaFn_HDSS_Call(LuaState * ls)
{
	LuaStack args(ls);

	DWORD nowval = args[1].GetInteger();
	int argscount = args.Count();
	if (argscount < 2)
	{
		ShowError(LUAERROR_LUAERROR, "HDSS args count error.");
		return 0;
	}

	switch (nowval & SCRKWMASK_TYPE)
	{
		/************************************************************************/
		/* Action                                                               */
		/************************************************************************/
	case SCRKW_ACTION:
		switch (nowval & SCRKWMASK_CLASS)
		{
		case SCRKW_CLASS_OTHER:
			switch (nowval)
			{
			case SCR_SD:
				return _HDSSCallGet::Call_SD(ls);
			case SCR_SDF:
				return _HDSSCallGet::Call_SDf(ls);
			}
			break;
		case SCRKW_CLASS_SPECIAL:
			switch (nowval)
			{
			case SCR_RETURN:
				return _HDSSCallGet::Call_RETURN(ls);
			case SCR_SETSTATE:
				return _HDSSCallGet::Call_SETSTATE(ls);
			case SCR_SETTIME:
				return _HDSSCallGet::Call_SETTIME(ls);
			case SCR_CLEARALL:
				return _HDSSCallGet::Call_CLEARALL(ls);
			case SCR_SETCHARA:
				return _HDSSCallGet::Call_SETCHARA(ls);
			case SCR_SETSCENE:
				return _HDSSCallGet::Call_SETSCENE(ls);
			case SCR_STARTPREP:
				return _HDSSCallGet::Call_STARTPREP(ls);
			case SCR_SETKEY:
				return _HDSSCallGet::Call_SETKEY(ls);
			case SCR_DISABLEALLKEY:
				return _HDSSCallGet::Call_DISABLEALLKEY(ls);
			case SCR_SETPUSHEVENT:
				return _HDSSCallGet::Call_SETPUSHEVENT(ls);
			case SCR_UPDATEPUSHEVENT:
				return _HDSSCallGet::Call_UPDATEPUSHEVENT(ls);
			case SCR_STOPACTION:
				return _HDSSCallGet::Call_STOPACTION(ls);
			case SCR_SAVEREPLAY:
				return _HDSSCallGet::Call_SAVEREPLAY(ls);
			}
			break;
		case SCRKW_CLASS_EFFECT:
			switch (nowval)
			{
			case SCR_MUSICCHANGE:
				return _HDSSCallGet::Call_MUSICCHANGE(ls);
			case SCR_MUSICSLIDE:
				return _HDSSCallGet::Call_MUSICSLIDE(ls);
			case SCR_SE:
				return _HDSSCallGet::Call_SE(ls);
			case SCR_SEOFF:
				return _HDSSCallGet::Call_SEOFF(ls);
			case SCR_HSVTORGB:
				return _HDSSCallGet::Call_HSVTORGB(ls);
			case SCR_PRINT:
				return _HDSSCallGet::Call_PRINT(ls);
			case SCR_FRONTSPRITE:
				return _HDSSCallGet::Call_FRONTSPRITE(ls);
			case SCR_FADEOUTFRONTSPRITE:
				return _HDSSCallGet::Call_FADEOUTFRONTSPRITE(ls);
			case SCR_FREEFRONTSPRITE:
				return _HDSSCallGet::Call_FREEFRONTSPRITE(ls);
			}
			break;
		}
		break;
		/************************************************************************/
		/* BASIC                                                                */
		/************************************************************************/
	case SCRKW_BASIC:
		switch (nowval & SCRKWMASK_CLASS)
		{
			/************************************************************************/
			/* ATTACKOBJECT                                                         */
			/************************************************************************/
		case SCRKW_CLASS_ATTACKOBJECT:
			switch (nowval)
			{
			case SCR_BUBUILD:
				return _HDSSCallGet::Call_BUBUILD(ls);
			case SCR_BUACTIONSET:
				return _HDSSCallGet::Call_BUACTIONSET(ls);
			case SCR_BUBUILDCIRCLE:
				return _HDSSCallGet::Call_BUBUILDCIRCLE(ls);
			case SCR_BUBUILDLINE:
				return _HDSSCallGet::Call_BUBUILDLINE(ls);
			case SCR_BUDECANCEL:
				return _HDSSCallGet::Call_BUDECANCEL(ls);
			case SCR_BEBUILD:
				return _HDSSCallGet::Call_BEBUILD(ls);
			}
			break;
			/************************************************************************/
			/* ENEMY                                                                */
			/************************************************************************/
		case SCRKW_CLASS_ENEMY:
			switch (nowval)
			{
			case SCR_ENBUILD:
				return _HDSSCallGet::Call_ENBUILD(ls);
			case SCR_ENACTIONSET:
				return _HDSSCallGet::Call_ENACTIONSET(ls);
			case SCR_ENSAIM:
				return _HDSSCallGet::Call_ENSAIM(ls);
			case SCR_ENTOI:
				return _HDSSCallGet::Call_ENTOI(ls);
			case SCR_ENAZBUILD:
				return _HDSSCallGet::Call_ENAZBUILD(ls);
			}
			break;
			/************************************************************************/
			/* MATH                                                                 */
			/************************************************************************/
		case SCRKW_CLASS_MATH:
			switch (nowval)
			{
			case SCR_RAMA:
				return _HDSSCallGet::Call_RAMA(ls);
			case SCR_INTER:
				return _HDSSCallGet::Call_INTER(ls);
			}
			break;
			/************************************************************************/
			/* SPECIAL                                                              */
			/************************************************************************/
		case SCRKW_CLASS_SPECIAL:
			switch (nowval)
			{
			case SCR_EZONEBUILD:
				return _HDSSCallGet::Call_EZONEBUILD(ls);
			case SCR_COLLISION_CIRCLE:
				return _HDSSCallGet::Call_COLLISION_CIRCLE(ls);
			}
			break;
			/************************************************************************/
			/* EFFECT                                                               */
			/************************************************************************/
		case SCRKW_CLASS_EFFECT:
			switch (nowval)
			{
			case SCR_EFFSETUP:
				return _HDSSCallGet::Call_EFFSETUP(ls);
			case SCR_EFFMOVETO:
				return _HDSSCallGet::Call_EFFMOVETO(ls);
			}
			break;
			/************************************************************************/
			/* PLAYER                                                               */
			/************************************************************************/
		case SCRKW_CLASS_PLAYER:
			switch (nowval)
			{
			case SCR_SETPINITLIFE:
				return _HDSSCallGet::Call_SETPINITLIFE(ls);
			case SCR_ADDPNCHARGE:
				return _HDSSCallGet::Call_ADDPNCHARGE(ls);
			case SCR_SETPBINFI:
				return _HDSSCallGet::Call_SETPBINFI(ls);
			}
			break;
			/************************************************************************/
			/* LAYER                                                                */
			/************************************************************************/
		case SCRKW_CLASS_LAYER:
			switch (nowval)
			{
			case SCR_BGVALUE:
				return _HDSSCallGet::Call_BGVALUE(ls);
			case SCR_BGVALEX:
				return _HDSSCallGet::Call_BGVALEX(ls);
			case SCR_BGCOLOR:
				return _HDSSCallGet::Call_BGCOLOR(ls);
			case SCR_BGBLEND:
				return _HDSSCallGet::Call_BGBLEND(ls);
			case SCR_BGFLAG:
				return _HDSSCallGet::Call_BGFLAG(ls);
			case SCR_BGOFF:
				return _HDSSCallGet::Call_BGOFF(ls);
			case SCR_BGSETUP:
				return _HDSSCallGet::Call_BGSETUP(ls);
			}
			break;
			/************************************************************************/
			/* SELECT                                                               */
			/************************************************************************/
		case SCRKW_CLASS_SELECT:
			switch (nowval)
			{
			case SCR_SELBUILD:
				return _HDSSCallGet::Call_SELBUILD(ls);
			case SCR_SELCLEAR:
				return _HDSSCallGet::Call_SELCLEAR(ls);
			case SCR_SELCONFIRM:
				return _HDSSCallGet::Call_SELCONFIRM(ls);
			case SCR_SELSETUP:
				return _HDSSCallGet::Call_SELSETUP(ls);
			case SCR_SELSET:
				return _HDSSCallGet::Call_SELSET(ls);
			}
			break;
		}
		break;
		/************************************************************************/
		/* CONTROL                                                              */
		/************************************************************************/
	case SCRKW_CONTROL:
		switch (nowval)
		{
		case SCR_CHATON:
			return _HDSSCallGet::Call_CHATON(ls);
		case SCR_CHAT:
			return _HDSSCallGet::Call_CHAT(ls);
		case SCR_CHATOFF:
			return _HDSSCallGet::Call_CHATOFF(ls);
		}
		break;
	}
	return 0;
}

#endif
#endif