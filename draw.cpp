#include "draw.h"

GLubyte red[3] = { 255, 0, 0 };
GLubyte green[3] = { 0, 255, 0 };

void DrawBox(float x, float y, float width, float height, GLubyte color[3]) {
    glLineWidth(1.5f);
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