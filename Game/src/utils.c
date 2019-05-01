#include "utils.h"
#include "GL/glut.h"

#include <math.h>
double MPI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067;

double degree_to_radian(double degree)
{
	return degree * MPI / 180.0;
}

void Perspective(Game* game) {
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, (double) game->width / game->height, 0.01, 20000.0);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Ortho(Game* game) {
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, game->width, 0, game->height, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void szovegKirajzolas(Game* game, float x, float y, char* s) {
    glDisable(GL_LIGHTING);
	Ortho(game);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glColor3f(128, 128, 128);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2f(x, y);
	unsigned i;
    for (i = 0; i < strlen(s); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
	
	Perspective(game);
    glEnable(GL_LIGHTING);
}
