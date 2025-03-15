#include <stdio.h>
#include <assert.h>
#include "../../include/Math/Vector2D.h"

Vector2D* Vector2D_new(float x, float y) {

    Vector2D* v = NULL;

    if ((v = calloc(1, sizeof(struct _vector2d))) == NULL) {
        return NULL;
    }

    v->x = x;
    v->y = y;

    return v;
}

/* ================================ */

Vector2D Vector2D_add(Vector2D* a, const Vector2D* b) {

    Vector2D v = {0.0f, 0.0f};

    assert((a != NULL) && (b != NULL));

    v.x += a->x + b->x;
    v.y += a->y + b->y;

    return v;
}   

/* ================================ */

Vector2D Vector2D_sub(Vector2D* a, const Vector2D* b) {

    Vector2D v = {0.0f, 0.0f};

    assert((a != NULL) && (b != NULL));

    v.x += a->x - b->x;
    v.y += a->y - b->y;

    return v;
}

/* ================================ */

float Vector2D_get_component(const Vector2D* v, int i) {

    assert(v != NULL);
    assert((i >= 0) && (i <= 1));

    return *((float*) v + i);
}

/* ================================ */

Vector2D Vector2D_negate(const Vector2D* _v) {

    Vector2D v = {0.0f, 0.0f};

    assert(_v != NULL);

    v.x = (_v) ? -_v->x : v.x;
    v.y = (_v) ? -_v->y : v.y;

    return v;
}

/* ================================ */

Vector2D Vector2D_multiply(const Vector2D* _v, float s) {

    Vector2D v = {0.0f, 0.0f};

    assert(_v != NULL);

    v.x = _v->x * s;
    v.y = _v->y * s;

    return v;
}

/* ================================ */

Vector2D Vector2D_divide(const Vector2D* _v, float s) {

    Vector2D v = {0.0f, 0.0f};

    assert(_v != NULL);
    assert(s != 0);

    v.x = _v->x / s;
    v.y = _v->y / s;

    return v;
}

/* ================================ */

float Vector2D_magnitude(const Vector2D* v) {

    if (v == NULL) {
        return 0;
    }

    return (sqrt(v->x * v->x + v->y * v->y));
}

/* ================================ */

Vector2D Vector2D_normalize(const Vector2D* _v) {

    return Vector2D_divide(_v, Vector2D_magnitude(_v));
}

/* ================================ */

void Vector2D_destroy(Vector2D* v) {
    free(v);
}
