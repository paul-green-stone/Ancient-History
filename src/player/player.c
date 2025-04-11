#include <player/idle_state.h>
#include <player/player.h>
#include <stdlib.h>

/**
 * We can start by implementing the different states for the player.
 *
 * The first state can be the idle state. The other states can be as follows:
 *
 *  ┌────┐        ┌──────┐
 *  │idle│<──────>│moving│
 *  └────┘        └──────┘
 *   ∧ ∧             ∧  ∧
 *   │ └─────────────┼┐ │
 *   │ ┌─────────────┘│ │
 *   ∨ ∨              ∨ ∨
 *  ┌─────┐      ┌───────┐
 *  │jump │<────>│falling│
 *  └─────┘      └───────┘
 *
 * All state structs have their first field set to the `PlayerState` struct as a base,
 * this allows for a form of polymorphism and prevents rewritting a lot of the code for every new state.
 *
 */

Player *createPlayer(int width, int height, float pos_x, float pos_y) {
    Player *player = (Player *)malloc(sizeof(Player));
    if (player == NULL) {
        perror("ALLOC ERROR : Could not allocate memory for player :");
        return NULL;
    }

    // Let the initial state of the player be idle
    player->state = (PlayerState *)createIdleState();

	player->acceleration[0] = 0;
	player->acceleration[1] = GRAVITY;

	player->vel[0] = 0;
	player->vel[1] = TERMINAL_VEL;

	player->terminal_vel = TERMINAL_VEL;

	player->width = width;
	player->height = height;

	player->pos[0] = pos_x;
	player->pos[1] = pos_y;

    return player;
}

void handlePlayer(Player *player, Level *level) {
    PlayerState *state = ((PlayerState *)(player->state))->handleInput(player->state, player, level);
    if (state != NULL) {
        free(player->state);
        player->state = state;
    }
}

void updatePlayer(Player *player, Level *level) {
    player->state->update(player->state, player, level);
}

void drawPlayer(SDL_Renderer *context, Player *player) {
    // player->state->draw(context, player);
}

void destroyPlayer(Player *player) {
    free(player->state);
    free(player);
}