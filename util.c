#include "util.h"

#define E 0.000001

/* Is a given float essentially zero? */
bool isZero(GLfloat f) {
        return (f > 0 && f < E) || (f < 0 && f > -E);
}
