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
	camera.position.x = game->ball.x - sin(degree_to_radian(game->ball.dir+90))*60;
	camera.position.y = game->ball.y + cos(degree_to_radian(game->ball.dir+90))*60;
	camera.position.z = 45;
	
	camera.rotation.x = 60.0;
    camera.rotation.y = 0;
    camera.rotation.z = 270.0 + game->ball.dir;
	
	int i;
	
	for(i=0; i < game->numberOfPads; i++)
	{
		float x1 = game->pads[i].x;
		float y1 = game->pads[i].y;
		float s = game->pads[i].size;
		
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, textures[game->pads[i].dir]);
			
			glTranslatef(x1, y1, 0);
			glRotatef(game->pads[i].rotation, 0, 0, 1);
			glColor3f(1, 1, 1);
			glScalef(s, s, 50);
			draw_model(&padmodel);
		glPopMatrix();
			
		glPushMatrix();
			glTranslatef(x1, y1, 5);
			glLineWidth(30);
			
			if(game->pads[i].dir == 2)
			{
				glPushMatrix();
					glRotated(game->pads[i].rotation, 0, 0, 1);
					glBegin(GL_LINES);
						glVertex3f(+s/2, -s/2, 1.0f);
						glVertex3f(-s/2, -s/2, 1.0f);
						glVertex3f(-s/2, -s/2, 1.0f);
						glVertex3f(-s/2, +s/2, 1.0f);
					glEnd();
				glPopMatrix();
			}
			
			if(game->pads[i].dir == 1)
			{
				glPushMatrix();
					glRotated(game->pads[i].rotation, 0, 0, 1);
					glBegin(GL_LINES);
						glVertex3f(-s/2, -s/2, 1.0f);
						glVertex3f(-s/2, +s/2, 1.0f);
						glVertex3f(+s/2, -s/2, 1.0f);
						glVertex3f(+s/2, +s/2, 1.0f);
					glEnd();
				glPopMatrix();
				
				if(game->pads[i].hasAkadaly)
				{
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, textures[4]);
						glTranslatef(0, 0, 20);
						glScalef(100, 100, 100);
						draw_model(&akadaly);
					glPopMatrix();
				}
			}
			
			if(game->pads[i].dir == 0)
			{
				glPushMatrix();
					glRotated(game->pads[i].rotation, 0, 0, 1);
					glBegin(GL_LINES);
						
						glVertex3f(-s/2, -s/2, 1.0f);
						glVertex3f(-s/2, +s/2, 1.0f);
						glVertex3f(-s/2, +s/2, 1.0f);
						glVertex3f(+s/2, +s/2, 1.0f);
					glEnd();
				glPopMatrix();
			}
			
			/*glBegin(GL_LINES);
				glVertex3f(-game->pads[i].size/2, -game->pads[i].size/2, 1.0f);
				glVertex3f(game->pads[i].size/2, -game->pads[i].size/2, 1.0f);

				glVertex3f(-game->pads[i].size/2, -game->pads[i].size/2, 1.0f);
				glVertex3f(-game->pads[i].size/2, game->pads[i].size/2, 1.0f);
				
				glVertex3f(+game->pads[i].size/2, +game->pads[i].size/2, 1.0f);
				glVertex3f(-game->pads[i].size/2, game->pads[i].size/2, 1.0f);
				
				glVertex3f(+game->pads[i].size/2, -game->pads[i].size/2, 1.0f);
				glVertex3f(+game->pads[i].size/2, +game->pads[i].size/2, 1.0f);
			glEnd();*/
		glPopMatrix();
	}
	
	glPushMatrix();
		glColor3f(0.6470, 0.2647, 0.2647);
		glBindTexture(GL_TEXTURE_2D, textures[3]);
		glTranslatef(game->ball.x, game->ball.y, 10);
		glRotatef(game->ball.dir+90, 0, 0, 1);
		glScalef(30, 30, 30);
		draw_model(&ballmodel);
		set_lightning();
	glPopMatrix();
	
	game->dist += game->ball.speed_x * (glutGet(GLUT_ELAPSED_TIME)/1000.0 / (60*60*60));
	
	sprintf(segedSting, "Speed: %f km/h", game->ball.speed_x);
	szovegKirajzolas(game, 0, 800, segedSting);
	sprintf(segedSting, "Distance: %f km", game->dist);
	szovegKirajzolas(game, 0, 750, segedSting);
}
