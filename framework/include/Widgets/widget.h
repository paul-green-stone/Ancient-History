#ifndef _WIDGET_SELECTOR_H
#define _WIDGET_SELECTOR_H

#include <stdio.h>
#include <SDL2/SDL.h>

#include "../text.h"
#include "Button.h"
#include "../Math/Vector2D.h"

/* ================================================================ */

/**
 * Create a new widget of the specified type.
 */
void* Widget_create(const void* widget_class, ...);

/**
 * 
 */
void Widget_destroy(void* widget);

/**
 * 
 */
void Widget_log(const void* widget, FILE* stream);

/**
 * 
 */
int Widget_draw(const void* widget, SDL_Renderer* context);

/**
 * 
 */
const char* Widget_getLable(const void* widget);

/**
 * 
 */
Text* Widget_getText(const void* widget);

/**
 * 
 */
Vector2D* Widget_getPosition(const void* widget);

/* ================================================================ */

#endif /* _WIDGET_SELECTOR_H */
