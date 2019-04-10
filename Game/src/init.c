#include <GL/glut.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "pad.h"
#include "init.h"

void init_opengl()
{
    glClearColor(1, 1, .5, 1);
	
	char texture_filenames[][32] = {
        "1.png",
        "2.png",
        "3.png",
        "4.png",
        "5.png"
    };
	
	load_model(&padmodel, "untitled.obj");
	int i;
	for(i = 1; i <=5; i++)
	{
		textures[i-1] = load_texture(texture_filenames[i-1]);
	}
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	init_camera(&camera);
	set_lightning();
}
