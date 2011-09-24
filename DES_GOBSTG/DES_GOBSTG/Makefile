TARGET = test
OBJS = Class/Beam.o Class/BGLayer.o Class/BObject.o Class/BossInfo.o Class/Bullet.o Class/Chat.o Class/EffectSp.o Class/Effectsys.o Class/Enemy.o Class/EventZone.o Class/Fontsys.o Class/FrontDisplay.o Class/GameAI.o Class/Ghost.o Class/InfoQuad.o Class/Item.o Class/Player.o Class/PlayerBullet.o Class/PlayerGhost.o Class/PlayerOtherAction.o Class/PushKey.o Class/Replay.o Class/SE.o Class/Selector.o Class/SelectSystem.o Class/Target.o Core/BMath.o Core/BResource.o Core/Data.o Core/DataConnector.o Core/DataMap.o Core/DataPrinter.o Core/DataTable.o Core/Export.o Core/Export_Lua.o Core/Export_Lua_Const.o Core/Export_Lua_Function.o Core/Export_Lua_Game.o Core/Export_Lua_HDSS.o Core/Export_Lua_HDSS_Call.o Core/Export_Lua_HDSS_CallFunctions.o Core/Export_Lua_HDSS_Get.o Core/Export_Lua_HDSS_GetFunctions.o Core/Export_Lua_HGE.o Core/Export_Lua_HGEHelper.o Core/GameInput.o Core/Keytable.o Core/Main.o Core/Parser.o Core/ParserFunction.o Core/ParserOther.o Core/Process.o Core/Scripter.o Core/SpriteItemManager.o Process/frame.o Process/frameEnd.o Process/frameStart.o Process/processClear.o Process/processContinue.o Process/processEnding.o Process/processGetInput.o Process/processInit.o Process/processMatchSelect.o Process/processMusic.o Process/processOption.o Process/processOver.o Process/processPause.o Process/processPlayerSelect.o Process/processReplay.o Process/processResult.o Process/processSceneSelect.o Process/processSpell.o Process/processStart.o Process/processStartPrep.o Process/processTitle.o Process/reload.o Process/render.o
BUILD_PRX = 1
PSP_FW_VERSION=371  
INCDIR = ../../include
LIBDIR = ../../lib
CFLAGS = -G0 -w -O2 -D__PSP -D__DEBUG
CXXFLAGS = $(CFLAGS) -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS =
LIBS +=  -lhge -lluaplus  -lpng -ljpeg -lg -lstdc++  -lpspmpeg -lpspaudiocodec -lpspaudio -lpsppower  -lpspgum -lpspgu -lpsprtc -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = TH09x
PSP_EBOOT_ICON = icon.png

PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
include $(PSPSDK)/lib/build.mak

link:
	rm -rf Class/Beam.o
	make

