#include <SDL2/SDL.h>
#include <constants.h>
#include <stdbool.h>

#include <texture.h>
#include <window.h>

#include <../include/Entities/entity.h>
#include <../include/Entities/Entity.h>
#include "../framework/include/Math/Vector2D.h"
#include "../framework/include/clock.h"
#include "../framework/include/io.h"

#include "Entities/Player.h"
#include "Entities/Manager.h"

#include <fps.h>

#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char **argv) {

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

    void* ent1 = Entity_create(Entity, (Vector2D) {50.0f, 50.0f}, 25, 25, 1, NULL, &(SDL_Color) {0, 0, 0, 255});
    void* player = Entity_create(Player, (Vector2D) {100.0f, 25.0f}, 50, 50, 1, NULL, &(SDL_Color) {0, 255, 0, 255});

    void* en1 = Entity_create(Enemy, (Vector2D) {175.0f, 30.0f}, 45, 45, 1, NULL, &(SDL_Color) {0, 0, 0, 255});
    void* c = Entity_create(Collectible, (Vector2D) {230.0f, 65.0f}, 10, 10, 1, NULL, &(SDL_Color) {0, 0, 255, 255});
    void* c1 = Entity_create(Collectible, (Vector2D) {300.0f, 160.0f}, 10, 10, 1, NULL, &(SDL_Color) {0, 0, 255, 255});
    void* c2 = Entity_create(Collectible, (Vector2D) {240.0f, 90.0f}, 10, 10, 1, NULL, &(SDL_Color) {0, 0, 255, 255});

    Clock* main_clock = Clock_new();
    Clock_start(main_clock);

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

        Input_update();

        Player_handle(player, Clock_getDelta(main_clock));

        // Vector2D* position = Entity_get_position(player);
        // position->y += 10 * Clock_getDelta(main_clock);

        /* Rendering */
        /* Draw to the screen texture first */
        // setRenderTarget(screen);
        SDL_SetRenderDrawColor(context, 255, 0, 0, 255);
        SDL_RenderClear(context);

        //clearRenderTarget(context);

        //SDL_SetRenderDrawColor(context, 0, 0, 0, 255);

        EntityManager_process();
        
        //Entity_draw(player, context);
        EntityManager_draw(context);

        //Texture_draw(&screen.texture, NULL, NULL);
        SDL_RenderPresent(context);

        /* Clock system */
        FPSClock_tick(&clock);
        Clock_update(main_clock);
    }

    //Entity_destroy(player);
    EntityManager_clear();

    //Entity_destroy(c);

    Clock_destroy(&main_clock);

    RenderTexture_destroy(screen);

    Window_destroy(&window);
    SDL_Quit();
    return 0;
}
