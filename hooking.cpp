#include "hooking.h"

DWORD WINAPI Inject(BYTE* HookLocation, vector<BYTE> InjectCode)
{
	vector <BYTE> saveSF = { 0x60, 0x9C };
	vector <BYTE> restoreSF = { 0x9D, 0x61 };
	vector <BYTE> bytecode;

	bytecode.insert(bytecode.end(), saveSF.begin(), saveSF.end());
	bytecode.insert(bytecode.end(), InjectCode.begin(), InjectCode.end());
	bytecode.insert(bytecode.end(), restoreSF.begin(), restoreSF.end());

	BYTE* CodeCave = (BYTE*)VirtualAlloc(nullptr, 100, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	DWORD oldProtect;
	VirtualProtect((VOID*)HookLocation, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

	uintptr_t CodeCaveOffset = (uintptr_t)CodeCave - ((uintptr_t)HookLocation + 5);
	*HookLocation = 0xE9;
	*(uintptr_t*)(HookLocation + 1) = (uintptr_t)CodeCaveOffset;

	int loop = saveSF.size() + restoreSF.size() + InjectCode.size();
	for (int i = 0; i < loop; i++)
	{
		*(CodeCave + i) = bytecode[i];
	}

	uintptr_t returnOffset = ((uintptr_t)HookLocation + 5) - ((uintptr_t)CodeCave + loop + 5);
	*(CodeCave + loop) = 0xE9;
	*(uintptr_t*)(CodeCave + loop + 1) = (uintptr_t)returnOffset;

	return 0;
}

