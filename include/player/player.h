#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <level_manager.h>
#include <stdbool.h>

/**
 * I'm following the state machine pattern described here: https://gameprogrammingpatterns.com/state.html
 *
 * In this implementation, we have two structs, one is the `PlayerState` struct for holding the virtual functions
 * for the input handling and drawing functions of the player depending on their state, and the other is the
 * actual `Player` struct which houses the main player data, it looks something like this:
 *
 *  ┏━━━━━━━━━━━━━┓            ┏━━━━━━━━━━━━━━━━━━━━┓
 *  ┃PlayerState  ┃──────────┐ ┃JumpState           ┃
 *  ┃─────────────┃          │ ┃────────────────────┃
 *  ┃handleInput()┃────────┐ └─┃base                ┃
 *  ┃enter()      ┃───────┐│   ┃────────────────────┃
 *  ┗━━━━━━━━━━━━━┛       │└─┬─┃handleInput()       ┃
 *                        └──│─┃enter()             ┃
 *                           │ ┃────────────────────┃
 *                           │ ┃//other variables...┃
 *                           │ ┃chargeTime          ┃
 *                           │ ┗━━━━━━━━━━━━━━━━━━━━┛
 *  ┏━━━━━━━━━━━━━━━━━━┓     │
 *  ┃Player            ┃     │
 *  ┃──────────────────┃     │
 *  ┃handle()          ┃─────┘
 *  ┃//other functions ┃
 *  ┃──────────────────┃
 *  ┃// attributes     ┃
 *  ┃pos[2], vel[2],...┃
 *  ┗━━━━━━━━━━━━━━━━━━┛
 *
 * Each state of the player will be hidden withing the implementation file for the the player (player.c).
 *
 * For now all states will have a `handleInput` function which does two things:
 *   1. Handles the input to move or change player states,
 *   2. Handle collision detection between the player and level tiles, as well as other entities (e.g. enemies).
 */

#define GRAVITY (1)
#define TERMINAL_VEL (10)
#define VEL (1)

// Generic player state structure
typedef struct PlayerState PlayerState;

typedef enum PlayerStates {
    IDLE,
    MOVING,
    JUMPING,
    FALLING,
} PlayerStates;

/**
 * The player struct, contains all the other variables related to the player used by all states,
 * including position, speed, and size of the player.
 */
typedef struct player {
    int width;              // Width of the player in pixels
    int height;             // Height of the player in pixels
    float pos[2];           // Position of the player
    float vel[2];           // Velocity of the player
    float acceleration[2];  // Acceleration components of the velocity
    int terminal_vel;       // Maximum speed of player when falling/jumping
    PlayerState *state;     // Pointer to the current state virtual functions.
} Player;

// Generic player state structure
typedef struct PlayerState {
    /**
     * Virtual function used to initialize the state when transitioning into it.
     */
    void (*enter)(PlayerState *self_state, Player *player);

    /**
     * Virtual function for handling input.
     *
     * It can take in a pointer to itself if the state store any variables via `self_state`,
     * or `null` if it is a static state. It's best to just pass the state pointer every time and ignore it in
     * the implementation.
     *
     * We also need to pass the level data to handle collisions
     */
    PlayerState *(*handleInput)(PlayerState *self_state, Player *player, Level *level);

    /**
     * Virtual function for updating the player.
     *
     * @note This should be called before `handleInput` in the game loop.
     */
    void (*update)(PlayerState *self_state, Player *player, Level *level);
} PlayerState;

/**
 * Create a new player.
 *
 * @param width The player's width
 * @param height The player's height
 * @param pos_x The player's tile position
 * @param pos_y The player's tile position
 */
Player *createPlayer(int width, int height, float pos_x, float pos_y);

/**
 * Used for handling input for the player
 */
void handlePlayer(Player *player, Level *level);

/**
 * Update the player (e.g. the animation frame, or position depending on the state)
 */
void updatePlayer(Player *player, Level *level);

/**
 * Draw the player to the screen.
 */
void drawPlayer(SDL_Renderer *context, Player *player);

/**
 * Destroy the player
 */
void destroyPlayer(Player *player);

#endif