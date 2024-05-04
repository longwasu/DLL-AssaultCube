#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include "global.h"
using namespace std;

//Resolve pointer chain to get address of status value
uintptr_t RPC(vector<unsigned int> Offsets);

//Manage console and message
void SetupConsole();
void Welcome();
void CleanConsole();

//Restore game code
void UnjectAll();



