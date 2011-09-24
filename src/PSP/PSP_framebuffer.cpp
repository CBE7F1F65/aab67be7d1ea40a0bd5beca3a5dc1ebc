#if defined __PSP || defined __IPHONE

#if defined __PSP
#include <psptypes.h>
#endif

#include "PSP_graphics.h"

Color* g_vram_base = (Color*) (0x40000000 | 0x04000000);
#endif // __PSP
