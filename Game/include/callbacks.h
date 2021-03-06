#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "game.h"
#include "camera.h"
#include "utils.h"
#include "draw.h"
#include "init.h"
#include <GL/glut.h>

/**
 * Game state object
 */
Game game;

/**
 * Call when need to display the graphical content.
 */
void display();

/**
 * Call after windows resizing.
 */
void reshape(GLsizei width, GLsizei height);

/**
 * Call after mouse event.
 */

void mouse(int button, int state, int x, int y);

/**
 * Call after keyboard event.
 */
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

/**
 * Call when there is no other event.
 */
void idle();

#endif