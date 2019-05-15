#include "draw.h"
#include "GL/glut.h"
#include <stdio.h>
#include "init.h"
#include "utils.h"
#include <obj/draw.h>

void set_lighting()
{
	GLfloat ambient[] = { 0.988f, 0.831f, 0.250f, 0.1 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 0.6 };
	GLfloat specular[] = { 1.0, 1.0, 0.7, 0.7 };
	GLfloat position[] = { 10, 10, 200.0f, 0.0 };

	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat local_view[] = { 0.0 };

	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 70);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.5);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

char txtString[200];
void draw_game(Game* game)
{	
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 0.3 };
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
	GLfloat mat_specular[] = { 1.0, 0.6, 0.6, 1.0 };
	GLfloat low_shininess[] = { 10 };
	GLfloat high_shininess[] = { 50.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, textures[5]);
		glTranslatef(game->car.x, game->car.y, 0);
		set_lighting();
		glScalef(1000, 1000, 2);
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
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
			
			draw_model(&roadModel);
		glPopMatrix();
			
		glPushMatrix();
			glTranslatef(x1, y1, 5);
			
			if(game->roads[i].hasObstacle)
			{
				float offset = game->roads[i].obstacleOffset;

				glPushMatrix();
					glBindTexture(GL_TEXTURE_2D, textures[3]);
					glTranslatef(offset, 0, 20);
					glScalef(100, 100, 120);
					
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
					
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
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);

		draw_model(&snailModel);
	glPopMatrix();
	
	if(!game->gameOver)
		game->dist += game->car.speed_x * (glutGet(GLUT_ELAPSED_TIME)/1000.0 / (60*60*60));
	
	sprintf(txtString, "Speed: %.0f km/h", game->car.speed_x);
	drawTextToScreen(game, 0, game->height-50, txtString);
	sprintf(txtString, "Distance: %.4f km", game->dist);
	drawTextToScreen(game, 0, game->height-100, txtString);
	
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
	
	glFlush();
}