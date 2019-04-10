#ifndef PAD_H
#define PAD_H
#include <GL/glut.h>
#include <obj/model.h>
/**
 * Pad position and size
 */

GLuint textures[5];
Model padmodel;
typedef struct Pad
{
	int size;
    float x;
    float y;
} Pad;

/**
 * Move the pad to the given position.
 * @param position required position of the pad
 * @param limit last reachable point of the pad
 */

#endif /* PAD_H */
