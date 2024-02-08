// dllmain.cpp : Defines the entry point for the DLL application.
#include "header.h"
#include "hooking.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    FILE* f = SetupConsole();

    Hooking noRecoil((BYTE*)0x004C2EC3, 5, (BYTE*)noRecoilCode);
    Hooking superHealth((BYTE*)0x0041C223, 5, (BYTE*)superHealthCode);
    Hooking infiniteAmmo((BYTE*)0x004C73EF, 6, (BYTE*)infiniteAmmoCode);

    while (true) {
        if (GetAsyncKeyState(VK_F1) & 1) 
            noRecoil.Toggle("No recoil");
        if (GetAsyncKeyState(VK_F2) & 1) 
            superHealth.Toggle("Super health");
        if (GetAsyncKeyState(VK_F3) & 1)
            infiniteAmmo.Toggle("Infinite ammo");
        if (GetAsyncKeyState(VK_F5) & 1) {
            cout << "Closing hack..." << endl;
            Sleep(3000);
            break;
        }  
    }

    if (noRecoil.active)
        noRecoil.Toggle("No recoil");
    if (superHealth.active)
        superHealth.Toggle("Super health");
    if (infiniteAmmo.active)
        infiniteAmmo.Toggle("Infinite ammo");
    

    CleanConsole(f);
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

