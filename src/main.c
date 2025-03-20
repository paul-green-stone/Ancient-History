#include <SDL2/SDL.h>
#include <constants.h>
#include <stdbool.h>

#include <texture.h>
#include <window.h>
#include <ppu.h>

#include <fps.h>

void drawNESTile(SDL_Renderer *r, NESPalette palette, NESTile tile, uint8_t x, uint8_t y)
{
    SDL_Color color1 = getColorFromPalette(palette.c1);
    SDL_Color color2 = getColorFromPalette(palette.c2);
    SDL_Color color3 = getColorFromPalette(palette.c3);

    SDL_Color colors[] = {
        (SDL_Color){0, 0, 0, 0}, color1, color2, color3};

    uint8_t pixel_count = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            uint8_t color = (tile.pixels[i] >> (6 - j * 2)) & 0b11;
            SDL_SetRenderDrawColor(r, colors[color].r, colors[color].g, colors[color].b, colors[color].a);
            SDL_RenderDrawPoint(r, x + pixel_count % 8, y + pixel_count / 8);
            pixel_count++;
        }
    }
}

#ifdef __cplusplus
extern "C"
#endif
    int
    main(int argc, char **argv)
{

    loadBackgroundPatternTable("./assets/background pattern table.png");

    NESPalette palette = {.c0 = 0x0E, .c1 = 0x37, .c2 = 0x27, .c3 = 0x17};

    SDL_Init(SDL_INIT_EVERYTHING); // Initialize all subsystems

    Window *window = Window_new("Ancient History", SCREEN_WIDTH, SCREEN_HEIGHT,
                                0, SDL_RENDERER_ACCELERATED);
    SDL_Renderer *context = Window_get_context(window);
    SDL_SetRenderDrawBlendMode(context, SDL_BLENDMODE_ADD);

    /* Create the NES screen canvas for drawing to */
    RenderTexture screen = RenderTexture_new(context, WIDTH, HEIGHT);

    /* Create the FPS clock */
    FPSClock clock = FPSClock_new(FPS);

    // Used to indicate if the game is still running
    bool isRunning = true;

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
        }

        /* Rendering */
        /* Draw to the screen texture first */
        setRenderTarget(screen);
        SDL_SetRenderDrawColor(context, 0, 0, 0, 255);
        SDL_RenderClear(context);

        drawNESTile(context, palette, _background_pattern_table[1], 0, 0);
        drawNESTile(context, palette, _background_pattern_table[3], 8, 0);
        drawNESTile(context, palette, _background_pattern_table[7], 0, 8);
        drawNESTile(context, palette, _background_pattern_table[9], 8, 8);

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
