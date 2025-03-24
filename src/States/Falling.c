#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/entity.h"

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

    entity->position.y += 1;

    if (Entity_isGrounded(entity)) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Standing);
    }

    /* ================ */

    if (Input_isKey_pressed(SDL_SCANCODE_LEFT)) {

        entity->position.x -= 1.5;

        if (entity->position.x <= 0) {
            entity->position.x = 0;
        }
    }

    /* ================ */

    if (Input_isKey_pressed(SDL_SCANCODE_RIGHT)) {

        entity->position.x += 1.5;

        if (entity->position.x <= 0) {
            entity->position.x = 0;
        }
    }
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
