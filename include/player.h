#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct player
{
    int width;          // Width of the player in pixels
    int height;         // Height of the player in pixels
    int pos[2];         // Position of the player
    int vel[2];         // Velocity of the player
    bool is_jumping;    // Used to indicate if the player is jumping/mid-air or not
    int gravity;        // Gravitational force/firction applied to player
    int terminal_vel;   // Maximum speed of player when falling/jumping
    int air_resistance; // Air resistance/decay of Y velocity
} Player;

/**
 * Create a new player.
 *
 * @param width The player's width
 * @param height The player's height
 * @param pos_x The player's tile position
 * @param pos_y The player's tile position
 * @param gravity Gravitational acceleration
 * @param terminal_vel Max speed of player when falling
 */
Player *createPlayer(int width, int height, int pos_x, int pos_y, int gravity, int terminal_vel);

/**
 * Draw the player to the screen.
 */
void drawPlayer(SDL_Renderer *context);

/**
 * Destroy the player
 */
void destroyPlayer(Player *player);

#endif