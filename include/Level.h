#ifndef _ANCIENT_HISTORY_LEVEL
#define _ANCIENT_HISTORY_LEVEL

#include <SDL2/SDL.h>

#include "constants.h"

#define TILE_SIZE 32
#define SCALED_TILE TILE_SIZE * SCALE

/* ================================================================ */

typedef struct level {
    char level[SCREEN_HEIGHT / TILE_SIZE][SCREEN_WIDTH / TILE_SIZE];
} Level;

/* ================================ */

/**
 * 
 */
void draw_grid(SDL_Renderer* r, SDL_Color* color);

/**
 * 
 */
void Level_draw(SDL_Renderer* r, Level* level);

/* ================================================================ */

#endif /* _ANCIENT_HISTORY_LEVEL */
