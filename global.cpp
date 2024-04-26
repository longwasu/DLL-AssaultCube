#include "global.h"

//Global variable
Entity entity_list[32];
BYTE* wglSwapBuffers;
DWORD* espRetAddr;
Hooking ESP;


//Set up global variable
void SetupGlobal() {
	SetupEntityList(entity_list, GetNumberOfPlayer());

	HMODULE hOpenGL = GetModuleHandleA("opengl32.dll");
	if (hOpenGL != NULL) {
		wglSwapBuffers = (BYTE*)GetProcAddress(hOpenGL, "wglSwapBuffers");
	}
	
	if (wglSwapBuffers) {
		ESP.Setup(wglSwapBuffers, (BYTE*)EspCodeCave, 5);
	}
	
	espRetAddr = (DWORD*)(wglSwapBuffers + 5);

}

//ESP
float xCenter = 1200, yCenter = 870, widthDefault = 250, heightDefault = 700;
float distanceRatio;
__declspec(naked) void EspCodeCave() {
	__asm {
		mov edi, edi
		push ebp;
		mov ebp, esp
		pushad
	}
	
	distanceRatio = DistanceFromMe(entity_list[0], entity_list[1]) / 10;
	DrawBox(xCenter, yCenter, widthDefault / distanceRatio, heightDefault / distanceRatio, red);

	__asm {
		popad
		jmp espRetAddr;
	}
}

