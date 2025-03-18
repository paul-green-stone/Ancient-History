#include "Level.h"

static void __draw(SDL_Renderer* r, SDL_Color* c, int x, int y) {

    SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);
    SDL_RenderFillRect(r, &(SDL_Rect) {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE});
}

/* ================================================================ */

void draw_grid(SDL_Renderer* r, SDL_Color* color) {

    SDL_Color oc;
    SDL_GetRenderDrawColor(r, &oc.r, &oc.g, &oc.b, &oc.a);

    SDL_SetRenderDrawColor(r, color->r, color->g, color->b, color->a);

    for (size_t i = 1; i < SCREEN_HEIGHT / TILE_SIZE; i++) {
        SDL_RenderDrawLine(r, 0, i * TILE_SIZE, SCREEN_WIDTH, i * TILE_SIZE);
    }

    for (size_t i = 1; i < SCREEN_WIDTH / TILE_SIZE; i++) {
        SDL_RenderDrawLine(r, i * TILE_SIZE, 0, i * TILE_SIZE, SCREEN_HEIGHT);
    }

    SDL_SetRenderDrawColor(r, oc.r, oc.g, oc.b, oc.a);
}

/* ================================ */

void Level_draw(SDL_Renderer* r, Level* level) {

    size_t width = SCREEN_WIDTH / TILE_SIZE;
    size_t height = SCREEN_HEIGHT / TILE_SIZE;

    for (size_t x = 0; x < height; x++) {

        for (size_t y = 0; y < width; y++) {

            if (level->level[x][y] > 0) {
                SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
                SDL_RenderFillRect(r, &(SDL_Rect) {y * TILE_SIZE, x * TILE_SIZE, TILE_SIZE, TILE_SIZE});
            }
        }
    }
}

/* ================================================================ */