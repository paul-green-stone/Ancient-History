#include <SDL2/SDL.h>
#include <constants.h>
#include <stdbool.h>

#include <texture.h>
#include <window.h>

#include <fps.h>
#include <level_manager.h>
#include <camera.h>

#ifdef __cplusplus
extern "C"
#endif
    int
    main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING); // Initialize all subsystems

    Window *window = Window_new("Ancient History", SCREEN_WIDTH, SCREEN_HEIGHT,
                                0, SDL_RENDERER_ACCELERATED);
    SDL_Renderer *context = Window_get_context(window);

    Camera *camera = createCamera(context, WIDTH, HEIGHT);

    /* Create the FPS clock */
    FPSClock clock = FPSClock_new(FPS);

    /**
     * Level loading
     */
    Level *level = loadLevel("./assets/level.png", TILE_SIZE);
    if (level == NULL)
    {
        printf("Could not load level!\n");
        return -1;
    }

    for (int h = 0; h < level->height; h++)
    {
        for (int w = 0; w < level->width; w++)
        {
            printf("%d ", level->map[w + h * level->width]);
        }
        printf("\n");
    }

    // Used to indicate if the game is still running
    bool isRunning = true;

    while (isRunning)
    {
        /* Event handing */
        SDL_PumpEvents();
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
                // Keyboard input handling
                switch (event.key.keysym.sym)
                {
                default:
                    break;
                }
            }
        }

        // EVENT HANDLING
        const Uint8 *keys_pressed = SDL_GetKeyboardState(NULL);
        if (keys_pressed[SDL_SCANCODE_LEFT]) {
            camera->pos[0]--;
        } else if (keys_pressed[SDL_SCANCODE_RIGHT]){
            camera->pos[0]++;
        }
        if (keys_pressed[SDL_SCANCODE_UP]) {
            camera->pos[1]--;
        } else if (keys_pressed[SDL_SCANCODE_DOWN]){
            camera->pos[1]++;
        }

        /* Rendering */
        /* Draw to the screen texture first */
        setRenderCamera(camera);
        SDL_SetRenderDrawColor(context, 255, 255, 255, 255);
        SDL_RenderClear(context);

        drawLevelToCamera(camera, level);

        clearRenderTarget(context);

        Texture_draw(&camera->texture.texture, NULL, NULL);
        SDL_RenderPresent(context);

        /* Clock system */
        FPSClock_tick(&clock);
    }

    unloadLevel(level);
    deleteCamera(camera);

    Window_destroy(&window);
    SDL_Quit();
    return 0;
}
