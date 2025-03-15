#ifndef _SPARK_MATH_H
#define _SPARK_MATH_H

#include <time.h>
#include <math.h>

/* ================================================================ */

/**
 * Get a random number from the range
 */
#define rand_range(min, max) (rand() % ((max) - (min) + 1) + (min))

/**
 * Find which of the two numbers is smaller
 */
#define min(x, y) ((x) > (y) ? (y) : (x))

/**
 * Find which of the two numbers is bigger
 */
#define max(x, y) ((x) > (y) ? (x) : (y))

/* ================================================================ */

#endif /* _SPARK_MATH_H */
