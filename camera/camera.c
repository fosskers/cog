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
        c->firstMouse = true;
        
        return c;
 error:
        return NULL;
}

/* Move the Camera based on key presses */
camera_t* cogcMove(camera_t* c, GLfloat delta, bool up, bool down, bool left, bool right) {
        matrix_t* temp;
        GLfloat speed = delta;

        check(c, "NULL Camera given.");

        // Seperate ifs, since all could be pressed.
        if(up) {
                temp = coglMScaleP(c->dir,speed);
                coglMAdd(c->pos,temp);
                coglMDestroy(temp);
        }
        if(down) {
                temp = coglMScaleP(c->dir,speed);
                coglMSub(c->pos,temp);
                coglMDestroy(temp);
        }
        if(left) {
                temp = coglVNormalize(coglVCrossP(c->dir,c->up));
                coglMSub(c->pos,coglMScale(temp,speed));
                coglMDestroy(temp);
        }
        if(right) {
                temp = coglVNormalize(coglVCrossP(c->dir,c->up));
                coglMAdd(c->pos,coglMScale(temp,speed));
                coglMDestroy(temp);
        }

        return cogcRefreshTar(c);
 error:
        return NULL;
}

/* Pan the Camera from some mouse movement */
camera_t* cogcPan(camera_t* c, double xpos, double ypos) {
        if(c->firstMouse) {
                c->lastX = xpos;
                c->lastY = ypos;
        }

        //debug("X: %f Y: %f", xpos, ypos);
        
        GLfloat xoffset = xpos - c->lastX;
        GLfloat yoffset = c->lastY - ypos;
        c->lastX = xpos;
        c->lastY = ypos;

        // Scale by mouse sensitivity factor
        GLfloat sensitivity = 0.01f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        // Update camera angles.
        c->yaw   += xoffset;
        c->pitch -= yoffset;

        //debug("YAW: %f", c->yaw);

        // WHY. Why is yaw=0 the side of the box?
        if(c->firstMouse) {
                c->yaw = -tau/4;
                c->pitch = 0;
                c->firstMouse = false;
        }
        
        // Max Pitch is tau/8
        if(c->pitch > MAX_PITCH) {
                c->pitch = MAX_PITCH;
        } else if(c->pitch < -MAX_PITCH) {
                c->pitch = -MAX_PITCH;
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
