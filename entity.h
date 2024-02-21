#pragma once
#include <Windows.h>
#include "header.h"

struct Entity
{
	//entity status
	BYTE* playerBase = nullptr;
	BYTE* dead = nullptr;
	float* xCoord = nullptr;
	float* yCoord = nullptr;
	float* zCoord = nullptr;
	int* team = nullptr;
	int* playerNumber = nullptr;
	int* health = nullptr;
	char* name = nullptr;

	//Use for aimbot/ESP
	bool check = false;
	float xRelative = NULL;
	float yRelative = NULL;
	float zRelative = NULL;
	float distance = 99999.0f;

	//just for me
	float* yaw = nullptr;
	float* pitch = nullptr;

	void set_value(BYTE* playerBase);
};

struct Offsets
{
	//entity status
	DWORD dead = 0x76;
	DWORD xCoord = 0x28;
	DWORD yCoord = 0x30;
	DWORD zCoord = 0x2C;
	DWORD team = 0x30C;
	DWORD playerNumber = 0x1C4;
	DWORD health = 0xEC;
	DWORD name = 0x205;

	//just for me
	DWORD yaw = 0x38;
	DWORD pitch = 0x34;
};


void SetupEntityList();

