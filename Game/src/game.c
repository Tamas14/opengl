#include "game.h"

#include "utils.h"
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

int in = 0;
void update_game(Game* game)
{
    update_car(&game->car);
	
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