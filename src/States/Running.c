#include "../../include/constants.h"
#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/entity.h"
#include "../../include/Entities/Manager.h"

#include "../../framework/include/clock.h"
#include "../../framework/include/io.h"

extern Clock* m_clock;

/* ================================================================ */

struct running_state {
    const void* state_class;    /* Must be first */
};

/* ================================ */

static void Running_handle(void* _entity) {

    struct entity* entity = _entity;

    /* Going to enter the `Standing` state */
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

    /* ================ */

    /* Going to enter the `Jumping` state */
    if (Input_isKey_pressed(SDL_SCANCODE_UP)) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Jumping);
        entity->velocity.y = entity->jump_speed;
    }
}

/* ================================ */

static void Running_update(void* _entity) {

    struct entity* entity = _entity;
    struct standing_state* state = entity->state;
    
    /* Increase the player's speed while running */
    if (Input_isKey_pressed(SDL_SCANCODE_LEFT)) {

        entity->velocity.x = -(Clock_getDelta(m_clock) * entity->speed);
        entity->position = Vector2D_add(&entity->position, &entity->velocity);

        if (entity->position.x <= 0) {
            entity->position.x = 0;
        }
    }

    /* ================ */

    /* Increase the player's speed while running */
    if (Input_isKey_pressed(SDL_SCANCODE_RIGHT)) {

        entity->velocity.x = Clock_getDelta(m_clock) * entity->speed;
        entity->position = Vector2D_add(&entity->position, &entity->velocity);

        if (entity->position.x + entity->width >= SCREEN_WIDTH) {
            entity->position.x = SCREEN_WIDTH - entity->width;
        }
    }

    /* ================ */

    /* The player is falling off the platform */
    if (!Entity_isGrounded(entity, EntityManager_getLevel())) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;
 
        /* Enter a new state */
        entity->state = State_create(Falling);
    }

    entity->velocity.x = entity->velocity.y = 0;
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
