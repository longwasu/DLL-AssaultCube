#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <gl/GL.h>
#include <cmath>

//Screen size 2400x1800
//Ti le giua khoang cach va do dai/rong cua box la 1:1

extern GLubyte red[3];
extern GLubyte green[3];

void DrawBox(float x, float y, float width, float height, GLubyte color[3]);

