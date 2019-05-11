#ifndef UTILS_H
#define UTILS_H

#define FALSE 0
#define TRUE 1

#include "game.h"

/**
 * GLSL-like three dimensional vector
 */
typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

/**
 * Color with RGB components
 */
typedef struct Color
{
    float red;
    float green;
    float blue;
} Color;

/**
 * Material
 */
typedef struct Material
{
    struct Color ambient; 
    struct Color diffuse; 
    struct Color specular; 
    float shininess;
} Material;

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);

/**
 * Sets up the scene for orthographics
 */
void Ortho(Game* game);

/**
 * Sets up the scene for projection
 */
void Perspective(Game* game);

/**
 * Draws text to the screen
 */
void drawTextToScreen(Game* game, float x, float y, char* s);

/**
 * Adding the numbers in an array
 */
int sumArray(int arr[], int len);

#endif /* UTILS_H */
