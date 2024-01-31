#pragma once

#include "header.h"
#include <vector>

DWORD WINAPI Inject(BYTE* hook_location, vector<BYTE> InjectCode);

