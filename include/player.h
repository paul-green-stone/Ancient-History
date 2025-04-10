#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

/**
 * I'm following the state machine pattern described here: https://gameprogrammingpatterns.com/state.html
 *
 * In this implementation, we have two structs, one is the `PlayerState` struct for holding the virtual functions
 * for the input handling and drawing functions of the player depending on their state, and the other is the
 * actual `Player` struct which houses the main player data.
 *
 * Each state of the player will be hidden withing the implementation file for the the player (player.c).
 */

// Generic player state structure
typedef struct PlayerState {
    /**
     * Virtual function for handling input.
     *
     * It can take in a pointer to itself if the state store any variables via `self_state`,
     * or `null` if it is a static state. It's best to just pass the state pointer every time and ignore it in
     * the implementation.
     */
    PlayerState *(*handleInput)(void *self_state, Player *);
    /**
     * Virtual function for drawing the player.
     */
    void (*draw)(SDL_Renderer *, Player *);
} PlayerState;

/**
 * The player struct, contains all the other variables related to the player used by all states,
 * including position, speed, and size of the player.
 */
typedef struct player {
    int width;            // Width of the player in pixels
    int height;           // Height of the player in pixels
    int pos[2];           // Position of the player
    int vel[2];           // Velocity of the player
    int acceleration[2];  // Acceleration components of the velocity
    int terminal_vel;     // Maximum speed of player when falling/jumping
    PlayerState *state;   // Pointer to the current state virtual functions.
} Player;

/**
 * Create a new player.
 *
 * @param width The player's width
 * @param height The player's height
 * @param pos_x The player's tile position
 * @param pos_y The player's tile position
 */
Player *createPlayer(int width, int height, int pos_x, int pos_y);

/**
 * Draw the player to the screen.
 */
void drawPlayer(SDL_Renderer *context);

/**
 * Destroy the player
 */
void destroyPlayer(Player *player);

#endif