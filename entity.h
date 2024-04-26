#pragma once
#include <Windows.h>
#include <math.h>
#include "header.h"
#include "global.h"

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
	float distance = NULL;

	//just for me
	float* yaw = nullptr;
	float* pitch = nullptr;

	void set_value(BYTE* playerBase);

	
};

void SetupEntityList(Entity entity_list[32], int NumberOfPlayer);

int GetNumberOfPlayer();

float DistanceFromMe(Entity player, Entity enemy);