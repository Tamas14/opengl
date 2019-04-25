#include "draw.h"

#include "GL/glut.h"
#include <SOIL/SOIL.h>
#include "init.h"
#include "utils.h"

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
    /*float ambient_material_color[] = {
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

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));*/
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
	camera.position.x = game->ball.x - sin(degree_to_radian(game->ball.dir+90))*50;
	camera.position.y = game->ball.y + cos(degree_to_radian(game->ball.dir+90))*50;
	camera.position.z = 50;
	
	camera.rotation.x = 60.0;
    camera.rotation.y = 0;
    camera.rotation.z = 270.0 + game->ball.dir;
	
	int i,j;
	
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
		glScalef(25, 25, 25);
		glRotatef(game->ball.dir+90, 0, 0, 1);
		draw_model(&ballmodel);
	glPopMatrix();
}
