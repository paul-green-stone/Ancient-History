#include <SDL2/SDL.h>
#include <constants.h>
#include <stdbool.h>

#include <texture.h>
#include <window.h>

#include <fps.h>

#ifdef __cplusplus
extern "C"
#endif
    int
    main(int argc, char **argv) {

    SDL_Init(SDL_INIT_EVERYTHING); // Initialize all subsystems
    Window *window = Window_new("Ancient History", SCREEN_WIDTH, SCREEN_HEIGHT,
                                0, SDL_RENDERER_ACCELERATED);
    SDL_Renderer *context = Window_get_context(window);

    /* Create the NES screen canvas for drawing to */
    RenderTexture screen = RenderTexture_new(context, WIDTH, HEIGHT);

    /* Create the FPS clock */
    FPSClock clock = FPSClock_new(FPS);

    // Used to indicate if the game is still running
    bool isRunning = true;

    while (isRunning) {
        /* Event handing */
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT ||
                (event.type == SDL_KEYDOWN &&
                 event.key.keysym.sym == SDLK_ESCAPE)) {
                isRunning = false;
            }
        }

        /* Rendering */
        /* Draw to the screen texture first */
        setRenderTarget(screen);
        SDL_SetRenderDrawColor(context, 255, 0, 0, 255);
        SDL_RenderClear(context);

        clearRenderTarget(context);

        Texture_draw(&screen.texture, NULL, NULL);
        SDL_RenderPresent(context);

        /* Clock system */
        FPSClock_tick(&clock);
    }

    RenderTexture_destroy(screen);

    Window_destroy(&window);
    SDL_Quit();
    return 0;
}
