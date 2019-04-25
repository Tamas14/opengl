#include "ball.h"
#include "utils.h"

void move_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
}

void start_ball(Ball* ball, float x, float y)
{

}

void draw_ball(Ball* ball)
{
}

void update_ball(Ball* ball, double time)
{

	ball->dir -= ball->turning*3;
	
    ball->x += ball->speed_x * cos(degree_to_radian(ball->dir));
    ball->y += ball->speed_x * sin(degree_to_radian(ball->dir));
}

