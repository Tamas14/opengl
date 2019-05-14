#ifndef UTILS_H
#define UTILS_H

#define FALSE 0
#define TRUE 1
#define VIEWPORT_RATIO (16.0 / 8.5)
#define VIEWPORT_ASPECT 80.0

#include "GL/glut.h"
#include "game.h"

#include <SOIL/SOIL.h>
#include <math.h>

typedef GLubyte Pixel[3];

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

GLuint load_texture(char* filename);

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
void Perspective();

/**
 * Draws text to the screen
 */
void drawTextToScreen(Game* game, float x, float y, char* s);

/**
 * Adding the numbers in an array
 */
int sumArray(int arr[], int len);

/**
 * Multiplies two matrices
 */
void mult(int rowsA, int colsA, int rowsB, int colsB, double a[rowsA][colsA], double b[rowsB][colsB], double c[rowsA][colsB]);

/**
 * Shift the road array
 */
void shift(Game* game);

/**
 * Generate road
 */
void generate(Game* game, int i);

#endif