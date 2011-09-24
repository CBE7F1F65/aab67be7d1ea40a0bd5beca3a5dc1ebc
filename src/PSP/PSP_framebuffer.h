#if defined __PSP || defined __IPHONE
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#if defined __PSP
#include <psptypes.h>
#elif defined __IPHONE
#ifndef u32
typedef unsigned int u32;
#endif
#ifndef u8
typedef unsigned char u8;
#endif
#endif

extern u32* g_vram_base;

#endif
#endif // __PSP
