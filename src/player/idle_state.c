#include <player/idle_state.h>
#include <player/moving_state.h>
#include <stdbool.h>
#include <utils.h>

PlayerState *idleStateHandleInput(PlayerState *self_state, Player *player, Level *level) {
    /**
     * When the player is idle, the following things can happen that we need to check:
     *   1. Is there a tile bellow the player? If not, the player transitions into the falling state,
     *   2. Has the player pressed any keys? If so, transition to the correct state.
     */

    PlayerStates next_state = IDLE;

    // First check the keyboard input and set the velocities of the player
    const Uint8 *keys_pressed = SDL_GetKeyboardState(NULL);
    if (keys_pressed[SDL_SCANCODE_LEFT]) {
        player->vel[0] = -VEL;
        next_state = MOVING;
    } else if (keys_pressed[SDL_SCANCODE_RIGHT]) {
        player->vel[0] = VEL;
        next_state = MOVING;
    }

    // Next check for any collision detection on the X-axis
    // Equivilent to checking the surrounding tiles
    player->pos[0] += player->vel[0];
    SDL_Rect player_rect = createSDLRect(player->pos[0], player->pos[1], player->width, player->height);
    for (int h = player_rect.y % level->tile_size; h < (player_rect.y + player_rect.h) % level->tile_size + 1; h++) {
        if (h < 0 || h >= level->height) {
            continue;
        }
        for (int w = player_rect.x % level->tile_size; w < (player_rect.x + player_rect.w) % level->tile_size + 1; w++) {
            if (w < 0 || w >= level->width || level->map[w + h * level->width] == 0) {
                continue;
            }
            SDL_Rect tile_rect = createSDLRect(w * level->tile_size, h * level->tile_size, level->tile_size, level->tile_size);
            if (checkCollisionRect(player_rect, tile_rect)) {
                if (player->vel[0] > 0) {  // Check if the player is moving to the right
                    player->pos[0] = tile_rect.x - player->width;
                } else {
                    player->pos[0] = tile_rect.x + tile_rect.w;
                }
            }
        }
    }

    // Now handle collisions on the Y-axis
    player->pos[1] += player->vel[1];
    player_rect = createSDLRect(player->pos[0], player->pos[1], player->width, player->height);
    bool hit_floor = false;  // Used to check if the player hit the floor or not
    for (int h = player_rect.y % level->tile_size; h < (player_rect.y + player_rect.h) % level->tile_size + 1; h++) {
        if (h < 0 || h >= level->height) {
            continue;
        }
        for (int w = player_rect.x % level->tile_size; w < (player_rect.x + player_rect.w) % level->tile_size + 1; w++) {
            if (w < 0 || w >= level->width || level->map[w + h * level->width] == 0) {
                continue;
            }
            SDL_Rect tile_rect = createSDLRect(w * level->tile_size, h * level->tile_size, level->tile_size, level->tile_size);
            if (checkCollisionRect(player_rect, tile_rect)) {
                if (player->vel[1] > 0) {  // Check if the player is moving to the down and hit the floor
                    player->pos[1] = tile_rect.y - player->height;
                    hit_floor = true;
                } else {  // Check if the player hit their head on a tile, and set their state to falling
                    player->pos[1] = tile_rect.y + tile_rect.w;
                    next_state = FALLING;
                }
            }
        }
    }

    if (!hit_floor) {  // If the player didn't hit the floor, it must mean that the player is falling.
        next_state = FALLING;
    }

    PlayerState *next_state_ptr = NULL;
    switch (next_state) {
        case IDLE:
            next_state_ptr = NULL;
            break;
        case MOVING:
            next_state_ptr = (PlayerState *)createMovingState();
            break;
        case FALLING:
            printf("Falling state not implemented yet!");
            next_state_ptr = NULL;
            break;
        default:
            next_state_ptr = NULL;
            break;
    }

    return next_state_ptr;
}

void idleStateUpdate(PlayerState *self_state, Player *player, Level *level) {
    // We can apply the acceleration to the player over here to adjust the velocity
    player->vel[0] += player->acceleration[0];
    player->vel[1] += player->acceleration[1];
    if (player->vel[1] > player->terminal_vel) {
        player->vel[1] = player->terminal_vel;
    }
}

void idleStateEnter(PlayerState *self_state, Player *player) {
    player->vel[0] = 0;
    player->vel[1] = 0;
    player->acceleration[0] = 0;
    player->acceleration[1] = GRAVITY;
    player->terminal_vel = TERMINAL_VEL;
    printf("Player state: IDLE\n");
}

IdleState *createIdleState() {
    IdleState *state = (IdleState *)malloc(sizeof(IdleState));
    state->base.handleInput = idleStateHandleInput;
    state->base.enter = idleStateEnter;
    state->base.update = idleStateUpdate;

    return state;
}