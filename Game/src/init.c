#include <GL/glut.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "pad.h"
#include "ball.h"
#include "init.h"

void init_opengl()
{
    glClearColor(1, 1, .5, 1);
	
	char texture_filenames[][32] = {
        "turnleft.png",
        "forward.png",
        "turnright.png",
        "arrow.png"
    };
	
	load_model(&padmodel, "untitled.obj");
	load_model(&ballmodel, "sphere.obj");
	int i;
	for(i = 0; i < 4; i++)
	{
		textures[i] = load_texture(texture_filenames[i]);
	}
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	init_camera(&camera);
	set_lightning();
}

