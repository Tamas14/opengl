#include "draw.h"
#include "GL/glut.h"
#include <SOIL/SOIL.h>
#include <stdio.h>
#include "init.h"
#include "utils.h"
#include <obj/draw.h>

typedef GLubyte Pixel[3];

void set_lightning()
{
	float ambient_light[] = { 	0.988f, 0.831f, 0.250f, 0.3f };
    float diffuse_light[] = { 	1.0f, 1.0f, 1.0f, 0.5f };
    float specular_light[] = { 	1.0f, 1.0f, 1.0f, 0.8f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 160.0f);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0f);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
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

    /*
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    */

    return texture_name;
}

char segedSting[200];
void draw_game(Game* game)
{	
	sprintf(segedSting, "Speed: %f", game->ball.speed_x);
	
	szovegKirajzolas(game, 0, 800, segedSting);
	camera.position.x = game->ball.x - sin(degree_to_radian(game->ball.dir+90))*60;
	camera.position.y = game->ball.y + cos(degree_to_radian(game->ball.dir+90))*60;
	camera.position.z = 50;
	
	camera.rotation.x = 60.0;
    camera.rotation.y = 0;
    camera.rotation.z = 270.0 + game->ball.dir;
	
	int i;
	
	for(i=0; i < game->numberOfPads; i++)
	{
		glPushMatrix();
			float x1 = game->pads[i].x;
			float y1 = game->pads[i].y;
			float s = game->pads[i].size;
			float temp = i*(1.0/game->numberOfPads);
			
			glBindTexture(GL_TEXTURE_2D, textures[game->pads[i].dir]);
			
			glTranslatef(x1, y1, 0);
			glRotatef(game->pads[i].rotation, 0, 0, 1);
			glColor3f(1-temp, 1-temp, 1-temp);
			glScalef(s, s, 50);
			draw_model(&padmodel);
		glPopMatrix();
	}
	
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[3]);
		glTranslatef(game->ball.x, game->ball.y, 0.5);
		glRotatef(game->ball.dir+90, 0, 0, 1);
		glScalef(25, 60, 25);
		draw_model(&ballmodel);
		set_lightning();
	glPopMatrix();
}
