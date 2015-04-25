COGC - COG Camera
=================

This library allows one to create and modify a `camera_t` struct,
which can be used with `coglM4LookAtP` to create a View matrix.
This View matrix enables a simple free-flying FPS camera.

## Usage
### Importing
```c
#include "cog/camera/camera.h"
```

### Initial State
It may be useful to have the following function in your code,
for both camera initialization and resetting:

```c
void resetCamera() {
        // Where the Camera starts.
        matrix_t* camPos = coglV3(0,0,4);

        // Where the Camera is facing. Must be a normalized.
        matrix_t* camDir = coglV3(0,0,-1);

        // The global Up direction. The Y-axis here.
        matrix_t* camUp = coglV3(0,1,0);

        camera = cogcCreate(camPos,camDir,camUp);
}
```

### Moving the Camera
There are two functions we use for moving the Camera:

```c
/* Move the Camera based on key presses */
camera_t* cogcMove(camera_t* c, GLfloat delta, bool up, bool down, bool left, bool right);

/* Pan the Camera from some mouse movement */
camera_t* cogcPan(camera_t* c, double xpos, double ypos);
```

For `cogcMove`, the `delta` is the speed at which one moves when holding
down the keys registered for forward-back-left-right movement.

For `cogcPan`, the two doubles come directly from a mouse-movement
event. The following is a simple way to implement a mouse callback:

```c
void mouse_callback(GLFWwindow* w, double xpos, double ypos) {
        cogcPan(camera,xpos,ypos);
}
```

**Note:** These functions are impure (see the linalg README for info
on function purity), meaning they *do* affect the `camera_t` pointer
that they are passed. The pointer returned is the same as the one
passed, provided nothing went wrong in the interim.
