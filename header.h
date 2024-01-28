#pragma once
#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
using namespace std;

//Resolve pointer chain
uintptr_t RPC(uintptr_t base, vector<unsigned int> Offsets);
//Overwrite game code
DWORD WINAPI Change_game_code(unsigned char* hook_location, unsigned char byte_to_write[]);
//Start hack
DWORD WINAPI HackThread(HMODULE hModule);





