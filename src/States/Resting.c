#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/__enemy.h"
#include "../../include/Entities/entity.h"
#include "../../include/Entities/Manager.h"

#include "../../framework/include/clock.h"

/* ================================================================ */

struct resting_state {

    const void* state_class;    /* Must be first */

    Clock* clock;
    int direction;
};

/* ================================ */

static void* Resting_ctor(void* _self, va_list* app) {

    struct resting_state* self = _self;

    self->direction = va_arg(*app, int);

    if ((self->clock = Clock_new()) == NULL) {
        return NULL;
    }

    Clock_setTimer(self->clock, va_arg(*app, double));
    Clock_start(self->clock);

    return self;
}

/* ================================ */

static void* Resting_dtor(void* _self) {

    struct resting_state* self = _self;

    Clock_destroy(&self->clock);

    return _self;
}

/* ================================ */

static void Resting_handle(void* _entity) {

    struct entity* entity = _entity;
    struct enemy* enemy_entity = _entity; 
    struct resting_state* state = entity->state;

    if (Clock_isReady(state->clock)) {
        
        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;
 
        /* Enter a new state */
        entity->state = State_create(Patrolling, get_row(entity), get_column(entity), enemy_entity->patrolling_distance, state->direction);

        return ;
    }
}

/* ================================ */

static void Resting_update(void* _entity) {

    SDL_Rect* env = Level_get_surroundings();

    struct entity* entity = _entity;
    struct resting_state* state = entity->state;

    Clock_update(state->clock);
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state_class _Resting = {

    .size = sizeof(struct resting_state),

    .ctor = Resting_ctor,
    .dtor = Resting_dtor,

    .handle = Resting_handle,
    .update = Resting_update,
    .draw = NULL,
};

const void* Resting = &_Resting;

/* ================================================================ */
