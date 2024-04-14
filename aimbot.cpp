#include "aimbot.h"

void CalculateDistance(Entity* entity_list, int NumberOfPlayer) {
	if (NumberOfPlayer > 0) {
		for (int i = 1; i < NumberOfPlayer; i++) {
			float xGap = *(entity_list+0)->xCoord - *(entity_list+i)->xCoord;
			float yGap = *(entity_list + 0)->yCoord - *(entity_list+i)->yCoord;
			float zGap = *(entity_list + 0)->zCoord - *(entity_list+i)->zCoord;
			float distance = sqrt(xGap * xGap + yGap * yGap + zGap * zGap);
			(entity_list+i)->distance = distance;
		}
	}
}


void Aimbot(Entity entity_list[32], int NumberOfPlayer) {
	CalculateDistance(entity_list, NumberOfPlayer);
    for (int i = 1; i < NumberOfPlayer; i++) {
        if (*entity_list[i].team != *entity_list[0].team && entity_list[i].distance < 40 && entity_list[i].distance > 10 && *entity_list[i].dead == 0) {
			float xGap = *entity_list[i].xCoord - *entity_list[0].xCoord;
			float yGap = *entity_list[i].yCoord - *entity_list[0].yCoord;
			float zGap = *entity_list[i].zCoord - *entity_list[0].zCoord;

			//yaw
			float newYaw = rad2degree(atan(zGap / entity_list[i].distance));
			*entity_list[0].yaw = newYaw;

			//pitch
			float newPitch = abs(rad2degree(atan(xGap / yGap)));
			if (*entity_list[i].xCoord > *entity_list[0].xCoord && *entity_list[i].yCoord < *entity_list[0].yCoord)
				newPitch = newPitch + 0;
			else if (*entity_list[i].xCoord > *entity_list[0].xCoord && *entity_list[i].yCoord > *entity_list[0].yCoord) {
				newPitch = 90 - newPitch;
				newPitch = newPitch + 90;
			}
			else if (*entity_list[i].xCoord < *entity_list[0].xCoord && *entity_list[i].yCoord > *entity_list[0].yCoord)
				newPitch = newPitch + 180;
			else {
				newPitch = 90 - newPitch;
				newPitch = newPitch + 270;
			}
				
			*entity_list[0].pitch = newPitch;
        }
    }
}

float rad2degree(float radian) {
	return (float)(radian / M_PI) * 180;
}