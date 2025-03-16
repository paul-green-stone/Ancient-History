#ifndef _ANCIENT_HISTORY_ENTITY_CLASS_REPRESENTATION_H
#define _ANCIENT_HISTORY_ENTITY_CLASS_REPRESENTATION_H

#include <stdlib.h>
#include <stdarg.h>
#include <SDL2/SDL.h>

/* ================================================================ */
/* ======================= Paul's Addition ======================== */
/* ================================================================ */

struct entity_class {

    size_t size;                                    /* Size in Bytes */

    void* (*ctor)(void* self, va_list* app);  /* Constructor */
    void* (*dtor)(void* self);                      /* Destructor */

    int (*is_collided)(const void* self, const void* other);

};

/* ================================================================ */

#endif /* _ANCIENT_HISTORY_ENTITY_CLASS_REPRESENTATION_H */
