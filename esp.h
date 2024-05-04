#pragma once
#include "entity.h"
#include "draw.h"
#include "global.h"

#define M_PI 3.14159265358979323846 
#define screenWidth viewport[2]
#define screenHeight viewport[3]

extern int viewport[4];

void DrawEsp();

bool WorldToScreen(vec3& entityCoord, vec2& screenCoord);

