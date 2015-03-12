COG - C OpenGL
==============

`cog` is a library suite for interacting with OpenGL in C nicely. It features:

* `linalg`: a Linear Algebra library with matrices implemented in a format
that OpenGL natively accepts
* `shaders`: a helper for compiling shaders easily, given `.glsl` filenames
* `camera`: a library for easily creating and moving a Camera in a 3D
OpenGL scene

`cog` makes liberal use of `dbg.h`, a debug helper for writing defensive C,
created by Zed Shaw. Follow in his learn'd ways with his
[C book](http://c.learncodethehardway.org/book/).

`cog` also has CMake integration. The following is an example of how
to link to cog libraries:

```
include_directories("$(PROJECT_SOURCE_DIR)/cog")
add_subdirectory(cog)

# More things here

target_link_libraries(PROJECTNAME m GL glfw GLEW pthread cogl cogc cogs)
```
