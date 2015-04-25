COGL - COG Linear Algebra
=========================

## General Information
### Importing
```c
#include "cog/linalg/linalg.h"
```

### Conventions
Every function in this library is prefixed with `cogl`. If `V` follows
`cogl`, it is a function meant for Vectors. If `M`, the function is meant
for Matrices. Most Matrix functions will also work with Vectors
(i.e. `coglMAdd`) but the opposite is not the case (i.e. `coglVDotProduct`).

**Note:** Some functions are prefixed with `coglM4` and are meant only
for 4-by-4 matrices, of which there are plenty in graphics work.

If a function name is suffixed with `P`, it is a pure function. More
information in the `Usage` section below.

### Matrix/Vector Representation
As Vectors can be thought of as n-by-1 Matrices, both Matrices and Vectors
are implemented with the same type: `matrix_t`. This makes many functions
polymorphic on Vectors/Matrices easy to use, but others specific to their
type have some overhead in checking the type integrity of their input (if
you pass a Vector to a Matrix-only function your code will compile, but the
library will get mad at you at runtime).

A `matrix_t` is an array of `GLfloat` values, as well as the dimensions
of the structure. The array, while representing 2D Matrices, is implemented
as a 1D array in **Column-Major Order**, meaning
the array `[1,2,3,4]` could be a 4-by-1 Matrix (a Vector) or the 2-by-2
Matrix:

```
[ 1 3 ]
[ 2 4 ]
```

Notice how the columns populate first. Column-Major Matrices are what
OpenGL requires for its transformation matrices.

## Usage
See `linalg.h` for specific function information.

### Vector Creation
Three functions are available for quick Vector creation:

```c
/* Create a Vector with 2 values */
matrix_t* coglV2(GLfloat f1, GLfloat f2);

/* Create a Vector with 3 values */
matrix_t* coglV3(GLfloat f1, GLfloat f2, GLfloat f3);

/* Create a Vector with 4 values */
matrix_t* coglV4(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);
```

Alternatively, if you require Vectors of arbitrary size, you can:

- Use `coglVCreate` to create a Vector of any size filled with 0s, then
populate it manually, or;
- Use `coglVFromArrayP`, passing an array filled with the values you
want. As this function is pure, the given array will not be overwritten.

### Matrix Creation
There are three way to create a new Matrix:

```c
/* Create a column-major Matrix of all 0s */
matrix_t* coglMCreate(GLuint cols, GLuint rows);

/* Create a column-major Matrix from a given array of floats */
matrix_t* coglMFromArrayP(GLuint cols, GLuint rows, GLfloat* fs);

/* Create an Identity Matrix of size `dim` */
matrix_t* coglMIdentity(GLuint dim);
```

### Pure Functions
Any function suffixed with `P` is a pure function. The functions are usually
passed a pointer to some other object (an array, or other `matrix_t`)
and produce a `matrix_t*` as output. These functions allocate new memory,
and do not clobber the memory of the objects passed to them.

**Note:** Make sure to use `coglMDestroy` once you're done with a `matrix_t`
you created with a pure function.
