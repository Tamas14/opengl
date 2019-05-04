#include <GL/glut.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "pad.h"
#include "ball.h"
#include "draw.h"
#include "init.h"

void init_opengl()
{
    glClearColor(1, 1, .5, 1);
	
	char texture_filenames[][32] = {
        "turnleft.png",
        "forward.png",
        "turnright.png",
        "arrow.png",
        "hegy.png"
    };
	
	load_model(&padmodel, "untitled.obj");
	load_model(&ballmodel, "sphere2.obj");
	load_model(&akadaly, "akadaly.obj");
	
	int i;
	for(i = 0; i < 5; i++)
	{
		textures[i] = load_texture(texture_filenames[i]);
	}
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_FOG);
	glShadeModel(GL_SMOOTH);
	
	float fog_light[] = {0.6f, 0.6f, 0.6f, 0.1f };
	
	glFogf(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_DENSITY, 0.5f);
	glFogf(GL_FOG_START, 0.0f);
	glFogf(GL_FOG_END, 400.0f);
	glFogfv(GL_FOG_COLOR, fog_light);
	
	init_camera(&camera);
	set_lightning();
}

