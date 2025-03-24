#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"

#include "../../framework/include/clock.h"
#include "../../framework/include/io.h"

/* ================================================================ */

struct standing_state {

    const void* state_class;    /* Must be first */

    Clock* clock;
};

/* ================================ */

static void* Standing_ctor(void* _self, va_list* app) {

    struct standing_state* self = _self;

    if ((self->clock = Clock_new()) == NULL) {
        return NULL;
    }

    Clock_setTimer(self->clock, 3.0f);
    Clock_start(self->clock);

    return self;
}

/* ================================ */

static void* Standing_dtor(void* _self) {

    struct standing_state* self = _self;

    Clock_destroy(&self->clock);

    return _self;
}

/* ================================ */

static void Standing_handle(void* _entity) {

    struct entity* entity = _entity;
    
    /* Going to enter the `Running` state */
    if (Input_isKey_pressed(SDL_SCANCODE_LEFT) || (Input_isKey_pressed(SDL_SCANCODE_RIGHT))) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Running);
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

    /* ================ */

    /* Going to enter the `Jumping` state */
    if (Input_isKey_pressed(SDL_SCANCODE_UP)) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Jumping);
    }
}

/* ================================ */

static void Standing_update(void* _entity) {

    struct entity* entity = _entity;
    struct standing_state* state = entity->state;

    if (Clock_isReady(state->clock)) {
        printf("IDLEing now\n");
    }

    Clock_update(state->clock);
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state_class _Standing = {

    .size = sizeof(struct standing_state),

    .ctor = Standing_ctor,
    .dtor = Standing_dtor,

    .handle = Standing_handle,
    .update = Standing_update,
};

const void* Standing = &_Standing;

/* ================================================================ */
