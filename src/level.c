#include "Level.h"
#include "../include/Entities/__entity.h"
#include "../include/Entities/Manager.h"

static SDL_Rect surroundings[8];

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

/* ================================ */

void Level_debug(const Level* level) {

    size_t width = SCREEN_WIDTH / TILE_SIZE;
    size_t height = SCREEN_HEIGHT / TILE_SIZE;

    for (size_t x = 0; x < height; x++) {

        for (size_t y = 0; y < width; y++) {

            if (level->level[x][y] > 0) {
                printf("Platform at: [%d; %d]\n", y, x);
            }
        }
    }
}

/* ================================ */

SDL_Rect Level_getPlatform(const Level* level, int row, int column) {
    return (SDL_Rect) {.x = row * TILE_SIZE, .y = column * TILE_SIZE, TILE_SIZE, TILE_SIZE};
}

/* ================================ */

int is_point_inside(int x, int y, SDL_Rect* rect) {

    if (rect == NULL) {
        return 0;
    }

    return (x >= rect->x && x <= (rect->x + rect->w) && y >= rect->y && y <= (rect->y + rect->h));
}

/* ================================ */

SDL_Rect* Level_get_surroundings(void) {
    return surroundings;
}

/* ================================ */

void Level_update_surroundings(const void* _entity) {

    const struct entity* entity = _entity;
    Level* level = EntityManager_getLevel();

    int row, column;

    if (entity == NULL) {
        return ;
    }

    row = get_row(entity) - 1;
    column = get_column(entity) - 1;

    if (level->level[row][column]) {
        surroundings[TopLeft] = (SDL_Rect) {.x = column * TILE_SIZE, .y = row * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
    }
    else {
        surroundings[TopLeft] = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};
    }

    /* ======== */

    row = get_row(entity) - 1;
    column = get_column(entity);

    if (level->level[row][column]) {
        surroundings[Top] = (SDL_Rect) {.x = column * TILE_SIZE, .y = row * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
    }
    else {
        surroundings[Top] = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};
    }

    /* ======== */

    row = get_row(entity) - 1;
    column = get_column(entity) + 1;

    if (level->level[row][column]) {
        surroundings[TopRight] = (SDL_Rect) {.x = column * TILE_SIZE, .y = row * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
    }
    else {
        surroundings[TopRight] = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};
    }

    /* ======== */

    row = get_row(entity);
    column = get_column(entity) + 1;

    if (level->level[row][column]) {
        surroundings[Right] = (SDL_Rect) {.x = column * TILE_SIZE, .y = row * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
    }
    else {
        surroundings[Right] = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};
    }
    
    /* ======== */

    row = get_row(entity) + 1;
    column = get_column(entity) + 1;

    if (level->level[row][column]) {
        surroundings[BottomRight] = (SDL_Rect) {.x = column * TILE_SIZE, .y = row * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
    }
    else {
        surroundings[BottomRight] = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};
    }

    /* ======== */

    row = get_row(entity) + 1;
    column = get_column(entity);

    if (level->level[row][column]) {
        surroundings[Bottom] = (SDL_Rect) {.x = column * TILE_SIZE, .y = row * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
    }
    else {
        surroundings[Bottom] = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};
    }

    /* ======== */

    row = get_row(entity) + 1;
    column = get_column(entity) - 1;

    if (level->level[row][column]) {
        surroundings[BottomLeft] = (SDL_Rect) {.x = column * TILE_SIZE, .y = row * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
    }
    else {
        surroundings[BottomLeft] = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};
    }

    /* ======== */
    
    row = get_row(entity);
    column = get_column(entity) - 1;

    if (level->level[row][column]) {
        surroundings[Left] = (SDL_Rect) {.x = column * TILE_SIZE, .y = row * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
    }
    else {
        surroundings[Left] = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};
    }
}

/* ================================================================ */

double get_length(int x1, int y1, int x2, int y2) {
    return sqrt((max(x1, x2) - min(x1, x2)) * (max(x1, x2) - min(x1, x2)) + (max(y1, y2) - min(y1, y2)) * (max(y1, y2) - min(y1, y2)));
}

/* ================================================================ */

int Level_isThere_obstacle(const void* _entity, double range) {

    const struct entity* entity = _entity;
    const struct entity* player = EntityManager_getPlayer();
    Level* level = EntityManager_getLevel();

    /* Number of columns the entity's range covers */
    int columns = range / TILE_SIZE;
    /* The entity's origin column */
    int entity_start_column = get_column(entity);
    int row = get_row(entity);

    int player_column = get_column(player);
    int direction;

    /* Determine which direction to check */
    direction = (entity_start_column < player_column) ? 1 : -1;

    for (int column = entity_start_column; ((direction > 0) ? column <= entity_start_column + columns : column >= entity_start_column + columns); column += direction) {

        if (column == player_column) {
            return 0;
        }

        if ((level->level[row][column] > 0) || (level->level[row + 1][column]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

/* ================================================================ */