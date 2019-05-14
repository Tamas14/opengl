#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include <GL/glut.h>
#include <math.h>

/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
} Camera;

Camera camera;

/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera* camera);

/**
 * Update the position, rotation of the camera.
 */
void update_camera(Camera* camera, Game* game);

/**
 * Apply the camera settings to the view transformation.
 */
void set_view(const Camera* camera);


#endif
