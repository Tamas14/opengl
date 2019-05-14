#include "draw.h"
#include "GL/glut.h"
#include <stdio.h>
#include "init.h"
#include "utils.h"
#include <obj/draw.h>

void set_lighting()
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

char txtString[200];
void draw_game(Game* game)
{	
	glColor3f(1, 1, 1);
	
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[5]);
		glTranslatef(game->car.x, game->car.y, 0);
		glScalef(1000, 1000, 1);
		draw_model(&roadModel);
	glPopMatrix();

	int i;
	for(i=0; i < game->numberOfPads; i++)
	{
		float x1 = game->roads[i].x;
		float y1 = game->roads[i].y;
		float s = game->roads[i].size;
		
		glPushMatrix();
			if(i == 0 && game->drawhelp)
				glBindTexture(GL_TEXTURE_2D, textures[7]);
			else
				glBindTexture(GL_TEXTURE_2D, textures[game->roads[i].dir]);
			
			glTranslatef(x1, y1, 0);
			glRotatef(game->roads[i].rotation, 0, 0, 1);
			glScalef(s, s, 50);
			draw_model(&roadModel);
		glPopMatrix();
			
		glPushMatrix();
			glTranslatef(x1, y1, 5);
			glLineWidth(30);
			
			if(game->roads[i].hasObstacle)
			{
				float offset = game->roads[i].obstacleOffset;

				glPushMatrix();
					glBindTexture(GL_TEXTURE_2D, textures[3]);
					glTranslatef(offset, 0, 20);
					glScalef(100, 100, 120);
					draw_model(&obstacleModel);
				glPopMatrix();
			}

		glPopMatrix();
	}
	
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[4]);
		glTranslatef(game->car.x, game->car.y, 10);
		glRotatef(game->car.dir+90, 0, 0, 1);
		glScalef(30, 30, 25);
		draw_model(&snailModel);
		set_lighting();
	glPopMatrix();
	
	if(!game->gameOver)
		game->dist += game->car.speed_x * (glutGet(GLUT_ELAPSED_TIME)/1000.0 / (60*60*60));
	
	sprintf(txtString, "Speed: %.0f km/h", game->car.speed_x);
	drawTextToScreen(game, 0, 800, txtString);
	sprintf(txtString, "Distance: %.4f km", game->dist);
	drawTextToScreen(game, 0, 750, txtString);
	
	if(game->gameOver)
	{
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, textures[6]);
			glTranslatef(game->car.x - sin(degree_to_radian(game->car.dir+90))*30,
			game->car.y + cos(degree_to_radian(game->car.dir+90))*30, 30);
			glRotatef(90, 1, 0, 0);
			glRotatef(game->car.dir+90, 0, 1, 0);
			
			glScalef(75, 30, 10);
			draw_model(&roadModel);
		glPopMatrix();
	}
}