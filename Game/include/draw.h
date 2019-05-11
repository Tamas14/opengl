#ifndef DRAW_H
#define DRAW_H

#include "game.h"

/**
 * Draw the game.
 */
void draw_game(Game* game);
GLuint load_texture(char* filename, int repeat);
void set_lightning();

#endif /* DRAW_H */
