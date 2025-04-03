#include "../../include/States/__state_class.h"
#include "../../include/States/state.h"
#include "../../include/States/States.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/entity.h"
#include "../../include/Entities/Manager.h"

#include "../../framework/include/clock.h"
#include "../../framework/include/io.h"

#include "constants.h"

/* ================================================================ */

struct jumping_state {
    const void* state_class;    /* Must be first */

    /* Here might go variables that control the jump */
};

/* ================================ */

static void Jumping_handle(void* _entity) {

    struct entity* entity = _entity;

    Level* level = EntityManager_getLevel();

    SDL_Rect* env = Level_get_surroundings();
    SDL_Rect hitbox = (SDL_Rect) {.x = entity->position.x, .y = entity->position.y, .w = entity->width, .h = entity->height};

    // if (does_rect_collide(hitbox, env[Top]) || does_rect_collide(hitbox, env[TopRight])) {

    //     /* Exit the current state */
    //     State_destroy(entity->state);
    //     entity->state = NULL;

    //     /* Enter a new state */
    //     entity->state = State_create(Falling);

    //     /* The player just hit the platform and immediately stopped. */
    //     entity->velocity.y = 0;
    // }
}

/* ================================ */

static void Jumping_update(void* _entity) {

    struct entity* entity = _entity;
    struct jumping_state* state = entity->state;

    Level* level = EntityManager_getLevel();

    SDL_Rect* env = Level_get_surroundings();
    SDL_Rect hitbox = (SDL_Rect) {.x = entity->position.x, .y = entity->position.y, .w = entity->width, .h = entity->height};

    Vector2D new_position;

    float y_v;

    /* ================================ */

    /* After entering the `Jumping` state, the player's vertical velocity is negative, causing the player to move upward.
    The gravitation acting on it increments its velocity. DO NOT FORGET THAT POSITIVE Y GOES DOWNWARD! */
    entity->velocity.y += gravity * Clock_getDelta(m_clock);

    new_position = Vector2D_add(&entity->position, &entity->velocity);
    hitbox.x = new_position.x - 1;
    hitbox.y = new_position.y;

    if (does_rect_collide(hitbox, env[Top]) || does_rect_collide(hitbox, env[TopRight])) {

        entity->position.y -= entity->position.y - ((env[Top].w != 0) ? (env[Top].y + env[Top].h) : (env[TopRight].y + env[TopRight].h));

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Falling);

        /* The player just hit the platform and immediately stopped. */
        entity->velocity.y = 0;

        return ;
    }

    entity->position = new_position;

    /* ================ */

    /* Allow the player to move while Jumping */
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
        else {
            entity->position.x = (env[Left].w) ? env[Left].x + env[Left].w : env[BottomLeft].x + env[BottomLeft].w;
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
        else {
            entity->position.x = (env[Right].w) ? env[Right].x - entity->width : env[BottomRight].x - entity->width;
        }

        if (entity->position.x + entity->width >= SCREEN_WIDTH) {
            entity->position.x = SCREEN_WIDTH - entity->width;
        }

        entity->velocity.y = y_v;
    }

    /* ================ */

    /* When the vertical velocity becomes positive or zero, it means the player started to fall down */
    if (entity->velocity.y >= 0) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;

        /* Enter a new state */
        entity->state = State_create(Falling);
    }

    /* Prevent inertia */
    entity->velocity.x = 0;
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
    .draw = NULL,
};

const void* Jumping = &_Jumping;

/* ================================================================ */
