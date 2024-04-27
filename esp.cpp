#include "esp.h"

void DrawEsp() {
	UpdateEntity();
	float xDefault = 1200, yDefault = 870, widthDefault = 250, heightDefault = 700;
	float distanceRatio = entity_list[1].distance / 10;
	float y = yDefault + (*entity_list[0].pitch * 23);

	float newPitch = atan(entity_list[1].zGap / entity_list[1].yGap);
	
	DrawBox(xDefault, y, widthDefault / distanceRatio, heightDefault / distanceRatio, red);
	
}


