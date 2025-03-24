#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/constants.h" 

#include "../../framework/include/clock.h"
#include "../../framework/include/io.h"

/* ================================================================ */

struct crouching_state {
    const void* state_class;    /* Must be first */
};

/* ================================ */

static void Crouching_handle(void* _entity) {

    struct entity* entity = _entity;

    if (!Input_isKey_pressed(SDL_SCANCODE_DOWN)) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Standing);
    }
}

/* ================================ */

static void Crouching_update(void* _entity) {

    struct entity* entity = _entity;
    struct standing_state* state = entity->state;

    /* Slighlty decrease the player's velocity */
    if (Input_isKey_pressed(SDL_SCANCODE_LEFT)) {

        entity->position.x -= 1;

        if (entity->position.x - entity->width + entity->width <= 0) {
            entity->position.x = 0;
        }
    }

    /* Slighlty decrease the player's velocity */
    if (Input_isKey_pressed(SDL_SCANCODE_RIGHT)) {

        entity->position.x += 1;

        if (entity->position.x + entity->width >= SCREEN_WIDTH) {
            entity->position.x = SCREEN_WIDTH - entity->width;
        }
    }
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state_class _Crouching = {

    .size = sizeof(struct crouching_state),

    .ctor = NULL,
    .dtor = NULL,

    .handle = Crouching_handle,
    .update = Crouching_update,
};

const void* Crouching = &_Crouching;

/* ================================================================ */
