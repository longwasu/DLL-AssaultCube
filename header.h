#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;

//Resolve pointer chain to get address of status value
uintptr_t RPC(vector<unsigned int> Offsets);

//Manage console and message
FILE* SetupConsole();
void Welcome();
void CleanConsole(FILE* f);



