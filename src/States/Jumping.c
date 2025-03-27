#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/entity.h"
#include "../../include/Entities/Manager.h"

#include "../../framework/include/clock.h"
#include "../../framework/include/io.h"

#include "constants.h"

/* ================================================================ */

struct jumping_state {
    const void* state_class;    /* Must be first */

    /* Here might go variables that control the jump */
};

/* ================================ */

static void Jumping_handle(void* _entity) {

    struct entity* entity = _entity;
}

/* ================================ */

static void Jumping_update(void* _entity) {

    struct entity* entity = _entity;
    struct standing_state* state = entity->state;

    /* After entering the `Jumping` state, the player's vertical velocity is negative, causing the player to move upward.
    The gravitation acting on it increments its velocity. DO NOT FORGET THAT POSITIVE Y GOES DOWNWARD! */
    entity->velocity.y += gravity * Clock_getDelta(m_clock);
    /* Update the player's position */
    entity->position = Vector2D_add(&entity->position, &entity->velocity);

    /* This one is supposed to check whether there is a platform above the player or not.
    SPOILER: Doesn't work as intended (AT ALL!) */
    if (Entity_isPlatformAbove(_entity, EntityManager_getLevel())) {

        entity->position.y = (entity->position.y / TILE_SIZE) + entity->height;

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Falling);

        printf("Platform is above the player\n");
    }

    /* ================ */

    /* When the vertical velocity becomes zero or negative, it means the player started to fall down */
    if (entity->velocity.y <= 0) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Falling);
    }
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state_class _Jumping = {

    .size = sizeof(struct jumping_state),

    .ctor = NULL,
    .dtor = NULL,

    .handle = Jumping_handle,
    .update = Jumping_update,
};

const void* Jumping = &_Jumping;

/* ================================================================ */
