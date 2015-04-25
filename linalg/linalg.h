#ifndef __linalg__
#define __linalg__

#include <GL/glew.h>
#include <stdbool.h>

// --- //

#define tau 6.283185
#define E 0.000001

typedef struct matrix_t {
        GLfloat* m;
        GLuint cols;
        GLuint rows;
} matrix_t;

// --- //

// --- VECTORS --- //

/* Create a Vector with 2 values */
matrix_t* coglV2(GLfloat f1, GLfloat f2);

/* Create a Vector with 3 values */
matrix_t* coglV3(GLfloat f1, GLfloat f2, GLfloat f3);

/* Create a Vector with 4 values */
matrix_t* coglV4(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

/* Create a Vector filled with zeros */
matrix_t* coglVCreate(GLuint size);

/* Create a Vector from a given array of floats */
matrix_t* coglVFromArrayP(GLuint size, GLfloat* fs);

/* The Cross-Product of two Vectors. Returns a new Vector. */
matrix_t* coglVCrossP(matrix_t* v1, matrix_t* v2);

/* Normalize a Vector (reduce its length to 1) */
matrix_t* coglVNormalize(matrix_t* v);

/* Yields the Length/Magnitude of a given Vector */
GLfloat coglVLength(matrix_t* v);

/* Yields the Dot Product of two Vectors */
GLfloat coglVDotProduct(matrix_t* v1, matrix_t* v2);

/* Are two Vectors orthogonal? */
bool coglVAreOrtho(matrix_t* v1, matrix_t* v2);

/* Is a given Matrix struct actually a Vector? */
bool coglVIsVector(matrix_t* v);

// --- MATRICES --- //

/* Create a column-major Matrix of all 0s */
matrix_t* coglMCreate(GLuint cols, GLuint rows);

/* Create a column-major Matrix from a given array of floats */
matrix_t* coglMFromArrayP(GLuint cols, GLuint rows, GLfloat* fs);

/* Make a copy of a given Matrix */
matrix_t* coglMCopy(matrix_t* m);

/* Create an Identity Matrix of size `dim` */
matrix_t* coglMIdentity(GLuint dim);

/* Are two Matrices equal? */
bool coglMEqual(matrix_t* m1, matrix_t* m2);

/* Set a value in a Matrix */
void coglMSet(matrix_t* m, GLuint col, GLuint row, GLfloat f);

/* Scale a Matrix by some scalar in place */
matrix_t* coglMScale(matrix_t* m, GLfloat f);

/* Scale a Matrix by some scalar. Returns a new Matrix. */
matrix_t* coglMScaleP(matrix_t* m, GLfloat f);

/* The values of m2 are added to m1 */
matrix_t* coglMAdd(matrix_t* m1, matrix_t* m2);

/* Add two same-sized Matrices together. Returns a new Matrix. */
matrix_t* coglMAddP(matrix_t* m1, matrix_t* m2);

/* Sum any number of same-dimension matrices together */
matrix_t* coglMSumsP(matrix_t** ms, GLuint len);

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
matrix_t* coglMTransposeP(matrix_t* m);

/* Rotate a 4x4 Matrix in place by `r` radians around the unit vector
formed by `x` `y` and `z` */
matrix_t* coglM4Rotate(matrix_t* m,GLfloat r,GLfloat x,GLfloat y,GLfloat z);

/* Adds translation factor to a transformation Matrix (in place) */
matrix_t* coglM4Translate(matrix_t* m, GLfloat x, GLfloat y, GLfloat z);

/* Invert a 3x3 Matrix. Returns a new Matrix */
matrix_t* coglM3InverseP(matrix_t* m);

/* Invert a 4x4 Model Matrix which has some scaling, rotation
and translation factor. Returns a new Matrix */
matrix_t* coglM4ModelInverseP(matrix_t* m);

/* Produces a Perspective Projection Matrix.
   fov  := Field of View. Vertical eye angle, usually (tau/8).
   aspr := Aspect Ratio. Screen (width/height).
   n    := Distance from camera to near-clipping plane.
   f    := Distance from camera to far-clipping plane. */
matrix_t* coglMPerspectiveP(GLfloat fov, GLfloat aspr, GLfloat n, GLfloat f);

/* Produces an Orthographic Projection Matrix */
matrix_t* coglMOrthoP(GLfloat l,GLfloat r,GLfloat b,GLfloat t,GLfloat n,GLfloat f);

/* Generate a View Matrix */
matrix_t* coglM4LookAtP(matrix_t* camPos, matrix_t* target, matrix_t* up);

/* Is a given Matrix 4x4? */
bool coglM4Check(matrix_t* m);

/* Deallocate a Matrix */
void coglMDestroy(matrix_t* m);

/* Print a Matrix */
void coglMPrint(matrix_t* m);

/* Print Matrix values in their internal order */
void coglMPrintLinear(matrix_t* m);

// --- MISC --- //

/* Is a given float essentially zero? */
bool isZero(GLfloat f);

#endif
