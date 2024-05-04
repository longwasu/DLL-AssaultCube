#include "hooking.h"

void Hooking::Setup(BYTE* hookLocation, BYTE* dstFunc, int len)
{
	this->hookLocation = hookLocation;
	this->len = len;
	this->dstFunc = dstFunc;
}

void Hooking::Inject() {
	VirtualProtect(hookLocation, len, PAGE_EXECUTE_READWRITE, &oldProtect);

	//Backup stolen bytes
	memcpy(stolenBytes, hookLocation, len);

	//Write to hook location
	*hookLocation = 0xE9;
	*(DWORD*)(hookLocation + 1) = (DWORD)(dstFunc - hookLocation - 5);

	//Fill remain byte with Nop
	for (int i = 5; i < len; i++) {
		*(hookLocation + i) = (BYTE)0x90;
	}
}

void Hooking::Unject()
{
	//Restore hook bytes
	memcpy(hookLocation, stolenBytes, len);

	DWORD oldProtect = this -> oldProtect;
	VirtualProtect(hookLocation, len, oldProtect, &oldProtect);
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