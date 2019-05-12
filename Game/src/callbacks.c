#include "callbacks.h"

void display()
{
	glClearColor(.8, .8, .8, .5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

	set_view(&camera);
    draw_game(&game);

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    resize_game(&game, width, height);
	
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 20000.0);
}

void keyboard(unsigned char key, int x, int y)
{
	y = x;
	x = y;
	
	if(game.gameOver)
	{
		switch(key){
			case 'r':
				init(&game, game.width, game.height);
			break;
		}
	}else{
		switch (key) {
			case 'w':
				game.car.acceleration = 1;
			break;
			
			case 'a':
				game.car.turning = -1;
			break;
			
			case 'd':
				game.car.turning = 1;
			break;
		}
	}
    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{ 	
	x = y;
	y = x;
	switch (key) {
		case 'a':
		case 'd':
			game.car.turning = 0;
		break;
	}
    glutPostRedisplay();
}

void idle()
{
    update_game(&game);
	update_camera(&camera, &game);
	
    glutPostRedisplay();
}

