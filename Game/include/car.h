#ifndef CAR_H
#define CAR_H
#include <GL/glut.h>
#include <obj/model.h>
#include <math.h>

/**
 * Car struct
 */
Model snailModel;

typedef struct Car
{
    float x;
    float y;
    float dir;
    float speed_x;
	float vel_x;
	int acceleration;
    int turning;
} Car;

/**
 * Moving the car
 */
void update_car(Car* car);

#endif /* BALL_H */
