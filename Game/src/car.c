#include "car.h"
#include "utils.h"

void update_car(Car* car)
{
	car->dir -= car->turning*3;
	
	if(car->acceleration == 1)
	{
		car->vel_x += 0.05;
		
		if(car->speed_x+car->vel_x > 50)
			car->vel_x = 0;
	}else if(car->acceleration == 2)
	{
		car->vel_x = -5;
	}else if(car->acceleration == 3)
		car->vel_x = -50;
	
	
	car->speed_x += car->vel_x;
	
	if(car->speed_x < 0)
		car->speed_x = 0;
	
	
	car->x += car->speed_x/10 * cos(degree_to_radian(car->dir));
	car->y += car->speed_x/10 * sin(degree_to_radian(car->dir));
}