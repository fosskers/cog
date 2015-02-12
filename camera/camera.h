#ifndef __camera__h__
#define __camera__h__

#include <GL/glew.h>

#include "../linalg/linalg.h"

// --- //

typedef struct camera_t {
        matrix_t* pos;  // Where is the Camera?
        matrix_t* dir;  // Where is it pointing?
        matrix_t* tar;  // Where is it _really_ pointing?
        matrix_t* up;   // Up vector in the world space.

        // Angles to divert from the original Direction.
        GLfloat yaw;
        GLfloat pitch;

        // Last coordinates of the mouse.
        GLfloat lastX;
        GLfloat lastY;
} camera_t;

// --- //

/* Create a Camera. Copies input Vectors */
camera_t* cogcCreate(matrix_t* pos, matrix_t* dir, matrix_t* up);

/* Move the Camera based on key presses */
camera_t* cogcMove(camera_t* c, bool up, bool down, bool left, bool right);

/* Pan the Camera from some mouse movement */
camera_t* cogcPan(camera_t* c, double xpos, double ypos);

/* Refresh the Target Vector based on Camera Direction and Position */
camera_t* cogcRefreshTar(camera_t* c);

/* Deallocate a Camera and its inner Vectors */
void cogcDestroy(camera_t* c);

#endif
