#include "entity.h"

Entity entity_list[32];

void Entity::set(BYTE* playerBase)
{
	this->playerBase = playerBase;
	this->dead = playerBase + 0x76;
	this->xCoord = (float*)(playerBase + 0x28);
	this->yCoord = (float*)(playerBase + 0x2C);
	this->zCoord = (float*)(playerBase + 0x30);
	this->team = (int*)(playerBase + 0x30C);
	this->playerNumber = (int*)(playerBase + 0x1C4);
	this->health = (int*)(playerBase + 0xEC);
	this->name = (char*)(playerBase + 0x205);

	//just for me
	this->yaw = (float*)(playerBase + 0x34);
	this->pitch = (float*)(playerBase + 0x38);

	xGap = *xCoord - *entity_list[0].xCoord;
	yGap = *yCoord - *entity_list[0].yCoord;
	zGap = *zCoord - *entity_list[0].zCoord;
	distance = sqrt(xGap*xGap + yGap*yGap);
}

void UpdateEntity() {
	BYTE* EntityPtr = (BYTE*)RPC({ 0x18AC04, 0x0 });
	BYTE* local_player = (BYTE*)RPC({ 0x17E0A8, 0x0 });
	entity_list[0].set(local_player);

	if (GetNumberOfPlayer() > 0) {	
		for (int i = 1; i < GetNumberOfPlayer(); i++) {
			BYTE* entity_addr = *(BYTE**)(EntityPtr + 4 * i);
			entity_list[i].set(entity_addr);
		}
	}
}

int GetNumberOfPlayer() {
	HMODULE base = GetModuleHandle(L"ac_client.exe");
	int NumberOfPlayer = *(int*)((int)base + 0x18AC0C);
	return NumberOfPlayer;
}

	

