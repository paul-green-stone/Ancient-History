#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TILE_SIZE (8)
#define GRID_WIDTH (32)  // Number of horizontal tiles shown on screen
#define GRID_HEIGHT (28) // Number of vertical tiles shown on screen

#define WIDTH (GRID_WIDTH * TILE_SIZE)
#define HEIGHT (GRID_HEIGHT * TILE_SIZE)
#define SCALE (4) /* Scale factor for screen */

const int SCREEN_WIDTH = WIDTH * SCALE;
const int SCREEN_HEIGHT = HEIGHT * SCALE;

#define FPS (60) /* FPS of the game */

#endif
