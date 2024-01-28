// dllmain.cpp : Defines the entry point for the DLL application.
#include "header.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) 
{
    HANDLE hThread;
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        
        //Create thread to inject dll
        hThread = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)HackThread, hModule, NULL, nullptr);

        CloseHandle(hThread);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

