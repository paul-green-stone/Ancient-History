#include "../../include/Entities/Entity.h"
#include "../../include/Entities/__entity.h"
#include "../../include/Entities/__entity_class.h"
#include "../../include/Entities/__player.h"
#include "../../include/Entities/entity.h"

#include "../../framework/include/io.h"

/* ================================================================ */

static void* Player_ctor(void* _self, va_list* app) {

    struct player* self = ((const struct entity_class*) Entity)->ctor(_self, app);

    return self;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct entity_class _Player = {
    .size = sizeof(struct player),
    .ctor = Player_ctor,
};

const void* Player = &_Player;

/* ================================================================ */
/* ======================== IMPLEMENTATION ======================== */
/* ================================================================ */

void Player_handle(void* player, float delta_time) {

    Vector2D* player_pos = Entity_get_position(player);

    if (Input_isKey_pressed(SDL_SCANCODE_UP)) {
        player_pos->y -= 1;
    }

    if (Input_isKey_pressed(SDL_SCANCODE_DOWN)) {
        player_pos->y += 1;
    }

    if (Input_isKey_pressed(SDL_SCANCODE_LEFT)) {
        player_pos->x -= 1;
    }

    if (Input_isKey_pressed(SDL_SCANCODE_RIGHT)) {
        player_pos->x += 1;
    }

    if (Input_isKey_just_pressed(SDL_SCANCODE_SPACE)) {

        // player_pos->y += velocity * delta_time;
        printf("I am supposed to jump whenever you hit the space bar\n");
    }
}
