#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"

#include "../../framework/include/clock.h"
#include "../../framework/include/io.h"

/* ================================================================ */

struct ducking_state {
    const void* state_class;    /* Must be first */
};

/* ================================ */

static void Ducking_handle(void* _entity) {

    struct entity* entity = _entity;

    if (!Input_isKey_pressed(SDL_SCANCODE_DOWN)) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Standing);
    }

    /* ================ */

    if (Input_isKey_pressed(SDL_SCANCODE_LEFT) || Input_isKey_pressed(SDL_SCANCODE_RIGHT)) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Crouching);
    }
}

/* ================================ */

static void Ducking_update(void* _entity) {

    struct entity* entity = _entity;
    struct standing_state* state = entity->state;

    if (Input_isKey_pressed(SDL_SCANCODE_DOWN)) {
        printf("You are ducking\n");
    }
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state_class _Ducking = {

    .size = sizeof(struct ducking_state),

    .ctor = NULL,
    .dtor = NULL,

    .handle = Ducking_handle,
    .update = Ducking_update,
    .draw = NULL,
};

const void* Ducking = &_Ducking;

/* ================================================================ */
