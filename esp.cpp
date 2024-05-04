#include "esp.h"

int viewport[4];

void DrawEsp() {
	glGetIntegerv(GL_VIEWPORT, viewport);
	UpdateEntity();
	for (int i = 1; i < GetNumberOfPlayer(); i++) {
		vec3 entityCoord(*entity_list[i].xCoord, *entity_list[i].yCoord, *entity_list[i].zCoord + 5);
		vec2 screenCoord;
		float distanceRatio = entity_list[i].distance / 10;
		float defaultWidth = 120, defaultHeight = 280;

		if (WorldToScreen(entityCoord, screenCoord)) {
			GLubyte *color;
			if (*entity_list[i].team != *entity_list[0].team)
				color = red;
			else
				color = green;
			DrawBox(screenCoord.x, screenCoord.y, defaultWidth / distanceRatio, defaultHeight / distanceRatio, color);
		}
	}
}

bool WorldToScreen(vec3& entityCoord, vec2& screenCoord) {
	float w2sMatrix[16];
	memcpy(w2sMatrix, (float*)0x57DFD0, sizeof(w2sMatrix));

	vec4 clipCoord;
	clipCoord.w = w2sMatrix[3] * entityCoord.x + w2sMatrix[7] * entityCoord.y + w2sMatrix[11] * entityCoord.z + w2sMatrix[15];
	if (clipCoord.w < 0.1f)
		return false;

	clipCoord.x = w2sMatrix[0] * entityCoord.x + w2sMatrix[4] * entityCoord.y + w2sMatrix[8] * entityCoord.z + w2sMatrix[12];
	clipCoord.y = w2sMatrix[1] * entityCoord.x + w2sMatrix[5] * entityCoord.y + w2sMatrix[9] * entityCoord.z + w2sMatrix[13];
	clipCoord.z = w2sMatrix[2] * entityCoord.x + w2sMatrix[6] * entityCoord.y + w2sMatrix[10] * entityCoord.z + w2sMatrix[14];

	vec3 normalize;
	normalize.x = clipCoord.x / clipCoord.w;
	normalize.y = clipCoord.y / clipCoord.w;
	normalize.z = clipCoord.z / clipCoord.w;

	screenCoord.x = (screenWidth / 2 * normalize.x) + (screenWidth / 2 + normalize.x);
	screenCoord.y = -(screenHeight / 2 * normalize.y) + (screenHeight / 2 + normalize.y);
	return true;
}

