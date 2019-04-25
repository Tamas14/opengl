#include "game.h"
#include "utils.h"
#include "GL/glut.h"
#include <math.h> 

void resize_game(Game* game, int width, int height)
{
	
}

void init(Game* game, int width, int height)
{
	game->dir = 0;
	game->rotation = 0;
    game->width = width;
    game->height = height;
	game->numberOfPads = sizeof(game->pads)/sizeof(game->pads[0]);
	int i;
	
	game->ball.x = 0;
	game->ball.y = 0;
	game->ball.dir = -90;
	
	game->pads[0].size = 100;
	game->pads[0].x = 0;
	game->pads[0].y = 0;
	game->pads[0].rotation = 0;
	game->pads[0].dir = 1;
	
	for(i = 1; i < game->numberOfPads; i++)
	{
		generate(game, i);
	}
}

void restart_game(Game* game)
{
    float center_x;
    float center_y;

    center_x = game->width / 2;
    center_y = game->height / 2;

    start_ball(&(game->ball), center_x, center_y);
}

void shift(Game* game)
{
	int i;
	for(i = 1; i < game->numberOfPads; i++)
	{
		game->pads[i-1] = game->pads[i];
	}
}

void generate(Game* game, int i)
{
	int newx, newy, ymove;
	Pad* tpads = game->pads;
	game->dir = (rand()%3-1);
	
	if(game->dir == 0)
		ymove = -1;
	else
		ymove = 0;
	
	game->rotation = (game->rotation + 90*game->dir*(-1)) % 360;
	
	double angle = degree_to_radian(game->rotation);
	
	/*double a[2][2] = { {cos(angle), -sin(angle)},
					  {sin(angle),  cos(angle)} }; */
	double a[2][2]; 
	a[0][0] = cos(angle);
	a[0][1] = -sin(angle);
	a[1][0] = sin(angle);
	a[1][1] = cos(angle);
					  
	double b[2][1] = {{game->dir}, {ymove}};
	double c[2][1];
	
	mult(2, 2, 2, 1, a, b, c);

	newx = tpads[i-1].size*c[0][0] + tpads[i-1].x;
	newy = tpads[i-1].size*c[1][0] + tpads[i-1].y;
	
	newx = round(newx/10.0)*10;
	newy = round(newy/10.0)*10;
	
	tpads[i].x = newx;
	tpads[i].y = newy;
	tpads[i].size = tpads[i-1].size;
	tpads[i].dir = game->dir+1;
	
	if(game->dir != 0)
		if(game->dir == -1)
			tpads[i].rotation = game->rotation;
		else
			tpads[i].rotation = game->rotation - 180;
		
	else
		tpads[i].rotation = game->rotation;
	int j;
	printf("----- \n");
	printf("%d, %d %d \n", i, game->dir, game->rotation);
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

void update_game(Game* game, double time)
{
    update_ball(game, time);
}


