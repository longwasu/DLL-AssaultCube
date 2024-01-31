// dllmain.cpp : Defines the entry point for the DLL application.
#include "header.h"
#include "hooking.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    cout << "===============AssaultCube hack================" << endl;
    cout << "Press 'F1': add more health, armor, ammo" << endl;
    cout << "Press 'F2': turn off hack" << endl;
    cout << "No recoil is automatically turn on" << endl;
    cout << "===============================================" << endl;
    
    vector<BYTE> noRecoil = { 0x90 };
    Inject((BYTE*)0x004C2EC3, noRecoil);

    while (true)
    {
        if (GetAsyncKeyState(VK_F2) & 1)
            break;
    }

    fclose(f);
    FreeConsole();
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

        CloseHandle(hThread);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

