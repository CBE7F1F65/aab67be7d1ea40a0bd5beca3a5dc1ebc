PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)
TARGET_LIB = libluaplus.a
OBJS = 	LuaPlus/LuaPlusAddons.o LuaPlus/luathread.o LuaPlus/lwstrlib.o LuaPlus/popen.o LuaPlus/pt.o LuaPlus/srm.o LuaPlus/src/lapi.o LuaPlus/src/lauxlib.o LuaPlus/src/lbaselib.o LuaPlus/src/lcode.o LuaPlus/src/ldblib.o LuaPlus/src/ldebug.o LuaPlus/src/ldo.o LuaPlus/src/ldump.o LuaPlus/src/lfunc.o LuaPlus/src/lgc.o LuaPlus/src/linit.o LuaPlus/src/liolib.o LuaPlus/src/llex.o LuaPlus/src/lmathlib.o LuaPlus/src/lmem.o LuaPlus/src/loadlib.o LuaPlus/src/lobject.o LuaPlus/src/lopcodes.o LuaPlus/src/loslib.o LuaPlus/src/lparser.o LuaPlus/src/lstate.o LuaPlus/src/lstring.o LuaPlus/src/lstrlib.o LuaPlus/src/ltable.o LuaPlus/src/ltablib.o LuaPlus/src/ltm.o LuaPlus/src/lua.o LuaPlus/src/lundump.o LuaPlus/src/lvm.o LuaPlus/src/lzio.o LuaPlus/src/print.o	\
				LuaPlus/LuaCall.o LuaPlus/LuaObject.o LuaPlus/LuaPlus.o LuaPlus/LuaPlus_Libs.o LuaPlus/LuaPlusFunctions.o LuaPlus/LuaStackObject.o LuaPlus/LuaStackTableIterator.o LuaPlus/LuaState.o LuaPlus/LuaState_DumpObject.o LuaPlus/LuaStateOutFile.o LuaPlus/LuaTableIterator.o
INCDIR = LuaPlus/src
LIBDIR = 
CFLAGS = -G0 -w -O2
CXXFLAGS = $(CFLAGS) -fno-rtti 
ASFLAGS = $(CFLAGS)
PSP_FW_VERSION=371
PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
include $(PSPSDK)/lib/build.mak
install:$(TARGET_LIB)
	rm -rf ../lib/libluaplus.a
	cp libluaplus.a ../lib/
	cp LuaPlus/*.h ../include/LuaPlus
	cp LuaPlus/src/*.h ../include/LuaPlus/src
	