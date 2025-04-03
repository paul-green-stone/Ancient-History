#ifndef _ANCIENT_HISTORY_LEVEL
#define _ANCIENT_HISTORY_LEVEL

#include <SDL2/SDL.h>

#include "constants.h"

#define TILE_SIZE 32
#define SCALED_TILE TILE_SIZE * SCALE

typedef enum {Top, TopRight, Right, BottomRight, Bottom, BottomLeft, Left, TopLeft} Corner;

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

/**
 * 
 */
void Level_debug(const Level* level);

/**
 * 
 */
SDL_Rect Level_getPlatform(const Level* level, int row, int column);

/**
 * 
 */
int is_point_inside(int x, int y, SDL_Rect* rect);

/**
 * 
 */
void Level_debug_surroundings(const void* entity);

/**
 * 
 */
void Level_update_surroundings(const void* entity);

/**
 * 
 */
SDL_Rect* Level_get_surroundings(void);

/* ================================================================ */

#endif /* _ANCIENT_HISTORY_LEVEL */
