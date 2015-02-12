// Testing opengl-linalg

#include <stdlib.h>

#include "linalg.h"
#include "../dbg.h"

// --- //

int main(int argc, char** argv) {
        int i;
        GLfloat A[] = {1,2,3,4};
        GLfloat B[] = {5,6,2,3,1,7};
        GLfloat C[] = {5,6,7,8};
        GLfloat z[] = {0,0,1,0};
        matrix_t* id = coglMIdentity(4);
        matrix_t* m = coglMIdentity(4);
        matrix_t* n = coglMFromArray(2,2,A);
        matrix_t* o = coglMFromArray(2,2,C);
        check(m, "Matrix didn't create properly.");

        log_info("Altered ID Matrix");
        coglMSet(m,3,0,7);
        coglMPrint(m);
        coglMDestroy(m);

        log_info("Created from Array");
        m = coglMFromArray(3,2,B);
        coglMPrint(m);

        log_info("Product of two matrices");
        matrix_t* prod = coglMMultiplyP(n,m);
        coglMPrint(prod);
        debug("cols: %d rows: %d", prod->cols, prod->rows);
        log_info("Product of incompatable matrices");
        coglMMultiplyP(m,n);

        log_info("Sum of two matrices");
        matrix_t* sum = coglMAddP(n,o);
        coglMPrint(sum);

        log_info("Copying a matrix");
        matrix_t* copy = coglMCopy(m);
        coglMPrint(copy);

        log_info("Testing Matrix equality");
        printf("Equal? %d\n", coglMEqual(copy,copy));
        printf("Equal? %d\n", coglMEqual(copy,sum));

        log_info("Transpose");
        matrix_t* trans = coglMTranspose(prod);
        coglMPrint(trans);

        log_info("Rotating a Matrix");
        coglMPrint(id);
        coglM4Rotate(id,tau/2, 0,0,1);
        coglMPrint(id);

        log_info("Cross Product");
        matrix_t* v = coglVFromArray(4,C);
        matrix_t* v2 = coglVFromArray(4,z);
        matrix_t* cross = coglVCrossP(v,v);
        matrix_t* cross2 = coglVCrossP(v,v2);
        coglMPrint(cross);
        puts("---");
        coglMPrint(cross2);
        printf("Ortho: %d\n",coglVIsOrtho(cross2,v));
        printf("Ortho: %d\n",coglVIsOrtho(cross2,v2));
        
        log_info("Vector Length");
        printf("%f\n", coglVLength(v));
        coglVNormalize(v);
        coglMPrint(v);
        printf("%f\n", coglVLength(v));
        
        debug("Destroying Matrices...");

        coglMDestroy(v);
        coglMDestroy(v2);
        coglMDestroy(cross);
        coglMDestroy(cross2);
        coglMDestroy(m);
        coglMDestroy(n);
        coglMDestroy(o);
        coglMDestroy(prod);
        coglMDestroy(sum);
        coglMDestroy(copy);
        coglMDestroy(trans);
        
        return EXIT_SUCCESS;

 error:
        return EXIT_FAILURE;
}
