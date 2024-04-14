#include "entity.h"

Entity::Entity() {

}

void Entity::set_value(BYTE* playerBase)
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
	this->yaw = (float*)(playerBase + 0x38);
	this->pitch = (float*)(playerBase + 0x34);
}


void SetupEntityList(Entity entity_list[32], int NumberOfPlayer) {
	uintptr_t EntityPtr = RPC({ 0x18AC04, 0x0 });
	uintptr_t local_player = RPC({ 0x17E0A8, 0x0 });
	entity_list[0].set_value((BYTE*)local_player);

	if (NumberOfPlayer > 0) {
		for (int i = 1; i < NumberOfPlayer; i++) {
			BYTE* entity_addr = *(BYTE**)(EntityPtr + 4*i);
			entity_list[i].set_value(entity_addr);
		}
	}
}
	

