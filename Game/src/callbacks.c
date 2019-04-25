#include "callbacks.h"
#include "draw.h"
#include "init.h"
float i = 0;

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 80.0

void display()
{
	glClearColor(.7, .7, .5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

	set_view(&camera);
	//printf("%f, %f, %f, %f, %f, %f \n", camera.position.x, camera.position.y, camera.position.z, camera.rotation.x, camera.rotation.y, camera.rotation.z);
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
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);

}

void keyboard(unsigned char key, int x, int y)
{
	y = x;
	x = y;
	
    switch (key) {
		case 'r':
			shift(&game);
			generate(&game, game.numberOfPads-1);
		break;
		case 'w':
			game.ball.speed_x = 2;
		break;
		
		case 's':
			game.ball.speed_x = -2;
		break;
		
		case 'a':
			game.ball.turning = -1;
		break;
		
		case 'd':
			game.ball.turning = 1;
		break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{ 	
	switch (key) {
		case 'w':
		case 's':
			game.ball.speed_x = 0;
		break;
		
		case 'a':
		case 'd':
			game.ball.turning = 0;
		break;
	}
    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

	update_camera(&camera, elapsed_time);
    update_game(&game, elapsed_time);
	
    glutPostRedisplay();
}

