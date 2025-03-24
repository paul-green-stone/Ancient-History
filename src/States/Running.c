#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"

#include "../../framework/include/clock.h"
#include "../../framework/include/io.h"

#include "../../include/constants.h"

/* ================================================================ */

struct running_state {
    const void* state_class;    /* Must be first */
};

/* ================================ */

static void Running_handle(void* _entity) {

    struct entity* entity = _entity;

    /* Ging to enter the `Standing` state */
    if (!Input_isKey_pressed(SDL_SCANCODE_LEFT) || (!Input_isKey_pressed(SDL_SCANCODE_RIGHT))) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Standing);
    }

    /* ================ */

    /* Going to enter the `Ducking` state */
    if (Input_isKey_pressed(SDL_SCANCODE_DOWN)) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Ducking);
    }
}

/* ================================ */

static void Running_update(void* _entity) {

    struct entity* entity = _entity;
    struct standing_state* state = entity->state;

    /* Increate the player's speed while running */
    if (Input_isKey_pressed(SDL_SCANCODE_LEFT)) {

        entity->position.x -= 3;

        if (entity->position.x <= 0) {
            entity->position.x = 0;
        }
    }

    /* Increate the player's speed while running */
    if (Input_isKey_pressed(SDL_SCANCODE_RIGHT)) {

        entity->position.x += 3;

        if (entity->position.x + entity->width >= SCREEN_WIDTH) {
            entity->position.x = SCREEN_WIDTH - entity->width;
        }
    }
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state_class _Running = {

    .size = sizeof(struct running_state),

    .ctor = NULL,
    .dtor = NULL,

    .handle = Running_handle,
    .update = Running_update,
};

const void* Running = &_Running;

/* ================================================================ */
