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
#include "../framework/include/animation.h"

#include "Entities/Player.h"
#include "Entities/Manager.h"
#include "Level.h"

#include <fps.h>

#ifdef __cplusplus
extern "C"
#endif

Clock* m_clock = NULL;
double gravity = 9.8f;
Animation* run = NULL;
Texture* run_t = NULL;

int main(int argc, char **argv) {

    Level level = {
        .level = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        }
    };

    SDL_Init(SDL_INIT_EVERYTHING); // Initialize all subsystems
    Window *window = Window_new("Ancient History", SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_RENDERER_ACCELERATED);
    SDL_Renderer *context = Window_get_context(window);

    run_t = Texture_new(context, "Run.png");
    if (run_t) { printf("Success!\n"); }

    run = Animation_new(run_t, 0, 0, 6, 42, 42, X);
    Animation_setSpeed(run, 1.0 / 6);
    if (run) { printf("Success!\n"); }

    /* Create the FPS clock */
    FPSClock clock = FPSClock_new(FPS);

    // Used to indicate if the game is still running
    bool isRunning = true;

    //void* ent1 = Entity_create(Entity, &(Vector2D) {2.0, 3.0}, 25, 25, 1, NULL, &(SDL_Color) {0, 0, 0, 255}, 0.0);
    void* player = Entity_create(Player, &(Vector2D) {4.0, 16.0}, 16, 16, 1, NULL, &(SDL_Color) {255, 0, 0, 255}, 150.0);

    void* c = Entity_create(Collectible, &(Vector2D) {10.0, 11.0}, 10, 10, 0.0, 1, NULL, &(SDL_Color) {236, 184, 56, 255}, 0.0);
    void* c1 = Entity_create(Collectible, &(Vector2D) {6.0, 13.0}, 10, 10, 0.0, 1, NULL, &(SDL_Color) {236, 184, 56, 255}, 0.0);
    void* c2 = Entity_create(Collectible, &(Vector2D) {18.0, 9.0}, 10, 10, 0.0, 1, NULL, &(SDL_Color) {236, 184, 56, 255}, 0.0);
    void* c3 = Entity_create(Collectible, &(Vector2D) {3.0, 1.0}, 10, 10, 0.0, 1, NULL, &(SDL_Color) {236, 184, 56, 255}, 0.0);

    void* enemy = Entity_create(Enemy, &(Vector2D) {5.0, 5.0}, 20, 20, 1, NULL, &(SDL_Color) {0, 0, 255, 255}, 75.0, 3);
    void* enemy1 = Entity_create(Enemy, &(Vector2D) {3.0, 1.0}, 20, 20, 1, NULL, &(SDL_Color) {0, 0, 255, 255}, 75.0, 3);
    void* enemy2 = Entity_create(Enemy, &(Vector2D) {20.0, 1.0}, 20, 20, 1, NULL, &(SDL_Color) {0, 0, 255, 255}, 75.0, 3);

    m_clock = Clock_new();
    Clock_start(m_clock);

    EntityManager_setLevel(&level);

    while (isRunning) {

        /* Event handing */
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if ((event.type == SDL_QUIT) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))) {
                isRunning = false;
            }
        }

        Input_update();

        /* Rendering */
        /* Draw to the screen texture first */
        // setRenderTarget(screen);
        SDL_SetRenderDrawColor(context, 76, 182, 182, 255);
        SDL_RenderClear(context);

        Level_draw(context, &level);

        draw_grid(context, &(SDL_Color) {255, 255, 255, 255});

        //clearRenderTarget(context);

        //SDL_SetRenderDrawColor(context, 0, 0, 0, 255);

        EntityManager_process();
        
        //Entity_draw(player, context);
        EntityManager_draw(context);

        //Texture_draw(&screen.texture, NULL, NULL);
        SDL_RenderPresent(context);

        /* Clock system */
        FPSClock_tick(&clock);

        Clock_update(m_clock);
    }

    Animation_destroy(&run);
    Texture_destroy(&run_t);

    EntityManager_clear();

    Window_destroy(&window);
    Clock_destroy(&m_clock);

    SDL_Quit();

    return 0;
}
