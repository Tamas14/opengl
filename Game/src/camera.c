#include "camera.h"

void init_camera(Camera* camera)
{
    camera->position.x = 0;
    camera->position.y = 0;
    camera->position.z = 150;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 90.0;
}

void update_camera(Camera* camera, Game* game)
{
    camera->position.x = game->car.x - sin(degree_to_radian(game->car.dir+90))*60;
	camera->position.y = game->car.y + cos(degree_to_radian(game->car.dir+90))*60;
	camera->position.z = 45;

	camera->rotation.x = 60.0;
    camera->rotation.y = 0;
    camera->rotation.z = 270.0 + game->car.dir;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x), 1.0, 0, 0);
    glRotatef(-(camera->rotation.y), 0, 1.0, 0.0);
    glRotatef(-(camera->rotation.z), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}
