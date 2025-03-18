#include "../../include/Entities/Entity.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__collectable.h"
#include "Level.h"

/* ================================================================ */

static void* Collectible_ctor(void* _self, va_list* app) {

    struct collectible* self = ((const struct entity_class*) Entity)->ctor(_self, app);

    /* Placing collectable entities in the middle of a tile */
    ((struct entity*) self)->level_x = ((struct entity*) self)->position.x / TILE_SIZE;
    ((struct entity*) self)->level_y = ((struct entity*) self)->position.y / TILE_SIZE;
    ((struct entity*) self)->position.x = ((struct entity*) self)->level_x * TILE_SIZE + TILE_SIZE / 2 - ((struct entity*) self)->width / 2;
    ((struct entity*) self)->position.y = ((struct entity*) self)->level_y * TILE_SIZE + TILE_SIZE / 2 - ((struct entity*) self)->height / 2;

    return self;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct entity_class _Collectible = {
    .size = sizeof(struct collectible),
    .ctor = Collectible_ctor,
};

const void* Collectible = &_Collectible;

/* ================================================================ */
