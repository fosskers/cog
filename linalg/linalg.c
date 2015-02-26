#include <stdlib.h>
#include <math.h>

#include "linalg.h"
#include "../dbg.h"

// --- //

// --- VECTORS --- //

/* Create a Vector with 2 values */
matrix_t* coglV2(GLfloat f1, GLfloat f2) {
        GLfloat fs[] = {f1,f2};

        return coglVFromArray(2,fs);
}

/* Create a Vector with 3 values */
matrix_t* coglV3(GLfloat f1, GLfloat f2, GLfloat f3) {
        GLfloat fs[] = {f1,f2,f3};

        return coglVFromArray(3,fs);
}

/* Create a Vector with 4 values */
matrix_t* coglV4(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4) {
        GLfloat fs[] = {f1,f2,f3,f4};

        return coglVFromArray(4,fs);
}

/* Create a Vector filled with zeros */
matrix_t* coglVCreate(size_t size) {
        return coglMCreate(1,size);
}

/* Create a Vector from a given array of floats */
matrix_t* coglVFromArray(size_t size, GLfloat* fs) {
        return coglMFromArray(1,size,fs);
}

/* The Cross-Product of two Vectors. Returns a new Vector. */
matrix_t* coglVCrossP(matrix_t* v1, matrix_t* v2) {
        matrix_t* newV = NULL;

        check(v1 && v2, "Null Vectors given.");
        check(v1->rows == v2->rows, "Vectors aren't same size.");

        newV = coglVCreate(v1->rows);
        check(newV, "Vector creation failed.");

        newV->m[0] = v1->m[1] * v2->m[2] - v1->m[2] * v2->m[1];
        newV->m[1] = v1->m[2] * v2->m[0] - v1->m[0] * v2->m[2];
        newV->m[2] = v1->m[0] * v2->m[1] - v1->m[1] * v2->m[0];

        return newV;
 error:
        return NULL;
}

/* Normalize a Vector (reduce its length to 1) */
matrix_t* coglVNormalize(matrix_t* v) {
        GLfloat len;
        size_t i;

        check(coglVIsVector(v), "Matrix given.");

        len = coglVLength(v);

        for(i = 0; i < v->rows; i++) {
                v->m[i] /= len;
        }

        return v;
 error:
        return NULL;
}

/* Yields the Length/Magnitude of a given Vector */
GLfloat coglVLength(matrix_t* v) {
        GLfloat len = 0;
        size_t i;

        check(coglVIsVector(v), "Matrix given.");

        for(i = 0; i < v->rows; i++) {
                len += v->m[i] * v->m[i];
        }

        return sqrt(len);
 error:
        return 0;
}

/* Yields the Dot Product of two Vectors */
GLfloat coglVDotProduct(matrix_t* v1, matrix_t* v2) {
        GLfloat total = 0;
        size_t i;

        check(coglVIsVector(v1) && coglVIsVector(v2), "Matrices given.");
        check(v1->rows == v2->rows, "Vectors aren't same length.");

        for(i = 0; i < v1->rows; i++) {
                total += v1->m[i] * v2->m[i];
        }

        return total;
 error:
        return 0;  // Take this return value with a grain of salt!
}

/* Are two Vectors orthogonal? */
bool coglVIsOrtho(matrix_t* v1, matrix_t* v2) {
        return coglVDotProduct(v1,v2) <= 0.000001;
}

/* Is a given Matrix struct actually a Vector? */
bool coglVIsVector(matrix_t* v) {
        check(v, "Null Vector given.");

        return v->cols == 1;
 error:
        return false;
}

// --- MATRICES --- //

/* Create a column-major matrix */
matrix_t* coglMCreate(size_t cols, size_t rows) {
        matrix_t* m = NULL;
        GLfloat* innerM;
        size_t i;

        check(cols > 0 && rows > 0, "Bad dimensions given.");

        innerM = (GLfloat*)malloc(cols * rows * sizeof(GLfloat));
        check_mem(innerM);

        // Initialize each entry to 0
        for(i = 0; i < cols * rows; i++) {
                innerM[i] = 0;
        }

        // Construct actual return value
        m = malloc(sizeof(matrix_t));
        check_mem(m);

        m->m = innerM;
        m->cols = cols;
        m->rows = rows;

        return m;

 error:
        return NULL;
}

/* Create a column-major Matrix from a given array of floats */
matrix_t* coglMFromArray(size_t cols, size_t rows, GLfloat* fs) {
        matrix_t* m = NULL;
        size_t i;
        
        check(fs, "Null float array given.");
        check(cols > 0 && rows > 0, "Bad sizes given.");

        m = coglMCreate(cols,rows);
        check(m, "Failed to create matrix.");

        // Copy values of given Floats
        for(i = 0; i < cols * rows; i++) {
                m->m[i] = fs[i];
        }
        
        return m;
 error:
        return NULL;
}

/* Make a copy of a given Matrix */
matrix_t* coglMCopy(matrix_t* m) {
        matrix_t* newM = NULL;
        size_t i;

        check(m, "Can't copy a Null Matrix.");

        newM = coglMCreate(m->cols,m->rows);
        check(newM, "Failed to create new Matrix.");

        for(i = 0; i < m->cols * m->rows; i++) {
                newM->m[i] = m->m[i];
        }

        return newM;
 error:
        return NULL;
}

/* Create an Identity Matrix of size `dim` */
matrix_t* coglMIdentity(size_t dim) {
        matrix_t* m = coglMCreate(dim,dim);
        unsigned int i;

        check(m, "Matrix creation failed.");

        for(i = 0; i < dim; i++) {
                m->m[dim * i + i] = 1;
        }

        return m;
 error:
        return NULL;
}

/* Are two Matrices equal? */
bool coglMEqual(matrix_t* m1, matrix_t* m2) {
        size_t i;

        check(m1 && m2, "Null Matrices given.");
        check(m1->cols == m2->cols && m1->rows == m2->rows,
              "Matrices given aren't the same size.");

        for(i = 0; i < m1->cols * m1->rows; i++) {
                quiet_check(m1->m[i] == m2->m[i]);
        }

        return true;
 error:
        return false;
}

/* Set a value in a Matrix */
void coglMSet(matrix_t* m, size_t col, size_t row, GLfloat f) {
        if(m && m->cols >= col && m->rows >= row) {
                m->m[m->rows * col + row] = f;
        }
}

/* Scale a Matrix by some scalar. If the Matrix is 4x4, resets the homo bit */
matrix_t* coglMScale(matrix_t* m, GLfloat f) {
        size_t i;

        check(m, "Null Matrix given.");
        
        for(i = 0; i < m->cols * m->rows; i++) {
                m->m[i] *= f;
        }

        // Reset homo bit to 1.
        if(m->cols == 4 && m->rows == 4) {
                coglMSet(m,3,3,1);
        }

        return m;
 error:
        return NULL;
}

/* The values of m2 are added to m1 */
matrix_t* coglMAdd(matrix_t* m1, matrix_t* m2) {
        size_t i;

        check(m1 && m2, "Null Matrices given.");
        check(m1->cols == m2->cols && m1->rows == m2->rows,
              "Matrices given aren't the same size.");

        for(i = 0; i < m1->cols * m1->rows; i++) {
                m1->m[i] += m2->m[i];
        }

        return m1;
 error:
        return NULL;
}

/* Add two same-sized Matrices together. Returns a new Matrix. */
matrix_t* coglMAddP(matrix_t* m1, matrix_t* m2) {
        matrix_t* newM = NULL;

        check(m1 && m2, "Null Matrices given.");

        newM = coglMCopy(m1);
        check(newM, "Failed to create Matrix.");

        newM = coglMAdd(newM,m2);

        return newM;
 error:
        return NULL;
}

/* Subtract two same-sized Matrices */
matrix_t* coglMSub(matrix_t* m1, matrix_t* m2) {
        size_t i;

        check(m1 && m2, "Null Matrices given.");
        check(m1->cols == m2->cols && m1->rows == m2->rows,
              "Matrices given aren't the same size.");

        for(i = 0; i < m1->cols * m1->rows; i++) {
                m1->m[i] -= m2->m[i];
        }

        return m1;
 error:
        return NULL;
}

/* Subtract two same-sized Matrices. Returns a new Matrix. */
matrix_t* coglMSubP(matrix_t* m1, matrix_t* m2) {
        matrix_t* newM = NULL;

        check(m1 && m2, "Null Matrices given.");

        newM = coglMCopy(m1);
        check(newM, "Failed to create Matrix.");

        newM = coglMSub(newM,m2);

        return newM;
 error:
        return NULL;
}

/* Multiply two 4x4 matrices together in place. Affects `m1`. */
matrix_t* coglM4Multiply(matrix_t* m1, matrix_t* m2) {
        static GLfloat fs[16];
        size_t i,j,k;

        // Were the matrices given valid?
        check(m1 && m2, "Null matrices given.");
        check(m1->cols == 4 && m1->rows == 4, "Matrix not 4x4.");
        check(m1->cols == m2->rows, "Matrix sizes not compatible.");

        // O(n^3)? I'm sorry?
        for(i = 0; i < m1->rows; i++) {
                for (j = 0; j < m2->cols; j++) {
                        fs[j * (m1->rows) + i] = 0;

                        for (k = 0; k < m2->rows; k++) {
                                fs[j * (m1->rows) + i] +=
                                        m1->m[k * (m1->rows) + i] *
                                        m2->m[j * (m2->rows) + k];
                        }
                }
        }

        // Copy values back into `m1`.
        for(i = 0; i < m1->cols * m1->rows; i++) {
                m1->m[i] = fs[i];
        }

        return m1;
 error:
        return NULL;
}

/* Multiply two matrices together. The number of rows of m2 must match
   the number of columns of m1. Returns a new Matrix. */
matrix_t* coglMMultiplyP(matrix_t* m1, matrix_t* m2) {
        matrix_t* newM = NULL;
        size_t i,j,k;

        // Were the matrices given valid?
        check(m1 && m2, "Null matrices given.");
        check(m1->cols == m2->rows, "Matrix sizes not compatible.");

        newM = coglMCreate(m2->cols, m1->rows);
        check_mem(newM);

        // O(n^3)? I'm sorry?
        for(i = 0; i < m1->rows; i++) {
                for (j = 0; j < m2->cols; j++) {
                        newM->m[j * (m1->rows) + i] = 0;

                        for (k = 0; k < m2->rows; k++) {
                                newM->m[j * (m1->rows) + i] +=
                                        m1->m[k * (m1->rows) + i] *
                                        m2->m[j * (m2->rows) + k];
                        }
                }
        }

        return newM;
 error:
        return NULL;
}

/* Transpose a Matrix. Returns a new Matrix. */
matrix_t* coglMTranspose(matrix_t* m) {
        matrix_t* newM = NULL;
        size_t i,j;

        check(m, "Null Matrix given.");

        newM = coglMCreate(m->rows,m->cols);
        check(newM, "Matrix creation failed.");

        for(i = 0; i < m->rows; i++) {
                for(j = 0; j < m->cols; j++) {
                        newM->m[i * m->cols + j] = m->m[j * m->rows + i];
                }
        }

        return newM;
 error:
        return NULL;
}

/* Rotate a 4x4 Matrix in place by `r` radians around the unit vector
formed by `x` `y` and `z` */
matrix_t* coglM4Rotate(matrix_t* m,GLfloat r,GLfloat x,GLfloat y,GLfloat z) {
        static matrix_t rot;
        static GLfloat fs[16] = {
                1,0,0,0,
                0,1,0,0,
                0,0,1,0,
                0,0,0,1
        };

        check(m, "Null Matrix given.");
        check(m->cols == 4 && m->rows == 4, "Matrix not 4x4");

        // To simply the Matrix below.
        GLfloat cosr = cos(r);
        GLfloat sinr = sin(r);
        
        // Borrowed from https://en.wikipedia.org/wiki/Rotation_matrix
        // Column 1
        fs[0] = cosr+x*x*(1-cosr);
        fs[1] = y*x*(1-cosr)+z*sinr;
        fs[2] = z*x*(1-cosr)-y*sinr;
        // Column 2
        fs[4] = x*y*(1-cosr)-z*sinr;
        fs[5] = cosr+y*y*(1-cosr);
        fs[6] = z*y*(1-cosr)+x*sinr;
        // Column 3
        fs[8]  = x*z*(1-cosr)+y*sinr;
        fs[9]  = y*z*(1-cosr)-x*sinr;
        fs[10] = cosr+z*z*(1-cosr);

        // Set stack struct values.
        rot.m = fs;
        rot.cols = 4;
        rot.rows = 4;

        return coglM4Multiply(m,&rot);
 error:
        return NULL;
}

/* Adds translation factor to a transformation Matrix (in place) */
matrix_t* coglM4Translate(matrix_t* m, GLfloat x, GLfloat y, GLfloat z) {
        check(m, "Null Matrix given.");
        check(m->cols == 4 && m->rows == 4, "Matrix isn't 4x4");

        // Set translation values.
        m->m[12] = x;
        m->m[13] = y;
        m->m[14] = z;

        return m;
 error:
        return NULL;
}

/* Produces a Perspective Projection Matrix.
   fov  := Field of View. Vertical eye angle, usually (tau/8).
   aspr := Aspect Ratio. Screen (width/height).
   n    := Distance from camera to near-clipping plane.
   f    := Distance from camera to far-clipping plane. */
matrix_t* coglMPerspectiveP(GLfloat fov, GLfloat aspr, GLfloat n, GLfloat f) {
        matrix_t* m = NULL;

        check(aspr > 0, "Invalid Aspect Ratio given.");
        check(n < f, "Near-clipping plane farther than far-clipping plane!");

        GLfloat t = n * tan(fov / 2.0);
        GLfloat r = t * aspr;

        GLfloat fs[16] = {
                n/r, 0, 0, 0,
                0, n/t, 0, 0,
                0, 0, -(f+n)/(f-n), -1,
                0, 0, (-2*f*n)/(f-n), 0
        };

        m = coglMFromArray(4,4,fs);
        check(m, "Could not create Perspective Matrix.");

        return m;
 error:
        return NULL;
}

/* Generate a View Matrix */
matrix_t* coglM4LookAtP(matrix_t* camPos, matrix_t* target, matrix_t* up) {
        matrix_t* view     = NULL;
        matrix_t* camDir   = NULL;
        matrix_t* camRight = NULL;
        matrix_t* camUp    = NULL;
        matrix_t* pos      = NULL;

        check(camPos && target && up, "Null Vectors given.");
        check(coglVIsVector(camPos) &&
              coglVIsVector(target) &&
              coglVIsVector(up), "Matrices given instead of Vectors.");

        camDir   = coglVNormalize(coglMSubP(camPos,target));
        camRight = coglVCrossP(up,camDir);
        camUp    = coglVCrossP(camDir,camRight);

        view = coglMIdentity(4);
        check(view, "View Matrix creation failed.");

        // Copy values.
        // Column 1
        view->m[0] = camRight->m[0];
        view->m[1] = camUp->m[0];
        view->m[2] = camDir->m[0];

        // Column 2
        view->m[4] = camRight->m[1];
        view->m[5] = camUp->m[1];
        view->m[6] = camDir->m[1];

        // Column 3
        view->m[8]  = camRight->m[2];
        view->m[9]  = camUp->m[2];
        view->m[10] = camDir->m[2];

        // Column 4
        pos = coglMCopy(camPos);
        check(pos, "`camPos` Matrix copy failed.");
        coglMScale(pos, -1);
        view->m[12] = pos->m[0];
        view->m[13] = pos->m[1];
        view->m[14] = pos->m[2];

        coglMDestroy(camDir);
        coglMDestroy(camRight);
        coglMDestroy(camUp);
        coglMDestroy(pos);

        return view;
 error:
        if(camDir)   { coglMDestroy(camDir);   }
        if(camRight) { coglMDestroy(camRight); }
        if(camUp)    { coglMDestroy(camUp);    }
        if(pos)      { coglMDestroy(pos);      }

        return NULL;
}

/* Deallocate a Matrix */
void coglMDestroy(matrix_t* m) {
        if(m) {
                free(m->m);
                free(m);
        }
}

/* Print a Matrix */
void coglMPrint(matrix_t* m) {
        size_t i,j;

        if(m) {
                for(i = 0; i < m->rows; i++) {
                        printf("[ ");

                        for(j = 0; j < m->cols; j++) {
                                printf("%.2f ", m->m[m->rows * j + i]);
                        }

                        printf("]\n");
                }
        }
}

/* Print Matrix values in their internal order */
void coglMPrintLinear(matrix_t* m) {
        size_t i;

        if(m) {
                for(i = 0; i < (m->rows * m->cols); i++) {
                        printf("%.2f\n", m->m[i]);
                }
        }
}
