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
    int turning;
} Ball;

/**
 * Move the ball to the given position.
 */
void move_ball(Ball* ball, float x, float y);

/**
 * Start the ball from the given position.
 */
void start_ball(Ball* ball, float x, float y);
void draw_ball(Ball* ball);

/**
 * Update the ball.
 * @param time elapsed time in seconds.
 */
void update_ball(Ball* ball, double time);

#endif /* BALL_H */
