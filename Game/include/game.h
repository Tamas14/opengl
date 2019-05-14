#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <math.h>
#include "car.h"
#include "road.h"
#include "GL/glut.h"

/**
 * Game state representation
 */
typedef struct Game
{
	Car car;
	Road roads[5];
	int numberOfPads;
	int rotation;
	int width;
	int height;
	int dir;
	double dist;
	int gameOver;
	int drawhelp;
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
 */
void update_game(Game* game);

/**
 * Sets up the game with default parameters
 */
void init(Game* game, int width, int height);

#endif