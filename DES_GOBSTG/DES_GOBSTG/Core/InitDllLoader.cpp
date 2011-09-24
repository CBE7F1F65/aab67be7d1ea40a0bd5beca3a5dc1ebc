#if defined WIN32
#include "../Header/MainDependency.h"

#pragma init_seg(lib)

static class InitDllLoader {
public:
	InitDllLoader() 
	{
		modulehge = LoadLibraryA(DEFAULT_HGEDLLPATH);
	}

	~InitDllLoader() 
	{
		FreeLibrary(modulehge);
	}

private:

	HMODULE modulehge;

} _initDllLoader;
#endif