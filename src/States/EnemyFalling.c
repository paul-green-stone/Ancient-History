#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/entity.h"
#include "../../include/Entities/Entity.h"
#include "../../include/Entities/Manager.h"

#include "../../framework/include/clock.h"

/* ================================================================ */

struct enemy_falling_state {
    const void* state_class;    /* Must be first */
};

/* ================================ */

static void EnemyFalling_handle(void* _entity) {

    struct entity* entity = _entity;
}

/* ================================ */

static void EnemyFalling_update(void* _entity) {

    struct entity* entity = _entity;
    struct enemy_falling_state* state = entity->state;

    SDL_Rect* env = Level_get_surroundings();
    SDL_Rect hitbox = (SDL_Rect) {.x = entity->position.x, .y = entity->position.y, .w = entity->width, .h = entity->height};

    Vector2D new_position;

    /* ================================ */

     /* Keep updating the entity's velocity.
    When you enter the `Falling` state, its vertical velocity becomes positive, and the player goes down */
    entity->velocity.y += gravity * Clock_getDelta(m_clock);

    new_position = Vector2D_add(&entity->position, &entity->velocity);
    hitbox.x = new_position.x;
    hitbox.y = new_position.y;

    entity->position = new_position;

    /* The entity has landed on the platform or something that can support it */
    if (Entity_isGrounded(entity)) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Resting, -1);
        entity->velocity.x = entity->velocity.y = 0;

        entity->position.y -= ((int) entity->position.y + entity->height) % TILE_SIZE;

        return ;
    }
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state_class _EnemyFalling = {

    .size = sizeof(struct enemy_falling_state),

    .ctor = NULL,
    .dtor = NULL,

    .handle = EnemyFalling_handle,
    .update = EnemyFalling_update,
    .draw = NULL,
};

const void* EnemyFalling = &_EnemyFalling;

/* ================================================================ */
