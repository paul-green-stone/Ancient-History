#include <level_manager.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

// Get the pixel color from and RGB888 formated surface
static SDL_Color getPixelColor(SDL_Surface *surface, int w, int h)
{
    SDL_Color pixel;
    SDL_GetRGB(((Uint32 *)surface->pixels)[w + h * surface->w], surface->format, &pixel.r, &pixel.g, &pixel.b);
    pixel.a = 255;

    return pixel;
}

Level *loadLevel(const char *level_pixel_map, int tile_size)
{
    Level *level = (Level *)malloc(sizeof(Level));
    if (level == NULL)
    {
        perror("ALLOC ERROR: Could not allocate memory for level :");
        return NULL;
    }

    level->tile_size = tile_size;

    // Setup the initial camera position
    level->camera_pos[0] = 0;
    level->camera_pos[1] = 0;

    SDL_Surface *temp = IMG_Load(level_pixel_map);
    if (temp == NULL)
    {
        perror("ALLOC ERROR: Could not load pixel map :");
        free(level);
        return NULL;
    }
    SDL_Surface *surface = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(temp);
    if (surface == NULL)
    {
        perror("ALLOC ERROR: Could not convert pixel map format to RGB :");
        free(level);
        return NULL;
    }

    int width = surface->w;
    int height = surface->h;
    level->width = width;
    level->height = height;

    // Allocate memory for the level map data
    level->map = (uint8_t *)calloc(width * height, sizeof(uint8_t));
    if (level->map == NULL)
    {
        perror("ALLOC ERROR: Could not allocate memory for level map data :");
        SDL_FreeSurface(surface);
        free(level);
        return NULL;
    }

    SDL_LockSurface(surface);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            SDL_Color pixel = getPixelColor(surface, w, h);

            if (pixel.r == 0)
            {
                level->map[w + h * width] = 1;
            }
            else
            {
                level->map[w + h * width] = 0;
            }
        }
    }

    SDL_UnlockSurface(surface);
    SDL_FreeSurface(surface);
    return level;
}

void unloadLevel(Level *level)
{
    free(level->map);
    free(level);
}