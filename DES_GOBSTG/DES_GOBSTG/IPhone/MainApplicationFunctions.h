#ifndef _MAINAPPLICATIONFUNCTIONS_H
#define _MAINAPPLICATIONFUNCTIONS_H


#ifdef __cplusplus
extern "C" {
#endif
	int Application_Init();
	int Application_Loop();
	int Application_Quit();
	const char * ResourceGetBaseDirectory();
	const char * ResourceGetAppDirectory();
	void TouchCallback_ButtonDown(float x, float y, int ID);
	void TouchCallback_ButtonUp(float x, float y, int ID);
	void TouchCallback_Move(float x, float y, int ID);
#ifdef __cplusplus
}
#endif
		
#endif