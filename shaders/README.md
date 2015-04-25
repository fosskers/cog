COGS - COG Shaders
==================

Provided with the filenames of vertex and fragment shaders,
will construct a Shader Program for use in a rendering loop.

### Usage

```c
#include "cog/shaders/shaders.h"

int main(int argc, char** argv) {
    // Define initial OpenGL config

    /* Make a shader program */
    // Reads the two files and attempts to compile them
    shaders_t* shaders = cogsShaders("vertex.glsl", "fragment.glsl");

    // Associate the compiled shaders with a Program
    GLuint shaderProgram = cogsProgram(shaders);

    // Free compiled shader memory (won't affect `shaderProgram`)
    cogsDestroy(shaders);

    while(!glfwWindowShouldClose(w)) {
        glUseProgram(shaderProgram);
        // Render, etc.
    }
        
    // Clean up and exit
}
```
