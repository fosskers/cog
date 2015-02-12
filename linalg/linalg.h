#ifndef __linalg__
#define __linalg__

#include <GL/glew.h>
#include <stdbool.h>

// --- //

#define tau 6.283185

typedef struct matrix_t {
        GLfloat* m;
        size_t cols;
        size_t rows;
} matrix_t;

// --- //

// --- VECTORS --- //

/* Create a Vector filled with zeros */
matrix_t* coglVCreate(size_t size);

/* Create a Vector from a given array of floats */
matrix_t* coglVFromArray(size_t size, GLfloat* fs);

/* The Cross-Product of two Vectors. Returns a new Vector. */
matrix_t* coglVCrossP(matrix_t* v1, matrix_t* v2);

/* Normalize a Vector (reduce its length to 1) */
matrix_t* coglVNormalize(matrix_t* v);

/* Yields the Length/Magnitude of a given Vector */
GLfloat coglVLength(matrix_t* v);

/* Yields the Dot Product of two Vectors */
GLfloat coglVDotProduct(matrix_t* v1, matrix_t* v2);

/* Are two Vectors orthogonal? */
bool coglVIsOrtho(matrix_t* v1, matrix_t* v2);

/* Is a given Matrix struct actually a Vector? */
bool coglVIsVector(matrix_t* v);

// --- MATRICES --- //

/* Create a column-major Matrix of all 0s */
matrix_t* coglMCreate(size_t cols, size_t rows);

/* Create a column-major Matrix from a given array of floats */
matrix_t* coglMFromArray(size_t cols, size_t rows, GLfloat* fs);

/* Make a copy of a given Matrix */
matrix_t* coglMCopy(matrix_t* m);

/* Create an Identity Matrix of size `dim` */
matrix_t* coglMIdentity(size_t dim);

/* Are two Matrices equal? */
bool coglMEqual(matrix_t* m1, matrix_t* m2);

/* Set a value in a Matrix */
void coglMSet(matrix_t* m, size_t col, size_t row, GLfloat f);

/* Scale a Matrix by some scalar in place */
void coglMScale(matrix_t* m, GLfloat f);

/* The values of m2 are added to m1 */
matrix_t* coglMAdd(matrix_t* m1, matrix_t* m2);

/* Add two same-sized Matrices together. Returns a new Matrix. */
matrix_t* coglMAddP(matrix_t* m1, matrix_t* m2);

/* Subtract two same-sized Matrices */
matrix_t* coglMSub(matrix_t* m1, matrix_t* m2);

/* Subtract two same-sized Matrices. Returns a new Matrix. */
matrix_t* coglMSubP(matrix_t* m1, matrix_t* m2);

/* Multiply two 4x4 matrices together in place. Affects `m1`. */
matrix_t* coglM4Multiply(matrix_t* m1, matrix_t* m2);

/* Multiply two matrices together. The number of rows of m2 must match
   the number of columns of m1. Returns a new Matrix. */
matrix_t* coglMMultiplyP(matrix_t* m1, matrix_t* m2);

/* Transpose a Matrix. Returns a new Matrix. */
matrix_t* coglMTranspose(matrix_t* m);

/* Rotate a 4x4 Matrix in place by `r` radians around the unit vector
formed by `x` `y` and `z` */
matrix_t* coglM4Rotate(matrix_t* m,GLfloat r,GLfloat x,GLfloat y,GLfloat z);

/* Adds translation factor to a transformation Matrix (in place) */
matrix_t* coglM4Translate(matrix_t* m, GLfloat x, GLfloat y, GLfloat z);

/* Produces a Perspective Projection Matrix.
   fov  := Field of View. Vertical eye angle, usually (tau/8).
   aspr := Aspect Ratio. Screen (width/height).
   n    := Distance from camera to near-clipping plane.
   f    := Distance from camera to far-clipping plane. */
matrix_t* coglMPerspectiveP(GLfloat fov, GLfloat aspr, GLfloat n, GLfloat f);

/* Generate a View Matrix */
matrix_t* coglM4LookAtP(matrix_t* camPos, matrix_t* target, matrix_t* up);

/* Deallocate a Matrix */
void coglMDestroy(matrix_t* m);

/* Print a Matrix */
void coglMPrint(matrix_t* m);

/* Print Matrix values in their internal order */
void coglMPrintLinear(matrix_t* m);

#endif
