#ifndef _SPARK_INPUT_MANAGER_H
#define _SPARK_INPUT_MANAGER_H

#include <SDL2/SDL.h>

/* ================================================================ */

typedef enum {LMB, MMB, RMB} MouseButton;

/**
 * 
 */
void Input_update(void);

/**
 * 
 */
int Input_isKey_pressed(SDL_Scancode key);

/**
 * 
 */
int Input_isKey_just_pressed(SDL_Scancode key);

/**
 * 
 */
int Input_isBtn_pressed(MouseButton btn);

/**
 * 
 */
int Input_isBtn_just_pressed(MouseButton btn);

/* ================================================================ */

#endif /* _SPARK_INPUT_MANAGER_H */
