#ifndef _SPARK_WINDOW_INTERFACE_H
#define _SPARK_WINDOW_INTERFACE_H

#include <SDL2/SDL.h>

/* Forward Declaration */
typedef struct _window Window;

/**
 * Create a new instance of a `Window`. The `Window` contains information
 * about `SDL_Window` and `SDL_Renderer` serving as an aggregate.
 * 
 * @param title the title of the window, in UTF-8 encoding.
 * @param width the width of the window, in screen coordinates.
 * @param height the height of the window, in screen coordinates.
 * @param window_flags 0, or one or more `SDL_WindowFlags` OR'd together.
 * 
 * @return Returns the `Window` that was created or NULL on failure.
 */
Window* Window_new(const char* title, int width, int height, Uint32 window_flags, Uint32 renderer_flags);

/**
 * Destroy a window.
 * 
 * @param w the window to destroy (`&window`).
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int Window_destroy(Window** window);

/**
 * Retrieve the rendering context of a window.
 * 
 * @param window the window from which to retrieve the context.
 * 
 * @return (`SDL_Renderer*`) Returns the `SDL_Renderer` of the window or NULL on failure.
 */
SDL_Renderer* Window_get_context(const Window* window);

#endif /* _SPARK_WINDOW_INTERFACE_H */
