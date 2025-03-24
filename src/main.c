#include <SDL2/SDL.h>
#include <constants.h>
#include <stdbool.h>

#include <texture.h>
#include <window.h>
#include <ppu.h>
#include <level_manager.h>

#include <fps.h>

#ifdef __cplusplus
extern "C"
#endif
    int
    main(int argc, char **argv)
{
    initPPU();

    SDL_Init(SDL_INIT_EVERYTHING); // Initialize all subsystems

    Window *window = Window_new("Ancient History", SCREEN_WIDTH, SCREEN_HEIGHT,
                                0, SDL_RENDERER_ACCELERATED);
    SDL_Renderer *context = Window_get_context(window);

    // TODO: Need to fix this
    // SDL_SetRenderDrawBlendMode(context, SDL_BLENDMODE_ADD);

    /* Create the NES screen canvas for drawing to */
    RenderTexture screen = RenderTexture_new(context, WIDTH, HEIGHT);

    /* Create the FPS clock */
    FPSClock clock = FPSClock_new(FPS);

    // Used to indicate if the game is still running
    bool isRunning = true;

    Level *level = createLevel();
    loadLevel(level, "./assets/level1.txt");
    loadBackgroundPatternTable("./assets/background pattern table.png");

    while (isRunning)
    {
        /* Event handing */
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT ||
                (event.type == SDL_KEYDOWN &&
                 event.key.keysym.sym == SDLK_ESCAPE))
            {
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    level->scroll -= 1;
                    if (level->scroll < 0) {
                        level->scroll = 0;
                    }
                    break;

                case SDLK_RIGHT:
                    level->scroll += 1;
                    if (level->scroll > 768) {
                        level->scroll = 768;
                    }
                    break;

                default:
                    break;
                }
            }
        }

        /* Rendering */
        /* Draw to the screen texture first */
        setRenderTarget(screen);

        copyLevelToNametable(level);
        drawNametables(context, level->scroll);

        clearRenderTarget(context);

        Texture_draw(&screen.texture, NULL, NULL);
        SDL_RenderPresent(context);

        /* Clock system */
        FPSClock_tick(&clock);
    }

    RenderTexture_destroy(screen);

    Window_destroy(&window);
    SDL_Quit();

    destroyLevel(level);
    return 0;
}
