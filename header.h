#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;

//Code cave 
void noRecoilCode();
void superHealthCode();
void infiniteAmmoCode();

//Resolve pointer chain to get address of status value
uintptr_t RPC(vector<unsigned int> Offsets);
uintptr_t GetPlayerHealth();
uintptr_t GetPlayerAmmo();

//Manage console and message
FILE* SetupConsole();
void Welcome();
void CleanConsole(FILE* f);



