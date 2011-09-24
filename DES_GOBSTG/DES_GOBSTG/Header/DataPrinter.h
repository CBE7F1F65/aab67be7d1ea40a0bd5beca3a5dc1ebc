#ifndef _DATAPRINTER_H
#define _DATAPRINTER_H

#include "MainDependency.h"
#include "Export.h"

#define DPS_SCOREFILENAME	"Score"
#define DPS_EXTENSION		"txt"

#define DPS_SECTION_HEADER		"[Header]\n"
#define DPS_SECTION_TOP10		"[Top10]\n"
#define DPS_SECTION_SPELL		"[SpellCard]\n"
#define DPS_SECTION_TOTAL		"[Total]\n"

#define DPS_SECTION_REPLAYINFO	"[ReplayData]\n"
#define DPS_SECTION_PARTNFO		"[BattleData]\n"
#define DPS_SECTION_REPLAYFRAME	"[ReplayFrame]\n"

#define DPS_COMMENT				"# "
#define DPS_RETURN				"\n"
#define DPS_TABLE_1				"\t"
#define DPS_TABLE_2				"\t\t"
#define DPS_TABLE_3				"\t\t\t"
#define DPS_TABLE_4				"\t\t\t\t"
#define DPS_LEFTANGLEBRACKET	"<"
#define DPS_RIGHTANGLEBRACKET	">"
#define DPS_LEFTBRACKET			"("
#define DPS_RIGHTBRACKET		")"
#define DPS_SLASH				"/"
#define DPS_SPACE				" "
#define DPS_COLON				":"
#define DPS_PERCENT				"%"

#define DPS_SPELLNAME_NFORMAT	40

#define DPS_HEAD_TITLE			"記録テキスト版 (Dumped Score File)"
#define DPS_HEAD_EXPLAIN_1		"このファイルは、現在の記録をダンプした物です。 (This file shows your game data.)"
#define DPS_HEAD_EXPLAIN_2		"このファイルの内容を変更してもゲームには反映されません。 (Changings in this file will not affect game data.)"
#define DPS_HEAD_EXPLAIN_3		"このファイルは自由に利用したり転載したり、別のフォーマットにしても構いません。 (You can post these data to anywhere you want.)"
#define DPS_HEAD_TIMESTAMPSIGN	"Time-stamp: "

#define DPS_COMMENTDOUBLELINE	"================================="
#define DPS_COMMENTLINE			"---------------------------------"

#define DPS_TITLE_TOP			"最高記録一覧 (Top 10 Data)"
#define DPS_TITLE_SPELL			"スペルカード一覧		普通モード（取得/挑戦）	練習モード（取得/挑戦）	(レベル マックスボーナス)"
#define DPS_TITLE_SPELL_EX		"SpellCard Data			NormalMode(Get/Meet)	PracticeMode(Get/Meet)	(level	MaxBonus)"
#define DPS_TITLE_TOTAL			"その他の状態一覧 (Other Data)"

#define DPS_TITLE_REPLAYINFO	"記録データ (Replay Data)"
#define DPS_TITLE_PARTINFO		"バトルデータ (Battle Data)"
#define DPS_TITLE_REPLAYFRAME	"その他のデータ (Other Data)"

#define DPS_TAG_TOPNUM			"No."
#define DPS_TAG_SPELLPRIFIX		"Spell-"
#define DPS_TAG_PART			"Stage"

#define DPS_TOTAL_RUNTIME		"総起動時間 (Total Run Time)"
#define DPS_TOTAL_GAMETIME		"総プレイ時間 (Total Play Time)"
#define DPS_TOTAL_PLAYTIME		"プレイ回数 (Total Play Count)"
#define DPS_TOTAL_PLAYTIME_ALL		"Total"
#define DPS_TOTAL_PLAYTIME_ALLCHARA	"全主人公合計 (All Charactors)"
#define DPS_TOTAL_CLEARTIME		"クリア回数 (Total Clear Count)"
#define DPS_TOTAL_PRACTICETIME	"プラクティス (Total Practice Count)"

#define DPS_TOP_TAGSTR_SPELLLIST				"取得スペルカード一覧		(総取得回数/総遭遇回数)"
#define DPS_TOP_TAGSTR_SPELLLIST_EX				"Get SpellCard List		(Total Get Count / Total Meet Count)"
#define DPS_RPYINFO_TAGSTR_SPELLLIST			"取得スペルカード一覧 (Get SpellCard List)"
#define DPS_REPLAYFRAME_TAGSTR_AVERAGE			"総平均FPS (Averange FPS)"
#define DPS_REPLAYFRAME_TAGSTR_TOTAL_AVERAGE	"300フレームごと平均FPS (Averange FPS of every 300 frames)"
#define DPS_REPLAYFRAME_AVERAGE_INTERVAL		300

class DataPrinter
{
public:
	DataPrinter();
	~DataPrinter();

	static bool PrintScore();
#ifdef __WIN32
	static bool WriteString(string * str, HANDLE hFile);
#endif // __WIN32
	static bool PrintReplayData(const char * foldername, const char * filename);
	static void getHeader();

#ifdef __WIN32
	static string str;
#endif // __WIN32
	static replayInfo rpyinfo;
	static partInfo partinfo[RPYPARTMAX];
	static replayFrame rpyframe[M_SAVEINPUTMAX];
};

extern HGE * hge;

#endif