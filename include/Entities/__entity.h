#ifndef _ANCIENT_HISTORY_ENTITY_REPRESENTATION_H
#define _ANCIENT_HISTORY_ENTITY_REPRESENTATION_H

#include <stdarg.h>

#include "../../framework/include/Math/Vector2D.h"
#include "../../framework/include/texture.h"
#include "../States/States.h"

#define NOT !

/**
 * Get the row of the entity 
 */
#define get_row(ent) (int) (ent)->position.y / TILE_SIZE

/**
 * Get the column of the entity
 */
#define get_column(ent) (int) (ent)->position.x / TILE_SIZE

/**
 * 
 */
#define does_rect_collide(r1, r2) ((r1.x <= r2.x + r2.w) && (r1.x + r1.w >= r2.x) && (r1.y <= r2.y + r2.h) && (r1.y + r1.h >= r2.y))

/* ================================================================ */
/* ======================= Paul's Addition ======================== */
/* ================================================================ */

struct entity {

    const void* entity_class;       /* Always goes first */

    Vector2D position;              /* Entity's position on the screen */
    int width;                      /* Entity's width */
    int height;                     /* Entity's height */

    int level_x;                    /* X position */
    int level_y;                    /* Y position */

    int lives;                      /* Describes how much damage an entity can withstand */

    Texture* texture;               /* Texture associated with the entity */

    SDL_Color color;                /* Entity's color. Just in case */

    void* state;                    /* Entity's current state */

    struct entity* next;            /* Next entity in the list */
    
    double speed;                   /* Entity's speed */
    double jump_speed;
    Vector2D velocity;              /* Entity's vector velocity */
};

/* ================================================================ */

#endif /* _ANCIENT_HISTORY_ENTITY_REPRESENTATION_H */