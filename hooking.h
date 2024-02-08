#pragma once

#include <Windows.h>
#include <iostream>
#include <string.h>
using namespace std;

struct Hooking
{
	BYTE* Hook{ nullptr };
	BYTE* desiredFunction{ nullptr };

	bool active = false;

	uintptr_t return_addr;

	BYTE StolenBytes[10] = { 0 };
	int NumberOfByte = 0;

	Hooking(){}
	Hooking(BYTE* Hook, int NumberOfByte, BYTE* desiredFunction);
	
	void Inject();
	
	void Unject();

	void Toggle(string name);

	void Notifi(const char name[]);
};

