#include <SDL2/SDL.h>
#include <fps.h>

FPSClock FPSClock_new(unsigned int fps) {
    return (FPSClock){
        .last_frame = SDL_GetPerformanceCounter(),
        .fps = fps,
        .current_fps = 0,
    };
}

void FPSClock_tick(FPSClock *clock) {
    Uint64 end = SDL_GetPerformanceCounter();
    float elapsed_time = ((float)(end - clock->last_frame) /
                          (float)SDL_GetPerformanceFrequency()) *
                         1000.0f;

    clock->current_fps = 1000.0f / elapsed_time;

    float delay = floor(((1.0f / (float)clock->fps) * 1000.0f) - elapsed_time);
    if (delay > 0)
        SDL_Delay(delay);

    end = SDL_GetPerformanceCounter();
    elapsed_time = ((float)(end - clock->last_frame) /
                    (float)SDL_GetPerformanceFrequency()) *
                   1000.0f;
    clock->current_fps = 1000.0f / elapsed_time;

    clock->last_frame = SDL_GetPerformanceCounter();
}

float FPSClock_getFPS(FPSClock clock) { return clock.current_fps; }
