/**
 * Header containing simple utility functions
 */

#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// Creates an SDL_Rect from position and size.
SDL_Rect createSDLRect(int x, int y, int w, int h);

// Check if two SDL_Rects are colliding
bool checkCollisionRect(SDL_Rect r1, SDL_Rect r2);

#endif  // UTILS_H