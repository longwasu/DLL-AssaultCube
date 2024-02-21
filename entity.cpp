#include "entity.h"

void Entity::set_value(BYTE* playerBase)
{
	this->playerBase = playerBase;
	this->dead = playerBase + 0x76;
	this->xCoord = (float*)(playerBase + 0x28);
	this->yCoord = (float*)(playerBase + 0x30);
	this->zCoord = (float*)(playerBase + 0x2C);
	this->team = (int*)(playerBase + 0x30C);
	this->playerNumber = (int*)(playerBase + 0x1C4);
	this->health = (int*)(playerBase + 0xEC);
	this->name = (char*)(playerBase + 0x205);

	//just for me
	this->yaw = (float*)(playerBase + 0x38);
	this->pitch = (float*)(playerBase + 0x34);
}

Entity entity_list[32];
void SetupEntityList() {
	int NumberOfPlayer = *((int*)RPC({ 0x18AC0C }));
	uintptr_t EntityPtr = RPC({ 0x18AC04, 0x0 });

	if (NumberOfPlayer > 0) {
		for (int i = 1; i < NumberOfPlayer; i++) {
			EntityPtr = EntityPtr + 4 * i;
			entity_list[i].set_value(*(BYTE**)EntityPtr);
		}
	}

	cout << "First entiy name: " << entity_list[1].name << endl;
}
