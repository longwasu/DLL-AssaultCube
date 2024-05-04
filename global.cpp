#include "global.h"

//Global variable
BYTE* wglSwapBuffers;
DWORD* espRetAddr;
Hooking ESP;

//Set up global variable
void SetupGlobal() {
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
__declspec(naked) void EspCodeCave() {
	__asm {
		mov edi, edi
		push ebp;
		mov ebp, esp
		pushad
	}

	SetupOrtho();
	DrawEsp();
	RestoreGL();

	__asm {
		popad
		jmp espRetAddr;
	}
}

