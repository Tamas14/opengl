#include "callbacks.h"
#include "init.h"
#include "time.h"
#include <stdio.h>
#include <GL/glut.h>

void set_callbacks()
{
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
    glutIdleFunc(idle);
}

int main(int argc, char* argv[])
{
    int window;
	srand(time(NULL));
    glutInit(&argc, argv);

    glutInitWindowSize(1000, 800);   
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    window = glutCreateWindow("Snail on a road");
    glutSetWindow(window);

	init(&game, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    init_opengl();
    set_callbacks();

    glutMainLoop();

    return 0;
}