#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/entity.h"
#include "../../include/Entities/Manager.h"

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
    struct falling_state* state = entity->state;

    Level* level = EntityManager_getLevel();

    SDL_Rect* env = Level_get_surroundings();
    SDL_Rect hitbox = (SDL_Rect) {.x = entity->position.x, .y = entity->position.y, .w = entity->width, .h = entity->height};

    Vector2D new_position;

    float y_v;

    /* Keep updating the entity's velocity.
    When you enter the `Falling` state, its vertical velocity becomes positive, and the player goes down */
    entity->velocity.y += gravity * Clock_getDelta(m_clock);

    new_position = Vector2D_add(&entity->position, &entity->velocity);
    hitbox.x = new_position.x;
    hitbox.y = new_position.y;

    entity->position = new_position;

    /* The player has landed on the platform or something that can support it */
    if (Entity_isGrounded(entity)) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Standing);
        entity->velocity.x = entity->velocity.y = 0;

        entity->position.y -= ((int) entity->position.y + entity->height) % TILE_SIZE;

        return ;
    }

    /* ================================ */

    if (Input_isKey_pressed(SDL_SCANCODE_LEFT)) {

        entity->velocity.x = -Clock_getDelta(m_clock) * entity->speed;
        y_v = entity->velocity.y;
        entity->velocity.y = 0;

        new_position = Vector2D_add(&new_position, &entity->velocity);
        hitbox.x = new_position.x;
        hitbox.y = new_position.y;

        if (!does_rect_collide(hitbox, env[Left]) && !does_rect_collide(hitbox, env[BottomLeft])) {
            entity->position = new_position;
        }

        if (entity->position.x <= 0) {
            entity->position.x = 0;
        }

        entity->velocity.y = y_v;
    }

    /* ================ */

    /* Allow the player to move while falling */
    if (Input_isKey_pressed(SDL_SCANCODE_RIGHT)) {

        entity->velocity.x = Clock_getDelta(m_clock) * entity->speed;
        y_v = entity->velocity.y;
        entity->velocity.y = 0;

        new_position = Vector2D_add(&new_position, &entity->velocity);
        hitbox.x = new_position.x;
        hitbox.y = new_position.y;

        if (!does_rect_collide(hitbox, env[Right]) && !does_rect_collide(hitbox, env[BottomRight])) {
            entity->position = new_position;
        }

        if (entity->position.x + entity->width >= SCREEN_WIDTH) {
            entity->position.x = SCREEN_WIDTH - entity->width;
        }

        entity->velocity.y = y_v;
    }

    /* Prevent inertia */
    entity->velocity.x = 0;
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
    .draw = NULL,
};

const void* Falling = &_Falling;

/* ================================================================ */
