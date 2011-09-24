#ifndef __NOTUSELUA
#ifndef __NOTUSEHDSS

#include "../Header/Export_Lua_HDSS.h"
#include "../Header/LuaConstDefine.h"
#include "../Header/Scripter.h"

#include "../Header/Export_Lua_HDSS_CallGet.h"

int Export_Lua_HDSS::LuaFn_HDSS_Get(LuaState * ls)
{
	LuaStack args(ls);

	DWORD nowval = args[1].GetInteger();

	switch (nowval & SCRKWMASK_CLASS)
	{
		/************************************************************************/
		/* AttackObject                                                         */
		/************************************************************************/
	case SCRKW_CLASS_ATTACKOBJECT:
		switch (nowval)
		{
		case SCR_BUI:
			break;
		case SCR_BUANGLE:
			break;
		case SCR_BUSPEED:
			break;
		case SCR_BUX:
			break;
		case SCR_BUY:
			break;
		case SCR_BUTIMER:
			break;
		case SCR_BUCANCELABLE:
			break;
		case SCR_BUHAVEGRAY:
			break;

		case SCR_BEI:
			break;
		case SCR_BEANGLE:
			break;
		case SCR_BESPEED:
			break;
		case SCR_BEX:
			break;
		case SCR_BEY:
			break;
		case SCR_BETIMER:
			break;
		case SCR_BEHOLDTAR:
			break;
		case SCR_BEPINTAR:
			break;
		}
		break;
		/************************************************************************/
		/* Ghost                                                                */
		/************************************************************************/
	case SCRKW_CLASS_GHOST:
		switch (nowval)
		{
		case SCR_GHX:
			break;
		case SCR_GHY:
			break;
		case SCR_GHTIMER:
			break;
		case SCR_GHI:
			break;
		case SCR_GHANGLE:
			break;
		case SCR_GHSPEED:
			break;
		case SCR_GHAMAP:
			break;
		case SCR_GHRMAP:
			break;
		case SCR_GHAIMX:
			break;
		case SCR_GHAIMY:
			break;
		case SCR_GHLIFE:
			break;
		case SCR_GHAC:
			break;
		}
		break;
		/************************************************************************/
		/* Enemy                                                                */
		/************************************************************************/
	case SCRKW_CLASS_ENEMY:
		switch (nowval)
		{
		case SCR_ENX:
			return _HDSSCallGet::Get_ENX(ls);
		case SCR_ENY:
			return _HDSSCallGet::Get_ENY(ls);
		case SCR_ENTIMER:
			break;
		case SCR_ENI:
			return _HDSSCallGet::Get_ENI(ls);
		case SCR_ENANGLE:
			return _HDSSCallGet::Get_ENANGLE(ls);
		case SCR_ENSPEED:
			return _HDSSCallGet::Get_ENSPEED(ls);
		case SCR_ENAMAP:
			break;
		case SCR_ENRMAP:
			break;
		case SCR_ENLEVEL:
			return _HDSSCallGet::Get_ENLEVEL(ls);
		case SCR_ENAIMX:
			return _HDSSCallGet::Get_ENAIMX(ls);
		case SCR_ENAIMY:
			return _HDSSCallGet::Get_ENAIMY(ls);
		case SCR_ENAIMANGLE:
			return _HDSSCallGet::Get_ENAIMANGLE(ls);
		case SCR_ENLIFE:
			return _HDSSCallGet::Get_ENLIFE(ls);
		case SCR_ENNUM:
			return _HDSSCallGet::Get_ENNUM(ls);
		}
		break;
		/************************************************************************/
		/* Math                                                                 */
		/************************************************************************/
	case SCRKW_CLASS_MATH:
		switch (nowval)
		{
		case SCR_RAND:
			break;
		case SCR_RANDR:
			break;
		case SCR_SEED:
			return _HDSSCallGet::Get_SEED(ls);
		case SCR_SINA:
			return _HDSSCallGet::Get_SINA(ls);
		case SCR_COSA:
			return _HDSSCallGet::Get_COSA(ls);
		case SCR_TANA:
			return _HDSSCallGet::Get_TANA(ls);
		case SCR_ASIN2:
			return _HDSSCallGet::Get_ASINA2(ls);
		case SCR_ACOS2:
			return _HDSSCallGet::Get_ACOSA2(ls);
		case SCR_ATAN2:
			return _HDSSCallGet::Get_ATAN2(ls);
		case SCR_SQRT:
			break;
		case SCR_SIGN:
			return _HDSSCallGet::Get_SIGN(ls);
		case SCR_ROLL:
			return _HDSSCallGet::Get_ROLL(ls);
		case SCR_REGANGLE:
			return _HDSSCallGet::Get_REGANGLE(ls);
		}
		break;
		/************************************************************************/
		/* Other                                                                */
		/************************************************************************/
	case SCRKW_CLASS_OTHER:
		switch (nowval)
		{
		case SCR_D:
			return _HDSSCallGet::Get_D(ls);
		case SCR_DU:
			return _HDSSCallGet::Get_Du(ls);
		case SCR_TX:
			break;
		case SCR_TY:
			break;
		case SCR_TIME:
			break;
		case SCR_NOWNAME:
			break;
		case SCR_NOWCON:
			break;

		case SCR_RANK:
			return _HDSSCallGet::Get_RANK(ls);
		case SCR_SNOSTAGE:
			break;
		case SCR_SNODIFFI:
			break;
		case SCR_SNOBATTLE:
			break;
		case SCR_SNOUSER:
			break;
		case SCR_CHARA:
			return _HDSSCallGet::Get_CHARA(ls);
		case SCR_GETSCENE:
			return _HDSSCallGet::Get_SCENE(ls);
		case SCR_MODE:
			break;
		case SCR_REPLAYMODE:
			return _HDSSCallGet::Get_REPLAYMODE(ls);
		case SCR_FRAMESKIP:
			break;
		}
		break;
		/************************************************************************/
		/* Special                                                              */
		/************************************************************************/
	case SCRKW_CLASS_SPECIAL:
		switch (nowval)
		{
		case SCR_CHATI:
			return _HDSSCallGet::Get_CHATI(ls);

		case SCR_BOSSFAILED:
			break;
		case SCR_BOSSFLAG:
			break;

		case SCR_CHECKKEY:
			return _HDSSCallGet::Get_CHECKKEY(ls);

		case SCR_GETFLAG:
			break;

		case SCR_PLAYERNAME:
			break;
		case SCR_ENEMYNAME:
			break;
		case SCR_SPELLNAME:
			break;
		case SCR_SPELLUSERNAME:
			break;
		case SCR_SPELLUSERENAME:
			break;
		}
		break;
		/************************************************************************/
		/* Effect                                                               */
		/************************************************************************/
	case SCRKW_CLASS_EFFECT:
		switch (nowval)
		{
		}
		break;
		/************************************************************************/
		/* Player                                                               */
		/************************************************************************/
	case SCRKW_CLASS_PLAYER:
		switch (nowval)
		{
		case SCR_PX:
			return _HDSSCallGet::Get_PX(ls);
		case SCR_PY:
			return _HDSSCallGet::Get_PY(ls);
		case SCR_PLIFE:
			return _HDSSCallGet::Get_PLIFE(ls);
		case SCR_PBOMB:
			break;
		case SCR_PPOWER:
			break;
		case SCR_PFAITH:
			break;
		case SCR_PPOINT:
			break;
		case SCR_PBDRAIN:
			return _HDSSCallGet::Get_PBDRAIN(ls);
		case SCR_PBSLOW:
			break;
		case SCR_PBINFI:
			return _HDSSCallGet::Get_PBINFI(ls);
		case SCR_PSPEED:
			break;
		case SCR_PSLOWSPEED:
			break;
		case SCR_PGX:
			return _HDSSCallGet::Get_PGX(ls);
		case SCR_PGY:
			return _HDSSCallGet::Get_PGY(ls);
		case SCR_HAVEPLAYER:
			break;
		}
		break;
		/************************************************************************/
		/* Layer                                                                */
		/************************************************************************/
	case SCRKW_CLASS_LAYER:
		switch (nowval)
		{
		case SCR_BGSINDEX:
			return _HDSSCallGet::Get_BGSINDEX(ls);
		case SCR_BGSTIMER:
			break;
		}
		break;
		/************************************************************************/
		/* Select                                                               */
		/************************************************************************/
	case SCRKW_CLASS_SELECT:
		switch (nowval)
		{
		case SCR_SELCOMPLETE:
			return _HDSSCallGet::Get_SELCOMPLETE(ls);
		case SCR_SEL:
			return _HDSSCallGet::Get_SEL(ls);
		case SCR_SELFIRSTID:
			return _HDSSCallGet::Get_SELFIRSTID(ls);
		case SCR_ISELCOMPLETE:
			break;
		case SCR_ISEL:
			break;
		case SCR_ISELFIRSTID:
			break;
		}
		break;
	}
	return 0;
}

#endif
#endif