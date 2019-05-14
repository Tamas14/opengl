#ifndef ROAD_H
#define ROAD_H
#include <GL/glut.h>
#include <obj/model.h>

/**
 * Stores textures
 */
GLuint textures[10];

/**
 * Stores models
 */
Model roadModel;
Model obstacleModel;

/**
 * Struct for the road
 */
typedef struct Road
{
	int size;
	float x;
	float y;
	int rotation;
	int dir;
	int hasObstacle;
	float obstacleOffset;
} Road;

#endif