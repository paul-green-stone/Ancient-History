#ifndef _ANCIENT_HISTORY_STATE_INTERFACE_H
#define _ANCIENT_HISTORY_STATE_INTERFACE_H

/* ================================================================ */

/**
 * 
 */
void* State_create(const void* state_type, ...);

/**
 * 
 */
void State_destroy(void* state);

/**
 * Handle the state of the entity
 */
void State_handle(void* entity);

/**
 *
 */
void State_update(void* entity);

/**
 * 
 */
int State_draw(void* entity);

/* ================================================================ */

#endif /* _ANCIENT_HISTORY_STATE_INTERFACE_H */
