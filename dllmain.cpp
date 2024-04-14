// dllmain.cpp : Defines the entry point for the DLL application.
#include "header.h"
#include "entity.h"
#include "aimbot.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    FILE* f = SetupConsole();

    Entity entity_list[32];
    int NumberOfPlayer = RPC({ 0x18AC0C, 0x0 });
    SetupEntityList(entity_list, NumberOfPlayer);

    while (true) {
        if (GetAsyncKeyState(VK_F1) & 1) {
            cout << "Active aimbot!" << endl;
            
        }
        Aimbot(entity_list, NumberOfPlayer);
        if (GetAsyncKeyState(VK_F5) & 1) {
            cout << "Closing hack..." << endl;
            Sleep(3000);
            break;
        }
    }
    

 
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

