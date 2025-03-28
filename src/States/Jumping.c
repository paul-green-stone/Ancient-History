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

    /* Allow the player to move while falling */
    if (Input_isKey_pressed(SDL_SCANCODE_LEFT)) {

        entity->velocity.x = -(Clock_getDelta(m_clock) * entity->speed);

        if (entity->position.x <= 0) {
            entity->position.x = 0;
        }
    }

    /* ================ */

    /* Allow the player to move while falling */
    if (Input_isKey_pressed(SDL_SCANCODE_RIGHT)) {

        entity->velocity.x = Clock_getDelta(m_clock) * entity->speed; 

        if (entity->position.x <= 0) {
            entity->position.x = 0;
        }
    }

    /* This one is supposed to check whether there is a platform above the player or not.
    SPOILER: Doesn't work as intended (AT ALL!) */
    if (Entity_isPlatformAbove(_entity, EntityManager_getLevel())) {

        entity->position.y = (entity->position.y / TILE_SIZE) + entity->height;

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Falling);

        /* The player just hit the platform and immediately stopped. */
        entity->velocity.y = 0;
        entity->position.y = (entity->level_y + 1) * TILE_SIZE;
    }

    /* ================ */

    /* When the vertical velocity becomes positive or zero, it means the player started to fall down */
    if (entity->velocity.y >= 0) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Falling);
    }

    /* Update the player's position */
    entity->position = Vector2D_add(&entity->position, &entity->velocity);
    /* Prevent inertia */
    entity->velocity.x = 0;
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
