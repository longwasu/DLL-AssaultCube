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
static FILE* f_console = nullptr;  

void SetupConsole() {
    AllocConsole();  
    freopen_s(&f_console, "CONOUT$", "w", stdout);  
    Welcome();  
}

void CleanConsole() {
    if (f_console) {
        fclose(f_console); 
        f_console = nullptr; 
    }
    FreeConsole();
}

void Welcome() {
    cout << "===============AssaultCube hack================" << endl;
    cout << "Press 'F1': turn ON/OFF Extra Sensory Perception" << endl;
    cout << "Press 'F5': turn OFF hack" << endl;
    cout << "===============================================" << endl;
}

void UnjectAll() {
    if (ESP.active == true) {
        ESP.Toggle("ESP");
    } 
}







