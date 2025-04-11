#ifndef PLAYER_IDLE_STATE_H
#define PLAYER_IDLE_STATE_H

#include <SDL2/SDL.h>
#include <player/player.h>
#include <stdlib.h>

/**
 * Used when the player is on the ground but not moving
 */
typedef struct IdleState {
    PlayerState base;
} IdleState;

// Handles input when in the idle state
PlayerState *idleStateHandleInput(PlayerState *self_state, Player *player, Level *level);

// Used to update the player
void idleStateUpdate(PlayerState *self_state, Player *player, Level *level);

// Called when entering the idle state
void idleStateEnter(PlayerState *self_state, Player *player);

IdleState *createIdleState();

#endif