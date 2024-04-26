// dllmain.cpp : Defines the entry point for the DLL application.
#include "header.h"
#include "entity.h"
#include "global.h"

extern Hooking ESP;

DWORD WINAPI HackThread(HMODULE hModule)
{
    SetupConsole();
    SetupGlobal();

    while (true) {   
        if (GetAsyncKeyState(VK_F1) & 1) {
            ESP.Toggle("ESP");
        }
        if (GetAsyncKeyState(VK_F5) & 1) {
            cout << "Closing hack..." << endl;
            UnjectAll();
            Sleep(3000);
            break;
        }
    }
 
    CleanConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) 
{
    HANDLE hThread;
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        
        //Create thread to inject dll
        hThread = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)HackThread, hModule, NULL, nullptr);
        if (hThread != NULL)
            CloseHandle(hThread);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

