#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"

/* ================================================================ */

void* State_create(const void* state_type, ...) {

    const struct state_class* state = state_type;
    void* new_state = NULL;

    if ((new_state = calloc(1, state->size)) == NULL) {
        return NULL;
    }
    
    /* Assigning a Virtual Table to the State */
    *(const struct state_class**) new_state = state_type;

    if (state->ctor != NULL) {

        va_list ap;

        va_start(ap, state_type);
        new_state = state->ctor(new_state, &ap);
        va_end(ap);
    }

    return new_state;
}

/* ================================ */

void State_destroy(void* _state) {

    const struct state_class* const* state_p = _state;

    if ((_state != NULL) && (*state_p != NULL) && ((*state_p)->dtor != NULL)) {
        _state = (*state_p)->dtor(_state);
    }

    free(_state);
}

/* ================================ */

void State_handle(void* _entity) {

    const struct entity* entity = _entity;
    const struct state_class* const* state = entity->state;

    if ((_entity != NULL) && (entity != NULL) && (state != NULL) && (*state != NULL)) {
        (*state)->handle(_entity);
    }
}

/* ================================ */

void State_update(void* _entity) {

    const struct entity* entity = _entity;
    const struct state_class* const* state = entity->state;


    if ((_entity != NULL) && (entity != NULL) && (state != NULL) && (*state != NULL)) {
        (*state)->update(_entity);
    }
}

/* ================================================================ */
