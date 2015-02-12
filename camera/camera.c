#include <GL/glew.h>
#include <math.h>
#include <stdlib.h>

#include "../dbg.h"
#include "../linalg/linalg.h"
#include "camera.h"

// --- //

/* Create a Camera. Copies input Vectors */
camera_t* cogcCreate(matrix_t* pos, matrix_t* dir, matrix_t* up) {
        camera_t* c = NULL;

        check(coglVIsVector(pos) &&
              coglVIsVector(dir) &&
              coglVIsVector(up), "Matrices given.");
        check(pos->rows == 3 &&
              dir->rows == 3 &&
              up->rows == 3, "Vectors are not length 3.");

        c = malloc(sizeof(camera_t));
        check_mem(c);
        c->pos = coglMCopy(pos);
        c->dir = coglMCopy(dir);
        c->up  = coglMCopy(up);
        c->tar = coglMAddP(c->pos,c->dir);
        c->yaw = 0;
        c->pitch = 0;
        c->lastX = 400;
        c->lastY = 300;
        
        return c;
 error:
        return NULL;
}

/* Move the Camera based on key presses */
camera_t* cogcMove(camera_t* c, bool up, bool down, bool left, bool right) {
        matrix_t* temp;

        check(c, "NULL Camera given.");

        // Seperate ifs, since all could be pressed.
        if(up) {
                coglMAdd(c->pos,c->dir);
        }
        if(down) {
                coglMSub(c->pos,c->dir);
        }
        if(left) {
                temp = coglVNormalize(coglVCrossP(c->dir,c->up));

                coglMSub(c->pos,temp);

                coglMDestroy(temp);
        }
        if(right) {
                temp = coglVNormalize(coglVCrossP(c->dir,c->up));

                coglMAdd(c->pos,temp);

                coglMDestroy(temp);
        }

        return cogcRefreshTar(c);
 error:
        return NULL;
}

/* Pan the Camera from some mouse movement */
camera_t* cogcPan(camera_t* c, double xpos, double ypos) {
        static bool firstMouse = true;  // Don't touch.

        if(firstMouse) {
                c->lastX = xpos;
                c->lastY = ypos;
                firstMouse = false;
                return c;
        }

        GLfloat xoffset = xpos - c->lastX;
        GLfloat yoffset = c->lastY - ypos;
        c->lastX = xpos;
        c->lastY = ypos;

        // Scale by mouse sensitivity factor
        GLfloat sensitivity = 0.05f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        // Update camera angles.
        c->yaw   += xoffset;
        c->pitch -= yoffset;
        if(c->pitch > tau/4) {
                c->pitch = 4 * tau / 17;
        } else if(c->pitch < -tau/4) {
                c->pitch = -4 * tau / 17;
        }

        // Update Camera Direction Vector
        c->dir->m[0] = cos(c->yaw) * cos(c->pitch);
        c->dir->m[1] = sin(c->pitch);
        c->dir->m[2] = sin(c->yaw) * cos(c->pitch);
        coglVNormalize(c->dir);
        return cogcRefreshTar(c);
}

/* Refresh the Target Vector based on Camera Direction and Position */
camera_t* cogcRefreshTar(camera_t* c) {
        check(c, "NULL Camera given.");

        coglMDestroy(c->tar);
        c->tar = coglMAddP(c->pos,c->dir);

        return c;
 error:
        return NULL;
}

/* Deallocate a Camera and its inner Vectors */
void cogcDestroy(camera_t* c) {
        if(c) {
                coglMDestroy(c->pos);
                coglMDestroy(c->dir);
                coglMDestroy(c->tar);
                coglMDestroy(c->up);
                free(c);
        }
}
