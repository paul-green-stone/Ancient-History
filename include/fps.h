/**
 * FPS limitter code
 */
#ifndef FPS_H
#define FPS_H

#include <stdint.h>
#include <SDL2/SDL.h>

typedef struct FPSClock {
    Uint64 last_frame;
    unsigned int fps;
    float current_fps;
} FPSClock;

/**
 * Set the targetted FPS.
 */
FPSClock FPSClock_new(unsigned int fps);

/**
 * Make the clock tick.
 *
 * @param clock Pointer to the FPSClock
 */
void FPSClock_tick(FPSClock *clock);

/**
 * Gets the current FPS of the game.
 */
float FPSClock_getFPS(FPSClock clock);

#endif
