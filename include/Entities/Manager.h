#ifndef _ANCIENT_HISTORY_ENTITY_MANAGER_H
#define _ANCIENT_HISTORY_ENTITY_MANAGER_H

#include "../Level.h"

/* ================================================================ */

/**
 * 
 */
int EntityManager_add(const void* entity);

/**
 * 
 */
int EntityManager_setPlayer(const void* player);

/**
 * 
 */
void EntityManager_clear(void);

/**
 * 
 */
void EntityManager_draw(SDL_Renderer* context);

/**
 * 
 */
void EntityManager_process(void);

/**
 * 
 */
Level* EntityManager_getLevel(void);

/**
 * 
 */
void EntityManager_setLevel(Level* level);

/* ================================================================ */

#endif /* _ANCIENT_HISTORY_ENTITY_MANAGER_H */
