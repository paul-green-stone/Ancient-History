#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/entity.h"
#include "../../include/Entities/Manager.h"

#include "../../framework/include/clock.h"
#include "../../framework/include/io.h"

/* ================================================================ */

struct falling_state {
    const void* state_class;    /* Must be first */
};

/* ================================ */

static void Falling_handle(void* _entity) {

    struct entity* entity = _entity;
}

/* ================================ */

static void Falling_update(void* _entity) {

    struct entity* entity = _entity;
    struct standing_state* state = entity->state;

    /* Keep updating the entity's velocity.
    When you enter the `Falling` state, its vertical velocity becomes positive, and the player goes down */
    entity->velocity.y += gravity * Clock_getDelta(m_clock);

    /* The player has landed on the platform or something that can support it */
    if (Entity_isGrounded(entity, EntityManager_getLevel())) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Standing);
        entity->velocity.x = entity->velocity.y = 0;

        /* To adjust the player vertically on the platform after landing */
        entity->position.y = (entity->level_y * TILE_SIZE) + (TILE_SIZE - entity->height);
    }

    /* ================ */

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

    /* Update the player's position */
    entity->position = Vector2D_add(&entity->position, &entity->velocity);
    /* Prevent inertia */
    entity->velocity.x = 0;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state_class _Falling = {

    .size = sizeof(struct falling_state),

    .ctor = NULL,
    .dtor = NULL,

    .handle = Falling_handle,
    .update = Falling_update,
};

const void* Falling = &_Falling;

/* ================================================================ */
