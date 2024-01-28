#include "header.h"


//Resolve pointer chain function
uintptr_t RPC(uintptr_t base, vector<unsigned int> Offsets)
{
    uintptr_t addr = base;
    addr += Offsets[0];
    for (unsigned int i = 1; i < Offsets.size(); i++)
    {
        addr = *(uintptr_t*)addr;
        addr = addr + Offsets[i];
    }
    return addr;
}

//Overwrite game code
DWORD WINAPI Change_game_code(unsigned char* hook_location, unsigned char byte_to_write[])
{
    SIZE_T dwSize = sizeof(byte_to_write);
    DWORD oldProtect;

    VirtualProtect((void*)hook_location, dwSize, PAGE_EXECUTE_READWRITE, &oldProtect);
    for (unsigned int i = 0; i < sizeof(byte_to_write); i++)
    {
        *(hook_location + i) = byte_to_write[i];
    }

    return 0;
}

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

    //No recoil
    unsigned char* hook_location = (unsigned char*)0x004C2EC3;
    unsigned char byte_to_write[5] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
    Change_game_code(hook_location, byte_to_write);

    //Add health, armo, ammo
    uintptr_t BaseAddr = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    uintptr_t Playerent = *(uintptr_t*)(BaseAddr + 0x17E0A8);

    int* HealthAddr = (int*)RPC(Playerent, { 0xEC });
    int* ArmorAddr = (int*)RPC(Playerent, { 0xF0 });
    int* AmmoAddr = (int*)RPC(Playerent, { 0x364, 0x14, 0x0 });

    while (true)
    {
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            *HealthAddr += 50;
            *ArmorAddr +=50;
            *AmmoAddr +=50;
            cout << "+50 health, +50 armor, +50 current weapon ammo" << endl;
        }

        if (GetAsyncKeyState(VK_F2) & 1)
        {
            cout << "Closing hack..." << endl;
            Sleep(3000);
            break;
        }   
    }

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}




