#ifndef _SE_H
#define _SE_H

#include "MainDependency.h"
#include "Const.h"

#define SE_DEFAULT				0

#define	SE_PLAYER_GRAZE			1
#define	SE_PLAYER_SHOT			2
#define	SE_PLAYER_DEAD			3
#define SE_PLAYER_EXPLODE		4
#define SE_PLAYER_ALERT			5
#define SE_PLAYER_SPELLCUTIN	6

#define	SE_PLAYER_SLOWON		8
#define SE_PLAYER_SLOWOFF		9
#define	SE_PLAYER_CHANGE		10
#define SE_PLAYER_BORDERON		11
#define SE_PLAYER_BORDEROFF		12
#define SE_PLAYER_CHARGEON		13
#define SE_PLAYER_CHARGEUP		14

#define SE_BULLET_ERASE			16
#define	SE_BULLET_CHANGE_1		17
#define	SE_BULLET_CHANGE_2		18
#define	SE_BULLET_BOUND			19
#define	SE_BULLET_FADEOUT		20
#define SE_BULLET_SENDEX		21

#define	SE_BEAM_1				22
#define	SE_BEAM_2				23
#define SE_BEAM_REFLECT			24
#define SE_BEAM_FADEOUT			25

#define	SE_BOSS_UP				28
#define	SE_BOSS_DEAD			29
#define	SE_BOSS_TIMEOUT			30
#define SE_BOSS_TIMEUP			31
#define	SE_BOSS_KIRA			32
#define	SE_BOSS_POWER_1			33
#define	SE_BOSS_POWER_2			34
#define SE_BOSS_BONUS			35
#define SE_BOSS_WARNING			36

#define	SE_ENEMY_DAMAGE_1		40
#define	SE_ENEMY_DAMAGE_2		41
#define	SE_ENEMY_DEAD			42

#define	SE_GHOST_DEAD			44
#define SE_GHOST_MERGE			45
#define SE_GHOST_ACTIVATE		46
#define SE_GHOST_SEND			47

#define	SE_ITEM_GET				50
#define	SE_ITEM_EXTEND			51
#define	SE_ITEM_POWERUP			52

#define	SE_SYSTEM_OK			54
#define	SE_SYSTEM_CANCEL		55
#define	SE_SYSTEM_SELECT		56
#define	SE_SYSTEM_PAUSE			57

class SE
{
public:
	static bool Initial();
	static bool have(BYTE type);
	static void play();
	static void push(BYTE type, float x = M_CLIENT_CENTER_X);
	static void stop(int type=-1);

public:
	HEFFECT eff;
	HCHANNEL chn;
	float sum;
	WORD counter;
	static SE se[SEMAX];
	static BYTE vol;
};

#endif