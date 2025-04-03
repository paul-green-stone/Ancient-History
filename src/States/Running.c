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
#include "../../framework/include/animation.h"

extern Clock* m_clock;

/* ================================================================ */

struct running_state {

    const void* state_class;    /* Must be first */

    Animation* animation;
};

/* ================================ */

static void* Running_ctor(void* _self, va_list* app) {

    struct running_state* self = _self;

    self->animation = run;
    
    printf("Animation is %d\n", self->animation != NULL);

    return self;
}

/* ================================ */

static void Running_handle(void* _entity) {

    struct entity* entity = _entity;

    /* Going to enter the `Standing` state */
    if (!Input_isKey_pressed(SDL_SCANCODE_LEFT) && (!Input_isKey_pressed(SDL_SCANCODE_RIGHT))) {

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

    /* ================ */

    /* The player is falling off the platform */
    if (!Entity_isGrounded(entity)) {

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;
 
        /* Enter a new state */
        entity->state = State_create(Falling);
    }
}

/* ================================ */

static void Running_update(void* _entity) {

    struct entity* entity = _entity;
    struct running_state* state = entity->state;

    SDL_Rect* env = Level_get_surroundings();
    SDL_Rect hitbox = (SDL_Rect) {.x = entity->position.x, .y = entity->position.y, .w = entity->width, .h = entity->height};

    Vector2D new_position;
    
    /* Increase the player's speed while running */
    if (Input_isKey_pressed(SDL_SCANCODE_LEFT)) {

        entity->velocity.x = -Clock_getDelta(m_clock) * entity->speed;
        new_position = Vector2D_add(&entity->position, &entity->velocity);

        hitbox.x = new_position.x;
        hitbox.y = new_position.y;

        if (!does_rect_collide(hitbox, env[Left])) {
            entity->position = new_position;
        }
        else {
            entity->position.x = env[Left].x + env[Left].w;
        }

        if (entity->position.x <= 0) {
            entity->position.x = 0;
        }
    }

    /* ================ */

    /* Increase the player's speed while running */
    if (Input_isKey_pressed(SDL_SCANCODE_RIGHT)) {

        entity->velocity.x = Clock_getDelta(m_clock) * entity->speed;
        new_position = Vector2D_add(&entity->position, &entity->velocity);

        hitbox.x = new_position.x;
        hitbox.y = new_position.y;

        if (!does_rect_collide(hitbox, env[Right])) {
            entity->position = new_position;
        }
        else {
            entity->position.x = env[Right].x - entity->width;
        }

        if (entity->position.x + entity->width >= SCREEN_WIDTH) {
            entity->position.x = SCREEN_WIDTH - entity->width;
        }
    }

    Animation_update(state->animation, Clock_getDelta(m_clock));
       
    entity->velocity.x = entity->velocity.y = 0;
}

/* ================================ */

static void Running_draw(void* _entity) {

    struct entity* entity = _entity;
    struct running_state* state = entity->state;

    Texture_draw(state->animation->texture, &state->animation->frame, &(SDL_Rect) {.x = entity->position.x, .y = entity->position.y - 16, .w = entity->width * 2, .h = entity->height * 2});
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state_class _Running = {

    .size = sizeof(struct running_state),

    .ctor = Running_ctor,
    .dtor = NULL,

    .handle = Running_handle,
    .update = Running_update,
    .draw = Running_draw,
};

const void* Running = &_Running;

/* ================================================================ */
