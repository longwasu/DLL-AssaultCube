#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <gl/GL.h>
#include <cmath>



extern GLubyte red[3];
extern GLubyte green[3];

void DrawBox(float x, float y, float width, float height, GLubyte color[3]);

