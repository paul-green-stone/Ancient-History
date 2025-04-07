#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "../framework/include/clock.h"
#include "../framework/include/animation.h"
#include "../framework/include/texture.h"

#define WIDTH (256)  /* NES Width resolution */
#define HEIGHT (224) /* NES Height resolution */
#define SCALE (3)    /* Scale factor for screen */

// const int SCREEN_WIDTH = WIDTH * SCALE;
// const int SCREEN_HEIGHT = HEIGHT * SCALE;

#define SCREEN_WIDTH WIDTH * SCALE
#define SCREEN_HEIGHT HEIGHT * SCALE

#define FPS (60) /* FPS of the game */

extern Clock* m_clock;
extern double gravity;
extern Animation* run;
extern Animation* idle;
extern Animation* jump;

#endif
