#ifndef _ANCIENT_HISTORY_STATE_CLASS_H
#define _ANCIENT_HISTORY_STATE_CLASS_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================ */

struct state_class {
    
    size_t size;

    void* (*ctor)(void* state_type, va_list* app);
    void* (*dtor)(void* self);

    void (*handle)(void* entity);
    void (*update)(void* entity);
    void (*draw)(void* entity);
};

/* ================================================================ */

#endif /* _ANCIENT_HISTORY_STATE_CLASS_H */
