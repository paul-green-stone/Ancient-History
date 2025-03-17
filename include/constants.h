#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WIDTH (256)  /* NES Width resolution */
#define HEIGHT (224) /* NES Height resolution */
#define SCALE (3)    /* Scale factor for screen */

const int SCREEN_WIDTH = WIDTH * SCALE;
const int SCREEN_HEIGHT = HEIGHT * SCALE;

#define FPS (60) /* FPS of the game */

#endif
