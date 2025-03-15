#ifndef _WIDGET_HIDDEN_CLASS_H
#define _WIDGET_HIDDEN_CLASS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <SDL2/SDL.h>

#include "../text.h"
#include "../Math/Vector2D.h"

/* ================================================================ */

/* ================================================================ */
/* =========== This file should only be included in the =========== */
/* ================ source files to avoid exposing ================ */
/* ==================== implementation details ==================== */
/* ================================================================ */

typedef struct widget_class {

    /* How much memory to allocate */
    size_t size;

    /* Widget class name */
    const char* name;

    /* How to construct a widget */
    void* (*ctor)(void* self, va_list* app);
    /* How to destroy a widget */
    void* (*dtor)(void* self);
    /* How to draw a widget on the screen */
    int   (*draw)(const void* self, SDL_Renderer* context);
    /* How to get a widget label */
    const char* (*get_label)(const void* self);
    /* Output widget information into the stream */
    void  (*log)(const void* self, FILE* stream);
    /* How to get widget `Text` */
    Text* (*get_text)(const void* self);
    /* How to get widget position */
    Vector2D* (*get_position)(const void* self);

    void* next_widget;
    void* previous_widget;
} WidgetClass;

/* ================================================================ */

#endif /* _WIDGET_HIDDEN_CLASS_H */
