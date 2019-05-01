#ifndef BALL_H
#define BALL_H
#include <GL/glut.h>
#include <obj/model.h>
#include <math.h>
/**
 * Ball position and speed
 */
Model ballmodel;
typedef struct Ball
{
    float x;
    float y;
    float dir;
    float speed_x;
	float vel_x;
	float vel_y;
	int acceleration;
    int turning;
} Ball;

void update_ball(Ball* ball);

#endif /* BALL_H */
