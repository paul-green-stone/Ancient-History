#include "../../include/Entities/Entity.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__enemy.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"

#include "../../include/Level.h"

/* ================================================================ */

static void* Enemy_ctor(void* _self, va_list* app) {

    struct enemy* self = ((const struct entity_class*) Entity)->ctor(_self, app);
    struct entity* enemy_entity = _self;

    ((struct entity*) self)->level_x = ((struct entity*) self)->position.x / TILE_SIZE;
    ((struct entity*) self)->level_y = ((struct entity*) self)->position.y / TILE_SIZE;
    ((struct entity*) self)->position.x = ((struct entity*) self)->level_x * TILE_SIZE + (TILE_SIZE - ((struct entity*) self)->width) / 2;
    ((struct entity*) self)->position.y = ((struct entity*) self)->level_y * TILE_SIZE + (TILE_SIZE - ((struct entity*) self)->height) / 2;

    self->patrolling_distance = va_arg(*app, int);

    enemy_entity->state = State_create(EnemyFalling);

    return self;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct entity_class _Enemy = {
    .size = sizeof(struct enemy),
    .ctor = Enemy_ctor,
};

const void* Enemy = &_Enemy;

/* ================================================================ */
