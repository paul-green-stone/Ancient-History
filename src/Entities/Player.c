#include "../../include/Entities/Entity.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__player.h"
#include "../../include/Entities/entity.h"
#include "../../include/States/States.h"
#include "../../include/States/state.h"

#include "../../framework/include/io.h"

/* ================================================================ */

static void* Player_ctor(void* _self, va_list* app) {

    struct player* self = ((const struct entity_class*) Entity)->ctor(_self, app);
    struct entity* player_entity = _self;

    /* The Player is IDLEing Initially */
    player_entity->state = State_create(Falling);

    return self;
}

/* ================================ */

static void* Player_dtor(void* _self) {

    struct player* self = _self;

    return self;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct entity_class _Player = {
    .size = sizeof(struct player),
    .ctor = Player_ctor,
    .dtor = Player_dtor,
};

const void* Player = &_Player;

/* ================================================================ */
/* ======================== IMPLEMENTATION ======================== */
/* ================================================================ */

void Player_handle(void* player) {

    Vector2D* player_pos = Entity_get_position(player);
    struct entity* player_entity = (struct entity*) player;
    struct player* p = (struct player*) player;

    // if (Input_isKey_pressed(SDL_SCANCODE_UP)) {
    //     player_pos->y -= 1;
    // }

    // if (Input_isKey_pressed(SDL_SCANCODE_DOWN)) {
    //     player_pos->y += 1;
    // }

    // if (Input_isKey_pressed(SDL_SCANCODE_LEFT)) {
    //     player_pos->x -= 1;
    // }

    // if (Input_isKey_pressed(SDL_SCANCODE_RIGHT)) {
    //     player_pos->x += 1;
    // }

    // if (Input_isKey_just_pressed(SDL_SCANCODE_SPACE)) {

    //     // player_pos->y += velocity * delta_time;
    //     printf("I am supposed to jump whenever you hit the space bar\n");
    // }

    // switch (player_entity->state) {

    //     case IDLE:

    //         /* Update the clock */
    //         Clock_update(p->clock);
             
    //         handle_IDLE(player);
    //         break ;
    // }
}
