#ifndef PLAYER_MOVING_STATE_H
#define PLAYER_MOVING_STATE_H

#include <player/player.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

/**
 * Used when the player is on the ground but not moving
 */
typedef struct MovingState {
    PlayerState base;
} MovingState;

// Handles input when in the idle state
PlayerState *movingStateHandleInput(PlayerState *self_state, Player *player, Level *level);

// Called when entering the idle state
void movingStateEnter(PlayerState *self_state, Player *player);

MovingState *createMovingState();

#endif