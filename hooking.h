#pragma once
#include <Windows.h>
#include <iostream>
using namespace std;

struct Hooking
{
	BYTE* hookLocation{ nullptr };
	BYTE* dstFunc{ nullptr };
	int len{ 0 };
	bool active = false;
	uintptr_t return_addr;
	BYTE stolenBytes[10] = { 0 };
	DWORD oldProtect;

	Hooking() { }

	void Setup(BYTE* hookLocation, BYTE* dstFunc, int len);
	
	void Inject();
	
	void Unject();

	void Toggle(string name);
};