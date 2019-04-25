#ifndef PAD_H
#define PAD_H
#include <GL/glut.h>
#include <obj/model.h>
/**
 * Pad position and size
 */

GLuint textures[5];
Model padmodel;
Model car;
typedef struct Pad
{
	int size;
    float x;
    float y;
	int rotation;
	int dir;
} Pad;

int getTexture(int padIndex);

/**
 * Move the pad to the given position.
 * @param position required position of the pad
 * @param limit last reachable point of the pad
 */

#endif /* PAD_H */
