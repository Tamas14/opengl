#include "utils.h"

double MPI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067;

double degree_to_radian(double degree)
{
	return degree * MPI / 180.0;
}

GLuint load_texture(char* filename)
{
	GLuint texture_name;
	glGenTextures(1, &texture_name);

	int width;
	int height;

	Pixel* image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

	glBindTexture(GL_TEXTURE_2D, texture_name);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    return texture_name;
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
		troads[i].hasObstacle = rand()%2;
		
		if(troads[i].hasObstacle)
			troads[i].obstacleOffset = (rand()%11-5)*10;
	}
	else
	{
		ymove = 0;
		troads[i].hasObstacle = 0;
	}
	
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

void Perspective() {
	glPushMatrix();
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(80, (double) VIEWPORT_RATIO, 0.01, 20000.0);
			glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Ortho(Game* game) {
	glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, game->width, 0, game->height, -100, 100);
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

int sumArray(int arr[], int len)
{
	int i, sum = 0;
	for(i = 0;i < len; i++)
		sum += arr[i];
	
	return sum;
}

void drawTextToScreen(Game* game, float x, float y, char* s) {
	glDisable(GL_LIGHTING);
	Ortho(game);
	
	glPushMatrix();
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glRasterPos2f(x, y);

		unsigned i;
		for (i = 0; i < strlen(s); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
		}
		
		glEnable(GL_DEPTH_TEST);
	glPopMatrix();

	Perspective();
	glEnable(GL_LIGHTING);
}