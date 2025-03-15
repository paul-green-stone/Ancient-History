#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "../include/clock.h"

typedef struct clock {

    double timer;
    double accumulator;
    double modifier;
    double delta;

    Clock_State state;

    Uint64 previous_ticks;
    Uint64 current_ticks;
} Clock;

/* ================================================================ */

Clock* Clock_new(void) {

    Clock* clock = NULL;

    if ((clock = calloc(1, sizeof(Clock))) == NULL) {
        return NULL;
    }

    clock->modifier = 1.0f;
    clock->state = STOPPED;
    clock->accumulator = 0.0f;

    return clock;
}

/* ================================ */

int Clock_destroy(Clock** clock) {

    if ((clock == NULL) || (*clock == NULL)) {
        return 1;
    }

    free(*clock);
    *clock = NULL;

    return 0;
}

/* ================================ */

void Clock_start(Clock* clock) {

    clock->state = STARTED;
    clock->previous_ticks = SDL_GetPerformanceCounter();
}

/* ================================ */

void Clock_stop(Clock* clock) {

    clock->state = STOPPED;
}

/* ================================ */

void Clock_update(Clock* clock) {

    double delta;

    if (clock->state == STOPPED) {
        return ;
    }

    clock->current_ticks = SDL_GetPerformanceCounter();

    delta = (clock->current_ticks - clock->previous_ticks) / (float) SDL_GetPerformanceFrequency();
    
    clock->previous_ticks = clock->current_ticks;
    clock->delta = delta * clock->modifier;

    clock->accumulator += clock->delta;
}

/* ================================ */

int Clock_setSpeed(Clock* clock, double speed) {

    if (speed <= 0) {
        return 2;
    }

    clock->modifier = speed;

    return 0;
}

/* ================================ */

int Clock_isReady(const Clock* clock) {

    return clock->accumulator >= clock->timer;
}

/* ================================ */

void Clock_reset(Clock* clock) {

    clock->accumulator = 0;
}

/* ================================ */

void Clock_setTimer(Clock* clock, double seconds) {

    clock->timer = fabs(seconds);
}

/* ================================ */

double Clock_getDelta(const Clock* clock) {

    return clock->delta;
}
