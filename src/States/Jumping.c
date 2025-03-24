#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"

#include "../../framework/include/clock.h"
#include "../../framework/include/io.h"

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

    /* Exit the current state */
    State_destroy(entity->state);
    entity->state = NULL;

    /* Enter a new state */
    entity->state = State_create(Falling);
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
