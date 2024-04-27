#pragma once
#include <Windows.h>
#include <cmath>
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
	float xGap = NULL;
	float yGap = NULL;
	float zGap = NULL;
	float distance = NULL;

	//just for me
	float* yaw = nullptr;
	float* pitch = nullptr;

	Entity() { }
	void set(BYTE* playerBase);
};

void UpdateEntity();

int GetNumberOfPlayer();

extern Entity entity_list[32];