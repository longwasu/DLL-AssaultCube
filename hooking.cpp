#include "hooking.h"

Hooking::Hooking(BYTE* Hook, int NumberOfByte, BYTE* desiredFunction)
{
	this->Hook = Hook;
	this->NumberOfByte = NumberOfByte;
	memcpy(StolenBytes, Hook, NumberOfByte);	//save original byte
	this->desiredFunction = desiredFunction;
	//set up bytes in code cave

}

void Hooking::Inject()
{
	DWORD oldProtect;
	VirtualProtect((VOID*)Hook, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

	//Write to hook location
	*Hook = 0xE9;
	*(uintptr_t*)(Hook + 1) = (uintptr_t)desiredFunction - ((uintptr_t)Hook + 5);

	//Fill remain byte with Nop
	for (int i = 5; i < NumberOfByte; i++)
	{
		*(BYTE*)(Hook + i) = (BYTE)0x90;
	}
}

void Hooking::Unject()
{
	//Restore hook bytes
	memcpy(Hook, StolenBytes, NumberOfByte);
}


void Hooking::Toggle(string name)
{
	active = !active;
	if (active) {
		Inject();
		cout << name << ": TURN ON" << endl;
	}
	else {
		Unject();
		cout << name << ": TURN OFF" << endl;
	}
		
}