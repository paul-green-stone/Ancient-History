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

struct patrolling_state {

    const void* state_class;    /* Must be first */

    /* Row of Resting */
    unsigned char main_row_cell;
    /* Column of Resting */
    unsigned char main_column_cell;

    /* How far the entity travels in terms of tiles in a single direction */
    unsigned char patrolling_distance;
    double distance_travelled;

    char direction;
};

/* ================================ */

static void* Patrolling_ctor(void* _self, va_list* app) {

    struct patrolling_state* self = _self;

    self->main_column_cell = va_arg(*app, int);
    self->main_row_cell = va_arg(*app, int);

    self->patrolling_distance = va_arg(*app, int);

    self->direction = va_arg(*app, int);

    return self;
}

/* ================================ */

static void Patrolling_handle(void* _entity) {

    struct entity* entity = _entity;
    struct patrolling_state* state = entity->state;

    SDL_Rect* env = Level_get_surroundings();    
}

/* ================================ */

static void Patrolling_update(void* _entity) {

    struct entity* entity = _entity;
    struct enemy* enemy_entity = _entity;
    struct entity* player = EntityManager_getPlayer();
    struct patrolling_state* state = entity->state;

    SDL_Rect* env = Level_get_surroundings();
    SDL_Rect hitbox = (SDL_Rect) {.x = entity->position.x, .y = entity->position.y, .w = entity->width, .h = entity->height};

    char old_direction;
    int row, column;

    double speed;

    /* ================================ */

    entity->velocity.x = Clock_getDelta(m_clock) * entity->speed * state->direction;
    entity->position = Vector2D_add(&entity->position, &entity->velocity);

    /* Keep updating how much distance the entity has traveled */
    state->distance_travelled += Clock_getDelta(m_clock) * entity->speed * state->direction;

    /* ================================================================ */
    /* ====================== Going To The Right ====================== */
    /* ================================================================ */

    hitbox.x += 5;

    /* If there is an obstacle to the right */
    if (does_rect_collide(hitbox, env[Right]) && state->direction > 0) {

        old_direction = state->direction;

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;
 
        /* Enter a new state */
        entity->state = State_create(Resting, -old_direction, 0.5f);

        return ;
    }

    /* If there is no floor ro the right */
    if (env[BottomRight].w == 0 && state->direction > 0) {

        old_direction = state->direction;

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;
 
        /* Enter a new state */
        entity->state = State_create(Resting, -old_direction, 1.5f);

        return ;
    }

    /* ================================================================ */
    /* ======================= Going To The Left ====================== */
    /* ================================================================ */

    hitbox.x -= 10;

    /* If there is an obstacle to the left */
    if (does_rect_collide(hitbox, env[Left]) && state->direction < 0) {

        old_direction = state->direction;

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;
 
        /* Enter a new state */
        entity->state = State_create(Resting, -old_direction, 0.5f);

        return ;
    }

    /* If there is no floor ro the left */
    if (env[BottomLeft].w == 0 && state->direction < 0) {

        old_direction = state->direction;

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;
 
        /* Enter a new state */
        entity->state = State_create(Resting, -old_direction, 1.5f);

        return ;
    }

    /* ======== */

    if ((((int) fabs(state->distance_travelled)) / TILE_SIZE) == state->patrolling_distance) {

        old_direction = state->direction;

        /* Exit the current state */
        State_destroy(entity->state);
        entity->state = NULL;
 
        /* Enter a new state */
        entity->state = State_create(Resting, old_direction, 1.5f);

        return ;
    }
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state_class _Patrolling = {

    .size = sizeof(struct patrolling_state),

    .ctor = Patrolling_ctor,
    .dtor = NULL,

    .handle = Patrolling_handle,
    .update = Patrolling_update,
    .draw= NULL,
};

const void* Patrolling = &_Patrolling;


/* ================================================================ */
