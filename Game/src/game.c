#include "game.h"
#include "utils.h"
#include "GL/glut.h"
#include <stdio.h>
#include <math.h>

void resize_game(Game* game, int width, int height)
{
	game->width = width;
    game->height = height;
}

void init(Game* game, int width, int height)
{
	game->gameOver = 0;
	game->dir = 0;
	game->rotation = 0;
    game->width = width;
    game->height = height;
    game->dist = 0;
	game->numberOfPads = sizeof(game->roads)/sizeof(game->roads[0]);
	int i;
	
	game->car.x = 0;
	game->car.y = 0;
	game->car.dir = -90;
	
	game->roads[0].size = 200;
	game->roads[0].x = 0;
	game->roads[0].y = 0;
	game->roads[0].rotation = 0;
	game->roads[0].dir = 1;
	game->roads[0].hasAkadaly = 0;
	
	for(i = 1; i < game->numberOfPads; i++)
	{
		generate(game, i);
	}
}

void shift(Game* game)
{
	int i;
	for(i = 1; i < game->numberOfPads; i++)
	{
		game->roads[i-1] = game->roads[i];
	}
}

void generate(Game* game, int i)
{
	int newx, newy, ymove;
	Road* troads = game->roads;
	
	if(i == 1)
		game->dir = 0;
	else
		game->dir = (rand()%3-1);
	
	if(game->dir == 0)
	{
		ymove = -1;
		troads[i].hasAkadaly = rand()%2;
	}
	else
		ymove = 0;
	
	game->rotation = (game->rotation + 90*game->dir*(-1)) % 360;
	
	double angle = degree_to_radian(game->rotation);
	
	double a[2][2]; 
	a[0][0] = cos(angle);
	a[0][1] = -sin(angle);
	a[1][0] = sin(angle);
	a[1][1] = cos(angle);
					  
	double b[2][1] = {{game->dir}, {ymove}};
	double c[2][1];
	
	mult(2, 2, 2, 1, a, b, c);

	newx = troads[i-1].size*c[0][0] + troads[i-1].x;
	newy = troads[i-1].size*c[1][0] + troads[i-1].y;
	
	newx = round(newx/10.0)*10;
	newy = round(newy/10.0)*10;
	
	troads[i].x = newx;
	troads[i].y = newy;
	troads[i].size = troads[i-1].size;
	troads[i].dir = game->dir+1;
	
	if(game->dir != 0)
		if(game->dir == -1)
			troads[i].rotation = game->rotation;
		else
			troads[i].rotation = game->rotation - 180;
		
	else
		troads[i].rotation = game->rotation;
	
}

void mult(int rowsA, int colsA, int rowsB, int colsB, double a[rowsA][colsA], double b[rowsB][colsB], double c[rowsA][colsB])
{
	int i, j, k;
	double sum = 0.0;
	
	for (i = 0; i < rowsA; i++) {
      for (j = 0; j < colsB; j++) {
        for (k = 0; k < colsA; k++) {
          sum = sum + a[i][k]*b[k][j];
        }

        c[i][j] = sum;
        sum = 0;
      }
    }
}

int in = 0;
void update_game(Game* game)
{
    update_ball(&game->car);
	
	
	float car_x = game->car.x;
	float car_y = game->car.y;
	int isin[game->numberOfPads], i;
	
	for(i = 0; i < game->numberOfPads; i++)
	{
		float x1 = game->roads[i].x;
		float y1 = game->roads[i].y;
		float shalf = game->roads[i].size/2;
		
		isin[i] = 0;
		if( x1-shalf < car_x && y1-shalf < car_y &&
			x1+shalf > car_x && y1+shalf > car_y)
		{
			isin[i] = 1;
		}
	}
	
	if(isin[1])
		in = 1;
	
	if(in && isin[2])
	{
		in = 0;
		shift(game);
		generate(game, game->numberOfPads-1);
	}
	
	if(sumArray(isin, game->numberOfPads) < 1 || isin[3] || isin[4])
	{
		game->gameOver = 1;
		game->car.acceleration = 2;
	}
}


