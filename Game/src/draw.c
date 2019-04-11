#include "draw.h"

#include "GL/glut.h"
#include <SOIL/SOIL.h>
#include <GL/glut.h>
#include "init.h"

typedef GLubyte Pixel[3];

void set_lightning()
{
	float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 2.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
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

void draw_game(Game* game)
{
	camera.position.x = game->pads[1].x;
	camera.position.y = game->pads[1].y;
	//camera.position.z = 0.1;
	
	glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);

    glEnd();
	
	int i,j;
	
	for(i=0; i < game->numberOfPads; i++)
	{
		
		glPushMatrix();
		
		float x1 = game->pads[i].x;
		float y1 = game->pads[i].y;
		float s = game->pads[i].size;
		//float x2 = x1+game->pads[i].size;
		//float y2 = y1+game->pads[i].size;
		float temp = i*(1.0/game->numberOfPads);
		
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTranslatef(x1, y1, 0);
		glColor3f(1-temp, 1-temp, 1-temp);
		//printf("%f, %f \n", x1, y1);
		glScalef(s, s, 50);
		draw_model(&padmodel);
	
		glPopMatrix();
		
	}
	
	
	/**for(i=0; i < game->numberOfPads; i++)
	{
		glPushMatrix();
		glScalef(50, 50, 1);
		float x1 = game->pads[i].x;
		float y1 = game->pads[i].y;
		//float x2 = x1+game->pads[i].size;
		//float y2 = y1+game->pads[i].size;
		//float temp = i*(1.0/game->numberOfPads);
		//glBindTexture(GL_TEXTURE_2D, game->pads[i].texture_id);
		glTranslatef(x1, y1, 0);
		
		printf("%f, %f \n", x1, y1);
		
		draw_model(&padmodel);
	
		glPopMatrix();
	}*/
}

/**void draw_game(Game* game)
{
	int i;
	for(i=0; i < game->numberOfPads; i++)
	{
		float x1 = game->pads[i].x;
		float y1 = game->pads[i].y;
		float x2 = x1+game->pads[i].size;
		float y2 = y1+game->pads[i].size;
		float temp = i*(1.0/game->numberOfPads);
		
		glBegin(GL_POLYGON);
			glColor3f(1-temp, 1-temp, 1-temp);
			glVertex2f(x1, y1);
			glVertex2f(x2, y1);
			glVertex2f(x2, y2);
			glVertex2f(x1, y2);
		glEnd();
		
		glBegin(GL_LINE_LOOP);
			glColor3d(.5, .5, .5);
			glVertex2f(x1, y1);
			glVertex2f(x2, y1);
			glVertex2f(x2, y2);
			glVertex2f(x1, y2);
		glEnd();
	}

    glPushMatrix();

    glPopMatrix();
}*/

