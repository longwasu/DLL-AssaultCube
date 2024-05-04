#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <gl/GL.h>

extern GLubyte red[3];
extern GLubyte green[3];

void DrawBox(float x, float y, float width, float height, GLubyte color[3]);
void SetupOrtho();
void RestoreGL();

class vec2 {
public:
	float x = 0, y = 0;

	vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}
	
	vec2() {}
};

class vec3 {
public:
	float x = 0, y = 0, z = 0;

	vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3() { }
};


class vec4 {
public:
	float x = 0, y = 0, z = 0, w = 0;

	vec4() { }
};