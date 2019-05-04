#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "pad.h"

/**
 * Game state representation
 */
typedef struct Game
{
    Ball ball;
	Pad pads[5];
	int numberOfPads;
	int rotation;
    int width;
    int height;
	int dir;
	double dist;
			 /** 
			  * 0 - előre
			  * 1 - balra
			  * 2 - jobbra
			  */
} Game;

/**
 * Resize the game and update positions.
 */
void resize_game(Game* game, int width, int height);

/**
 * Restart the game.
 */
void restart_game(Game* game);

/**
 * Update the state of the game.
 * @param time elapsed time in seconds
 */
void update_game(Game* game);
void shift(Game* game);
void generate(Game* game, int i);
void init(Game* game, int width, int height);
void mult(int rowsA, int colsA, int rowsB, int colsB, double a[rowsA][colsA], double b[rowsB][colsB], double c[rowsA][colsB]);



#endif /* GAME_H */
