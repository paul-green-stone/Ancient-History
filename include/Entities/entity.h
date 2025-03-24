#ifndef _ACIENT_HISTORY_ENTITY_INTERFACE_H
#define _ACIENT_HISTORY_ENTITY_INTERFACE_H

#include <SDL2/SDL.h>

#include "../../framework/include/Math/Vector2D.h"

/* ================================================================ */

/**
 * 
 */
void* Entity_create(const void* entity_type, ...);

/**
 * 
 */
void Entity_destroy(void* entity);

/**
 * 
 */
void Entity_move(const void* self, float delta_time);

/**
 * Statically linked function
 */
Vector2D* Entity_get_position(const void* self);

/**
 * Statically linked function
 */
int Entity_draw(void* entity, SDL_Renderer* context);

/**
 * Statically linked function
 */
SDL_Rect Entity_get_dimensions(const void* entity);

/**
 * Statically linked function
 */
int Entity_isCollided(const void* self, const void* other);

/**
 * This is just a test function to check the `Falling` state.
 * Me, Paul Stone, is not responsible for checking whether the player is on the platform or not,
 * it involves a slightly different mechanism.
 * For more information ask for Brick-Sigma.
 */
int Entity_isGrounded(const void* entity);

/* ================================================================ */

#endif /* _ACIENT_HISTORY_ENTITY_INTERFACE_H */
