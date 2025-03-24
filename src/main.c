#include <SDL2/SDL.h>
#include <constants.h>
#include <stdbool.h>

#include <texture.h>
#include <window.h>
#include <ppu.h>

#include <../include/Entities/entity.h>
#include <../include/Entities/Entity.h>
#include "../framework/include/Math/Vector2D.h"
#include "../framework/include/clock.h"
#include "../framework/include/io.h"

#include "Entities/Player.h"
#include "Entities/Manager.h"
#include "Level.h"

#include <fps.h>

// void drawBackgroundTile(SDL_Renderer *r, NESPalette palette, NESSprite tile, uint8_t x, uint8_t y)
// {
//     SDL_Color color1 = {.r = PALETTE[palette.c1] >> 16,
//                         .g = (PALETTE[palette.c1] >> 8) & 0xFF,
//                         .b = PALETTE[palette.c1] & 0xFF,
//                         .a = 255};
//     SDL_Color color2 = {.r = PALETTE[palette.c2] >> 16,
//                         .g = (PALETTE[palette.c2] >> 8) & 0xFF,
//                         .b = PALETTE[palette.c2] & 0xFF,
//                         .a = 255};
//     SDL_Color color3 = {.r = PALETTE[palette.c3] >> 16,
//                         .g = (PALETTE[palette.c3] >> 8) & 0xFF,
//                         .b = PALETTE[palette.c3] & 0xFF,
//                         .a = 255};
//     SDL_Color colors[] = {
//         (SDL_Color){0, 0, 0, 0}, color1, color2, color3};

//     uint8_t pixel_count = 0;
//     for (uint8_t i = 0; i < 16; i++)
//     {
//         for (uint8_t j = 0; j < 4; j++)
//         {
//             uint8_t color = (tile.pixels[i] >> (6 - j * 2)) & 0b11;
//             SDL_SetRenderDrawColor(r, colors[color].r, colors[color].g, colors[color].b, colors[color].a);
//             SDL_RenderDrawPoint(r, x + pixel_count % 8, y + pixel_count / 8);
//             pixel_count++;
//         }
//     }
// }

#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char **argv)
{

    // NESSprite tile = {
    //     .pixels = {
    //         0b00001010,
    //         0b10100000,
    //         0b00101010,
    //         0b10100000,
    //         0b00000101,
    //         0b01010000,
    //         0b00000111,
    //         0b01110000,
    //         0}};

    // NESPalette palette = {.c0 = 0x0E, .c1 = 0x20, .c2 = 0x21, .c3 = 0x22};

    Level level = {
        .level = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        }
    };

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

    void* ent1 = Entity_create(Entity, (Vector2D) {2.0, 3.0}, 25, 25, 1, NULL, &(SDL_Color) {0, 0, 0, 255});
    void* player = Entity_create(Player, (Vector2D) {4.0, 16.0}, 32, 32, 1, NULL, &(SDL_Color) {0, 255, 0, 255});

    void* en1 = Entity_create(Enemy, (Vector2D) {6.0, 7.0}, 45, 45, 1, NULL, &(SDL_Color) {0, 0, 0, 255});
    void* c = Entity_create(Collectible, (Vector2D) {10.0, 11.0}, 10, 10, 1, NULL, &(SDL_Color) {0, 0, 255, 255});
    void* c1 = Entity_create(Collectible, (Vector2D) {6.0, 13.0}, 10, 10, 1, NULL, &(SDL_Color) {0, 0, 255, 255});
    void* c2 = Entity_create(Collectible, (Vector2D) {18.0, 9.0}, 10, 10, 1, NULL, &(SDL_Color) {0, 0, 255, 255});

    while (isRunning) {
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

        Input_update();

        Player_handle(player);

        /* Rendering */
        /* Draw to the screen texture first */
        // setRenderTarget(screen);
        SDL_SetRenderDrawColor(context, 255, 0, 0, 255);
        SDL_RenderClear(context);

        Level_draw(context, &level);

        draw_grid(context, &(SDL_Color) {0, 255, 0, 255});

        //clearRenderTarget(context);

        //SDL_SetRenderDrawColor(context, 0, 0, 0, 255);

        EntityManager_process();
        
        //Entity_draw(player, context);
        EntityManager_draw(context);

        //Texture_draw(&screen.texture, NULL, NULL);
        SDL_RenderPresent(context);

        /* Clock system */
        FPSClock_tick(&clock);
    }

    //Entity_destroy(player);
    EntityManager_clear();

    //Entity_destroy(c);

    RenderTexture_destroy(screen);

    Window_destroy(&window);
    SDL_Quit();
    return 0;
}
