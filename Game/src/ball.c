#include "ball.h"
#include "utils.h"


void update_ball(Ball* ball)
{
	ball->dir -= ball->turning*3;
	
	if(ball->acceleration == 0)
		ball->vel_x -= 0.02;
	else
		ball->vel_x += 0.07;
	
	if(ball->speed_x <= 0 && !ball->acceleration)
	{
		ball->speed_x = 0;
		ball->vel_x = 0;
	}
	
	if(ball->speed_x > 50 && ball->acceleration)
		ball->vel_x = 0;
	
	if(ball->speed_x > 50 && !ball->acceleration)
		ball->vel_x = -0.02;
	
	ball->speed_x += ball->vel_x;
	
    ball->x += ball->speed_x/10 * cos(degree_to_radian(ball->dir));
    ball->y += ball->speed_x/10 * sin(degree_to_radian(ball->dir));
}

