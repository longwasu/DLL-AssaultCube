#include "header.h"

//No recoil code
uintptr_t return_addr_recoil = 0x004C2EC8;
__declspec(naked) void noRecoilCode() {
    __asm {
        add[esi + 38], 0
        jmp return_addr_recoil
    }
}

//Super health mode
uintptr_t return_addr_health = 0x0041C228;
uintptr_t target_health;
uintptr_t local_player_health;
__declspec(naked) void superHealthCode() {
    __asm {
        mov eax, esi
        pushad
        //sub [ebx+04],esi
        lea ecx, [ebx + 04]
        mov edx, offset target_health
        mov[edx], ecx
    }

    //If local player, subtract only 1 health
    local_player_health = GetPlayerHealth();
    if (target_health == local_player_health) {
        __asm {
            popad
            dec[ebx + 04]
        }
    }
    else {
        __asm {
            popad
            sub[ebx + 04], esi
        }
    }

    __asm {
        jmp return_addr_health
    }
}

//Infinite Ammo code
uintptr_t return_addr_Ammo = 0x004C73F5;
uintptr_t local_player_ammo;
uintptr_t target_ammo;
__declspec(naked) void infiniteAmmoCode() {
    __asm {
        dec[eax]
        pushad
        mov ebx, offset target_ammo
        mov[ebx], eax
    }

    local_player_ammo = GetPlayerAmmo();
    if (target_ammo == local_player_ammo) {
        if (*(uintptr_t*)local_player_ammo == 1) {
            __asm {
                popad
                pushad
                add[eax], 20
            }
        }
    }
        
    __asm {
        popad
        lea eax, [esp + 0x1C]
        jmp return_addr_Ammo
    }
}




//Resolve pointer chain
uintptr_t RPC(vector<unsigned int> Offsets) {
    HMODULE base = GetModuleHandle(L"ac_client.exe");
    uintptr_t addr = (uintptr_t)base;

    for (unsigned int i = 0; i < Offsets.size() - 1; i++) {
        addr = *(uintptr_t*)(addr + Offsets[i]);
    }

    addr = addr + Offsets[Offsets.size() - 1];
    return addr;
}
//Funtion using RPC(resolve pointer chain) so that it does not affect stack.
uintptr_t GetPlayerHealth() {
    return RPC({ 0x17E0A8, 0xEC });
}
uintptr_t GetPlayerAmmo() {
    /*return RPC({ 0x17E0A8, 0x364, 0x14, 0 });*/
    return RPC({ 0x17E0A8, 0x140 });
}



//Manage console and message
FILE* SetupConsole() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    Welcome();
    return f;
}
void CleanConsole(FILE *f) {
    fclose(f);
    FreeConsole();
}
void Welcome() {
    cout << "===============AssaultCube hack================" << endl;
    cout << "Press 'F1': turn ON/OFF no recoil" << endl;
    cout << "Press 'F2': turn ON/OFF tanker mode" << endl;
    cout << "Press 'F3': turn ON/OFF infinite ammo" << endl;
    cout << "Press 'F5': turn OFF hack" << endl;
    cout << "===============================================" << endl;
}






