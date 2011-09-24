PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)
TARGET_LIB = libhge.a
OBJS =	core/font.o core/graphics.o core/ini.o core/input.o core/math.o core/random.o core/resource.o core/sound.o core/system.o core/timer.o \
				core/ZLIB/adler32.o core/ZLIB/compress.o core/ZLIB/crc32.o core/ZLIB/deflate.o core/ZLIB/gzio.o core/ZLIB/infback.o core/ZLIB/inffast.o core/ZLIB/inflate.o core/ZLIB/inftrees.o core/ZLIB/ioapi.o core/ZLIB/mztools.o core/ZLIB/trees.o core/ZLIB/uncompr.o core/ZLIB/unzip.o core/ZLIB/zip.o core/ZLIB/zutil.o \
				helpers/hgecolor.o helpers/hgeEffectSystem.o helpers/hgefont.o helpers/hgerect.o helpers/hgesprite.o helpers/hgevector.o \
				Exception/exception.o \
				PSP/PSP_framebuffer.o PSP/PSP_graphics.o
INCDIR = psp/include
LIBDIR = 
CFLAGS = -G0 -w -g -D__PSP
CXXFLAGS = $(CFLAGS) -fno-rtti
ASFLAGS = $(CFLAGS)
PSP_FW_VERSION=371
PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
include $(PSPSDK)/lib/build.mak
install:$(TARGET_LIB)
	rm -rf ../lib/libhge.a
	cp libhge.a ../lib/
	