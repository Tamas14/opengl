#include "game.h"
#include "GL/glut.h"
void resize_game(Game* game, int width, int height)
{
	
}

void init(Game* game, int width, int height)
{
	game->dir = 0;
	game->axis = 0;
    game->width = width;
    game->height = height;
	game->numberOfPads = sizeof(game->pads)/sizeof(game->pads[0]);
	int i;
	
	game->pads[0].size = 50;
	//game->pads[0].x = width/2-game->pads[0].size/2;
	game->pads[0].x = 0;
	//game->pads[0].y = height/2-game->pads[0].size/2;
	game->pads[0].y = 0;
	
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
	Pad* tpads = game->pads;
	game->dir = rand()%3;
	int data = 10*game->dir + game->axis;

	switch(data)
	{
		case 0:
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x;
			tpads[i].y = tpads[i-1].y - tpads[i].size;
		break;
		
		case 1:
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x + tpads[i].size;
			tpads[i].y = tpads[i-1].y;
		break;
		
		case 2:
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x;
			tpads[i].y = tpads[i-1].y + tpads[i].size;
		break;
		
		case 3:
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x - tpads[i].size;
			tpads[i].y = tpads[i-1].y;
		break;
		
		case 10:
			game->axis = (game->axis+3)%4;
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x - tpads[i].size;
			tpads[i].y = tpads[i-1].y;
		break;
		
		case 11:
			game->axis = (game->axis+3)%4;
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x;
			tpads[i].y = tpads[i-1].y - tpads[i].size;
		break;
		
		case 12:
			game->axis = (game->axis+3)%4;
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x + tpads[i].size;
			tpads[i].y = tpads[i-1].y;
		break;
		
		case 13:
			game->axis = (game->axis+3)%4;
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x;
			tpads[i].y = tpads[i-1].y + tpads[i].size;
		break;
		
		case 20:
			game->axis = (game->axis+1)%4;
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x + tpads[i].size;
			tpads[i].y = tpads[i-1].y;
		break;
		
		case 21:
			game->axis = (game->axis+1)%4;
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x;
			tpads[i].y = tpads[i-1].y + tpads[i].size;
		break;
		
		case 22:
			game->axis = (game->axis+1)%4;
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x - tpads[i].size;
			tpads[i].y = tpads[i-1].y;
		break;
		
		case 23:
			game->axis = (game->axis+1)%4;
			tpads[i].size = tpads[i-1].size;
			tpads[i].x = tpads[i-1].x;
			tpads[i].y = tpads[i-1].y - tpads[i].size;
		break;
	}
	
	 
}


void update_game(Game* game, double time)
{
    
}


