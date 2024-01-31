#include "header.h"
#include <vector>

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






