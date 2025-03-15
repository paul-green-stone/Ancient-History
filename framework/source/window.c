#include <SDL2/SDL.h>
#include "../include/window.h"

typedef struct _window {
    SDL_Window*   w;
    SDL_Renderer* r;    /* Rendering Context */
} Window;

Window* Window_new(const char* title, int width, int height, Uint32 window_flags, Uint32 renderer_flags) {

    Window* w = NULL;

    if ((w = calloc(1, sizeof(struct _window))) == NULL) {
        return NULL;
    }

    if ((w->w = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags)) == NULL) {
        free(w);

        return NULL;
    }

    if ((w->r = SDL_CreateRenderer(w->w, -1, renderer_flags)) == NULL) {
        SDL_DestroyWindow(w->w);
        free(w);

        return NULL;
    }

    return w;
}

/* ================================ */

int Window_destroy(Window** window) {
    
    if (!window || !(*window)) {
        return -1;
    }
    
    if ((*window)->r) { SDL_DestroyRenderer((*window)->r); }
    if ((*window)->w) { SDL_DestroyWindow((*window)->w); }

    free(*window);
    *window = NULL;

    return 0;
}

/* ================================ */

SDL_Renderer* Window_get_context(const Window* window) {

    if (window) {
        return window->r;
    }

    return NULL;
}
