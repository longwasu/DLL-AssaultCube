#include "header.h"

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








