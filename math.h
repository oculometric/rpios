#ifndef MATH_H
#define MATH_H

#include <stdint.h>
#include <stddef.h>

#define MATH_PI 3.141592653589793 // Pi
#define MATH_PI2 6.28318530718    // 2*Pi
#define MATH_PI_2 1.57079632679   // Pi/2

// sin (radians)
static inline float sin (float x) {
    float xp = x;
    if (xp < 0)
        do { xp+=MATH_PI2; } while (xp < 0);
    else if (xp > MATH_PI2)
        do { xp-=MATH_PI2; } while (xp > MATH_PI2);

    float p = (xp-MATH_PI);
    float pp = p*p;
    return  - (p)
            + (p*pp)/6
            - (p*pp*pp)/120
            + (p*pp*pp*pp)/5040
            - (p*pp*pp*pp*pp)/362880;
}

// cos (radians)
static inline float cos (float x) {
    return sin (x-MATH_PI_2);
}

#endif