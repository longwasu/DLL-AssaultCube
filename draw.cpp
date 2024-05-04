#include "draw.h"

GLubyte red[3] = { 255, 0, 0 };
GLubyte green[3] = { 0, 255, 0 };

void DrawBox(float x, float y, float width, float height, GLubyte color[3]) {
    glLineWidth(1.0f);
    glBegin(GL_LINE_STRIP);
    glColor3ub(color[0], color[1], color[2]);
    glVertex2f(x, y);
    glVertex2f(x + width/2, y);
    glVertex2f(x + width/2, y + height);
    glVertex2f(x - width/2, y + height);
    glVertex2f(x - width/2, y);
    glVertex2f(x, y);
    glEnd();
}

void SetupOrtho()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void RestoreGL()
{
	glPopMatrix();
	glPopAttrib();
}