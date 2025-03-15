#ifndef _SPARK_VECTOR_INTERFACE_H
#define _SPARK_VECTOR_INTERFACE_H

#include <stdlib.h>
#include "math.h"

typedef struct _vector2d {
    float x;
    float y;
} Vector2D;

#define V2D_neg(v) Vector2D_negate((v))
#define V2D_gct(v, i) Vector2D_get_component((v), (i))
#define V2D_mlt(v, s) Vector2D_multiply((v), (s))
#define V2D_div(v, s) Vector2D_divide((v), (s))
#define V2D_mgt(v) Vector2D_magnitude((v))
#define V2D_nmz(v) Vector2D_normalize((v))
#define V2D_add(a, b) Vector2D_add((a), (b))
#define V2D_sub(a, b) Vector2D_sub((a), (b))

/**
 * Get a component of a given vector (0-based).
 * 
 * Usage: `V2D_gct(v, 1);`
 * Retreive the Y-component of a 2D vector.
 */
float Vector2D_get_component(const Vector2D* v, int i);

/**
 * Negate the vector.
 */
Vector2D Vector2D_negate(const Vector2D* v);

/**
 * Multiply the given vector by some scalar.
 */
Vector2D Vector2D_multiply(const Vector2D* _v, float s);

/**
 * Divide the given vector by some scalar (multiply byy its reciprocal)
 */
Vector2D Vector2D_divide(const Vector2D* _v, float s);

/**
 * Get the magnitude of the vector.
 */
float Vector2D_magnitude(const Vector2D* v);

/**
 * Normalize the vector.
 */
Vector2D Vector2D_normalize(const Vector2D* _v);

/**
 * Destroy a dyamically allocated vector.
 */
void Vector2D_destroy(Vector2D* v);

/**
 * Dynamicall create (allocate) a vector.
 */
Vector2D* Vector2D_new(float x, float y);

/**
 * Add `b` to `a`.
 */
Vector2D Vector2D_add(Vector2D* a, const Vector2D* b);

/**
 * Subtract `b` from `a`.
 */
Vector2D Vector2D_sub(Vector2D* a, const Vector2D* b);

#endif /* _SPARK_VECTOR_INTERFACE_H */
