# OpenGL-Shaders

### Usage

```c
#include "opengl-shaders.h"

int main(int argc, char** argv) {
    // Define initial OpenGL config

    // Make a shader program
    shaders_t* shaders = oglsShaders("vertex.glsl", "fragment.glsl");
    GLuint shaderProgram = oglsProgram(shaders);
    oglsDestroy(shaders);

    while(!glfwWindowShouldClose(w)) {
        glUseProgram(shaderProgram);
        // Render, etc.
    }
        
    // Clean up and exit
}
```
