#include "../Header/Main.h"
#include "../Header/Export.h"


#ifdef __PSP
#include <pspkernel.h>
PSP_MODULE_INFO("h5nc", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(0);
PSP_HEAP_SIZE_KB(-256);
extern "C"
{
#include "../../../include/exception.h"
};
#endif // __PSP

HGE *hge = NULL;

int gametime = 0;

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0x00000000);

	hge->Gfx_EndScene();
	
	return false;
}

bool FrameFunc()
{
	return false;
}

#ifdef __WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main(int argc, char* argv[])
#endif
{
#ifdef __PSP
	initExceptionHandler();
#endif
	hge = hgeCreate(HGE_VERSION);
	
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);

	Export::clientInitial(true);

	if(hge->System_Initiate())
	{
		gametime = 0;
//		Process::mp.state = STATE_INIT;
		hge->System_Start();
	}

	//
	//////////////////////////////////////////////////////////////////////////
//	Process::mp.Realease();

//	hge->System_Shutdown();
	Export::Release();

	return 0;
}